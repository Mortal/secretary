CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++11 -O3 -march=native
secretary: secretary.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
