# LinkedList
LinkedList implementation for c++.

The code of the library is in the **LinkedList.cpp file**.


> ## Documentation
>
> ### Objects
> - LinkedList<T>

> ### Functions
> - `LinkedList<T>::LinkedList()`\
>   Create new empty list.
> 
> - `LinkedList<T>::LinkedList(void *array, size_t size)`\
>   Create new empty list an insert data from array.
> 
> - `LinkedList<T>::unsigned int len()`\
>   get the number of items.
> 
> - `LinkedList<T>::void append(T item)`\
>   Insert new element at the end
> 
> - `LinkedList<T>::void append(void *array, size_t size)`\
>   Insert all the elements in the given array at the end of the list.
> 
> - `LinkedList<T>::void push(T item)`\
>   Insert new item at the beginning.
> 
> - `LinkedList<T>::T pop()`\
>   Removes the first item an return it.
> 
> - `LinkedList<T>::T get(unsigned int index)`\
>   Returns the i-element.
> 
> - `LinkedList<T>::void remove(unsigned int index)`\
>   Removes the i-element.
> 
> - `LinkedList<T>::int index(T item, bool (*equals)` (T, T))\
>   Returns the index of the element. to find, or -1 if not found.
> 
> - `LinkedList<T>::void sort(int (*compareTo) (T, T))`\
>   Sort applying 'merge sort' algorithm.
###