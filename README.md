# QInt
Convert and calculate on decimal, binary and hexadecimal made by 1712206 and 1712415

# A. How to install
1. sample 1
2. Do nothing
3. Do thing none

## Requirements
o ABC

## Steps to do
o Nothing
O none

# B. Credentials
user: `vinh`
pass: 12345678

Sample code:
```C++
string QInt::mul2(string obj)
{
	int temp; //lưu số khi đổi từ chuỗi sang số
	int remember = 0; //lưu giá trị nhớ khi cộng
	string result = ""; //lưu kết quả
	for (int i = obj.length() - 1; i >= 0; i--)
	{
		temp = (int)obj[i] - 48; //chuyển kí tự thành số
		temp = temp * 2 + remember;	//nhân 2 và cộng giá trị nhớ
		remember = 0;			//xóa giá trị nhớ
		remember += temp / 10;	//lưu giá trị nhớ mới
		temp = temp % 10;		//lấy phần được đưa vào chuỗi
		result = (char)(temp + 48) + result;//đưa số vào chuỗi kết quả
	}
	if (remember != 0)		//kiểm tra giá trị nhớ, nếu còn thì cộng vào chuỗi kết quả
		result = (char)(remember + 48) + result;
	if (result == "") result = "0";
	return result;
}
```

# C. Instruction
Nothing to guide people here. Do it yourself.

# D. License
_MIT_

# E. Misc
\*this is for testing*\
