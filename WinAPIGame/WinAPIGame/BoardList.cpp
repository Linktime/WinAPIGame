#include "GameHead.h"
#include "DrawBoard.cpp"
#ifndef BOARDLIST
#define BOARDLIST
class List {
private :
	int max;
	Board * blist[10];
	int top;
	int til;
	int count;
public :
	List():top(0),til(0),count(0) {
		max = 10;
	};

	int getCount(){
		return count;
	}

	int getTil() {
		return til;
	}

	int getMax() {
		return max;
	}

	int empty() {
		return !count;
	}

	void addBoard(Board * b) {
		if (count<max) {
			top = (count+til)%max;
			blist[top] = b;
			count += 1;
		}
		else return;
	}
	void removeTopBoard() {
		if (count>0) {
			delete blist[til];
			til = (til+1)%max;
			count -= 1;
		}
		else return;
	}
	Board * operator[](int i){
		return blist[i];
	}

	void clean() {
		for (int i=til;i<count;i++) {
			delete blist[(i+count)%max];
		}
		til = 0;
		top = 0;
		count = 0;
	}
};

#endif

