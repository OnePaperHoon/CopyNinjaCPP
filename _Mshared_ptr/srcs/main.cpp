#include <iostream>
#include "_Mshared_ptr.hpp"

class Test
{
	public:
		Test() { std::cout << "Test created" << std::endl; }
		~Test() { std::cout << "Test destroyed" << std::endl; }

		void Hello() { std::cout << "Hello from Test!" << std::endl; }
	private:
};

void leaks()
{
	system("leaks run");
}

int main(void)
{
	{
		_Mshared_ptr<Test> sp1(new Test());
		std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;

		{
			_Mshared_ptr<Test> sp2(sp1);
			std::cout << "sp2 use_count: " << sp2.use_count() << std::endl;
			sp2->Hello();
			(*sp2).Hello();
		} // sp2 goes out of scope, Test is not destroyed yet
		std::cout << "sq1 use_count after sp2: " << sp1.use_count() << std::endl;
	}
	atexit(leaks);
	return 0;
}
