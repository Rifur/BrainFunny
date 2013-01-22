CXX = clang++
CPP = g++
all:
	$(CPP) -o bfInt -Wall -O3 BF_Message.cpp BF_Proc.cpp BF_VM.cpp main.cpp \
		-I../include/

clean:
	rm -f *.o
	rm -f bfInt
