EXE = exe.x
CXX = c++

dirL = $(PWD)/src
dirI = $(PWD)/include
dirD = $(PWD)/Doxygen

CXXFLAGS = -I$(dirI) -g -std=c++11 -Wall -Wextra

SRC= main.cc $(dirL)/Tree.cc $(dirL)/Iterator.cc $(dirL)/Node.cc
OBJ=$(SRC:.cc=.o)
INC = $(dirI)/Tree.h $(dirI)/Iterator.h $(dirI)/Node.h $(dirI)/BST_utility.h

LDFLAGS = -Wl,-rpath,$(dirL)

# VPATH = ../05_error_handling

# eliminate default suffixes
.SUFFIXES:
SUFFIXES =

# just consider our own suffixes
.SUFFIXES: .cc .o

all: $(EXE)

.PHONY: all

clean:
	$(info clean up)
	@rm -rf $(OBJ) $(EXE) $(dirL)/*~ $(dirI)/*~ $(dirD)/*~ *~ $(dirD)/html $(dirD)/latex 

.PHONY: clean

%.o: %.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(EXE): $(OBJ)
	$(CXX) $^ -o $(EXE) $(LDFLAGS)

documentation: $(dirD)/doxy.in
	doxygen $^

.PHONY: documentation

main.o: $(INC)

src/Tree.o: $(INC)

src/Iterator.o: $(dirI)/Iterator.h $(dirI)/Node.h $(dirI)/BST_utility.h

src/Node.o : $(dirI)/Node.h $(dirI)/BST_utility.h

format: $(SRC) $(INC)
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"

.PHONY: format
