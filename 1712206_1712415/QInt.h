#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

class QInt
{
public:
	string mul2(string);// Hàm nhân 2 cho số lớn
	string div2(string);// Hàm chia 2 cho số lớn
	string add(string, string);// Hàm cộng số lớn
	string LT2(int);// Hàm tính lũy thừa cơ số 2
	QInt Setto2Complement();// Chuyển sang dạng bù 2

	string BinarytoDec();// Hàm chuyển hệ nhị phân sang thập phân (2->10)
	string BinarytoHex();// Hàm chuyển hệ nhị phân sang thập lục phân (2->16)
	QInt DectoBinary(string);// Hàm chuyển hệ thập phân sang nhị phân (10->2)
	QInt HextoBinary(string);// Hàm chuyển hệ thập lục phân sang nhị phân (16->2)
	string DectoHex(string);// Hàm chuyển hệ thập phân sang thập lục phân (10->16)
	string HextoDec(string);// Hàm chuyển hệ thập lục phân sang thập phân (16->10)

	QInt operator>>(int);// Dịch phải số học một số nguyên bit
	QInt operator<<(int);// Dịch trái số học một số nguyên bit

	QInt operator~();// Phép NOT
	QInt operator^(QInt);// Phép XOR
	QInt operator&(QInt);// Phép AND
	QInt operator|(QInt);// phép OR

	QInt Chuan_Hoa();

	QInt operator=(QInt);// Toán tử gán
	QInt operator+(QInt);// Toán tử cộng
	QInt operator-(QInt);// Toán tử trừ
	QInt operator*(QInt);// Toán tử nhân
	QInt operator/(QInt);// Toán tử chia

	QInt ror();// Phép xoay phải 1 bit
	QInt rol();// Phép xoay trái 1 bit

	void scan(string);// Chuyển chuỗi string thành bool*
	void print();// Xuất dạng nhị phân

	/*-constructor-*/
	QInt();
	QInt(bool*, int);
	QInt(const QInt&);

	~QInt();
private:
	bool *BitsArray;//mảng bit
	int length;//độ dài mảng
};

