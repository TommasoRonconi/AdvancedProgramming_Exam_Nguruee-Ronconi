#################################################################
# Pre-processor options (uncomment for adding)

# if uncommented activates push-back option
# leave it commented to use default push-front option
#OPT += -DPUSH_BACK

#################################################################
#

CC = g++

dirI = $(PWD)/include
dirL = $(PWD)/src

# name of the executable

exe_name = tree.x

# flags for debugging and optimization
# (these are the flags I might want to change)

FLAGS = -std=c++14 -Wall -Wextra -g -O0

# flags for the compiler

CFLAGS = -I $(dirI) $(FLAGS) $(OPT)

# flags for the linker

LDFLAGS = -Wl,-rpath,$(dirL)

# objects

OBJs = $(dirL)/Tree.o main.o # $(dirL)/Node.o $(dirL)/Iterator.o 

#################################################################
# Rules:

# eliminate default suffixes
.SUFFIXES:
SUFFIXES =

# just consider our own suffixes
.SUFFIXES: .cc .o 

# default rule

all: $(exe_name)

# make the executable

$(exe_name): $(OBJs)
	$(CC) $^ -o $@ $(LDFLAGS)

# general rule

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

# pre-requisites

main.o: $(dirL)/*.o

$(dirL)/Tree.o: $(dirI)/Node.h $(dirI)/Iterator.h $(dirI)/BST_utility.h

# $(dirL)/Iterator.o: $(dirI)/Node.h  $(dirI)/BST_utility.h

# $(dirL)/Node.o: $(dirI)/BST_utility.h

# cleaning rule and co.

.PHONY: clean

clean:
	rm -f $(exe_name) $(OBJs) *~ *# $(dirL)/*~ $(dirI)/*~





# # EXE = exe.x
# # CXX = c++

# # dirL = $(PWD)/src
# # dirI = $(PWD)/include
# # dirD = $(PWD)/Doxygen

# # CXXFLAGS = -I$(dirI) -g -std=c++14 -Wall -Wextra

# # SRC= main.cc $(dirL)/Tree.cc $(dirL)/Iterator.cc $(dirL)/Node.cc

# # OBJ=$(SRC:.cc=.o)

# # INC = $(dirI)/Tree.h $(dirI)/Iterator.h $(dirI)/Node.h $(dirI)/BST_utility.h

# # LDFLAGS = -Wl,-rpath,$(dirL)

# # # VPATH = ../05_error_handling

# # # eliminate default suffixes
# # .SUFFIXES:
# # SUFFIXES =

# # # just consider our own suffixes
# # .SUFFIXES: .cc .o

# # all: $(EXE)

# # .PHONY: all

# # clean:
# # 	$(info clean up)
# # 	@rm -rf $(OBJ) $(EXE) $(dirL)/*~ $(dirI)/*~ $(dirD)/*~ *~ $(dirD)/html $(dirD)/latex 

# # .PHONY: clean

# # %.o: %.cc
# # 	$(CXX) -c $< -o $@ $(CXXFLAGS)

# # $(EXE): $(OBJ)
# # 	$(CXX) $^ -o $(EXE) $(LDFLAGS)

# # documentation: $(dirD)/doxy.in
# # 	doxygen $^

# # .PHONY: documentation

# # main.o: $(INC)

# # src/Tree.o: $(INC)

# # src/Iterator.o: $(dirI)/Iterator.h $(dirI)/Node.h $(dirI)/BST_utility.h

# # src/Node.o : $(dirI)/Node.h $(dirI)/BST_utility.h

# # format: $(SRC) $(INC)
# # 	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"

# # .PHONY: format
