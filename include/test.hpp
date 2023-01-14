#ifndef TEST_HPP
#define TEST_HPP

#define S_M std::map<int, int>
#define F_M ft::map<int, int>
#define S_V std::vector<int>
#define F_V ft::vector<int>
#define S_STK std::stack<int>
#define F_STK ft::stack<int>
#define S_SET std::set<int>
#define F_SET ft::set<int>

#define TEST_SIZE 50 * 1000

void test_map();
void test_set();
void test_vector();
void test_stack();

#include <vector>
#include <string>
#include <iostream>
#include <time.h>


const std::string GREEN = "\x1B[1;32m";
const std::string RED = "\x1B[1;31m";
const std::string YELLOW = "\x1B[1;33m";
const std::string WHITE = "\x1B[1;39m";
const std::string RESET = "\033[0m";

#include <iomanip>
#include <unistd.h>

void print_element(std::string t);
void print_header(std::string container);
bool isTimeout(int std_time, int ft_time);
int leaks_test(pid_t pid);

template <class T>
void check_result(const std::string& test_name, int std_time, int ft_time, std::vector<T> std_res, std::vector<T> ft_res)
{
	print_element(test_name);
	print_element(std_res == ft_res ? "OK" : "FAILED");
	
	std::string stdTime = (std_time / 1000 <= ft_time / 1000 ? GREEN : RED) + std::to_string(std_time / 1000) + "ms";
	std::string ftTime = (std_time / 1000 < ft_time / 1000 ? RED : GREEN) + std::to_string(ft_time / 1000) + "ms";
	
	print_element(stdTime);
	if (isTimeout(std_time / 1000, ft_time / 1000))
		print_element(RED + "TIMEOUT");
	else
		print_element(ftTime);
	leaks_test(getpid());
	std::cout << RESET<< std::endl;
}

#endif