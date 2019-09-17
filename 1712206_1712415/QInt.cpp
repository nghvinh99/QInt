#include "QInt.h"

// Hàm nhân 2 cho số lớn
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

// Hàm chia 2 cho số lớn
string QInt::div2(string obj)
{
	string result = "";// lưu kết quả
	int temp = 0; //lưu số khi đổi từ chuỗi sang số
	for (int i = 0; i < obj.length(); i++)
	{
		temp = temp * 10 + (int)obj[i] - 48; // chuyển kí tự thành số
		result = result + (char)(temp / 2 + 48);
		temp = temp - (temp / 2) * 2;// khởi tạo lại giá trị cho temp
	}
	while (result[0] == '0') result.erase(result.begin());//xóa giá trị 0 ở đầu
	if (result == "") result = "0";
	return result;
}

// Hàm cộng số lớn
string QInt::add(string a, string b)
{
	int mode = 0; //kiểm soát trường hợp có dấu trừ ở a,b
	if (a[0] == '-')
		if (b[0] == '-')// a,b đều âm ==> mode=3
		{
			a.erase(a.begin());
			b.erase(b.begin());
			mode = 3;
		}
		else //a âm, b dương ==> mode=1
		{
			a.erase(a.begin());
			mode = 1;
		}
	else
		if (b[0] == '-') // a dương , b âm ==> mode = 2
		{
			b.erase(b.begin());
			mode = 2;
		}
	// a, b dương ==> mode =0
	while (a.length() > b.length()) b = "0" + b; //
	while (b.length() > a.length()) a = "0" + a; //cân bằng chiều dài 2 chuỗi a,b

	int temp_a, temp_b; //lưu giá trị số chuyển đổi từ chuỗi a,b
	int temp_res;//lưu giá trị phép cộng từng cặp số
	int remember = 0;//lưu giá trị nhớ khi cộng
	string result = "";//lưu kết quả
	bool neg = false;//kết quả có dấu âm hay ko (true/false)
	if (a < b) //đảm bảo giá trị lớn hơn được lưu ở a (hỗ trợ phép trừ)
	{
		string med = a;		//
		a = b;				//swap
		b = med;			//
		if (mode == 2)
			neg = true;
	}
	else
	{
		if (mode == 1)
			neg = true;
	}
	if ((mode == 1) || (mode == 2)) //trường hợp có 1 số âm (phép trừ)
	{
		for (int i = a.length() - 1; i >= 0; i--)
		{
			temp_a = (int)a[i] - 48;
			temp_b = (int)b[i] - 48;
			{
				temp_res = temp_a - temp_b - remember;
				remember = 0;// xóa giá trị nhớ
				if (temp_res < 0)
				{
					temp_res = 10 + temp_res; //*****
					remember += 1;
				}
				result = (char)(temp_res + 48) + result;
			}
		}
	}
	else
	{//phép cộng 2 số cùng dấu
		for (int i = a.length() - 1; i >= 0; i--)
		{
			temp_a = (int)a[i] - 48;
			temp_b = (int)b[i] - 48;
			{
				temp_res = temp_a + temp_b + remember;
				remember = 0;
				remember = temp_res / 10;
				temp_res = temp_res % 10;
				result = (char)(temp_res + 48) + result;
			}
		}
		if (remember != 0) result = (char)(remember + 48) + result;// số dư cuối cùng
	}
	while (result[0] == '0') result.erase(result.begin());// xóa những số 0 ở đầu
	if ((result != "") && ((mode == 3) || (neg == true)))//thêm dấu trừ trường hợp kết quả là số âm
		result = '-' + result;
	if (result == "") result = "0";
	return result;
}

// Hàm tính lũy thừa cơ số 2
string QInt::LT2(int n)
{
	string result = "1";
	for (int i = 0; i < n; i++)
		result = mul2(result);
	return result;
}

// Hàm tìm bù 2
QInt QInt::Setto2Complement()
{
	QInt result;
	result = ~*this;// Đảo bit
	int remember = 1;// Lưu giá trị nhớ khi cộng bit
	int i = 0;// Biến chạy
	while ((remember != 0) && (i < result.length))
	{
		if (result.BitsArray[i] == 0)
		{
			result.BitsArray[i] = 1;
			remember = 0;
		}
		else
			result.BitsArray[i] = 0;
		i++;
	}
	while ((result.BitsArray[result.length - 1] == 0) && (result.length > 1)) result.length--;
	return result;
}

// Hàm chuyển hệ nhị phân sang thập phân (2->10)
string QInt::BinarytoDec()
{
	string result = "";// lưu kết quả
	int i = length - 1;// biến đếm
	if ((i == 127) && (BitsArray[i] == 1))//bit thứ 128 là 1
	{
		result = "-" + LT2(127);
	}
	else
		if (BitsArray[i] == 1)
		{
			result = LT2(i);
		}
		else
			result = "0";
	for (int j = i - 1; j >= 0; j--)
	{
		if (BitsArray[j] == 1)
			result = add(result, LT2(j));
	}
	while (result[0] == '0') result.erase(result.begin());// xóa những số 0 ở đầu
	if (result == "") result = "0";
	return result;
}

// Hàm chuyển hệ nhị phân sang thập lục phân (2->16)
string QInt::BinarytoHex()
{
	string result = "";//lưu kết quả
	int i = 0;//biến đếm
	int temp;//biến tạm tính giá trị mỗi 4 bit
	while (i <= length - 1)
	{
		if (i <= length - 1)
			temp = BitsArray[i] * 1;//tính bit 1/4
		if (i + 1 <= length - 1)
			temp = temp + BitsArray[i + 1] * 2;//tính bit 2/4
		if (i + 2 <= length - 1)
			temp = temp + BitsArray[i + 2] * 4;//tính bit 3/4
		if (i + 3 <= length - 1)
			temp = temp + BitsArray[i + 3] * 8;//tính bit 4/4
		if (temp < 10)
			result = (char)(temp + 48) + result;
		else
			result = (char)(temp + 55) + result;//temp-10+65
		i += 4;
	}
	while (result[0] == '0') result.erase(result.begin());// xóa những số 0 ở đầu
	if (result == "") result = "0";
	return result;
}

// Hàm chuyển hệ thập phân sang nhị phân (10->2)
QInt QInt::DectoBinary(string obj)
{
	bool neg = false;//số nguyên có dấu âm hay không (true/false)
	if (obj[0] == '-')
	{
		neg = true;
		obj.erase(obj.begin());
	}
	string temp = obj;
	int i = 0;//biến đếm số bit
	string remember; //lưu giá trị dư khi chia
	string sub_result = "";//lưu tạm dãy bit dưới dạng string
	while (temp != "0")
	{
		remember = add(temp, "-" + mul2(div2(temp)));//remember=temp-(temp/2)*2
		sub_result = sub_result + remember;
		i++;
		temp = div2(temp);
	}
	QInt result;
	result.length = i;
	result.BitsArray = (bool*)calloc(result.length, sizeof(bool));//cấp phát vùng nhớ
	for (i = 0; i < result.length; i++)
		result.BitsArray[i] = (int)sub_result[i] - 48;//chép các bit qua BitsArray
	if (neg == true)
		result = result.Setto2Complement();
	while ((result.BitsArray[result.length - 1] == 0) && (result.length > 1)) result.length--;//xóa các bit 0 ở đầu
	if (result.length == 0)
	{
		result.length = 1;
		result.BitsArray = (bool*)calloc(1, sizeof(bool));
		result.BitsArray[0] = 0;
	}
	return result;
}

// Hàm chuyển hệ thập lục phân sang nhị phân (16->2)
QInt QInt::HextoBinary(string obj)
{
	int k = 0;//biến chạy
	QInt result;
	result.BitsArray = (bool*)calloc(obj.length() * 4, sizeof(bool));//cấp phát vùng nhớ
	int temp;//lưu số thập phân được chuyển từ mỗi kí tự hex
	for (int i = obj.length() - 1; i >= 0; i--)
	{
		if ((int)obj[i] >= 65)
			temp = (int)obj[i] - 55;
		else
			temp = (int)obj[i] - 48;//chuyển kí tự thành số thập phân tương ứng
		for (int j = 0; j < 4; j++)//chuyển sang hệ nhị phân
		{
			if (temp != 0)
			{
				result.BitsArray[k] = temp % 2;
				temp = temp / 2;
			}
			else
				result.BitsArray[k] = 0;
			k++;
		}
	}
	result.length = k;
	while ((result.BitsArray[result.length - 1] == 0) && (result.length > 1)) result.length--;//xóa các bit 0 ở đầu
	return result;
}

// Hàm chuyển hệ thập phân sang thập lục phân (10->16)
string QInt::DectoHex(string obj)
{
	QInt temp;
	temp = temp.DectoBinary(obj);
	return temp.BinarytoHex();
}

// Hàm chuyển hệ thập lục phân sang thập phân (16->10)
string QInt::HextoDec(string obj)
{
	QInt temp;
	temp = temp.HextoBinary(obj);
	return temp.BinarytoDec();
}

// Hàm dịch phải số học
QInt QInt::operator>>(int bits_count)
{
	bool Left_bit;//lưu lại giá trị bit trái cùng trường hợp 128 bit
	QInt temp = *this;// biến trung gian khởi tạo bằng cách truyền QInt this
	QInt result;//lưu kết quả
	int k = temp.length + bits_count;// biến tạm lưu length của result

	result.BitsArray = (bool*)calloc(k, sizeof(bool));// cấp phát vùng nhớ cho result
	result.length = k;

	if (temp.length == 128)
		Left_bit = temp.BitsArray[temp.length - 1];
	else
		Left_bit = 0;// kiểm tra và lưu bit trái cùng trong dịch bit số học

	for (int i = 0; i < result.length; i++)
		result.BitsArray[i] = Left_bit;
	for (int i = 0; i < temp.length - bits_count; i++)//dịch các bit sang phải bits_count đơn vị
		result.BitsArray[i] = temp.BitsArray[i + bits_count];
	while (result.length > 128)// xóa các bit thừa
		result.length--;
	while ((result.BitsArray[result.length - 1] == 0) && (result.length > 1)) result.length--;//xóa các bit 0 ở đầu
	return result;
}

// Hàm dịch trái số học
QInt QInt::operator<<(int bits_count)
{
	QInt temp = *this;//biến trung gian khởi tạo bằng cách truyền this->BitsArray vào
	QInt result;//lưu kết quả
	int k = temp.length + bits_count;// biến tạm lưu length của result
	result.BitsArray = (bool*)calloc(k, sizeof(bool));// cấp phát vùng nhớ cho result
	result.length = k;

	for (int i = 0; i < result.length; i++)
		result.BitsArray[i] = 0;

	for (int i = result.length - 1; i >= bits_count; i--)//dịch các bit sang trái bits_count đơn vị
	{
		result.BitsArray[i] = temp.BitsArray[i - bits_count];
	}
	while (result.length > 128)// xóa các bit thừa
		result.length--;
	while ((result.BitsArray[result.length - 1] == 0) && (result.length > 1)) result.length--;//xóa các bit 0 ở đầu
	return result;
}

// Hàm NOT
QInt QInt::operator~()
{
	bool temp[128];
	QInt result;//lưu kết quả
	for (int i = 0; i < 128; i++)
		temp[i] = 0;
	for (int i = 0; i < length; i++)
		temp[i] = BitsArray[i];
	for (int i = 0; i < 128; i++)// đảo bit
	{
		if (temp[i] == 0)
			temp[i] = 1;
		else
			temp[i] = 0;
	}
	int i = 128;
	while (temp[i - 1] == 0) i--;// xóa các số 0 ở đầu sau khi đảo bit
	result.length = i; // cập nhật lại chiều dài bit
	result.BitsArray = (bool*)calloc(result.length, sizeof(bool));// cấp phát vùng nhớ mới
	for (i = 0; i < result.length; i++)
		result.BitsArray[i] = temp[i];
	return result;
}

// Hàm XOR
QInt QInt::operator^(QInt b)
{
	QInt a = *this;
	QInt result;//lưu kết quả
	int temp_length;
	if (a.length < b.length)//tìm độ dài dãy bit ngắn và khởi gán cho result dãy bit dài
	{
		temp_length = a.length;
		result.BitsArray = (bool*)calloc(b.length, sizeof(bool));
		result.length = b.length;
		for (int i = 0; i < result.length; i++)
			result.BitsArray[i] = b.BitsArray[i];
	}
	else
	{
		temp_length = b.length;
		result.BitsArray = (bool*)calloc(a.length, sizeof(bool));
		result.length = a.length;
		for (int i = 0; i < result.length; i++)
			result.BitsArray[i] = a.BitsArray[i];
	}
	for (int i = 0; i < temp_length; i++)
	{
		if (a.BitsArray[i] == b.BitsArray[i])
			result.BitsArray[i] = 0;
		else
			result.BitsArray[i] = 1;
	}
	return result;
}

// Phép AND
QInt QInt::operator&(QInt b)
{
	QInt a = *this;
	QInt result;//lưu kết quả
	int temp_length;
	if (a.length < b.length)//tìm độ dài dãy bit ngắn và khởi gán cho result dãy bit dài
	{
		temp_length = a.length;
		result.BitsArray = (bool*)calloc(b.length, sizeof(bool));
		result.length = b.length;
		for (int i = 0; i < result.length; i++)
			result.BitsArray[i] = 0;
	}
	else
	{
		temp_length = b.length;
		result.BitsArray = (bool*)calloc(a.length, sizeof(bool));
		result.length = a.length;
		for (int i = 0; i < result.length; i++)
			result.BitsArray[i] = 0;
	}
	for (int i = 0; i < temp_length; i++)
	{
		if (a.BitsArray[i] == 1 && b.BitsArray[i] == 1)
			result.BitsArray[i] = 1;
		else
			result.BitsArray[i] = 0;
	}
	while ((result.BitsArray[result.length - 1] == 0) && (result.length > 1)) result.length--;//xóa các bit 0 ở đầu
	return result;
}

// Phép OR
QInt QInt::operator|(QInt b)
{
	QInt a = *this;
	QInt result;//lưu kết quả
	int temp_length;
	if (a.length < b.length)//tìm độ dài dãy bit ngắn và khởi gán cho result dãy bit dài
	{
		temp_length = a.length;
		result.BitsArray = (bool*)calloc(b.length, sizeof(bool));
		result.length = b.length;
		for (int i = 0; i < result.length; i++)
			result.BitsArray[i] = b.BitsArray[i];
	}
	else

	{
		temp_length = b.length;
		result.BitsArray = (bool*)calloc(a.length, sizeof(bool));
		result.length = a.length;
		for (int i = 0; i < result.length; i++)
			result.BitsArray[i] = a.BitsArray[i];
	}
	for (int i = 0; i < temp_length; i++)
	{
		if (a.BitsArray[i] == 0 && b.BitsArray[i] == 0)
			result.BitsArray[i] = 0;
		else
			result.BitsArray[i] = 1;
	}
	return result;
}

// Toán tử gán
QInt QInt::operator=(QInt b)
{
	if (BitsArray != NULL) free(BitsArray);
	length = b.length;
	BitsArray = (bool*)calloc(length, sizeof(bool));
	for (int i = 0; i < length; i++)
		BitsArray[i] = b.BitsArray[i];
	return *this;
}

// Toán tử cộng
QInt QInt::operator+(QInt b)
{
	QInt a = *this;
	QInt result;//lưu kết quả
	QInt temp;// biến tạm khi cân bằng hai dãy bit
	int flag;// biến lưu giá trị khi cộng hai dãy bit
	bool remember = 0;// biến lưu giá trị dư khi cộng
	//gán dãy bit ngắn hơn cho temp và cân bằng độ dài của chúng
	if (a.length > b.length)
	{
		temp.BitsArray = (bool*)calloc(a.length, sizeof(bool));
		temp.length = a.length;
		for (int i = 0; i < temp.length; i++)
		{
			if (i >= b.length)temp.BitsArray[i] = 0;
			else temp.BitsArray[i] = b.BitsArray[i];
		}
		b = temp;
	}
	else
	{
		temp.BitsArray = (bool*)calloc(b.length, sizeof(bool));
		temp.length = b.length;
		for (int i = 0; i < temp.length; i++)
		{
			if (i >= a.length)temp.BitsArray[i] = 0;
			else temp.BitsArray[i] = a.BitsArray[i];
		}
		a = temp;

	}
	result.BitsArray = (bool*)calloc(temp.length + 1, sizeof(bool));// cấp phát vùng nhớ cho result
	result.length = temp.length + 1;
	for (int i = 0; i < temp.length; i++)
	{
		flag = a.BitsArray[i] + b.BitsArray[i] + remember;
		if (flag == 0)
		{
			result.BitsArray[i] = 0;
			remember = 0;
		}
		else if (flag == 1)
		{
			result.BitsArray[i] = 1;
			remember = 0;
		}
		else if (flag == 2)
		{
			result.BitsArray[i] = 0;
			remember = 1;
		}
		else if (flag == 3)
		{
			result.BitsArray[i] = 1;
			remember = 1;
		}
	}
	result.BitsArray[result.length - 1] = remember;
	while (result.length > 128)// xóa các bit vượt qua bit thứ 128
		result.length--;
	while ((result.BitsArray[result.length - 1] == 0) && (result.length > 1)) result.length--;//xóa các bit 0 ở đầu
	return result;
}

// Toán tử trừ
QInt QInt::operator-(QInt b)
{
	QInt a = *this;
	QInt result;// lưu kết quả
	b = b.Setto2Complement();// chuyển b sang dạng bù 2
	result = a + b;
	return result;
}

// đưa dãy bit về 128 bit
QInt QInt::Chuan_Hoa()
{
	QInt result;//lưu kết quả
	result.BitsArray = (bool*)calloc(128, sizeof(bool));//
	result.length = 128;// khởi tạo và cấp vùng nhớ cho result
	for (int i = 0; i < 128; i++)// tạo result dài 128 bit và có giá trị của *this
	{
		if (i < (*this).length)
			result.BitsArray[i] = (*this).BitsArray[i];
		else
			result.BitsArray[i] = 0;
	}
	return result;
}

// Toán tử nhân
QInt QInt::operator*(QInt b)
{
	QInt a = *this;
	bool remember = 0;//biến Q0
	QInt extra;//biến phụ A
	QInt Minus_b = b.Setto2Complement(); //--//nên gán bù 2 cho một biến rồi + ->>nhanh hơn

	b = b.Chuan_Hoa();// đưa b về dãy 128 bit
	a = a.Chuan_Hoa();// đưa a về dãy 128 bit

	extra = extra.DectoBinary("0");
	int n = 128;
	while (n > 0)
	{
		// hai bit cuối là 01 ==> extra = extra + b
		if (a.BitsArray[0] == 0 && remember == 1)
		{
			extra = extra + b;
		}
		// hai bit cuối là 01 ==> extra = extra - b
		else if (a.BitsArray[0] == 1 && remember == 0)
		{
			extra = extra + Minus_b;
		}
		// dịch phải dãy bit [extra,a,remember]
		remember = a.BitsArray[0];
		a = a >> 1;
		a = a.Chuan_Hoa();// đưa a về dãy 128 bit
		a.BitsArray[127] = extra.BitsArray[0];
		extra = extra >> 1;
		extra = extra.Chuan_Hoa();// đưa extra về dãy 128 bit
		n--;
	}
	while ((a.BitsArray[a.length - 1] == 0) && (a.length > 1)) a.length--;//xóa các bit 0 ở đầu
	return a;
}

// Toán tử chia
QInt QInt::operator/(QInt M)
{
	bool neg = false;//true khi kết quả cần đảo dấu
	QInt Q;
	if (((*this).length == 128) && ((*this).BitsArray[length - 1] == 1))
	{
		Q = (*this).Setto2Complement();
		neg = !neg;
	}
	else
		Q = *this;
	if ((M.length == 128) && (M.BitsArray[M.length - 1] == 1))
	{
		M = M.Setto2Complement();
		neg = !neg;
	}
	QInt Minus_M = M.Setto2Complement();//bù 2 của M
	int k = 128;//biến chạy

	QInt temp;//mảng phụ
	temp.BitsArray = (bool*)calloc(k, sizeof(bool));
	temp.length = k;
	for (int i = 0; i < temp.length; i++)
		temp.BitsArray[i] = 0;//khởi gán mảng phụ

	while (k > 0)//thuật toán chia trong slide
	{
		temp = temp << 1;
		if (Q.length == 128)
			temp.BitsArray[0] = Q.BitsArray[Q.length - 1];
		Q = Q << 1;
		temp = temp + Minus_M;
		if ((temp.length == 128) && (temp.BitsArray[temp.length - 1] == 1))
		{
			temp = temp + M;
			Q.BitsArray[0] = 0;
		}
		else
			Q.BitsArray[0] = 1;
		k--;
	}
	while ((Q.BitsArray[Q.length - 1] == 0) && (Q.length > 1)) Q.length--;//xóa các bit 0 ở đầu
	if (neg) Q = Q.Setto2Complement();//nếu kết quả có đảo dấu thì tìm bù 2 của Q
	return Q;
}

// Phép xoay phải 1 bit
QInt QInt::ror()
{
	QInt result;
	if (BitsArray[0] == 1)
	{
		result.length = 128;
		result.BitsArray = (bool*)calloc(result.length, sizeof(bool));
		for (int i = 1; i < length; i++)
		{
			result.BitsArray[i - 1] = BitsArray[i];
		}
		result.BitsArray[result.length - 1] = 1;
	}
	else
	{
		result = *this >> 1;
	}
	while ((result.BitsArray[result.length - 1] == 0) && (result.length > 1)) result.length--;//xóa các bit 0 ở đầu
	return result;
}

// Phép xoay trái 1 bit
QInt QInt::rol()
{
	QInt result;
	if (length == 128)
	{
		if (BitsArray[127] == 1)
		{
			result.length = 128;
			result.BitsArray = (bool*)calloc(result.length, sizeof(bool));
			for (int i = length - 1; i >= 1; i--)
			{
				result.BitsArray[i] = BitsArray[i - 1];
			}
			result.BitsArray[0] = 1;
		}
	}
	else
	{
		result = *this << 1;
	}
	while ((result.BitsArray[result.length - 1] == 0) && (result.length > 1)) result.length--;//xóa các bit 0 ở đầu
	return result;
}

// Chuyển chuỗi bit (string) thành mảng bool (bool*) các bit
void QInt::scan(string str)
{
	length = str.length();
	BitsArray = (bool*)calloc(length, sizeof(bool));
	for (int i = 0; i < length; i++)
	{
		BitsArray[length - i - 1] = (int)str[i] - 48;
	}
}

// Xuất dãy bit
void QInt::print()
{
	while ((BitsArray[length - 1] == 0) && (length > 1)) length--;//xóa các bit 0 ở đầu
	for (int i = length - 1; i >= 0; i--)
		cout << BitsArray[i];
	cout << endl;
}

/*--------Constructor----------*/
QInt::QInt()
{
	BitsArray = NULL;
	length = 0;
}

QInt::QInt(bool *src, int size)
{
	length = size;
	BitsArray = (bool*)calloc(length, sizeof(bool));
	for (int i = 0; i < length; i++)
		BitsArray[length - i - 1] = src[i];
}

QInt::QInt(const QInt &src)
{
	length = src.length;
	BitsArray = (bool*)calloc(length, sizeof(bool));
	for (int i = 0; i < length; i++)
		BitsArray[i] = src.BitsArray[i];
}

QInt::~QInt()
{
	if (BitsArray != NULL)
		free(BitsArray);
}
