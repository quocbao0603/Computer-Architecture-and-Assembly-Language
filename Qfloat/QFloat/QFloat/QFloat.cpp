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
//Phần xuất
//convert QFloat to bit String
string QFloat::To_bit_string() {
	if (Is_Inf()) {
		if (Is_Negative()) return "-Inf";
		return "Inf";
	}
	if (Is_NaN())
		return "NaN";
	if (Is_Zero())
		return "0";

	// Xét dấu
	bool sign = Get_bit(MAX_BIT - 1);

	// Lấy phần mũ
	int power = 0;
	for (int i = MAX_BIT - 2; i >= MAX_BIT - Exponent - 1; i--) {
		power = power << 1 + Get_bit(i);
	}
	power -= biased;

	// Lấy phần trị
	string s;
	s.clear();
	for (int i = MAX_BIT - Exponent - 2; i >= 0; i--) {
		s.push_back('0' + Get_bit(i));
	}

	// Xét số không chuẩn
	if (power == -biased)
		s = "0" + s;
	else
		s = "1" + s;
	while (power < 0) {
		s = '0' + s;
		power++;
	}

	// Thêm 0 ở đầu cho phần trị
	int n = s.size();
	while (power > s.size())
		s = '0' + s;

	// Xét dấu .
	if (power >= n || power == -1)
		s = "0." + s;
	else if (power >= 0) {
		s.insert(s.begin() + power + 1, '.');
	}

	// Chuẩn hóa chuỗi, không có 0 hay . ở cuối
	while (s.back() == '0') s.pop_back();
	if (s.back() == '.') s.pop_back();

	// Thêm dấu - nếu là số âm
	if (sign) s = '-' + s;
	return s;
}
//convert QFloat to Decimal String
string QFloat::To_dec_string() {
	return "";
};


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
	//debug(before);
	//debug(power);
	string res = Fraction_to_binary(before, after, power);
	//debug(res);
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
	int count = 0;
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
