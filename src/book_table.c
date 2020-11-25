#include "book_table.h"
#include <stdio.h>
#include <string.h>
#include "globals.h"

/*
 * I should definitely refactor these two functions
 * into one, using a param for the time... but that's
 * effort, and effort is not my specialty.
 *
 * Oh, and time restraints prevent me, too.
 */
void BookTableFor7(int index);
void BookTableFor9(int index);

void BookTable() {
  printf("\n\nBOOK DINNER TABLE\n");
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

  const int Board = BookingBoard[BookingIndex];

  if (Board != FullBoard && Board != HalfBoard) {
    printf(
        "\nERROR: You may only book a dinner table if you have paid for Full Board or Half "
        "Board.\n");
    return;
  }

  int Guests = BookingGuestCounts[BookingIndex];

  int TablesAvailable7PM = 0;
  int TablesAvailable9PM = 0;

  int AlreadyBooked = false;
  int ExistingBookingTable = invalid;
  int ExistingBookingTime = invalid;

  for (int i = 0; i <= TABLE_TATOOINE; i++) {
    if (strcmp(TableBookings7[i], "") == 0) {
      TablesAvailable7PM += 1;
    }

    if (strcmp(TableBookings9[i], "") == 0) {
      TablesAvailable9PM += 1;
    }

    // if already booked
    if (strcmp(TableBookings7[i], BookingIDs[BookingIndex]) == 0) {
      AlreadyBooked = true;
      ExistingBookingTable = i;
      ExistingBookingTime = 7;
    } else if (strcmp(TableBookings9[i], BookingIDs[BookingIndex]) == 0) {
      AlreadyBooked = true;
      ExistingBookingTable = i;
      ExistingBookingTime = 9;
    }

    if (AlreadyBooked) {
      break;
    }
  }

  // don't let people book tables multiple times... one dinner is enough for them!
  if (AlreadyBooked) {
    printf(
        "\nERROR: There is already a reservation for the %s table associated with this booking at "
        "%d pm.\n\n",
        ExistingBookingTable == TABLE_ENDOR
            ? "Endoor"
            : (ExistingBookingTable == TABLE_NABOO ? "Naboo" : "Tatooine"),
        ExistingBookingTime);
    return;
  }

  int SpaceAt7 = TablesAvailable7PM * TABLE_CAPACITY > Guests;
  int SpaceAt9 = TablesAvailable9PM * TABLE_CAPACITY > Guests;

  if (SpaceAt7 == false && SpaceAt9 == false) {
    printf("\nERROR: No available tables for your booking size.\n\n");
    return;
  }

  int input = invalid;

  while (input != 1 && input != 2) {
    printf("\nYou have %d guests in your booking.\nTables available:\n",
           BookingGuestCounts[BookingIndex]);

    if (SpaceAt7) {
      printf("1. 7PM - %d\n", TablesAvailable7PM);
    }
    if (SpaceAt9) {
      printf("2. 9PM - %d\n\n", TablesAvailable9PM);
    }

    printf("Choose a time:");
    int entries = scanf("%d", &input);
    EmptyStdin();
    fflush(stdin);

    if (entries == 0 || entries > 1) {
      input = invalid;
      continue;
    }

    if (input == 1 && !SpaceAt7) {
      input = invalid;
    }
    if (input == 2 && !SpaceAt9) {
      input = invalid;
    }
  }

  // Yes, I have covered all possible pathways CLion. Shush.
  switch (input) {  // NOLINT(hicpp-multiway-paths-covered)
    case 1:
      BookTableFor7(BookingIndex);
      break;

    case 2:
      BookTableFor9(BookingIndex);
      break;
  }

  printf("\n\n");
}

void BookTableFor7(int index) {
  int EndoorAvailable = strcmp(TableBookings7[TABLE_ENDOR], "") == 0;
  int NabooAvailable = strcmp(TableBookings7[TABLE_NABOO], "") == 0;
  int TatooineAvailable = strcmp(TableBookings7[TABLE_TATOOINE], "") == 0;

  int tableChoice = invalid;
  int GuestsRemainingToSeat = BookingGuestCounts[index];

  char BookingID[66] = "";
  strcpy(BookingID, BookingIDs[index]);

  while (tableChoice == invalid && GuestsRemainingToSeat > 0) {
    printf("You have %d guests not booked at a table.\n\n", GuestsRemainingToSeat);

    if (EndoorAvailable) {
      printf("1. Endoor table -- seats 4\n");
    }
    if (NabooAvailable) {
      printf("2. Naboo table -- seats 4\n");
    }
    if (TatooineAvailable) {
      printf("3. Tatooine table -- seats 4\n");
    }

    printf("\nChoose table:");
    scanf("%d", &tableChoice);
    EmptyStdin();
    fflush(stdin);

    switch (tableChoice) {
      case 1:
        if (!EndoorAvailable) {
          // they shouldn't choose this table
          tableChoice = invalid;
          continue;
        }
        strcpy(TableBookings7[TABLE_ENDOR], BookingID);
        GuestsRemainingToSeat -= TABLE_CAPACITY;
        printf("Endoor table booked for 4 at 7 PM for Booking \"%s\".", BookingID);
        break;

      case 2:
        if (!NabooAvailable) {
          // they shouldn't choose this table
          tableChoice = invalid;
          continue;
        }
        strcpy(TableBookings7[TABLE_NABOO], BookingID);
        GuestsRemainingToSeat -= TABLE_CAPACITY;
        printf("Naboo table booked for 4 at 7 PM for Booking \"%s\".", BookingID);
        break;

      case 3:
        if (!TatooineAvailable) {
          // they shouldn't choose this table
          tableChoice = invalid;
          continue;
        }
        strcpy(TableBookings7[TABLE_TATOOINE], BookingID);
        GuestsRemainingToSeat -= TABLE_CAPACITY;
        printf("Tatooine table booked for 4 at 7 PM for Booking \"%s\".", BookingID);
        break;

      default:
        tableChoice = invalid;
        break;
    }
  }
}

void BookTableFor9(int index) {
  int EndoorAvailable = strcmp(TableBookings9[TABLE_ENDOR], "") == 0;
  int NabooAvailable = strcmp(TableBookings9[TABLE_NABOO], "") == 0;
  int TatooineAvailable = strcmp(TableBookings9[TABLE_TATOOINE], "") == 0;

  int tableChoice = invalid;
  int GuestsRemainingToSeat = BookingGuestCounts[index];

  char BookingID[66] = "";
  strcpy(BookingID, BookingIDs[index]);

  while (tableChoice == invalid && GuestsRemainingToSeat > 0) {
    printf("You have %d guests not booked at a table.\n\n", GuestsRemainingToSeat);

    if (EndoorAvailable) {
      printf("1. Endoor table -- seats 4\n");
    }
    if (NabooAvailable) {
      printf("2. Naboo table -- seats 4\n");
    }
    if (TatooineAvailable) {
      printf("3. Tatooine table -- seats 4\n");
    }

    printf("\nChoose table:");
    scanf("%d", &tableChoice);
    EmptyStdin();
    fflush(stdin);

    switch (tableChoice) {
      case 1:
        if (!EndoorAvailable) {
          // they shouldn't choose this table
          tableChoice = invalid;
          continue;
        }
        strcpy(TableBookings9[TABLE_ENDOR], BookingID);
        GuestsRemainingToSeat -= TABLE_CAPACITY;
        printf("Endoor table booked for 4 at 9 PM for Booking \"%s\".", BookingID);
        break;

      case 2:
        if (!NabooAvailable) {
          // they shouldn't choose this table
          tableChoice = invalid;
          continue;
        }
        strcpy(TableBookings9[TABLE_NABOO], BookingID);
        GuestsRemainingToSeat -= TABLE_CAPACITY;
        printf("Naboo table booked for 4 at 9 PM for Booking \"%s\".", BookingID);
        break;

      case 3:
        if (!TatooineAvailable) {
          // they shouldn't choose this table
          tableChoice = invalid;
          continue;
        }
        strcpy(TableBookings9[TABLE_TATOOINE], BookingID);
        GuestsRemainingToSeat -= TABLE_CAPACITY;
        printf("Tatooine table booked for 4 at 9 PM for Booking \"%s\".", BookingID);
        break;

      default:
        tableChoice = invalid;
        break;
    }
  }
}
