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
// BOOKING DATA
// ---------------------

#define MAX_BOOKINGS 10

char BookingIDs[MAX_BOOKINGS][66] = {""};
char BookingSurnames[MAX_BOOKINGS][64] = {""};
int BookingGuestCounts[MAX_BOOKINGS] = {0};
int BookingChildren[MAX_BOOKINGS] = {0};
char BookingDatesOfBirth[MAX_BOOKINGS][10] = {"1970-01-01"};
int BookingBoard[MAX_BOOKINGS] = {-1};
int BookingLengths[MAX_BOOKINGS] = {0};
int BookingWakeUpCalls[MAX_BOOKINGS] = {-1};
int BookingRooms[MAX_BOOKINGS][6] = {0};

// ---------------------
// TABLE BOOKINGS
// ---------------------

char TableBookings7[3][66] = {""};
char TableBookings9[3][66] = {""};

#endif //KASHYYYK_HOTEL_HEADER_H
