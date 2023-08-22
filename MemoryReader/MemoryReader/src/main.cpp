#include <iostream>
#include "memory.h"

int main()
{
	Memory mem = Memory("mspaint.exe");

	std::cout << "Process id: " << mem.GetProcessId() << std::endl;	

	std::cin.get();
	return 0;
}