#pragma once
#include <math.h>
#include <stdio.h>
#include <string>
#define MAX_NUM 4
#define INT_SIZE sizeof(int)
#define QINT_SIZE MAX_NUM*INT_SIZE
using namespace std;

class QInt {
private:
	int data[MAX_NUM];
public:
	string toBinary(); // Chuyển QInt sang binary
	void assign(string bin); // Gán QInt từ binary
	bool lastBit();	 // Lấy bit cuối của QInt
	bool firstBit(); // Lấy bit đầu của QInt
	
	int Get_bit(int k); // lấy bit thứ k của một số QInt
	void Turn_on_bit(int k); // bật bit thứ k của một số QInt
	
	QInt operator + (QInt const& a);	//Toán tử cộng
	QInt operator - (QInt  a);			//Toán tử trừ
	QInt operator * (QInt const& a);	//Toán tử nhân
	QInt operator / (QInt const& a);	//Toán tử chia
	bool operator < (QInt const& a);	//Các toán tử khác.....
	bool operator > (QInt const& a);
	bool operator == (QInt const& a);
	bool operator <= (QInt const& a);
	bool operator >= (QInt const& a);
	QInt& operator = (QInt const& a);
	
 	QInt operator & (QInt); // Toán tử AND
	QInt operator | (QInt); // Toán tử OR
	QInt operator ^ (QInt); // Toán tử XOR 
	QInt operator ~ (); // Toán tử NOT (lưu ý "~" not "!")

	QInt operator >> (int); // Dịch bit phải (dịch số học) của một số QInt
	QInt operator << (int); // Dịch bit trái (dịch số học) của một số QInt
	
	QInt();
	QInt(QInt const &a);
	QInt(int k);
	~QInt();
};
