#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "globals.h"

// Get the price of the booking at the passed index
double CalculatePrice(int index);
// Get the age of the main booker
int EligibleForConcessionDiscount(int index);

void CheckOut() {
  printf("\n\nCHECK OUT\n");
  printf("Enter booking ID: ");

  // workaround for using fgets after a scanf (consumes new line)
  EmptyStdin();

  char bookingId[66] = "";
  scanf("%65[A-Za-z0-9]c\n", bookingId);
  fflush(stdin);

  const int BookingIndex = FindBookingIndex(bookingId);

  if (BookingIndex == invalid) {
    // invalid booking ID
    printf("\nInvalid booking ID. Please contact a staff member.\n\n");

    EmptyStdin();
    return;
  }

  CalculatePrice(BookingIndex);

  for (int i = 0; i < 6; i++) {
    // free up rooms
    if (BookingRooms[BookingIndex][i] == true) {
      printf("Freed up Room #%d\n\n", i + 1);
      RoomsBooked[i + 1] = false;
    }
  }

  // Delete booking from system
  strcpy_s(BookingIDs[BookingIndex], 66, "");

  EmptyStdin();
}

double CalculatePrice(int index) {
  double AllRoomCost = 0;
  double BoardCost = 0;
  double WakeUpCallCost = 0;

  // add room prices to price per day
  for (int i = 0; i < 6; i++) {
    int roomNum = BookingRooms[index][i];

    if (roomNum > 0 && roomNum < 7) {
      AllRoomCost += (double)RoomPrices[roomNum];
    }
  }

  // add price of board to price per day
  int BoardPrice = BoardPrices[BookingBoard[index]];

  // add adult board cost
  BoardCost += BoardPrice * (BookingGuestCounts[index] - BookingChildren[index]);

  // add child board cost (they get 50% off)
  BoardCost += CHILD_BOARD_DISCOUNT * BoardPrice * (BookingChildren[index]);

  // add wake-up call cost
  if (BookingWakeUpCalls[index] == true) {
    WakeUpCallCost = WAKE_UP_CALL_PRICE;
  }

  int concessionEligibility = EligibleForConcessionDiscount(index);

  if (concessionEligibility == invalid) {
    printf(
        "\nWARN: Invalid date of birth! Please contact a staff member if you are age 65 or over.");
  } else if (concessionEligibility == true) {
    AllRoomCost *= CONCESSION_DISCOUNT;
  }

  int StayLength = BookingLengths[index];

  double costBeforeDiscounts = ((AllRoomCost + BoardCost) * StayLength) + WakeUpCallCost;
  double costAfterDiscounts = costBeforeDiscounts;

  // if 65+, we overwrite after discount price with the discounted cost
  if (concessionEligibility == true) {
    costAfterDiscounts =
        (((AllRoomCost * CONCESSION_DISCOUNT) + BoardCost) * StayLength) + WakeUpCallCost;
  }

  // PRINT SUBTOTALS AND FINAL TOTAL
  printf("\n\n");
  printf("===============================\n");
  printf("         R E C E I P T         \n\n");
  printf("Booking ID: %s\n\n", BookingIDs[index]);
  printf("Room price        GBP %.2f\n", AllRoomCost * StayLength);
  printf("Board cost        GBP %.2f\n", BoardCost * StayLength);

  if (WakeUpCallCost > 0) {
    printf("Wake-up calls     GBP %.2f\n", WakeUpCallCost);
  }

  printf("\n");
  printf("Subtotal          GBP %.2f\n", costBeforeDiscounts);

  if (concessionEligibility == true) {
    printf("65+ discount      GBP %.2f\n", costAfterDiscounts - costBeforeDiscounts);
    printf("\n");
  }

  printf("Total             GBP %.2f\n\n", costAfterDiscounts);
  printf("===============================\n\n");

  return costAfterDiscounts;
}

int EligibleForConcessionDiscount(int index) {
  char DOB[11] = "";
  strcpy(DOB, BookingDatesOfBirth[index]);

  char yearOfBirth[5] = "";
  char monthOfBirth[3] = "";
  char dayOfBirth[3] = "";

  int year = 0, month = 0, day = 0;

  // assign values from DOB string - ex = 1992-08-21
  yearOfBirth[0] = DOB[0];   // 1
  yearOfBirth[1] = DOB[1];   // 9
  yearOfBirth[2] = DOB[2];   // 9
  yearOfBirth[3] = DOB[3];   // 2
  year = atoi(yearOfBirth);  // convert str year to int year

  monthOfBirth[0] = DOB[5];    // 0
  monthOfBirth[1] = DOB[6];    // 8
  month = atoi(monthOfBirth);  // convert str month to int month

  dayOfBirth[0] = DOB[8];  // 2
  dayOfBirth[1] = DOB[9];  // 1
  day = atoi(dayOfBirth);  // convert str day to int day

  if (day == 0 || month == 0 || year == 0) {
    // erm... DOB is invalid... argh!
    return invalid;
  }

  time_t t = time(NULL);
  struct tm CurrentTime;
  localtime_s(&CurrentTime, &t);

  int currentYear = CurrentTime.tm_year + 1900;  // get current year (+1900 because C is C...)
  int currentMonth = CurrentTime.tm_mon + 1;     // get current month (+1 because it's 0-indexed)
  int currentDay = CurrentTime.tm_mday;          // get current date of month

  int yearDiff = currentYear - year;

  if (yearDiff > 65) {  // definitely 65+ if year gap is 66 or more
    return true;
  } else if (yearDiff < 65) {  // definitely NOT 65+ if year gap is 64 or less
    return false;
  } else {  // gap is 65 -- might be 65+
    int monthGap = currentMonth - month;

    if (monthGap < 0) {  // birth month is after current month - not 65+
      return false;
    } else if (monthGap > 0) {  // birth month is before current month - is 65+
      return true;
    } else {  // birth month is current month -- more checks needed

      int dateGap = currentDay - day;

      if (dateGap < 0) {  // birth date is after current date - not 65+
        return false;
      } else {  // either after birthday or today is birthday
        return true;
      }
    }
  }
}