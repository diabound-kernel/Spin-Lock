CXX=clang++ -std=c++20 
LIBS=-lpthread

spin-lock: main.cpp
	$(CXX) $? $(LIBS) -o $@

clean:
	rm spin-lock;