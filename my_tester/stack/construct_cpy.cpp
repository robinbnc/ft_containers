#include "print_stack.hpp"

#ifndef NAME_SPACE
# define NAME_SPACE std
#endif

using namespace NAME_SPACE;

#define TESTED_TYPE foo<int>
#define t_stack_ NAME_SPACE::stack<TESTED_TYPE>
typedef t_stack_::container_type container_type;

int		main(void)
{
	{	
		NAME_SPACE::stack<TESTED_TYPE> stck;

		std::cout << "empty: " << stck.empty() << std::endl;
		std::cout << "size: " << stck.size() << std::endl;

		stck.push(41);
		stck.push(29);
		stck.push(10);
		stck.push(42);
		std::cout << "Added some elements" << std::endl;

		std::cout << "empty: " << stck.empty() << std::endl;
		printSize(stck);
	}
	{
		container_type	ctnr;

		ctnr.push_back(21);
		ctnr.push_back(42);
		ctnr.push_back(1337);
		ctnr.push_back(19);
		ctnr.push_back(0);
		ctnr.push_back(183792);

		t_stack_		stck(ctnr);

		std::cout << "empty: " << stck.empty() << std::endl;
		std::cout << "size: " << stck.size() << std::endl;

		stck.push(1);
		stck.push(2);
		stck.push(3);
		stck.push(4);
		stck.push(5);
		stck.push(6);

		std::cout << "Added some elements" << std::endl;

		std::cout << "empty: " << stck.empty() << std::endl;
		printSize(stck);
	}
	return (0);
}