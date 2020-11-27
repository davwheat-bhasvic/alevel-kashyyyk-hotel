#include <stdio.h>

#include "book_table.h"
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
    printf("$ ");

    // using fgets with sscanf_s prevents infinite loop when invalid
    // entry is supplied
    char input[2] = {0};
    int option = 0;
    fgets(input, 2, stdin);
    int valid = sscanf_s(input, "%d", &option);
    fflush(stdin);

    if (valid != 1) {
      printf("\n\n\n\n\n\n\n\n");
      continue;
    }

    printf("\n");

    switch (option) {
      case 1:
        CheckIn();
        break;

      case 2:
        CheckOut();
        break;
      case 3:
        BookTable();
        break;

      default:
      case 4:
        // we just want to loop back to start
        printf("\n\n\n\n\n\n\n\n");
        break;
    }
  }
#pragma clang diagnostic pop
}
