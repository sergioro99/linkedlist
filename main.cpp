#include <stdio.h>
#include "LinkedList.cpp"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

void print(LinkedList<int> *ls) {
    printf("(");
    for (int i = 0; i < ls->len(); i++) {
        printf("%i", ls->get(i));
        if (i == (ls->len() - 1)) {
            printf(")\n");
        } else {
            printf(", ");
        }
    }
}

void fill_list(LinkedList<int> *ls, int n) {
    srand(time(NULL));   // Initialization, should only be called once.
    for (int i = 0; i < n; i++) {
        int r = rand() % n;      // Returns a pseudo-random integer between 0 and RAND_MAX.
        ls->append(r);
    }
}

bool int_equals(int x1, int x2) {
    return x1 == x2;
}

int int_compareTo(int a, int b) {
    if (a > b) return 1;
    if (b > a) return -1;
    return 0;
}

int main() {
    clock_t start, end;
    const int N = 1000;
    LinkedList<int> *ls = new LinkedList<int>();
    
    fill_list(ls, N);

    printf("Before sort: ");
    // print(ls);

    start = clock();
    ls->sort(int_compareTo);
    end = clock();

    printf("After sort: ");
    // print(ls);

    printf("Time to merge sort over %i elements: %f seconds\n", N, ((double)(end-start))/CLOCKS_PER_SEC);


    return 0;

}