CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++11 -O3 -march=native
EXECS=find_best check_monotone evaluate performance dump
all: $(EXECS)
$(EXECS): %: %.cpp secretary.h
	$(CXX) $(CXXFLAGS) $< -o $@
