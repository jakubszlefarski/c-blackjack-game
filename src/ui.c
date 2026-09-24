#include "ui.h"
#include "card.h"
#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
    void sleep_ms(int ms) { Sleep(ms); }
#else
    #include <unistd.h>
    void sleep_ms(int ms) { usleep((ms) * 1000); }
#endif

int SHORTWAIT = 100;
int MEDIUMWAIT = 500;

void clear_screen(void) {
    printf("\033[2J\033[H");
    fflush(stdout);
}

void hide_cursor(void) {
    printf("\033[?25l");
    fflush(stdout);
}

void show_cursor(void) {
    printf("\033[?25h");
    fflush(stdout);
}

void betinputhandling(int *currentbet_val) {
    int betinput;
    int guard = -1;
    while (guard == -1) {
        if (scanf("%d", &betinput) != 1 || betinput < 1) {
            sleep_ms(SHORTWAIT);
            printf("no such chip, use integer value greater than 1\n>");
            while (getchar() != '\n');
        } else {
            *currentbet_val = betinput;
            guard = 0;
        }
    }
}

void displaybets(void) {
    printf("your saldo: %d\n", saldo);
    printf("Place your bet!\n>");
}

void displayinfo(void) {
    printf("******BLACKJACK******\n");
    printf("Dealer's hand:\n");
    for (int i = 0; i < 21; i++) {
        if (dealerhand[i] == -1) break;
        int tempindex = dealerhand[i];
        printf("| %s %s |  ", deck[tempindex].figure, deck[tempindex].color);
    }
    printf("\nPlayer's hand:\n");
    for (int i = 0; i < 21; i++) {
        if (playerhand[i] == -1) break;
        int tempindex = playerhand[i];
        printf("| %s %s |  ", deck[tempindex].figure, deck[tempindex].color);
    }
    printf("\n");
}

void dealerbehavior(int dealerhand_arr[]) {
    sumhand(dealerhand_arr, &dealersum);
    while (dealersum < 17) {
        hit(dealerhand_arr);
        sleep_ms(MEDIUMWAIT);
        clear_screen();
        displayinfo();
        sumhand(dealerhand_arr, &dealersum);
    }
}

int displayplayeraction(GameStatus *currentgame, int *tempturn) {
    printf("press: \nh to hit\ns to stand\n");
    if (saldo - currentbet >= 0 && *tempturn == 0) {
        printf("d to double down\n");
    }

    while (1) {
        char rawinput;
        printf("> ");

        if (scanf(" %c", &rawinput) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        Action actioninput = char_to_enum(rawinput);

        if (actioninput == ACTION_UNKNOWN) {
            printf("no such action, try again\n>");
        } else if (actioninput == ACTION_HIT) {
            hit(playerhand);
            sleep_ms(MEDIUMWAIT);
            clear_screen();
            return 0;
        } else if (actioninput == ACTION_STAND) {
            dealerbehavior(dealerhand);
            sleep_ms(MEDIUMWAIT);
            checkforwin(currentgame);
            return 0;
        } else {
            if (saldo - currentbet >= 0 && *tempturn == 0) {
                saldo -= currentbet;
                doubledown(currentgame);
                sleep_ms(MEDIUMWAIT);
                clear_screen();
                displayinfo();
                dealerbehavior(dealerhand);
                sleep_ms(MEDIUMWAIT);
                return 0;
            } else if (*tempturn != 0) {
                sleep_ms(MEDIUMWAIT);
                clear_screen();
                printf("you can't double down after hit!\n");
                sleep_ms(MEDIUMWAIT);
                clear_screen();
            } else if (saldo - currentbet < 0) {
                sleep_ms(MEDIUMWAIT);
                clear_screen();
                printf("you don't have enough chips to double down!\n");
                sleep_ms(MEDIUMWAIT);
                clear_screen();
            }
        }
    }
}

int asktocontinue(void) {
    printf("continue? (press y/n)\n");
    while (1) {
        char rawinput;
        printf("> ");

        if (scanf(" %c", &rawinput) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        CONTINUEVAL gamecontval = char_to_enum_countinueval(rawinput);

        if (gamecontval == GAME_UNKNOWN) {
            printf("no such action, try again\n>");
        } else if (gamecontval == GAME_CONTINUE) {
            return GAME_CONTINUE;
        } else {
            return GAME_END;
        }
    }
}

void displaysummary(GameStatus *currentgame, int bet_out) {
    printf("*****SUMMARY*****\n");
    if (*currentgame == GAME_BLACKJACK) {
        printf("YOU WIN VIA NATURAL BLACKJACK!\n");
        printf("+%d\n", bet_out);
    } else if (*currentgame == GAME_VICTORY) {
        printf("YOU WIN!\n");
        printf("+%d\n", bet_out);
    } else if (*currentgame == GAME_DEFEAT) {
        printf("YOU LOOSE!\n");
        printf("-%d\n", bet_out);
    } else {
        printf("IT'S A DRAW!\n");
    }

    printf("Current Saldo: %d\n", saldo);
}