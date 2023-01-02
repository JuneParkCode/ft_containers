#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "array.hpp"
#include <cstddef>
#include <memory>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		/* define easy typename */
		private:
			typedef typename ft::vector<T> vector_t;
		private:
			array<T> mData;
		public:
			/* contructor destructor ... */
			vector();
			explicit vector(size_t size);
			explicit vector(const Allocator& alloc );
			explicit vector(size_t count, 
                			const T& value = T(),
                			const Allocator& alloc = Allocator());
			template< class InputIt >
			vector(InputIt first, InputIt last, 
        							const Allocator& alloc = Allocator() );
			vector(const vector_t& other );
			/* assignment operator */
			vector_t& operator=(const vector_t& v);
			/* allocator */
			Allocator get_allocator();
			/* assign */
			template< class InputIt >
			void assign(InputIt first, InputIt last );
			void assign(size_t count, const T& value);
			/* capacity */
			int		 	size() const;
			bool 		empty() const;
			/* element access */
			T&			at(int size);
			T&			operator[](int size);
			T&			front();
			T&			back();
			T*			data();
			~vector();
	};
}

#endif 
