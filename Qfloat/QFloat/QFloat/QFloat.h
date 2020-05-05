#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define MAX_NUM 4
//4 * 32 bit = 128 bit
class QFloat {
private:
	unsigned int data[MAX_NUM];
public:
	// constructor
	QFloat();
	QFloat(const QFloat &other);
	QFloat(const string &s);

	// scanf and printf
	friend void ScanQInt(QFloat&); // Đọc số QInt
	friend void PrintQInt(QFloat); // In số QInt
	QFloat BinToDec(string bin);
	string DecToBin(QFloat x)
}