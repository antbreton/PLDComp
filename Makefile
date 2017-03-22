default:
	flex test.l
	bison -v --defines=test.tab.h test.y
	clang -o test *.c
clean : 
	rm -f *.yy.c *.tab.c *.tab.h *.output test core
