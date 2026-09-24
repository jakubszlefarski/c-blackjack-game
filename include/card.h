#pragma once

#define NUM_OF_CARDS 52

/** @brief Represents a single playing card. */
typedef struct {
    char figure[3]; /**< Card rank representation (e.g., "10", "K", "A") */
    int value;      /**< Numerical value in Blackjack */
    char *color;    /**< Card suit symbol (♠, ♣, ♥, ♦) */
} Card;

extern Card deck[NUM_OF_CARDS];

/**
 * @brief Initializes the global deck array with standard 52 playing cards.
 */
void generatedeck(void);

/**
 * @brief Generates a pseudo-random index for selecting a card from the deck.
 * 
 * @return Random card index between 0 and 51.
 */
int getrandomcard(void);

/**
 * @brief //Appends card via index to either hand
 * 
 * @return 0 or -1 if error occured
 */
int indextohand(int *hand, int index, int cardnumber);

/**
 * @brief Gets numercial value of card of certain index.
 * 
 * @return Value of card
 */
int getcardvalue(int index);