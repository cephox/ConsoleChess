#include "Utils.h"
#include <stdio.h>
#include <String.h>

void abs(int* number)
{
	if (*number < 0)
	{
		*number *= -1;
	}
}

void printBoard(const char* board[8][8], const char currentPlayer[])
{

	for (int k = 0; k < 100; k++)
	{
		printf("\n");
	}

	printf("%s ist dran\n\n  | ", currentPlayer);

	for (int i = 0; i < 8; i++)
	{
		printf("%i  ", i);
	}
	printf(" x\n----");
	for (int i = 0; i < 8; i++)
	{
		printf("---", i);
	}
	printf("\n");

	for (int i = 0; i < 8; i++)
	{
		printf("%i | ", i);
		for (int j = 0; j < 8; j++)
		{
			printf("%s ", board[i][j]);
		}
		printf("\n");
	}

	printf("\ny\n\n");
}

char currentPlayerShort(const char player[])
{
	if (player[0] == 'W')
	{
		return 'w';
	}
	if (player[0] == 'S')
	{
		return 's';
	}
	return player[0];
}

void transmutate(int x, int y, const char* board[8][8], int choice, char figureTeam)
{

	if (choice == 1)
	{
		if (figureTeam == 's')
		{
			board[y][x] = "sD";
		}
		else
		{
			board[y][x] = "wD";
		}
	}
	else if (choice == 2)
	{
		if (figureTeam == 's')
		{
			board[y][x] = "sT";
		}
		else
		{
			board[y][x] = "wT";
		}
	}
	else if (choice == 3)
	{
		if (figureTeam == 's')
		{
			board[y][x] = "sS";
		}
		else
		{
			board[y][x] = "wS";
		}
	}
	else if (choice == 4)
	{
		if (figureTeam == 's')
		{
			board[y][x] = "sL";
		}
		else
		{
			board[y][x] = "wL";
		}
	}

}

void getFigurType(int x, int y, const char* board[8][8], char result[])
{

	const char* figure = board[y][x];
	char figureType = figure[1];

	switch (figureType)
	{
	case TOWER:
		strcpy(result, "Turm");
		break;
	case HORSE:
		strcpy(result, "Springer");
		break;
	case RUNNER:
		strcpy(result, "Laeufer");
		break;
	case KING:
		strcpy(result, "Koenig");
		break;
	case QUEEN:
		strcpy(result, "Dame");
		break;
	case FARMER:
		strcpy(result, "Bauer");
		break;
	default:
		break;
	}

}

int move(int x, int y, int toX, int toY, const char* board[8][8])
{

	const char* figure = board[y][x];
	char figureTeam = figure[0];
	char figureType = figure[1];

	if (board[toY][toX][1] == 'K')
	{

		board[y][x] = "  ";
		board[toY][toX] = figure;
		return 1;
	}

	board[y][x] = "  ";
	board[toY][toX] = figure;

	bool foundOneNoKing = false;

	while (!foundOneNoKing)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++) 
			{
				if (board[j][i] != "  ")
				{
					if (board[j][i][1] != 'K')
					{
						foundOneNoKing = true;
					}
				}
			}
		}
	}

	if (!foundOneNoKing)
	{
		return 2;
	}

	if (figureType == 'B')
	{
		if (figureTeam == 'w')
		{
			if (toY == 0)
			{
				return 3;
				//board[toY][toX] = "wD";
			}
		}

		if (figureTeam == 's')
		{
			if (toY == 7)
			{
				return 3;
				//board[toY][toX] = "sD";
			}
		}
	}

	return 0;

}

bool canMove(int x, int y, int toX, int toY, const char* board[8][8])
{

	const char* figure = board[y][x];
	const char* destFigure = board[toY][toX];

	char figureTeam = figure[0];
	char figureType = figure[1];

	char destFigureTeam = destFigure[0];

	// Kann nicht auf Platz mit selbem Team
	if (figureTeam == destFigureTeam)
	{
		return false;
	}

	// Man kann nicht stehen bleiben
	if (toX - x == 0 && toY - y == 0)
	{
		return false;
	}

	switch (figureType)
	{

	case TOWER:
		return towerCanMove(x, y, toX, toY, board);

	case HORSE:
		return horseCanMove(x, y, toX, toY);

	case RUNNER:
		return runnerCanMove(x, y, toX, toY, board);

	case KING:
		return kingCanMove(x, y, toX, toY, board);

	case QUEEN:
		return queenCanMove(x, y, toX, toY, board);

	case FARMER:
		return farmerCanMove(x, y, toX, toY, board, figureTeam, destFigureTeam);

	default:
		return false;
	}

	return false;
}

bool towerCanMove(int x, int y, int toX, int toY, const char* board[8][8])
{

	// Horizontale Kollision
	if (toX - x > 0)
	{
		for (int i = x + 1; i < toX; i++)
		{
			const char* figureBetween = board[y][i];
			if (figureBetween != "  ")
			{
				return false;
			}
		}
	}
	if (toX - x < 0)
	{
		for (int i = x - 1; i > toX; i--)
		{
			const char* figureBetween = board[y][i];
			if (figureBetween != "  ")
			{
				return false;
			}
		}
	}

	// Vertikale Kollision
	if (toY - y > 0)
	{
		for (int i = y + 1; i < toY; i++)
		{
			const char* figureBetween = board[i][x];
			if (figureBetween != "  ")
			{
				return false;
			}
		}
	}
	if (toY - y < 0)
	{
		for (int i = y - 1; i > toY; i--)
		{
			const char* figureBetween = board[i][x];
			if (figureBetween != "  ")
			{
				return false;
			}
		}
	}

	if (toX - x != 0 && toY - y != 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool runnerCanMove(int x, int y, int toX, int toY, const char* board[8][8])
{

	int m = (toY - y) / (toX - x);
	int b = y - m * x;

	for (int i = x; i < toX; i++)
	{
		if (i == x)
		{
			continue;
		}

		int j = m * i + b;

		if (board[j][i] != "  ")
		{
			return false;
		}

	}

	int distX = toX - x;
	int distY = toY - y;
	abs(&distX);
	abs(&distY);

	return distX == distY;
}

bool queenCanMove(int x, int y, int toX, int toY, const char* board[8][8])
{

	int distX = toX - x;
	int distY = toY - y;
	abs(&distX);
	abs(&distY);

	// Horizontale Kollision
	if (toX - x > 0 && distY == 0)
	{
		for (int i = x + 1; i < toX; i++)
		{
			const char* figureBetween = board[y][i];
			if (figureBetween != "  ")
			{
				return false;
			}
		}
	}
	if (toX - x < 0 && distY == 0)
	{
		for (int i = x - 1; i > toX; i--)
		{
			const char* figureBetween = board[y][i];
			if (figureBetween != "  ")
			{
				return false;
			}
		}
	}

	// Vertikale Kollision
	if (toY - y > 0 && distX == 0)
	{
		for (int i = y + 1; i < toY; i++)
		{
			const char* figureBetween = board[i][x];
			if (figureBetween != "  ")
			{
				return false;
			}
		}
	}
	if (toY - y < 0 && distX == 0)
	{
		for (int i = y - 1; i > toY; i--)
		{
			const char* figureBetween = board[i][x];
			if (figureBetween != "  ")
			{
				return false;
			}
		}
	}

	int m = (toY - y) / (toX - x);
	int b = y - m * x;

	for (int i = x; i < toX; i++)
	{
		if (i == x)
		{
			continue;
		}

		int j = m * i + b;

		if (board[j][i] != "  ")
		{
			return false;
		}

	}

	if (toX - x != 0 && toY - y != 0)
	{
		return distX == distY;
	}
	else
	{
		return true;
	}
}

bool kingCanMove(int x, int y, int toX, int toY, const char* board[8][8])
{
	int distX = toX - x;
	int distY = toY - y;
	abs(&distX);
	abs(&distY);

	if (distX > 1 || distY > 1)
	{
		return false;
	}

	for (int i = toX - 1; i <= toX + 1; i++)
	{
		for (int j = toY - 1; j <= toY + 1; j++)
		{
			if (i == x && y == y)
			{
				continue;
			}
			if (board[j][i][1] == 'K')
			{
				return false;
			}
		}
	}

	return true;
}

bool farmerCanMove(int x, int y, int toX, int toY, const char* board[8][8], char figureTeam, char destFigureTeam)
{

	int distX = toX - x;
	int distY = toY - y;
	abs(&distX);
	abs(&distY);

	if (toY - y > 0 && figureTeam == 'w')
	{
		return false;
	}

	if (toY - y < 0 && figureTeam == 's')
	{
		return false;
	}

	if (board[toY][x] != "  ")
	{
		return false;
	}

	if (distY == 2)
	{
		if (figureTeam == 'w')
		{

			if (board[5][x] != "  ")
			{
				return false;
			}

			if (y == 6 && toY == 4 && distX == 0)
			{
				return true;
			}
		}


		if (figureTeam == 's')
		{
			if (board[2][x] != "  ")
			{
				return false;
			}
			if (y == 1 && toY == 3 && distX == 0)
			{
				return true;
			}
		}
	}

	if (distY > 1)
	{
		return false;
	}

	if (distX > 1)
	{
		return false;
	}

	if (distX == 0)
	{
		return true;
	}

	if (distX == 1)
	{
		if (destFigureTeam == ' ')
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	return false;
}

bool horseCanMove(int x, int y, int toX, int toY)
{

	int distX = toX - x;
	int distY = toY - y;
	abs(&distX);
	abs(&distY);

	if (distX > 2 || distY > 2)
	{
		return false;
	}

	if (distX == distY)
	{
		return false;
	}

	if (distX + 1 == distY)
	{
		return true;
	}

	if (distY + 1 == distX)
	{
		return true;
	}

	return false;
}