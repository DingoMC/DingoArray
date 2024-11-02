/**
 * @file dingo_array.h
 * @author DingoMC (martin701-2001@wp.pl)
 * @brief Dingo Array for C++. Manage array calculations in more modern and convenient way.
 * @version 1.0
 * @date 2024-11-02
 * 
 * @copyright Copyright (c) DingoMC Systems 2024
 * @warning Library written and tested on C++11. Older versions not supported!
 * 
 */
#pragma once
#ifndef DINGO_ARRAY_H
#define DINGO_ARRAY_H

#include <math.h>
#include <vector>
#include <list>
#include <set>
#pragma GCC optimize("O3")
#define MAX_S(a, b) a > b ? a : b
#define ARRAY_BEGIN 0                // Min index available
#define ARRAY_END 2147483647         // Max index available

template <class T>
class Array {
  private:
    T* A;
    int S;
    int idx (int index) const {
      if (index < -this->S || index >= this->S) throw std::invalid_argument("Invalid Array Index!");
      if (index >= 0) return index;
      return index + this->S;
    }
    void checkRange (int From, int To) const {
      int width = idx(To) - idx(From) + 1;
      if (width < 1 || width > this->S) throw std::invalid_argument("Invalid From-To Range");
      return;
    }
    static void checkSize (int size) {
      if (size < ARRAY_BEGIN || size > ARRAY_END) throw std::invalid_argument("Invalid Array Size provided");
      return;
    }
    void sizeAlloc (int size) {
      checkSize(size);
      this->S = size;
      if (size > 0) this->A = (T*) calloc(size, sizeof(T));
      else this->A = nullptr;
    }
  public:
    /* STATIC METHODS FOR CONVERSIONS */
    static Array fromVector (const std::vector < T > &STL_Vector) {
      Array a;
      a.sizeAlloc(STL_Vector.size());
      for (int i = 0; i < a.size(); i++) a[i] = STL_Vector[i];
      return a;
    }
    static Array fromList (const std::list < T > &STL_List) {
      Array a;
      a.sizeAlloc(STL_List.size());
      int i = 0;
      for (auto it = STL_List.cbegin(); it != STL_List.cend(); it++) {
        if (i >= a.size()) break;
        a[i] = *it;
        i++;
      }
      return a;
    }
    static Array fromSet (const std::set < T > &STL_Set) {
      Array a;
      a.sizeAlloc(STL_Set.size());
      int i = 0;
      for (auto it = STL_Set.cbegin(); it != STL_Set.cend(); it++) {
        if (i >= a.size()) break;
        a[i] = *it;
        i++;
      }
      return a;
    }
    static Array fromInitList (std::initializer_list<T> InitValues) {
      Array a;
      a.sizeAlloc(InitValues.size());
      int i = 0;
      for (auto it = InitValues.begin(); it != InitValues.end(); it++) {
        if (i >= a.size()) break;
        a[i] = *it;
        i++;
      }
      return a;
    }
    static Array fromPointer (T* ptr, int size) {
      Array a;
      a.sizeAlloc(size);
      for (int i = 0; i < a.size(); i++) a[i] = ptr[i];
      return a;
    }
    /* CONSTRUCTORS */
    // Empty Array Constructor -> Size = 0
    Array () {
      this->S = 0;
      this->A = nullptr;
    }
    // Array Constructor with initial size
    explicit Array (int s) { this->sizeAlloc(s); }
    // Array Constructor using STL Vector
    explicit Array (const std::vector < T > &STL_Vector) {
      this->sizeAlloc(STL_Vector.size());
      for (int i = 0; i < this->S; i++) this->A[i] = STL_Vector[i];
    }
    // Array Constructor using STL List
    explicit Array (const std::list < T > &STL_List) {
      this->sizeAlloc(STL_List.size());
      int i = 0;
      for (auto it = STL_List.cbegin(); it != STL_List.cend(); it++) {
        if (i >= this->S) break;
        this->A[i] = *it;
        i++;
      }
    }
    // Array Constructor using STL Set
    explicit Array (const std::set < T > &STL_Set) {
      this->sizeAlloc(STL_Set.size());
      int i = 0;
      for (auto it = STL_Set.cbegin(); it != STL_Set.cend(); it++) {
        if (i >= this->S) break;
        this->A[i] = *it;
        i++;
      }
    }
    // Array Constructor using STL Initializer List
    explicit Array (std::initializer_list<T> InitValues) {
      this->sizeAlloc(InitValues.size());
      int i = 0;
      for (auto it = InitValues.begin(); it != InitValues.end(); ++it) {
        if (i >= this->S) break;
        this->A[i] = *it;
        i++;
      }
    }
    // Array Constructor using pointer
    Array (const T* dynamicArray, int arraySize) {
      this->sizeAlloc(arraySize);
      for (int i = 0; i < this->S; i++) this->A[i] = dynamicArray[i];
    }
    // Copy constructor
    Array(const Array& other) : S(other.S) {
      if (this->S > 0) {
        this->A = (T*) malloc(this->S * sizeof(T));
        for (int i = 0; i < this->S; i++) this->A[i] = other.A[i];
      } else this->A = nullptr;
    }
    // Move constructor
    Array(Array&& other) noexcept : S(other.S), A(other.A) {
      other.S = 0;
      other.A = nullptr;
    }
    // Default Destructor
    ~Array () {
      if (this->A != nullptr) free(this->A);
    }
    // Getting array size
    int size () noexcept {return this->S;}
    int size () const noexcept {return S;}
    // Same as `size()`
    int length () noexcept {return this->S;}
    int length () const noexcept {return S;}
    /**
     * @brief Print Array to stdout
     * @param showType View `Array` type. Default `false`
     * @param showBrackets View Brakcets. Default `true`
     * @param endNewLine Print `\n` after viewing the array. Default `true`
     * @param elemNewLine Print `\n` after each element. Default `false`
     * @param bracketOpenChar Opening bracket character. Default `'['`
     * @param bracketCloseChar Closing bracket character. Default `']'`
     * @param sep Separator string. Default `", "`
     */
    void show (
      bool showType = false, bool showBrackets = true, bool endNewLine = true, bool elemNewLine = false,
      char bracketOpenChar = '[', char bracketCloseChar = ']', const std::string &sep = ", "
    ) const noexcept {
      if (showType) std::cout<<"`Array` ";
      if (showBrackets) std::cout<<bracketOpenChar;
      for (int i = 0; i < this->S; i++) {
        std::cout<<this->A[i];
        if (i < this->S - 1) std::cout<<sep;
        if (elemNewLine) std::cout<<std::endl;
      }
      if (showBrackets) std::cout<<bracketCloseChar;
      if (endNewLine) std::cout<<std::endl;
    }
    // Non-accessible and accessible subscripts (Negative indexing supported)
    T& operator[] (int index) {return A[idx(index)];}
    T operator[] (int index) const {return A[idx(index)];}
    // Multi-index subscript operator (read-only)
    Array<T> operator[] (Array<int> index) const {
      Array<T> X;
      for (int i = 0; i < index.size(); i++) {
        X.append(this->A[idx(index[i])]);
      }
      return X;
    }
    Array<T> operator[] (const std::vector <int> &index) const { return this->operator[](Array<int>::fromVector(index)); }
    Array<T> operator[] (const std::list <int> &index) const { return this->operator[](Array<int>::fromList(index)); }
    Array<T> operator[] (const std::set <int> &index) const { return this->operator[](Array<int>::fromSet(index)); }
    Array<T> operator[] (const std::initializer_list <int> &index) const { return this->operator[](Array<int>::fromInitList(index)); }

    /**
     * @brief Append `elem` to the end of Array
     * @param elem 
     */
    void append (const T& elem) {
      int newSize = this->S + 1;
      checkSize(newSize);
      this->A = (T*)realloc(this->A, newSize * sizeof(T));
      if (this->A == NULL) throw std::invalid_argument("Failed to Allocate Memory");
      this->A[newSize - 1] = elem;
      this->S++;
    }
    /**
     * @brief Append `array` to the end of Array
     * @param array 
     */
    void append (const Array<T>& array) {
      if (array.size() == 0) return;
      int newSize = this->S + array.size();
      checkSize(newSize);
      this->A = (T*)realloc(this->A, newSize * sizeof(T));
      if (this->A == NULL) throw std::invalid_argument("Failed to Allocate Memory");
      for (int i = 0; i < array.size(); i++) this->A[this->S + i] = array[i];
      this->S += array.size();
    }
    void append (const std::vector < T > &STL_Vector) { append(fromVector(STL_Vector)); }
    void append (const std::list < T > &STL_List) { append(fromList(STL_List)); }
    void append (const std::set < T > &STL_Set) { append(fromSet(STL_Set)); }
    void append (std::initializer_list<T> InitValues) { append(fromInitList(InitValues)); }
    void append (T* ptr, int size) { append(fromPointer(ptr, size)); }

    /**
     * @brief Insert `elem` into Array at specific `index`
     * @param elem 
     * @param index Default 0
     */
    void insert (const T& elem, int index = ARRAY_BEGIN) {
      int newSize = this->S + 1;
      checkSize(newSize);
      int i_idx = idx(index);
      this->A = (T*)realloc(this->A, newSize * sizeof(T));
      if (this->A == NULL) throw std::invalid_argument("Failed to Allocate Memory");
      for (int i = newSize - 1; i > i_idx; i--) this->A[i] = this->A[i - 1];
      this->A[i_idx] = elem;
      this->S++;
    }
    /**
     * @brief Insert `array` into Array at specific `index`
     * @param array 
     * @param index Default 0
     */
    void insert (const Array<T>& array, int index = ARRAY_BEGIN) {
      if (array.size() == 0) return;
      int newSize = this->S + array.size();
      checkSize(newSize);
      int i_idx = idx(index);
      this->A = (T*)realloc(this->A, newSize * sizeof(T));
      if (this->A == NULL) throw std::invalid_argument("Failed to Allocate Memory");
      for (int i = newSize - 1; i >= i_idx + array.size(); i--) this->A[i] = this->A[i - array.size()];
      for (int i = 0; i < array.size(); i++) this->A[i_idx + i] = array[i];
      this->S += array.size();
    }
    void insert (const std::vector < T > &STL_Vector, int index = ARRAY_BEGIN) { insert(fromVector(STL_Vector), index); }
    void insert (const std::list < T > &STL_List, int index = ARRAY_BEGIN) { insert(fromList(STL_List), index); }
    void insert (const std::set < T > &STL_Set, int index = ARRAY_BEGIN) { insert(fromSet(STL_Set), index); }
    void insert (std::initializer_list<T> InitValues, int index = ARRAY_BEGIN) { insert(fromInitList(InitValues), index); }
    void insert (T* ptr, int size, int index = ARRAY_BEGIN) { insert(fromPointer(ptr, size), index); }

    /**
     * @brief Delete n = `count` Array elements starting from `index`
     * @param index Default 0
     * @param count Default 1
     */
    void erase (int index = ARRAY_BEGIN, int count = 1) {
      if (this->S == 0 || count <= 0) return;
      int e_idx = idx(index);
      int c_count = e_idx + count > this->S ? (e_idx + count - this->S + 1) : count;
      int newSize = this->S - c_count;
      checkSize(newSize);
      if (newSize == 0) {
        this->A = nullptr;
        this->S = 0;
        return;
      }
      if (e_idx + c_count >= this->S) {
        this->A = (T*)realloc(this->A, newSize * sizeof(T));
        this->S = newSize;
        return;
      }
      for (int i = e_idx + count; i < this->S; i++) this->A[i - count] = this->A[i];
      this->A = (T*)realloc(this->A, newSize * sizeof(T));
      this->S = newSize;
    }

    /**
     * @brief Fill the Array with `elem` in range `[from,to]`
     * @param elem 
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     */
    void fill (const T& elem, int from = ARRAY_BEGIN, int to = ARRAY_END) {
      if (this->S == 0) return;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      for (int i = b; i <= e; i++) this->A[i] = elem;
    }

    /**
     * @brief Fill the Array with specific `pattern` in range `[from,to]`
     * @param pattern Array Pattern
     * @param mode `'r'` - Repeating (default) - repeats pattern values if pattern is smaller than fill range.
     * `'s'` - Stretch - copies pattern values to match fill range length
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     */
    void fill (const Array<T>& pattern, char mode = 'r', int from = ARRAY_BEGIN, int to = ARRAY_END) {
      if (this->S == 0 || pattern.size() == 0) return;
      if (pattern.size() == 1) {
        this->fill(pattern[0], from, to);
        return;
      }
      if (mode != 'r' && mode != 's') throw std::invalid_argument("Mode should be s - stretch or r - repeat");
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      if (mode == 'r') {
        for (int i = b; i <= e; i++) this->A[i] = pattern[(i - b) % pattern.size()];
        return;
      }
      for (int i = b; i <= e; i++) {
        int index = (int) floor((i - b) * pattern.size() / (e - b + 1.0));
        this->A[i] = pattern[index];
      }
    }
    void fill (const std::vector < T > &pattern, char mode = 'r', int from = ARRAY_BEGIN, int to = ARRAY_END) { fill(fromVector(pattern), mode, from, to); }
    void fill (const std::list < T > &pattern, char mode = 'r', int from = ARRAY_BEGIN, int to = ARRAY_END) { fill(fromList(pattern), mode, from, to); }
    void fill (const std::set < T > &pattern, char mode = 'r', int from = ARRAY_BEGIN, int to = ARRAY_END) { fill(fromSet(pattern), mode, from, to); }
    void fill (std::initializer_list<T> pattern, char mode = 'r', int from = ARRAY_BEGIN, int to = ARRAY_END) { fill(fromInitList(pattern), mode, from, to); }
    void fill (T* pattern, int size, char mode = 'r', int from = ARRAY_BEGIN, int to = ARRAY_END) { fill(fromPointer(pattern, size), mode, from, to); }

    /**
     * @brief Reverse `Array` items in range `[from,to]`
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     */
    void reverse (int from = ARRAY_BEGIN, int to = ARRAY_END) {
      if (this->S == 0) return;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      for (int i = b; i < (e + b + 1) / 2; i++) {
        T temp = this->A[i];
        this->A[i] = this->A[e - i + b];
        this->A[e - i + b] = temp;
      }
    }

    /**
     * @brief Remove all elements of the `Array`
     */
    void clear () {
      if (this->S == 0) return;
      this->A = nullptr;
      this->S = 0;
    }

    /**
     * @brief Resize the `Array` into specified size.
     * @warning Resizing array into smaller size will remove the data which is out of bounds. Resizing to `0` removes data completely
     * @param size New Size
     */
    void resize (int size) {
      checkSize(size);
      T *new_a = (T*)calloc(size, sizeof(T));
      if (new_a == NULL) throw std::invalid_argument("Failed to Allocate Memory");
      memcpy(new_a, this->A, this->S * sizeof(T));
      this->S = size;
      free(this->A);
      this->A = new_a;
    }

    /**
     * @brief Shift `Array` items in range `[from,to]` by specified `amount`
     * @param amount Shift amount. If negative, it shifts to the left
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     */
    void shift (int amount, int from = ARRAY_BEGIN, int to = ARRAY_END) {
      if (this->S == 0 || amount == 0) return;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int len = e - b + 1;
      if (amount % len == 0 || len <= 1) return;
      Array<T> temp = *this;
      for (int i = b; i <= e; i++) {
        int destIndex = b + ((i + amount - b) % len);
        if (destIndex < b) destIndex = len + ((i + amount) % len);
        this->A[destIndex] = temp[i];
      }
    }

    /**
     * @brief Replace all `Array` items in range `[from,to]`, which are `searchElem` with value of `replaceWith`
     * @param searchElem Search Element
     * @param replaceWith Replace Value
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     */
    void replace (const T& searchElem, const T& replaceWith, int from = ARRAY_BEGIN, int to = ARRAY_END) {
      if (this->S == 0) return;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      for (int i = b; i <= e; i++) {
        if (this->A[i] == searchElem) this->A[i] = replaceWith;
      }
    }

    /**
     * @brief Sort `Array` items in range `[from,to]` using optimized bubble sort
     * 
     * @param ascending Default `true`. `false` = descending order
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     */
    void sort (bool ascending = true, int from = ARRAY_BEGIN, int to = ARRAY_END) {
      if (this->S <= 1) return;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int len = (e - b + 1);
      if (len <= 1) return;
      for (int i = 0; i < len; i++) {
        bool swapped = false;
        for (int j = b; j < e - i; j++) {
          if ((ascending && this->A[j] > this->A[j+1]) || (!ascending && this->A[j] < this->A[j+1])) {
            T temp = this->A[j];
            this->A[j] = this->A[j+1];
            this->A[j+1] = temp;
            swapped = true;
          }
        }
        if (!swapped) break;
      }
    }
    /**
     * @brief Returns `Array` with sorted items in range `[from,to]` using optimized bubble sort. 
     * Does not modify initial `Array`
     * @param ascending Default `true`. `false` = descending order
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return Array<T> 
     */
    Array<T> toSorted (bool ascending = true, int from = ARRAY_BEGIN, int to = ARRAY_END) {
      Array<T> X = *this;
      if (this->S <= 1) return X;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int len = (e - b + 1);
      if (len <= 1) return X;
      for (int i = 0; i < len; i++) {
        bool swapped = false;
        for (int j = b; j < e - i; j++) {
          if ((ascending && X[j] > X[j+1]) || (!ascending && X[j] < X[j+1])) {
            T temp = X[j];
            X[j] = X[j+1];
            X[j+1] = temp;
            swapped = true;
          }
        }
        if (!swapped) break;
      }
      return X;
    }

    /**
     * @brief Check if `Array` items in range `[from,to]` contain `elem`
     * @param elem Search element
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return true - Element found,
     * @return false - Element not found
     */
    bool contains (const T& elem, int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      if (this->S == 0) return false;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      for (int i = b; i <= e; i++) {
        if (this->A[i] == elem) return true;
      }
      return false;
    }

    /**
     * @brief Check if `Array` items in range `[from,to]` contain a `pattern`
     * @param pattern Search pattern
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return true - Pattern found,
     * @return false - Pattern not found
     */
    bool contains (const Array<T>& pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      if (this->S == 0 || pattern.size() > this->S) return false;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int current_search = 0;
      for (int i = b; i <= e; i++) {
        if (this->A[i] == pattern[current_search]) current_search++;
        else current_search = 0;
        if (current_search == pattern.size()) return true;
      }
      return false;
    }
    bool contains (const std::vector < T > &pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return contains(fromVector(pattern), from, to); }
    bool contains (const std::list < T > &pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return contains(fromList(pattern), from, to); }
    bool contains (const std::set < T > &pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return contains(fromSet(pattern), from, to); }
    bool contains (std::initializer_list<T> pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return contains(fromInitList(pattern), from, to); }
    bool contains (T* pattern, int size, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return contains(fromPointer(pattern, size), from, to); }

    /**
     * @brief Count how many `elems` exist in an `Array` in range `[from,to]`
     * @param elem Search element
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return int - Successful search count
     */
    int count (const T& elem, int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      if (this->S == 0) return 0;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int cnt = 0;
      for (int i = b; i <= e; i++) {
        if (this->A[i] == elem) cnt++;
      }
      return cnt;
    }

    /**
     * @brief Count how many `patterns` exist in an `Array` in range `[from,to]`
     * @param pattern Search pattern (sub-array)
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return int - Successful search count
     */
    int count (const Array<T>& pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      if (this->S == 0 || pattern.size() > this->S) return 0;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int cnt = 0;
      int current_search = 0;
      for (int i = b; i <= e; i++) {
        if (this->A[i] == pattern[current_search]) current_search++;
        else current_search = 0;
        if (current_search == pattern.size()) {
          cnt++;
          current_search = 0;
        }
      }
      return cnt;
    }
    int count (const std::vector < T > &pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return count(fromVector(pattern), from, to); }
    int count (const std::list < T > &pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return count(fromList(pattern), from, to); }
    int count (const std::set < T > &pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return count(fromSet(pattern), from, to); }
    int count (std::initializer_list<T> pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return count(fromInitList(pattern), from, to); }
    int count (T* pattern, int size, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return count(fromPointer(pattern, size), from, to); }

    /**
     * @brief Find first index of search `elem` in range `[from,to]`. Returns `-1` if none found
     * @param elem Search element
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return int - Found index or `-1`
     */
    int find (const T& elem, int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      if (this->S == 0) return -1;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      for (int i = b; i <= e; i++) {
        if (this->A[i] == elem) return i;
      }
      return -1;
    }

    /**
     * @brief Find first index of search `pattern` in range `[from,to]`. Returns `-1` if none found
     * @param pattern Search pattern
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return int - Start index of found pattern or `-1`
     */
    int find (const Array<T>& pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      if (this->S == 0 || pattern.size() > this->S) return -1;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int current_search = 0;
      for (int i = b; i <= e; i++) {
        if (this->A[i] == pattern[current_search]) current_search++;
        else current_search = 0;
        if (current_search == pattern.size()) return (i + 1 - pattern.size());
      }
      return -1;
    }
    int find (const std::vector < T > &pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return find(fromVector(pattern), from, to); }
    int find (const std::list < T > &pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return find(fromList(pattern), from, to); }
    int find (const std::set < T > &pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return find(fromSet(pattern), from, to); }
    int find (std::initializer_list<T> pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return find(fromInitList(pattern), from, to); }
    int find (T* pattern, int size, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return find(fromPointer(pattern, size), from, to); }

    /**
     * @brief Find all indices of search `elem` in range `[from,to]`. Returns empty Array if none found
     * @param elem Search element
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return Array<int> - Array of indices
     */
    Array<int> findAll (const T& elem, int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      Array<int> X;
      if (this->S == 0) return X;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      for (int i = b; i <= e; i++) {
        if (this->A[i] == elem) X.append(i);
      }
      return X;
    }

    /**
     * @brief Find all indices of search `pattern` in range `[from,to]`. Returns empty Array if none found
     * @param pattern Search pattern
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return Array<int> - Starting indices of each pattern found
     */
    Array<int> findAll (const Array<T>& pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      Array<int> X;
      if (this->S == 0 || pattern.size() > this->S) return X;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int current_search = 0;
      for (int i = b; i <= e; i++) {
        if (this->A[i] == pattern[current_search]) current_search++;
        else current_search = 0;
        if (current_search == pattern.size()) {
          X.append(i + 1 - pattern.size());
          current_search = 0;
        }
      }
      return X;
    }
    Array<int> findAll (const std::vector < T > &pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return findAll(fromVector(pattern), from, to); }
    Array<int> findAll (const std::list < T > &pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return findAll(fromList(pattern), from, to); }
    Array<int> findAll (const std::set < T > &pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return findAll(fromSet(pattern), from, to); }
    Array<int> findAll (std::initializer_list<T> pattern, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return findAll(fromInitList(pattern), from, to); }
    Array<int> findAll (T* pattern, int size, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return findAll(fromPointer(pattern, size), from, to); }

    /**
     * @brief Get slice of the Array using `from` and `to` index
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return `Array<T>` Array Slice
     */
    Array<T> slice(int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      Array<T> X;
      if (this->S == 0) return X;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int s_size = e - b + 1;
      X.sizeAlloc(s_size);
      for (int i = 0; i < s_size; i++) X[i] = this->A[b + i];
      return X;
    }

    /**
     * @brief Return `Array` with unique elements
     * @return Array<T> - Unique Array
     */
    Array<T> unique () const {
      Array<T> X;
      for (int i = 0; i < this->S; i++) {
        if (!X.contains(this->A[i])) X.append(this->A[i]);
      }
      return X;
    }

    /**
     * Array functors
     */

    /**
     * @brief Execute `func` for each element of the `Array`
     * @param func Function to execute. Element is passed as an argument. Should return `void`.
     */
    void forEach (void (*func)(T elem)) const {
      for (int i = 0; i < this->S; i++) func(this->A[i]);
    }
    /**
     * @brief Execute `func` for each element of the `Array`
     * @param func Function to execute. Arguments: element, index of an element. Should return `void`.
     */
    void forEach (void (*func)(T elem, int index)) const {
      for (int i = 0; i < this->S; i++) func(this->A[i], i);
    }
    /**
     * @brief Execute `func` for each element of the `Array`
     * @param func Function to execute. Arguments: element, index of an element, array. Should return `void`.
     */
    void forEach (void (*func)(T elem, int index, const Array<T> &array)) const {
      for (int i = 0; i < this->S; i++) func(this->A[i], i, *this);
    }

    /**
     * @brief Filters `Array` elements using `func` provided
     * @param func Filtering function. Element is passed as an argument. Should return `bool`.
     * @return Array<T> Filtered `Array`
     */
    Array<T> filter (bool (*func)(T elem)) const {
      Array<T> X;
      for (int i = 0; i < this->S; i++) {
        if (func(this->A[i])) X.append(this->A[i]);
      }
      return X;
    }
    /**
     * @brief Filters `Array` elements using `func` provided
     * @param func Filtering function. Arguments: element, index of an element. Should return `bool`.
     * @return Array<T> Filtered `Array`
     */
    Array<T> filter (bool (*func)(T elem, int index)) const {
      Array<T> X;
      for (int i = 0; i < this->S; i++) {
        if (func(this->A[i], i)) X.append(this->A[i]);
      }
      return X;
    }
    /**
     * @brief Filters `Array` elements using `func` provided
     * @param func Filtering function. Arguments: element, index of an element, array. Should return `bool`.
     * @return Array<T> Filtered `Array`
     */
    Array<T> filter (bool (*func)(T elem, int index, const Array<T> &array)) const {
      Array<T> X;
      for (int i = 0; i < this->S; i++) {
        if (func(this->A[i], i, *this)) X.append(this->A[i]);
      }
      return X;
    }

    /**
     * @brief Map `Array` elements using `func` provided
     * @tparam U Destination `Array` type
     * @param func Mapping function. Element is passed as an argument. Should return `U`.
     * @return Array<U> Mapped `Array`
     */
    template <typename U>
    Array<U> map (U (*func)(T elem)) const {
      Array<U> X;
      for (int i = 0; i < this->S; i++) X.append(func(this->A[i]));
      return X;
    }
    /**
     * @brief Map `Array` elements using `func` provided
     * @tparam U Destination `Array` type
     * @param func Mapping function. Arguments: element, index of an element. Should return `U`.
     * @return Array<U> Mapped `Array`
     */
    template <typename U>
    Array<U> map (U (*func)(T elem, int index)) const {
      Array<U> X;
      for (int i = 0; i < this->S; i++) X.append(func(this->A[i], i));
      return X;
    }
    /**
     * @brief Map `Array` elements using `func` provided
     * @tparam U Destination `Array` type
     * @param func Mapping function. Arguments: element, index of an element, array. Should return `U`.
     * @return Array<U> Mapped `Array`
     */
    template <typename U>
    Array<U> map (U (*func)(T elem, int index, const Array<T> &array)) const {
      Array<U> X;
      for (int i = 0; i < this->S; i++) X.append(func(this->A[i], i, *this));
      return X;
    }

    /*
     * Converters
     */

    /**
     * @brief Return `Array` in different type `U`
     * @tparam U Destination `Array` type
     * @return Array<U> Re-typed `Array`
     */
    template <typename U>
    Array<U> astype () {
      Array<U> X;
      for (int i = 0; i < this->S; i++) X.append((U) (this->A[i]));
      return X;
    }
    
    /**
     * @brief Convert `Array` to `std::vector`
     * @return std::vector<T> 
     */
    std::vector<T> toVector () {
      std::vector<T> vec;
      for (int i = 0; i < this->S; i++) vec.push_back(this->A[i]);
      return vec;
    }

    /**
     * @brief Convert `Array` to `std::list`
     * @return std::list<T> 
     */
    std::list<T> toList () {
      std::list<T> lst;
      for (int i = 0; i < this->S; i++) lst.push_back(this->A[i]);
      return lst;
    }

    /**
     * @brief Convert `Array` to `std::set`
     * @return std::set<T> 
     */
    std::set<T> toSet () {
      std::set<T> st;
      for (int i = 0; i < this->S; i++) st.insert(this->A[i]);
      return st;
    }

    /**
     * Methods for number arrays only
     */

    /**
     * @brief Get min value of `Array` items in range `[from,to]`
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return T - min value
     */
    T min (int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      if (this->S == 0) return 0;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int len = e - b + 1;
      if (len == 0) return 0;
      T minV = this->A[b];
      for (int i = b + 1; i <= e; i++) {
        if (this->A[i] < minV) minV = this->A[i];
      }
      return minV;
    }

    /**
     * @brief Get max value of `Array` items in range `[from,to]`
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return T - max value
     */
    T max (int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      if (this->S == 0) return 0;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int len = e - b + 1;
      if (len == 0) return 0;
      T maxV = this->A[b];
      for (int i = b + 1; i <= e; i++) {
        if (this->A[i] > maxV) maxV = this->A[i];
      }
      return maxV;
    }

    /**
     * @brief Get indices of min values of `Array` items in range `[from,to]`
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return Array<int> - min values' indices
     */
    Array<int> argmin (int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      Array<int> X;
      if (this->S == 0) return X;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int len = e - b + 1;
      if (len == 0) return X;
      T minV = this->A[b];
      X.append(b);
      for (int i = b + 1; i <= e; i++) {
        if (this->A[i] < minV) {
          minV = this->A[i];
          X.clear();
          X.append(i);
        } else if (this->A[i] == minV) X.append(i);
      }
      return X;
    }

    /**
     * @brief Get indices of max values of `Array` items in range `[from,to]`
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return Array<int> - max values' indices
     */
    Array<int> argmax (int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      Array<int> X;
      if (this->S == 0) return X;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int len = e - b + 1;
      if (len == 0) return X;
      T maxV = this->A[b];
      X.append(b);
      for (int i = b + 1; i <= e; i++) {
        if (this->A[i] > maxV) {
          maxV = this->A[i];
          X.clear();
          X.append(i);
        } else if (this->A[i] == maxV) X.append(i);
      }
      return X;
    }

    /**
     * @brief Get Sum of the `Array` items in range `[from,to]`
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return T - sum
     */
    T sum (int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      if (this->S == 0) return 0;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int len = e - b + 1;
      if (len == 0) return 0;
      T s = 0;
      for (int i = b; i <= e; i++) s += this->A[i];
      return s;
    }

    /**
     * @brief Get Product of the `Array` items in range `[from,to]`
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return T - product
     */
    T product (int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      if (this->S == 0) return 0;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int len = e - b + 1;
      if (len == 0) return 0;
      T p = 1;
      for (int i = b; i <= e; i++) {
        p *= this->A[i];
        if (p == 0) return 0;
      }
      return p;
    }

    /**
     * @brief Get Arithmetic Mean of the `Array` items in range `[from,to]`
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return double - arithmetic mean
     */
    double mean (int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      if (this->S == 0) return 0;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int len = e - b + 1;
      if (len == 0) return 0;
      return (this->sum(b, e) * 1.0) / (len * 1.0);
    }

    /**
     * @brief Get Geometric Mean of the `Array` items in range `[from,to]`
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return double - geometric mean
     */
    double meanG (int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      if (this->S == 0) return 0;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int len = e - b + 1;
      if (len == 0) return 0;
      return pow(this->product(b, e) * 1.0, 1.0 / (len * 1.0));
    }

    /**
     * @brief Get Harmonic Mean of the `Array` items in range `[from,to]`
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return double - harmonic mean
     */
    double meanH (int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      if (this->S == 0) return 0;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int len = e - b + 1;
      if (len == 0) return 0;
      double rs = 0.0;
      for (int i = b; i <= e; i++) rs += (1.0 / (1.0 * this->A[i]));
      return (len * 1.0) / rs;
    }

    /**
     * @brief Get Weighted Mean of the `Array` items in range `[from,to]` using `weights` array
     * @param weights Weights Array. If shorter than `[from,to]` range, weights for remaining elements will be `0`.
     * If longer than `[from,to]` range, remaining weights will not be used.
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return double - Weighted mean
     */
    double weightedMean (Array<double> weights, int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      if (this->S == 0 || weights.size() == 0) return 0;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int len = e - b + 1;
      if (len == 0) return 0;
      double s = 0.0, ws = 0.0;
      for (int i = b; i <= e; i++) {
        int wIdx = i - b;
        if (wIdx >= weights.size()) break;
        s += (this->A[i] * weights[wIdx]);
        ws += weights[wIdx];
      }
      return s / ws;
    }
    double weightedMean (const std::vector < double > &weights, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return weightedMean(Array<double>::fromVector(weights), from, to); }
    double weightedMean (const std::list < double > &weights, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return weightedMean(Array<double>::fromList(weights), from, to); }
    double weightedMean (const std::set < double > &weights, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return weightedMean(Array<double>::fromSet(weights), from, to); }
    double weightedMean (std::initializer_list<double> weights, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return weightedMean(Array<double>::fromInitList(weights), from, to); }
    double weightedMean (double* weights, int size, int from = ARRAY_BEGIN, int to = ARRAY_END) const { return weightedMean(Array<double>::fromPointer(weights, size), from, to); }

    /**
     * @brief Get Variance of the `Array` items in range `[from,to]`
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return double - variance
     */
    double variance (int from = ARRAY_BEGIN, int to = ARRAY_END) const {
      if (this->S == 0) return 0;
      int b = idx(from), e = (to == ARRAY_END ? this->S - 1 : idx(to));
      this->checkRange(b, e);
      int len = e - b + 1;
      if (len <= 1) return 0;
      double m = this->mean(b, e), s = 0.0;
      for (int i = b; i <= e; i++) { s += pow(this->A[i] - m, 2.0); }
      return s / (this->S - 1.0);
    }

    /**
     * @brief Get Standard Deviation of the `Array` items in range `[from,to]`
     * @param from Default 0 (Inclusive)
     * @param to Default Last Index (Inclusive)
     * @return double - standard deviation
     */
    double stdev (int from = ARRAY_BEGIN, int to = ARRAY_END) const { return sqrt(this->variance(from, to)); }

    /*
     * OPERATORS
     */
    // Copy assignment operator
    Array& operator=(const Array& other) {
      if (this != &other) {
        free(this->A);
        this->S = other.S;
        if (this->S > 0) {
          this->A = (T*) malloc(this->S * sizeof(T));
          for (int i = 0; i < S; i++) this->A[i] = other.A[i];
        } else this->A = nullptr;
      }
      return *this;
    }
    // Move assignment operator
    Array& operator=(Array&& other) noexcept {
      if (this != &other) {
        free(this->A);
        this->S = other.S;
        this->A = other.A;
        other.S = 0;
        other.A = nullptr;
      }
      return *this;
    }

    /*
     * Arithmetic operations with constants (keeping the Array)
     */
    Array<T> operator+ (const T& number) const {
      Array <T> X;
      X.sizeAlloc(this->S);
      for (int i = 0; i < this->S; i++) X[i] = this->A[i] + number;
      return X;
    }
    Array<T> operator- (const T& number) const {
      Array <T> X;
      X.sizeAlloc(this->S);
      for (int i = 0; i < this->S; i++) X[i] = this->A[i] - number;
      return X;
    }
    Array<T> operator* (const T& number) const {
      Array <T> X;
      X.sizeAlloc(this->S);
      for (int i = 0; i < this->S; i++) X[i] = (this->A[i] * number);
      return X;
    }
    Array<T> operator/ (const T& number) const {
      Array <T> X;
      X.sizeAlloc(this->S);
      for (int i = 0; i < this->S; i++) X[i] = (this->A[i] / number);
      return X;
    }
    Array<T> operator% (const T& number) const {
      Array <T> X;
      X.sizeAlloc(this->S);
      for (int i = 0; i < this->S; i++) X[i] = (this->A[i] % number);
      return X;
    }

    /*
     * Arithmetic operations with arrays (keeping both arrays)
     */
    Array<T> operator+ (const Array<T>& array) const {
      int max_size = MAX_S(this->S, array.size());
      Array <T> X;
      X.sizeAlloc(max_size);
      for (int i = 0; i < this->S; i++) X[i] += this->A[i];
      for (int i = 0; i < array.size(); i++) X[i] += array[i];
      return X;
    }
    Array<T> operator+ (const std::vector <T> &STL_Vector) const { return this->operator+(Array::fromVector(STL_Vector)); }
    Array<T> operator+ (const std::list <T> &STL_List) const { return this->operator+(Array::fromList(STL_List)); }
    Array<T> operator+ (const std::set <T> &STL_Set) const { return this->operator+(Array::fromSet(STL_Set)); }
    Array<T> operator+ (const std::initializer_list <T> &STL_InitList) const { return this->operator+(Array::fromInitList(STL_InitList)); }
    Array<T> operator- (const Array<T>& array) const {
      int max_size = MAX_S(this->S, array.size());
      Array <T> X;
      X.sizeAlloc(max_size);
      for (int i = 0; i < this->S; i++) X[i] += this->A[i];
      for (int i = 0; i < array.size(); i++) X[i] -= array[i];
      return X;
    }
    Array<T> operator- (const std::vector <T> &STL_Vector) const { return this->operator-(Array::fromVector(STL_Vector)); }
    Array<T> operator- (const std::list <T> &STL_List) const { return this->operator-(Array::fromList(STL_List)); }
    Array<T> operator- (const std::set <T> &STL_Set) const { return this->operator-(Array::fromSet(STL_Set)); }
    Array<T> operator- (const std::initializer_list <T> &STL_InitList) const { return this->operator-(Array::fromInitList(STL_InitList)); }
    Array<T> operator* (const Array<T>& array) const {
      int max_size = MAX_S(this->S, array.size());
      Array <T> X;
      X.sizeAlloc(max_size);
      for (int i = 0; i < this->S; i++) X[i] += this->A[i];
      for (int i = 0; i < array.size(); i++) X[i] *= array[i];
      return X;
    }
    Array<T> operator* (const std::vector <T> &STL_Vector) const { return this->operator*(Array::fromVector(STL_Vector)); }
    Array<T> operator* (const std::list <T> &STL_List) const { return this->operator*(Array::fromList(STL_List)); }
    Array<T> operator* (const std::set <T> &STL_Set) const { return this->operator*(Array::fromSet(STL_Set)); }
    Array<T> operator* (const std::initializer_list <T> &STL_InitList) const { return this->operator*(Array::fromInitList(STL_InitList)); }
    Array<T> operator/ (const Array<T>& array) const {
      int max_size = MAX_S(this->S, array.size());
      Array <T> X;
      X.sizeAlloc(max_size);
      for (int i = 0; i < this->S; i++) X[i] += this->A[i];
      for (int i = 0; i < array.size(); i++) X[i] /= array[i];
      return X;
    }
    Array<T> operator/ (const std::vector <T> &STL_Vector) const { return this->operator/(Array::fromVector(STL_Vector)); }
    Array<T> operator/ (const std::list <T> &STL_List) const { return this->operator/(Array::fromList(STL_List)); }
    Array<T> operator/ (const std::set <T> &STL_Set) const { return this->operator/(Array::fromSet(STL_Set)); }
    Array<T> operator/ (const std::initializer_list <T> &STL_InitList) const { return this->operator/(Array::fromInitList(STL_InitList)); }
    Array<T> operator% (const Array<T>& array) const {
      int max_size = MAX_S(this->S, array.size());
      Array <T> X;
      X.sizeAlloc(max_size);
      for (int i = 0; i < this->S; i++) X[i] += this->A[i];
      for (int i = 0; i < array.size(); i++) X[i] %= array[i];
      return X;
    }
    Array<T> operator% (const std::vector <T> &STL_Vector) const { return this->operator%(Array::fromVector(STL_Vector)); }
    Array<T> operator% (const std::list <T> &STL_List) const { return this->operator%(Array::fromList(STL_List)); }
    Array<T> operator% (const std::set <T> &STL_Set) const { return this->operator%(Array::fromSet(STL_Set)); }
    Array<T> operator% (const std::initializer_list <T> &STL_InitList) const { return this->operator%(Array::fromInitList(STL_InitList)); }

    /*
     * Arithmetic operations with constants (modifying the Array)
     */
    Array<T> operator+= (const T& number) {
      for (int i = 0; i < this->S; i++) this->A[i] += number;
      return *this;
    }
    Array<T> operator-= (const T& number) {
      for (int i = 0; i < this->S; i++) this->A[i] -= number;
      return *this;
    }
    Array<T> operator*= (const T& number) {
      for (int i = 0; i < this->S; i++) this->A[i] *= number;
      return *this;
    }
    Array<T> operator/= (const T& number) {
      for (int i = 0; i < this->S; i++) this->A[i] /= number;
      return *this;
    }
    Array<T> operator%= (const T& number) {
      for (int i = 0; i < this->S; i++) this->A[i] %= number;
      return *this;
    }

    
    /*
     * Arithmetic operations with other arrays (modifying the first Array)
     */
    Array<T> operator+= (const Array<T> &array) {
      for (int i = this->S; i < array.size(); i++) this->append((T)(0));
      for (int i = 0; i < array.size(); i++) this->A[i] += array[i];
      return *this;
    }
    Array<T> operator+= (const std::vector <T> &STL_Vector) { return this->operator+=(Array::fromVector(STL_Vector)); }
    Array<T> operator+= (const std::list <T> &STL_List) { return this->operator+=(Array::fromList(STL_List)); }
    Array<T> operator+= (const std::set <T> &STL_Set) { return this->operator+=(Array::fromSet(STL_Set)); }
    Array<T> operator+= (const std::initializer_list <T> &STL_InitList) { return this->operator+=(Array::fromInitList(STL_InitList)); }
    Array<T> operator-= (const Array<T> &array) {
      for (int i = this->S; i < array.size(); i++) this->append((T)(0));
      for (int i = 0; i < array.size(); i++) this->A[i] -= array[i];
      return *this;
    }
    Array<T> operator-= (const std::vector <T> &STL_Vector) { return this->operator-=(Array::fromVector(STL_Vector)); }
    Array<T> operator-= (const std::list <T> &STL_List) { return this->operator-=(Array::fromList(STL_List)); }
    Array<T> operator-= (const std::set <T> &STL_Set) { return this->operator-=(Array::fromSet(STL_Set)); }
    Array<T> operator-= (const std::initializer_list <T> &STL_InitList) { return this->operator-=(Array::fromInitList(STL_InitList)); }
    Array<T> operator*= (const Array<T> &array) {
      for (int i = this->S; i < array.size(); i++) this->append((T)(0));
      for (int i = 0; i < array.size(); i++) this->A[i] *= array[i];
      return *this;
    }
    Array<T> operator*= (const std::vector <T> &STL_Vector) { return this->operator*=(Array::fromVector(STL_Vector)); }
    Array<T> operator*= (const std::list <T> &STL_List) { return this->operator*=(Array::fromList(STL_List)); }
    Array<T> operator*= (const std::set <T> &STL_Set) { return this->operator*=(Array::fromSet(STL_Set)); }
    Array<T> operator*= (const std::initializer_list <T> &STL_InitList) { return this->operator*=(Array::fromInitList(STL_InitList)); }
    Array<T> operator/= (const Array<T> &array) {
      for (int i = this->S; i < array.size(); i++) this->append((T)(0));
      for (int i = 0; i < array.size(); i++) this->A[i] /= array[i];
      return *this;
    }
    Array<T> operator/= (const std::vector <T> &STL_Vector) { return this->operator/=(Array::fromVector(STL_Vector)); }
    Array<T> operator/= (const std::list <T> &STL_List) { return this->operator/=(Array::fromList(STL_List)); }
    Array<T> operator/= (const std::set <T> &STL_Set) { return this->operator/=(Array::fromSet(STL_Set)); }
    Array<T> operator/= (const std::initializer_list <T> &STL_InitList) { return this->operator/=(Array::fromInitList(STL_InitList)); }
    Array<T> operator%= (const Array<T> &array) {
      for (int i = this->S; i < array.size(); i++) this->append((T)(0));
      for (int i = 0; i < array.size(); i++) this->A[i] %= array[i];
      return *this;
    }
    Array<T> operator%= (const std::vector <T> &STL_Vector) { return this->operator%=(Array::fromVector(STL_Vector)); }
    Array<T> operator%= (const std::list <T> &STL_List) { return this->operator%=(Array::fromList(STL_List)); }
    Array<T> operator%= (const std::set <T> &STL_Set) { return this->operator%=(Array::fromSet(STL_Set)); }
    Array<T> operator%= (const std::initializer_list <T> &STL_InitList) { return this->operator%=(Array::fromInitList(STL_InitList)); }

    /*
     * Boolean operators - comparing to constant
     */
    Array<bool> operator== (const T& val) const {
      Array<bool> X(this->S);
      for (int i = 0; i < this->S; i++) X[i] = (this->A[i] == val);
      return X;
    }
    Array<bool> operator>= (const T& val) const {
      Array<bool> X(this->S);
      for (int i = 0; i < this->S; i++) X[i] = (this->A[i] >= val);
      return X;
    }
    Array<bool> operator<= (const T& val) const {
      Array<bool> X(this->S);
      for (int i = 0; i < this->S; i++) X[i] = (this->A[i] <= val);
      return X;
    }
    Array<bool> operator> (const T& val) const {
      Array<bool> X(this->S);
      for (int i = 0; i < this->S; i++) X[i] = (this->A[i] > val);
      return X;
    }
    Array<bool> operator< (const T& val) const {
      Array<bool> X(this->S);
      for (int i = 0; i < this->S; i++) X[i] = (this->A[i] < val);
      return X;
    }
    Array<bool> operator!= (const T& val) const {
      Array<bool> X(this->S);
      for (int i = 0; i < this->S; i++) X[i] = (this->A[i] != val);
      return X;
    }

    /* 
     * Boolean operators - comparing to another `Array`
     */
    Array<bool> operator== (const Array<T> &array) const {
      int max_size = MAX_S(this->S, array.size());
      Array<bool> X(max_size);
      for (int i = 0; i < max_size; i++) {
        X[i] = (i >= this->S || i >= array.size()) ? false : (this->A[i] == array[i]);
      }
      return X;
    }
    Array<bool> operator== (const std::vector <T> &STL_Vector) const { return this->operator==(Array::fromVector(STL_Vector)); }
    Array<bool> operator== (const std::list <T> &STL_List) const { return this->operator==(Array::fromList(STL_List)); }
    Array<bool> operator== (const std::set <T> &STL_Set) const { return this->operator==(Array::fromSet(STL_Set)); }
    Array<bool> operator== (const std::initializer_list <T> &STL_InitList) const { return this->operator==(Array::fromInitList(STL_InitList)); }
    Array<bool> operator>= (const Array<T> &array) {
      int max_size = MAX_S(this->S, array.size());
      Array<bool> X(max_size);
      for (int i = 0; i < max_size; i++) {
        X[i] = (i >= this->S || i >= array.size()) ? false : (this->A[i] >= array[i]);
      }
      return X;
    }
    Array<bool> operator>= (const std::vector <T> &STL_Vector) const { return this->operator>=(Array::fromVector(STL_Vector)); }
    Array<bool> operator>= (const std::list <T> &STL_List) const { return this->operator>=(Array::fromList(STL_List)); }
    Array<bool> operator>= (const std::set <T> &STL_Set) const { return this->operator>=(Array::fromSet(STL_Set)); }
    Array<bool> operator>= (const std::initializer_list <T> &STL_InitList) const { return this->operator>=(Array::fromInitList(STL_InitList)); }
    Array<bool> operator<= (const Array<T> &array) {
      int max_size = MAX_S(this->S, array.size());
      Array<bool> X(max_size);
      for (int i = 0; i < max_size; i++) {
        X[i] = (i >= this->S || i >= array.size()) ? false : (this->A[i] <= array[i]);
      }
      return X;
    }
    Array<bool> operator<= (const std::vector <T> &STL_Vector) const { return this->operator<=(Array::fromVector(STL_Vector)); }
    Array<bool> operator<= (const std::list <T> &STL_List) const { return this->operator<=(Array::fromList(STL_List)); }
    Array<bool> operator<= (const std::set <T> &STL_Set) const { return this->operator<=(Array::fromSet(STL_Set)); }
    Array<bool> operator<= (const std::initializer_list <T> &STL_InitList) const { return this->operator<=(Array::fromInitList(STL_InitList)); }
    Array<bool> operator> (const Array<T> &array) {
      int max_size = MAX_S(this->S, array.size());
      Array<bool> X(max_size);
      for (int i = 0; i < max_size; i++) {
        X[i] = (i >= this->S || i >= array.size()) ? false : (this->A[i] > array[i]);
      }
      return X;
    }
    Array<bool> operator> (const std::vector <T> &STL_Vector) const { return this->operator>(Array::fromVector(STL_Vector)); }
    Array<bool> operator> (const std::list <T> &STL_List) const { return this->operator>(Array::fromList(STL_List)); }
    Array<bool> operator> (const std::set <T> &STL_Set) const { return this->operator>(Array::fromSet(STL_Set)); }
    Array<bool> operator> (const std::initializer_list <T> &STL_InitList) const { return this->operator>(Array::fromInitList(STL_InitList)); }
    Array<bool> operator< (const Array<T> &array) {
      int max_size = MAX_S(this->S, array.size());
      Array<bool> X(max_size);
      for (int i = 0; i < max_size; i++) {
        X[i] = (i >= this->S || i >= array.size()) ? false : (this->A[i] < array[i]);
      }
      return X;
    }
    Array<bool> operator< (const std::vector <T> &STL_Vector) const { return this->operator<(Array::fromVector(STL_Vector)); }
    Array<bool> operator< (const std::list <T> &STL_List) const { return this->operator<(Array::fromList(STL_List)); }
    Array<bool> operator< (const std::set <T> &STL_Set) const { return this->operator<(Array::fromSet(STL_Set)); }
    Array<bool> operator< (const std::initializer_list <T> &STL_InitList) const { return this->operator<(Array::fromInitList(STL_InitList)); }
    Array<bool> operator!= (const Array<T> &array) {
      int max_size = MAX_S(this->S, array.size());
      Array<bool> X(max_size);
      for (int i = 0; i < max_size; i++) {
        X[i] = (i >= this->S || i >= array.size()) ? false : (this->A[i] != array[i]);
      }
      return X;
    }
    Array<bool> operator!= (const std::vector <T> &STL_Vector) const { return this->operator!=(Array::fromVector(STL_Vector)); }
    Array<bool> operator!= (const std::list <T> &STL_List) const { return this->operator!=(Array::fromList(STL_List)); }
    Array<bool> operator!= (const std::set <T> &STL_Set) const { return this->operator!=(Array::fromSet(STL_Set)); }
    Array<bool> operator!= (const std::initializer_list <T> &STL_InitList) const { return this->operator!=(Array::fromInitList(STL_InitList)); }

    /**
     * Boolean operators for Array Masks (Keeping inital Array Masks)
     */
    Array<bool> operator! () const {
      Array<bool> X(this->S);
      for (int i = 0; i < this->S; i++) X[i] = !(this->A[i]);
      return X;
    }
    Array<bool> operator| (const Array<bool> &mask) const {
      int max_size = MAX_S(this->S, mask.size());
      Array<bool> X(max_size);
      for (int i = 0; i < this->S; i++) X[i] = (bool) A[i];
      for (int i = 0; i < mask.size(); i++) X[i] = (bool) X[i] | (bool) mask[i];
      return X;
    }
    Array<bool> operator| (const std::vector<bool> &mask) const { return this->operator|(Array<bool>::fromVector(mask)); }
    Array<bool> operator| (const std::list<bool> &mask) const { return this->operator|(Array<bool>::fromList(mask)); }
    Array<bool> operator| (const std::set<bool> &mask) const { return this->operator|(Array<bool>::fromSet(mask)); }
    Array<bool> operator| (const std::initializer_list<bool> &mask) const { return this->operator|(Array<bool>::fromInitList(mask)); }
    Array<bool> operator& (const Array<bool> &mask) const {
      int max_size = MAX_S(this->S, mask.size());
      Array<bool> X(max_size);
      for (int i = 0; i < this->S; i++) X[i] = (bool) A[i];
      for (int i = 0; i < mask.size(); i++) X[i] = (bool) X[i] & (bool) mask[i];
      return X;
    }
    Array<bool> operator& (const std::vector<bool> &mask) const { return this->operator&(Array<bool>::fromVector(mask)); }
    Array<bool> operator& (const std::list<bool> &mask) const { return this->operator&(Array<bool>::fromList(mask)); }
    Array<bool> operator& (const std::set<bool> &mask) const { return this->operator&(Array<bool>::fromSet(mask)); }
    Array<bool> operator& (const std::initializer_list<bool> &mask) const { return this->operator&(Array<bool>::fromInitList(mask)); }
    Array<bool> operator^ (const Array<bool> &mask) const {
      int max_size = MAX_S(this->S, mask.size());
      Array<bool> X(max_size);
      for (int i = 0; i < this->S; i++) X[i] = (bool) A[i];
      for (int i = 0; i < mask.size(); i++) X[i] = (bool) X[i] ^ (bool) mask[i];
      return X;
    }
    Array<bool> operator^ (const std::vector<bool> &mask) const { return this->operator^(Array<bool>::fromVector(mask)); }
    Array<bool> operator^ (const std::list<bool> &mask) const { return this->operator^(Array<bool>::fromList(mask)); }
    Array<bool> operator^ (const std::set<bool> &mask) const { return this->operator^(Array<bool>::fromSet(mask)); }
    Array<bool> operator^ (const std::initializer_list<bool> &mask) const { return this->operator^(Array<bool>::fromInitList(mask)); }

    /**
     * Boolean operators with `bool` constant for Array Mask (Keeping inital Array Mask)
     */
    Array<bool> operator| (bool val) const {
      Array<bool> X(this->S);
      for (int i = 0; i < this->S; i++) X[i] = (bool) A[i] | val;
      return X;
    }
    Array<bool> operator& (bool val) const {
      Array<bool> X(this->S);
      for (int i = 0; i < this->S; i++) X[i] = (bool) A[i] & val;
      return X;
    }
    Array<bool> operator^ (bool val) const {
      Array<bool> X(this->S);
      for (int i = 0; i < this->S; i++) X[i] = (bool) A[i] ^ val;
      return X;
    }

    /**
     * Boolean operators for Array Masks (modifying initial Array Mask)
     */
    Array<bool> operator|= (const Array<bool> &mask) {
      int max_size = MAX_S(this->S, mask.size());
      for (int i = this->S; i < max_size; i++) this->append(false);
      for (int i = 0; i < mask.size(); i++) this->A[i] = (bool) A[i] | (bool) mask[i];
      return *this;
    }
    Array<bool> operator|= (const std::vector<bool> &mask) { return this->operator|=(Array<bool>::fromVector(mask)); }
    Array<bool> operator|= (const std::list<bool> &mask) { return this->operator|=(Array<bool>::fromList(mask)); }
    Array<bool> operator|= (const std::set<bool> &mask) { return this->operator|=(Array<bool>::fromSet(mask)); }
    Array<bool> operator|= (const std::initializer_list<bool> &mask) { return this->operator|=(Array<bool>::fromInitList(mask)); }
    Array<bool> operator&= (const Array<bool> &mask) {
      int max_size = MAX_S(this->S, mask.size());
      for (int i = this->S; i < max_size; i++) this->append(false);
      for (int i = 0; i < mask.size(); i++) this->A[i] = (bool) A[i] & (bool) mask[i];
      return *this;
    }
    Array<bool> operator&= (const std::vector<bool> &mask) { return this->operator&=(Array<bool>::fromVector(mask)); }
    Array<bool> operator&= (const std::list<bool> &mask) { return this->operator&=(Array<bool>::fromList(mask)); }
    Array<bool> operator&= (const std::set<bool> &mask) { return this->operator&=(Array<bool>::fromSet(mask)); }
    Array<bool> operator&= (const std::initializer_list<bool> &mask) { return this->operator&=(Array<bool>::fromInitList(mask)); }
    Array<bool> operator^= (const Array<bool> &mask) {
      int max_size = MAX_S(this->S, mask.size());
      for (int i = this->S; i < max_size; i++) this->append(false);
      for (int i = 0; i < mask.size(); i++) this->A[i] = (bool) A[i] ^ (bool) mask[i];
      return *this;
    }
    Array<bool> operator^= (const std::vector<bool> &mask) { return this->operator^=(Array<bool>::fromVector(mask)); }
    Array<bool> operator^= (const std::list<bool> &mask) { return this->operator^=(Array<bool>::fromList(mask)); }
    Array<bool> operator^= (const std::set<bool> &mask) { return this->operator^=(Array<bool>::fromSet(mask)); }
    Array<bool> operator^= (const std::initializer_list<bool> &mask) { return this->operator^=(Array<bool>::fromInitList(mask)); }
};

#endif // !DINGO_ARRAY_H
