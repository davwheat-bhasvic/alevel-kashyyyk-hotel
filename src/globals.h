//
// Created by David on 10/11/2020.
//

#ifndef KASHYYYK_HOTEL_GLOBALS_H
#define KASHYYYK_HOTEL_GLOBALS_H 1

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define true 1
#define false 0
#define invalid -1

#define IS_DEBUG_MODE true

#define FullBoard 0
#define HalfBoard 1
#define BedAndBreakfast 2

extern const int RoomPrices[7];
extern const int RoomCapacities[7];
extern const int BoardPrices[3];
#define WAKE_UP_CALL_PRICE 5

#define CONCESSION_DISCOUNT 0.9
#define CHILD_BOARD_DISCOUNT 0.5

// ---------------------
// BOOKING DATA
// ---------------------

#define MAX_BOOKINGS 10

extern char BookingIDs[MAX_BOOKINGS][66];
extern char BookingSurnames[MAX_BOOKINGS][64];
extern int BookingGuestCounts[MAX_BOOKINGS];
extern int BookingChildren[MAX_BOOKINGS];
extern char BookingDatesOfBirth[MAX_BOOKINGS][11];
extern int BookingBoard[MAX_BOOKINGS];
extern int BookingLengths[MAX_BOOKINGS];
extern int BookingWakeUpCalls[MAX_BOOKINGS];
extern int BookingRooms[MAX_BOOKINGS][6];

extern int RoomsBooked[7];

// ---------------------
// TABLE BOOKINGS
// ---------------------

extern char TableBookings7[3][66];
extern char TableBookings9[3][66];

#define TABLE_ENDOR 0
#define TABLE_NABOO 1
#define TABLE_TATOOINE 2

#define TABLE_CAPACITY 4

// Find the index of a booking by its booking ID, or -1 if not found
int FindBookingIndex(char bookingID[66]);

#endif  // KASHYYYK_HOTEL_GLOBALS_H
