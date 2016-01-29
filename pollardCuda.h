#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define NUM_THREADS 32



/*
 * 
 * 
 * 
 * 
 * Calculating GCD
 * 
 * 
 * 
 * 
 * 
 */ 


__device__ long long int gcd ( long long int u , long long int v)
{
	long long  int shift;
	long long int diff;
	if (u == 0 || v == 0){
			return u | v;
		}

	for (shift = 0; ((u | v) & 1) == 0; ++shift) {
			u >>= 1;
			v >>= 1;
		}

	while ((u & 1) == 0){
			u >>= 1;
		}

	do {
			while ((v & 1) == 0){
				v >>= 1;
			}

			if (u < v) {
				v -= u;
			} else {
				 diff = u - v;
				u = v;
				v = diff;
			}
			v >>= 1;
		} while (v != 0);

		return u << shift;
}

/*
 * 
 * 
 * Pollard's p-1 algorithm
 * 
 * 
 * 
 * 
 * 
 * 
 */ 

__global__ void pollard_gpu(long long int *d_primearray, long long int highestPrime, long long int bound, long long int *res, long long int n)
{


    long long int a =2,g,j;
    long long int x,c =1;
    long long int power,temp,tot_th;
    tot_th = bound;	
    temp = 1;
    bound = highestPrime;
    long long int tid = blockIdx.x*blockDim.x+threadIdx.x;
    x=d_primearray[tid];
    
    if( x< bound && tid < tot_th)
    {
          
            power=(long long int)(log10((double)bound)/log10((double)x));
            
		
            if(power!=0)
            {
                temp =(long long int)pow((double)x,(double)power);
                
                for(j=1;j<=temp;j++)
                {
                  c= (c*2)%n;
                }
                a=c;

                g = gcd(a-1,n); 
		
                if((1 < g) && (g < n))
                {
                     printf("factor=%lld\n",g);
					*res = g;
			
                }

            }

    }
//printf("factor=%ld\n",g); */
}
