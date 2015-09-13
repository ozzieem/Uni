#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <vector>
#include <Windows.h>


using namespace std;

#if 0 
// IF/ELSE - SHORTCUT

// If prime[i] > max assign prime[i] to max, else keep max as is.
max = prime[i] > max ? prime[i] : max;

#endif

#if 0
//_____________________________________________________________________________________
// ARRAYS

int main()
{
	char question1[] = "What is your name? ";
	string question2 = "Where do you live? ";
	char answer1[80];
	string answer2;
	cout << question1;
	cin >> answer1;
	cout << question2;
	cin >> answer2;

	cout << "Hello, " << answer1;
	cout << "from " << answer2 << "!\n";

	return 0;
}
#endif


#if 0
//_________________________________________________________________________________________
// POINTERS

int main()
{
	int firstvalue, secondvalue;
	int *mypointer;

	mypointer = &firstvalue;	// Assigning mypointer to address of firstvalue
	*mypointer = 10;			// Declaring value 10 to the value pointed by mypointer, which is firstvalue

	mypointer = &secondvalue;	// Assigning mypointer to address of secondvalue
	*mypointer = 20;			// Declaring value 10 to the value pointed by mypointer, which is secondvalue

	cout << "Firstvalue is " << firstvalue << '\n';
	cout << "Secondvalue is " << secondvalue << '\n';

	return 0;
}
#endif

#if 0 
//_________________________________________________________________________________________
// Problem 1 of Project Euler

int main()
{
	int input, result = 0;

	cout << "Find the sum of all the multiples of 3 and 5 below a number." << endl;
	cout << "Enter a number: ";
	cin >> input;

	for (int i = 1; i < input; i++)
	{
		if (i % 3 == 0 || i % 5 == 0)
		{
			cout << i << '+';
			result += i;
		}
		else
			;;
	}

	cout << '=' << result;
	cin >> input;
}

#endif



#if 0
//_________________________________________________________________________________________
// Problem 2 of Project Euler

int main()
{
	int result = 0, input;
	int firstTerm = 1, secondTerm = 1, nextTerm = 0;

	cout << "Add all the even terms of fibonacci series up to a number." << endl;
	cout << "Enter a number: ";
	cin >> input;

	while (nextTerm < input)
	{
		nextTerm = firstTerm + secondTerm;
		firstTerm = secondTerm;
		secondTerm = nextTerm;

		if (nextTerm % 2 == 0)
			result += nextTerm;
	}

	cout << result;
	cin >> result;
}

#endif




//_________________________________________________________________________________________
// Problem 3 of Project Euler

#if 0
typedef long long int int64;


int factors(int64 n)
{
	int z = 2;

	while (z*z <= n)
	{
		if (n % z == 0)
		{
			cout << z << " ";
			n /= z;
		}
		else
			z++;
	}

	if (n > 1)
		return n;
}


/*
The easiest way to understand the above function is by an example.
Consider the factorization of n = 13195. Initially z = 2,
but dividing 13195 by 2 leaves a remainder of 1,
so the else clause sets z = 3 and we loop.
Now n is not divisible by 3, or by 4, but when z = 5
the remainder when dividing 13195 by 5 is zero, so output 5 and
divide 13195 by 5 so n = 2639 and z = 5 is unchanged.
Now the new n = 2639 is not divisible by 5 or 6, but is divisible by 7,
so output 7 and set n = 2639 / 7 = 377. Now we continue with z = 7,
and that leaves a remainder, as does division by 8, and 9, and 10, and 11,
and 12, but 377 / 13 = 29 with no remainder, so output 13 and set n = 29.
At this point z = 13, and z * z = 169, which is larger than 29,
so 29 is prime and is the final factor of 13195, so output 29.
The complete factorization is 5 * 7 * 13 * 29 = 13195.
*/


int main()
{
	int64 input, result = 1, max = 0;
	std::vector< int > prime;


	cout << "Enter a number: ";
	cin >> input;
	//input = 600851475143;

	cout << "The prime factors of " << input << " are ";
	result = factors(input);
	cout << result << "." << endl;
	max = result > max ? result : max;
	cout << "Largest prime factor is " << max << endl;

	cin >> input;


	// Completely wrong code down there for this task...
	/*
	for (int i = 2; i <= input; i++)
	{
	bool primecheck = true;
	for (int j = 2; j*j <= i; j++)
	{
	if (i % j == 0)
	{
	primecheck = false;
	break;
	}
	}
	if (primecheck)
	{
	prime.push_back(i);
	}
	}
	*/


	for (int i = 0; i < prime.size(); i++)
	{
		// If prime[i] > max assign prime[i] to max, else keep max as is.
		max = prime[i] > max ? prime[i] : max;
	}

	//DEBUG
	cout << "Vector size: " << prime.size() << endl;
	cout << "Highest prime factor: " << max;



}
#endif


//EXEMEPEL DOTHIS 
#if 0
void DoThis(int &alpha, int beta)
{
	int temp;
	alpha += 392;
	temp = beta;
	beta = 322;
}

int main()
{
	int gamma = 185;
	int delta = 262;

	DoThis(gamma, delta);

	cout << "Gamma: " << gamma << endl;
	cout << "Delta: " << delta;

	cin >> gamma;
}
#endif



#if 0

void Demo(int &intVal, float &floatVal)
{
	intVal *= 2;
	floatVal = float(intVal) + 3.5;
}

int main()
{
	int myInt = 12;
	float myFloat = 3.6;

	Demo(myInt, myFloat);

	cout << "myInt: " << myInt << endl;
	cout << "myFloat: " << myFloat;

	cin >> myFloat;
}*/

#endif



#if 0

// Factorial of a number
typedef long long unsigned int facint;

facint factorial(facint n)
{
	if (n <= 1)
		return 1;
	else
		return n * factorial(n - 1);
}

int main()
{
	facint num, new_num = 0;

	cout << "Enter a value to find the factorial of:";
	cin >> num;

	new_num = factorial(num);

	cout << "The factor of " << num << " is: " << new_num << endl;
	cin >> new_num;
}

#endif


#if 0
void Twist(int a, int& b)
{
	int c;
	c = a + 2;
	a = a * 3;
	b = c + a;
}

int main()
{
	int r = 11;
	int s = 13;
	int t = 15;

	Twist(t, s);
	cout << r << " " << s << " " << t << endl;
	cin.get();
}
#endif


#if 0
//Which of the function-calls are correct?

void Fix(int &, float);

int main()
{
	int x;
	float y;

	Fix(24, 6.85);
	y = 0.3 * Fix(x, 6.85);
	Fix(x + 5, y);
	//Answer: None of the above.

}

#endif


#if 0
//Typomvandling - Prints 15 instead of 10.6 + 5.6 = 16.2
//static_cast<int> "removes" decimals from double.
int main()
{
	double da = 10.6;
	double db = 5.6;
	int result = static_cast<int>(da) + static_cast<int>(db);

	cout << result;

	cin.get();
}
#endif


#if 0
// Which of the cases prints out "one"
void bool_cases(bool A, bool B, bool C, bool D)
{

	if (A&&B)
	{
		if (!C || !D)
			cout << "one" << endl;
		else if (D)
			cout << "two" << endl;
		else
			cout << "three" << endl;
	}
	else if (C != D)
		cout << "four" << endl;
	else if (C)
		cout << "five" << endl;
	else
		cout << "six" << endl;


}

int main()
{
	bool_cases(true, true, true, true); //case 1
	bool_cases(true, true, true, false); //case 2
	bool_cases(true, true, false, true); //case 3
	bool_cases(true, true, false, false); //case 4

	cin.get();
}

#endif


#if 0
void Demo(int &intVal, float &floatVal)
{
	intVal = intVal * 2;
	floatVal = float(intVal) + 3.5;
}

int main()
{
	int myInt = 4;
	float myFloat = 5.9;
	Demo(myInt, myFloat);

	cout << myInt << " " << myFloat;
	cin.get();

}
#endif


#if 0
// Which of the cases prints out "one"
void bool_cases(bool A, bool B, bool C, bool D)
{

	if (A&&B)
	{
		if (!C || !D)
			cout << "one" << endl;
		else if (D)
			cout << "two" << endl;
		else
			cout << "three" << endl;
	}
	else if (C != D)
		cout << "four" << endl;
	else if (C)
		cout << "five" << endl;
	else
		cout << "six" << endl;


}

int main()
{
	bool_cases(true, false, true, true); //case 1
	bool_cases(false, true, false, true); //case 2
	bool_cases(false, true, true, false); //case 3
	bool_cases(false, false, false, false); //case 4

	cin.get();
}
#endif


//Pop-up window
int CALLBACK
WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	MessageBoxA(0, "This is a pop-up window", "Pop-up window",
		MB_OK | MB_ICONINFORMATION);

	return(0);
}


