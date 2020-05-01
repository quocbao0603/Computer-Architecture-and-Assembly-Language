#include "QInt.h"

//Khoa's part

string QInt::toBinary(){
	string r[MAX_NUM];
	
	string result;
	int n, number_bit = 0;
	for (int i = 0; i < MAX_NUM; i++) {
		n = data[i];
		while (n != 0) {
			r[i] = (n % 2 == 0 ? "0" : "1") + r[i]; 
			n /= 2; 
			number_bit++;
		}
		/*
		if (number_bit < 32) {
			r[i] = 
		}
		*/
		result += r[i];
	}
	return result;
}

void QInt::assign(string bin){
	int lastPos = 0;
	for (int i = 0; i < MAX_NUM; i++) {
		lastPos = i * INT_SIZE - 1;
		data[i] = 0;
		for (int j = i * INT_SIZE; j < (i + 1) * INT_SIZE; j++) {
			data[i] += (bin[j] - 48)*pow(2, (lastPos - j));
		}
	}
}

bool QInt::lastBit(){
	return data[3] & 1;
}

bool QInt::firstBit(){
	if (data[0] < 0) return 1;
	return 0;
}

QInt QInt::operator+(QInt const & a){
	QInt result, tmp_qint = a;
	string k = this->toBinary(), h = tmp_qint.toBinary(), result_bin;
	bool rem = 0;
	int tmp = 0;
	for (int i = QINT_SIZE - 1; i >= 0; i--) {
		tmp = k[i] + h[i] - 96 + rem;
		if (tmp >= 2) {
			tmp -= 2;
			rem = 1;
		}
		else 
			rem = 0;
		result_bin.insert(0, 1,char(tmp + 48));
		
	}
	result.assign(result_bin);
	return result;
}

QInt QInt::operator-(QInt a){
	// Trừ a nghĩa là cộng của trừ a nên lấy số đối của a và dùng toán tử cộng.
	QInt result;
	QInt minusA = ~a, one = 1;
	minusA = minusA + 1;
	result = *this + minusA;
	return result;
}

QInt QInt::operator*(QInt const & a){
	// Thuật toán Booth.
	QInt A = 0, Q = a;

	bool q[2] = { 0 };							//q[0] là Q0, q[1] là Q(-1).

	q[0] = Q.lastBit();
	for (int i = 0; i < QINT_SIZE; i++) {
		if (q[0] == 0 && q[1] == 1) {			//Trường hợp 01.
			A = A + *this;
		}
		else if (q[0] == 1 && q[1] == 0) {		//Trường hợp 10.
			A = A - *this;
		}
		Q >> 1;									//Dịch phải Q 1 bit.
		if (A.lastBit == 1) {					//Lấy bit cuối của A làm bit đầu của Q.
			Q.data[0] = Q.data[0] | INT_MIN;
		}
		else {
			Q.data[0] = Q.data[0] & (INT_MAX);
		}
		q[1] = q[0];							//Cập nhật Q(-1) và Q0.
		q[0] = Q.lastBit();
		A >> 1;									//Dịch phải A 1 bit.
	}
		

	return Q;
}

QInt QInt::operator/(QInt const & a){

	QInt A = 0, Q = a, One  = 1;
	bool sign = (this->firstBit() ^ Q.firstBit());		//Kiểm tra xem hai số ngược dấu nhau.
	for (int i = 0; i <= QINT_SIZE; i++) {				
		A << 1;
		if (Q.firstBit() == 1) {						//
			A.data[3] = A.data[3] | 1;
		}
		else {
			A.data[3] = A.data[3] & (INT_MIN << 1);
		}
		Q << 1;
		A = A - *this;
		if (A < 0) {
			A = A + *this;
			Q.data[3] = Q.data[3] & (INT_MIN << 1);
		}
		else {
			Q.data[3] = Q.data[3] | 1;
		}
	}
	
	if (sign = 1) {
		Q.data[0] = Q.data[0] | INT_MIN;
	}

	return Q;
}

bool QInt::operator<(QInt const & a){
	//Trừ nhau, nếu kq bé hơn 0 thì trả về đúng.
	QInt tmp_result = *this - a;
	if (tmp_result.firstBit() == 1) return 1;
	return 0;
}

bool QInt::operator>(QInt const & a){
	//Trừ ngược lại, nếu kq bé hơn 0 thì trả về đúng.
	QInt tmp = a;
	QInt tmp_result = tmp - *this;
	if (tmp_result.firstBit() == 1) return 1;
	return 0;
}

bool QInt::operator==(QInt const & a){
	for (int i = 0; i < MAX_NUM; i++) {
		if (this->data[i] != a.data[i]) return 0;
	}
	return 1;
}

bool QInt::operator<=(QInt const & a){
	return !(*this > a);
}

bool QInt::operator>=(QInt const & a){
	return !(*this < a);
}

QInt & QInt::operator=(QInt const & a){
	for (int i = 0; i < MAX_NUM; i++) {
		this->data[i] = a.data[i];
	}
	return *this;
}

QInt QInt::operator~(){
	for (int i = 0; i < MAX_NUM; i++)
		this->data[i] = ~(this->data[i]);
}


QInt::QInt(){
	for (int i = 0; i < MAX_NUM; i++)
		data[i] = 0;
}

QInt::QInt(QInt const & a){
	for (int i = 0; i < MAX_NUM; i++)
		data[i] = a.data[i];
}

QInt::QInt(int k){
	data[3] = k;
	if (k < 0) {
		data[0] = data[1] = data[2] = INT_MIN;
	}
}


QInt::~QInt()
{
}




//Bảo's part
//Lấy bit thứ k
int QInt::Get_bit(int k) {
	int i_data = k / 32;
	int k_data = k % 32;
	int res = ((this->data[i_data]) >> k_data) & 1;
	return res;
}
//Bật bit thứ k
void QInt::Turn_on_bit(int k) {
	int i_data = k / 32;
	int k_data = k % 32;
	this->data[i_data] |= (1 << k_data);
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
		int ith_bit = res.Get_bit(i + k);
		if (ith_bit == 1)res.Turn_on_bit(i);
	}
	return res;
}
// Dịch bit trái (dịch số học) của một số QInt
QInt QInt::operator << (int k){
	QInt res; //khởi tạo kết quả: res = 0
	//Nếu dịch quá nhiều thì kết quả = 0
	//if (k >= 128) return res;
	//Dịch phải k bit thì bit thứ i sau khi dịch = bit thứ i - k ban đầu.
	for (int i = MAX_NUM * 32 - 1; i - k >= 0; i--) {
		int ith_bit = res.Get_bit(i - k);
		if (ith_bit == 1)res.Turn_on_bit(i);
	}
	return res;
}
