CC = gcc
CXX = g++
CPPFLAGS =        # put pre-processor settings (-I, -D, etc) here
CXXFLAGS = -std=c++20 -Wpedantic -pedantic-errors -Wall -Wextra  # put compiler settings here
LDFLAGS =         # put linker settings here
EXE = Othello
OBJS=color.o othello.o main.o

#DEBUG
DBGDIR = debug
DBGEXE = $(DBGDIR)/$(EXE)
DBGOBJS = $(addprefix $(DBGDIR)/, $(OBJS))
DBGCXXFLAGS = -g -Og -DDEBUG

#RELEASE
RELDIR = release
RELEXE = $(RELDIR)/$(EXE)
RELOBJS = $(addprefix $(RELDIR)/, $(OBJS))
RELCXXFLAGS = -Ofast -DNDEBUG


all: create debug_
debug: create debug_
release: create release_

create:
	@mkdir -p $(DBGDIR) $(RELDIR)
release_ : $(RELEXE)
debug_ : $(DBGEXE)

$(RELEXE) : $(RELOBJS)
	$(CXX) $(CXXFLAGS) $(RELCXXFLAGS) -o $(RELEXE) $^
$(DBGEXE) : $(DBGOBJS)
	$(CXX) $(CXXFLAGS) $(DBGCXXFLAGS) -o $(DBGEXE) $^

$(RELDIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(RELCXXFLAGS) -o $@ $<
$(RELDIR)/%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $(RELCXXFLAGS) -o $@ $<
$(RELDIR)/%.o: %.c
	$(CC) -c $(CXXFLAGS) $(RELCXXFLAGS) -o $@ $<
$(DBGDIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(DBGCXXFLAGS) -o $@ $<
$(DBGDIR)/%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $(DBGCXXFLAGS) -o $@ $<
$(DBGDIR)/%.o: %.c
	$(CC) -c $(CXXFLAGS) $(DBGCXXFLAGS) -o $@ $<

clean:
	rm -f $(RELEXE) $(RELOBJS) $(DBGEXE) $(DBGOBJS)
	rmdir $(DBGDIR) $(RELDIR) 2>/dev/null | true
