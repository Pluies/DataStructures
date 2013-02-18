HashTable:
	gcc -g -Wall -Wextra -c HashTable.c -o HashTable.o
	gcc -g -Wall -Wextra -c HashTable_test.c -o HashTable_test.o
	gcc HashTable.o HashTable_test.o -o HashTable

HashFunTest:
	gcc -g -Wall -Wextra -c HashTable.c -o HashTable.o
	gcc -g -Wall -Wextra -c HashFunTest.c -o HashFunTest.o
	gcc HashTable.o HashFunTest.o -o HashFunTest

clean:
	rm -f *.o
	rm -f HashTable HashFunTest
