#pragma once

#include "game.h"

extern int SHORTWAIT;
extern int MEDIUMWAIT;

void sleep_ms(int ms);
void clear_screen(void);
void hide_cursor(void);
void show_cursor(void);

void betinputhandling(int *currentbet_val);
void displaybets(void);
void displayinfo(void);
void dealerbehavior(int dealerhand_arr[]);
int displayplayeraction(GameStatus *currentgame, int *tempturn);
int asktocontinue(void);
void displaysummary(GameStatus *currentgame, int bet_out);

