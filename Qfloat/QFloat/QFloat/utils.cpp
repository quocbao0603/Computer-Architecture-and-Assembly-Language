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
	vector <int> a, res;
	//Bỏ phần X,..... lấy từ sau dấu phẩy
	for (int i = 2; i < number.size(); ++i) a.push_back(number[i] - '0');
	res.resize(a.size());
	reverse(a.begin(), a.end());
	int remain = 0;
	for (int i = 0; i < a.size(); ++i) {
		res[i] += a[i] * 2 + remain;
		remain = res[i] / 10;
		res[i] %= 10;
	}
	string ans;
	if (remain == 0)ans = "0."; else ans = "1.";
	for (int i = res.size() - 1; i >= 0; --i) ans += (res[i] + '0');
	while (ans.back() == '0')ans.pop_back();
	return ans;
}

// chuyển đổi phần nguyên từ xâu thập phân thành xâu nhị phân
string Int_to_binary(string num) {
	string ans = "";
	string tmp = num;
	while (tmp != "0") {
		int bit = (tmp.back() - '0') % 2;
		if (bit == 1) ans.push_back('1');
		else ans.push_back('0');
		tmp = Div2(tmp);
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

// chuyển đổi phần thập phân sau dấu phẩy từ xâu thập phân thành xâu nhị phân
string Fraction_to_binary(string before, string after, int &power) {
	string fractionBit = "";
	int flag = 1;
	if (before != "") {
		//số dạng xxx.010101.....
		//xxx dạng nhị phân
		//debug(flag);
		//debug(after);
		//debug(flag);
		// debug(before);
		power = biased + int(before.size()) - 1;
		//debug(power);
		for (int i = 0; i < 112 - (before.size() - 1); i++) {
			after = Mul2(after);
			fractionBit.push_back(after[0]);
			after[0] = '0';
		}
	}
	else {
		//chuẩn hoá số dạng 0,000.....
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
	//debug(before);
	//debug(fractionBit);
	string res = before + fractionBit;
	while (res[0] == '0') res.erase(0, 1);
	while (res.size() < 112) res.push_back('0');
	//debug(res);
	return res;
}
//End