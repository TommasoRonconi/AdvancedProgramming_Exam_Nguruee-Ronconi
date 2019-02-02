#################################################################
# Pre-processor options (uncomment for adding)

# default action: fill tree, balance it, print on stdout
OPT = -DDEFAULT

# if uncommented runs basic tests
# OPT = -DTEST

# if uncommented compares performance with std::map
# ( note that couples key-value are taken from stdin )
# OPT = -DPERFORMANCE

# if uncommented measures performance of balance() function
# ( note that couples key-value are taken from stdin )
# OPT = -DTEST_BALANCE

#################################################################
# Flags and variables

CC = g++

dirI = $(PWD)/include
dirT = $(PWD)/tpl
dirD = $(PWD)/Doxygen

# name of the executable

exe_name = tree.x

# flags for debugging and optimization
# (these are the flags I might want to change)

FLAGS = -g -fsanitize=address

# flags for the compiler

CFLAGS = -I $(dirI) -I $(dirT) $(FLAGS) $(OPT) -std=c++14 -Wall -Wextra -O3 

# flags for the linker

LDFLAGS = $(FLAGS) 

# includes

INC = $(dirI)/Tree.h $(dirI)/Node.h $(dirI)/Iterator.h

# templates

TPL = $(dirT)/Tree.tpp $(dirT)/Node.tpp

# objects

OBJ = main.o

#################################################################
# Rules

# default rule

all: $(exe_name)

# make the executable

$(exe_name): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

# make the object

main.e: main.cpp $(INC) $(TPL) Makefile
	$(CC) $(CFLAGS) -E $< -o $@

main.o: main.cpp $(INC) $(TPL) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

# make the documentation

documentation: $(dirD)/doxy.in
	doxygen $^

# eliminate default suffixes

.SUFFIXES:
SUFFIXES =

# just consider our own suffixes

.SUFFIXES: .cpp .tpp .o

#################################################################
# phony rules

.PHONY: clean documentation clean_doc

clean:
	$(info clean up)
	rm -rf $(exe_name) main.o $(OBJ) *~ *# $(dirT)/*~ $(dirI)/*~ $(dirD)/*~ $(PWD)/input/*~

clean_doc:
	$(info clean doc)
	rm -rf  $(dirD)/*~ $(dirD)/html $(dirD)/latex
