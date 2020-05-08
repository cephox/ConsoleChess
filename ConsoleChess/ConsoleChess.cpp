#include "Utils.h"
#include <stdio.h>
#include <String.h>

const char* board[8][8] = {
	{"sT", "sS", "sL", "sK", "sD", "sL", "sS", "sT"},
	{"sB", "sB", "sB", "sB", "sB", "sB", "sB", "sB"},
	{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
	{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
	{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
	{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
	{"wB", "wB", "wB", "wB", "wB", "wB", "wB", "wB"},
	{"wT", "wS", "wL", "wK", "wD", "wL", "wS", "wT"}

	/*{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
	{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
	{"  ", "  ", "wB", "  ", "  ", "  ", "  ", "  "},
	{"  ", "  ", "sK", "  ", "  ", "  ", "  ", "  "},
	{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
	{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
	{"  ", "  ", "wK", "  ", "  ", "  ", "  ", "  "},
	{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "}*/
};

int amountPlayerOne = 0;
int amountPlayerTwo = 0;

int main()
{

	char currentPlayer[] = "Weiss";

	int color = -1;

	while (color == -1)
	{

		printf("Welche Farbe moechtest du spielen?\n[1] Weiss\n[2] Schwarz\n> ");
		scanf("%i", &color);

		if (color == 1)
		{
			strcpy(currentPlayer, "Weiss");
		}
		else if (color == 2)
		{
			strcpy(currentPlayer, "Schwarz");
		}
		else
		{
			color = -1;
			printf("Diese Auswahl gibt es nicht. Bitte gib nur \"1\" oder \"2\" ein.\n");
		}
	}

OUTER:
	while (true)
	{
		printBoard(board, currentPlayer);
		bool foundCorrect = false;

		int x = -1;
		int y = -1;
		const char* figure = "";

		// Getting figure Name and checking if moveable
		while (!foundCorrect)
		{
			x = -1;
			y = -1;

			while (x == -1 || x > 7)
			{
				printf("Bitte gebe den x-Wert der Figur an, die du ziehen moechtest: ");
				scanf("%i", &x);
			}

			while (y == -1 || y > 7)
			{
				printf("Bitte gebe den y-Wert der Figur an, die du ziehen moechtest: ");
				scanf("%i", &y);
			}

			const char* tempFigure = board[y][x];

			if (tempFigure == "  ")
			{
				printf("\nDieses Feld ist leer! Bitte waehle ein anderes aus!\n\n");
				continue;
			}

			char playerShort = currentPlayerShort(currentPlayer);
			if (tempFigure[0] != playerShort)
			{
				printf("\nDiese Figur kannst du nicht bewegen, da es im anderen Team ist! Bitte waehle eine andere aus!\n\n");
				continue;
			}

			figure = tempFigure;
			foundCorrect = true;
		}

		char figureFullName[] = "";
		getFigurType(x, y, board, figureFullName);

		printf("\nDu hast den/die %s auf (%i, %i) ausgewaehlt.\n\n", figureFullName, x, y);

		foundCorrect = false;

		int toX = -1;
		int toY = -1;

		while (!foundCorrect)
		{
			toX = -5;
			toY = -5;

			while (toX == -5 || toX > 7)
			{
				printf("Bitte gebe den x-Wert der Figur an, wohin du ziehen moechtest\nOder gib \"-1\" um eine andere Figur auszuwaehlen: ");
				scanf("%i", &toX);
				if (toX == -1)
				{
					goto OUTER;
				}
			}

			while (toY == -5 || toY > 7)
			{
				printf("Bitte gebe den y-Wert der Figur an, wohin du ziehen moechtest\nOder gib \"-1\" um eine andere Figur auszuwaehlen: ");
				scanf("%i", &toY);
				if (toY == -1)
				{
					goto OUTER;
				}
			}

			if (canMove(x, y, toX, toY, board))
			{
				foundCorrect = true;
			}
			else
			{
				printf("\nDahin kannst du nicht ziehen! Bitte waehle ein anderes Feld aus!\n\n");
			}
		}

		if (currentPlayer[0] == 'W')
		{
			amountPlayerOne++;
		}
		else
		{
			amountPlayerTwo++;
		}

		int moved = move(x, y, toX, toY, board);

		if (moved == 1)
		{
			printBoard(board, currentPlayer);
			printf("\n\n%s hat in %i Zuegen gewonnen!\nHerzlichen Glueckwunsch!\n\n", currentPlayer, currentPlayer[0] == 'W' ? amountPlayerOne : amountPlayerTwo);
			while (true)
			{
			}
		}
		else if (moved == 2)
		{
			printBoard(board, "Niemand");
			printf("\n\nPatt!\n\n");
			while (true)
			{
			}

		}

		if (currentPlayer[0] == 'W')
		{
			strcpy(currentPlayer, "Schwarz");
		}
		else
		{
			strcpy(currentPlayer, "Weiss");
		}

	}

}