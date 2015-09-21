
#include "MemorySpace.h"

using namespace MemorySpace;


struct PtrPos
{
	int x = 0;
	int y = 0;
} ptrPos;

Memory::Memory()
{
	srand(time(NULL));
}

void Memory::CreateCards()
{
	
	for (int i = 0; i < this->MatrixSide; i++)
	{
		for (int j = 0; j < this->MatrixSide; j++)
		{
			this->CardMatrix[i][j].SetValue("M");
		}
	}
}

void Memory::GenMemCards()
{
	struct Position
	{
		int x1;
		int y1;
		int x2;
		int y2;
	} rPos;

	vector<string> MemCard =
	{ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" };


	int randomCard = 0;
	for (int i = 0; i < this->MatrixSide; i++)
	{
		for (int j = 0; j < this->MatrixSide; j=j+2)
		{
			if (this->CardMatrix[i][j].GetValue() == "M")
			{
				this->CardMatrix[i][j].SetmemVal(MemCard[randomCard]);
				this->CardMatrix[i][j+1].SetmemVal(MemCard[randomCard]);
				randomCard++;
			}
		}
	}


	for (int i = 0; i < 10; i++)
	{
		rPos.x1 = rand() % this->MatrixSide;
		rPos.y1 = rand() % this->MatrixSide;
		rPos.x2 = rand() % this->MatrixSide;
		rPos.y2 = rand() % this->MatrixSide;

		Card tempCard;
		tempCard = CardMatrix[rPos.x1][rPos.y1];
		CardMatrix[rPos.x1][rPos.y1] = CardMatrix[rPos.x2][rPos.y2];
		CardMatrix[rPos.x2][rPos.y2] = tempCard;
	}

}

void Memory::PrintCards()
{
	for (int i = 0; i < this->MatrixSide; i++)
	{
		for (int j = 0; j < this->MatrixSide; j++)
		{
			string card = this->CardMatrix[i][j].GetValue();
			cout << card;
		}
		cout << endl;
	}
}

void Memory::cardFlip()
{
	char c;

	switch (c = _getch())
	{
		case 'H':	//arrow up
		{
			Console::gotoxy(ptrPos.x, ptrPos.y - 1);
			cout << "up" << endl;
		} break;
		case 'P':	//arrow down
		{
			Console::gotoxy(ptrPos.x, ptrPos.y + 1);
			cout << "down" << endl;
		} break;
		case 'M':	//arrow right
		{
			Console::gotoxy(ptrPos.x + 1, ptrPos.y);
			cout << "right" << endl;
		} break;
		case 'K':	// arrow left
		{
			Console::gotoxy(ptrPos.x - 1, ptrPos.y);
			cout << "left" << endl;
		} break;
		case '\n':
		{
			//Flip card
		} break;
		default:
		{

		} break;

	}
}