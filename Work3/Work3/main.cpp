#include"Item.h"
#include"VIP.h"
#include"Cart.h"
#include"VIPManage.h"
#include <windows.h> 
#include<iostream>
using namespace std;

void Welcome();
bool Check(string);
Cart *AppendNode(Cart *head);  //�½��ڵ�
void Display(Cart *head, bool IsVIP, string userName, int &points, int money);      //��ӡȫ����Ʒ��Ϣ

void main()
{
	Welcome();
	char con = 'y';
	Cart *head = NULL;  //ָ������ͷ

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
	if (p == NULL)               //������ʧ�������������Ϣ
	{
		cout << "No enough memory to alloc." << endl;
		exit(0);
	}
	if (head == NULL)  //��ԭ����Ϊ�գ����½��ڵ���Ϊ�׽ڵ�
	{
		head = p;
	}
	else      //��ԭ����Ϊ�ǿգ����½ڵ���ӵ���β
	{         //��δ����β��������ƶ�ָ��pr��ֱ��prָ���β
		while (pr->next != NULL)
		{
			pr = pr->next;
		}
		pr->next = p;    //���½��ڵ���ӵ������ĩβ
	}
	pr = p;    //��prָ���½��ڵ�

    //��ָ��ڵ����������
	do {  //�����Ʒ���
		if (is_barcode == false)
			cout << "barcode doesn't exist,please input again:";
		else
			cout << "barcode:";
		cin >> barcode;
		is_barcode = Check(barcode);
	} while (is_barcode == false);
	pr->GetBarcode(barcode);

	do {    //�����Ʒ����
		if (number < 1)
			cout << "The number can't be less than 1,please input again:";
		else
			cout << "number:";
		cin >> number;
	} while (number < 1);
	pr->GetNum(number);
	pr->ReadFile(barcode, number);

	//����Ʒ��ź����������ļ���Ϊ����
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

	cout << endl << "***�̵깺���嵥***" << endl;
	if (IsVIP)
		cout << "��Ա���:" << userName << "     ��Ա����:" << points << endl;
	else
		cout << "�û����:" << userName << endl;
	cout << "-----------------------------" << endl;

	//���ϵͳʱ��
	SYSTEMTIME time;
	GetLocalTime(&time);
	cout <<"��ӡʱ��: "<< time.wYear << "��" << time.wMonth << "��" << time.wDay << "��  " << time.wHour << ":" << time.wMinute << ":" << time.wSecond << endl;
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
		cout << "�����Ա:200Ԫ"<< endl ;
		sum += 200;
		sumNoDiscount += 200;
	}
	cout << "-----------------------------" << endl;
	cout << "�ܼ�:" << sum << "Ԫ" << endl;
	if (sumNoDiscount != sum)
		cout << "��ʡ:" << (sumNoDiscount - sum) << "Ԫ" << endl;
	cout << "*****************************" << endl << endl;
	
}
