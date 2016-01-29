#include "pollardSerial.h"

/*****************************************
 * 
 * 
 *Calculating GCD
 * 
 * 
 * 
 *****************************************/
long long int gcd (long long int a , long long int b)
{
	long long int i,g;
	for ( i=1;i <= a || i <=b ; ++i)
	{
		if (a%i==0 && b%i==0)
		g=i;
	}

	return g;
	}
	
/*****************************************
 * 
 * 
 *Pollard's p-1 algorithm
 * 
 * 
 * 
 *****************************************/
long long int pollard ( long long int n)
{


	long long int bound=50;
    long long int i,j;
    long long int *primearray;
    long long int highestPrime,t;
    long long int x;
    
    long long int g;
    

    
    long long int a =2,p,q;
    long long int b,e,c =1;
    long long int power,temp;
    highestPrime = prime(bound, &primearray);  temp = 1;
    bound = highestPrime;
    x= primearray[0];
    
    for(i=0;x<bound;i++)
    {


		power=(long long int)(log10(bound)/log10(x));
        if(power!=0)
        {
			temp =(long long int)pow(x,power);
			for(j=1;j<=temp;j++)
                {
                  c= (c*2)%n;
                }
                a=c;
               
                g = gcd(a-1,n);
                if((1 < g) && (g < n))
                {
                        return g;
                }

		}

        x = primearray[i+1];
    }
  
    return 0;
} 			
