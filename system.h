#ifndef __SYSTEM_H
#define __SYSTEM_H
#include <vector>
#include "seller.h"
#include "buyer.h"
#include "bns.h"
#include "users.h"

class System
{
private:
	vector <Users *> user_arr;
public:
	System();
	~System();
	vector <Users *> & getUserArray();
	int getLogicSize() const;
	void addUser(Users * my_user);
	void approveLogIn( string & name, string & pass);
	Seller * findSeller(const string & name);
	Buyer * findBuyer(const string & name);
	bool checkName(const string & name);
	void LargerCart();
//	void setLogicSize(const int num);
public:
	const System & operator+=(Users & other);
};
#endif // !__System_H