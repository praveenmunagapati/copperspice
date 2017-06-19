/***********************************************************************
*
* Copyright (c) 2012-2017 Barbara Geller
* Copyright (c) 2012-2017 Ansel Sermersheim
* Copyright (c) 2012-2016 Digia Plc and/or its subsidiary(-ies).
* Copyright (c) 2008-2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* This file is part of CopperSpice.
*
* CopperSpice is free software. You can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* <http://www.gnu.org/licenses/>.
*
***********************************************************************/

#ifndef QMULTIMAP_H
#define QMULTIMAP_H

#include <qcontainerfwd.h>
#include <qmapfunc.h>

#include <qlist.h>
#include <qrefcount.h>

#include <map>
#include <initializer_list>

template <typename Key, typename Val, typename C>
class QMultiMapIterator;

template <typename Key, typename Val, typename C>
class QMutableMultiMapIterator;

template <typename Key, typename Val, typename C>
class QMultiMap
{
 public:
   class iterator : private std::multimap<Key, Val, C>::iterator
   {
    public:
      using iterator_category = std::bidirectional_iterator_tag;

      using pointer           = Val *;
      using reference         = Val &;

      using difference_type   = typename std::multimap<Key, Val, C>::difference_type;
      using size_type         = typename std::multimap<Key, Val, C>::difference_type;
      using value_type        = Val;

      iterator() = default;

      iterator(typename std::multimap<Key, Val, C>::iterator iter)
         : std::multimap<Key, Val, C>::iterator(std::move(iter)) {
      }

      const Key &key() const {
         const Key &retval = std::multimap<Key, Val, C>::iterator::operator*().first;
         return retval;
      }

      Val &value() const {
         Val &retval = std::multimap<Key, Val, C>::iterator::operator*().second;
         return retval;
      }

      std::pair<const Key, Val> &pair() const {
         return std::multimap<Key, Val, C>::iterator::operator*();
      }

      // operators
      Val &operator*() const {
         return value();
      }

      Val *operator->() const {
         return &value();
      }

      bool operator==(iterator other) const {
         return std::multimap<Key, Val, C>::iterator::operator==(other);
      }

      bool operator!=(iterator other) const {
         return std::multimap<Key, Val, C>::iterator::operator!=(other);
      }

      iterator &operator+=(size_type n) {
         std::advance(*this, n);
         return *this;
      }

      iterator &operator-=(size_type n) {
         std::advance(*this, -n);
         return *this;
      }

      iterator &operator+(size_type n) {
         std::advance(*this, n);
         return *this;
      }

      iterator &operator-(size_type n) {
         std::advance(*this, -n);
         return *this;
      }

      iterator &operator++() {
         std::multimap<Key, Val, C>::iterator::operator++();
         return *this;
      }

      iterator operator++(int n) {
         return std::multimap<Key, Val, C>::iterator::operator++(n);
      }

      iterator &operator--() {
         std::multimap<Key, Val, C>::iterator::operator--();
         return *this;
      }

      iterator operator--(int n) {
         return std::multimap<Key, Val, C>::iterator::operator--(n);
      }

      friend class QMultiMap<Key, Val, C>;
   };

   class const_iterator : private std::multimap<Key, Val, C>::const_iterator
   {
    public:
      using iterator_category = std::bidirectional_iterator_tag;

      using pointer         = const Val *;
      using reference       = const Val &;

      using difference_type = typename std::multimap<Key, Val, C>::difference_type;
      using size_type       = typename std::multimap<Key, Val, C>::difference_type;
      using value_type      = Val;

      const_iterator() = default;

      const_iterator(typename std::multimap<Key, Val, C>::const_iterator iter)
         : std::multimap<Key, Val, C>::const_iterator(std::move(iter)) {
      }

      const_iterator(iterator iter)
         : std::multimap<Key, Val, C>::const_iterator(std::move(iter)) {
      }

      const Key &key() const {
         const Key &retval = std::multimap<Key, Val, C>::const_iterator::operator*().first;
         return retval;
      }

      const Val &value() const {
         const Val &retval = std::multimap<Key, Val, C>::const_iterator::operator*().second;
         return retval;
      }

      const std::pair<const Key, Val> &pair() const {
         return std::multimap<Key, Val, C>::const_iterator::operator*();
      }

      // operators
      const Val &operator*() const {
         return value();
      }

      const Val *operator->() const {
         return &value();
      }

      bool operator==(const_iterator other) const {
         return std::multimap<Key, Val, C>::const_iterator::operator==(other);
      }

      bool operator!=(const_iterator other) const {
         return std::multimap<Key, Val, C>::const_iterator::operator!=(other);
      }

      const_iterator &operator+=(size_type n) {
         std::advance(*this, n);
         return *this;
      }

      const_iterator &operator-=(size_type n) {
         std::advance(*this, -n);
         return *this;
      }

      const_iterator &operator+(size_type n) {
         std::advance(*this, n);
         return *this;
      }

      const_iterator &operator-(size_type n) {
         std::advance(*this, -n);
         return *this;
      }

      const_iterator &operator++() {
         std::multimap<Key, Val, C>::const_iterator::operator++();
         return *this;
      }

      const_iterator operator++(int n) {
         return std::multimap<Key, Val, C>::const_iterator::operator++(n);
      }

      const_iterator &operator--() {
         std::multimap<Key, Val, C>::const_iterator::operator--();
         return *this;
      }

      const_iterator operator--(int n) {
         return std::multimap<Key, Val, C>::const_iterator::operator--(n);
      }

      friend class QMultiMap<Key, Val, C>;
   };

   // legacy
   using Iterator        = iterator;
   using ConstIterator   = const_iterator;

   using const_pointer   = const Val *;
   using const_reference = const Val &;
   using pointer         = Val *;
   using reference       = Val &;

   using difference_type = typename std::multimap<Key, Val, C>::difference_type;
   using size_type       = typename std::multimap<Key, Val, C>::difference_type;   // signed instead of unsigned
   using value_type      = Val;

   using key_type        = typename std::multimap<Key, Val, C>::key_type;
   using mapped_type     = typename std::multimap<Key, Val, C>::mapped_type;

   using key_compare     = typename std::multimap<Key, Val, C>::key_compare;

   // from std
   using allocator_type         = typename std::multimap<Key, Val, C>::allocator_type;
   using reverse_iterator       = std::reverse_iterator<iterator>;
   using const_reverse_iterator = std::reverse_iterator<const_iterator>;

   // java
   using Java_Iterator          = QMultiMapIterator<Key, Val, C>;
   using Java_MutableIterator   = QMutableMultiMapIterator<Key, Val, C>;

   QMultiMap() = default;

   QMultiMap(const QMultiMap<Key, Val, C> &other) = default;
   QMultiMap(QMultiMap<Key, Val, C> &&other)      = default;

   QMultiMap(std::initializer_list<std::pair<Key, Val>> list, const C &compare = C())
      : m_data(list)  {}

   explicit QMultiMap(C compare)
      : m_data(compare) {}

   explicit QMultiMap(const std::multimap<Key, Val, C> &other)
      : m_data(other) {}

   template<typename Input_Iterator>
   QMultiMap(Input_Iterator first, Input_Iterator last, const C &compare = C())
      : m_data(first, last, compare) {}

  ~QMultiMap() = default;

   // methods
   void clear() {
      m_data.clear();
   }

   bool contains(const Key &key) const {
      return m_data.find(key) != m_data.end();
   }

   bool contains(const Key &key, const Val &value)   const;

   size_type count(const Key &key) const {
      return m_data.count(key);
   }

   size_type count() const {
      return size();
   }

   size_type count(const Key &key, const Val &value) const;

   bool empty() const {
      return m_data.empty();
   }

   bool isEmpty() const {
      return m_data.empty();
   }

   iterator erase(const_iterator iter) {
      return m_data.erase(iter);
   }

   iterator find(const Key &key) {
      // find returns an std::map::iterator, constructor will convert to QMultiMap::iterator
      return m_data.find(key);
   }

   const_iterator find(const Key &key) const {
      return m_data.find(key);
   }

   iterator find(const Key &key, const Val &value) {
      auto range = m_data.equal_range(key);

      for (auto iter = range.first; iter != range.second; ++iter) {
         if (iter->second == value) {
            return iter;
         }
      }

      return end();
   }

   const_iterator find(const Key &key, const Val &value) const {
     auto range = m_data.equal_range(key);

      for (auto iter = range.first; iter != range.second; ++iter) {
         if (iter->second == value) {
            return iter;
         }
      }

      return end();
   }

   const_iterator constFind(const Key &key) const {
      return m_data.find(key);
   }

   const_iterator constFind(const Key &key, const Val &value) const {
      return find(key, value);
   }

   iterator insert(const Key &key, const Val &value)  {
      return insertMulti(key, value);
   }

   iterator insertMulti(const Key &key, const Val &value)  {
      // ensure newest item is first
      auto iter = m_data.lower_bound(key);
      return m_data.emplace_hint(iter, key, value);
   }

   const Key key(const Val &value) const;
   const Key key(const Val &value, const Key &defaultKey) const;

   QList<Key> keys() const;
   QList<Key> keys(const Val &value) const;

   iterator lowerBound(const Key &key) {
      return m_data.lower_bound(key);
   }

   const_iterator lowerBound(const Key &key) const  {
      return m_data.lower_bound(key);
   }

   size_type remove(const Key &key)  {
      return m_data.erase(key);
   }

   size_type remove(const Key &key, const Val &value);

   iterator replace(const Key &key, const Val &value) {
      auto iter = m_data.find(key);

      if (iter == m_data.end()) {
         // add new element
         return m_data.emplace(key, value).first;
      }

      iter->second = value;

      return iter;
   }

   size_type size() const {
      // returns unsigned, must convert to signed
      return static_cast<size_type>(m_data.size());
   }

   void swap(QMultiMap<Key, Val, C> &other) {
      qSwap(m_data, other.m_data);
   }

   Val take(const Key &key)  {
      auto iter = m_data.find(key);

      if (iter == m_data.end()) {
         return Val();
      }

      Val retval = std::move(iter->second);
      m_data.erase(iter);

      return retval;
   }

   iterator upperBound(const Key &key)  {
      return m_data.upper_bound(key);
   }

   const_iterator upperBound(const Key &key) const {
      return m_data.upper_bound(key);
   }

   QList<Key> uniqueKeys() const;

   QMultiMap<Key, Val, C> &unite(const QMultiMap<Key, Val, C> &other) {
      m_data.insert(other.m_data.begin(), other.m_data.end());
      return *this;
   }

   const Val value(const Key &key) const {
      auto range = m_data.equal_range(key);

      if (range.first == range.second) {
         // key was not found
         return Val();
      }

      // get last key in the range
      auto iter = --range.second;

      return iter->second;
   }

   const Val value(const Key &key, const Val &defaultValue) const;

   QList<Val> values() const;
   QList<Val> values(const Key &key) const;

   // to from
   std::map<Key, Val, C> toStdMap() const;

   // iterators
   iterator begin() {
      // m_data.begin is an stl iterator
      // return calls a conversion constructor since the return type is iterator, returns a QMultiMap iterator

      return m_data.begin();
   }

   const_iterator begin() const {
      return m_data.begin();
   }

   const_iterator constBegin() const {
      return m_data.begin();
   }

   const_iterator cbegin() const {
      return m_data.begin();
   }

   iterator end() {
      return m_data.end();
   }

   const_iterator end() const {
      return m_data.end();
   }

   const_iterator constEnd() const {
      return m_data.end();
   }

   const_iterator cend() const {
      return m_data.end();
   }

   QMultiMap &operator+=(const QMultiMap &other) {
      this->unite(other);
      return *this;
   }

   QMultiMap operator+(const QMultiMap &other) const {
      QMultiMap result = *this;
      result += other;
      return result;
   }

   // operators
   QMultiMap<Key, Val, C> &operator=(const QMultiMap<Key, Val, C> &other) = default;
   QMultiMap<Key, Val, C> &operator=(QMultiMap<Key, Val, C> &&other)      = default;

   bool operator==(const QMultiMap<Key, Val, C> &other) const {
      return m_data == other.m_data;
   }

   bool operator!=(const QMultiMap<Key, Val, C> &other) const {
      return m_data != other.m_data;
   }

   Val &operator[](const Key &key);
   const Val operator[](const Key &key) const;

 private:
   std::map<Key, Val, C> m_data;

};

template <class Key, class Val, class C>
bool QMultiMap<Key, Val, C>::contains(const Key &key, const Val &value) const
{
   return constFind(key, value) != QMultiMap<Key, Val, C>::constEnd();
}

template <class Key, class Val, class C>
typename QMultiMap<Key, Val, C>::size_type QMultiMap<Key, Val, C>::count(const Key &key, const Val &value) const
{
   int retval = 0;

   auto range = m_data.equal_range(key);

   for (auto iter = range.first; iter != range.second; ++iter) {
      if (iter->second == value) {
         ++retval;
      }
   }

   return retval;
}

template <class Key, class Val, class C>
typename QMultiMap<Key, Val, C>::size_type QMultiMap<Key, Val, C>::remove(const Key &key, const Val &value)
{
   int retval = 0;

   auto range = m_data.equal_range(key);
   auto iter  = range.first;

   while (iter != range.second) {
      if (iter->second == value) {
         iter = m_data.erase(iter);
         ++retval;
      } else {
         ++iter;
      }
   }

   return retval;
}

template <class Key, class Val, class C>
QList<Val> QMultiMap<Key, Val, C>::values() const
{
   QList<Val> retval;
   retval.reserve(size());

   const_iterator iter = begin();

   while (iter != end()) {
      retval.append(iter.value());
      ++iter;
   }

   return retval;
}

template <class Key, class Val, class C>
QList<Val> QMultiMap<Key, Val, C>::values(const Key &key) const
{
   QList<Val> retval;

   auto range = m_data.equal_range(key);

   for (auto iter = range.first; iter != range.second; ++iter) {
      retval.append(iter->second);
   }

   return retval;
}

// java style iterators

template <class Key, class Val, class C = qMapCompare<Key>>
class QMultiMapIterator
{
   typedef typename QMultiMap<Key, Val, C>::const_iterator const_iterator;
   typedef const_iterator Item;

   const QMultiMap<Key, Val, C> *c;
   const_iterator i;
   const_iterator n;

   inline bool item_exists() const {
      return n != c->constEnd();
   }

 public:
   inline QMultiMapIterator(const QMultiMap<Key, Val, C> &container)
      : c(&container), i(c->constBegin()), n(c->constEnd()) {}

   inline QMultiMapIterator &operator=(const QMultiMap<Key, Val, C> &container) {
      c = container;
      i = c->constBegin();
      n = c->constEnd();

      return *this;
   }

   inline void toFront() {
      i = c->constBegin();
      n = c->constEnd();
   }

   inline void toBack() {
      i = c->constEnd();
      n = c->constEnd();
   }

   inline bool hasNext() const {
      return i != c->constEnd();
   }

   inline Item next() {
      n = i++;
      return n;
   }

   inline Item peekNext() const {
      return i;
   }

   inline bool hasPrevious() const {
      return i != c->constBegin();
   }

   inline Item previous() {
      n = --i;
      return n;
   }
   inline Item peekPrevious() const {
      const_iterator p = i;
      return --p;
   }

   inline const Val &value() const {
      Q_ASSERT(item_exists());
      return *n;
   }

   inline const Key &key() const {
      Q_ASSERT(item_exists());
      return n.key();
   }

   inline bool findNext(const Val &t) {
      while ((n = i) != c->constEnd()) {
         if (*i++ == t) {
            return true;
         }
      }
      return false;
   }

   inline bool findPrevious(const Val &t) {
      while (i != c.constBegin()) {
         if (*(n = --i) == t) {
            return true;
         }
      }

      n = c->constEnd();
      return false;
   }
};

template <class Key, class Val, class C = qMapCompare<Key>>
class QMutableMultiMapIterator
{
   typedef typename QMultiMap<Key, Val, C>::iterator iterator;
   typedef typename QMultiMap<Key, Val, C>::const_iterator const_iterator;
   typedef iterator Item;

   QMultiMap<Key, Val, C> *c;
   iterator i;
   iterator n;

   bool item_exists() const {
      return const_iterator(n) != c->constEnd();
   }

 public:
   inline QMutableMultiMapIterator(QMultiMap<Key, Val, C> &container)
      : c(&container), i(c->begin()), n(c->end()) {}

   inline ~QMutableMultiMapIterator() {
   }

   inline QMutableMultiMapIterator &operator=(QMultiMap<Key, Val, C> &container) {
      c = &container;
      i = c->begin();
      n = c->end();

      return *this;
   }

   inline void toFront() {
      i = c->begin();
      n = c->end();
   }

   inline void toBack() {
      i = c->end();
      n = i;
   }

   inline bool hasNext() const {
      return c->constEnd() != const_iterator(i);
   }

   inline Item next() {
      n = i++;
      return n;
   }

   inline Item peekNext() const {
      return i;
   }

   inline bool hasPrevious() const {
      return c->constBegin() != const_iterator(i);
   }

   inline Item previous() {
      n = --i;
      return n;
   }

   inline Item peekPrevious() const {
      iterator p = i;
      return --p;
   }

   inline void remove() {
      if (c->constEnd() != const_iterator(n)) {
         i = c->erase(n);
         n = c->end();
      }
   }

   inline void setValue(const Val &t) const {
      if (c->constEnd() != const_iterator(n)) {
         *n = t;
      }
   }

   inline Val &value() {
      Q_ASSERT(item_exists());
      return *n;
   }

   inline const Val &value() const {
      Q_ASSERT(item_exists());
      return *n;
   }

   inline const Key &key() const {
      Q_ASSERT(item_exists());
      return n.key();
   }

   inline bool findNext(const Val &t) {
      while (c->constEnd() != const_iterator(n = i)) {
         if (*i++ == t)  {
            return true;
         }
      }

      return false;
   }

   inline bool findPrevious(const Val &t) {
      while (c->constBegin() != const_iterator(i)) {
         if (*(n = --i) == t) {
            return true;
         }
      }

      n = c->end();
      return false;
   }

};

#endif
