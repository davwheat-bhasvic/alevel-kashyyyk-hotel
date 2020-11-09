#include <stdio.h>

#define FullBoard 0
#define HalfBoard 1
#define BedAndBreakfast 2

const int RoomPrices[7] = {-1, 100, 100, 85, 75, 75, 50};
const int BoardPrices[4] = {20, 15, 5};

int main() {
    printf("%d\n", RoomPrices[2]); // price of room 2
    printf("%d\n", BoardPrices[FullBoard]); // price of FullBoard
    return 0;
}
