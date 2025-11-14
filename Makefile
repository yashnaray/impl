CXXFLAGS = -std=c++23 -Wall -Wextra -g

run: implement
	./implement

implement: implement.cpp
	g++ $(CXXFLAGS) -o implement implement.cpp

clean:
	rm -f implement implement.exe

.PHONY: run implement clean
