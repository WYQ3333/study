compile_sever:compile_sever.cpp compile.hpp
	g++ compile_sever.cpp -o compile_sever -std=c++11 -lpthread -ljsoncpp

test:test.cc
	g++ test.cc -o test -std=c++11 -lpthread -ljsoncpp

.PHONY:clean
clean:
	rm test compile_sever

