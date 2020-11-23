//
// Created by dwhea on 20/11/2020.
//
#include <stdio.h>
#include <string.h>
#include "globals.h"

// Get the price of the booking at the passed index
int CalculatePrice(int index);
// Find the index of a booking by its booking ID, or -1 if not found
int FindBookingIndex(char bookingID[66]);

void CheckOut() {
  printf("\n\nCHECK OUT\n");
  printf("Enter booking ID: ");

  char bookingId[66] = "";
  scanf("%s", bookingId);
  fflush(stdin);

  const int BookingIndex = FindBookingIndex(bookingId);

  if (BookingIndex == -1) {
    // invalid booking ID
    printf("\nInvalid booking ID. Please contact a staff member.\n\n");
    return;
  }

  int Price = CalculatePrice(BookingIndex);

  printf("\n\nIndex: %d", BookingIndex);
  printf("\nPrice per day: GBP %d", Price);
}

int CalculatePrice(int index) {
  int pricePerDay = 0;

  for (int i = 0; i < 6; i++) {
    int roomNum = BookingRooms[index][i];

    if (roomNum > 0 && roomNum < 7) {
      pricePerDay += RoomPrices[roomNum];
    }
  }

  return -1;
}

int FindBookingIndex(char bookingID[66]) {
  for (int i = 0; i < MAX_BOOKINGS; i++) {
    if (strcmp(BookingIDs[i], bookingID) == 0) {
      return i;
    }
  }

  return -1;
}