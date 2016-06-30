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
	bool isDiscount;
	bool isPromotion;
public:
	Item();
	void Print(string _barcode, int _number);
	void PrintAll();

	void GetBarcode(string barcode);

	double OutPrice();
	double OutDiscount();
};
#endif

