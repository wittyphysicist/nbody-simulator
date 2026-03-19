CXX      = g++
CXXFLAGS = -O2 -std=c++17 -Xpreprocessor -fopenmp \
           -I$(shell brew --prefix libomp)/include
LDFLAGS  = -L$(shell brew --prefix libomp)/lib -lomp

main: main.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.cpp -o main

clean:
	rm -f main