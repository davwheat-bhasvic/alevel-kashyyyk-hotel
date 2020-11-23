//
// Created by dwhea on 20/11/2020.
//
#include "globals.h"

const int RoomPrices[7] = {-1, 100, 100, 85, 75, 75, 50};
const int RoomCapacities[7] = {-1, 4, 4, 4, 2, 2, 2};
const int BoardPrices[3] = {20, 15, 5};

char BookingIDs[MAX_BOOKINGS][66] = {""};
char BookingSurnames[MAX_BOOKINGS][64] = {""};
int BookingGuestCounts[MAX_BOOKINGS] = {0};
int BookingChildren[MAX_BOOKINGS] = {0};
char BookingDatesOfBirth[MAX_BOOKINGS][11] = {"1970-01-01"};
int BookingBoard[MAX_BOOKINGS] = {-1};
int BookingLengths[MAX_BOOKINGS] = {0};
int BookingWakeUpCalls[MAX_BOOKINGS] = {-1};
int BookingRooms[MAX_BOOKINGS][6] = {-1};

int RoomsBooked[7] = {-1, false};

char TableBookings7[3][66] = {""};
char TableBookings9[3][66] = {""};