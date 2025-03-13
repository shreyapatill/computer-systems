#include <stdio.h>
#include <stdlib.h>

/*
Partners: nbadam2, mp31
We begin by setting the coefficient to 1 in order to perform multiplication, used to find the 
product over a set of terms. Then we set up a nested for loop to calculate and print each coefficient. 
*/

int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);

  unsigned long coefficient = 1;
  for( int k = 0; k <= row; k++ ){ // calculate coefficients by interating [0,n]
    for( int i = 1; i <= k; i++ ){ // iterate i [1,k] to calculate product of coefficient
      coefficient *= (row - i + 1); // apply formular to calculate binomial coefficient
      coefficient /= i;
    }
    printf( "%lu ", coefficient ); // print coefficient followed by space
    coefficient = 1; // reset coefficent to 1 for next calculation
  }

  return 0;
}
