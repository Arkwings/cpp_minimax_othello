CC = gcc
CXX = g++
CPPFLAGS =        # put pre-processor settings (-I, -D, etc) here
CXXFLAGS = -std=c++17 -Wall  # put compiler settings here
LDFLAGS =         # put linker settings here
EXEC_NAME = Othello
OBJ_FILES=main.o othello.o

all: $(EXEC_NAME)

clean:
	rm -f $(EXEC_NAME) $(OBJ_FILES) *.gch

$(EXEC_NAME) : $(OBJ_FILES)
	$(CXX) -o $(EXEC_NAME) $(OBJ_FILES)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<

%.o: %.cc
	$(CXX) $(CFLAGS) -c $<

%.o: %.c
	${CC} $(CFLAGS) -c $<
