CC = gcc
CXX = g++
CPPFLAGS =        # put pre-processor settings (-I, -D, etc) here
CXXFLAGS = -std=c++20 -Wpedantic -pedantic-errors -Wall -Wextra  # put compiler settings here
LDFLAGS =         # put linker settings here
EXE = Othello
OBJS=color.o named_pipe.o play.o othello.o main.o

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


all: create debug_ release_
debug: create debug_
release: create release_

create:
	@mkdir -p $(DBGDIR) $(RELDIR)
release_ : $(RELEXE) relIAs
debug_ : $(DBGEXE) dbgIAs

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

relIAs:
	cd IAs && make release

dbgIAs:
	cd IAs && make debug

clean:
	rm -rf $(DBGDIR) $(RELDIR)
	cd IAs && make clean
