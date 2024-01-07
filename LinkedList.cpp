#include <stdio.h>
#include <assert.h>

template <typename T>
class Node {
    public:
        T value;
        Node<T> *next;

        Node(T item) {
            this->value = item;
            this->next = NULL;
        }

        // Copy constructor
        Node(const Node<T>& node)
        {
            this->value = node.value;
            this->next = node.next;
        }

        // Deletes the attributes of the Node and free the memory occupied by the itself
        ~Node() {}
};

template<typename T>
class LinkedList {
    private:
        unsigned int length;
        Node<T> *head;
        Node<T> *tail;
        void assert_index_not_out_of_bounds(unsigned int index);
        void merge_sort(T *list, unsigned int begin, unsigned int end, int (*compareTo) (T, T));
        void merge(T* list, unsigned int begin, unsigned int middle, unsigned int end, int (*compareTo) (T,T));
        void bubble_sort(int (*compareTo) (T, T));

    public:
        LinkedList();
        LinkedList(void *array, size_t size);
        ~LinkedList();
        unsigned int len();
        void append(T item);
        void append(void *array, size_t size);
        void push(T item);
        T pop();
        T get(unsigned int index);
        void remove(unsigned int index);
        void clear();
        int index(T item, bool (*equals) (T, T));
        void sort(int (*compareTo) (T, T));
};

// --------------------- List implementation --------------------- //
template <typename T>
void LinkedList<T>::assert_index_not_out_of_bounds(unsigned int index) {
    assert(0 <= index && index < (this->length));
}

/**
 * Create new empty list.
 *
 * @return LinkedList<T>
 */
template <typename T>
LinkedList<T>::LinkedList() {
    this->head = NULL;
    this->tail = NULL;
    this->length = 0;
}



template <typename T>
LinkedList<T>::~LinkedList() {    
    // Iterates over all nodes in order to free the memory allocated for each one
    if (this->length > 0) {
        Node<T> *current = this->head;
        Node<T> *next = this->head->next;

        while (true) {
            delete current;
            current = next;
            if (current == NULL) break;
            next = next->next;
        }
    }

    // Finally the memory allocated for the list {head, tail and length} will be free   
}

/**
 * Return the numbers of elements in the list.
 *
 * @return number of elements
 */
template <typename T>
unsigned int LinkedList<T>::len() {
    return this->length;
}

/**
 * Insert the new item at the end of the list.
 *
 * @param item Item to insert
 */
template <typename T>
void LinkedList<T>::append(T item) {
    Node<T> *new_node = new Node<T>(item);

    if (this->length == 0) {
        this->head = new_node;
        this->tail = new_node;
    } else {
        this->tail->next = new_node;
        this->tail = new_node;
    }

    this->length++;
}

/**
 * Create new list inserting the values on the array
 *
 *
 * @param array Pointer to the array.
 * @param size Size of the pointer to one element of the array.
 */
template <typename T>
LinkedList<T>::LinkedList(void *array, size_t size) {
    // Init empty list
    this->head = NULL;
    this->tail = NULL;
    this->length = 0;

    this->append(array, size);  
}

/**
 * Insert elements of the array at the end of the list.
 *
 * @param array Pointer to the array.
 * @param size Size of the pointer to one element of the array.
 */
template <typename T>
void LinkedList<T>::append(void *array, size_t size){
    T *arr = (T*) array;

    // Insert elements of the array in the list
    for (size_t i = 0; i < size; i++){
        this->append(arr[i]);
    }
}

/**
 * Insert new element at the begining of the list
 *
 * @param item Item to insert
 */
template <typename T>
void LinkedList<T>::push(T item) {
    Node<T> *node = new Node<T>(item);
    if(this->length == 0) {
        this->head = node;
        this->tail = node;
    } else {
        node->next = this->head;
        this->head = node;
    }

    this->length++;
}

/**
 * Remove and return the first element of the list.
 * 
 * This operation raise an error if the list is empty.
 *
 * @return T: first item.
 */
template <typename T>
T LinkedList<T>::pop(){
    assert(this->length > 0);

    // Store first node in order to return the value
    Node<T> *aux = this->head;

    // Set the head to the item next to the first
    this->head = this->head->next;

    // Decrement the length of the list
    this->length--;

    // Get the value
    T item = aux->value;

    // Clean the memory taken by the node
    delete aux;

    return item;
}

/**
 * Return the i-item.
 * 
 * This function iterate over the list until the i-element is found. The functions raise
 * an error if the index is out of bounds.
 *
 * @param index
 * @return T: i-elemen
 */
template <typename T>
T LinkedList<T>::get(unsigned int index) {
    // Ensure index is not out of bounds
    this->assert_index_not_out_of_bounds(index);

    Node<T> *aux = NULL;

    if (index == 0) {
        aux = this->head;
    } else if (index == (this->length - 1)) {
        aux = this->tail;
    } else {
        // Iterate over nodes util points to the i-node
        Node<T> *current = this->head->next;
        for (int i = 1; i < index; i++) {
            current = current ->next;
        }
        aux = current;
    }

    return aux->value;

}

/**
 * Remove the i-element
 * 
 * This function iterate over the list until the i-element is found and remove it. The functions raise
 * an error if the index is out of bounds.
 * 
 * @param index
 */
template <typename T>
void LinkedList<T>::remove(unsigned int index) {
    this->assert_index_not_out_of_bounds(index);

    Node<T> *node = this->head;
    Node<T> *before = NULL;
    for (unsigned int i = 0; i < index; i++) {
        before = node;
        node = node->next;
    }

    // First node
    if (before == NULL) {
        this->head = this->head->next;
    } else {
        before->next = node->next;
    }
    delete node;

    this->length--;
}

/**
 * Clear the list
 * 
 * This function iterate over the list clearing it.
 * 
 */
template <typename T>
void LinkedList<T>::clear() {
    if(this->length > 0){
        Node<T> *node = this->head;
        Node<T> *before = NULL;
        for (unsigned int i = 0; i < this->length; i++) {
            before = node;
            node = node->next;
            delete before;
        }
        delete node;

        this->head = NULL;
        this->tail = NULL;
        this->length = 0;
    }
}

/**
 * Return the index of the given value if exists, otherwise return -1
 *
 * @param item Item to find
 * @param compareTo Function which accepts two values to compare, return true if are equals, else false
 */
template <typename T>
int LinkedList<T>::index(T item, bool (*equals) (T, T)) {
    int index = -1;
    Node<T> *current = this->head;
    for (int i = 0; i < this->length; i++) {
        if (equals(current->value, item)) {
            index = i;
            break;
        }
        current = current->next;
    }

    return index;
}

template <typename T>
void swap(Node<T> *n1, Node<T> *n2) {
    T temp = n1->value;
    n1->value = n2->value;
    n2->value = temp;
}


template <typename T>
void LinkedList<T>::bubble_sort(int (*compareTo) (T, T)) {
    // List is already sorted
    if(this->length <= 1) {
        return;
    }

    // Apply bubble algorithm to sort the list
    Node<T> *n1 = this->head;
    Node<T> *n2 = this->head->next;

    bool is_sorted = false;
    bool swapped = false;

    while (!is_sorted) {
        
        if (compareTo(n1->value, n2->value) > 0) {
            swapped = true;
            swap(n1, n2);
        }

        n1 = n1->next;
        n2 = n1->next;

        if(n2 == NULL) {
            if (!swapped) {
                is_sorted = true;
            }
            
            n1 = this->head;
            n2 = n1->next;

            swapped = false;

        }
    }
}


template <typename T>
void LinkedList<T>::merge(T* list, unsigned int begin, unsigned int middle, unsigned int end, int (*compareTo) (T, T)) {
    // Left list goes from [begin, middle]
    // Right list goes from [middle + 1, end]
    unsigned int left_size = middle - begin + 1;
    unsigned int right_size = end - middle;
    unsigned int greater_size = (left_size > right_size) ? left_size : right_size;

    // Create a temp left and right arrays
    T *left = new T [left_size];
    T *right = new T [right_size];

    // Copy the data from 'list' into the the temp arrays
    for (unsigned int i = 0; i < greater_size; i++) {
        if (i < left_size) {
            left[i] = list[begin+i];
        }

        if (i < right_size) {
            right[i] = list[middle+1+i];
        }

    }

    unsigned int left_i = 0;
    unsigned int right_i = 0;
    unsigned int list_index = begin;

    // Merge the list
    while ((left_i < left_size) && (right_i < right_size)) {
        int left_item = left[left_i];
        int right_item = right[right_i];

        if (compareTo(left_item,right_item) < 0) {
            list[list_index] = left_item;
            left_i++;
        } else {
            list[list_index] = right_item;
            right_i++;
        }

        list_index++;
    }

    // Put the rest of the elements from one of the side into the list
    while (left_i < left_size) {
        list[list_index] = left[left_i];
        left_i++;
        list_index++;
    }

    while (right_i < right_size) {
        list[list_index] = right[right_i];
        right_i++;
        list_index++;
    }

    // Delete temporal left and right arrays
    delete [] left;
    delete [] right;
}

/**
 * Sort the list using the merge sort algorithm.
 *
 * @param list List to sort
 * @param begin index where the list starts
 * @param right index where the list finish starts
 */
template <typename T>
void LinkedList<T>::merge_sort(T *list, unsigned int begin, unsigned int end, int (*compareTo) (T, T)) {
    // Stop condition
    if (begin >= end) {
        return;
    }

    // Calculate the middle point
    unsigned int middle = (begin + end) / 2;

    // Sort left side from [begin, middel]
    merge_sort(list, begin, middle, compareTo);

    // Sort right side from [middle + 1, end]
    merge_sort(list, middle + 1, end, compareTo);

    // merge both sides
    merge(list, begin, middle, end, compareTo);
}


/**
 * Sort the list.
 * 
 * The list is sorted applying the merge-sort algorithm.
 *
 * @param compareTo Function which must receive two values of the type of the elements of the list.
 * The function should return 3 different values:
 * (-1) -> First item is lower than second.
 * (0) -> The elements are equals.
 * (1) -> First item is greater than second.
 */
template <typename T>
void LinkedList<T>::sort(int (*compareTo) (T, T)) {
    if (this->length <= 1) return;

    // Temporal list array to store all the values from the linked list
    T *list = new T [this->length];

    Node<T> *current = this->head;
    for (unsigned int i = 0; i < this->length; i++) {
        list[i] = current->value;
        current = current->next;
    }

    merge_sort(list, 0, this->length-1, compareTo);


    // list is ordered, set the values in the linkedlist
    current = this->head;
    for (unsigned int i = 0; i < this->length; i++) {
        current->value = list[i];
        current = current->next;
    }

    // Delete the memory used for the temporal list array
    delete [] list;
}