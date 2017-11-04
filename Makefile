all: fixeddemo


fixeddemo: DirectFormI.h fixeddemo.cpp
	g++ -Ofast -o fixeddemo fixeddemo.cpp

clean:
	rm -f fixeddemo ecg_filtered2.dat
