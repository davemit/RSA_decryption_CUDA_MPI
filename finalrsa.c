#include<stdio.h>
#include "pollardSerial.h"
//#include"file.h"

#define MAX_LENGTH 100;
long long int e[100],d[100],temp[100];
char en[100];




int Isprime (long long int);



/************************************
 * 
 * Prime number Generation.
 * 
 * 
 * 
 * 
 ****************************************************/
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
	
	long long int fac1;
	long long int other_factor,after_e,g1;
	long long int p, q, n;
	int flag;
	
	long long int t;
	
	double start, end, time;
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
	
	//decrypt(after_e);
	g1 = gcd( p, q);
    fac1 = pollard(n);
	printf("Factor is : %lld", fac1);
	other_factor = n/ fac1;
	
	after_e = (fac1-1)*(other_factor-1);
	start = clock();
	
	end = clock(); 
	time = (double) (end-start)/CLOCKS_PER_SEC;
	printf("\nTime taken = %f\n", time);
	
	return 0;
}

