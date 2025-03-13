#include <stdlib.h>
#include <stdio.h>
/*
Partners: nbadam2, mp31
In the main.c program, the only error was that line 26 was missing a semi-colon.It caused a compiler error.
The is_prime function was returning 1 for prime values and 0 for non-prime values. We just switched the return statements in line 21 and line 24
The print_semiprimes function was returning 0 at all times since ret was not altered in the code. ret is supposed to be 1 if there is a semiprime, so we change ret to equal to 1 at line 28 since that is the point where we determine if thethere is a semiprime value or not. 
The print_semiprimes function was also printing out all the integers a through b. We determined that the issues was at line 43. Since we already know that i%j=0 because of the if condition, the value will always be printed out since k is always prime.  
The print_semiprimes function was also returning the correct values twice. We added line 48 to stop the loop after printing the value once. 
*/


/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=  b; i++) { //for each item in interval
        //check if semiprime
      for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        printf("%d ", i);
			ret = 1;
			j = i + 1;
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
