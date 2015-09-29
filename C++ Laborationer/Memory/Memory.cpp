
#include "MemorySpace.h"

using namespace MemorySpace;
using namespace std;
using namespace Course;

HighScoreData HSdata;	//TODO(Ozziee): Remove this at some point...

struct PtrVal
{
	int x = 0;
	int y = 0;
} ptrVal;

int turn = 0;

vector<string> MemCard =
{ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" };

Memory::Memory()
{
	srand(unsigned int(time(NULL)));
}

void Memory::CreateCards()
{
	
	for (int i = 0; i < this->MatrixSide; i++)
	{
		for (int j = 0; j < this->MatrixSide; j++)
		{
			this->CardMatrix[i][j].setBack("M");
		}
	}
}

void Memory::GenMemCards()
{
	
	int randomCard = 0;
	for (int i = 0; i < this->MatrixSide; i++)
	{
		for (int j = 0; j < this->MatrixSide; j=j+2)
		{
			if (this->CardMatrix[i][j].getBack() == "M")
			{
				this->CardMatrix[i][j].setFront(MemCard[randomCard]);
				this->CardMatrix[i][j+1].setFront(MemCard[randomCard]);

				//DEBUG - Display cardvalues
				//this->CardMatrix[i][j].setBack(MemCard[randomCard]);
				//this->CardMatrix[i][j + 1].setBack(MemCard[randomCard]);

				randomCard++;
			}
		}
	}

	// Randomly switching around cards
	//TODO(Ozziee): Try and make it more clean
	for (int i = 0; i < 10; i++)
	{
		this->rVal.x1 = rand() % this->MatrixSide;
		this->rVal.y1 = rand() % this->MatrixSide;
		this->rVal.x2 = rand() % this->MatrixSide;
		this->rVal.y2 = rand() % this->MatrixSide;

		Card tempCard;
		tempCard = this->CardMatrix[rVal.x1][rVal.y1];
		this->CardMatrix[rVal.x1][rVal.y1] = this->CardMatrix[rVal.x2][rVal.y2];
		this->CardMatrix[rVal.x2][rVal.y2] = tempCard;
	}

}

void Memory::PrintCards()
{
	for (int i = 0; i < this->MatrixSide; i++)
	{
		for (int j = 0; j < this->MatrixSide; j++)
		{
			cout << this->CardMatrix[i][j].getBack();
		}
		cout << endl;
	}

	Console::gotoxy(10, 0);
	cout << "Points: " << HSdata.getPoints();

	Console::gotoxy(ptrVal.x, ptrVal.y);

}

void Memory::CardFlip(int row, int col)
{

	if (this->CardMatrix[row][col].getBack() == "M")
	{
		this->CardMatrix[row][col].setBack(this->CardMatrix[row][col].getFront());
		
		if (turn == 1)
		{
			this->fPos.x2 = row;
			this->fPos.y2 = col;
		}
		else if (turn == 2)
		{
			this->fPos.x1 = row;
			this->fPos.y1 = col;

			Console::clrscr();
			PrintCards();
			CheckCards();
		}

	}
	else
	{
		OutputDebugStringA("Can't flip card\n");
		turn--;
	}

}


void Memory::CardNav()
{
	char key;

	switch (key = _getch())
	{
		case 'H':	//arrow up
		{	
			//--operator before to change variable value
			Console::gotoxy(ptrVal.x, --ptrVal.y);

			//OutputDebugStringA("up\n");
		} break;
		case 'P':	// arrow down
		{
			Console::gotoxy(ptrVal.x, ++ptrVal.y);

			//OutputDebugStringA("down\n");
		} break;
		case 'M':	// arrow right
		{
			Console::gotoxy(++ptrVal.x, ptrVal.y);

			//OutputDebugStringA("right\n");
		} break;
		case 'K':	// arrow left
		{
			Console::gotoxy(--ptrVal.x , ptrVal.y);

			//OutputDebugStringA("left\n");
		} break;
		case 32:	// blankspace
		{
			//OutputDebugStringA("flip\n");

			turn++;
			CardFlip(ptrVal.y, ptrVal.x);
			
		} break;
		default:
		{

		} break;

	}
}


void Memory::CheckCards()
{

	if (CardMatrix[fPos.x1][fPos.y1].getBack() == CardMatrix[fPos.x2][fPos.y2].getBack())
	{

		OutputDebugStringA("Pair\n");
		HSdata.addPoints(2);
		OutputDebugStringA("Added 2 points to HighScoreData\n"); 

		Sleep(1000);

	}
	else
	{
		OutputDebugStringA("No Pair\n");
		HSdata.subPoints(1);
		OutputDebugStringA("Subtracted 1 point from HighScoreData\n");

		Sleep(1000);
		OutputDebugStringA("Reseting...\n");
		CardMatrix[fPos.x1][fPos.y1].setBack("M");
		CardMatrix[fPos.x2][fPos.y2].setBack("M");

	}

	
	turn = 0;
}
