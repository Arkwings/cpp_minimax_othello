CC = gcc
CXX = g++
CPPFLAGS =        # put pre-processor settings (-I, -D, etc) here
CXXFLAGS = -std=c++20 -Wpedantic -pedantic-errors -Wall -Wextra  # put compiler settings here
LDFLAGS =         # put linker settings here
EXE = montecarlo
OBJS= othello.o heuristic.o montecarlo.o named_pipe.o main.o

#DEBUG
DBGDIR = debug
DBGEXEDIR = ../../debug
DBGEXE = $(DBGEXEDIR)/$(EXE)
DBGOBJS = $(addprefix $(DBGDIR)/, $(OBJS))
DBGCXXFLAGS = -g -Og -DDEBUG

#RELEASE
RELDIR = release
RELEXEDIR = ../../release
RELEXE = $(RELEXEDIR)/$(EXE)
RELOBJS = $(addprefix $(RELDIR)/, $(OBJS))
RELCXXFLAGS = -Ofast -DNDEBUG

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
	rm -rf $(DBGDIR) $(RELDIR)
