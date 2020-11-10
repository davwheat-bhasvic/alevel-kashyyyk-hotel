//
// Created by David on 10/11/2020.
//

#ifndef KASHYYYK_HOTEL_HEADER_H
#define KASHYYYK_HOTEL_HEADER_H

#define FullBoard 0
#define HalfBoard 1
#define BedAndBreakfast 2

const int RoomPrices[7] = {-1, 100, 100, 85, 75, 75, 50};
const int BoardPrices[4] = {20, 15, 5};

// ---------------------

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

#endif //KASHYYYK_HOTEL_HEADER_H
