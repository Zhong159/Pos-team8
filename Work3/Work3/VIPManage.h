#ifndef VIPMANAGE_H
#define VIPMANAGE_H
#include<string>
using namespace std;

class VIPManage 
{
private:
	string shoppingCardName;
	int moneyForVIP;
public:
	VIPManage();
	bool AskForUser();
	bool AskForVIP();
	void InputShoppingCardName();
	bool IsUser(string name);
	bool IsVIP(string name);
	void BecomingVIP(string name);
	void  CreateUser();

	string OutShoppingCardName();
	int OutMoney();
};

#endif
