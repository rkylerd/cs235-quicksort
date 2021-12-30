#include "QS.h"
#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <algorithm>
using namespace std;

QS::QS()
{
	myArray = NULL;
	size = 0;
	capacity = 0;
}

void QS::baylo2(int x, int y)
{
	int temp[1];
	temp[0] = myArray[x];
	myArray[x] = myArray[y];
	myArray[y] = temp[0];
}

void QS::balikbalik(int l, int r)
{ 

	int MID = 0;
	int p = 0;
	if ((r - l) < 3) {
		if (r - l == 2) {
			int middle = (l + r) / 2;// middle index is made the pivot

			if (myArray[l] > myArray[middle]) {
				baylo2(middle, l);
			}
			if (myArray[middle] > myArray[r]) {
				baylo2(middle, r);
			}
			if (myArray[l] > myArray[middle]) {
				baylo2(middle, l);
			}
		}
		if (r - l == 1) {
			
			if (myArray[l] > myArray[r]) {
				baylo2(l, r);
			}
		}
		if (r - l == 0) {
			return;
		}
	}
	else {
		MID = medianOfThree(l, r);
		p=partition(l, r, MID);
		
	//	cout << "MID:  " << MID << " p:  " << p << endl;
		balikbalik(l, p-1);
		balikbalik(p+1, r);
	}	
}

void QS::sortAll() {
	if (size != 0 && size != NULL) {
		balikbalik(0, size - 1);//is this how we get left and right?
	}
}

int QS::medianOfThree(int left, int right)
{
	if (size == 0  || left >= right || left < 0 || right >= size) {
		return -1;
	}

	int middle = (left + right) / 2;// middle index is made the pivot
	
	if (myArray[left] > myArray[middle]) {
		baylo2(middle, left);
	}
	else if (myArray[middle] > myArray[right]) {
		baylo2(middle, right);
	}
	if (myArray[left] > myArray[middle]) {
		baylo2(middle, left);
	}
	return middle;
	//}
	
	//LEFT = left;
	//RIGHT = right;
	// returns the median index of the first, middle and last indices
}


int QS::partition(int left, int right, int pivotIndex){
	
	if (size == 0||myArray == NULL) {//will this work?
		//cout << "Dili ni pwede uy" << endl;
		return -1;
	}
	if (right >= size || size < left || right < 0 || left < 0 || left > right|| pivotIndex < left || pivotIndex > right) {
		return -1;
	}
	int up = left + 1;
	int down = right;

	if (right - left == 1) {
		if (myArray[left] > myArray[right]) {
			baylo2(left, right);
		}
		return left; //not sure if this is okay yet
	}


	baylo2(pivotIndex, left);
	while (down > up) {
		while (myArray[up] <= myArray[left] && up < right) {
			up++;
		}
		while (myArray[down] > myArray[left] && down > left + 1) {
			down--;
		}
		if (up < down) {
			baylo2(down, up);
		}
	} // should down eventually be less than up? 
	baylo2(down, left);

	return down;
}

string QS::getArray() 
{
	stringstream ss;
	string array ="";

	if (size == 0 || myArray == NULL) {//will this work?
		return array;
	}
	for (int i = 0; i < size; i++) {
		if (i == (size-1)) {
			ss << myArray[i];
			break;
		}
		if (i < size) {
			ss << myArray[i] << ",";
		}
		
	}
	ss >> array;
	//array.substr(0, array.length() - 2);
	return array;
}

int QS::getSize() 
{
	return size;
}

void QS::addToArray(int value) {
	if (size < this->capacity) {
		myArray[size] = value;
		size++;
	}
}

bool QS::createArray(int capacity) { 
	if (myArray!=NULL) {
		clear();
	}
	this->capacity = capacity;
	if (capacity >= 0) { 
		myArray = new int[capacity]; 
		return true;
	}
	else return false;
}

void QS::clear() {
	if (myArray != NULL) {
		delete[]myArray;
	}
	myArray = NULL;
	size = 0;
	capacity = 0;
}

QS::~QS()
{
	clear();
}