#include "process.h"
#include "utils.h"

string process_IntUnaryOp(string a, int oper, int inp_type){
	string result;
	QInt int_a, int_res;
	switch (oper)
	{
	//Chuyen tu chuoi Dec (a) sang Bin (result).
	case 0: {
		int_a = QInt(a);
		result = int_a.DecToBin();
		break;
	}
	//Chuyen tu chuoi Bin (a) sang Dec (result).
	case 1: {
		//int_a = QInt(std::string("0"));
		int_a = int_a.BinToDec(a);
		result = int_a.toDecString();
		break;
	}
	//Chuyen tu chuoi Bin (a) sang Hex (result).
	case 2: {
		int_a = int_a.BinToDec(a);
		result = BinToHexStr(a);
		break;
	}
	//Chuyen tu chuoi Dec (a) sang Hex (result).
	case 3: {
		int_a = QInt(a);
		result = int_a.DecToHex();
		break;
	}
	//NOT
	case 18: {
		if(inp_type == 0){
			int_a = int_a.BinToDec(a);
			result = (~int_a).DecToBin();
		}
		else {
			int_a = QInt(a);
			int_res = ~int_a;
			result = int_res.toDecString();
		}
		break;
	}
	case 21: {
		result = HexToBinStr(a);
		break;
	}
			//Chuyen tu chuoi Dec (a) sang Hex (result).
	case 22: {
		int_a = int_a.BinToDec(HexToBinStr(a));
		result = int_a.toDecString();
		break;
	}
			//NOT
	}
	return result;
}

string process_IntBinaryOp(string a, string b, int oper, int inp_type)
{
	string result;
	QInt int_a, int_b, int_res;

	if (inp_type == 0) {
		int_a = int_a.BinToDec(a);
		int_b = int_b.BinToDec(b);
	}
	else if(inp_type == 1){
		int_a = QInt(a);
		int_b = QInt(b);
	}
	else {
		int_a = int_a.BinToDec(HexToBinStr(a));
		int_b = int_b.BinToDec(HexToBinStr(b));
	}
	
	switch (oper)
	{
	//Cong hai so
	case 4: {
		int_res = int_a + int_b;
		break;
	}
			//Tru hai so
	case 5: {
		int_res = int_a - int_b;
		break;
	}
			//Nhan
	case 6: {
		int_res = int_a * int_b;
		break;
	}
			//Chia
	case 7: {
		if (int_b.Zero()) {
			return "NaN";
		}
		int_res = int_a / int_b;
		break;
	}
			//So sanh be hon
	case 8: {
		if (int_a < int_b) result = "True";
		else result = "False";
		return result;
	}
			//So sanh be hon hoac bang
	case 9: {
		if (int_a <= int_b) result = "True";
		else result = "False";
		return result;
	}
			//So sanh lon hon
	case 10: {
		if (int_a > int_b) result = "True";
		else result = "False";
		return result;
	}
			 //So sanh lon hon hoac bang
	case 11: {
		if (int_a >= int_b) result = "True";
		else result = "False";
		return result;
	}
	case 12: {
		if (int_a == int_b) result = "True";
		else result = "False";
		return result;
	}
			 //Rightshift
	case 13: {
		int k = stoi(b);
		int_res = int_a >> k;
		break;
	}
	//Leftshift
	case 14: {
		int k = stoi(b);
		int_res = int_a << k;
		break;
	}
			 //AND
	case 15: {
		int_res = int_a & int_b;
		break;
	}
			 //OR
	case 16: {
		int_res = int_a | int_b;
		break;
	}
			 //XOR
	case 17: {
		int_res = int_a ^ int_b;
		break;
	}
	//ROL
	case 19: {
		int k = stoi(b);
		int_res = int_a.RollLeft(k);
		break;
	}
	//ROR
	case 20: {
		int k = stoi(b);
		int_res = int_a.RollRight(k);
		break;
	}
	}
	if (inp_type == 0) result = int_res.DecToBin();
	else result = int_res.toDecString();
	return result;
}

string process_FloUnaryOp(string a, int oper){
	string result;
	QFloat flo_a, flo_res;
	switch (oper)
	{
		//Chuyen tu chuoi Dec (a) sang Bin (result).
	case 0: {
		flo_a = QFloat(a);
		result = flo_a.To_bit_string();
		break;
	}
			//Chuyen tu chuoi Bin (a) sang Dec (result).
	case 1: {
		//int_a = QInt(std::string("0"));
		flo_a.fromBin(a);
		result = flo_a.To_dec_string();
		break;
	}
	}
	return result;
}

string process_FloBinaryOp(string a, string b, int oper, int inp_type)
{
	string result;
	QFloat flo_a, flo_b, flo_res;

	if (inp_type == 0) {
		flo_a.fromBin(a);
		flo_b.fromBin(b);
	}
	else {
		flo_a = QFloat(a);
		flo_b = QFloat(b);
	}
	switch (oper)
	{
		//Cong hai so
	case 2: {
		flo_res = flo_a + flo_b;
		break;
	}
			//Tru hai so
	case 3: {
		flo_res = flo_a - flo_b;
		break;
	}
			//Nhan
	case 4: {
		flo_res = flo_a * flo_b;
		break;
	}
			//Chia
	case 5: {
		flo_res = flo_a / flo_b;
		break;
	}
	}
	if (inp_type == 0) result = flo_res.To_bit_string();
	else result = flo_res.To_dec_string();
	return result;
}
