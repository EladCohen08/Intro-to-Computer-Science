/******************
Name: Elad Cohen
ID: 331526079
Assignment: ex1
*******************/
#include <stdio.h>

// REMIDER : YOU CANT USE ANY CONTROL FLOW OPERATIONS OR FUNCTIONS, ONLY BITWISE.

int main() {

  // What bit

  /*Scan two integers (representing number and a position)
  Print the bit in this position. */

  printf("What bit:\n");
  int num, pos;

  printf("Please enter a number:\n");
  scanf("%d", &num);

  printf("Please enter a position:\n");
  scanf(" %d", &pos);

  printf("The bit in position %d of number %d is: %d\n", pos, num, (num >> pos)&1);


  // Set bit
  printf("\nSet bit:\n");

  printf("Please enter a number:\n");
  scanf(" %d", &num);

  printf("Please enter a position:\n");
  scanf(" %d", &pos);

  int dig = (num >> pos) & 1;
  int opposite_dig = !dig;

  int opp_num_single_dig = 1 << pos;
  int opposite_num = num ^ opp_num_single_dig;

  printf("Number with bit %d set to %d: %d\n", pos, opposite_dig, opposite_num);
  printf("Number with bit %d set to %d: %d\n", pos, dig, num);


  /*Scan two integers (representing number and a position)
  Make sure the bit in this position is "on" (equal to 1)
  Print the output
  Now make sure it's "off" (equal to 0)
  Print the output */

  // Toggle bit
  printf("\nToggle bit:\n");

  printf("Please enter a number:\n");
  scanf("%d", &num);

  printf("Please enter a position:\n");
  scanf(" %d", &pos);


  int num_toggled = num ^ (1 << pos);

  printf("Number with bit %d toggled: %d\n", pos, num_toggled);

  /*Scan two integers (representing number and a position)
  Toggle the bit in this position
  Print the new number */

  // Even - Odd
  printf("\nEven - Odd:\n");
  /* Scan an integer
  If the number is even - print 1, else - print 0. */

  printf("Please enter a number:\n");
  scanf("%d", &num);

    int odd_even = !(num & 1);
  printf("%d\n", odd_even);

  // 3, 5, 7, 11
  printf("\n3, 5, 7, 11:\n");
  /* Scan two integers in octal base
  sum them up and print the result in hexadecimal base
  Print only 4 bits, in positions: 3,5,7,11 in the result. */

  int num1, num2;

  printf("Please enter the first number (octal): \n");
  scanf("%o", &num1);

  printf("Please enter the second number (octal): \n");
  scanf(" %o", &num2);

  int sum = num1 + num2;

  printf("The sum in hexadecimal: %X\n", sum);

  printf("The 3,5,7,11 bits are: ");
  printf("%d", (sum >> 3) & 1);
  printf("%d", (sum >> 5) & 1);
  printf("%d", (sum >> 7) & 1);
  printf("%d\n", (sum >> 11) & 1);


  printf("Bye!\n");
  
  return 0;
}
