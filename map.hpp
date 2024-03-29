#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "pair.hpp"
# include "tree.hpp"

namespace ft
{
	template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>,
				typename _Alloc = std::allocator<ft::pair<const _Key, _Tp> > >
		class map
		{
			public:
				typedef _Key							key_type;
				typedef _Tp								mapped_type;
				typedef ft::pair<const _Key, _Tp>		value_type;
				typedef _Compare						key_compare;
				typedef _Alloc							allocator_type;

				class value_compare
				: public std::binary_function<value_type, value_type, bool>
				{
					friend class map<_Key, _Tp, _Compare, _Alloc>;

					protected:
						_Compare comp;

					value_compare(_Compare __c)
					: comp(__c) { }

					public:
						bool operator()(const value_type& __x, const value_type& __y) const
						{ return comp(__x.first, __y.first); }
				};

			private:
				typedef Rb_tree<key_type, value_type, key_compare> Rep_type;

				Rep_type	m_tree;

			public:
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;
				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename Rep_type::iterator					iterator;
				typedef typename Rep_type::const_iterator			const_iterator;
				typedef typename Rep_type::size_type				size_type;
				typedef typename Rep_type::difference_type			difference_type;
				typedef typename Rep_type::reverse_iterator			reverse_iterator;
				typedef typename Rep_type::const_reverse_iterator	const_reverse_iterator;

				map()
				: m_tree() { }

				explicit
				map(const key_compare& comp,
				const allocator_type& a = allocator_type())
				: m_tree(comp, a) { }

				map(const map& x)
				: m_tree(x.m_tree) { }

				template <class InputIterator>
				map (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
				: m_tree(comp, alloc)
				{ insert(first, last); }

				map&
				operator=(const map& x)
				{
					m_tree = x.m_tree;
					return (*this);
				}

				// __iterators__
				iterator
				begin()
				{ return m_tree.begin(); }

				const_iterator
				begin() const
				{ return m_tree.begin(); }

				iterator
				end()
				{ return m_tree.end(); }

				const_iterator
				end() const
				{ return m_tree.end(); }

				reverse_iterator
				rbegin()
				{ return m_tree.rbegin(); }

				const_reverse_iterator
				rbegin() const
				{ return m_tree.rbegin(); }

				reverse_iterator
				rend()
				{ return m_tree.rend(); }

				const_reverse_iterator
				rend() const
				{ return m_tree.rend(); }

				// __capacity__
				bool
				empty() const
				{ return m_tree.empty(); }

				size_type
				size() const
				{ return m_tree.size(); }

				size_type
				max_size() const
				{ return m_tree.max_size(); }

				// __Element access__
				mapped_type&
				operator[] (const key_type& k)
		       {
					iterator it = find(k);

					if (it == end())
						it = insert(it, value_type(k, mapped_type()));
					return ((*it).second);
				}

				// __Modifiers__
				ft::pair<iterator, bool>
				insert (const value_type& val)
				{ return (m_tree.insert(val)); }

				iterator
				insert(iterator position, const value_type& val)
				{
					(void)position;
					return (m_tree.insert(val).first);
				}

				template <class InputIterator>
					void
					insert(InputIterator first, InputIterator last)
					{
						for (; first != last; first++)
						{
							if (find(first->first) == end())
								m_tree.insert(*first);
						}
					}

				void
				erase(iterator position)
				{ m_tree.erase(position->first); }

				size_type
				erase(const key_type& k)
				{ return (m_tree.erase(k)); }

				void
				erase(iterator first, iterator last)
				{
					Rep_type new_tree;

					for (iterator it = first; it != last; it++)
						new_tree.insert(*it);

					for (iterator it = new_tree.begin(); it != new_tree.end(); it++)
						m_tree.erase(it->first);
				}

				void
				swap(map& x)
				{ m_tree.swap(x.m_tree); }

				void
				clear()
				{ m_tree.clear(); }

				// __Observers__
				key_compare
				key_comp() const
				{ return (m_tree.get_comp()); }

				value_compare
				value_comp() const
				{ return (value_compare(key_comp())); }

				// __Operations__
				iterator
				find(const key_type& k)
				{
					iterator to_find = iterator(m_tree.find(k));

					if (size() == 0
						|| (to_find != end()
						&& to_find->first != k))
						return (end());
					return (to_find);
				}

				const_iterator
				find(const key_type& k) const
				{
					const_iterator to_find = iterator(m_tree.find(k));

					if (empty() || (to_find != end()
						&& to_find->first != k))
						return (end());
					return (to_find);
				}

				size_type
				count(const key_type& k) const
				{ return (find(k) == end() ? 0 : 1); }

				iterator
				lower_bound(const key_type& k)
				{ return (m_tree.lower_bound(k)); }

				const_iterator
				lower_bound(const key_type& k) const
				{ return (m_tree.lower_bound(k)); }

				iterator
				upper_bound(const key_type& k)
				{ return (m_tree.upper_bound(k)); }

				const_iterator
				upper_bound(const key_type& k) const
				{ return (m_tree.upper_bound(k)); }

				ft::pair<const_iterator, const_iterator>
				equal_range(const key_type& k) const
				{ return (ft::make_pair(const_iterator(m_tree.equal_range(k)),
										upper_bound(k))); }

				ft::pair<iterator, iterator>
				equal_range(const key_type& k)
				{ return (ft::make_pair(iterator(m_tree.equal_range(k)),
										upper_bound(k))); }

				// __Allocator__
				allocator_type
				get_allocator() const
				{ return (m_tree.get_allocator()); }

				template<typename Key_, typename Tp_, typename Compare_, typename Alloc_>
					friend inline bool
					operator==(const map<Key_, Tp_, Compare_, Alloc_>& x,
					const map<Key_, Tp_, Compare_, Alloc_>& y);

				template<typename Key_, typename Tp_, typename Compare_, typename Alloc_>
					friend inline bool
					operator<(const map<Key_, Tp_, Compare_, Alloc_>& x,
					const map<Key_, Tp_, Compare_, Alloc_>& y);

		};

		template<typename Key, typename Tp, typename Compare, typename Alloc>
			inline bool
			operator==(const map<Key, Tp, Compare, Alloc>& x,
			const map<Key, Tp, Compare, Alloc>& y)
			{ return (x.m_tree == y.m_tree); }

		template<typename Key, typename Tp, typename Compare, typename Alloc>
			inline bool
			operator<(const map<Key, Tp, Compare, Alloc>& x,
			const map<Key, Tp, Compare, Alloc>& y)
			{ return (x.m_tree < y.m_tree); }

		template<typename Key, typename Tp, typename Compare, typename Alloc>
			inline bool
			operator!=(const map<Key, Tp, Compare, Alloc>& x,
			const map<Key, Tp, Compare, Alloc>& y)
			{ return !(x == y); }

		template<typename Key, typename Tp, typename Compare, typename Alloc>
			inline bool
			operator>(const map<Key, Tp, Compare, Alloc>& x,
			const map<Key, Tp, Compare, Alloc>& y)
			{ return (y < x); }

		template<typename Key, typename Tp, typename Compare, typename Alloc>
			inline bool
			operator<=(const map<Key, Tp, Compare, Alloc>& x,
			const map<Key, Tp, Compare, Alloc>& y)
			{ return !(y < x); }

		template<typename Key, typename Tp, typename Compare, typename Alloc>
			inline bool
			operator>=(const map<Key, Tp, Compare, Alloc>& x,
			const map<Key, Tp, Compare, Alloc>& y)
			{ return !(x < y); }


		template <class Key, class T, class Compare, class Alloc>
			void
			swap(map<Key, T, Compare, Alloc>& x,
					map<Key, T, Compare, Alloc>& y)
			{ x.swap(y); }
}

#endif