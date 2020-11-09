# Data dictionary

This file serves to represent the data structures that will be used in the program

## Contents <!-- omit in toc -->

- [Data dictionary](#data-dictionary)
  - [Booking](#booking)
    - [Generating booking IDs](#generating-booking-ids)
  - [Board type](#board-type)
  - [Pricing](#pricing)

## Booking

We need to store each piece of data about the bookings (IDs, surnames, guest count) in separate arrays.

```c
// the max number of bookings the system can handle
#define MAX_BOOKINGS 10

// list of all booking IDs
char BookingIDs[MAX_BOOKINGS][66] = {""};
// list of all booking surnames
char BookingSurnames[MAX_BOOKINGS][64] = {""};
// list of all booking guest counts
int BookingGuestCounts[MAX_BOOKINGS] = {0};
// number of children in bookings
int BookingChildren[MAX_BOOKINGS] = {0};
// booking dates of birth
char BookingDatesOfBirth[MAX_BOOKINGS][10] = {"1970-01-01"};
// booking board types
int BookingBoard[MAX_BOOKINGS] = {-1};
// booking lengths (in days)
int BookingLengths[MAX_BOOKINGS] = {0};
// whether they want daily wake-up calls (0 = no, 1 = yes)
int BookingWakeUpCalls[MAX_BOOKINGS] = {-1};
// list of all rooms in each booking
// remember we can have multiple rooms in one booking!
// room 1 = 1, room 2 = 2, etc
int BookingRooms[MAX_BOOKINGS][6] = {0};
```

### Generating booking IDs

We'll need to generate booking IDs for guests to use throughout their stay. The brief states that this should be "made up of their surname plus a random number".

**Psuedocode**

```
subroutine GenerateBookingID(string surname)
  // get random number between 10 and 99 (inclusive)
  // we use 10 and 99 to make sure it's always a 2-digit number
  int randomNumber = Random(10, 99)

  // return the surname, concatenated with the random number
  return surname + randomNumber
endsubroutine
```

## Board type

Since we know that the board type can only be one of 3 options, we can use static values for these, instead of comparing against numbers.

```c
#define FullBoard 0
#define HalfBoard 1
#define BedAndBreakfast 2
```

Using these hash-defines prevents confusion as we can now use `booking.board == FullBoard` as opposed to `booking.board == 0`. We're less likely to mix-up what 0, 1 and 2 are.

## Pricing

Pricing doesn't change, so we can also use hash-defines for that.

```c
// Room prices
// we need -1 at the start because otherwise room 1 would be RoomPrices[0]
const int RoomPrices[7] = {-1, 100, 100, 85, 75, 75, 50};

// Board prices
const int BoardPrices[4] = {20, 15, 5};
```

We can then access these anywhere in the program with...

```c
RoomPrices[2]; // room 2 price
BoardPrices[FullBoard]; // full board price
```