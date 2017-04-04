COMPIL = g++
EXECNAME = Compilo
COMPILFLAGS = -std=c++1y
OPTIMISATIONFLAGS = -O1


SRC = $(wildcard *.cpp) $(wildcard *.c) $(wildcard IR/*.cpp)
OBJS = $(SRC:.cXX=.o)

bison:
	flex test.l
	bison -v --defines=test.tab.h test.y
	make all
	
all : $(EXECNAME)

$(EXECNAME) : $(OBJS)
	$(COMPIL) -o $@ $(COMPILFLAGS) $(OPTIMISATIONFLAGS) $^
	
%.o : %.c
	$(COMPIL)  -o $@ $(COMPILFLAGS) $(OPTIMISATIONFLAGS) -c $<

assembleur:
	as main.s -o main.o
	g++ main.o -o exe
	

clean : 
	rm -f *.o *.exe *.yy.c *.tab.c *.tab.h *.output test $(EXECNAME) core
