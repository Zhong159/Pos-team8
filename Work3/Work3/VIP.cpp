#include"VIP.h"
#include<iostream>
#include<io.h>
#include<fstream>
using namespace std;

VIP::VIP(string name,bool IsVIP)
{
	this->name = name;
	this->IsVIP = IsVIP;
	ifstream in;
	string s1;
	if (IsVIP == true)
	{
		in.open("VIP.txt");
		if (in)
		{
			while (getline(in, s1))
			{
				size_t separator = s1.find(":");
				if (s1.substr(0, separator) == name)
				{
					points = atoi((s1.substr(separator + 1, s1.length() - separator - 1)).c_str());
					break;
				}
			};
			in.close();
		}
	}
	
}

string VIP::OutName()
{
	return name;
}

int VIP::OutPoints()
{
	return points;
}

void VIP::SetPoints(int points)
{
	this->points = points;
	string s1;
	string s2;
	ofstream out("BBB.txt", ios::app);
	ifstream in;
	in.open("VIP.txt");
	if (in)
	{
		while (getline(in, s1))
		{
			size_t separator1 = s1.find(":");
			s2 = s1.substr(0, separator1);
			if (s2 == name)
			{

				if (out.is_open())
				{
					out << name << ":" << points << endl;
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
	system("del VIP.txt");

	if (!_access("BBB.txt", 0))//如果文件存在:
	{
		rename("BBB.txt", "VIP.txt");//重命名成功
	}
}


