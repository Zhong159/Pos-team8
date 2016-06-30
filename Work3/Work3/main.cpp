#include"Item.h"
#include"VIP.h"
#include"Cart.h"
#include"VIPManage.h"
#include <windows.h> 
#include<iostream>
using namespace std;

void Welcome();
bool Check(string);
Cart *AppendNode(Cart *head);  //新建节点
void Display(Cart *head, bool IsVIP, string userName, int &points, int money);      //打印全部商品信息

void main()
{
	Welcome();
	char con = 'y';
	Cart *head = NULL;  //指向链表头

	cout << "Please input goods information:" << endl;
	do {
		head = AppendNode(head);
		cout << endl << "Is there any other goods? Y/y or N/n :";
		cin >> con;
	} while (con == 'Y' || con == 'y');

	VIPManage user;
	string userName;
	bool IsUser;
	bool IsVIP;
	IsUser = user.AskForUser();
	if (IsUser)
	{
		user.InputShoppingCardName();
		IsVIP = user.AskForVIP();
	}
	else
	{
		user.CreateUser();
		IsVIP = user.AskForVIP();
	}
	string name = user.OutShoppingCardName();
	VIP v1(name,IsVIP);
	int points = v1.OutPoints();
	int money = user.OutMoney();
	Display(head,IsVIP,name,points,money);

	v1.SetPoints(points);

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

Cart *AppendNode(Cart *head)
{
	string barcode;
	int number = 1;
	bool is_barcode = true;

	Cart *p = NULL;
	Cart *pr = head;

	p = new Cart;
	if (p == NULL)               //若申请失败则输出错误信息
	{
		cout << "No enough memory to alloc." << endl;
		exit(0);
	}
	if (head == NULL)  //若原链表为空，则将新建节点置为首节点
	{
		head = p;
	}
	else      //若原链表为非空，则将新节点添加到表尾
	{         //若未到表尾，则继续移动指针pr，直到pr指向表尾
		while (pr->next != NULL)
		{
			pr = pr->next;
		}
		pr->next = p;    //将新建节点添加到链表的末尾
	}
	pr = p;    //让pr指向新建节点

    //往指针节点里添加数据
	do {  //添加商品编号
		if (is_barcode == false)
			cout << "barcode doesn't exist,please input again:";
		else
			cout << "barcode:";
		cin >> barcode;
		is_barcode = Check(barcode);
	} while (is_barcode == false);
	pr->GetBarcode(barcode);

	do {    //添加商品数量
		if (number < 1)
			cout << "The number can't be less than 1,please input again:";
		else
			cout << "number:";
		cin >> number;
	} while (number < 1);
	pr->GetNum(number);
	pr->ReadFile(barcode, number);

	//将商品编号和数量输入文件作为备份
	ofstream out("purchased.txt", ios::app);
	if (out.is_open())
	{
		out << barcode << "," << number << endl;
	}
	out.close();
    
	pr->PrintSingle(barcode);

	pr->next = NULL;
	return head;
}

void Display(Cart *head,bool IsVIP,string userName,int &points,int money)
{
	double sum = 0;
	double sumNoDiscount = 0;

	Cart *p = head;
	Cart *pr = head;

	if (!IsVIP)
	{
		while (p != NULL)
		{
			p->Choose();
			p->SettleAccountNotVIP(sum, sumNoDiscount);
			p = p->next;
		};	
	}
	else
	{
		while (p != NULL)
		{
			p->Choose();
			p->SettleAccountVIP(sum, sumNoDiscount);

			p = p->next;
		};
		
	}

	int addPoints = (int)sum / 5;
	if (points >= 0 && points <= 200)
		points += addPoints;
	else if (points >= 200 && points <= 500)
		points += (addPoints * 3);
	else
		points += addPoints * 5;

	cout << endl << "***商店购物清单***" << endl;
	if (IsVIP)
		cout << "会员编号:" << userName << "     会员积分:" << points << endl;
	else
		cout << "用户编号:" << userName << endl;
	cout << "-----------------------------" << endl;

	//输出系统时间
	SYSTEMTIME time;
	GetLocalTime(&time);
	cout <<"打印时间: "<< time.wYear << "年" << time.wMonth << "月" << time.wDay << "日  " << time.wHour << ":" << time.wMinute << ":" << time.wSecond << endl;
	cout << "-----------------------------" << endl;

	if (!IsVIP)
	{
		while (pr != NULL)
		{
			pr->PrintNotVIP();
			pr = pr->next;
		};
	}
	else
	{
		while (pr != NULL)
		{
			pr->PrintVIP();
			pr = pr->next;
		};
	}
	if (money != 0)
	{
		cout << "购买会员:200元"<< endl ;
		sum += 200;
		sumNoDiscount += 200;
	}
	cout << "-----------------------------" << endl;
	cout << "总计:" << sum << "元" << endl;
	if (sumNoDiscount != sum)
		cout << "节省:" << (sumNoDiscount - sum) << "元" << endl;
	cout << "*****************************" << endl << endl;
	
}
