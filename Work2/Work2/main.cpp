#include"Item.h"
#include<iostream>
using namespace std;

void Welcome();
bool Check(string);

void main()
{
	Item goods;
	Welcome();
	char con = 'y';
	string barcode = " ";
	int number = 2;
	bool isBarcode = true;

	cout << "Please input goods information:" << endl;

	//录入商品编号
	do {
		do {
			if (isBarcode == false)
				cout << "barcode doesn't exist,please input again:";
			else
				cout << "barcode:";
			cin >> barcode;
			isBarcode = Check(barcode);
		} while (isBarcode == false);

		//录入商品数量
		do {
			if (number < 1)
				cout << "The number can't be less than 1,please input again:";
			else
				cout << "number:";
			cin >> number;
		} while (number < 1);

		ofstream out("purchased.txt", ios::app);
		if (out.is_open())
		{
				out << barcode << "," << number << endl;
		}
		out.close();

		//打印该商品信息
		string s;
		string s1;
		ifstream in;
		in.open("goods.txt");
		if (in)
		{
			while (getline(in, s))
			{
				if (s == barcode)
				{
					getline(in, s);
					cout  << s << endl;  //打印名称
					getline(in, s);
					cout << s << endl;   //打印规格
					getline(in, s);
					cout << s << endl;   //打印单价

					ifstream in2;
					in2.open("discount.txt");
					if (in2)
					{
						while (getline(in2, s1))
						{
							size_t separator = s1.find(",");
							if (s1.substr(0, separator) == barcode)
							{
								cout << "discount:" << s1.substr(separator + 1, s1.length() -separator - 1) << endl ;
								break;
							}	
						};
						in2.close();
					}

					ifstream in3;
					in3.open("promotion.txt");
					if (in3)
					{
						while (getline(in3, s1))
						{
							if (s1 == barcode)
							{
								cout << "promotion:true" << endl;	
								break;
							}							
						};
						in3.close();
					}
					break;
				}
			}
		}
		in.close();

		cout << endl << "Is there any other goods? Y/y or N/n :";
		cin >> con;
	} while (con == 'Y' || con == 'y');

	
	goods.PrintAll();
	ofstream out("purchased.txt", ios::out);
	out.close();

	system("pause");
}

void Welcome()
{
	cout << "           *****************************************" << endl
		<< endl
		<< endl
		<< endl
		<< endl
		<< "                     Welcome to POS System! " << endl
		<< endl
		<< endl
		<< endl
		<< endl
		<< "           *****************************************" << endl << endl;
	system("pause");
	system("cls");
}

bool Check(string barcode)
{
	ifstream in;
	string s;
	in.open("goods.txt", ofstream::in);
	if (in)
	{
		while (getline(in, s))
		{
			if (s == barcode)
				return true;
		}
		return false;

	}
	in.close();
}