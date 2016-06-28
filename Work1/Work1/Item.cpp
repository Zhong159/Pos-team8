#include"Item.h"
#include<iostream>
using namespace std;

void Item::ReadFile()
{
	ifstream in;
	string s1 = "";
	in.open("goods.txt", ofstream::in);
	if (in)
	{
		while (getline(in, s1))
		{
			if (s1 == barcode)
			{

				getline(in, s1);
				name = s1;

				getline(in, s1);
				unit = s1;

				getline(in, s1);
				price = atof(s1.c_str());

				getline(in, s1);
				discount = atof(s1.c_str());

				break;
			}
		}
		in.close();
	}

}
void Item::Print()
{
	ReadFile();

	cout << "name:" << name << " ,数量:" << number << " ,unit:" << unit << " ,单价:" << price << "元，小计:" << number * price * discount << "元." << endl;


}

void Item::GetBarcode(string barcode)
{
	this->barcode = barcode;
}

void Item::GetNum(int number)
{
	this->number = number;
}

double Item::OutPrice()
{
	return price;
}

int Item::OutNumber()
{
	return number;
}

double Item::OutDiscount()
{
	return discount;
}





