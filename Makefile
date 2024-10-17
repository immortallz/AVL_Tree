prog: Tree.o main.o malloc.o
	wg++ Tree.o main.o malloc.o -o prog.exe && del malloc.o main.o Tree.o && prog.exe
Tree.o: Tree.cpp
	wg++ -c Tree.cpp
main.o: main.cpp
	wg++ -c main.cpp
malloc.o: malloc.cpp
	wg++ -c malloc.cpp