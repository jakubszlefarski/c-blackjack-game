#include "card.h"
#include <stdlib.h>
#include <stdio.h>

static char *colors[] = {"♠", "♣", "♥", "♦"};
static Card figures[13] = {
    {"2", 2, NULL}, {"3", 3, NULL}, {"4", 4, NULL}, {"5", 5, NULL},
    {"6", 6, NULL}, {"7", 7, NULL}, {"8", 8, NULL}, {"9", 9, NULL},
    {"10", 10, NULL}, {"J", 10, NULL}, {"Q", 10, NULL}, {"K", 10, NULL},
    {"A", 11, NULL}
};

Card deck[NUM_OF_CARDS];

void generatedeck(void) {
    for (int h = 0; h < 13; h++) {
        for (int g = 0; g < 4; g++) {
            int index = (h * 4) + g;
            deck[index] = figures[h];
            deck[index].color = colors[g];
        }
    }
}

int getrandomcard(void) {
    return rand() % NUM_OF_CARDS;
}

int indextohand(int *hand, int index, int cardnumber) {
    if (index >= NUM_OF_CARDS || index < 0 || cardnumber > 21 || cardnumber < 1) {
        printf("error: wrong index or too many cards\n");
        return -1;
    }
    int cardindex = cardnumber - 1;
    hand[cardindex] = index;
    return 0;
}

int getcardvalue(int index) {
    return deck[index].value;
}