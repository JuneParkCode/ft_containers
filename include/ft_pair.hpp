#ifndef FT_PAIR_HPP
#define FT_PAIR_HPP

namespace ft
{
	/** pair */
	template <class firstType, class secondType>
	class pair
	{
		public:
			/** member variables */
			firstType			first;
			secondType			second;
			typedef firstType	first_type;
			typedef secondType	second_type;
		public:
			/** constructors  */
			pair() : first(), second() {}
			template<class U, class V>
			pair(const pair<U,V>& pr) 						: first(pr.first), second(pr.second) {}
			pair(const first_type& a, const secondType& b)	: first(a), second(b) {}
	};
	/** compare operators, it uses lexicographical compare */
	template< class T1, class T2 >	bool	operator==(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)	{ return (lhs.first == rhs.first && lhs.second == rhs.second); }
	template< class T1, class T2 >	bool	operator!=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)	{ return (!(lhs == rhs)); }
	template< class T1, class T2 >	bool	operator>=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)	{ return (lhs >= rhs); }
	template< class T1, class T2 >	bool	operator<=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)	{ return (lhs <= rhs); }
	template< class T1, class T2 >	bool	operator>(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)	{ return (lhs > rhs); }
	template< class T1, class T2 >	bool	operator<(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)	{ return (lhs < rhs); }
	/** make pair  */
	template< class first_type, class second_type >	ft::pair<first_type, second_type> make_pair(first_type t, second_type u) { return (ft::pair<first_type, second_type>(t, u)); }
}

#endif 
