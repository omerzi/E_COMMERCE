#ifndef __ORDER_H
#define __ORDER_H
#include "cart.h"

class Seller;
class Buyer;
class Product;

class  Order
{
private:
	static int counter;//for o_number
	int  o_number;
	Product *o_productArr;
	int o_numberofP = 0;
	int o_price;
public:
	Order(int numberofProduct);
	Order();
	Order(const Order & other);//copy c'tor
	~Order();
public:
	inline void SetPrice(const int price);
	int GetPriceOfOrder() const;
	int GetOrderNumber()const;
	Product *GetProductsArray()const;
	bool SetProductArray();
};
#endif // !__ORDER_H