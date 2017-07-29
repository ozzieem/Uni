#pragma once

#include "Libs.h"
#include <string>


class A {
public:
	std::string stringVal;
	static int x;

	A() {
		this->stringVal = "This is A";
	}

	virtual void printInfo() {
		std::cout << stringVal;
	}

	static void func() {

	}
};

class B : public A {
public:
	B() {
		this->stringVal = "This is B";
	}
};

class C : public B {
public:
	C() {
		this->stringVal = "This is C";
	}
};

class H {
public:
	virtual void f() = 0;
};


static void RunInheritance() {
	A aClass = A();
	B bClass = B();
	C cClass = C();

	A *aClass1 = &bClass;
	A *aClass2 = &cClass;

	aClass1->printInfo();
	aClass2->printInfo();

	//cClass = aClass;	// cannot assign derived class to base class
	//cClass = bClass;	// cannot assign derived class to base class
	//bClass = aClass;	// cannot assign derived class to base class
	
	aClass = cClass;
	bClass = cClass;

	//H hClass = H();	// no initialization of abstract class allowed
}