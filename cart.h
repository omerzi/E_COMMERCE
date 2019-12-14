#ifndef __CART_H
#define __CART_H

class Product;

class Cart
{
public:
	friend class Buyer;
	friend class Seller;
public:
	Cart();
	Cart(const Cart&other);
	~Cart();
	inline const int GetLogicS() const;
	inline const int GetPhiS() const;
	Product ** getProductArr() const;
	void SetLogicS(int logic);
	void SetPhiS(int phis);
	void PrintCart();

private:
	int c_logicSize;
	int c_phsize;
	Product ** c_prouductArr;
	void SetProductArr(Product **Arr);
};


#endif // !__CART_H

