	/**
	 * @file KeyedList.h
	 * @brief Declaration of tc::KeyedList
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2019/06/30
	 */
#pragma once
#include <map>
#include <list>

namespace tc {

template <class Key, class T>
class KeyedList
{
public:
	using pair_type = typename std::pair<Key,T>;
	using iterator = typename std::list<pair_type>::iterator;
	using const_iterator = typename std::list<pair_type>::const_iterator;
	
	KeyedList();
	KeyedList(std::initializer_list<pair_type> list);
	~KeyedList();
	
	// clear map
	void clear();

	// insert pair
	void insert(const pair_type& pair);
	void insert(pair_type&& pair);

	// [] access (non const)
	T& operator[](const Key& key);
	T& operator[](Key&& key);

	// access member (includes non const and const)
	T& at(const Key& key);
	const T& at(const Key& key) const;

	// get number of elements
	size_t size() const;

	// find elements
	iterator find(const Key& key);
	const_iterator find(const Key& key) const;

	// begin iterator
	iterator begin();
	const_iterator begin() const;

	// end iterator
	iterator end();
	const_iterator end() const;

	// erase iterator
	size_t erase(const Key& key);
	iterator erase(iterator pos);
	iterator erase(const_iterator pos);
	iterator erase(iterator first, iterator last);
	iterator erase(const_iterator first, const_iterator last);

private:
	using map_itr = typename std::map<Key, iterator>::iterator;
	using map_const_itr = typename std::map<Key, iterator>::const_iterator;

	std::list<pair_type> mList;
	std::map<Key, iterator> mLookup;
};

template <class Key, class T>
inline KeyedList<Key,T>::KeyedList() :
	mList(),
	mLookup()
{}

template <class Key, class T>
inline KeyedList<Key,T>::KeyedList(std::initializer_list<pair_type> list) :
	KeyedList()
{
	for (typename std::initializer_list<pair_type>::iterator itr = list.begin(); itr != list.end(); ++itr)
	{
		insert(std::move(*itr));
	}
}

template <class Key, class T>
inline KeyedList<Key,T>::~KeyedList()
{
	clear();
}

template <class Key, class T>
inline void KeyedList<Key,T>::clear()
{
	mLookup.clear();
	mList.clear();
}

template <class Key, class T>
inline void KeyedList<Key,T>::insert(const pair_type& pair)
{
	mList.push_back(pair);
	mLookup.insert({mList.back().first, --mList.end()});
}

template <class Key, class T>
inline void KeyedList<Key,T>::insert(pair_type&& pair)
{
	mList.push_back(std::move(pair));
	mLookup.insert({mList.back().first, --mList.end()});
}

template <class Key, class T>
inline T& KeyedList<Key,T>::operator[](const Key& key)
{
	if (mLookup.find(key) == mLookup.end())
	{
		insert({key, T()});
	}

	return (*mLookup[key]).second;
}

template <class Key, class T>
inline T& KeyedList<Key,T>::operator[](Key&& key)
{
	if (mLookup.find(key) == mLookup.end())
	{
		insert({key, T()});
	}

	return (*mLookup[std::move(key)]).second;
}

template <class Key, class T>
inline T& KeyedList<Key,T>::at(const Key& key)
{
	// map<Key,iterator>
	// at() returns iterator
	// we want T, so we deref itr and get member .second as that is type T (*iterator).second

	return (*mLookup.at(key)).second;
}

template <class Key, class T>
inline const T& KeyedList<Key,T>::at(const Key& key) const
{
	// map<Key,iterator>
	// at() returns iterator
	// we want T, so we deref itr and get member .second as that is type T (*iterator).second

	return (*mLookup.at(key)).second;
}

template <class Key, class T>
inline size_t KeyedList<Key,T>::size() const
{
	return mList.size();
}

template <class Key, class T>
inline typename KeyedList<Key,T>::iterator KeyedList<Key,T>::find(const Key& key)
{
	map_itr itr = mLookup.find(key);

	// if lookup doesn't have key, then neither will list
	if (itr == mLookup.end())
	{
		return mList.end();
	}
	else
	{
		// otherwise return (*find()).second as that is of type list::iterator
		return (*itr).second;
	}
}

template <class Key, class T>
inline typename KeyedList<Key,T>::const_iterator KeyedList<Key,T>::find(const Key& key) const
{
	map_const_itr itr = mLookup.find(key);

	// if lookup doesn't have key, then neither will list
	if (itr == mLookup.end())
	{
		return mList.end();
	}
	else
	{
		// otherwise return (*find()).second as that is of type list::iterator
		return (*itr).second;
	}
}

template <class Key, class T>
inline typename KeyedList<Key,T>::iterator KeyedList<Key,T>::begin()
{
	return mList.begin();
}

template <class Key, class T>
inline typename KeyedList<Key,T>::const_iterator KeyedList<Key,T>::begin() const
{
	return mList.begin();
}

template <class Key, class T>
inline typename KeyedList<Key,T>::iterator KeyedList<Key,T>::end()
{
	return mList.end();
}

template <class Key, class T>
inline typename KeyedList<Key,T>::const_iterator KeyedList<Key,T>::end() const
{
	return mList.end();
}

template <class Key, class T>
inline size_t KeyedList<Key,T>::erase(const Key& key)
{
	iterator itr = find(key);
	if (itr == end())
	{
		return 0;
	}
	
	erase(itr);
	return 1;
}

template <class Key, class T>
inline typename KeyedList<Key,T>::iterator KeyedList<Key,T>::erase( iterator pos )
{
	if (pos == mList.end())
		return mList.end();

	mLookup.erase((*pos).first);
	return mList.erase(pos);
}

template <class Key, class T>
inline typename KeyedList<Key,T>::iterator KeyedList<Key,T>::erase( const_iterator pos )
{
	if (pos == mList.end())
		return mList.end();

	mLookup.erase((*pos).first);
	return mList.erase(pos);
}

template <class Key, class T>
inline typename KeyedList<Key,T>::iterator KeyedList<Key,T>::erase( iterator first, iterator last )
{
	iterator itr = first;
	while (itr != last)
		itr = erase(itr);
	
	return itr;
}

template <class Key, class T>
inline typename KeyedList<Key,T>::iterator KeyedList<Key,T>::erase( const_iterator first, const_iterator last )
{
	iterator itr;
	if (first != last)
	{
		itr = erase(first);
		while (itr != last)
			itr = erase(itr);
	}
	
	return itr;
}

} // namespace tc