#include "_Munique_ptr.hpp"
#include <cstdlib>

void leaks()
{
	system("leaks run");
}

void func(void)
{
	int *c = new int[100];
	_Munique_ptr<int> p(c);
	return;
}

int main(void)
{
	func();
	atexit(leaks);
	return (0);
}
