// PREP FOR EXAM
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("Hello World\n");
  char a[] = "Hello World";
  char *firstVal = a;
  for (int i = 0; i < 3; i++) {
    *(a++) = 'X'
    for (int j = 1; j < 10; j++) {
      printf("%c", *(firstVal + j));
    }
  }

  return 0;
}