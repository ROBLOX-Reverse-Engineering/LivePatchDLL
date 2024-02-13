#pragma once
#include <memory>
#include "Globals.h"

// Credits: https://www.unknowncheats.me/forum/battlefield-2/72875-bf2-std-library-vs-2005-08-and-10-a.html

#ifdef VS2008
namespace old
{
	class string 
	{	
		using Allocator = std::allocator<char>;

	public:
 
		enum
		{	
			_BUF_SIZE = 16 / sizeof (char) < 1 ? 1 : 16 / sizeof(char),
			_ALLOC_MASK = sizeof (char) <= 1 ? 15 : sizeof (char) <= 2 ? 7 : sizeof (char) <= 4 ? 3 : sizeof (char) <= 8 ? 1 : 0,
		};		
						
		string() : _Alval(Allocator::template rebind<char>::other()) 
		{	
			_Tidy();
		}
 
		string(const char* _Ptr) : _Alval(Allocator::template rebind<char>::other()) 
		{	
			_Tidy();
			assign(_Ptr, std::char_traits<char>::length(_Ptr));
		}
 
		~string()
		{	
			_Tidy(true);
		}
 
		const char* c_str() const
		{	
			return (_Myptr());
		}
 
		const char* _Myptr() const
		{	
			return (_BUF_SIZE <= _Myres ? _Bx._Ptr : _Bx._Buf);
		}
 
		void  _Tidy(bool _Built = false, std::allocator_traits<Allocator>::size_type _Newsize = 0)
		{	
			if (!_Built)
			{
			}
			else if (_BUF_SIZE <= _Myres)
			{	
				char* _Ptr = _Bx._Ptr;
 
				if (0 < _Newsize)
					copy(_Bx._Buf, _Ptr, _Newsize);
 
				_Alval.deallocate(_Ptr, _Myres + 1);
			}
 
			_Myres = _BUF_SIZE - 1;
			_Eos(_Newsize);
		}
 
		string& assign(const char* _Ptr, std::allocator_traits<Allocator>::size_type _Count)
		{	
			if (_Grow(_Count))
			{	
				copy((char*)_Myptr(), _Ptr, _Count);
				_Eos(_Count);
			}
 
			return (*this);
		}
 
		bool _Grow(std::allocator_traits<Allocator>::size_type _Newsize, bool _Trim = false)
		{	
			if (max_size() < _Newsize)
			{
				//_Xlength_error("string too long");	
			}
 
			if (_Myres < _Newsize)
			{
				_Copy(_Newsize, _Mysize);	
			}
			else if (_Trim && _Newsize < _BUF_SIZE)
			{
				_Tidy(true, _Newsize < _Mysize ? _Newsize : _Mysize);
			}
			else if (_Newsize == 0)
			{
				_Eos(0);	
			}
 
			return (0 < _Newsize);	
		}
 
		std::allocator_traits<Allocator>::size_type max_size() const
		{	
			return (_AlTraits.max_size(_Alval) <= 1 ? 1 : _AlTraits.max_size(_Alval) - 1);
		}
 
		static char* copy(char* _First1, const char* _First2, size_t _Count)
		{	
			return ((char *)_CSTD memcpy(_First1, _First2, _Count));
		}
 
		void _Copy(std::allocator_traits<Allocator>::size_type _Newsize, std::allocator_traits<Allocator>::size_type _Oldlen)
		{	
			std::allocator_traits<Allocator>::size_type _Newres = _Newsize | _ALLOC_MASK;
 
			if (max_size() < _Newres)
			{
				_Newres = _Newsize;	
			}
			else if (_Newres / 3 < _Myres / 2 && _Myres <= max_size() - _Myres / 2)
			{
				_Newres = _Myres + _Myres / 2;	
			}
 
			char *_Ptr = 0;
 
			_TRY_BEGIN
				_Ptr = _Alval.allocate(_Newres + 1);
			_CATCH_ALL
				_Newres = _Newsize;
				_TRY_BEGIN
					_Ptr = _Alval.allocate(_Newres + 1);
				_CATCH_ALL
				_Tidy(true);	
				_RERAISE;
				_CATCH_END
			_CATCH_END
 
			if (0 < _Oldlen)
				copy(_Ptr, _Myptr(), _Oldlen);	
 
			_Tidy(true);
			_Bx._Ptr = _Ptr;
			_Myres = _Newres;
			_Eos(_Oldlen);
		}
			
		void _Eos(std::allocator_traits<Allocator>::size_type _Newsize)
		{	
			std::char_traits<char>::assign((char)_Myptr()[_Mysize = _Newsize], char());
		}
 
		bool _Inside(const char* _Ptr)
		{	
			if (_Ptr == 0 || _Ptr < _Myptr() || _Myptr() + _Mysize <= _Ptr)
				return false;	
		
			return true;
		}
 
	protected:
 
		std::allocator_traits<Allocator>::template rebind_alloc<char> _Alval;
		std::allocator_traits<Allocator>::template rebind_traits<char> _AlTraits;
 
		union _Bxty
		{	
			char _Buf[_BUF_SIZE];
			char* _Ptr;
		} _Bx;
 
		std::allocator_traits<Allocator>::size_type _Mysize;
		std::allocator_traits<Allocator>::size_type _Myres;
	};
 
	template <class T, class Y>
	struct map
	{
		struct iterator
		{	
			friend struct map;
		
			struct node
			{
			friend struct map;
 
			protected:
				node* _Left;	
				node* _Parent;
				node* _Right;
			public:
				T first;
				Y second;
			protected:
				char _Unknown0;
				char _isHead;
			};
 
		protected:
			node* _Ptr;
		public:
			iterator(node* _Node) : _Ptr(_Node) { }
 
			bool operator == (const iterator& it) { return _Ptr == it._Ptr; }
			bool operator != (const iterator& it) { return _Ptr != it._Ptr; }	
 
			node* operator ->() 
			{
				return _Ptr; 
			}
 
			node operator *()
			{
				return *_Ptr;
			}
 
			iterator& operator++(int) 
			{ 
				node* _Node = _Ptr->_Right;
 
				if (!_Node->_isHead)
				{
					while (!_Node->_Left->_isHead)			
						_Node = _Node->_Left;
				}
				else {   
					while (!(_Node = _Ptr->_Parent)->_isHead && _Ptr == _Node->_Right)				
						_Ptr= _Node; 
				}
 
				_Ptr = _Node;
				return *this; 
			}
		};
	protected:
		char _Unknown0[4]; 
		iterator _Head; 
		unsigned long _Size;
	public:
 
		iterator begin()
		{
			return iterator(_Head._Ptr->_Left);
		}
 
		iterator end()
		{
			return iterator(_Head._Ptr);
		}
 
		unsigned long size()
		{
			return _Size;
		}
	};  
		
	template <class T>
	struct list
	{
		struct iterator
		{
			class node
			{	
			friend struct list;
			protected:
				node* _Left;
				node* _Right;
			public:
				T _Data;
			};
 
		friend struct list;
 
		protected:
			node* _Ptr;
		public:
 
			iterator(node* _Node) : _Ptr(_Node) { }
 
			bool operator == (const iterator& it) { return _Ptr == it._Ptr; }
			bool operator != (const iterator& it) { return _Ptr != it._Ptr; }	
 
			node* operator ->() 
			{
				return _Ptr; 
			}
 
			T& operator *()
			{
				return _Ptr->_Data;
			}
 
			iterator& operator++(int) 
			{ 
				_Ptr = _Ptr->_Right;
				return *this;
			}
		};
 
	protected:
		char _Unknown0[4];
		iterator _Head;
		unsigned long _Size;
	public:
		iterator begin()
		{
			return iterator(_Head._Ptr->_Right);
		}
 
		iterator end()
		{
			return iterator(_Head._Ptr);
		}
 
		unsigned long size()
		{
			return _Size;
		}
	};  
 
	template <class T>
	struct vector
	{
		void* unk0;
		void* unk1;
		void* unk2;
		void* unk3;
	};		
};
#endif