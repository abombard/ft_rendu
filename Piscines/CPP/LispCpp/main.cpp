#include <iostream>
#include "Lisp.class.hpp"

int main()
{
	Lisp list;

	int a = 1, b = 0, c = 2, d = 12, e = 42;

	list.push(&a);
	list.push(&b);
	list.push(&c);
	list.del(1);
	list.add(&d);
	list.push(&e);
	std::cout << list << std::endl;
	return (0);
}
