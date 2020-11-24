#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "check_in.h"
#include "check_out.h"
#include "globals.h"

int main() {
  setbuf(stdout, NULL);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
  while (true) {
    puts("Choose an option");
    puts("1. Check in");
    puts("2. Check out");
    puts("3. Book dinner table");
    puts("4. Exit");

    int option = 0;
    printf("$ ");
    scanf_s("%d", &option);

    switch (option) {
      case 1:
        CheckIn();
        break;

      case 2:
        CheckOut();
        break;
        //        break;
      case 3:
        //        break;

      default:
      case 4:
        // we just want to loop back to start
        printf("\n\n\n\n\n\n\n\n");
        break;
    }
  }
#pragma clang diagnostic pop
}
