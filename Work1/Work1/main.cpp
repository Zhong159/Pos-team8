#include"Item.h"
#include<iostream>
using namespace std;

void Welcome();
bool Check(string);
Item *AppendNode(Item *head);
void Display(Item *head);

void main()
{
	Welcome();
	char con = 'y';
	Item *head = NULL;  //ָ������ͷ
	cout << "Please input goods information:" << endl;
	do {
		head = AppendNode(head);
		cout << endl << "Is there any other goods? Y/y or N/n :";
		cin >> con;
	} while (con == 'Y' || con == 'y');
	Display(head);
}

Item *AppendNode(Item *head)
{
	string barcode;
	int number = 1;
	bool is_barcode = true;

	Item *p = NULL;
	Item *pr = head;

	p = new Item;
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
	do {
		if (is_barcode == false)
			cout << "barcode doesn't exist,please input again:";
		else
			cout << "barcode:";
		cin >> barcode;
		is_barcode = Check(barcode);
	} while (is_barcode == false);
	pr->GetBarcode(barcode);

	do {
		if (number < 1)
			cout << "The number can't be less than 1,please input again:";
		else
			cout << "number:";
		cin >> number;
	} while (number < 1);
	pr->GetNum(number);

	string s;
	ifstream in;
	in.open("goods.txt", ofstream::in);
	if (in)
	{
		while (getline(in, s))
		{
			if (s != "")
			{
				if (s == barcode)
				{
					getline(in, s);
					cout << "name:" << s << endl;
					getline(in, s);
					cout << "unit:" << s << endl;
					getline(in, s);
					cout << "price:" << s << endl;
					getline(in, s);
					if (s != "1.0")
						cout << "discount:" << s << endl;
				}
			}
		}
	}
	pr->next = NULL;
	return head;
}

void Display(Item *head)
{
	double sum = 0;
	double sumNoDiscount = 0;

	Item *p = head;
	cout << endl << "***�̵깺���嵥***" << endl;
	while (p != NULL)
	{
		p->Print();
		sumNoDiscount += p->OutPrice() * p->OutNumber();
		sum += p->OutPrice() * p->OutNumber() * p->OutDiscount();

		p = p->next;
	}
	cout << "----------------------" << endl;
	cout << "�ܼ�:" << sum << "Ԫ" << endl;
	if (sumNoDiscount != sum)
		cout << "��ʡ:" << (sumNoDiscount - sum) << "Ԫ" << endl;
	cout << "**********************" << endl << endl;

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



