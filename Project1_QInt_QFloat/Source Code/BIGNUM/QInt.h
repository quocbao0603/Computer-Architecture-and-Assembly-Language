#pragma once
#include <cmath>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>


#define MAX_NUM 4

using namespace std;

class QInt {
private:
	unsigned int data[MAX_NUM];
public:
	// constructor
	QInt();
	QInt(const QInt &that);
	QInt(const string &s);
	//Khởi tạo từ chuỗi thập phân

	// scanf and printf
	friend void ScanQInt(QInt&); // Đọc số QInt
	friend void PrintQInt(QInt); // In số QInt
	//In ra chuỗi thập phân

	string toDecString();
	//Lấy ra chuỗi thập phân					 
	
	// bit operator
	int Get_bit(int k);
	void Turn_on_bit(int k);
	void Set_bit(int k, int t);
	void Flip_bit(int k);
	QInt operator & (QInt); // Toán tử AND
	QInt operator | (QInt); // Toán tử OR
	QInt operator ^ (QInt); // Toán tử XOR
	QInt operator ~ (); // Toán tử NOT (lưu ý "~" not "!")

	QInt operator >> (int); // Dịch bit phải (dịch số học) của một số QInt
	QInt operator << (int); // Dịch bit trái (dịch số học) của một số QInt


	//function convert giua cac hệ
	string DecToBin();
	//Chuyển từ kiểu Dec của obj hiện tại sang Bin, cũng có tác dụng lấy ra chuỗi nhị phân.
	QInt BinToDec(string bin);
	//Có thể dùng để nhập chuỗi nhị phân vào obj hiện tại.
	string DecToHex();
	//DectoHex nằm trong file Utils.

	// function
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
	QInt RollLeft(int);
	QInt RollRight(int);

	// check số âm và lấy ngược
	bool Negative();
	QInt opposite(); // -5 --> 5, 5 --> -5
	bool Zero();

	QInt shl(int);
	//Dich trai logic - Dung cho phep chia


};
