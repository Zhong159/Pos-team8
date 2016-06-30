#include"Item.h"
#include<iostream>
using namespace std;

void Item::ReadFile(string _barcode, int _number)
{
	ifstream in;
	string s1 = "";
	in.open("goods.txt", ofstream::in);
	if (in)
	{
		while (getline(in, s1))
		{
			if (s1 == _barcode)
			{

				getline(in, s1);
				size_t separator1 = s1.find(":");
				name = s1.substr(separator1 + 1, s1.length() - separator1 - 1);

				getline(in, s1);
				size_t separator2 = s1.find(":");
				unit = s1.substr(separator2 + 1, s1.length() - separator2 - 1);

				getline(in, s1);
				size_t separator3 = s1.find(":");
				price = atof(s1.substr(separator3 + 1, s1.length() - separator3 - 1).c_str());

				break;
			}
		}
		in.close();
	}

	ifstream in2;
	in2.open("discount.txt");
	if (in2)
	{
		while (getline(in2, s1))
		{
			size_t separator = s1.find(",");
			if (s1.substr(0, separator) == _barcode)
			{
				isDiscount = true;
				discount = atof((s1.substr(separator + 1, s1.length() - separator - 1)).c_str());
				break;
			}
			isDiscount = false;
		};
		in2.close();
	}

	ifstream in3;
	in3.open("promotion.txt");
	if (in3)
	{
		while (getline(in3, s1))
		{
			if (s1 == _barcode)
			{
				isPromotion = true ;
				break;
			}
			isPromotion = false;
		};
		in3.close();
	}

	ifstream in4;
	in4.open("VIPDiscount.txt");
	if (in4)
	{
		while (getline(in4, s1))
		{
			size_t separator2 = s1.find(":");
			if (s1.substr(0, separator2) == _barcode)
			{
				isVIPdiscount = true;
				VIPdiscount = atof((s1.substr(separator2 + 1, s1.length() - separator2 - 1)).c_str());
				break;
			}
			isVIPdiscount = false;
		};
		in4.close();
	}

}

void Item::PrintSingle(string _barcode)
{
	//打印该商品信息
	string s;
	string s1;
	ifstream in;
	in.open("goods.txt");
	if (in)
	{
		while (getline(in, s))
		{
			if (s == _barcode)
			{
				getline(in, s);
				cout << s << endl;  //打印名称
				getline(in, s);
				cout << s << endl;   //打印规格
				getline(in, s);
				cout << s << endl;   //打印单价
				break;
			}
		};
		in.close();
	}

	//打印优惠信息(是否有普通折扣)
	ifstream in2;
	in2.open("discount.txt");
	if (in2)
	{
		while (getline(in2, s1))
		{
			size_t separator = s1.find(",");
			if (s1.substr(0, separator) == _barcode)
			{
				cout << "Discount:" << s1.substr(separator + 1, s1.length() - separator - 1) << endl;
				break;
			}
		};
		in2.close();
	}

	//打印优惠信息(是否有买二赠一)
	ifstream in3;
	in3.open("promotion.txt");
	if (in3)
	{
		while (getline(in3, s1))
		{
			if (s1 == _barcode)
			{
				cout << "promotion:true" << endl;
				break;
			}
		};
		in3.close();
	}

	//打印优惠信息(是否有VIP折扣)
	ifstream in4;
	in4.open("VIPDiscount.txt");
	if (in4)
	{
		while (getline(in4, s1))
		{
			size_t separator1 = s1.find(":");
			if (s1.substr(0, separator1) == _barcode)
			{
				cout << "VIPDiscount:" << s1.substr(separator1 + 1, s1.length() - separator1 - 1) << endl;
				break;
			}
		};
		in4.close();
	}
}



void Item::PrintNotVIP()
{
	if (isChoose)
	{
		if (choose == 'd')
		{
			cout << "name:" << name << " ,数量:" << number << " ,unit:"
				<< unit << " ,单价:" << price << "元，小计:" << number * price * discount << "元." << endl;
		}
		else
		{
			cout << "name:" << name << " ,数量(含赠送):" << number+1 << " ,unit:"
				<< unit << " ,单价:" << price << "元，小计:" << number * price << "元." << endl;
		}
	}
	else if (isPromotion && number > 1 && !isDiscount)
	{
		cout << "name:" << name << " ,数量(含赠送):" << number+1 << " ,unit:"
			<< unit << " ,单价:" << price << "元，小计:" << number * price << "元." << endl;
	}
	else if (isDiscount)
	{
		cout << "name:" << name << " ,数量:" << number << " ,unit:"
			<< unit << " ,单价:" << price << "元，小计:" << number * price * discount << "元." << endl;
	}
	else
	{
		cout << "name:" << name << " ,数量:" << number << " ,unit:"
			<< unit << " ,单价:" << price << "元，小计:" << number * price << "元." << endl;
	}
}

void Item::PrintVIP()
{
	if (isChoose)
	{
		if (choose == 'd')
		{
			cout << "name:" << name << " ,数量:" << number << " ,unit:"
				<< unit << " ,单价:" << price << "元，小计:" << number * price * discount << "元." << endl;
		}
		else
		{
			cout << "name:" << name << " ,数量(含赠送):" << number + 1 << " ,unit:"
				<< unit << " ,单价:" << price << "元，小计:" << number * price << "元." << endl;
		}
	}
	else if (isPromotion && number > 1 && !isDiscount)
	{
		cout << "name:" << name << " ,数量(含赠送):" << number + 1 << " ,unit:"
			<< unit << " ,单价:" << price << "元，小计:" << number * price << "元." << endl;
	}
	else if (isDiscount)
	{
		if (!isVIPdiscount)
		{
			cout << "name:" << name << " ,数量:" << number << " ,unit:"
				<< unit << " ,单价:" << price << "元，小计:" << number * price * discount << "元." << endl;
		}
		else
		{
			cout << "name:" << name << " ,数量:" << number << " ,unit:"
				<< unit << " ,单价:" << price << "元，小计:" << number * price * discount * VIPdiscount<< "元." << endl;
		}
	}
	else
	{
		if (!isVIPdiscount)
		{
			cout << "name:" << name << " ,数量:" << number << " ,unit:"
				<< unit << " ,单价:" << price << "元，小计:" << number * price << "元." << endl;
		}
		else
		{
			cout << "name:" << name << " ,数量:" << number << " ,unit:"
				<< unit << " ,单价:" << price << "元，小计:" << number * price * VIPdiscount << "元." << endl;
		}
	}
}

void Item::Choose()
{
	if (isPromotion && number > 1 && isDiscount)
	{
		isChoose = true;
		double count1 = price * discount;
		double count2 = price * number / (number + 1);
		if (count1 < count2)
		{
			cout << endl << "There are two benefits for " << name << ":discount or promotion,which do you choose? " << endl;
			cout << "(discount/d or promotion/p, we recommend the discount) : ";
		}
		else if (count1 > count2)
		{
			cout << endl << "There are two benefit for " << name << ":discount or promotion,which do you choose? " << endl;
			cout << "(discount/d or promotion/p,we recommend the promotion):";
		}
		else
		{
			cout << endl << "There are two benefits for " << name << ":discount or promotion,which do you choose? " << endl;
			cout << "(discount/d or promotion/p, two benefits are the same) : ";

		}
		cin >> choose;
	}
	else   isChoose = false;

}

void Item::GetBarcode(string barcode)
{
	this->barcode = barcode;
}

void Item::GetNum(int number)
{
	this->number = number;
}

string Item::OutName()
{
	return name;
}

string Item::OutUnit()
{
	return unit;
}

double Item::OutVIPDiscount()
{
	return VIPdiscount;
}

double Item::OutPrice()
{
	return price;
}

double Item::OutNumber()
{
	return number;
}

char Item::OutChoose()
{
	return choose;
}

double Item::OutDiscount()
{
	return discount;
}

bool Item::OutIsDiscount()
{
	return isDiscount;
}

bool Item::OutIsPromotion()
{
	return isPromotion;
}

bool Item::OutIsVIPDiscount()
{
	return isVIPdiscount;
}

bool Item::OutIsChoose()
{
	return isChoose;
}






