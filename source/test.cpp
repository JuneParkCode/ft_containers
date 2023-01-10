#include <algorithm>
#include <iostream>
#include "map.hpp"
#include <map>

using namespace std;

void mapTest()
{
	std::map<int, int> std_map;
	ft::map<int, int> ft_map;

	std::cout << "test insert\n";
	for (int i = 0; i < 10 ; ++i)
	{
		std_map.insert(std::pair<int, int> (i, i + 1));
		ft_map.insert(ft::pair<int, int> (i, i + 1));
		std::cout << "insert " << i << "," << i + 1 << std::endl;
	}
	std::cout << "test operator[]\n";
	for (int i = 0; i < 10 ; ++i)
	{
		int ft = ft_map[i];
		int std = std_map[i];
		std::cout << ft << ", " << std << std::endl;
	}
	std::cout << "test erase\n";
	for (int i = 0; i < 10; ++i)
	{
		ft_map.erase(ft_map.find(i));
		try
		{
			ft_map.at(i);
			std::cout << "NOT ERASED : " << i << endl;
		}
		catch (...)
		{
			std::cout << "ERASED\n";
			int x = 0;
			for (ft::map<int,int>::iterator it = ft_map.begin(); ; ++it)
			{
				std::cout << it->first << ", " << it->second << std::endl; 
				if (ft_map.size() == 0 || ++x == ft_map.size())
				{
					std::cout << "SIZE: " << ft_map.size() << std::endl;
					break;
				}
			}
			std::cout << std::endl;
		}
	}
}

int main()
{
	mapTest();
}
