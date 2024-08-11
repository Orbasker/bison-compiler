# Define compiler and flags
CC = g++
CXXFLAGS = -std=c++11 -g

# Define source and object files
SRCS = SetLangLexer.l lang.y 
OBJS = lex.yy.o lang.tab.o 

# Define header files
HDRS = lang.tab.h

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
	rm -f $(OBJS) lex.yy.c lang.tab.c lang.tab.h setlang output.cpp output

# Define run target to execute the compiler on a given file
run: setlang
	@echo "Running setlang on file: $(FILE)"
	./setlang $(FILE)

# Define compile_output target to compile the generated output.cpp
compile_output: output.cpp
	$(CC) $(CXXFLAGS) -o output output.cpp

# Define run_output target to run the compiled C++ code
run_output: compile_output
	./output

# Define compile_and_run target to compile and run the generated C++ code
compile_and_run: compile_output run_output

# Option to choose example 1 or 2 and run it
example1: setlang
	$(MAKE) run FILE=example1.set
	$(MAKE) compile_and_run

example2: setlang
	$(MAKE) run FILE=example2.set
	$(MAKE) compile_and_run
