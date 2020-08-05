#include "utils.h"
#include "QInt.h"
#include "QFloat.h"
// Author: Duc Doan Phu

string Power2(int p) {
	// trả về 2 ^ n
	string ans = "1";
	string a = "2";
	while (p) {
		if (p & 1) ans = MulInt(ans, a);
		a = MulInt(a, a);
		p >>= 1;
	}
	return ans;
}


string MulInt(string a, string b) {
	// Nhân 2 số không âm
	vector <int> aa, bb, cc;
	for (int i = 0; i < a.size(); ++i) aa.push_back(a[i] - '0');
	for (int i = 0; i < b.size(); ++i) bb.push_back(b[i] - '0');
	cc.resize(aa.size() + bb.size());
	reverse(aa.begin(), aa.end());
	reverse(bb.begin(), bb.end());
	for (int i = 0; i < aa.size(); ++i)
		for (int j = 0; j < bb.size(); ++j)
			cc[i + j] += aa[i] * bb[j];
	Fix10(cc);
	string ans;
	for (int i = cc.size() - 1; i >= 0; --i) ans += (cc[i] + '0');
	return ans;
}

string AddInt(string a, string b) {
	// cộng 2 string a, b
	int sz = max(a.size(), b.size());
	while (a.size() < sz) a = "0" + a;
	while (b.size() < sz) b = "0" + b;
	string ret;
	int carry = 0;
	for (int i = sz - 1; i >= 0; --i) {
		int t = (a[i] - '0' + b[i] - '0') + carry;
		ret += char(t % 10 + '0');
		carry = t / 10;
	}
	if (carry > 0) {
		ret.push_back(carry + '0');
	}
	while (ret.size() > 1 && ret.back() == '0') ret.pop_back();
	reverse(ret.begin(), ret.end());
	if (ret.size() == 0) return "0";
	return ret;
}

string SubInt(string a, string b) {
	// trả về a - b với a >= b
	int sz = max(a.size(), b.size());
	while (a.size() < sz) a = "0" + a;
	while (b.size() < sz) b = "0" + b;
	string ret;
	int carry = 0;
	for (int i = sz - 1; i >= 0; --i) {
		int t = (a[i] - '0') - (b[i] - '0') - carry;
		if (t < 0) {
			t += 10;
			carry = 1;
		}
		else {
			carry = 0;
		}
		ret += (t + '0');
	}
	while (ret.size() > 1 && ret.back() == '0') ret.pop_back();
	reverse(ret.begin(), ret.end());
	if (ret.size() == 0) return "0";
	return ret;
}

bool LessInt(string a, string b) {
	// trả về true nếu a <= b
	if (a.size() != b.size()) return a.size() < b.size();
	for (int i = 0; i < a.size(); ++i) if (a[i] != b[i]) return a[i] < b[i];
	return true;
}

char binGroup4ToHex(int v) {
	if (0 <= v && v < 10) return v + '0';
	return char('A' + v - 10);
}

string BinToHexStr(string bin) {
	string ans;
	int t = MAX_NUM * 32 - (int)bin.size();
	string zeros; for (int i = 1; i <= t; ++i) zeros += "0";
	// thêm vào cho đủ string độ dài MAX_NUM * 32
	bin = zeros + bin;
	if (bin[0] == '1') {
		// signed bit (~bin + 1)
		for (int i = 0; i < bin.size(); ++i) {
			bin[i] = ((bin[i] - '0') ^ 1) + '0';
		}
		// +1
		int cr = 1;
		for (int i = bin.size() - 1; i >= 0; --i) {
			int t = bin[i] - '0' + cr;
			bin[i] = (t % 2) + '0';
			cr = t / 2;
		}
		return "-" + BinToHexStr(bin);
	}
	for (int i = 0; i < bin.size(); i += 4) {
		int t = 0;
		for (int j = i; j < i + 4; ++j) t = t * 2 + (bin[j] - '0');
		ans += binGroup4ToHex(t);
	}
	return ans;
}

string HexToGroup4Bin(char c) {
	int num = 0;
	if ('0' <= c && c <= '9') num = c - '0';
	else num = 10 + (c - 'A');
	string bin = "";
	for (int i = 3; i >= 0; --i) bin += (num >> i & 1) + '0';
	return bin;
}

string HexToBinStr(string s) {
	bool _signed = s[0] == '-' ? true : false;
	string bin;
	for (int i = _signed; i < s.size(); ++i) bin += HexToGroup4Bin(s[i]);
	if (_signed) {
		// chuyen qua bu` 2
		string zeros;
		for (int i = 1; i <= MAX_NUM * 32 - (int)bin.size(); ++i) zeros += "0";
		bin = zeros + bin;

		for (int i = bin.size() - 1; i >= 0; --i) bin[i] = ((bin[i] - '0') ^ 1) + '0';
		int cr = 1;
		for (int i = bin.size() - 1; i >= 0; --i) {
			int t = bin[i] - '0' + cr;
			bin[i] = (t % 2) + '0';
			cr = t / 2;
		}
	}
	else {
		string zeros;
		for (int i = 1; i <= MAX_NUM * 32 - (int)bin.size(); ++i) zeros += "0";
		bin = zeros + bin;
	}
	return bin;
}

string HexPlusHex(string p, string q) {
	string bin_p = HexToBinStr(p), bin_q = HexToBinStr(q);
	QInt int_p; int_p = int_p.BinToDec(bin_p);
	QInt int_q; int_q = int_q.BinToDec(bin_q);
	QInt ret; ret = int_p + int_q;
	string ret_hex = ret.DecToHex();
	return ret_hex;
}

// End Int

//Start Float

//Chuan hoa so thành dạng x.xxxxxxxxxxE(y)
string normalize(string num) {
	string result = num;
	int dot = num.find(".");
	int count = 0;
	if (dot == string::npos) dot = num.size();

	//Trường hợp số > 10.
	if (dot > 1) {
		count = dot - 1;
		result.erase(dot, 1);
		result.insert(1, ".");
		//Thêm số 0 ở sau nếu chưa đủ 10 số phần thập phân
		if (result.size() < 12)
			result.insert(result.size(), 12 - result.size(), '0');
		//Xóa bớt nếu phần thập phân nhiều hơn 10 số.
		else if (result.size() > 12)
			result.resize(12);
		//Thêm phần mũ
		result.append("E");
		result.append(to_string(count));
	}
	//Trường hợp số < 0.
	if (dot == 1) {
		for (int i = dot + 1; i < num.size(); i++) {
			if (result[i] != '0') break;
			result[i - 1] = '0';
			result[i] = '.';
			dot = i;
			count++;
		}
		//Xóa số 0 ở trước
		result.erase(0, dot - 1);
		if (result.size() < 10)
			result.insert(result.size(), 10 - result.size(), '0');
		//Lấy 10 chữ số phần thập phân
		else if (result.size() > 10)
			result.resize(12);
		//Thêm mũ
		if (count == 0) result.append("E");
		else result.append("-E");
		result.append(to_string(count));
	}
	return result;
}

//Chia 2 day bit.
string Div(string a, string b) {
	string result;
	string curQ;
	string Q = a, M = b;
	for (int i = 0; i < M.size(); i++) {
		if (M[i] == '1') break;
		M.erase(i);
	}
	for (int i = 0; i < Q.size(); i++) {
		curQ += Q[i];
		if (!Less(curQ, M)) {
			result += '1';
			curQ = Sub(curQ, M);
			while (curQ[0] == '0') {
				curQ.erase(0, 1);
			}
		}
		else {
			result += '0';
			while (curQ[0] == '0') {
				curQ.erase(0);
			}
		}

	}
	if (curQ.size() != 0) {
		result += ".";
		for (int i = 0; i < 112; i++) {
			curQ += "0";
			if (!Less(curQ, M)) {
				result += '1';
				curQ = Sub(curQ, M);
				while (curQ[0] == '0') {
					curQ.erase(0, 1);
				}
			}
			else {
				result += '0';
				while (curQ[0] == '0') {
					curQ.erase(0);
				}
			}
			if (curQ.size() == 0) break;
		}
	}
	while (result[0] == '0') {
		result.erase(0, 1);
	}
	if (result[0] == '.')
		result = "0" + result;

	result.resize(112);
	return result;
}

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

string Sub(string a, string b) {
	string ans;
	int max = 0;
	bool rem = 0, curBit = 0;
	if (a.size() > b.size()) {
		max = a.size();
		b.insert(b.begin(), max - b.size(), '0');
	}
	else if (b.size() > a.size()) {
		max = b.size();
		a.insert(a.begin(), max - a.size(), '0');
	}
	else {
		max = a.size();
	}
	for (int i = max - 1; i >= 0; i--) {
		if (a[i] < b[i] + rem) {
			curBit = 2 + a[i] - (b[i] + rem);
			rem = 1;
			ans += char(curBit + 48);
		}
		else {
			curBit = a[i] - (b[i] + rem);
			rem = 0;
			ans += char(curBit + 48);
		}
	}
	return reverse(ans);
}

//Chia đôi số thực
string Div2_float(string num) {
	string res = num;
	int len = num.size();
	int k = 0, tmp = 0, Digit, j = 0, isDot = 0;
	for (int i = 0; i < len; i++) {
		if (num[i] == '.') {
			res[j] = '.';
			isDot = 1;
		}
		else {
			Digit = (num[i] - '0');
			tmp = k * 10 + Digit;
			res[j] = tmp / 2 + '0';
			k = tmp % 2;
		}
		j++;
	}
	if (k == 1)
		if (isDot == 0) res += ".5";
		else res += "5";
	// Xóa 0 ở đầu
	while ((res[0] == '0' && res[1] != '.') && res.size() > 1)res.erase(0, 1);
	return res;
}

// Nhân đôi số thực không âm
string Mul2(string number) {
	vector <int> a, b, resInt, resFraction;
	int pos = number.find('.');
	int dot = 0;
	//x2 phần thập phân
	int remain = 0;
	if (pos != -1) {
		dot = 1;
		for (int i = pos + 1; i < number.size(); ++i) a.push_back(number[i] - '0');
		resFraction.resize(a.size());
		reverse(a.begin(), a.end());
		for (int i = 0; i < a.size(); ++i) {
			resFraction[i] += a[i] * 2 + remain;
			remain = resFraction[i] / 10;
			resFraction[i] %= 10;
		}
	}
	else pos = number.size();

	//x2 Phần nguyên
	for (int i = 0; i < pos; i++)b.push_back(number[i] - '0');
	resInt.resize(b.size());
	reverse(b.begin(), b.end());
	for (int i = 0; i < b.size(); ++i) {
		resInt[i] += b[i] * 2 + remain;
		remain = resInt[i] / 10;
		resInt[i] %= 10;
	}

	if (remain > 0)resInt.push_back(1);

	reverse(resInt.begin(), resInt.end());
	reverse(resFraction.begin(), resFraction.end());
	//Ket qua ans, ghép phần nguyên và thập phân lại

	string ans = "";
	for (int i = 0; i < resInt.size(); i++) ans += '0' + resInt[i];
	if (dot) {
		ans += '.';
		for (int i = 0; i < resFraction.size(); i++) ans += '0' + resFraction[i];
		while (ans.back() == '0')ans.pop_back();
	}
	return ans;
}

string Mul(string a, string b) {
	// Nhân 2 số không âm
	vector <int> aa, bb, cc;
	for (int i = 0; i < a.size(); ++i) aa.push_back(a[i] - '0');
	for (int i = 0; i < b.size(); ++i) bb.push_back(b[i] - '0');
	cc.resize(aa.size() + bb.size());
	reverse(aa.begin(), aa.end());
	reverse(bb.begin(), bb.end());
	for (int i = 0; i < aa.size(); ++i)
		for (int j = 0; j < bb.size(); ++j)
			cc[i + j] += aa[i] * bb[j];
	Fix2(cc);
	string ans;
	for (int i = cc.size() - 1; i >= 0; --i) ans += (cc[i] + '0');
	return ans;
}

//Đảo xâu
string reverse(string a) {
	string result;
	for (int i = a.size() - 1; i >= 0; i--) {
		result += a[i];
	}
	return result;
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
	string fractionBit = "", tmp_after = after;
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
		//Tính toán các bit mantissa
		while (cnt < biased) {
			after = Mul2(after);
			fractionBit.push_back(after[0]);
			after[0] = '0';
			if (fractionBit.back() == '1') break;
			cnt++;

		}

		//Tính toán phần mũ
		power = -(cnt + 1) + biased;

		//Trường hợp số quá nhỏ => Dạng không chuẩn
		if (cnt > biased) {
			//Nhân cho 2 mũ (bias - 1)
			for (int i = 0; i < 16382 - cnt; i++) {
				after = Mul2(after);
			}
			//Tính toán phần mantissa
			cnt = 0;
			fractionBit.clear();
			//Thêm không ở đầu để lúc xử lý sẽ xóa đi
			fractionBit = "0";
			while (cnt < 112) {
				after = Mul2(after);
				fractionBit.push_back(after[0]);
				after[0] = '0';
				cnt++;
			}
			power = 0;
		}

		else {
			//Trường hợp dạng chuẩn
			cnt = 0;
			fractionBit = "1";
			//Tính đến khi hết 112 bit hoặc phần dư  = 0
			while (cnt < 112 && (after.compare("0.0") != 0)) {
				after = Mul2(after);
				fractionBit += after[0];
				after[0] = '0';
				cnt++;
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
	//bit đầu tiên đại diện cho 1.
	while (res.size() < 113) res.push_back('0');
	//debug(res);
	return res;
}

//Add  numbers(string type).
string Add(string a, string b) {
	string result;
	int a_i, b_i;
	bool rem = 0;
	int dotA, dotB, sizeA = a.size(), sizeB = b.size(), dASize, dBSize;

	//Find position of "."
	dotA = a.find(".");
	dotB = b.find(".");

	//If the postition of "." cant be found.
	if (dotA == string::npos) dotA = sizeA - 1;
	if (dotB == string::npos) dotB = sizeB - 1;

	//Get the decimal part.
	string dA = a.substr(dotA + 1, sizeA - dotA - 1), dB = b.substr(dotB + 1, sizeB - dotB - 1);
	dASize = dA.size(); dBSize = dB.size();

	//Add two decimals part.
	for (int i = (dASize > dBSize ? dASize : dBSize) - 1; i >= 0; i--) {
		if (i >= dASize) a_i = 0;
		else a_i = dA[i] - 48;
		if (i >= dBSize) b_i = 0;
		else b_i = dB[i] - 48;
		result.append(1, char((a_i + b_i + rem) % 10 + 48));
		rem = (a_i + b_i + rem) / 10;
	}

	//If one of them has decimals part.
	if (dASize != 0 || dBSize != 0) result.append(".");

	//Get natural parts.
	if (dASize > 0) dA = a.substr(0, dotA);
	else dA = a;
	if (dBSize > 0) dB = b.substr(0, dotB);
	else dB = b;

	dASize = dA.size(); dBSize = dB.size();

	//Reverse dA, dB to make it easy to add two natural parts.
	dA = reverse(dA);
	dB = reverse(dB);
	for (int i = 0; i < (dASize > dBSize ? dASize : dBSize); i++) {
		if (i >= dASize) a_i = 0;
		else a_i = dA[i] - 48;
		if (i >= dBSize) b_i = 0;
		else b_i = dB[i] - 48;
		result.append(1, char((a_i + b_i + rem) % 10 + 48));
		rem = (a_i + b_i) / 10;
	}

	//
	return reverse(result);
}

bool Less(string a, string b) {
	int max = 0;
	if (a.size() > b.size()) {
		max = a.size();
		b.insert(b.begin(), max - b.size(), '0');
	}
	else if (b.size() > a.size()) {
		max = b.size();
		a.insert(a.begin(), max - a.size(), '0');
	}
	else {
		max = a.size();
	}
	for (int i = 0; i < max; i++) {
		if (a[i] != b[i]) return (a[i] == '0');
	}
	return 1;
}

void Fix2(vector <int> &a) {
	static const int BASE = 2;
	a.push_back(0);
	for (int i = 0; i < (int)a.size() - 1; ++i) {
		a[i + 1] += a[i] / BASE; a[i] %= BASE;
		if (a[i] < 0) a[i] += BASE, a[i + 1]--;
	}
	while (a.size() >= 2 && a.back() == 0) a.pop_back();
}

void Fix10(vector <int> &a) {
	static const int BASE = 10;
	a.push_back(0);
	for (int i = 0; i < (int)a.size() - 1; ++i) {
		a[i + 1] += a[i] / BASE; a[i] %= BASE;
		if (a[i] < 0) a[i] += BASE, a[i + 1]--;
	}
	while (a.size() >= 2 && a.back() == 0) a.pop_back();
}

//Ene