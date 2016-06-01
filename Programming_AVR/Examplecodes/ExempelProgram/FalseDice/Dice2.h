/* 
* Dice2.h
*
* Created: 1/30/2015 1:54:16 PM
* Author: Kjell
*/


#ifndef __DICE2_H__
#define __DICE2_H__




class Dice2
{
//variables
public:
	enum class State
	{
		Normal,
		False,
		Throw1Active,
		Throw1Finished,
		Throw2Active
	};	
protected:
private:
	State state;
	int value;

//functions
public:
	Dice2();
	void Run(int eventThrow, int eventFalse);
	void Increment();
	int Value();
	~Dice2();
protected:
private:
	Dice2( const Dice2 &c );
	Dice2& operator=( const Dice2 &c );

}; //Dice2

#endif //__DICE2_H__
