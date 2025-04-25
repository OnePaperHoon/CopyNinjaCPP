#include "_Munique_ptr.hpp"
#include <cstdlib>
#include <iostream>

void leaks()
{
	system("leaks run");
}

void func(void)
{
	int *c = new int[1];
	*c = 10;
	_Munique_ptr<int> p(c);
	int* raw_ptr = p.get();
	std::cout << "p.get()" << std::endl;
	std::cout << *raw_ptr << std::endl << std::endl;;

	_Munique_ptr<int> moved = std::move(p);
	std::cout << "std::move(p)" << std::endl;
	if (!p.get())
		std::cout << "p is now null" << std::endl << std::endl;

	return;
}

int main(void)
{
	func();
	atexit(leaks);
	return (0);
}
