#include <algorithm>
#include <functional>
#include <iostream>
#include "ft_pair.hpp"
#include "map.hpp"
#include <map>
#include <chrono>
using namespace std::chrono;
using namespace std;

template <class T, class V, class C>
void fillMap(std::map<T, V, C> &mp) {
	mp.insert(std::make_pair(16, 3));
	mp.insert(std::make_pair(8, 3));
	mp.insert(std::make_pair(23, 3));
	mp.insert(std::make_pair(7, 3));
	mp.insert(std::make_pair(19, 3));
	mp.insert(std::make_pair(29, 3));
	mp.insert(std::make_pair(41, 3));
	mp.insert(std::make_pair(4, 3));
	mp.insert(std::make_pair(11, 3));
}

template <class T, class V, class C>
void fillMap(ft::map<T, V, C> &mp) {
	mp.insert(ft::make_pair(16, 3));
	mp.insert(ft::make_pair(8, 3));
	mp.insert(ft::make_pair(23, 3));
	mp.insert(ft::make_pair(7, 3));
	mp.insert(ft::make_pair(19, 3));
	mp.insert(ft::make_pair(29, 3));
	mp.insert(ft::make_pair(41, 3));
	mp.insert(ft::make_pair(4, 3));
	mp.insert(ft::make_pair(11, 3));
}

template <class T, class V>
std::vector<int>    iterators_test(std::map<T, V> mp) {
    std::vector<int> v;
    std::map<T, V> mpp;
    fillMap(mpp);
	std::cout <<"STD START" << std::endl;
    for (typename std::map<T, V>::iterator it = mpp.begin(); it != mpp.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mpp.end(); it != mpp.begin(); it--) { v.push_back(it->first); }
    std::map<int, int> mp0;
    std::map<int, int>::iterator ii = mp0.insert(std::make_pair(3, 3)).first;
    ii++;
    v.push_back((--ii)->first);
    for (int i = 0, j = 10; i < 5; ++i, ++j)
        mp.insert(std::make_pair(i, j));
    typename std::map<T, V>::iterator it = mp.begin();
    typename std::map<T, V>::iterator it2 = mp.end();
    v.push_back(it->first);
    it++;
    it++;
    it++;
    it++;
    v.push_back(it->first);
    it++;
    it--;
    v.push_back(it->first);
    it2--;
    v.push_back(it2->first);
    v.push_back(it2 == it);
    v.push_back((--it2)->first);
    v.push_back((it2--)->first);
    v.push_back((it2++)->first);
    v.push_back((++it2)->first);

	std::cout <<"STD RESULT" << std::endl;
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
    return v;
}

template <class T, class V>
std::vector<int> iterators_test(ft::map<T, V> mp) {
    std::vector<int> v;
    ft::map<T, V> mpp;
	std::cout <<"FT START" << std::endl;
    fillMap(mpp);
	std::cout << ((mpp.isRbTree()) ? "MPP IS RB TREE\n" : "IS NOT RB TREE\n");

    for (typename ft::map<T, V>::iterator it = mpp.begin(); it != mpp.end(); it++) { std::cout << it->first << std::endl; }
	std::cout <<"FT REVERSE" << std::endl;
    for (typename ft::map<T, V>::iterator it = --mpp.end(); it != mpp.begin(); --it)
	{
		std::cout << it->first << std::endl;
		v.push_back(it->first);
	}
	std::cout <<"FT REVERSE DONE" << std::endl;
    ft::map<int, int> mp0;
    ft::map<int, int>::iterator ii = mp0.insert(ft::make_pair(3, 3)).first;
    ii++;
    v.push_back((--ii)->first);
    for (int i = 0, j = 10; i < 5; ++i, ++j)
        mp.insert(ft::make_pair(i, j));
    typename ft::map<T, V>::iterator it = mp.begin();
    typename ft::map<T, V>::iterator it2 = mp.end();
    v.push_back(it->first);
    it++;
    it++;
    it++;
    it++;
    v.push_back(it->first);
    it++;
    it--;
    v.push_back(it->first);
    it2--;
    v.push_back(it2->first);
    v.push_back(it2 == it);
    v.push_back((--it2)->first);
    v.push_back((it2--)->first);
    v.push_back((it2++)->first);
    v.push_back((++it2)->first);
	std::cout <<"FT RESULT" << std::endl;
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
    return v;
}


void mapTest()
{
	std::map<int, int> std_map;
	ft::map<int, int> ft_map;
	ft::map<int, int> ft_map2;

	std::cout << "test insert\n";
	auto start = high_resolution_clock::now();
	for (int i = 0; i < 10 * 1000 ; ++i)
	{
		std_map.insert(std::pair<int, int> (i, i));
		// std::cout << "insert " << i << "," << i + 1 << std::endl;
	}
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	std::cout << "STD TIME : " <<  duration.count()  << endl;
	start = high_resolution_clock::now();
	for (int i = 0; i < 10 * 1000; ++i)
	{
		ft_map.insert(ft::make_pair<int, int>(i, i));
		// std::cout << "insert " << i << "," << i + 1 << std::endl;
	}
	end = high_resolution_clock::now();
	std::cout << "FT TIME : " <<  duration.count()  << endl;

	std::cout << "insertion result\n";
	for (auto it = ft_map.begin(); it != ft_map.end(); ++it)
	{
		// std::cout << it->first << ", " << it->second << std::endl;
	}
	std::cout << "test iterating\n";
	int i = 0;
	for (ft::map<int, int>::const_iterator it = ft_map.begin(); it != ft_map.end(); ++it)
	{
		std::cout << ++i << " : " << it->first << ", " << it->second << " : " << it.mCurrent << std::endl;
	}
	// std::cout << "test operator=\n";
	// ft_map2 = ft_map;
	// std::cout << "test clear()\n";
	// std_map.clear();
	// ft_map.clear();
	// std::cout << "test insert (hint)\n";
	// for (int i = 0; i < 10 ; ++i)
	// {
	// 	std_map.insert(std_map.find(1), std::pair<int, int> (i, i + 1));
	// 	ft_map.insert(ft_map.find(1), ft::pair<int, int> (i, i + 1));
	// 	std::cout << "insert (hint) " << i << "," << i + 1 << std::endl;
	// }
	// std::cout << "test operator[]\n";
	// for (int i = 0; i < 10 ; ++i)
	// {
	// 	int ft = ft_map[i];
	// 	int std = std_map[i];
	// 	std::cout << ft << ", " << std << std::endl;
	// }
	// std_map.clear();
	// ft_map.clear();
	// std::cout << "test insert (iterator)\n";
	// for (int i = 0; i < 10 ; ++i)
	// {
	// 	std_map.insert(std_map.find(1), std::pair<int, int> (i, i + 1));
	// 	ft_map.insert(ft_map.find(1), ft::pair<int, int> (i, i + 1));
	// 	std::cout << "insert (hint) " << i << "," << i + 1 << std::endl;
	// }
	
	// std::cout << "test operator[]\n";
	// for (int i = 0; i < 10 ; ++i)
	// {
	// 	int ft = ft_map[i];
	// 	int std = std_map[i];
	// 	std::cout << ft << ", " << std << std::endl;
	// }
	// std::cout << "test erase\n";
	// for (int i = 0; i < 10; ++i)
	// {
	// 	ft_map.erase(ft_map.find(i));
	// 	try
	// 	{
	// 		ft_map.at(i);
	// 		std::cout << "NOT ERASED : " << i << endl;
	// 	}
	// 	catch (...)
	// 	{
	// 		std::cout << "ERASED\n";
	// 		for (ft::map<int,int>::iterator it = ft_map.begin(); it != ft_map.end(); ++it)
	// 		{
	// 			std::cout << it->first << ", " << it->second << std::endl; 
	// 		}
	// 		std::cout << std::endl;
	// 	}
	// }
}
#define _ratio 10000
#define _map ft::map
#define _make_pair ft::make_pair

template <class T, class V>
std::vector<int> comparator_test(std::map<T, V> mp) {

    std::vector<int> v;
    fillMap(mp);
    for (typename std::map<T, V>::iterator it = mp.begin(); it != mp.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mp.end(); it != mp.begin(); it--) { v.push_back(it->first); }
    std::map<int, int, std::greater<int> > mp1;
    fillMap(mp1);
    v.push_back(mp1.begin()->first);
    mp1.erase(41);
    v.push_back(mp1.begin()->first);
    mp1.erase(29);
    v.push_back(mp1.begin()->first);
    std::map<int, int, std::greater<int> > mp2;
    mp2.insert(std::make_pair(3, 3));
    v.push_back(mp2.begin()->first);
    mp2.erase(3);
    if (mp2.begin() == mp2.end())
        v.push_back(1);
    std::map<int, int, std::plus<int> > mp3;
    fillMap(mp3);
    for (typename std::map<T, V>::iterator it = mp3.begin(); it != mp3.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mp3.end(); it != mp3.begin(); it--) { v.push_back(it->first); }
    std::map<int, int, std::minus<int> > mp4;
    fillMap(mp4);
    for (typename std::map<T, V>::iterator it = mp4.begin(); it != mp4.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mp4.end(); it != mp4.begin(); it--) { v.push_back(it->first); }
    std::map<int, int, std::greater_equal<int> > mp5;
    fillMap(mp5);
    for (typename std::map<T, V>::iterator it = mp5.begin(); it != mp5.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mp5.end(); it != mp5.begin(); it--) { v.push_back(it->first); }
    std::map<int, int, std::multiplies<int> > mp6;
    fillMap(mp6);
    for (typename std::map<T, V>::iterator it = mp6.begin(); it != mp6.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mp6.end(); it != mp6.begin(); it--) { v.push_back(it->first); }
    std::map<int, int, std::bit_xor<int> > mp7;
    fillMap(mp7);
    for (typename std::map<T, V>::iterator it = mp7.begin(); it != mp7.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mp7.end(); it != mp7.begin(); it--) { v.push_back(it->first); }
    std::map<int, int, std::logical_and<int> > mp8;
    fillMap(mp8);
    for (typename std::map<T, V>::iterator it = mp8.begin(); it != mp8.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mp8.end(); it != mp8.begin(); it--) { v.push_back(it->first); }
    v.push_back(mp1.size());
    return v;
}

template <class T, class V>
std::vector<int> comparator_test(_map<T, V> mp) {
    std::vector<int> v;
    fillMap(mp);
    for (typename _map<T, V>::iterator it = mp.begin(); it != mp.end(); it++) { v.push_back(it->first); }
    for (typename _map<T, V>::iterator it = --mp.end(); it != mp.begin(); it--) { v.push_back(it->first); }
    _map<int, int, std::greater<int> > mp1;
    fillMap(mp1);
    v.push_back(mp1.begin()->first);
    mp1.erase(41);
    v.push_back(mp1.begin()->first);
    mp1.erase(29);
    v.push_back(mp1.begin()->first);
    _map<int, int, std::greater<int> > mp2;
    mp2.insert(_make_pair(3, 3));
    v.push_back(mp2.begin()->first);
    // mp2.erase(3);
    if (mp2.begin() == mp2.end())
        v.push_back(1);
    _map<int, int, std::plus<int> > mp3;
    fillMap(mp3);
    for (typename _map<T, V>::iterator it = mp3.begin(); it != mp3.end(); it++) { v.push_back(it->first); }
    for (typename _map<T, V>::iterator it = --mp3.end(); it != mp3.begin(); it--) { v.push_back(it->first); }
    _map<int, int, std::minus<int> > mp4;
    fillMap(mp4);
    for (typename _map<T, V>::iterator it = mp4.begin(); it != mp4.end(); it++) { v.push_back(it->first); }
    for (typename _map<T, V>::iterator it = --mp4.end(); it != mp4.begin(); it--) { v.push_back(it->first); }
    _map<int, int, std::greater_equal<int> > mp5;
    fillMap(mp5);
    for (typename _map<T, V>::iterator it = mp5.begin(); it != mp5.end(); it++) { v.push_back(it->first); }
    for (typename _map<T, V>::iterator it = --mp5.end(); it != mp5.begin(); it--) { v.push_back(it->first); }
    _map<int, int, std::multiplies<int> > mp6;
    fillMap(mp6);
    for (typename _map<T, V>::iterator it = mp6.begin(); it != mp6.end(); it++) { v.push_back(it->first); }
    for (typename _map<T, V>::iterator it = --mp6.end(); it != mp6.begin(); it--) { v.push_back(it->first); }
    _map<int, int, std::bit_xor<int> > mp7;
    fillMap(mp7);
    for (typename _map<T, V>::iterator it = mp7.begin(); it != mp7.end(); it++) { v.push_back(it->first); }
    for (typename _map<T, V>::iterator it = --mp7.end(); it != mp7.begin(); it--) { v.push_back(it->first); }
    std::map<int, int, std::logical_and<int> > mp8;
    fillMap(mp8);
    for (typename std::map<T, V>::iterator it = mp8.begin(); it != mp8.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mp8.end(); it != mp8.begin(); it--) { v.push_back(it->first); }
    v.push_back(mp1.size());

    return v;
}


template <class T, class V>
std::vector<int> erase_test_3(std::map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j)
        mp.insert(std::make_pair(i, j));

    mp.erase(mp.begin(), --mp.end());
    v.push_back(mp.begin()->first);
    return v;
}

template <class T, class V>
std::vector<int> erase_test_3(ft::map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j)
        mp.insert(ft::make_pair(i, j));

    mp.erase(mp.begin(), --mp.end());
    v.push_back(mp.begin()->first);
    return v;
}

template <class T, class V>
std::vector<int> copy_constructor_test(ft::map<T, V> mp) {

    std::vector<int> v;

    for (int i = 0, j = 10; i < 30 * _ratio; ++i, ++j) {
        mp.insert(ft::make_pair(i, j));
    }
    ft::map<int, int> mp2 = mp;
    ft::map<int, int>::iterator it = mp2.begin();
    for (int i = 0; i < 30 * _ratio; ++i, it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }
    return v;
}

template <class T, class V>
std::vector<int> assign_overload_test(ft::map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 10; i < 20 * _ratio; ++i, ++j)
        mp.insert(ft::make_pair(i, j));
    ft::map<T, V> mp2;
    for (int i = 20 * _ratio, j = 200010; i < 40 * _ratio; ++i, ++j)
        mp2.insert(ft::make_pair(i, j));
    mp2 = mp;
    typename ft::map<T, V>::iterator it = mp2.begin();
    for (; it != mp2.end(); it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }
    v.push_back(mp2.size());
    return v;
}


template <class T, class V>
    std::vector<int> size_test(std::map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 0; i < 100 * _ratio; ++i, ++j)
        mp.insert(std::make_pair(i, j));
    v.push_back(mp.size());
    for (int i = 0; i < 43 * _ratio; ++i)
        mp.erase(i);
    v.push_back(mp.size());
    return v;
}

template <class T, class V>
	std::vector<int> size_test(ft::map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 0; i < 100 * _ratio; ++i, ++j)
        mp.insert(ft::make_pair(i, j));
    v.push_back(mp.size());
    for (int i = 0; i < 43 * _ratio; ++i)
        mp.erase(i);
    v.push_back(mp.size());
    return v;
}

#include <cstdlib>

void lk()
{
	system("leaks container");
}
int main()
{
	atexit(lk);
	// mapTest();
	// std::map<int, int> m1;
    std::map<int, int, std::plus<int> > m1;
	ft::map<int, int, std::plus<int> > m2;
    for (int i = 0; i < 10; ++i)
    {
        int key = rand() % 100;
        int value = rand() % 1000;
        m1.insert(std::make_pair(key, value));
        m2.insert(_make_pair(key, value));
        
        std::cout << key << ", " << value << std::endl;
    }
    std::cout << "FT : SIZE : " << m2.size() << endl ;
    for (auto it = m2.begin(); it != m2.end(); ++it)
        std::cout << it->first << ", " << it->second << std::endl;
    std::cout << "STD : SIZE : " << m1.size() << endl;
    for (auto it = m1.begin(); it != m1.end(); ++it)
        std::cout << it->first << ", " << it->second << std::endl;

    // insertion -> success
    // but, some node is lost
}
