#pragma once

#define len(x) (sizeof(x) / sizeof(x[0]))

#define TOWER 'T'
#define HORSE 'S'
#define RUNNER 'L'
#define KING 'K'
#define QUEEN 'D'
#define FARMER 'B'

void abs(int* number);

void printBoard(const char* board[8][8], const char currentPlayer[]);
char currentPlayerShort(const char player[]);

void transmutate(int x, int y, const char* board[8][8], int choice, char figureTeam);

void getFigurType(int x, int y, const char* board[8][8], char result[]);
int move(int x, int y, int toX, int toY, const char* board[8][8]);
bool canMove(int x, int y, int toX, int toY, const char* board[8][8]);

bool towerCanMove(int x, int y, int toX, int toY, const char* board[8][8]);
bool runnerCanMove(int x, int y, int toX, int toY, const char* board[8][8]);
bool queenCanMove(int x, int y, int toX, int toY, const char* board[8][8]);
bool kingCanMove(int x, int y, int toX, int toY, const char* board[8][8]);
bool farmerCanMove(int x, int y, int toX, int toY, const char* board[8][8], char figureTeam, char destFigureTeam);
bool horseCanMove(int x, int y, int toX, int toY);