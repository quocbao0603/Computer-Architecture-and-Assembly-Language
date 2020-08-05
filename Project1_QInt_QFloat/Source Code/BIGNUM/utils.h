#pragma once
#include "QInt.h"

char binGroup4ToHex(int); // trả về giá trị hexa của 4-bit binary
string BinToHexStr(string); // 2 --> 16
string Power2(int);
string AddInt(string, string);
string SubInt(string, string);
string MulInt(string, string);
bool LessInt(string, string);
string HexToBinStr(string);
string HexToGroup4Bin(char c);
string HexPlusHex(string, string);

//Float Utils.
string Int_to_binary(string);
string Fraction_to_binary(string, string, int&);

//Cong hai day bit
string Add(string a, string b);

//Tru hai day bit (khong dau)
string Sub(string a, string b);

//Kiem tra be hon.
bool Less(string a, string b);
//Nhan 2
string Mul2(string);
//nhân 2 số hệ nhị phân
string Mul(string, string);

//Chia 2 (so nguyen)
string Div2(string);

//Chia 
string Div(string, string);

//Chia 2 (so thuc) 
string Div2_float(string);

void Fix10(vector <int> &a);
void Fix2(vector <int> &a);
string reverse(string);

//Chuyen ve dang chuan.
string normalize(string);