#include "test.hpp"
#include "map.hpp"
#include "ft_pair.hpp"
#include <ctime>
#include <map>
#include <utility>

typedef F_M::iterator F_MI;
typedef S_M::iterator S_MI;


static void test_construct()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	// test 1. construct with nothing.
	S_M std_map;
	F_M ft_map;
	
	std_res.push_back(std_map.size());
	ft_res.push_back(ft_map.size());

	S_M std_tmp;
	F_M ft_tmp;
	for (int i = 0; i < TEST_SIZE; ++i)
		std_tmp.insert(std::make_pair(i, i));
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_tmp.insert(ft::make_pair(i, i));
	// test 2. construct with iterator
	start = clock();
	S_M std_map_iter(std_tmp.begin(), std_tmp.end());
	end = clock();
	std_time = end - start;

	start = clock();
	F_M ft_map_iter(ft_tmp.begin(), ft_tmp.end());
	end = clock();
	ft_time = end - start;
	
	// push to result
	std_res.push_back(std_map_iter.size());
	for (S_MI it = std_map_iter.begin(); it != std_map_iter.end(); ++it)
		std_res.push_back(it->first);
	ft_res.push_back(ft_map_iter.size());
	for (F_MI it = ft_map_iter.begin(); it != ft_map_iter.end(); ++it)
		ft_res.push_back(it->first);
	check_result("constructor(), (iter)", std_time, ft_time, std_res, ft_res);
}

static void test_assign_operator()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	std_res.push_back(std_map.size());
	ft_res.push_back(ft_map.size());

	S_M std_tmp;
	F_M ft_tmp;
	for (int i = 0; i < TEST_SIZE; ++i)
		std_tmp.insert(std::make_pair(i, i));
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_tmp.insert(ft::make_pair(i, i));
	// test 2. assign test
	start = clock();
	S_M std_map_iter = std_map;
	std_map_iter = std_tmp;
	end = clock();
	std_time = end - start;

	start = clock();
	F_M ft_map_iter = ft_map;
	ft_map_iter = ft_tmp;
	end = clock();
	ft_time = end - start;
	
	// push to result
	std_res.push_back(std_map_iter.size());
	for (S_MI it = std_map_iter.begin(); it != std_map_iter.end(); ++it)
		std_res.push_back(it->first);
	ft_res.push_back(ft_map_iter.size());
	for (F_MI it = ft_map_iter.begin(); it != ft_map_iter.end(); ++it)
		ft_res.push_back(it->first);

	check_result("operator=", std_time, ft_time, std_res, ft_res);
}

static void test_at()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	for (int i = 0; i < TEST_SIZE; ++i)
		std_map.insert(std::make_pair(i, i));
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_map.insert(ft::make_pair(i, i));
	for (S_MI it = std_map.begin(); it != std_map.end(); ++it)
	{
		std_res.push_back(std_map.at(it->first));
	}
	for (F_MI it = ft_map.begin(); it != ft_map.end(); ++it)
	{
		ft_res.push_back(ft_map.at(it->first));
	}
	// test throw
	try { std_map.at(-1); } catch (...) { std_res.push_back(true);}
	try { ft_map.at(-1); } catch (...) { ft_res.push_back(true);}
	// check time.
	start = clock();
	std_map.at(1000);
	end = clock();
	std_time = end - start;

	start = clock();
	ft_map.at(1000);
	end = clock();
	ft_time = end - start;

	check_result("at()", std_time, ft_time, std_res, ft_res);
}

static void test_operator_access()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	for (int i = 0; i < TEST_SIZE; ++i)
		std_map.insert(std::make_pair(i, i));
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_map.insert(ft::make_pair(i, i));
	for (S_MI it = std_map.begin(); it != std_map.end(); ++it)
	{
		std_res.push_back(std_map[(it->first)]);
	}
	for (F_MI it = ft_map.begin(); it != ft_map.end(); ++it)
	{
		ft_res.push_back(ft_map[(it->first)]);
	}
	// check not exist value
	std_res.push_back(std_map[-1]);
	ft_res.push_back(ft_map[-1]);

	// check time.
	start = clock();
	int x = std_map[1000];
	end = clock();
	std_time = end - start;

	start = clock();
	int y = ft_map[1000];
	end = clock();
	(void) x; (void) y;
	ft_time = end - start;

	check_result("operator[]", std_time, ft_time, std_res, ft_res);
}

static void test_iterator()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	for (int i = 0; i < TEST_SIZE; ++i)
		std_map.insert(std::make_pair(i, i));
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_map.insert(ft::make_pair(i, i));
	
	// test 1. common iterating.
	start = clock();
	for (S_MI it = std_map.begin(); it != std_map.end(); ++it)
	{
		std_res.push_back(std_map[(it->first)]);
	}
	end = clock();
	std_time = end - start;

	start = clock();
	for (F_MI it = ft_map.begin(); it != ft_map.end(); ++it)
	{
		ft_res.push_back(ft_map[(it->first)]);
	}
	end = clock();
	ft_time = end - start;

	// test 2. reverse iterating
	for (S_MI it = --std_map.end(); it != std_map.begin(); --it)
	{
		std_res.push_back(std_map[(it->first)]);
	}
	for (F_MI it = --ft_map.end(); it != ft_map.begin(); --it)
	{
		ft_res.push_back(ft_map[(it->first)]);
	}

	// test 3. iterator operator test
	S_MI it_std = std_map.begin(); 
	F_MI it_ft = ft_map.begin();

	std_res.push_back(it_std == std_map.find(0));
	ft_res.push_back(it_ft == ft_map.find(0));
	std_res.push_back(it_std == std_map.find(10));
	ft_res.push_back(it_ft == ft_map.find(10));
	std_res.push_back(it_std != std_map.find(0));
	ft_res.push_back(it_ft != ft_map.find(0));
	std_res.push_back(it_std != std_map.find(99));
	ft_res.push_back(it_ft != ft_map.find(99));

	// test 4. const_iterator
	for (S_M::const_iterator it = std_map.begin(); it != std_map.end(); ++it)
	{
		std_res.push_back(std_map[(it->first)]);
	}
	for (F_M::const_iterator it = ft_map.begin(); it != ft_map.end(); ++it)
	{
		ft_res.push_back(ft_map[(it->first)]);
	}
	// reverse
	for (S_M::const_iterator it = --std_map.end(); it != std_map.begin(); --it)
	{
		std_res.push_back(std_map[(it->first)]);
	}
	for (F_M::const_iterator it = --ft_map.end(); it != ft_map.begin(); --it)
	{
		ft_res.push_back(ft_map[(it->first)]);
	}


	check_result("iterator", std_time, ft_time, std_res, ft_res);
}

static void test_empty()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	start = clock();
	std_res.push_back(std_map.empty());
	end = clock();
	std_time = end - start;

	start = clock();
	ft_res.push_back(ft_map.empty());
	end = clock();
	ft_time = end - start;

	for (int i = 0; i < 10; ++ i)
	{
		std_map.insert(std::make_pair(i, 1));
		std_res.push_back(std_map.empty());
		ft_map.insert(ft::make_pair(i, 1));
		ft_res.push_back(ft_map.empty());
	}

	check_result("empty()", std_time, ft_time, std_res, ft_res);
}

static void test_size()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	start = clock();
	std_res.push_back(std_map.size());
	end = clock();
	std_time = end - start;

	start = clock();
	ft_res.push_back(ft_map.size());
	end = clock();
	ft_time = end - start;

	for (int i = 0; i < 10; ++ i)
	{
		std_map.insert(std::make_pair(i, 1));
		std_res.push_back(std_map.size());
		ft_map.insert(ft::make_pair(i, 1));
		ft_res.push_back(ft_map.size());
	}

	check_result("size()", std_time, ft_time, std_res, ft_res);
}

static void test_max_size()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	start = clock();
	std_res.push_back(std_map.max_size() ? 1 : 0);
	end = clock();
	std_time = end - start;

	start = clock();
	ft_res.push_back(ft_map.max_size() ? 1 : 0);
	end = clock();
	ft_time = end - start;

	for (int i = 0; i < 10; ++ i)
	{
		std_map.insert(std::make_pair(i, 1));
		std_res.push_back(std_map.max_size() ? 1 : 0);
		ft_map.insert(ft::make_pair(i, 1));
		ft_res.push_back(ft_map.max_size() ? 1 : 0);
		// std::cout << std_res.back() << ", " << ft_res.back() << std::endl;
	}
	check_result("max_size()", std_time, ft_time, std_res, ft_res);
}

static void test_clear()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	// test 1. empty
	std_map.clear();
	std_res.push_back(std_map.size());
	ft_map.clear();
	ft_res.push_back(ft_map.size());

	// test 2. not empty 
	for (int i = 0; i < TEST_SIZE; ++i)
		std_map.insert(std::make_pair(i, i));
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_map.insert(ft::make_pair(i, i));
	
	start = clock();
	std_map.clear();
	end = clock();
	std_time = end - start;

	start = clock();
	ft_map.clear();
	end = clock();
	ft_time = end - start;
	
	std_res.push_back(std_map.size());
	ft_res.push_back(ft_map.size());

	check_result("clear()", std_time, ft_time, std_res, ft_res);
}

static void test_insert()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	start = clock();
	for (int i = 0; i < TEST_SIZE; ++i)
		std_map.insert(std::make_pair(i, i));
	std_map.insert(std::make_pair(10, 10)); // not insert.
	end = clock();
	std_time = end - start;

	start = clock();
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_map.insert(ft::make_pair(i, i));
	ft_map.insert(ft::make_pair(10, 10)); // not insert
	end = clock();
	ft_time = end - start;

	// push result
	std_res.push_back(std_map.size());
	for (S_MI it = std_map.begin(); it != std_map.end(); ++it)
		std_res.push_back(it->first);
	ft_res.push_back(ft_map.size());
	for (F_MI it = ft_map.begin(); it != ft_map.end(); ++it)
		ft_res.push_back(it->first);

	// test return value
	// success
	std::pair<S_MI, bool> std_it = std_map.insert(std::make_pair(-1, 1));
	ft::pair<F_MI, bool> ft_it = ft_map.insert(ft::make_pair(-1, 1));
	std_res.push_back(std_it.second);
	ft_res.push_back(ft_it.second);
	// failed
	std_it = std_map.insert(std::make_pair(1, 1));
	ft_it = ft_map.insert(ft::make_pair(1, 1));
	std_res.push_back(std_it.second);
	ft_res.push_back(ft_it.second);
	std_res.push_back(std_map.size());
	ft_res.push_back(ft_map.size());
	
	check_result("insert(value)", std_time, ft_time, std_res, ft_res);
}

static void test_insert_hint()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	S_MI it_std = std_map.begin();
	start = clock();
	for (int i = 0; i < TEST_SIZE; ++i)
	{
		it_std = std_map.insert(it_std, std::make_pair(i, i));
	}
	it_std = std_map.insert(it_std, std::make_pair(10, 10)); // not insert.
	end = clock();
	std_time = end - start;
	std_res.push_back(it_std->first);

	F_MI it_ft = ft_map.begin();
	start = clock();
	for (int i = 0; i < TEST_SIZE; ++i)
	{
		it_ft = ft_map.insert(it_ft, ft::make_pair(i, i));
	}
	it_ft = ft_map.insert(it_ft, ft::make_pair(10, 10)); // not insert
	end = clock();
	ft_time = end - start;
	ft_res.push_back(it_ft->first);

	// push result
	std_res.push_back(std_map.size());
	for (S_MI it = std_map.begin(); it != std_map.end(); ++it)
		std_res.push_back(it->first);
	ft_res.push_back(ft_map.size());
	for (F_MI it = ft_map.begin(); it != ft_map.end(); ++it)
		ft_res.push_back(it->first);

	// test return value
	// success
	S_MI std_it = std_map.insert(std_map.begin(), std::make_pair(-1, 1));
	F_MI ft_it = ft_map.insert(ft_map.begin(), ft::make_pair(-1, 1));
	std_res.push_back(std_it->first);
	ft_res.push_back(ft_it->first);
	// failed
	std_it = std_map.insert(std_map.begin(), std::make_pair(1, 1));
	ft_it = ft_map.insert(ft_map.begin(), ft::make_pair(1, 1));
	std_res.push_back(std_it->first);
	ft_res.push_back(ft_it->first);
	std_res.push_back(std_map.size());
	ft_res.push_back(ft_map.size());
	
	
	check_result("insert(hint)", std_time, ft_time, std_res, ft_res);
}

static void test_insert_iter()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	// prepare
	std::vector<std::pair<int, int> > std_temp;
	std::vector<ft::pair<int, int> > ft_temp;
	for (int i = 0; i < TEST_SIZE; ++i)
	{
		std_temp.push_back(std::make_pair(i, i));
		ft_temp.push_back(ft::make_pair(i, i));
	}

	start = clock();
	std_map.insert(std_temp.begin(), std_temp.end());
	end = clock();
	std_time = end - start;

	start = clock();
	ft_map.insert(ft_temp.begin(), ft_temp.end());
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_map.size());
	for (S_MI it = std_map.begin(); it != std_map.end(); ++it)
		std_res.push_back(it->first);
	ft_res.push_back(ft_map.size());
	for (F_MI it = ft_map.begin(); it != ft_map.end(); ++it)
		ft_res.push_back(it->first);
	
	check_result("insert(iterator)", std_time, ft_time, std_res, ft_res);
}

static void test_erase()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	// do not make segfault in here
	{
		std_map.erase(-1);
		ft_map.erase(-1);
	}
	// prepare
	for (int i = 0; i < TEST_SIZE; ++i)
		std_map.insert(std::make_pair(i, i));
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_map.insert(ft::make_pair(i, i));
	// test 1. erase exist
	start = clock();
	for (S_MI it = std_map.begin(); it != std_map.end();)
	{
		S_MI temp = it++;
		std_map.erase(temp->first);
	}
	end = clock();
	std_time = end - start;
	start = clock();
	for (F_MI it = ft_map.begin(); it != ft_map.end();)
	{
		F_MI temp = it++;
		ft_map.erase(temp->first);
	}
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_map.size());
	ft_res.push_back(ft_map.size());
	try { std_map.at(1); } catch (...) { std_res.push_back(true);}
	try { ft_map.at(1); } catch (...) { ft_res.push_back(true);}
	// test 2. erase not exist
	std_map.erase(-1);
	ft_map.erase(-1);
	std_res.push_back(std_map.size());
	ft_res.push_back(ft_map.size());

	std_res.push_back(std_map.size());
	for (S_MI it = std_map.begin(); it != std_map.end(); ++it)
		std_res.push_back(it->first);
	ft_res.push_back(ft_map.size());
	for (F_MI it = ft_map.begin(); it != ft_map.end(); ++it)
		ft_res.push_back(it->first);
	
	// test 3. in empty case
	std_map.clear();
	ft_map.clear();
	std_map.erase(-1);
	ft_map.erase(-1);
	std_res.push_back(std_map.size());
	ft_res.push_back(ft_map.size());

	check_result("erase(key)", std_time, ft_time, std_res, ft_res);
}

static void test_erase_pos()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	// if empty, it makes segfault

	// prepare
	for (int i = 0; i < TEST_SIZE; ++i)
		std_map.insert(std::make_pair(i, i));
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_map.insert(ft::make_pair(i, i));

	// test 1. erase exist
	start = clock();
	for (S_MI it = std_map.begin(); it != std_map.end();)
	{
		S_MI temp = it++;
		std_map.erase(temp);
	}
	end = clock();
	std_time = end - start;

	start = clock();
	for (F_MI it = ft_map.begin(); it != ft_map.end();)
	{
		F_MI temp = it++;
		ft_map.erase(temp);
	}
	end = clock();
	ft_time = end - start;
	std_res.push_back(std_map.size());
	ft_res.push_back(ft_map.size());
	try { std_map.at(1); } catch (...) { std_res.push_back(true);}
	try { ft_map.at(1); } catch (...) { ft_res.push_back(true);}
	// test 2. erase not exist -> SEGFAULT
	// std_map.erase(std_map.end());
	// ft_map.erase(ft_map.end());
	// std_res.push_back(std_map.size());
	// ft_res.push_back(ft_map.size());

	std_res.push_back(std_map.size());
	for (S_MI it = std_map.begin(); it != std_map.end(); ++it)
		std_res.push_back(it->first);
	ft_res.push_back(ft_map.size());
	for (F_MI it = ft_map.begin(); it != ft_map.end(); ++it)
		ft_res.push_back(it->first);

	// BELOW CODES MUST MAKE SEGFAULT.	
	// // test 3. in empty case 
	// std_map.clear();
	// ft_map.clear();
	// std_map.erase(std_map.end());
	// ft_map.erase(ft_map.end());
	// std_res.push_back(std_map.size());
	// ft_res.push_back(ft_map.size());
	// // test 4. in empty case, invalid iterator
	// std_map.erase(it);
	// ft_map.erase(it2);
	// std_res.push_back(std_map.size());
	// ft_res.push_back(ft_map.size());
	check_result("erase(pos)", std_time, ft_time, std_res, ft_res);
}

static void test_swap()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	// prepare
	for (int i = 0; i < TEST_SIZE; ++i)
		std_map.insert(std::make_pair(i, i));
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_map.insert(ft::make_pair(i, i));

	S_M std_tmp;
	F_M ft_tmp;
	start = clock();
	std_map.swap(std_tmp);
	end = clock();
	std_time = end - start;

	start = clock();
	ft_map.swap(ft_tmp);
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_map.size());
	for (S_MI it = std_map.begin(); it != std_map.end(); ++it)
		std_res.push_back(it->first);
	ft_res.push_back(ft_map.size());
	for (F_MI it = ft_map.begin(); it != ft_map.end(); ++it)
		ft_res.push_back(it->first);

	std_res.push_back(std_tmp.size());
	for (S_MI it = std_tmp.begin(); it != std_tmp.end(); ++it)
		std_res.push_back(it->first);
	ft_res.push_back(ft_tmp.size());
	for (F_MI it = ft_tmp.begin(); it != ft_tmp.end(); ++it)
		ft_res.push_back(it->first);
	check_result("swap()", std_time, ft_time, std_res, ft_res);
}

static void test_count()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	// test 1. in empty case
	std_res.push_back(std_map.count(-1));
	ft_res.push_back(ft_map.count(-1));
	
	// prepare
	for (int i = 0; i < TEST_SIZE; ++i)
		std_map.insert(std::make_pair(i, i));
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_map.insert(ft::make_pair(i, i));

	// test 2. exist
	start = clock();
	std_res.push_back(std_map.count(1));
	end = clock();
	std_time = end - start;
	std_res.push_back(std_map.count(-1));
	// test 3. not exist
	start = clock();
	ft_res.push_back(ft_map.count(1));
	end = clock();
	ft_time = end - start;
	ft_res.push_back(ft_map.count(-1));
	check_result("count()", std_time, ft_time, std_res, ft_res);
}

static void test_find()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	// test 1. find in empty case
	std_res.push_back(std_map.find(1) == std_map.end());
	ft_res.push_back(ft_map.find(1) == ft_map.end());

	// test 2. find in exist
	for (int i = 0; i < TEST_SIZE; ++i)
		std_map.insert(std::make_pair(i, i));
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_map.insert(ft::make_pair(i, i));
	start = clock();
	for (int i = 0; i < TEST_SIZE; ++i)
		std_res.push_back(std_map.find(i)->first);
	end = clock();
	std_time = end - start;
	
	start = clock();
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_res.push_back(ft_map.find(i)->first);
	end = clock();
	ft_time = end - start;

	// test 3. not empty but not exist
	std_res.push_back(std_map.find(-1) == std_map.end());
	ft_res.push_back(ft_map.find(-1) == ft_map.end());

	check_result("find())", std_time, ft_time, std_res, ft_res);
}

static void test_equal_range()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	std::pair<S_MI, S_MI> std_pair;
	ft::pair<F_MI, F_MI> ft_pair;
	std_pair = std_map.equal_range(3);
	ft_pair = ft_map.equal_range(3);
	std_res.push_back(std_pair.first == std_map.end());
	ft_res.push_back(ft_pair.first == ft_map.end());
	std_res.push_back(std_pair.second == std_map.end());
	ft_res.push_back(ft_pair.second == ft_map.end());
	
	// preapare
	for (int i = 0; i < TEST_SIZE; ++i)
		std_map.insert(std::make_pair(i, i));
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_map.insert(ft::make_pair(i, i));
	
	start = clock();
	std_pair = std_map.equal_range(3);
	end = clock();
	std_time = end - start;

	start = clock();
	ft_pair = ft_map.equal_range(3);
	end = clock();
	ft_time = end - start;
	
	std_res.push_back(std_pair.first->first);
	std_res.push_back(std_pair.second->first);
	ft_res.push_back(ft_pair.first->first);
	ft_res.push_back(ft_pair.second->first);

	check_result("equal_range()", std_time, ft_time, std_res, ft_res);
}

static void test_lower_bound()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	S_MI std_it;
	F_MI ft_it;
	// check in empty 
	std_it = std_map.lower_bound(3);
	ft_it = ft_map.lower_bound(3);
	std_res.push_back(std_it == std_map.end());
	ft_res.push_back(ft_it == ft_map.end());
	std_res.push_back(std_it == std_map.end());
	ft_res.push_back(ft_it == ft_map.end());
	
	// preapare
	for (int i = 0; i < TEST_SIZE; ++i)
		std_map.insert(std::make_pair(i, i));
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_map.insert(ft::make_pair(i, i));
	
	start = clock();
	std_it = std_map.lower_bound(3);
	end = clock();
	std_time = end - start;

	start = clock();
	ft_it = ft_map.lower_bound(3);
	end = clock();
	ft_time = end - start;
	
	std_res.push_back(std_it->first);
	std_res.push_back(std_it->first);
	ft_res.push_back(ft_it->first);
	ft_res.push_back(ft_it->first);

	check_result("lower_bound()", std_time, ft_time, std_res, ft_res);
}
static void test_upper_bound()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map;
	F_M ft_map;

	S_MI std_it;
	F_MI ft_it;
	// check in empty 
	std_it = std_map.upper_bound(3);
	ft_it = ft_map.upper_bound(3);
	std_res.push_back(std_it == std_map.end());
	ft_res.push_back(ft_it == ft_map.end());
	std_res.push_back(std_it == std_map.end());
	ft_res.push_back(ft_it == ft_map.end());
	
	// preapare
	for (int i = 0; i < TEST_SIZE; ++i)
		std_map.insert(std::make_pair(i, i));
	for (int i = 0; i < TEST_SIZE; ++i)
		ft_map.insert(ft::make_pair(i, i));
	
	start = clock();
	std_it = std_map.upper_bound(3);
	end = clock();
	std_time = end - start;

	start = clock();
	ft_it = ft_map.upper_bound(3);
	end = clock();
	ft_time = end - start;
	
	std_res.push_back(std_it->first);
	std_res.push_back(std_it->first);
	ft_res.push_back(ft_it->first);
	ft_res.push_back(ft_it->first);

	check_result("upper_bound()", std_time, ft_time, std_res, ft_res);
}

// static void test_key_comp()
// {
// 	clock_t start, end;
// 	int std_time, ft_time;
// 	S_V std_res, ft_res;
// 	S_M std_map;
// 	F_M ft_map;

// 	check_result("constructor(iterator)", std_time, ft_time, std_res, ft_res);
// }
// static void test_value_comp()
// {
// 	clock_t start, end;
// 	int std_time, ft_time;
// 	S_V std_res, ft_res;
// 	S_M std_map;
// 	F_M ft_map;

// 	check_result("constructor(iterator)", std_time, ft_time, std_res, ft_res);
// }
static void test_operator_compare()
{
	// clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_M std_map, std_tmp;
	F_M ft_map, ft_tmp;

	std_map.insert(std::make_pair(1, 1));
	std_tmp.insert(std::make_pair(2, 1));
	ft_map.insert(ft::make_pair(1, 1));
	ft_tmp.insert(ft::make_pair(2, 1));
	
	std_time = 0;
	ft_time = 0;

	std_res.push_back(std_map == std_tmp);
	std_res.push_back(std_map == std_map);
	std_res.push_back(std_map != std_tmp);
	std_res.push_back(std_map != std_map);
	std_res.push_back(std_map != std_tmp);
	std_res.push_back(std_map > std_tmp);
	std_res.push_back(std_map >= std_tmp);
	std_res.push_back(std_map < std_tmp);
	std_res.push_back(std_map <= std_tmp);

	ft_res.push_back(ft_map == ft_tmp);
	ft_res.push_back(ft_map == ft_map);
	ft_res.push_back(ft_map != ft_tmp);
	ft_res.push_back(ft_map != ft_map);
	ft_res.push_back(ft_map != ft_tmp);
	ft_res.push_back(ft_map > ft_tmp);
	ft_res.push_back(ft_map >= ft_tmp);
	ft_res.push_back(ft_map < ft_tmp);
	ft_res.push_back(ft_map <= ft_tmp);

	check_result("operator(compare)", std_time, ft_time, std_res, ft_res);
}

void test_map()
{
	print_header("MAP");
	test_construct();
	test_assign_operator();
	test_at();
	test_operator_access();
	test_iterator();
	test_empty();
	test_size();
	test_max_size(); // this can not equal with std::map, because, std::map uses allocator_traits
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