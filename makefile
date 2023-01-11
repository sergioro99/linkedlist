BINARY = main.exe
OBJS_LINKED_LIST = main.o LinkedList.o
COMPILER = clang++

program: $(OBJS_LINKED_LIST)
	${COMPILER} -o $(BINARY) $(OBJS_LINKED_LIST)

main.o: main.cpp LinkedList.cpp
	${COMPILER} -c main.cpp

Linkedlist.o: LinkedList.cpp
	${COMPILER} -c LinkedList.cpp

clean:
	rm -f *.o $(BINARY)