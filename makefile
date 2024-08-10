# Define compiler and flags
CC = g++
CXXFLAGS = -std=c++11 -g

# Define source and object files
SRCS = SetLangLexer.l lang.y SyntaxTree.cpp 
OBJS = lex.yy.o lang.tab.o SyntaxTree.o 

# Define header files
HDRS = SyntaxTree.hpp lang.tab.h

# Define all targets
all: setlang

# Define parser generation rule
lang.tab.c lang.tab.h: lang.y
	bison -d -o lang.tab.c lang.y

# Define lexer generation rule
lex.yy.c: lang.l lang.tab.h
	flex lang.l

# Define object file compilation rules
%.o: %.cpp $(HDRS)
	$(CC) $(CXXFLAGS) -c $< -o $@ -I.

lex.yy.o: lex.yy.c lang.tab.h
	$(CC) $(CXXFLAGS) -c lex.yy.c -o $@ -I.

lang.tab.o: lang.tab.c
	$(CC) $(CXXFLAGS) -c lang.tab.c -o $@ -I.

# Define output file generation rule
setlang: $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $(OBJS)

# Define clean target to remove object files and executables
clean:
	rm -f $(OBJS) lex.yy.c lang.tab.c lang.tab.h setlang

# Define run target to execute the compiler on example2.set
run: setlang
	./setlang example2.set

compile_output: output.cpp
	$(CC) $(CXXFLAGS) -o output output.cpp

run_output: compile_output
	./output

compile_and_run: compile_output run_output
