#include "QInt.h"

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