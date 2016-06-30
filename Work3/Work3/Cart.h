#ifndef CART_H
#define CART_H
#include"Item.h"

class Cart : public Item
{
public:
	Cart *next;
	void SettleAccountNotVIP(double &sum, double &sumNoDiscount);
	void SettleAccountVIP(double &sum, double &sumNoDiscount);
	void Loop();
};

#endif
