#include "VectorFloat.h"

int main()
{
	while (true)
	{
		int VectorSize;
		cout << "Ange storlek på vector: ";
		cin >> VectorSize;

		VectorFloat vc(VectorSize);

		vc.ReadFromKeyboard();
		vc.Print();

		cout << "Enter to restart" << endl;
		_getch();	//Bad using _getch();
	}
}