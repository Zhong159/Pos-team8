#include"Cart.h"
#include<iostream>

using namespace std;

void Cart::SettleAccountNotVIP(double &sum, double &sumNoDiscount)
{
	if (OutIsChoose())
	{
		if (OutChoose() == 'd')
		{
			sum += OutPrice() * OutNumber() * OutDiscount();
			sumNoDiscount += OutPrice() * OutNumber();
		}
		else
		{
			sum += OutPrice() * OutNumber();
			sumNoDiscount += OutPrice() * (OutNumber() + 1);
		}
	}
	else if (OutIsPromotion() && OutNumber() > 1 && !OutIsDiscount())
	{
		sum += OutPrice() * OutNumber();
		sumNoDiscount += OutPrice() * (OutNumber() + 1);
	}
	else if (OutIsDiscount())
	{
		sum += OutPrice() * OutNumber() * OutDiscount();
		sumNoDiscount += OutPrice() * OutNumber();
	}
	else
	{
		sum += OutPrice() * OutNumber();
		sumNoDiscount += OutPrice() * OutNumber();
	}
}
void Cart::SettleAccountVIP(double &sum, double &sumNoDiscount)
{
	if (OutIsChoose())
	{
		if (OutChoose() == 'd')
		{
			sum += OutPrice() * OutNumber() * OutDiscount();
			sumNoDiscount += OutPrice() * OutNumber();
		}
		else
		{
			sum += OutPrice() * OutNumber();
			sumNoDiscount += OutPrice() * (OutNumber() + 1);
		}
	}
	else if (OutIsPromotion() && OutNumber() > 1 && !OutIsDiscount())
	{
		sum += OutPrice() * OutNumber();
		sumNoDiscount += OutPrice() * (OutNumber() + 1);
	}
	else if (OutIsDiscount())
	{
		if (!OutIsVIPDiscount())
		{
			sum += OutPrice() * OutNumber() * OutDiscount();
			sumNoDiscount += OutPrice() * OutNumber();
		}
		else
		{
			sum += OutPrice() * OutNumber() * OutDiscount() * OutVIPDiscount();
			sumNoDiscount += OutPrice() * OutNumber();
		}
	}
	else
	{
		if (!OutIsVIPDiscount())
		{
			sum += OutPrice() * OutNumber();
			sumNoDiscount += OutPrice() * OutNumber();
		}
		else
		{
			sum += OutPrice() * OutNumber() * OutVIPDiscount();
			sumNoDiscount += OutPrice() * OutNumber();
		}
	}
}

void Cart::Loop()
{

}


