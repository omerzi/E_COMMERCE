#include "buyer.h"
#include "product.h"
Buyer::Buyer(const char * name, const char * password, Address &add, Cart & cart)
	: b_address(add), b_cart(cart) 
{
	//main c'tor
	setPassword(password);
	setName(name);
	this->b_order = nullptr;
	this->b_order_size = 0;
}
//----------------------------------------------------------------------------------------//
Buyer::Buyer(const Buyer & other)
{//copy c'tor
	setName(other.b_name);
	setAddress(other.b_address);
	setPassword(other.b_password);
}
//----------------------------------------------------------------------------------------//
Buyer::Buyer(Buyer && other)
{
	//move c'tor
	b_name = other.b_name;
	b_address = other.b_address;
	b_password = other.b_password;
	other.b_name = nullptr;
	other.b_password = nullptr;
}
//----------------------------------------------------------------------------------------//
Buyer::~Buyer()
{//d'tor

	delete[] b_name;
	delete[] b_password;
}

//----------------------------------------------------------------------------------------//
void Buyer::setName(const char * name)
{
	//the function sets the buyer's name
	b_name = strdup(name);
}
//----------------------------------------------------------------------------------------//
void Buyer::setAddress(Address address)
{
	//the function sets the buyer's address
	this->b_address.setCity(address.getCity());
	this->b_address.setState(address.getState());
	this->b_address.setStreet(address.getStreet());
}
//----------------------------------------------------------------------------------------//
bool Buyer::setPassword(const char * password)
{
	if (strlen(password) < MIN_PASSWORD_SIZE)
	{
		cout << "The password must contain a least 6 digits or numbers, please enter a new one" << endl;
		return 0; //password didn't match requierments
	}
	else
	{
		b_password = strdup(password);
		return 1; //password has set
	}
}
//----------------------------------------------------------------------------------------//
const char *Buyer::getName() const
{//the function return the buyer's name
	return b_name;
}
//----------------------------------------------------------------------------------------//
const Address Buyer::getAddress() const
{//the function return the buyer's address
	return b_address;
}
//----------------------------------------------------------------------------------------//
const char *Buyer::getPassword()const
{//the function return the buyer's password
	return b_password;
}
//----------------------------------------------------------------------------------------//
Cart Buyer::getCart()
{
	return this->b_cart;
}

//----------------------------------------------------------------------------------------//
void Buyer::addToCart(Product * prod)
{
	if (this->b_cart.c_prouductArr == nullptr)
	{//empty arr
		this->b_cart.c_prouductArr = new Product *[this->b_cart.c_phsize];
		this->b_cart.c_prouductArr[this->b_cart.c_logicSize] = new Product(*prod);
		this->b_cart.c_logicSize++;
	}
	else
	{ // realloc
		if (this->b_cart.c_logicSize == this->b_cart.c_phsize)
		{
			this->b_cart.c_phsize *= 2;
			Product ** new_prod_array = new Product *[this->b_cart.c_phsize];
			for (int i = 0; i < this->b_cart.c_logicSize; i++)
			{
				new_prod_array[i] = this->b_cart.c_prouductArr[i];
			}
			delete[] this->b_cart.c_prouductArr;
			this->b_cart.c_prouductArr = new_prod_array;
		}
		this->b_cart.c_prouductArr[this->b_cart.c_logicSize] = new Product(*prod); //insert new product by ptr
		this->b_cart.c_logicSize++;
	}
}
//----------------------------------------------------------------------------------------//
bool Buyer::findOrder(int num_of_order)
{ // finds a specific order and return true if the order exits, false if it doesn't
	for (int i = 0; i < this->b_order_size; i++)
	{
		if (this->b_order[i]->GetOrderNumber() == num_of_order)
		{
			return true;
		}
	}
	return false;
}
