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
	int number;
	double discount;
	double VIPdiscount;
	bool isDiscount;
	bool isPromotion;
	bool isVIPdiscount;
	bool isChoose;
	char choose;
public:
	void ReadFile(string _barcode,int _number);
	void PrintSingle(string _barcode);
	void PrintNotVIP();
	void PrintVIP();
	
	void Choose();

	void GetBarcode(string barcode);
	void GetNum(int number);

	string OutName();
	string OutUnit();
	double OutVIPDiscount();
	double OutPrice();
	double OutNumber();
	char OutChoose();
	double OutDiscount();
	bool OutIsDiscount();
	bool OutIsPromotion();
	bool OutIsVIPDiscount();
	bool OutIsChoose();
};
#endif


