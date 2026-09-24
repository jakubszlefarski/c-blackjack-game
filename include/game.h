#pragma once
/** @brief Initial player saldo */
#define INITSALDO 100

/** @brief Represents a state of single turn(deal). */
typedef enum {
    GAME_IN_PROGRESS,
    GAME_VICTORY,
    GAME_DEFEAT,
    GAME_DRAW,
    GAME_BLACKJACK
} GameStatus;

/** @brief Represents possible player actions. */
typedef enum {
    ACTION_HIT,
    ACTION_STAND,
    ACTION_DOUBLEDOWN,
    ACTION_UNKNOWN
} Action;

/** @brief Represents a state of whole game (all the rounds). */
typedef enum {
    GAME_CONTINUE,
    GAME_END,
    GAME_UNKNOWN
} CONTINUEVAL;

// game state variables
extern int saldo; //player saldo
extern int currentbet;
extern int playerhand[21];
extern int dealerhand[21];
extern int playersum;
extern int dealersum;

/**
 * @brief Converts a user input character to an Action enum.
 * 
 * @param c Input character ('h', 's', 'd').
 * @return Corresponding Action enum value (ACTION_HIT, ACTION_STAND, ACTION_DOUBLEDOWN, or ACTION_UNKNOWN).
 */
Action char_to_enum(char c);

/**
 * @brief Converts a user input character to an Continueval enum.
 * 
 * @param c Input character ('y', 'n').
 * @return Corresponding Action enum value (GAME_CONTINUE, GAME_END, GAME_UNKNOWN).
 */
CONTINUEVAL char_to_enum_countinueval(char c);

/**
 * @brief Resets all card slots in a hand array to -1.
 * 
 * @param[out] hand Pointer to an array of size 21 representing card indices.
 * @return Always returns 0.
 */
int resethand(int *hand);

int betmoney(int *saldo_val, int *currentbet_val);
int betoutput(GameStatus *currentgame);
int sumhand(int *hand, int *handsum);

int checkplayerbust(GameStatus *currentgame);
void checkinitialblackjack(GameStatus *currentgame);
void checkforwin(GameStatus *currentgame);

int deal(GameStatus *currentgame);
void hit(int hand[]);
void doubledown(GameStatus *currentgame);