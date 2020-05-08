#pragma once
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>

#define debug(a) cout << #a << ": " << a << endl
#define ALL(a) a.begin(),a.end()
using namespace std;

#define MAX_BIT 128
#define MAX_NUM 4
const int biased = (1 << 14) - 1;
#define Exponent 15
//4 * 32 bit = 128 bit


class QFloat {
private:
	unsigned int data[MAX_NUM];
public:
	// constructor
	QFloat();
	QFloat(const QFloat &other);
	QFloat(const string &s);

	//bit operator
	int Get_bit(int k);
	void Turn_on_bit(int k);
	void Set_bit(int k, int t);
	void Flip_bit(int k);

	//Kiểm tra các trường hợp đặc biệt
	//Kiểm tra số Inf
	bool Is_Inf();
	bool Is_Zero();
	bool Is_Negative();
	bool Is_NaN();

	//convert to 2s & 10s
	string To_bit_string();
	string To_dec_string();

	// scanf and printf 
	QFloat Scan_QFloat(string, int);// Đọc số QFloat hệ thập phân or nhị phân
	QFloat Scan_Dec_string_to_QFloat(string);
	QFloat Scan_Bin_string_to_QFloat(string);

	friend void Print_QFloat(QFloat); // In số QFloat
	//string BinToDec();
	//string DecToBin(QFloat x);
};