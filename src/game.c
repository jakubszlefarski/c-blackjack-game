#include "game.h"
#include "card.h"
#include <math.h>

int saldo = INITSALDO;
int currentbet = 0;
int playerhand[21];
int dealerhand[21];
int playersum = 0;
int dealersum = 0;

Action char_to_enum(char c) {
    switch (c) {
        case 'h': case 'H': return ACTION_HIT;
        case 's': case 'S': return ACTION_STAND;
        case 'd': case 'D': return ACTION_DOUBLEDOWN;
        default: return ACTION_UNKNOWN;
    }
}

CONTINUEVAL char_to_enum_countinueval(char c) {
    switch (c) {
        case 'y': case 'Y': return GAME_CONTINUE;
        case 'n': case 'N': return GAME_END;
        default: return GAME_UNKNOWN;
    }
}

int resethand(int *hand) {
    for (int y = 0; y < 21; y++) {
        hand[y] = -1;
    }
    return 0;
}

int betmoney(int *saldo_val, int *currentbet_val) {
    if (*saldo_val < *currentbet_val) {
        return -1;
    } else {
        *saldo_val -= *currentbet_val;
        return *currentbet_val;
    }
}

int betoutput(GameStatus *currentgame) {
    if (*currentgame == GAME_DEFEAT) {
        return currentbet;
    } else if (*currentgame == GAME_VICTORY) {
        saldo += (2 * currentbet);
        return (2 * currentbet);
    } else if (*currentgame == GAME_DRAW) {
        saldo += currentbet;
        return currentbet;
    } else if (*currentgame == GAME_BLACKJACK) {
        int t = currentbet + (int)floor(1.5 * currentbet);
        saldo += t;
        return t;
    }
    return 0;
}

int sumhand(int *hand, int *handsum) {
    *handsum = 0;
    for (int o = 0; o < 21; o++) {
        if (hand[o] != -1) {
            int cardindex = hand[o];
            *handsum += deck[cardindex].value;
        }
    }
    for (int p = 0; p < 21; p++) {
        if (hand[p] != -1 && deck[hand[p]].value == 11 && *handsum > 21) {
            *handsum -= 10;
        }
    }
    return 0;
}

int checkplayerbust(GameStatus *currentgame) {
    sumhand(playerhand, &playersum);
    if (playersum > 21) {
        *currentgame = GAME_DEFEAT;
        return 1;
    }
    return 0;
}

void checkinitialblackjack(GameStatus *currentgame) {
    sumhand(playerhand, &playersum);
    sumhand(dealerhand, &dealersum);
    if (playersum == 21 && dealersum != 10 && dealersum != 11) {
        *currentgame = GAME_BLACKJACK;
    }
}

void checkforwin(GameStatus *currentgame) {
    sumhand(playerhand, &playersum);
    sumhand(dealerhand, &dealersum);

    if (dealersum > 21) {
        *currentgame = GAME_VICTORY;
    } else if (playersum > dealersum) {
        *currentgame = GAME_VICTORY;
    } else if (playersum < dealersum) {
        *currentgame = GAME_DEFEAT;
    } else {
        *currentgame = GAME_DRAW;
    }
}

int deal(GameStatus *currentgame) {
    dealerhand[0] = getrandomcard();
    playerhand[0] = getrandomcard();
    playerhand[1] = getrandomcard();
    *currentgame = GAME_IN_PROGRESS;
    return 0;
}

void hit(int hand[]) {
    for (int i = 0; i < 21; i++) {
        if (hand[i] == -1) {
            hand[i] = getrandomcard();
            break;
        }
    }
}

void doubledown(GameStatus *currentgame) {
    currentbet *= 2;
    hit(playerhand);
    checkforwin(currentgame);
}