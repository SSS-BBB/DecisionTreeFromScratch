#include <iostream>
#include "Data.h"

using namespace std;

int main()
{
	Data dummy(1, 2, 1, 3);

	dummy.InsertInt(20);

	dummy.InsertFloat(176.2);
	dummy.InsertFloat(58.7);

	dummy.InsertChar('O');

	dummy.InsertString("Suphawit");
	dummy.InsertString("Buaphan");
	dummy.InsertString("Kaow");

	dummy.PrintData();

	return 0;
}