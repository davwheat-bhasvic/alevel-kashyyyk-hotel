#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "globals.h"

// Gets surname
void surname();

// Gets date of birth
void DOB();

// Gets how many guests there are including children
void Guests();

// Assigns one of three boards
void Board();

// Gets duration of stay
void Length();

// Asks if daily wake up is wanted
void wakeup();

// Books the rooms
void BookingRoom();

// Using surname and random number creates a Booking ID
void BookingID();

void SaveThisBooking();

//// list of all booking IDs
char ThisBookingID[66] = {""};
//
//// booking dates of birth
char ThisBookingDateOfBirth[11];
//
//// list of all booking surnames
char ThisBookingSurname[64];

// list of all booking guest counts
int ThisBookingGuestCount;

// number of children in bookings
int ThisBookingChildren;

// booking board types
int ThisBookingBoard;

// booking lengths (in days)
int ThisBookingLength;

// whether they want daily wake-up calls (0 = no, 1 = yes)
int ThisBookingWakeUpCalls;

// 1 means the room is booked so all rooms are set to 0 for the start
int ThisBookingRooms[7] = {0};

// the room number currently chosen
int RoomNum = 0;

void SaveThisBooking() {
  int foundSlot = false;

  for (int i = 0; i < ARRAY_SIZE(BookingIDs); i++) {
    if (strcmp(BookingIDs[i], "") == 0) {
      // empty booking slot found
      // we should save this booking here
      foundSlot = true;

      strcpy_s(BookingIDs[i], sizeof(BookingIDs[0]), ThisBookingID);
      strcpy_s(BookingSurnames[i], sizeof(BookingSurnames[0]), ThisBookingSurname);
      BookingGuestCounts[i] = ThisBookingGuestCount;
      BookingChildren[i] = ThisBookingChildren;
      strcpy_s(BookingDatesOfBirth[i], sizeof(BookingDatesOfBirth[0]), ThisBookingDateOfBirth);
      BookingBoard[i] = ThisBookingBoard;
      BookingLengths[i] = ThisBookingLength;
      BookingWakeUpCalls[i] = ThisBookingWakeUpCalls;

      int counter = 0;
      for (int room = 1; room <= 6; room++) {
        BookingRooms[i][counter] = ThisBookingRooms[room];

        if (ThisBookingRooms[room] == true) {
          RoomsBooked[room] = true;
          counter++;
        }
      }

      // stop searching for an empty slot after we found one
      break;
    }
  }

  if (foundSlot != true) {
    // THIS IS BAD!
    exit(-1);
  }
}

void CheckIn() {
  srand(time(NULL));

  surname();
  DOB();
  Guests();
  Board();
  Length();
  wakeup();

  BookingRoom();
  // create int counter that = 0
  int counter = 0;
  // Forever loop
  while (true) {
    // Asks if they would like to book more rooms
    printf("Would you like to book another room?\n1. Yes\n2. No");
    // checks for yes or no
    fflush(stdin);
    scanf_s("%d", &counter);
    fflush(stdin);
    // if yes(1) go through room booking again
    if (counter == 1) {
      BookingRoom();
      printf("%d", RoomNum);
    }
    // if no(2) break out of loop
    else if (counter == 2) {
      break;
    } else {
      counter = -1;
    }
  }

  BookingID();

  printf("\n\n=================\n");
  printf("YOUR BOOKING ID: %s\n", ThisBookingID);
  printf("=================\n\n");

  SaveThisBooking();
}

void BookingRoom() {
  // output message available rooms
  printf("available rooms\n");

  // start for loop and uses i to cycle through array of rooms.
  for (int i = 1; i <= 6; ++i) {
    // when room value = 0 print room
    // If the value is 1 it means the room is booked so it will not be displayed
    if (ThisBookingRooms[i] == 0) {
      printf("Room %d\t", i);
      printf("Sleeps up to %d people | GBP %d per night\n\n", RoomCapacities[i], RoomPrices[i]);
    }
  }
  printf("enter room number\n");
  scanf_s("%d", &RoomNum);
  fflush(stdin);

  switch (RoomNum) {
    case 1:
      ThisBookingRooms[1] = true;
      break;
    case 2:
      ThisBookingRooms[2] = true;
      break;
    case 3:;
      ThisBookingRooms[3] = true;
      break;
    case 4:
      ThisBookingRooms[4] = true;
      break;
    case 5:
      ThisBookingRooms[5] = true;
      break;
    default:
    case 6:
      ThisBookingRooms[6] = true;
      break;
  }
}

void surname() {
  // Asks for users surname
  printf("What is your surname?\n");
  // Assigns users surname
  scanf("%s", &ThisBookingSurname);
}

void DOB() {
  // Asks for users DOB
  printf("What is your date of birth?\n");
  printf("Format: YYYY-MM-DD\n");
  // Assigns users DOB
  scanf("%s", &ThisBookingDateOfBirth);
}

void Guests() {
  // Asks for the number of guests
  printf("How many guests?\n");
  // Assigns the number of guests
  scanf_s("%d", &ThisBookingGuestCount);
  fflush(stdin);

  // Asks for the number of children
  printf("How many of these guests are children aged 16 or under?\n");
  // Assigns the number of children
  scanf_s("%d", &ThisBookingChildren);
  fflush(stdin);
}

void Board() {
  // Asks the user to pick a board
  printf("What board type? (prices per day)\n");
  printf("1. Full Board (GBP %d)\t2. Half Board (GBP %d)\t3. Bed and Breakfast (GBP %d)\n",
         BoardPrices[FullBoard], BoardPrices[HalfBoard], BoardPrices[BedAndBreakfast]);

  // Assigns number to ThisBookingBoard
  scanf_s("%d", &ThisBookingBoard);
  fflush(stdin);

  // convert input to board
  ThisBookingBoard--;

  if (ThisBookingBoard > BedAndBreakfast || ThisBookingBoard < FullBoard) {
    ThisBookingBoard = BedAndBreakfast;
  }
}

void Length() {
  // Asks for duration of stay
  printf("How long will you be staying (in days)?\n");
  // Assigns users booking length
  scanf_s("%d", &ThisBookingLength);
}

void wakeup() {
  // Asks if wake up call is wanted
  printf("Do you want a daily wake up call?\n");
  printf("\t1)Yes\t2)No\n");

  // Assigns value depending on option
  scanf_s("%d", &ThisBookingWakeUpCalls);
  fflush(stdin);

  // Goes through case to set 0 if no and 1 if yes
  // Defaults to 0 if invalid
  switch (ThisBookingWakeUpCalls) {
    default:
    case 2:
      ThisBookingWakeUpCalls = 0;
      break;

    case 1:
      ThisBookingWakeUpCalls = 1;
      break;
  }
}

void BookingID() {
  // Creates a random number between 1 and 99 incl.
  int RandomNum = (rand() % 99) + 1;

  // create booking ID with surname and 2 random numbers
  sprintf(ThisBookingID, "%s%02d", ThisBookingSurname, RandomNum);
}
