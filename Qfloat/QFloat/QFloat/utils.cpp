#include "utils.h"
#include "QFloat.h"


// Chia đôi số dạng xâu
string Div2(string num) {
	string res = num;
	int len = num.size();
	int k = 0, tmp = 0, Digit;
	for (int i = 0; i < len; i++) {
		Digit = (num[i] - '0');
		tmp = k * 10 + Digit;
		res[i] = tmp / 2 + '0';
		k = tmp % 2;
	}
	// Xóa 0 ở đầu
	while (res[0] == '0' && res.size() > 1)res.erase(0, 1);
	return res;
}

// Nhân đôi số thực
string Mul2(string number) {
	int len = number.length();
	string result;
	int k = number.find('.');
	int carry = 0, tmp;

	if (k != string::npos) {
		// Nhân 2 với phần thập phân
		for (int i = len - 1; i > k; --i) {
			tmp = (number[i] - '0') * 2 + carry;
			if (tmp >= 10) {
				result.insert(result.begin(), char(tmp - 10 + '0'));
				carry = 1;
			}
			else {
				result.insert(result.begin(), char(tmp + '0'));
				carry = 0;
			}
		}
		result.insert(result.begin(), '.');

		// Nhân 2 với phần nguyên trước dấu '.'
		for (int i = k - 1; i >= 0; --i) {
			tmp = (number[i] - '0') * 2 + carry;
			if (tmp >= 10) {
				result.insert(result.begin(), char(tmp - 10 + '0'));
				carry = 1;
			}
			else {
				result.insert(result.begin(), char(tmp + '0'));
				carry = 0;
			}
		}
	}
	else {
		for (int i = len - 1; i >= 0; --i) {
			tmp = (number[i] - 48) * 2 + carry;
			if (tmp >= 10) {
				result.insert(result.begin(), char(tmp - 10 + '0'));
				carry = 1;
			}
			else {
				result.insert(result.begin(), char(tmp + '0'));
				carry = 0;
			}
		}
	}
	if (carry == 1) result.insert(result.begin(), '1');
	return result;
}

// chuyển đổi phần nguyên từ xâu thập phân thành xâu nhị phân
string Int_to_binary(string num) {
	string ans = "0";
	string tmp = num;
	while (tmp != "0") {
		int bit = (tmp.back() - '0') % 2;
		if (bit == 1) ans.push_back(1);
		else ans.push_back(0);
		tmp = Div2(tmp);
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

// chuyển đổi phần thập phân sau dấu phẩy từ xâu thập phân thành xâu nhị phân
string Fraction_to_binary(string before, string after, int &power) {
	string fractionBit = "";
	
	if (before != "0") {
		//số dạng xxx.010101.....
		//xxx dạng nhị phân
		power = before.size() - 1 + biased;
		for (int i = 0; i < 112 - (before.size() - 1); i++) {
			after = Mul2(after);
			fractionBit.push_back(after[0]);
			after[0] = '0';
		}
	}
	else {
		int cnt = 0;
		
		while (cnt < biased) {
			after = Mul2(after);
			fractionBit.push_back(after[0]);
			after[0] = '0';
			if (fractionBit.back() == '1') break;
			cnt++;
		}

		
		power = -(cnt + 1) + biased;
		if (cnt + 1 < biased) {
			for (int i = 0; i < MAX_BIT - 1 - Exponent; ++i) {
				after = Mul2(after);
				fractionBit += after[0];
				after[0] = '0';
			}
		}
		else {
			fractionBit = "";
			while (power < 1) {
				after = Mul2(after);
				fractionBit += after[0];
				after[0] = '0';
				power++;
			}
			string res = before + fractionBit;
			while (res.size() < MAX_BIT - 1 - Exponent) res += '0';
			return res;
		}
	}

	string res = before + fractionBit;
	while (res[0] == '0') res.erase(0, 1);
	while (res.size() < 113) res.push_back('0');
	return res;
}
//End