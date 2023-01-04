#include <memory>
#include <iostream>
#include "vector.hpp"
#include <sys/_types/_size_t.h>
#include <vector.hpp>

using namespace std;

int main()
{
	ft::vector<int> v;
	ft::vector<int> v2(1, 1);

	for (int i = 0; i < 10; ++i)
		v2.push_back(i);
	for (int i = 0; i < 10; ++i)
		std::cout << v2[i] << std::endl;
}
