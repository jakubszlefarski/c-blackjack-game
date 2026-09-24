#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "card.h"
#include "game.h"
#include "ui.h"

#ifdef _WIN32
    #include <windows.h>
#endif

int main(void) {
    hide_cursor();

#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    srand((unsigned int)time(NULL));
    clear_screen();
    GameStatus currentgame = GAME_IN_PROGRESS;
    GameStatus *currentgameptr = &currentgame;
    generatedeck();
    CONTINUEVAL conttemp;

    do {
        clear_screen();
        resethand(dealerhand);
        resethand(playerhand);
        printf("******BLACKJACK******\n");

        while (1) {
            displaybets();
            betinputhandling(&currentbet);
            if (betmoney(&saldo, &currentbet) != -1) {
                sleep_ms(MEDIUMWAIT);
                printf("you successfully bet %d\n", currentbet);
                sleep_ms(MEDIUMWAIT);
                clear_screen();
                break;
            } else {
                sleep_ms(SHORTWAIT);
                printf("you don't have enough money for that bet, try again\n");
                sleep_ms(MEDIUMWAIT);
                clear_screen();
            }
        }

        deal(currentgameptr);
        checkinitialblackjack(currentgameptr);
        int tempturn = 0;

        while (currentgame == GAME_IN_PROGRESS) {
            displayinfo();
            displayplayeraction(currentgameptr, &tempturn);
            tempturn++;

            if (checkplayerbust(currentgameptr) == 1) {
                break;
            }
        }

        displaysummary(currentgameptr, betoutput(currentgameptr));

        if (saldo <= 0) {
            break;
        }
        conttemp = asktocontinue();

    } while (conttemp == GAME_CONTINUE && saldo > 0);

    sleep_ms(MEDIUMWAIT);
    clear_screen();

    printf("GAME OVER\n");
    if (saldo > 0) {
        printf("FINAL SALDO: %d \n", saldo);
        float t = ((float)(saldo - INITSALDO) / INITSALDO) * 100.0f;
        char s = (t > 0) ? '+' : '-';
        printf("%c%.0f%%\n", s, t);
    } else {
        printf("BANKRUPT!\n");
    }

    show_cursor();
    sleep_ms(MEDIUMWAIT);

    printf("\npress Enter to close program");
    
 
   
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    getchar(); 
    return 0;
}