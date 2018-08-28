#include <stdio.h>
#include <iostream>

#include "MyBoost.h"
#include "Testthread.h"

int main()
{
	Testthread test_thread;
	test_thread.BeginTest();

	int i;
	std::cin >> i;
	return 0;
}
