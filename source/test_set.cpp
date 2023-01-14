#include "test.hpp"
#include "set.hpp"
#include "pair.hpp"
#include <ctime>
#include <set>
#include <utility>

typedef F_SET::iterator F_SETI;
typedef S_SET::iterator S_SETI;


static void test_construct()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	// test 1. construct with nothing.
	S_SET std_set;
	F_SET ft_set;
	
	std_res.push_back(std_set.size());
	ft_res.push_back(ft_set.size());

	S_SET std_tmp;
	F_SET ft_tmp;
	for (int i = 0; i < TEST_SIZE; ++i)
		std_tmp.insert(i);
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_tmp.insert(i);
	// test 2. construct with iterator
	start = clock();
	S_SET std_set_iter(std_tmp.begin(), std_tmp.end());
	end = clock();
	std_time = end - start;

	start = clock();
	F_SET ft_set_iter(ft_tmp.begin(), ft_tmp.end());
	end = clock();
	ft_time = end - start;
	
	// push to result
	std_res.push_back(std_set_iter.size());
	for (S_SETI it = std_set_iter.begin(); it != std_set_iter.end(); ++it)
		std_res.push_back(*it);
	ft_res.push_back(ft_set_iter.size());
	for (F_SETI it = ft_set_iter.begin(); it != ft_set_iter.end(); ++it)
		ft_res.push_back(*it);
	check_result("constructor(), (*iter)", std_time, ft_time, std_res, ft_res);
}

static void test_assign_operator()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set;
	F_SET ft_set;

	std_res.push_back(std_set.size());
	ft_res.push_back(ft_set.size());

	S_SET std_tmp;
	F_SET ft_tmp;
	for (int i = 0; i < TEST_SIZE; ++i)
		std_tmp.insert(i);
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_tmp.insert(i);
	// test 2. assign test
	start = clock();
	S_SET std_set_iter = std_set;
	std_set_iter = std_tmp;
	end = clock();
	std_time = end - start;

	start = clock();
	F_SET ft_set_iter = ft_set;
	ft_set_iter = ft_tmp;
	end = clock();
	ft_time = end - start;
	
	// push to result
	std_res.push_back(std_set_iter.size());
	for (S_SETI it = std_set_iter.begin(); it != std_set_iter.end(); ++it)
		std_res.push_back(*it);
	ft_res.push_back(ft_set_iter.size());
	for (F_SETI it = ft_set_iter.begin(); it != ft_set_iter.end(); ++it)
		ft_res.push_back(*it);

	check_result("operator=", std_time, ft_time, std_res, ft_res);
}

static void test_iterator()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set;
	F_SET ft_set;

	for (int i = 0; i < TEST_SIZE; ++i)
		std_set.insert(i);
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_set.insert(i);
	
	// test 1. common iterating.
	start = clock();
	for (S_SETI it = std_set.begin(); it != std_set.end(); ++it)
	{
		std_res.push_back(*it);
	}
	end = clock();
	std_time = end - start;

	start = clock();
	for (F_SETI it = ft_set.begin(); it != ft_set.end(); ++it)
	{
		ft_res.push_back(*it);
	}
	end = clock();
	ft_time = end - start;

	// test 2. reverse iterating
	for (S_SETI it = --std_set.end(); it != std_set.begin(); --it)
	{
		std_res.push_back(*it);
	}
	for (F_SETI it = --ft_set.end(); it != ft_set.begin(); --it)
	{
		ft_res.push_back(*it);
	}

	// test 3. iterator operator test
	S_SETI it_std = std_set.begin(); 
	F_SETI it_ft = ft_set.begin();

	std_res.push_back(it_std == std_set.find(0));
	ft_res.push_back(it_ft == ft_set.find(0));
	std_res.push_back(it_std == std_set.find(10));
	ft_res.push_back(it_ft == ft_set.find(10));
	std_res.push_back(it_std != std_set.find(0));
	ft_res.push_back(it_ft != ft_set.find(0));
	std_res.push_back(it_std != std_set.find(99));
	ft_res.push_back(it_ft != ft_set.find(99));

	// test 4. const_iterator
	for (S_SET::const_iterator it = std_set.begin(); it != std_set.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_SET::const_iterator it = ft_set.begin(); it != ft_set.end(); ++it)
	{
		ft_res.push_back(*it);
	}
	// reverse
	for (S_SET::const_iterator it = --std_set.end(); it != std_set.begin(); --it)
	{
		std_res.push_back(*it);
	}
	for (F_SET::const_iterator it = --ft_set.end(); it != ft_set.begin(); --it)
	{
		ft_res.push_back(*it);
	}


	check_result("iterator", std_time, ft_time, std_res, ft_res);
}

static void test_empty()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set;
	F_SET ft_set;

	start = clock();
	std_res.push_back(std_set.empty());
	end = clock();
	std_time = end - start;

	start = clock();
	ft_res.push_back(ft_set.empty());
	end = clock();
	ft_time = end - start;

	for (int i = 0; i < 10; ++ i)
	{
		std_set.insert(i);
		std_res.push_back(std_set.empty());
		ft_set.insert(i);
		ft_res.push_back(ft_set.empty());
	}

	check_result("empty()", std_time, ft_time, std_res, ft_res);
}

static void test_size()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set;
	F_SET ft_set;

	start = clock();
	std_res.push_back(std_set.size());
	end = clock();
	std_time = end - start;

	start = clock();
	ft_res.push_back(ft_set.size());
	end = clock();
	ft_time = end - start;

	for (int i = 0; i < 10; ++ i)
	{
		std_set.insert(i);
		std_res.push_back(std_set.size());
		ft_set.insert(i);
		ft_res.push_back(ft_set.size());
	}

	check_result("size()", std_time, ft_time, std_res, ft_res);
}

static void test_max_size()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set;
	F_SET ft_set;

	start = clock();
	std_res.push_back(std_set.max_size() ? 1 : 0);
	end = clock();
	std_time = end - start;

	start = clock();
	ft_res.push_back(ft_set.max_size() ? 1 : 0);
	end = clock();
	ft_time = end - start;

	for (int i = 0; i < 10; ++ i)
	{
		std_set.insert(i);
		std_res.push_back(std_set.max_size() ? 1 : 0);
		ft_set.insert(i);
		ft_res.push_back(ft_set.max_size() ? 1 : 0);
		// std::cout << std_res.back() << ", " << ft_res.back() << std::endl;
	}
	check_result("max_size()", std_time, ft_time, std_res, ft_res);
}

static void test_clear()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set;
	F_SET ft_set;

	// test 1. empty
	std_set.clear();
	std_res.push_back(std_set.size());
	ft_set.clear();
	ft_res.push_back(ft_set.size());

	// test 2. not empty 
	for (int i = 0; i < TEST_SIZE; ++i)
		std_set.insert(i);
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_set.insert(i);
	
	start = clock();
	std_set.clear();
	end = clock();
	std_time = end - start;

	start = clock();
	ft_set.clear();
	end = clock();
	ft_time = end - start;
	
	std_res.push_back(std_set.size());
	ft_res.push_back(ft_set.size());

	check_result("clear()", std_time, ft_time, std_res, ft_res);
}

static void test_insert()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set;
	F_SET ft_set;

	start = clock();
	for (int i = 0; i < TEST_SIZE; ++i)
		std_set.insert(i);
	std_set.insert(10); // not insert.
	end = clock();
	std_time = end - start;

	start = clock();
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_set.insert(i);
	ft_set.insert(10); // not insert
	end = clock();
	ft_time = end - start;

	// push result
	std_res.push_back(std_set.size());
	for (S_SETI it = std_set.begin(); it != std_set.end(); ++it)
		std_res.push_back(*it);
	ft_res.push_back(ft_set.size());
	for (F_SETI it = ft_set.begin(); it != ft_set.end(); ++it)
		ft_res.push_back(*it);

	// test return value
	// success
	std::pair<S_SETI, bool> std_it = std_set.insert(-1);
	ft::pair<F_SETI, bool> ft_it = ft_set.insert(-1);
	std_res.push_back(std_it.second);
	ft_res.push_back(ft_it.second);
	// failed
	std_it = std_set.insert(1);
	ft_it = ft_set.insert(1);
	std_res.push_back(std_it.second);
	ft_res.push_back(ft_it.second);
	std_res.push_back(std_set.size());
	ft_res.push_back(ft_set.size());
	
	check_result("insert(value)", std_time, ft_time, std_res, ft_res);
}

static void test_insert_hint()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set;
	F_SET ft_set;

	S_SETI it_std = std_set.begin();
	start = clock();
	for (int i = 0; i < TEST_SIZE; ++i)
	{
		it_std = std_set.insert(it_std, i);
	}
	it_std = std_set.insert(it_std, 10); // not insert.
	end = clock();
	std_time = end - start;
	std_res.push_back(*it_std);

	F_SETI it_ft = ft_set.begin();
	start = clock();
	for (int i = 0; i < TEST_SIZE; ++i)
	{
		it_ft = ft_set.insert(it_ft, i);
	}
	it_ft = ft_set.insert(it_ft, 10); // not insert
	end = clock();
	ft_time = end - start;
	ft_res.push_back(*it_ft);

	// push result
	std_res.push_back(std_set.size());
	for (S_SETI it = std_set.begin(); it != std_set.end(); ++it)
		std_res.push_back(*it);
	ft_res.push_back(ft_set.size());
	for (F_SETI it = ft_set.begin(); it != ft_set.end(); ++it)
		ft_res.push_back(*it);

	// test return value
	// success
	S_SETI std_it = std_set.insert(std_set.begin(), -1);
	F_SETI ft_it = ft_set.insert(ft_set.begin(), -1);
	std_res.push_back(*std_it);
	ft_res.push_back(*ft_it);
	// failed
	std_it = std_set.insert(std_set.begin(), 1);
	ft_it = ft_set.insert(ft_set.begin(), 1);
	std_res.push_back(*std_it);
	ft_res.push_back(*ft_it);
	
	check_result("insert(hint)", std_time, ft_time, std_res, ft_res);
}

static void test_insert_iter()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set;
	F_SET ft_set;

	// prepare
	S_V std_temp;
	S_V ft_temp;
	for (int i = 0; i < TEST_SIZE; ++i)
	{
		std_temp.push_back(i);
		ft_temp.push_back(i);
	}

	start = clock();
	std_set.insert(std_temp.begin(), std_temp.end());
	end = clock();
	std_time = end - start;

	start = clock();
	ft_set.insert(ft_temp.begin(), ft_temp.end());
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_set.size());
	for (S_SETI it = std_set.begin(); it != std_set.end(); ++it)
		std_res.push_back(*it);
	ft_res.push_back(ft_set.size());
	for (F_SETI it = ft_set.begin(); it != ft_set.end(); ++it)
		ft_res.push_back(*it);
	
	check_result("insert(*iterator)", std_time, ft_time, std_res, ft_res);
}

static void test_erase()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set;
	F_SET ft_set;

	// do not make segfault in here
	{
		std_set.erase(-1);
		ft_set.erase(-1);
	}
	// prepare
	for (int i = 0; i < TEST_SIZE; ++i)
		std_set.insert(i);
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_set.insert(i);
	// test 1. erase exist
	start = clock();
	for (S_SETI it = std_set.begin(); it != std_set.end();)
	{
		S_SETI temp = it++;
		std_set.erase(*temp);
	}
	end = clock();
	std_time = end - start;
	start = clock();
	for (F_SETI it = ft_set.begin(); it != ft_set.end();)
	{
		F_SETI temp = it++;
		ft_set.erase(*temp);
	}
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_set.size());
	ft_res.push_back(ft_set.size());
	
	std_res.push_back(std_set.find(1) == std_set.end());
	ft_res.push_back(ft_set.find(1) == ft_set.end());
	
	// test 2. erase not exist
	std_set.erase(-1);
	ft_set.erase(-1);
	std_res.push_back(std_set.size());
	ft_res.push_back(ft_set.size());

	std_res.push_back(std_set.size());
	for (S_SETI it = std_set.begin(); it != std_set.end(); ++it)
		std_res.push_back(*it);
	ft_res.push_back(ft_set.size());
	for (F_SETI it = ft_set.begin(); it != ft_set.end(); ++it)
		ft_res.push_back(*it);
	
	// test 3. in empty case
	std_set.clear();
	ft_set.clear();
	std_set.erase(-1);
	ft_set.erase(-1);
	std_res.push_back(std_set.size());
	ft_res.push_back(ft_set.size());

	check_result("erase(key)", std_time, ft_time, std_res, ft_res);
}

static void test_erase_pos()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set;
	F_SET ft_set;

	// if empty, it makes segfault

	// prepare
	for (int i = 0; i < TEST_SIZE; ++i)
		std_set.insert(i);
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_set.insert(i);

	// test 1. erase exist
	start = clock();
	for (S_SETI it = std_set.begin(); it != std_set.end();)
	{
		S_SETI temp = it++;
		std_set.erase(temp);
	}
	end = clock();
	std_time = end - start;

	start = clock();
	for (F_SETI it = ft_set.begin(); it != ft_set.end();)
	{
		F_SETI temp = it++;
		ft_set.erase(temp);
	}
	end = clock();
	ft_time = end - start;
	std_res.push_back(std_set.size());
	ft_res.push_back(ft_set.size());
	std_res.push_back(std_set.find(1) == std_set.end());
	ft_res.push_back(ft_set.find(1) == ft_set.end());
	// test 2. erase not exist -> SEGFAULT
	// std_set.erase(std_set.end());
	// ft_set.erase(ft_set.end());
	// std_res.push_back(std_set.size());
	// ft_res.push_back(ft_set.size());

	std_res.push_back(std_set.size());
	for (S_SETI it = std_set.begin(); it != std_set.end(); ++it)
		std_res.push_back(*it);
	ft_res.push_back(ft_set.size());
	for (F_SETI it = ft_set.begin(); it != ft_set.end(); ++it)
		ft_res.push_back(*it);

	// BELOW CODES MUST MAKE SEGFAULT.	
	// // test 3. in empty case 
	// std_set.clear();
	// ft_set.clear();
	// std_set.erase(std_set.end());
	// ft_set.erase(ft_set.end());
	// std_res.push_back(std_set.size());
	// ft_res.push_back(ft_set.size());
	// // test 4. in empty case, invalid iterator
	// std_set.erase(*it);
	// ft_set.erase(*it2);
	// std_res.push_back(std_set.size());
	// ft_res.push_back(ft_set.size());
	check_result("erase(pos)", std_time, ft_time, std_res, ft_res);
}

static void test_swap()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set;
	F_SET ft_set;

	// prepare
	for (int i = 0; i < TEST_SIZE; ++i)
		std_set.insert(i);
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_set.insert(i);

	S_SET std_tmp;
	F_SET ft_tmp;
	start = clock();
	std_set.swap(std_tmp);
	end = clock();
	std_time = end - start;

	start = clock();
	ft_set.swap(ft_tmp);
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_set.size());
	for (S_SETI it = std_set.begin(); it != std_set.end(); ++it)
		std_res.push_back(*it);
	ft_res.push_back(ft_set.size());
	for (F_SETI it = ft_set.begin(); it != ft_set.end(); ++it)
		ft_res.push_back(*it);

	std_res.push_back(std_tmp.size());
	for (S_SETI it = std_tmp.begin(); it != std_tmp.end(); ++it)
		std_res.push_back(*it);
	ft_res.push_back(ft_tmp.size());
	for (F_SETI it = ft_tmp.begin(); it != ft_tmp.end(); ++it)
		ft_res.push_back(*it);
	check_result("swap()", std_time, ft_time, std_res, ft_res);
}

static void test_count()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set;
	F_SET ft_set;

	// test 1. in empty case
	std_res.push_back(std_set.count(-1));
	ft_res.push_back(ft_set.count(-1));
	
	// prepare
	for (int i = 0; i < TEST_SIZE; ++i)
		std_set.insert(i);
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_set.insert(i);

	// test 2. exist
	start = clock();
	std_res.push_back(std_set.count(1));
	end = clock();
	std_time = end - start;
	std_res.push_back(std_set.count(-1));
	// test 3. not exist
	start = clock();
	ft_res.push_back(ft_set.count(1));
	end = clock();
	ft_time = end - start;
	ft_res.push_back(ft_set.count(-1));
	check_result("count()", std_time, ft_time, std_res, ft_res);
}

static void test_find()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set;
	F_SET ft_set;

	// test 1. find in empty case
	std_res.push_back(std_set.find(1) == std_set.end());
	ft_res.push_back(ft_set.find(1) == ft_set.end());

	// test 2. find in exist
	for (int i = 0; i < TEST_SIZE; ++i)
		std_set.insert(i);
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_set.insert(i);
	start = clock();
	for (int i = 0; i < TEST_SIZE; ++i)
		std_res.push_back(*std_set.find(i));
	end = clock();
	std_time = end - start;
	
	start = clock();
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_res.push_back(*ft_set.find(i));
	end = clock();
	ft_time = end - start;

	// test 3. not empty but not exist
	std_res.push_back(std_set.find(-1) == std_set.end());
	ft_res.push_back(ft_set.find(-1) == ft_set.end());

	check_result("find())", std_time, ft_time, std_res, ft_res);
}

static void test_equal_range()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set;
	F_SET ft_set;

	std::pair<S_SETI, S_SETI> std_pair;
	ft::pair<F_SETI, F_SETI> ft_pair;
	std_pair = std_set.equal_range(3);
	ft_pair = ft_set.equal_range(3);
	std_res.push_back(std_pair.first == std_set.end());
	ft_res.push_back(ft_pair.first == ft_set.end());
	std_res.push_back(std_pair.second == std_set.end());
	ft_res.push_back(ft_pair.second == ft_set.end());
	
	// preapare
	for (int i = 0; i < TEST_SIZE; ++i)
		std_set.insert(i);
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_set.insert(i);
	
	start = clock();
	std_pair = std_set.equal_range(3);
	end = clock();
	std_time = end - start;

	start = clock();
	ft_pair = ft_set.equal_range(3);
	end = clock();
	ft_time = end - start;
	
	std_res.push_back(*std_pair.first);
	std_res.push_back(*std_pair.second);
	ft_res.push_back(*std_pair.first);
	ft_res.push_back(*ft_pair.second);

	check_result("equal_range()", std_time, ft_time, std_res, ft_res);
}

static void test_lower_bound()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set;
	F_SET ft_set;

	S_SETI std_it;
	F_SETI ft_it;
	// check in empty 
	std_it = std_set.lower_bound(3);
	ft_it = ft_set.lower_bound(3);
	std_res.push_back(std_it == std_set.end());
	ft_res.push_back(ft_it == ft_set.end());
	std_res.push_back(std_it == std_set.end());
	ft_res.push_back(ft_it == ft_set.end());
	
	// preapare
	for (int i = 0; i < TEST_SIZE; ++i)
		std_set.insert(i);
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_set.insert(i);
	
	start = clock();
	std_it = std_set.lower_bound(3);
	end = clock();
	std_time = end - start;

	start = clock();
	ft_it = ft_set.lower_bound(3);
	end = clock();
	ft_time = end - start;
	
	std_res.push_back(*std_it);
	std_res.push_back(*std_it);
	ft_res.push_back(*ft_it);
	ft_res.push_back(*ft_it);

	check_result("lower_bound()", std_time, ft_time, std_res, ft_res);
}
static void test_upper_bound()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set;
	F_SET ft_set;

	S_SETI std_it;
	F_SETI ft_it;
	// check in empty 
	std_it = std_set.upper_bound(3);
	ft_it = ft_set.upper_bound(3);
	std_res.push_back(std_it == std_set.end());
	ft_res.push_back(ft_it == ft_set.end());
	std_res.push_back(std_it == std_set.end());
	ft_res.push_back(ft_it == ft_set.end());
	
	// preapare
	for (int i = 0; i < TEST_SIZE; ++i)
		std_set.insert(i);
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_set.insert(i);
	
	start = clock();
	std_it = std_set.upper_bound(3);
	end = clock();
	std_time = end - start;

	start = clock();
	ft_it = ft_set.upper_bound(3);
	end = clock();
	ft_time = end - start;
	
	std_res.push_back(*std_it);
	std_res.push_back(*std_it);
	ft_res.push_back(*ft_it);
	ft_res.push_back(*ft_it);

	check_result("upper_bound()", std_time, ft_time, std_res, ft_res);
}

// static void test_key_comp()
// {
// 	clock_t start, end;
// 	int std_time, ft_time;
// 	S_V std_res, ft_res;
// 	S_SET std_set;
// 	F_SET ft_set;

// 	check_result("constructor(*iterator)", std_time, ft_time, std_res, ft_res);
// }
// static void test_value_comp()
// {
// 	clock_t start, end;
// 	int std_time, ft_time;
// 	S_V std_res, ft_res;
// 	S_SET std_set;
// 	F_SET ft_set;

// 	check_result("constructor(*iterator)", std_time, ft_time, std_res, ft_res);
// }
static void test_operator_compare()
{
	// clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_SET std_set, std_tmp;
	F_SET ft_set, ft_tmp;

	std_set.insert(1);
	std_tmp.insert(2);
	ft_set.insert(1);
	ft_tmp.insert(2);
	
	std_time = 0;
	ft_time = 0;

	std_res.push_back(std_set == std_tmp);
	std_res.push_back(std_set == std_set);
	std_res.push_back(std_set != std_tmp);
	std_res.push_back(std_set != std_set);
	std_res.push_back(std_set != std_tmp);
	std_res.push_back(std_set > std_tmp);
	std_res.push_back(std_set >= std_tmp);
	std_res.push_back(std_set < std_tmp);
	std_res.push_back(std_set <= std_tmp);

	ft_res.push_back(ft_set == ft_tmp);
	ft_res.push_back(ft_set == ft_set);
	ft_res.push_back(ft_set != ft_tmp);
	ft_res.push_back(ft_set != ft_set);
	ft_res.push_back(ft_set != ft_tmp);
	ft_res.push_back(ft_set > ft_tmp);
	ft_res.push_back(ft_set >= ft_tmp);
	ft_res.push_back(ft_set < ft_tmp);
	ft_res.push_back(ft_set <= ft_tmp);

	check_result("constructor(*iterator)", std_time, ft_time, std_res, ft_res);
}

void test_set()
{
	print_header("set");
	test_construct();
	test_assign_operator();
	test_iterator();
	test_empty();
	test_size();
	test_max_size(); // this can not equal with std::set, because, std::set uses allocator_traits
	test_clear();
	test_insert();
	test_insert_hint();
	test_insert_iter();
	test_erase();
	test_erase_pos();
	test_swap();
	test_count();
	test_find();
	test_equal_range();
	test_lower_bound();
	test_upper_bound();
	test_operator_compare();
	// test_key_comp();
	// test_value_comp();
}