#include"VIPManage.h"
#include<windows.h>
#include<io.h>
#include<fstream>
#include<sstream>
#include<iostream>
using namespace std;

VIPManage::VIPManage()
{
	moneyForVIP = 0;
}

bool VIPManage::AskForUser()
{
	char shoppingCard;
	cout << endl << "Do you have a shopping card? (Y/y or other character) : ";
	cin >> shoppingCard ;
	if (shoppingCard == 'Y' || shoppingCard == 'y')
		return true;
	else
		return false;
}

bool VIPManage::AskForVIP()
{
	
	bool IsVip = IsVIP(shoppingCardName);
	if (IsVip)
	{
		cout << "You are a VIP，so you can enjoy VIP discount!" << endl;
		return true;
	}
	else
	{
		char becomingVIP;
		cout << "Do you want to become a VIP? (200 yuan for VIP discount forever)" << endl;
        cout <<"Y/y or other character : ";
		cin >> becomingVIP ;
		if (becomingVIP == 'Y' || becomingVIP == 'y')
		{
			BecomingVIP(shoppingCardName);
			cout << "OK! Now,you are a VIP." << endl;
			return true;
		}
		else   return false;
	}
}

void  VIPManage::InputShoppingCardName()
{
	cout << "Please input your shopping card name: ";
	bool isUser = true;
	do {
		if (!isUser)
			cout << "The name doesn't exist,please inout again: ";
		cin >> shoppingCardName;
		isUser = IsUser(shoppingCardName);
	} while (isUser != true);
}


bool VIPManage::IsUser(string name)
{
	ifstream in;
	string s1;
	string s2;
	in.open("user.txt", ofstream::in);
	if (in)
	{
		while (getline(in, s1))
		{
			size_t separator1 = s1.find(" ");
			s2 = s1.substr(0, separator1);
			size_t separator2 = s1.find(":");
			if ((s2.substr(separator2 + 1, s1.length() - separator2 - 1)) == name)
			{
				in.close();
				return true;
			}

		};
		in.close();
		return false;
	}
}

bool VIPManage::IsVIP(string name)
{
	ifstream in;
	string s;
	in.open("VIP.txt", ofstream::in);
	if (in)
	{
		while (getline(in, s))
		{
			size_t separator = s.find(":");
			if ((s.substr(0, separator)) == name)
			{
				return true;
			}
		};
		in.close();
		return false;
	}
}

void VIPManage::BecomingVIP(string name)
{
	string s1;
	string s2;
	string s3;
	ofstream out("AAA.txt", ios::app);
	ifstream in;
	in.open("user.txt");
	if (in)
	{
		while (getline(in, s1))
		{
			
			size_t separator1 = s1.find(" ");
			s2 = s1.substr(0, separator1);
			size_t separator2 = s2.find(":");
			if (s2.substr(separator2 + 1, s1.length() - separator2 - 1) == name)
			{
				
				if (out.is_open())
				{
					out << "name:"<< name << " IsVIP:true"<< endl;
				}
			}
			else
			{
				if (out.is_open())
				{
					out << s1 << endl;
				}
			}

		};
		in.close();
		out.close();
	}
	system("del user.txt");
	
	if (!_access("AAA.txt", 0))//如果文件存在:
	{
		rename("AAA.txt", "user.txt");//重命名成功
	}

	ofstream out2("VIP.txt", ios::app);
	if (out2.is_open())
	{
		out2 << endl << name << ":0" << endl;
	}
	out2.close();
	moneyForVIP = 200;
}

void VIPManage::CreateUser()
{
	ifstream in;

	bool isExist;
	string s1;
	string s2;
	string s3;
	string s4;
	string username = "********";
	cout << "Now,let's create an account,please input a username" << endl;
	cout<<"(between 4 and 10 characters, numbers or underline) : ";
	do {
		if (username.length() < 4 || username.length() > 10)
			cout << "It's invalid,please input again: ";
		in.open("user.txt");
		if (in)
		{
			while (getline(in, s1))
			{
				if (s1 == username)
				{
					cout << "The username exists,please input another username: ";
					isExist = false;
					break;
				}
				isExist = true;
			}
			in.close();
		}
		cin >> username;
	} while (username.length() < 4 || username.length() > 10  || !isExist);

	ofstream out("user.txt", ios::app);
	if (out.is_open())
	{
		out << endl << "name:" << username << " IsVIP:false";
	}
	out.close();

	shoppingCardName = username;
}

string VIPManage::OutShoppingCardName()
{
	return shoppingCardName;
}

int VIPManage::OutMoney()
{
	return moneyForVIP;
}

