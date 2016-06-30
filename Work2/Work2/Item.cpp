#include"Item.h"
#include<iostream>
using namespace std;

Item::Item()
{

}


void Item::Print(string _barcode,int _number)
{
	string _name ;
	string _unit ;
	string s1 = "";
	isDiscount = false;
	isPromotion = true;

	ifstream in ;
	in.open("goods.txt");
	if (in)
	{
		while (getline(in, s1))
		{
			if (s1 == _barcode)
			{
				getline(in, s1);
				size_t separator1 = s1.find(":");
				_name = s1.substr(separator1 + 1, s1.length() - separator1 - 1);

				getline(in, s1);
				size_t separator2 = s1.find(":");
				_unit = s1.substr(separator2 + 1, s1.length() - separator2 - 1);

				getline(in, s1);
				size_t separator3 = s1.find(":");
				price = atof((s1.substr(separator3 + 1, s1.length() - separator3 - 1)).c_str());

				ifstream in2;
				in2.open("discount.txt");
				if (in2)
				{
					while (getline(in2, s1))
					{
						size_t separator = s1.find(",");
						if (s1.substr(0, separator) == _barcode)
						{
							discount = atof((s1.substr(separator + 1, s1.length() - separator - 1)).c_str());
							isDiscount = true;
							isPromotion = false;
							break;
						}
					} 
					in2.close();
				}
				if (isPromotion == true)
				{
					ifstream in3;
					in3.open("promotion.txt");
					if (in3)
					{
						while (getline(in3, s1))
						{
							if (s1 == _barcode)
							{
								isPromotion = true ;
								break ;
							}
							isPromotion = false ;
						}
						in3.close();
					}
				}
				break;
			}

			
		}
	}
	in.close();

	if (isDiscount == true)
		cout << "name:" << _name << " ,数量:" << _number << " ,unit:"
			<< _unit << " ,单价:" << price << "元，小计:" << _number * price * discount << "元." << endl;
	else if (isPromotion == true)
		cout << "name:" << _name << " ,数量(含赠送的一瓶):" <<( (_number > 1)?(_number + 1):_number )<< " ,unit:"
			<< _unit << " ,单价:" << price << "元，小计:" << _number * price << "元." << endl;	
	else
		cout << "name:" << _name << " ,数量:" << _number << " ,unit:"
			<< _unit << " ,单价:" << price << "元，小计:" << _number * price << "元." << endl;
}

void Item::PrintAll()
{
	string s1 ;
	double sum = 0;
	double sumNoDiscount = 0;
	string commodityID ;
	int commodityNumber ;
	cout << endl << "                 ***商店购物清单***" << endl;

	ifstream in("purchased.txt", ios::in);
	if (in)
	{
		while (getline(in, s1)) {
			size_t separator = s1.find(",");
			commodityID = s1.substr(0, separator );
			commodityNumber = atoi((s1.substr(separator + 1, s1.length() - separator - 1)).c_str());
			Print(commodityID, commodityNumber);
			if (isDiscount == true)
			{
				sum += OutPrice() * commodityNumber * OutDiscount();
				sumNoDiscount += OutPrice() * commodityNumber;
			}
			else if (isPromotion == true)
			{
				sum += OutPrice() * commodityNumber ;
				sumNoDiscount += OutPrice() * commodityNumber;
				if (commodityNumber > 1)
				{
					sumNoDiscount += price ;
				}
			}
			else
			{
				sumNoDiscount += OutPrice() * commodityNumber;
                sum += OutPrice() * commodityNumber;
			}
		};

		cout << "-----------------------------------------------" << endl;
		cout << "总计:" << sum << "元" << endl;
		if (sumNoDiscount != sum)
			cout << "节省:" << (sumNoDiscount - sum) << "元" << endl;
		cout << "***********************************************" << endl << endl;
	}
	in.close();
}


void Item::GetBarcode(string barcode)
{
	this->barcode = barcode;
}

double Item::OutPrice()
{
	return price;
}

double Item::OutDiscount()
{
	return discount;
}





