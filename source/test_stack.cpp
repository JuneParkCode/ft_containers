#include "test.hpp"
#include "stack.hpp"
#include <stack>


#define TEST_VEC_SIZE 50 * 100000

void fill(S_STK& s)
{
	for (int i = 0; i < TEST_VEC_SIZE; ++i)
		s.push(i);
}

void fill(F_STK& s)
{
	for (int i = 0; i < TEST_VEC_SIZE; ++i)
		s.push(i);
}

static void test_construct_default()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	
	// test 1
	start = clock();
	S_STK std_stk;
	end = clock();
	std_time = end - start;
	start = clock();
	F_STK ft_stk;
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_stk.size());
	ft_res.push_back(ft_stk.size());
	check_result("constructor(default)", std_time, ft_time, std_res, ft_res);
}

static void test_assign_operator()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_STK std_tmp;
	F_STK ft_tmp;
	fill(std_tmp);
	fill(ft_tmp);

	// test 1
	start = clock();
	S_STK std_stk = std_tmp;
	end = clock();
	std_time = end - start;

	start = clock();
	F_STK ft_stk = ft_tmp;
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_stk.size());
	ft_res.push_back(ft_stk.size());
	while (!std_stk.empty())
	{
		std_res.push_back(std_stk.top());
		std_stk.pop();
	}
	while (!ft_stk.empty())
	{
		ft_res.push_back(ft_stk.top());
		ft_stk.pop();
	}
	check_result("operator=", std_time, ft_time, std_res, ft_res);
}

static void test_size()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_STK std_stk;
	fill(std_stk);
	F_STK ft_stk;
	fill(ft_stk);

	// test 1. with elem
	int std_, ft_;
	start = clock();
	std_ = std_stk.size();
	end = clock();
	std_time = end - start;
	start = clock();
	ft_ = ft_stk.size();
	end = clock();
	ft_time = end - start;
	std_res.push_back(std_);
	ft_res.push_back(ft_);

	// test 2. with no elem;
	S_STK std_tmp;
	F_STK ft_tmp;
	std_res.push_back(std_tmp.size());
	ft_res.push_back(ft_tmp.size());

	check_result("size()", std_time, ft_time, std_res, ft_res);
}

static void test_empty()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_STK std_stk;
	fill(std_stk);
	F_STK ft_stk;
	fill(ft_stk);

	// test 1. with elem
	int std_, ft_;
	start = clock();
	std_ = std_stk.empty();
	end = clock();
	std_time = end - start;
	start = clock();
	ft_ = ft_stk.empty();
	end = clock();
	ft_time = end - start;
	std_res.push_back(std_);
	ft_res.push_back(ft_);

	// test 2. with no elem;
	S_STK std_tmp;
	F_STK ft_tmp;
	std_res.push_back(std_tmp.empty());
	ft_res.push_back(ft_tmp.empty());

	check_result("empty()", std_time, ft_time, std_res, ft_res);
}

static void test_top()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_STK std_stk;
	fill(std_stk);
	F_STK ft_stk;
	fill(ft_stk);

	// check time.
	start = clock();
	int x = std_stk.top();
	end = clock();
	std_time = end - start;

	start = clock();
	int y = ft_stk.top();
	end = clock();
	ft_time = end - start;

	std_res.push_back(x);
	ft_res.push_back(y);
	
	// in empty case it will be make SEGFAULT
	check_result("top()", std_time, ft_time, std_res, ft_res);
}

static void test_push()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_STK std_stk;
	F_STK ft_stk;


	// test 1
	start = clock();
	for (int i = 0; i < TEST_VEC_SIZE; ++i)
		std_stk.push(i);
	end = clock();
	std_time = end - start;
	start = clock();
	for (int i = 0; i < TEST_VEC_SIZE; ++i)
		ft_stk.push(i);
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_stk.size());
	ft_res.push_back(ft_stk.size());
	while (!std_stk.empty())
	{
		std_res.push_back(std_stk.top());
		std_stk.pop();
	}
	while (!ft_stk.empty())
	{
		ft_res.push_back(ft_stk.top());
		ft_stk.pop();
	}

	check_result("push()", std_time, ft_time, std_res, ft_res);
}

static void test_pop()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_STK std_stk;
	fill(std_stk);
	F_STK ft_stk;
	fill(ft_stk);

	// test 1
	start = clock();
	for (int i = 0; i < TEST_VEC_SIZE; ++i)
	{
		std_res.push_back(std_stk.top());
		std_stk.pop();
	}
	end = clock();
	std_time = end - start;
	start = clock();
	for (int i = 0; i < TEST_VEC_SIZE; ++i)
	{
		ft_res.push_back(ft_stk.top());
		ft_stk.pop();
	}
	end = clock();
	ft_time = end - start;
	std_res.push_back(std_stk.size());
	ft_res.push_back(ft_stk.size());
	while (!std_stk.empty())
	{
		std_res.push_back(std_stk.top());
		std_stk.pop();
	}
	while (!ft_stk.empty())
	{
		ft_res.push_back(ft_stk.top());
		ft_stk.pop();
	}
	check_result("pop()", std_time, ft_time, std_res, ft_res);
}

static void test_operator_compare()
{
	// clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_STK std_stk, std_tmp;
	F_STK ft_stk, ft_tmp;

	std_stk.push(1);
	std_tmp.push(2);
	ft_stk.push(1);
	ft_tmp.push(2);
	
	std_time = 0;
	ft_time = 0;

	std_res.push_back(std_stk == std_tmp);
	std_res.push_back(std_stk == std_stk);
	std_res.push_back(std_stk != std_tmp);
	std_res.push_back(std_stk != std_stk);
	std_res.push_back(std_stk != std_tmp);
	std_res.push_back(std_stk > std_tmp);
	std_res.push_back(std_stk >= std_tmp);
	std_res.push_back(std_stk < std_tmp);
	std_res.push_back(std_stk <= std_tmp);

	ft_res.push_back(ft_stk == ft_tmp);
	ft_res.push_back(ft_stk == ft_stk);
	ft_res.push_back(ft_stk != ft_tmp);
	ft_res.push_back(ft_stk != ft_stk);
	ft_res.push_back(ft_stk != ft_tmp);
	ft_res.push_back(ft_stk > ft_tmp);
	ft_res.push_back(ft_stk >= ft_tmp);
	ft_res.push_back(ft_stk < ft_tmp);
	ft_res.push_back(ft_stk <= ft_tmp);

	check_result("operator(compare)", std_time, ft_time, std_res, ft_res);
}

void test_stack()
{
	print_header("STACK");
	test_construct_default();
	test_assign_operator();
	test_empty();
	test_size();
	test_top();
	test_push();
	test_pop();
	test_operator_compare();
}