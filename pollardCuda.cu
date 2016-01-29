#include "pollardCuda.h"



int Isprime (long long int);


long long int prime(long long int num,long long int** primearray)

{
    long long int   count, c;
    long long int i=3;
    long long int *tmp = (long long int*) malloc(num*(sizeof(long long int)));
    
    for ( count = 2 ; count <= num ;  )
    {
        for ( c = 2 ; c <= i - 1 ; c++ ) {
        if ( i%c == 0 )
        break;
        }
        if ( c == i )
        {
           
            tmp[0]=2;
            tmp[count-1]=i;

            *primearray=tmp;
            
            count++;
        }
        i++;
    }
        //printf("abcd %ld",tmp[8]);
    return tmp[count-2];
}

/*****************************************
 * 
 * 
 *Checking if the number is prime number 
 * 
 * 
 * 
 * 
 * 
 *****************************************/
int IsPrime(long long int num)
{
	long long int j;
	long long int k;
	k = sqrt(num);
	
	for (j=2;j<=k;j++)
	{
		//printf("\nHere");
		if(num%j==0)
		return 0;
	}
	return 1;
}



int main()
{
	long long int *d_primearray;
	long long int *h_primearray;
	long long int bound=75;
	long long int h_highestPrime; 
	long long int *res;
	
	
	
	
	long long int other_factor,after_e;
	long long int p, q, n;
	int flag;
	
	long long int t;
	
	
	printf("Enter the prime number\n");
	scanf("%lld",&p);
	
	flag = IsPrime(p);
	if( flag == 0)
	{
		printf("wrong input");
		exit(0);
	}
	printf("Enter another prime number\n");
	scanf("%lld",&q);
	flag = IsPrime(q);
	if(flag ==0 || p==q)
	{
		printf("wrong input");
		exit(0);
	}
	
	
	n= p*q;
	t = (p-1)*(q-1);
	
	
	/*************************************************/
	
	h_highestPrime = prime(bound, &h_primearray);
	
 	cudaEvent_t start,stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start);
    cudaMalloc((void**)&d_primearray,bound*sizeof(long long int));
    cudaMalloc((void**)&res,sizeof(long long int));
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float time_cmalloc = 0;
    cudaEventElapsedTime(&time_cmalloc,start,stop);
	cudaEventRecord(start);
    cudaMemcpy(d_primearray,h_primearray,bound*sizeof(long long int),cudaMemcpyHostToDevice);
	cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float time_htod=0;
	double NUM_BLOCKS;
	NUM_BLOCKS = ceil((double)bound /NUM_THREADS);
	
    cudaEventElapsedTime(&time_htod,start,stop);
    
	cudaEventRecord(start);
	
    pollard_gpu<<<(int)NUM_BLOCKS,NUM_THREADS>>>(d_primearray,h_highestPrime,bound,res, n);
	cudaError_t err = cudaGetLastError();
	if (err != cudaSuccess) {
        printf("Error: %s\n", cudaGetErrorString(err));
	}
	cudaDeviceSynchronize();
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    
    
    float time_kernel = 0;
    cudaEventElapsedTime(&time_kernel,start,stop);
	long long int *gpu_res;
	gpu_res = (long long int*) malloc(sizeof(long long int));
	cudaEventRecord(start);
    cudaMemcpy(gpu_res,res,sizeof(long long int),cudaMemcpyDeviceToHost);
	printf("Factor = %lld\n",*gpu_res);
	
	
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float time_dtoh = 0;
    cudaEventElapsedTime(&time_dtoh,start,stop);
	cudaFree(d_primearray);
	cudaFree(res);
	other_factor = n/ (*gpu_res);
	after_e = ((*gpu_res)-1)*(other_factor-1);
	
	
  	printf("Device malloc = %f ms\n",time_cmalloc);
    printf("Device to Host = %f ms\n",time_htod);
    printf("Kernel execution = %f ms\n",time_kernel);        
	printf("Host to Device = %f ms\n",time_dtoh);
    return 0;                                          
}

