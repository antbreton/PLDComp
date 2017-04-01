default:
	flex test.l
	bison -v --defines=test.tab.h test.y
	clang++ -o gc+ *.c *.cpp
clean : 
	rm -f *.yy.c *.tab.c *.tab.h *.output test core
