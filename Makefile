all: fixeddemo


fixeddemo: DirectFormI.h fixeddemo.cpp
	g++ -O2 -o fixeddemo fixeddemo.cpp

clean:
	rm -f fixeddemo ecg_filtered.dat

