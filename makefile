toy: toy.cpp
	clang++ -g -O3 toy.cpp `llvm-config --cxxflags --ldflags --system-libs --libs all` -o toy

run: toy
	./toy