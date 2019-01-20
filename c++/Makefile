#################################################################
# Pre-processor options (uncomment for adding)

# if uncommented activates push-back option
# leave it commented to use default push-front option
#OPT += -DPUSH_BACK

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

FLAGS = -std=c++14 -Wall -Wextra -g -O0

# flags for the compiler

CFLAGS = -I $(dirI) -I $(dirT) $(FLAGS) $(OPT)

# flags for the linker

LDFLAGS =

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
	$(CC) $^ -o $@ 

# make the object

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

.PHONY: clean documentation

clean:
	$(info clean up)
	rm -rf $(exe_name) main.o $(OBJ) *~ *# $(dirT)/*~ $(dirI)/*~ $(dirD)/*~ $(dirD)/html $(dirD)/latex $(PWD)/input/*~
