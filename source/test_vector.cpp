#include "test.hpp"
#include "vector.hpp"

#define S_VI S_V::iterator
#define F_VI F_V::iterator

#define TEST_VEC_SIZE 50 * 100000

static void test_construct_default()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	
	// test 1
	start = clock();
	S_V std_vec;
	end = clock();
	std_time = end - start;
	start = clock();
	F_V ft_vec;
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	check_result("constructor(default)", std_time, ft_time, std_res, ft_res);
}

static void test_construct_size()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	
	// test 1
	start = clock();
	S_V std_vec(TEST_VEC_SIZE, 1);
	end = clock();
	std_time = end - start;
	start = clock();
	F_V ft_vec(TEST_VEC_SIZE, 1);
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}
	check_result("constructor(size, val)", std_time, ft_time, std_res, ft_res);
}

static void test_construct_iter()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_tmp(TEST_VEC_SIZE, 1);

	// test 1
	start = clock();
	S_V std_vec(std_tmp.begin(), std_tmp.end());
	end = clock();
	std_time = end - start;
	start = clock();
	F_V ft_vec(std_tmp.begin(), std_tmp.end());
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());

	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}
	check_result("constructor(iter)", std_time, ft_time, std_res, ft_res);
}

static void test_assign_operator()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_tmp(TEST_VEC_SIZE, 1);
	F_V ft_tmp(TEST_VEC_SIZE, 1);

	// test 1
	start = clock();
	S_V std_vec = std_tmp;
	end = clock();
	std_time = end - start;

	start = clock();
	F_V ft_vec = ft_tmp;
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());

	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}
	check_result("operator=", std_time, ft_time, std_res, ft_res);
}

static void test_iterator()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE, 1);
	F_V ft_vec(TEST_VEC_SIZE, 1);

	// test 1
	start = clock();
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it) { std_res.push_back(*it); }
	for (S_VI it = --std_vec.end(); it != std_vec.begin(); --it) { std_res.push_back(*it); }
	for (S_V::const_iterator it = std_vec.begin(); it != std_vec.end(); ++it) { std_res.push_back(*it); }
	for (S_V::const_iterator it = --std_vec.end(); it != std_vec.begin(); --it) { std_res.push_back(*it); }
	end = clock();
	std_time = end - start;
	start = clock();
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it) { ft_res.push_back(*it); }
	for (F_VI it = --ft_vec.end(); it != ft_vec.begin(); --it) { ft_res.push_back(*it); }
	for (F_V::const_iterator it = ft_vec.begin(); it != ft_vec.end(); ++it) { ft_res.push_back(*it); }
	for (F_V::const_iterator it = --ft_vec.end(); it != ft_vec.begin(); --it) { ft_res.push_back(*it); }
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());

	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}
	check_result("iterator", std_time, ft_time, std_res, ft_res);
}

static void test_size()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE, 1);
	F_V ft_vec(TEST_VEC_SIZE, 1);

	// test 1. with elem
	int std_, ft_;
	start = clock();
	std_ = std_vec.size();
	end = clock();
	std_time = end - start;
	start = clock();
	ft_ = ft_vec.size();
	end = clock();
	ft_time = end - start;
	std_res.push_back(std_);
	ft_res.push_back(ft_);

	// test 2. with no elem;
	S_V std_tmp;
	F_V ft_tmp;
	std_res.push_back(std_tmp.size());
	ft_res.push_back(ft_tmp.size());

	check_result("size()", std_time, ft_time, std_res, ft_res);
}

static void test_empty()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE, 1);
	F_V ft_vec(TEST_VEC_SIZE, 1);

	// test 1. with elem
	int std_, ft_;
	start = clock();
	std_ = std_vec.empty();
	end = clock();
	std_time = end - start;
	start = clock();
	ft_ = ft_vec.empty();
	end = clock();
	ft_time = end - start;
	std_res.push_back(std_);
	ft_res.push_back(ft_);

	// test 2. with no elem;
	S_V std_tmp;
	F_V ft_tmp;
	std_res.push_back(std_tmp.empty());
	ft_res.push_back(ft_tmp.empty());

	check_result("empty()", std_time, ft_time, std_res, ft_res);
}

static void test_clear()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE, 1);
	F_V ft_vec(TEST_VEC_SIZE, 1);

	// test 1. with elem
	start = clock();
	std_vec.clear();
	end = clock();
	std_time = end - start;
	start = clock();
	ft_vec.clear();
	end = clock();
	ft_time = end - start;
	std_res.push_back(std_vec.size());
	ft_res.push_back(ft_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.capacity());

	// test 2. with no elem;
	S_V std_tmp;
	F_V ft_tmp;
	std_tmp.clear();
	ft_tmp.clear();
	std_res.push_back(std_vec.size());
	ft_res.push_back(ft_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.capacity());

	check_result("clear()", std_time, ft_time, std_res, ft_res);
}

static void test_max_size()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE, 1);
	F_V ft_vec(TEST_VEC_SIZE, 1);

	// test 1. with elem
	int std_, ft_;
	start = clock();
	std_ = std_vec.max_size() ? 1 : 0;
	end = clock();
	std_time = end - start;
	start = clock();
	ft_ = ft_vec.max_size() ? 1 : 0;
	end = clock();
	ft_time = end - start;
	std_res.push_back(std_);
	ft_res.push_back(ft_);

	// test 2. with no elem;
	S_V std_tmp;
	F_V ft_tmp;
	std_res.push_back(std_tmp.max_size() ? 1 : 0);
	ft_res.push_back(ft_tmp.max_size() ? 1 : 0);

	check_result("max_size()", std_time, ft_time, std_res, ft_res);
}

static void test_resize()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE, 1);
	F_V ft_vec(TEST_VEC_SIZE, 1);

	// test 1. with elem, larger than capa
	start = clock();
	std_vec.resize(std_vec.capacity() * 3);
	end = clock();
	std_time = end - start;
	start = clock();
	ft_vec.resize(ft_vec.capacity() * 3);
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}

	// test 2. with elem, over capa
	std_vec.resize(std_vec.capacity() * 3);
	ft_vec.resize(ft_vec.capacity() * 3);

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}

	// test 3. no elem, inside capa
	std_vec.clear();
	ft_vec.clear();
	std_vec.resize(TEST_VEC_SIZE);
	ft_vec.resize(TEST_VEC_SIZE);

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}

	// test 4. with elem, inside capa;
	std_vec.resize(TEST_VEC_SIZE);
	ft_vec.resize(TEST_VEC_SIZE);

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}

	check_result("resize()", std_time, ft_time, std_res, ft_res);
}

static void test_reserve()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE, 1);
	F_V ft_vec(TEST_VEC_SIZE, 1);

	// test 1. with elem, larger than capa
	start = clock();
	std_vec.reserve(std_vec.capacity() * 3);
	end = clock();
	std_time = end - start;
	start = clock();
	ft_vec.reserve(ft_vec.capacity() * 3);
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}

	// test 2. with elem, over capa
	std_vec.reserve(std_vec.capacity() * 3);
	ft_vec.reserve(ft_vec.capacity() * 3);

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}

	// test 3. no elem, inside capa
	std_vec.clear();
	ft_vec.clear();
	std_vec.reserve(TEST_VEC_SIZE);
	ft_vec.reserve(TEST_VEC_SIZE);

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}

	// test 4. with elem, inside capa;
	std_vec.reserve(TEST_VEC_SIZE);
	ft_vec.reserve(TEST_VEC_SIZE);

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}

	check_result("reserve()", std_time, ft_time, std_res, ft_res);
}


static void test_at()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE, 1);
	F_V ft_vec(TEST_VEC_SIZE, 1);

	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(std_vec.at(*it));
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(ft_vec.at(*it));
	}
	// test throw
	try { std_vec.at(-1); } catch (...) { std_res.push_back(true);}
	try { ft_vec.at(-1); } catch (...) { ft_res.push_back(true);}
	// check time.
	start = clock();
	std_vec.at(1000);
	end = clock();
	std_time = end - start;

	start = clock();
	ft_vec.at(1000);
	end = clock();
	ft_time = end - start;

	check_result("at()", std_time, ft_time, std_res, ft_res);
}

static void test_operator_access()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE, 1);
	F_V ft_vec(TEST_VEC_SIZE, 1);

	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(std_vec[(*it)]);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(ft_vec[(*it)]);
	}
	// check not exist value // SEGFAULT
	// std_res.push_back(std_vec[-1]);
	// ft_res.push_back(ft_vec[-1]);

	// check time.
	start = clock();
	int x = std_vec[1000];
	end = clock();
	std_time = end - start;

	start = clock();
	int y = ft_vec[1000];
	end = clock();
	(void) x; (void) y;
	ft_time = end - start;

	check_result("operator[]", std_time, ft_time, std_res, ft_res);
}

static void test_front()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE, 1);
	F_V ft_vec(TEST_VEC_SIZE, 1);

	// check time.
	start = clock();
	int x = std_vec.front();
	end = clock();
	std_time = end - start;

	start = clock();
	int y = ft_vec.front();
	end = clock();
	ft_time = end - start;

	std_res.push_back(x);
	ft_res.push_back(y);
	
	// in empty case it will be make SEGFAULT
	check_result("front()", std_time, ft_time, std_res, ft_res);
}

static void test_back()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE, 1);
	F_V ft_vec(TEST_VEC_SIZE, 1);

	// check time.
	start = clock();
	int x = std_vec.back();
	end = clock();
	std_time = end - start;

	start = clock();
	int y = ft_vec.back();
	end = clock();
	ft_time = end - start;

	std_res.push_back(x);
	ft_res.push_back(y);
	
	// in empty case it will be make SEGFAULT
	check_result("back()", std_time, ft_time, std_res, ft_res);
}

static void test_data()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE, 1);
	F_V ft_vec(TEST_VEC_SIZE, 1);

	// check time.
	start = clock();
	int* x = std_vec.data();
	end = clock();
	std_time = end - start;

	start = clock();
	int* y = ft_vec.data();
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (unsigned int i = 0; i < std_vec.size(); ++i)
	{
		std_res.push_back(x[i]);
	}
	for (unsigned int i = 0; i < ft_vec.size(); ++i)
	{
		ft_res.push_back(y[i]);
	}
	// in empty case it will be make SEGFAULT
	check_result("data()", std_time, ft_time, std_res, ft_res);
}


static void test_assign_iter()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE, 1);
	F_V ft_vec(TEST_VEC_SIZE, 1);

	S_V tmp(100000, 2);

	// test 1. larger than capa
	start = clock();
	std_vec.assign(tmp.begin(), tmp.end());
	end = clock();
	std_time = end - start;
	start = clock();
	ft_vec.assign(tmp.begin(), tmp.end());
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}
	// test 2. less than capa
	S_V s(1);
	F_V f(1);
	
	std_vec.swap(s);
	ft_vec.swap(f);
	std_vec.reserve(TEST_SIZE);
	ft_vec.reserve(TEST_SIZE);

	std_vec.assign(tmp.begin(), tmp.end());
	ft_vec.assign(tmp.begin(), tmp.end());

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}

	// test 3. empty case
	S_V s2;
	F_V f2;
	std_vec.swap(s2);
	ft_vec.swap(f2);

	std_vec.assign(tmp.begin(), tmp.end());
	ft_vec.assign(tmp.begin(), tmp.end());

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}
	check_result("assign(iter)", std_time, ft_time, std_res, ft_res);
}

static void test_assign_size()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE, 1);
	F_V ft_vec(TEST_VEC_SIZE, 1);


	// test 1. larger than capa
	start = clock();
	std_vec.assign(TEST_VEC_SIZE, 1);
	end = clock();
	std_time = end - start;
	start = clock();
	ft_vec.assign(TEST_VEC_SIZE, 1);
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}
	// test 2. less than capa
	S_V s(1);
	F_V f(1);
	
	std_vec.swap(s);
	ft_vec.swap(f);
	std_vec.reserve(TEST_SIZE);
	ft_vec.reserve(TEST_SIZE);

	std_vec.assign(TEST_VEC_SIZE, 1);
	ft_vec.assign(TEST_VEC_SIZE, 1);

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}

	// test 3. empty case
	S_V s2;
	F_V f2;
	std_vec.swap(s2);
	ft_vec.swap(f2);

	std_vec.assign(TEST_VEC_SIZE, 1);
	ft_vec.assign(TEST_VEC_SIZE, 1);

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}
	check_result("assign(size, val)", std_time, ft_time, std_res, ft_res);
}

static void test_push_back()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(0);
	F_V ft_vec(0);


	// test 1
	start = clock();
	for (int i = 0; i < TEST_VEC_SIZE; ++i)
		std_vec.push_back(i);
	end = clock();
	std_time = end - start;
	start = clock();
	for (int i = 0; i < TEST_VEC_SIZE; ++i)
		ft_vec.push_back(i);
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}

	check_result("push_back()", std_time, ft_time, std_res, ft_res);
}

static void test_pop_back()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE, 1);
	F_V ft_vec(TEST_VEC_SIZE, 1);

	// test 1
	start = clock();
	for (int i = 0; i < TEST_VEC_SIZE; ++i)
	{
		std_res.push_back(std_vec.back());
		std_vec.pop_back();
	}
	end = clock();
	std_time = end - start;
	start = clock();
	for (int i = 0; i < TEST_VEC_SIZE; ++i)
	{
		ft_res.push_back(ft_vec.back());
		ft_vec.pop_back();
	}
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}
	check_result("pop_back()", std_time, ft_time, std_res, ft_res);
}

static void test_erase_pos()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE);
	F_V ft_vec(TEST_VEC_SIZE);

	// test 1
	start = clock();
	for (S_VI it = std_vec.begin(); it != std_vec.begin() + 100; ++it)
	{
		S_VI temp = it++;
		std_vec.erase(temp);
	}
	end = clock();
	std_time = end - start;
	start = clock();
	for (F_VI it = ft_vec.begin(); it != ft_vec.begin() + 100; ++it)
	{
		F_VI temp = it++;
		ft_vec.erase(temp);
	}
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}
	// check it is erased
	std_vec.clear();
	ft_vec.clear();
	std_vec.push_back(1);
	std_vec.push_back(2);
	ft_vec.push_back(1);
	ft_vec.push_back(2);
	std_vec.erase(std_vec.begin());
	ft_vec.erase(ft_vec.begin());
	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	std_res.push_back(std_vec.at(0));
	ft_res.push_back(ft_vec.at(0));
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}

	check_result("erase(pos)", std_time, ft_time, std_res, ft_res);
}

static void test_erase_iter()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE);
	F_V ft_vec(TEST_VEC_SIZE);

	// test 1
	start = clock();
	std_vec.erase(std_vec.begin(), --std_vec.end());
	end = clock();
	std_time = end - start;
	start = clock();
	ft_vec.erase(ft_vec.begin(), --ft_vec.end());
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}
	// check it is erased
	std_vec.clear();
	ft_vec.clear();
	std_vec.push_back(1);
	std_vec.push_back(2);
	ft_vec.push_back(1);
	ft_vec.push_back(2);
	std_vec.erase(std_vec.begin(), ++std_vec.begin());
	ft_vec.erase(ft_vec.begin(), ++ft_vec.begin());
	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	std_res.push_back(std_vec.at(0));
	ft_res.push_back(ft_vec.at(0));
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}

	check_result("erase(iter)", std_time, ft_time, std_res, ft_res);
}

static void test_swap()
{
	clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec(TEST_VEC_SIZE);
	F_V ft_vec(TEST_VEC_SIZE);
	S_V std_tmp(0);
	S_V std_tmp2(TEST_VEC_SIZE, 100);
	F_V ft_tmp(0);
	F_V ft_tmp2(TEST_VEC_SIZE, 100);

	// swap with empty
	start = clock();
	std_vec.swap(std_tmp);
	end = clock();
	std_time = end - start;
	start = clock();
	ft_vec.swap(ft_tmp);
	end = clock();
	ft_time = end - start;

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}
	std_res.push_back(std_tmp.size());
	std_res.push_back(std_tmp.capacity());
	ft_res.push_back(ft_tmp.size());
	ft_res.push_back(ft_tmp.capacity());
	for (S_VI it = std_tmp.begin(); it != std_tmp.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_tmp.begin(); it != ft_tmp.end(); ++it)
	{
		ft_res.push_back(*it);
	}

	// swap with not empty
	std_vec.swap(std_tmp2);
	ft_vec.swap(ft_tmp2);

	std_res.push_back(std_vec.size());
	std_res.push_back(std_vec.capacity());
	ft_res.push_back(ft_vec.size());
	ft_res.push_back(ft_vec.capacity());
	for (S_VI it = std_vec.begin(); it != std_vec.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_vec.begin(); it != ft_vec.end(); ++it)
	{
		ft_res.push_back(*it);
	}
	std_res.push_back(std_tmp2.size());
	std_res.push_back(std_tmp2.capacity());
	ft_res.push_back(ft_tmp2.size());
	ft_res.push_back(ft_tmp2.capacity());
	for (S_VI it = std_tmp2.begin(); it != std_tmp2.end(); ++it)
	{
		std_res.push_back(*it);
	}
	for (F_VI it = ft_tmp2.begin(); it != ft_tmp2.end(); ++it)
	{
		ft_res.push_back(*it);
	}
	check_result("swap()", std_time, ft_time, std_res, ft_res);
}

static void test_operator_compare()
{
	// clock_t start, end;
	int std_time, ft_time;
	S_V std_res, ft_res;
	S_V std_vec, std_tmp;
	F_V ft_vec, ft_tmp;

	std_vec.push_back(1);
	std_tmp.push_back(2);
	ft_vec.push_back(1);
	ft_tmp.push_back(2);
	
	std_time = 0;
	ft_time = 0;

	std_res.push_back(std_vec == std_tmp);
	std_res.push_back(std_vec == std_vec);
	std_res.push_back(std_vec != std_tmp);
	std_res.push_back(std_vec != std_vec);
	std_res.push_back(std_vec != std_tmp);
	std_res.push_back(std_vec > std_tmp);
	std_res.push_back(std_vec >= std_tmp);
	std_res.push_back(std_vec < std_tmp);
	std_res.push_back(std_vec <= std_tmp);

	ft_res.push_back(ft_vec == ft_tmp);
	ft_res.push_back(ft_vec == ft_vec);
	ft_res.push_back(ft_vec != ft_tmp);
	ft_res.push_back(ft_vec != ft_vec);
	ft_res.push_back(ft_vec != ft_tmp);
	ft_res.push_back(ft_vec > ft_tmp);
	ft_res.push_back(ft_vec >= ft_tmp);
	ft_res.push_back(ft_vec < ft_tmp);
	ft_res.push_back(ft_vec <= ft_tmp);

	check_result("operator(compare)", std_time, ft_time, std_res, ft_res);
}

void test_vector()
{
	print_header("VECTOR");
	test_construct_default();
	test_construct_size();
	test_construct_iter();
	test_assign_operator();
	test_iterator();
	test_empty();
	test_size();
	test_max_size(); // this can not equal with std::map, because, std::map uses allocator_traits
	test_clear();
	test_resize();
	test_reserve();
	test_operator_access();
	test_at();
	test_front();
	test_back();
	test_assign_size();
	test_assign_iter();
	test_data();
	test_push_back();
	test_pop_back();
	test_erase_pos();
	test_erase_iter();
	test_swap();
	test_operator_compare();
}