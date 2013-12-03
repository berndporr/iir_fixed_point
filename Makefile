all: fixeddemo


fixeddemo: DirectFormI.h fixeddemo.cpp
	g++ -g -o fixeddemo fixeddemo.cpp

clean:
	rm -f fixeddemo
