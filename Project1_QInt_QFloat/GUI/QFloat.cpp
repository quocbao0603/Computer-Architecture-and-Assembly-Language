#include "stdafx.h"
#include "QFloat.h"
#include "utils.h"


//Số biased

//constructor
QFloat::QFloat() {
	for (int i = 0; i < MAX_NUM; i++) data[i] = 0;
}
QFloat::QFloat(const QFloat &other) {
	for (int i = 0; i < MAX_NUM; i++) {
		data[i] = other.data[i];
	}
}

QFloat::QFloat(const string &num) {
	for (int i = 0; i < MAX_NUM; i++) data[i] = 0;
	//Xét 0
	if (num == "0") return;
	//Xét số inf
	if (num == "Inf" || num == "-Inf") {
		for (int i = MAX_BIT - 2; i >= MAX_BIT - 1 - Exponent; i--) {
			Turn_on_bit(i);
		}
		if (num[0] == '-') Turn_on_bit(MAX_BIT - 1);
	}
	//Xét số NaN
	else if (num == "NaN") {
		for (int i = MAX_BIT - 2; i >= MAX_BIT - 1 - Exponent; i--) {
			Turn_on_bit(i);
		}
		if (num[0] == '-') Turn_on_bit(MAX_BIT - 1);
		Turn_on_bit(0);
	}
	else {
		*this = QFloat().Scan_Dec_string_to_QFloat(num);
	}
}


// bit operator
int QFloat::Get_bit(int k) {
	int i = 3 - k / 32, j = k % 32;
	return data[i] >> j & 1;
}

void QFloat::Turn_on_bit(int k) {
	int i = 3 - k / 32, j = k % 32;
	data[i] |= (1 << j);
}

void QFloat::Flip_bit(int k) {
	int i = 3 - k / 32, j = k % 32;
	data[i] ^= (1 << j);
}

void QFloat::Set_bit(int k, int t) {
	if (Get_bit(k) != t) {
		Flip_bit(k);
	}
}


// Kiểm tra số âm
bool QFloat::Is_Negative()  {
	return Get_bit(MAX_BIT - 1);
}

// Kiểm tra = 0
bool QFloat::Is_Zero() {
	for (int i = 0; i < MAX_NUM; i++)
		if (data[i] != 0)
			return false;
	return true;
}



// Kiểm tra số là số INF
bool QFloat::Is_Inf() {
	
	for (int i = MAX_BIT - 2; i >= MAX_BIT - 1 - Exponent; i--)
		if (Get_bit(i) != 1)
			//debug
			//cout << "bit " << i << "\n";
			return false;
	for (int i = MAX_BIT - 1 - Exponent - 1; i >= 0; i--)
		if (Get_bit(i) != 0)
			return false;
	return true;
}

// Kiểm tra là số báo lỗi
bool QFloat::Is_NaN() {
	for (int i = MAX_BIT - 2; i >= MAX_BIT - 1 - Exponent; i--)
		if (Get_bit(i) != 1)
			return false;
	for (int i = MAX_BIT - 1 - Exponent - 1; i >= 0; i--)
		if (Get_bit(i) != 0)
			return true;
	return false;
}

int QFloat::realExponent(){
	int exponent = 0, ex_tmpVal = 1;
	for (int i = 0; i < 15; i++) {
		if (Get_bit(i + 112))
			exponent += ex_tmpVal;
		ex_tmpVal *= 2;
	}
	exponent -= biased;
	return exponent;
}

//Phần xuất
//convert QFloat to bit String
string QFloat::To_bit_string() {
	if (Is_Inf()) {
		if (Is_Negative()) return "-Inf";
		return "Inf";
	}
	if (Is_NaN())
		return "NaN";
	string res = "";
	for (int i = MAX_BIT - 1; i >= 0; i--) {
		res += '0' + Get_bit(i);
	}
	return res;
}
//convert QFloat to Decimal String
// Hàm xuất QFloat dưới dạng chuỗi thập phân
string QFloat::To_dec_string() {
	string result = "0", tmpVal = "0.5";
	// Xét trường hợp các số đặc biệt
	if (Is_Inf()) {
		if (Is_Negative()) return "-Inf";
		return "Inf";
	}
	if (Is_NaN())
		return "NaN";
	if (Is_Zero())
		return "0";

	//Get value of mantissa.	
	for (int i = 111; i >= 0; i--) {
		if (Get_bit(i)) result = Add(result, tmpVal);
		tmpVal = Div2_float(tmpVal);
	}

	//Get exponent Value 
	int exponent = this->realExponent();

	//Unnormalized case
	if (exponent == biased) {
		for (int i = 0; i > exponent; i--) result = Div2_float(result);
	}
	//Normal case
	//Multiply 2^(exponent) to result.
	else {
		result = Add(result, "1");
		//Exponent < 0
		if (exponent < 0)
			for (int i = 0; i > exponent; i--)
				result = Div2_float(result);

		//Exponent > 0 
		else if (exponent > 0)
			for (int i = 0; i < exponent; i++)
				result = Mul2(result);
	}
	
	//Normalize result number
	result =  normalize(result);

	//Negative case.
	if (Get_bit(127)) result = "-" + result;
	return result;
}

void QFloat::fromBin(string num){
	*this = QFloat();
	if (num.size() != 128){
	return;
	}
	for (int i = 0; i < 128; i++) {
		if ((num[i] - 48)) Turn_on_bit(127 - i);
	}
}


//Phần nhập
// covert từ xâu thập phân sang xâu nhị phân
string From_decimal_string_to_bit_string(string num, int &power) {

	int pos = num.find('.');
	//tách phần nguyên và thực
	string before, after;
	if (pos == -1) {
		before = num;
		after = "0";
	}
	else {
		before = num.substr(0, pos);
		after = num.substr(pos);
		after = '0' + after;
	}
	
	// Chuyển string của phần nguyên sang binary
	before = Int_to_binary(before);
	string res = Fraction_to_binary(before, after, power);
	return res;
}

//hàm đọc và xuất
// Đọc số QFloat dưới dạng chuỗi thập phân
QFloat QFloat::Scan_Dec_string_to_QFloat(string num) {
	// Kiểm tra trường hợp đặc biệt
	
	if (num == "Inf" || num == "-Inf") {
		for (int i = MAX_BIT - 2; i >= MAX_BIT - 1 - Exponent; i--) {
			Turn_on_bit(i);
		}
		if (num[0] == '-') Turn_on_bit(MAX_BIT - 1);
		return *this;
	}
	else if (num == "NaN") {
		for (int i = MAX_BIT - 2; i >= MAX_BIT - 1 - Exponent; i--) {
			Turn_on_bit(i);
		}
		if (num[0] == '-') Turn_on_bit(MAX_BIT - 1);
		Turn_on_bit(0);
		
		return *this;
	}
	else if (num == "0") {
		*this = QFloat();
		return *this;
	}
	
	//khởi tạo tất cả bit = 0
	for (int i = 0; i < MAX_NUM; i++) {
		data[i] = 0;
	}
	
	// Xét số âm
	if (num[0] == '-') {
		Turn_on_bit(MAX_BIT - 1);
		num.erase(0, 1);
	}


	// Tìm dãy bit của phần trị và phần mũ
	int power = 0;
	string Bit_string = From_decimal_string_to_bit_string(num, power);
	//debug(Bit_string);
	//debug(power);
	// Gán phần mũ
	for (int i = MAX_BIT - 1 - Exponent; i <= MAX_BIT - 2; i++) {
		Set_bit(i, (power & 1));
		power >>= 1;
	}
		

	// Gán phần trị
	int count = 1;
	for (int i = MAX_BIT - 1 - Exponent - 1; i >= 0; i--)
		Set_bit(i, Bit_string[count++] - '0');
	//for (int i = 0; i < 4; i++)debug(data[i]);
	return (*this);
}

// Đọc số QFloat dưới dạng chuỗi nhị phân
QFloat QFloat::Scan_Bin_string_to_QFloat(string n) {
	if (n == "0" || n == "Inf" || n == "-Inf" || n == "NaN") return QFloat(n);

	//Xét bit dấu
	if (n[0] == '-')Turn_on_bit(MAX_BIT - 1);
	//Tách phần nguyên và thập phân
	string before, after;
	int pos = n.find('.');
	if (pos == -1) {
		before = n;
	}
	else {
		before = n.substr(0, pos);
		after = n.substr(pos + 1);
	}
	//xoá số 0 đầu
	while (before.size() > 1 && before[0] == '0')before.erase(before.begin());
	//Tìm số mũ
	int power = before.size() - 1 + biased;
	// nếu phần nguyên = 0 => chuẩn hoá
	if (before == "") {
		while (after.size() > 0 && after[0] == '0' && power > 1) {
			power--;
			after.erase(after.begin());
		}
		//Trường hợp dạng không chuẩn
		if (power == 1) {
			while (after.size() > 112 + 1)after.pop_back();
		}
	}
	
	//Ghép lại và chuẩn hoá
	string res = before + after;
	while (res.size() < 112)res += '0';

	//Set bit phần mũ
	for (int i = MAX_BIT - 1 - Exponent; i <= MAX_BIT - 2; i++) {
		if (power & 1 == 0)Turn_on_bit(i);
		power >>= 1;
	}	

	//Set bit phần trị
	int count = 0;
	for (int i = MAX_BIT - 1 - Exponent - 1; i >= 0; i--) {
		Set_bit(i, res[count++] - '0');
	}	
	return *this;
}



//Đọc số QFloat từ string 
QFloat QFloat::Scan_QFloat(string n, int b) {
	if (b == 10) return QFloat().Scan_Dec_string_to_QFloat(n);
	if (b == 2) return QFloat().Scan_Bin_string_to_QFloat(n);
}
//in số QFloat he nhi phan
void Print_QFloat(QFloat num) {
	cout << num.To_bit_string() << '\n';
}


//Operator 
QFloat& QFloat::operator = (const QFloat &that) {
for (int i = 0; i < MAX_NUM; i++) {
	this->data[i] = that.data[i];
}
return (*this);
}

QFloat QFloat::operator + (const QFloat &that) {
	// xét các trường hợp đặc biệt
	// cả 2 là NaN

	QFloat other = that;
	if (Is_NaN() || other.Is_NaN()) return QFloat("NaN");
	// 2 số vô cực + nhau
	int x = Is_Inf(), y = other.Is_Inf();
	if (x || y) {
		if (x + y == 2) {
			// cả 2 là vô cực
			// cùng dấu thì ra vô cực, ngược dấu thì ra NaN
			if ((Is_Negative() ^ other.Is_Negative())) {
				// khác dấu
				return QFloat("NaN");
			}
			else return (*this);
		}
		else {
			// một trong 2 là vô cực thì trả về số đó
			// vì vô cực + một số = vô cực
			QFloat ans = x ? (*this) : other;
			return ans;
		}
	}
	// 1 trong 2 số là 0 thì trả về số còn lại
	x = Is_Zero(); y = other.Is_Zero();
	if (x || y) return (x ? other : *this);

	// trường hợp bình thường
	// lấy thông tin
		// lấy dấu
	int sign_a = this->Get_bit(MAX_BIT - 1);
	int sign_b = other.Get_bit(MAX_BIT - 1);


	// lấy số mũ ở dạng biased
	int pw_a = 0, pw_b = 0; int bit = 14;
	for (int i = MAX_BIT - 2; i >= MAX_BIT - 1 - Exponent; --i) {
		pw_a += this->Get_bit(i) * (1 << bit);
		pw_b += other.Get_bit(i) * (1 << bit);
		--bit;
	}
	// nếu phần mũ = 0 --> return opposite number
	if (pw_a == 0) return other;
	if (pw_b == 0) return *this;
	// để tổng quát thì luôn lấy số có pw_a > pw_b để cộng
	if (pw_a < pw_b) return other + (*this);

	// lấy phần trị
	vector <int> significand_a, significand_b;
	for (int i = MAX_BIT - 2 - Exponent; i >= 0; --i) {
		significand_a.push_back(this->Get_bit(i));
		significand_b.push_back(other.Get_bit(i));
	}
	assert(significand_a.size() == 112);

	// hàm kiểm tra 2 dãy bit có < hơn nhau hay không
	auto less = [&](const vector <int> &a, const vector <int> &b) {
		for (int i = 0; i < a.size(); ++i) if (a[i] != b[i]) return a[i] < b[i];
		return false;
	};
	auto sub = [&](const vector <int> &a, const vector <int> &b) {
		// a - b với a >= b; a, b là 2 dãy bit
		int cr = 0;
		vector <int> ret;
		for (int i = a.size() - 1; i >= 0; --i) {
			int t = a[i] - b[i] - cr;
			if (t < 0) {
				t += 2;
				cr = 1;
			}
			else cr = 0;
			ret.push_back(t);
		}
		reverse(ret.begin(), ret.end());
		return ret;
	};
	auto add = [&](const vector <int> &a, const vector <int> &b, int& lst_cr) {
		// a + b với a, b là 2 dãy bit
		int cr = 0;
		vector <int> ret;
		for (int i = a.size() - 1; i >= 0; --i) {
			int t = a[i] + b[i] + cr;
			ret.push_back(t % 2);
			cr = t / 2;
		}
		lst_cr = cr;
		reverse(ret.begin(), ret.end());
		return ret;
	};
	auto modify = [&](vector <int> &r_significand, int &pw) {
		// do nó có dạng 0. nên phải chuẩn hóa
		while (r_significand[0] == 0) {
			r_significand.erase(r_significand.begin());
			r_significand.push_back(0);
			--pw;
		}
		// đem số 1 ra làm phần 1.
		r_significand.erase(r_significand.begin());
		r_significand.push_back(0);
		--pw;
	};

	vector <int> r_significand; // kết quả phần trị
	int pw = pw_a, sign;
	// Case 1: Equal exponent
	if (pw_a == pw_b) {
		if (sign_a ^ sign_b) {
			// khác dấu
			// a - b or b - a
			if (less(significand_a, significand_b)) {
				r_significand = sub(significand_b, significand_a);
				// dấu của số b
				sign = sign_b;
			}
			else if (less(significand_b, significand_a)) {
				r_significand = sub(significand_a, significand_b);
				// dấu của số a
				sign = sign_a;
			}
			else {
				// giống số mũ, giống phần trị mà khác dấu --> 0
				QFloat zero("0");
				return zero;
			}
			// lúc này 1. (do 2 số nghịch dấu) --> 0. rồi --> dịch phải để chuẩn hóa
			modify(r_significand, pw);

		}
		else {
			// cùng dấu
			int lst_cr = 0; // bit nhớ cuối
			r_significand = add(significand_a, significand_b, lst_cr);
			// phần mantisa đã là 1. + 1. = 10. rồi

			++pw;
			r_significand.insert(r_significand.begin(), lst_cr);
			r_significand.pop_back();

			sign = sign_a;
		}
	}
	else {
		// khác số mũ --> dịch để tăng số mũ pw_b
		// dịch lần 1 để lấy số 1.
		++pw_b;
		significand_b.insert(significand_b.begin(), 1);
		significand_b.pop_back();
		// các lần dịch sau add số 0 vào
		while (pw_b < pw_a) {
			++pw_b;
			significand_b.insert(significand_b.begin(), 0);
			significand_b.pop_back();
		}
		if (sign_a ^ sign_b) { // khác dấu
			// số a luôn lớn hơn số b rồi --> dấu luôn là của số a
			// trừ bit phần trị
			if (less(significand_a, significand_b)) {
				// phải mượn nhớ nên 1. --> 0. rồi
				r_significand = sub(significand_a, significand_b);
				// lúc này phải chuẩn hóa lại
				modify(r_significand, pw);
			}
			else {
				r_significand = sub(significand_a, significand_b);
			}
			sign = sign_a;
		}
		else { // cùng dấu
			// 1. + 0. = 1. nên không sao
			int lst_cr = 0;
			r_significand = add(significand_a, significand_b, lst_cr);
			if (lst_cr) {
				// có nhớ bit 1 --> 1. + 1. = 10.
				++pw;
				r_significand.insert(r_significand.begin(), 0);
				r_significand.pop_back();
			}
			sign = sign_a;
		}
	}
	QFloat ans;
	ans.Set_bit(MAX_BIT - 1, sign);
	bit = 14; // gồm 14 bit ở phần exponent
	for (int i = MAX_BIT - 2; i >= MAX_BIT - 1 - Exponent; --i) {
		ans.Set_bit(i, pw >> bit & 1);
		--bit;
	}
	assert(bit == -1);
	assert(r_significand.size() == 112);
	int p = 0;
	for (int i = MAX_BIT - 2 - Exponent; i >= 0; --i) {
		ans.Set_bit(i, r_significand[p++]);
	}
	return ans;
}

QFloat QFloat::operator - (const QFloat &that) {
	QFloat other = that;
	other.Set_bit(MAX_BIT - 1, !other.Get_bit(MAX_BIT - 1));
	return (*this + other);
}

QFloat QFloat::operator *(QFloat other) {
	QFloat that = *this;
	//Nếu 1 trong 2 là số Nan 
	if (Is_NaN() || other.Is_NaN())return QFloat("NaN");
	//Nếu 2 số đều oo
	if (Is_Inf() && other.Is_Inf()) {
		bool sign1 = Is_Negative();
		bool sign2 = other.Is_Negative();
		if (sign1 && sign2) return QFloat("-Inf");
		if (!sign1 && !sign2)return QFloat("Inf");
		return QFloat("NaN");

		return QFloat("NaN");
	}
	if (Is_Inf()) {
		if (Is_Negative()) return QFloat("-Inf");
		else return QFloat("Inf");
	}
	if (other.Is_Inf()) {
		if (Is_Negative()) return QFloat("-Inf");
		else return QFloat("Inf");
	}
	if (Is_Zero())return *this;
	if (other.Is_Zero()) return other;
	//xét dấu
	bool sign = that.Get_bit(MAX_BIT - 1) ^ other.Get_bit(MAX_BIT - 1);
	//xét mũ & cộng mũ
	int e1 = 0, e2 = 0, e = 0;
	for (int i = 0; i < 15; i++) {
		e1 += (1 << i) * that.Get_bit(MAX_BIT - 1 - Exponent + i);
		e2 += (1 << i) * other.Get_bit(MAX_BIT - 1 - Exponent + i);
	}
	e = e1 + e2 - biased;
	if (e1 == 0) return other;
	if (e2 == 0) return that;
	//debug(e);
	//Lấy phần trị, thêm số 1 vô đầu tiên để thuật toán chạy đúng
	string a = "1", b = "1";
	for (int i = MAX_BIT - 1 - Exponent - 1; i >= 0; i--) {
		a.push_back('0' + that.Get_bit(i));
		b.push_back('0' + other.Get_bit(i));
	}
	string res = Mul(a, b);
	int dot = res.size() - (112 + 112);
	//chuẩn hoá
	//debug(dot);
	if (dot > 1) {
		e += dot - 1;
		dot = 1;
	}


	//set bit dấu
	if (sign) that.Turn_on_bit(MAX_BIT - 1);
	//Set bit mũ
	for (int i = MAX_BIT - Exponent - 1; i < MAX_BIT - 1; i++) {
		that.Set_bit(i, e & 1);
		e >>= 1;
	}
	//Set bit trị
	int count = 1;
	for (int i = MAX_BIT - Exponent - 2; i >= 0; i--) {
		that.Set_bit(i, res[count++] - '0');
	}
	return that;
}

QFloat QFloat::operator/(QFloat b) {
	bool sign1 = 0, sign2 = 0;

	if (this->Is_NaN() || b.Is_NaN() || (this->Is_Inf() && b.Is_Inf()))
		return QFloat("NaN");

	if (this->Is_Zero())
		return QFloat("0");

	if (b.Is_Zero())
		return QFloat("NaN");

	if (this->Is_Zero() && b.Is_Inf())
		return QFloat("0");

	if (this->Is_Inf() && (!b.Is_Zero())) {
		sign1 = this->Get_bit(127);
		sign2 = b.Get_bit(127);
		if ((sign1 == 0 && sign2 == 1) || (sign1 == 1 && sign2 == 0))
			return QFloat("-Inf");
		return QFloat("Inf");
	}


	int ex1 = this->realExponent();
	int ex2 = b.realExponent();

	string ma1 = this->To_bit_string();
	string ma2 = b.To_bit_string();

	ma1 = ma1.substr(16, 112);
	ma2 = ma2.substr(16, 112);

	if (ex1 == -biased)
		ma1 = "0" + ma1;
	else
		ma1 = "1" + ma1;

	if (ex2 == -biased)
		ma2 = "0" + ma2;
	else
		ma2 = "1" + ma2;

	int int_resultEx = ex1 - ex2;
	if (int_resultEx > biased) return QFloat("Inf");
	if (int_resultEx < (-biased + 1)) return QFloat("-Inf");

	string resultMa = Div(ma1, ma2);

	string resultEx;
	while (resultMa[0] == '0' && resultMa[1] == '.') {
		resultMa.erase(resultMa.begin(), resultMa.begin() + 2);
		resultMa.insert(1, ".");
		resultMa += "0";
		int_resultEx--;
	}
	if (int_resultEx < 0) {
		resultEx = "011111111111111";
		int count = 8192;
		int_resultEx = -int_resultEx;
		for (int i = 1; i < 15; i++) {
			if (count <= int_resultEx) {
				resultEx[i] = '0';
				int_resultEx -= count;
			}
			count /= 2;
		}
	}
	else {
		resultEx = "100000000000000";
		int count = 8192;
		int_resultEx -= 1;
		for (int i = 1; i < 15; i++) {
			if (count <= int_resultEx) {
				resultEx[i] = '1';
				int_resultEx -= count;
			}
			count /= 2;
		}
	}
	resultMa.erase(resultMa.begin(), resultMa.begin() + 2);
	resultMa += "00";
	string resultSi;
	if ((sign1 == 0 && sign2 == 1) || (sign1 == 1 && sign2 == 0)) {
		resultSi = "1";
	}
	else
		resultSi = "0";

	string result = resultSi + resultEx + resultMa;
	QFloat ans;
	ans.fromBin(result);
	return ans;

}