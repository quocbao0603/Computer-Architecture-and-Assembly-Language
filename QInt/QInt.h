#pragma once
#include <math.h>
#include <stdio.h>
#include <string>
#define MAX_NUM 4
using namespace std;

class QInt {
private:
	int data[MAX_NUM];
public:
	int Get_bit(int k); // lấy bit thứ k của một số QInt
	void Turn_on_bit(int k); // bật bit thứ k của một số QInt
 	QInt operator & (QInt); // Toán tử AND
	QInt operator | (QInt); // Toán tử OR
	QInt operator ^ (QInt); // Toán tử XOR 
	QInt operator ~ (); // Toán tử NOT (lưu ý "~" not "!")

	QInt operator >> (int); // Dịch bit phải (dịch số học) của một số QInt
	QInt operator << (int); // Dịch bit trái (dịch số học) của một số QInt
};