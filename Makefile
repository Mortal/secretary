CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++11
EXECS=find_best check_monotone evaluate performance dump
all: $(EXECS)

clean:
	$(RM) $(EXECS) $(EXECS:=-debug) $(EXECS:=-asan)

$(EXECS): %: %.cpp secretary.h
	$(CXX) $(CXXFLAGS) -O3 -march=native $< -o $@

$(EXECS:=-debug): %-debug: %.cpp secretary.h
	$(CXX) $(CXXFLAGS) -g $< -o $@

$(EXECS:=-asan): %-asan: %.cpp secretary.h
	$(CXX) $(CXXFLAGS) -g -fsanitize=address $< -o $@
