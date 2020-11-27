#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "globals.h"

// Gets Surname
void Surname();

// Gets date of birth
void DOB();

// Gets how many guests there are including children
void Guests();

// Assigns one of three boards
void Board();

// Gets duration of stay
void Length();

// Asks if daily wake up is wanted
void WakeUp();

// Books the rooms
void BookingRoom();

// Using Surname and random number creates a Booking ID
void GenerateBookingID();

void SaveThisBooking();
int IsValidDayOfMonth(int day, int month, int year);
int GetAvailableCapacity();

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

      // reset vars
      strcpy_s(ThisBookingID, 66, "");
      strcpy_s(ThisBookingDateOfBirth, 11, "");
      strcpy_s(ThisBookingSurname, 64, "");
      ThisBookingGuestCount = invalid;
      ThisBookingChildren = invalid;
      ThisBookingBoard = invalid;
      ThisBookingLength = invalid;
      ThisBookingWakeUpCalls = invalid;
      RoomNum = 0;

      EmptyStdin();

      // stop searching for an empty slot after we found one
      break;
    }
  }

  if (foundSlot != true) {
    // NO ROOM AT THE INN!
    exit(-1);
  }
}

void CheckIn() {
  srand(time(NULL));

  ThisBookingRooms[0] = invalid;
  ThisBookingRooms[1] = RoomsBooked[1];
  ThisBookingRooms[2] = RoomsBooked[2];
  ThisBookingRooms[3] = RoomsBooked[3];
  ThisBookingRooms[4] = RoomsBooked[4];
  ThisBookingRooms[5] = RoomsBooked[5];
  ThisBookingRooms[6] = RoomsBooked[6];

  Surname();
  DOB();
  Guests();
  Board();
  Length();
  WakeUp();

  BookingRoom();
  GenerateBookingID();

  printf("\n\n=================\n");
  printf("YOUR BOOKING ID: %s\n", ThisBookingID);
  printf("=================\n\n");

  SaveThisBooking();
}

void BookingRoom() {
  int PeopleLeftToHouse = ThisBookingGuestCount;

  while (PeopleLeftToHouse > 0) {
    int valid = false;

    while (!valid) {
      // output message available rooms
      printf("People remaining: %d\n", PeopleLeftToHouse);
      printf("Available rooms:\n");

      // start for loop and uses i to cycle through array of rooms.
      for (int i = 1; i <= 6; ++i) {
        // when room value = 0 print room
        // If the value is 1 it means the room is booked so it will not be displayed
        if (ThisBookingRooms[i] == false) {
          printf("Room %d\t", i);
          printf("Sleeps up to %d people\tGBP %d per night\n", RoomCapacities[i], RoomPrices[i]);
        }
      }

      printf("\nChoose a room to book: \n");
      scanf_s("%d", &RoomNum);
      fflush(stdin);

      // unless they're paying for a building expansion, don't
      // let them do that
      if (RoomNum < 1 || RoomNum > 6) {
        valid = false;
        continue;
      }

      if (ThisBookingRooms[RoomNum] == true) {
        valid = false;
      } else {
        ThisBookingRooms[RoomNum] = true;
        valid = true;
        PeopleLeftToHouse -= ROOM_CAPACITY(RoomNum);
      }
    }
  }
}

void Surname() {
  // Asks for users Surname
  int valid = false;

  while (!valid) {
    // workaround for using fgets after a scanf (consumes new line)
    while ((getchar()) != '\n')
      ;

    printf("What is your surname?\n");

    // up to 63 chars of alphabetical chars, or hyphen
    scanf("%63[A-Za-z]c\n", ThisBookingSurname);
    fflush(stdin);

    _strupr_s(ThisBookingSurname, sizeof(ThisBookingSurname));

    // not empty string
    valid = strcmp(ThisBookingSurname, "") != 0;
  }
}

void DOB() {
  int valid = false;

  while (!valid) {
    // workaround for using fgets after a scanf (consumes new line)
    while ((getchar()) != '\n')
      ;

    // Asks for users DOB
    printf("What is your date of birth?\n");
    printf("Format: YYYY-MM-DD\n");
    // Assigns users DOB
    fgets(ThisBookingDateOfBirth, 11, stdin);

    // workaround for using fgets after a scanf (consumes new line)
    while ((getchar()) != '\n')
      ;

    fflush(stdin);

    int day = 0, month = 0, year = 0, charsParsed = invalid;

    // Adapted from https://codereview.stackexchange.com/a/231086
    // YES CLION, I KNOW I REPEAT THE SAME BRANCH, BUT MAKING IT ONE BRANCH MAKES IT LOOK UGLY
    // SO STOP GIVING ME YOUR "cLaNg-TiDy" MESSAGES!
    if (sscanf_s(ThisBookingDateOfBirth, "%4d-%2d-%2d%n", &year, &month, &day, &charsParsed) !=
        3) {  // NOLINT(bugprone-branch-clone)
      // we dont get 3 inputs
      valid = false;
    } else if (ThisBookingDateOfBirth[charsParsed] != 0) {
      // extra garbage at end
      valid = false;
    } else if (year > 2020 || year < 1900) {
      // eek, maybe i should get current year from system here
      valid = false;
    } else if (month > 12 || month < 1) {
      // month is invalid
      valid = false;
    } else if (!IsValidDayOfMonth(day, month, year)) {
      // invalid day of the month
      valid = false;
    } else {
      // probably valid...
      valid = true;
    }
  }
}

int IsValidDayOfMonth(int day, int month, int year) {
  switch (month) {
    // sept, april, june, nov
    case 9:
    case 4:
    case 6:
    case 11:
      return !(day > 30 || day < 0);

    // feb
    case 2:
      if ((year % 4 == 0 && year % 100 != 0) || (year % 4 == 0 && year % 400 == 0)) {
        // if leap year
        return !(day > 29 || day < 0);
      } else {
        return !(day > 28 || day < 0);
      }

    // "the others"
    default:
      return !(day > 31 || day < 0);
  }
}

void Guests() {
  int ValidGuestCombo = false;

  while (!ValidGuestCombo) {
    int valid = false;

    while (!valid) {
      // Asks for the number of guests
      printf("How many guests? (Adults and children total)\n");
      // Assigns the number of guests
      valid = scanf_s("%d", &ThisBookingGuestCount) == 1;
      fflush(stdin);

      if (ThisBookingGuestCount < 1) {
        valid = false;
      }

      int capacity = GetAvailableCapacity();
      // too many people!
      if (ThisBookingGuestCount > capacity) {
        printf("\nNo room at the inn! There are only %d spaces available.\n", capacity);
        valid = false;
      }
    }

    valid = false;
    while (!valid) {
      // Asks for the number of children
      printf("How many of these guests are children aged 16 or under?\n");
      // Assigns the number of children
      valid = scanf_s("%d", &ThisBookingChildren) == 1;

      fflush(stdin);

      if (ThisBookingChildren < 0) {
        valid = false;
      }
    }

    if (ThisBookingGuestCount <= ThisBookingChildren) {
      printf(
          "\n\nERROR: There cannot be a booking with more children than adults, or only "
          "children!\n");
      ValidGuestCombo = false;
    } else {
      ValidGuestCombo = true;
    }
  }
}

void Board() {
  int valid = false;

  while (!valid) {
    // Asks the user to pick a board
    printf("What board type? (prices per day)\n");
    printf("1. Full Board (GBP %d)\t2. Half Board (GBP %d)\t3. Bed and Breakfast (GBP %d)\n",
           BoardPrices[FullBoard], BoardPrices[HalfBoard], BoardPrices[BedAndBreakfast]);

    // Assigns number to ThisBookingBoard
    valid = scanf_s("%d", &ThisBookingBoard) == 1;
    fflush(stdin);

    // convert input to board
    ThisBookingBoard--;

    if (ThisBookingBoard > BedAndBreakfast || ThisBookingBoard < FullBoard) {
      // out of range -- try again
      valid = false;
    }
  }
}

void Length() {
  int valid = false;

  while (!valid) {
    // Asks for duration of stay
    printf("\nHow long will you be staying (in days)?\n");
    // Assigns users booking length
    valid = scanf_s(" %d", &ThisBookingLength) == 1;
    fflush(stdin);

    if (ThisBookingLength < 1) {
      valid = false;
    }
  }
}

void WakeUp() {
  int valid = false;

  // loop until we get a valid entry
  while (!valid) {
    // Asks if wake up call is wanted
    printf("Do you want a daily wake up call?\n");
    printf("\t1. Yes\t2. No\n");

    // Assigns value depending on option
    valid = scanf_s("%d", &ThisBookingWakeUpCalls) == 1;
    fflush(stdin);

    switch (ThisBookingWakeUpCalls) {
      case 2:
        ThisBookingWakeUpCalls = false;
        break;

      case 1:
        ThisBookingWakeUpCalls = true;
        break;

      default:
        valid = false;
        break;
    }
  }
}

void GenerateBookingID() {
  // Creates a random number between 1 and 99 incl.
  int RandomNum = (rand() % 99) + 1;

  // create booking ID with Surname and 2 random numbers
  sprintf(ThisBookingID, "%s%02d", ThisBookingSurname, RandomNum);
}

int GetAvailableCapacity() {
  int cap = 0;

  for (int i = 1; i <= 6; i++) {
    if (RoomsBooked[i] == false) {
      cap += ROOM_CAPACITY(i);
    }
  }

  return cap;
}