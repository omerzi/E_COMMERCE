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
	for (int i = 0; i < this->b_order_size; i++)
		delete this->b_order[i];
	delete[] this->b_order;
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
Cart & Buyer::getCart()
{
	return this->b_cart;
}
//----------------------------------------------------------------------------------------//
bool Buyer::findOrder(int num_of_order)
{ // finds a specific order and return true if the order exits and already paid, false if it doesn't
	for (int i = 0; i < this->b_order_size; i++)
	{
		if (this->b_order[i]->GetOrderNumber() == num_of_order)
		{
			if (this->b_order[i]->getPaymentSatus() == true)
			{
				return true;
			}
		}
	}
	return false;
}
//----------------------------------------------------------------------------------------//
Order ** Buyer::GetOrderArray() const
{
	return this->b_order;
}
//----------------------------------------------------------------------------------------//
void Buyer::SetOrderLogicSize(const int size)
{
	this->b_order_size = size;
}
//----------------------------------------------------------------------------------------//
void Buyer::AddOrderToOrderArr(Order * order)
{
	if (this->b_order == nullptr)
	{//empty arr
		this->b_order = new Order*;
		this->b_order[0] = new Order(*order);
		this->b_order_size++;
	}
	else
	{ // realloc
		Order ** new_order_array = new Order *[this->b_order_size+1];
		int size = this->b_order_size;
		for (int i = 0; i < size; i++)
		{
			new_order_array[i] = this->b_order[i];
		}
		delete[] this->b_order;
		this->b_order = new_order_array;
		this->b_order[this->b_order_size] = new Order(*order); //insert new order by ptr
		this->b_order_size++;
	}

}
//----------------------------------------------------------------------------------------//
int Buyer::getOrderlogicsize() const
{
	return this->b_order_size;
}
//----------------------------------------------------------------------------------------//
void Buyer::printBuyer()
{
	cout << "- Buyer's Name : " << this->getName() << endl;
	cout << "- Buyer's Address : " << this->b_address.getState() << ", " << this->b_address.getCity() << ", " << this->b_address.getStreet() << endl;
	if (this->b_order_size == 0)
		cout << "- "<< this->getName() << " didn't buy anything yet!" << endl;
	else
	{
		cout << "- These are the products " << this->getName() <<" bought:" << endl;
		for (int i = 0; i < this->b_order_size; i++)
		{
			for (int j = 0; j < this->b_order[i]->getNumberOfProd();j++)
			{
				cout << "- Product's Name : " << this->b_order[i]->GetProductsArray()[j]->getName() << endl;
				cout << "- Product's Price : " << this->b_order[i]->GetProductsArray()[j]->getPrice() << endl;
				cout << "- Product's serial number : " << this->b_order[i]->GetProductsArray()[j]->getSerial() << endl;
				cout << "<----------------------------------------->" << endl;
			}
		}
	}
	cout << "<----------------------------------------->" << endl;
}
//----------------------------------------------------------------------------------------//
void Buyer::makeOrder()
{
	bool found = false;
	int lastOrder = -1;
	for (int i = 0; i < this->b_order_size && found == false; i++)
	{//find the last order the buyer didn't pay for
		if (this->b_order[i]->getPaymentSatus() == false)
		{
			lastOrder = i;
			found = true;
		}
	}
	if (lastOrder == -1)
	{ //all the orders have been paid, or no orders exist yet
		cout << "You have no orders to pay for right now " << endl;
		return;
	}
	int updatedCartSize = this->b_cart.GetLogicS() - this->GetOrderArray()[lastOrder]->getNumberOfProd();
	int lastIndex = -1;
	bool flag = false;

	for (int i = 0; i < this->b_cart.GetLogicS(); i++)
	{
		for (int j = 0; j < this->b_order[lastOrder]->getNumberOfProd() && flag == false; j++)
		{
			if (this->b_cart.getProductArr()[i] == this->b_order[lastOrder]->GetProductsArray()[j])
			{
				this->b_cart.getProductArr()[i] = nullptr;
				flag = true;
			}
		}
		flag = false;
	}
	if (updatedCartSize != 0)
	{
		for (int i = 0; i < this->b_cart.GetLogicS(); i++)
		{
			if (this->b_cart.getProductArr()[i] == nullptr)
			{
				flag = false;
				for (int j = i + 1; j < this->b_cart.GetLogicS() && flag == false; j++)
				{
					if (this->b_cart.getProductArr()[j] != nullptr)
					{
						this->b_cart.getProductArr()[i] = this->b_cart.getProductArr()[j];
						this->b_cart.getProductArr()[j] = nullptr;
						flag = true;
					}
				}
			}
		}
	}
	if (updatedCartSize > 0)
	{

		this->b_cart.SetLogicS(updatedCartSize);
		this->b_cart.SetPhiS(updatedCartSize);
		this->GetOrderArray()[lastOrder]->setPaymentSatus(true);
	}
	if (updatedCartSize <= 0)
	{ // cart need initialization
		this->b_cart.SetLogicS(0);
		this->b_cart.SetPhiS(1);
		this->b_cart.SetProductArr(nullptr);
		this->GetOrderArray()[lastOrder]->setPaymentSatus(true);
	}
}
//----------------------------------------------------------------------------------------//

