#ifndef ITEM_H
#define ITEM_H
#include<fstream>
#include<string>
using namespace std;

class Item
{
private:
	string barcode;
	string name;
	string unit;
	double price;
	double discount;
	int number;

	void ReadFile();
public:
	Item *next;

	void Print();
	void GetBarcode(string barcode);
	void GetNum(int number);

	double OutPrice();
	int OutNumber();
	double OutDiscount();


};
#endif

