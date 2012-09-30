CPP = clang++

all:
	$(CPP) -O3 -c BF_Proc.cpp BF_VM.cpp main.cpp
	$(CPP) -o bfInt -O3 BF_VM.o BF_Proc.o main.o

clean:
	rm -f *.o
	rm -f bfInt