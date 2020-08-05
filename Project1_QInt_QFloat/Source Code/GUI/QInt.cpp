#include "stdafx.h"
#include "QInt.h"
#include "utils.h"

// check số âm và lấy ngược
bool QInt::Negative() {
	int t = (*this).Get_bit(MAX_NUM * 32 - 1);
	return t == 1;
}
QInt QInt::opposite() { // -5 --> 5, 5 --> -5
	QInt ans = *this;
	return ~ans + QInt("1");
}

bool QInt::Zero() {
	for (int i = 0; i < MAX_NUM; ++i) 
		if (data[i] != 0) 
			return false;
	return true;
}

QInt QInt::shl(int k) {
	QInt res;
	for (int i = MAX_NUM * 32 - 1; i - k >= 0; i--) {
		int ith_bit = (*this).Get_bit(i - k);
		if (ith_bit == 1)res.Turn_on_bit(i);
	}
	return res;
}
// hàm in và xuất
void ScanQInt(QInt &num) {
	string s;
	cin >> s;
	QInt tmp(s);
	num = tmp;
}
void PrintQInt(QInt num) {
	string t = "0";
	for (int i = MAX_NUM * 32 - 2; i >= 0; --i) {
		int bit = num.Get_bit(i);
		if (bit & 1) t = AddInt(t, Power2(i));
	}
	if (num.Get_bit(MAX_NUM * 32 - 1)) {
		t = SubInt(Power2(MAX_NUM * 32 - 1), t);
		t = "-" + t;
	}
	cout << t << '\n';
}

string QInt::toDecString() {
	string t = "0";
	for (int i = MAX_NUM * 32 - 2; i >= 0; --i) {
		int bit = this->Get_bit(i);
		if (bit & 1) t = AddInt(t, Power2(i));
	}
	if (this->Get_bit(MAX_NUM * 32 - 1)) {
		t = SubInt(Power2(MAX_NUM * 32 - 1), t);
		t = "-" + t;
	}
	return t;
}

// end

// setting for constructor

QInt::QInt() {
	for (int i = 0; i < MAX_NUM; ++i) data[i] = 0;
}

QInt::QInt(const QInt &that) {
	for (int i = 0; i < MAX_NUM; ++i) data[i] = that.data[i];
}

QInt::QInt(const string &s) {
	for (int i = 0; i < MAX_NUM; ++i) data[i] = 0;
	string unsigned_num;
	for (int i = (s[0] == '-' ? 1 : 0); i < (int)s.size(); ++i) unsigned_num += s[i];
	// khoi tao so (+) truoc voi string unsigned_num
	string dec = unsigned_num;
	for (int i = MAX_NUM * 32 - 1; i >= 0; --i) {
		string pw2 = Power2(i);
		if (LessInt(pw2, dec)) {
			dec = SubInt(dec, pw2);
			// turn on bit i
			Turn_on_bit(i);
		}
		if (dec == "0") break;
	}
	if (s[0] == '-')
		*this = opposite();
}




// bit operator
int QInt::Get_bit(int k) {
	int i = 3 - k / 32, j = k % 32;
	return data[i] >> j & 1;
}

void QInt::Turn_on_bit(int k) {
	int i = 3 - k / 32, j = k % 32;
	data[i] |= (1 << j);
}

void QInt::Flip_bit(int k) {
	int i = 3 - k / 32, j = k % 32;
	data[i] ^= (1 << j);
}

void QInt::Set_bit(int k, int t) {
	if (Get_bit(k) != t) {
		Flip_bit(k);
	}
}

// Toán tử AND
QInt QInt::operator & (QInt other) {
	QInt res; //Biến lưu kết quả
			  //lần lượt duyệt qua từng cụm 32 bit của this, AND với từng cụm 32 bit của other.
	for (int i = 0; i < MAX_NUM; i++) {
		res.data[i] = this->data[i] & other.data[i];
	}
	return res;
}

// Toán tử OR
QInt QInt::operator | (QInt other) {
	QInt res; //Biến lưu kết quả
			  //lần lượt duyệt qua từng cụm 32 bit của this, OR với từng cụm 32 bit của other.
	for (int i = 0; i < MAX_NUM; i++) {
		res.data[i] = this->data[i] | other.data[i];
	}
	return res;
}

// Toán tử XOR
QInt QInt::operator ^ (QInt other) {
	QInt res; //Biến lưu kết quả
			  //lần lượt duyệt qua từng cụm 32 bit của this, XOR với từng cụm 32 bit của other.
	for (int i = 0; i < MAX_NUM; i++) {
		res.data[i] = this->data[i] ^ other.data[i];
	}
	return res;
}

// Toán tử NOT (lưu ý "~" not "!")
QInt QInt::operator ~ () {
	//lần lượt thực hiện phép NOT theo từng cụm 32 bit của this
	for (int i = 0; i < MAX_NUM; i++) {
		this->data[i] = ~this->data[i];
	}
	return *this;
}

// Dịch bit phải (dịch số học) của một số QInt
QInt QInt::operator >> (int k) {
	QInt res; //khởi tạo kết quả: res = 0
			  //Nếu dịch quá nhiều thì kết quả = 0
			  //if (k >= 128) return res;
			  //Dịch phải k bit thì bit thứ i sau khi dịch = bit thứ i + k ban đầu.
	for (int i = 0; i + k < MAX_NUM * 32; i++) {
		int ith_bit = (*this).Get_bit(i + k);
		if (ith_bit == 1) res.Turn_on_bit(i);
	}
	// k bit trái nhất sẽ fill là bit dấu (do dịch số học)
	bool t = (*this).Negative();
	if (t == true)
		for (int i = MAX_NUM * 32 - k; i < MAX_NUM * 32; ++i)
			res.Turn_on_bit(i);

	return res;
}

// Dịch bit trái (dịch số học) của một số QInt
QInt QInt::operator << (int k) {
	QInt res; //khởi tạo kết quả: res = 0
			  //Nếu dịch quá nhiều thì kết quả = 0
			  //if (k >= 128) return res;
			  //Dịch phải k bit thì bit thứ i sau khi dịch = bit thứ i - k ban đầu.
	for (int i = MAX_NUM * 32 - 1; i - k >= 0; i--) {
		int ith_bit = this->Get_bit(i - k);
		if (ith_bit == 1)res.Turn_on_bit(i);
	}

	// check bit dấu
	bool t = (*this).Negative();
	if (t == true) {
		res.Turn_on_bit(MAX_NUM * 32 - 1);
	}
	return res;
}

// Function

QInt QInt::operator + (QInt const& a) {
	QInt res;
	QInt tmp = a;
	int cr = 0; // nhớ
	for (int i = 0; i < MAX_NUM * 32; ++i) {
		int t = Get_bit(i) + tmp.Get_bit(i) + cr;
		cr = t / 2;
		if (t % 2) res.Turn_on_bit(i);
	}
	return res;
}
QInt QInt::operator - (QInt  a) {
	// chuyển sang opposite rồi cộng
	a = a.opposite();
	return (*this) + a;
}

QInt QInt::RollLeft(int k) {
	// dich trai k byte
	if (k > 128) k = k - 128;
	QInt res;
	for (int i = MAX_NUM * 32 - 1; i - k >= 0; --i) {
		int t = Get_bit(i - k);
		if (t & 1)
			res.Turn_on_bit(i);
	}
	// bit k - 1 se la bit MAX_NUM * 32 - 1
	// bit k - 2 se la bit MAX_NUM * 32 - 2
	for (int i = 1; i <= k; ++i) {
		int t = Get_bit(MAX_NUM * 32 - i);
		if (t & 1)
			res.Turn_on_bit(k - i);
	}
	return res;
}

QInt QInt::RollRight(int k) {
	// dich phai k byte
	if (k > 128) k = k - 128;
	QInt res;
	for (int i = 0; i + k < MAX_NUM * 32; ++i) {
		int t = Get_bit(i + k);
		if (t & 1)
			res.Turn_on_bit(i);
	}
	// bit k - 1 se la bit MAX_NUM * 32 - 1
	// bit k - 2 se la bit MAX_NUM * 32 - 2

	// pattern: k - 1 k - 2 ..... (dich phai k bit)
	int ptr = MAX_NUM * 32 - 1;
	for (int i = k - 1; i >= 0; --i) {
		int t = Get_bit(i);
		if (t & 1)
			res.Turn_on_bit(ptr);
		--ptr;
	}
	return res;
}


QInt QInt::operator * (QInt const& that) {
	QInt A; int carry = 0;
	QInt Q = *this, M = that;
	QInt M_two_compliment = M.opposite();
	int cnt = 128;
	while (cnt > 0) {
		if (Q.Get_bit(0) == 0 && carry == 1) {
			A = A + M;
		}
		else if (Q.Get_bit(0) == 1 && carry == 0) {
			A = A + M_two_compliment;
		}
		carry = Q.Get_bit(0);
		Q = Q >> 1;
		// bit thu 127 cua Q sẽ gán bằng bit 0 cua A
		Q.Set_bit(127, A.Get_bit(0));
		A = A >> 1;
		--cnt;
	}
	// nối 2 dãy bit A Q ta sẽ được đáp án, nhưng nó là 128 + 128 = 256 bit thì tràn số ==> chỉ lấy ở Q là đủ
	return Q;
} //Toán tử nhân

QInt QInt::operator / (QInt const& a) {
	QInt res, temp = a;
	if (temp.Zero()) {
		// lỗi chia 0
		return res;
	}
	else {
		int sign = 1;
		QInt Q = *this, M = a; // return Q / M
		if (Q.Negative()) {
			sign *= -1;
			Q = Q.opposite();
		}
		if (M.Negative()) {
			sign *= -1;
			M = M.opposite();
		}
		int cnt = MAX_NUM * 32;
		QInt A;
		QInt minus_M = M.opposite();
		while (cnt > 0) {
			A = A.shl(1);
			// bit 0 cua A se la bit 127 cua Q
			A.Set_bit(0, Q.Get_bit(127));
			Q = Q.shl(1);
			A = A + minus_M;
			if (A.Negative()) {
				A = A + M;
			}
			else {
				Q.Set_bit(0, 1);
			}
			--cnt;
		}
		if (sign == -1) {
			Q = Q.opposite();
		}
		return Q;
	}
} //Toán tử chia

// converting based function

string QInt::DecToBin() {
	// convert *this to Binary
	string bin; bin.resize(MAX_NUM * 32);
	for (int i = 0; i < MAX_NUM * 32; ++i) {
		int t = Get_bit(i);
		bin[MAX_NUM * 32 - i - 1] = t + '0';
	}
	return bin;
}

QInt QInt::BinToDec(string bin) {
	QInt res;
	int t = MAX_NUM * 32 - bin.size();
	string zeros; for (int i = 1; i <= t; ++i) zeros += "0";
	// thêm vào cho đủ string độ dài MAX_NUM * 32
	bin = zeros + bin;
	for (int i = 0; i < MAX_NUM * 32; ++i) if (bin[i] == '1') {
		res.Turn_on_bit(MAX_NUM * 32 - i - 1);
	}
	return res;
}

string QInt::DecToHex() {
	// convert *this to Hex
	if (Negative()) return "-" + opposite().DecToHex();
	string bin = DecToBin();
	return BinToHexStr(bin); // hàm này ở utils
}

// compare function
bool QInt::operator < (QInt const& a) {
	// so sánh từng bit
	QInt tmp = a;
	for (int i = MAX_NUM * 32 - 1; i >= 0; --i) {
		int x = Get_bit(i), y = tmp.Get_bit(i);
		if (x != y) 
			return x < y;
	}
	return false;
}

bool QInt::operator > (QInt const& a) {
	QInt x = *this, y = a;
	return y < x;
}

bool QInt::operator == (QInt const& a) {
	QInt x = *this, y = a;
	return !(x < y || y < x);
}

bool QInt::operator <= (QInt const& a) {
	return (*this) < a || (*this) == a;
}
bool QInt::operator >= (QInt const& a) {
	return (*this) > a || (*this) == a;
}

QInt& QInt::operator = (QInt const& a) {
	for (int i = 0; i < MAX_NUM; ++i)
		this->data[i] = a.data[i];
	return *this;
}
