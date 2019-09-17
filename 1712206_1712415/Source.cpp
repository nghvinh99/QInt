#include "QInt.h"
#include <sstream>
using namespace std;

// chuyển chuỗi số (string) thành số nguyên (int)
int string_to_num(string a)
{
	int result = 0;
	while (a != "")
	{
		result = result * 10 + ((int)a[0] - 48);
		a.erase(a.begin());
	}
	return result;
}

// xử lí trường hợp thực hiện các phép tính
void math_operator_process(string line)
{
	string type;
	string a, op, b;
	QInt aa, bb;

	istringstream iss;
	iss.str(line);//đưa dữ liệu vào buffer
	iss >> type >> a >> op >> b;

	if (type == "2")
	{
		aa.scan(a);
		bb.scan(b);
	}
	else if (type == "10")
	{
		aa = aa.DectoBinary(a);
		bb = bb.DectoBinary(b);
	}
	else if (type == "16")
	{
		aa = aa.HextoBinary(a);
		bb = bb.HextoBinary(b);
	}

	QInt result;

	if (op == "+") result = aa + bb;
	else if (op == "-") result = aa - bb;
	else if (op == "*") result = aa * bb;
	else if (op == "/") result = aa / bb;
	else if (op == "&") result = aa & bb;
	else if (op == "|") result = aa | bb;
	else if (op == "^") result = aa ^ bb;
	else if (op == ">>") result = aa >> string_to_num(b);
	else if (op == "<<") result = aa << string_to_num(b);

	if (type == "2")
		result.print();
	else if (type == "10")
		cout << result.BinarytoDec() << endl;
	else if (type == "16")
		cout << result.BinarytoHex() << endl;
}


// xử lí trường hợp chuyển hệ, xoay...
void transform_process(string line)
{
	string type1, type2;
	string a;
	QInt aa;

	istringstream iss;

	iss.str(line);
	iss >> type1 >> type2 >> a;

	if (type1 == "2")
		aa.scan(a);
	else if (type1 == "10")
		aa = aa.DectoBinary(a);
	else if (type1 == "16")
		aa = aa.HextoBinary(a);

	if (type2 == "2")
	{
		aa.print();
		return;
	}
	else if (type2 == "10")
	{
		cout << aa.BinarytoDec() << endl;
		return;
	}
	else if (type2 == "16")
	{
		cout << aa.BinarytoHex() << endl;
		return;
	}

	QInt result;

	if (type2 == "rol") result = aa.rol();
	else if (type2 == "ror") result = aa.ror();
	else if (type2 == "~") result = ~aa;

	if (type1 == "2")
		result.print();
	else if (type1 == "10")
		cout << result.BinarytoDec() << endl;
	else if (type1 == "16")
		cout << result.BinarytoHex() << endl;
}

// đếm số lần xuất hiện kí tự t trong chuỗi str
int strcount(string str, char t)
{
	int count = 0;
	for (int i = 0; i < str.length(); i++)
		if (str[i] == t)
			count++;
	return count;
}

int main(int argc, char* args[])
{
	freopen(args[1], "rt", stdin);
	freopen(args[2], "wt", stdout);

	string line;
	while (!cin.eof())
	{
		getline(cin, line);//đọc dòng
		if (strcount(line, ' ') == 3)
			math_operator_process(line);
		else
			transform_process(line);
	}
}