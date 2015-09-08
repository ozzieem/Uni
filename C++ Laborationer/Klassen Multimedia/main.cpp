#include "Multimedia.h"
#include "Book.h"



int main()
{
	Multimedia video("Aliens", 1979);
	Book book;

	video.display_item();
	cout << endl;

	book.add_item();
	cout << endl;

	book.display_item();

	int temp;
	cin >> temp;

}