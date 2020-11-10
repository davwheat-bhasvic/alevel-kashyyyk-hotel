#include <stdio.h>
#include <string.h>

#include "header.h"

int main() {
  printf("%d\n", RoomPrices[2]);           // price of room 2
  printf("%d\n", BoardPrices[FullBoard]);  // price of FullBoard

  strcpy(BookingIDs[0], "Wheatley49");

  printf(BookingIDs[0]);

  return 0;
}
