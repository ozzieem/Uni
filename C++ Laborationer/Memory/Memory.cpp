
#include "MemorySpace.h"
//#include <vector>

using namespace MemorySpace;

Memory::Memory()
{

}

void Memory::CreateCards()
{
	for (int i = 0; i < nCards; i++)
	{
		CardMatrix[i] = vector<Card>(MatrixSide);
	}

	for (int i = 0; i < MatrixSide; i++)
	{
		for (int j = 0; j < nCards; j++)
		{
			CardMatrix[i][j].SetValue("R");
		}
	}
}