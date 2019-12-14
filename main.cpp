#include "user.h"
#include "product.h"

static const int ExitMenu = 11;
void PrintMenu();
void Menu(User & user);
void MenuOpertaion(int oper, User & user);
static const int MAX_CHAR_INPUT = 30;
static const int MAX_DESCRIPTION_SIZE = 256;
int main()
{
	User A;
	Menu(A);
}

void PrintMenu()
{
	cout << "Welcome: " << endl;
	cout << "Please select from the list: " << endl;
	cout << "1.  Add a buyer " << endl;
	cout << "2.  Add a seller " << endl;
	cout << "3.  Add a product for seller" << endl;
	cout << "4.  Add a feedback to the seller " << endl;
	cout << "5.  Add a product to a buyer's cart " << endl;
	cout << "6.  Place an order for a buyer" << endl;
	cout << "7.  Payment order for buyer " << endl;
	cout << "8.  View all buyers information " << endl;
	cout << "9.  View all sellers information" << endl;
	cout << "10. View all the products with the same name" << endl;
	cout << "11. Exit " << endl;
}
void Menu(User & user)
{
	int menu;
	PrintMenu();
	cin >> menu;
	while (menu != ExitMenu)
	{
		MenuOpertaion(menu, user);
		system("CLS");
		PrintMenu();
		cin >> menu;
	}
}


void MenuOpertaion(int oper, User & user)
{
	switch (oper)
	{
	case 1:
	{
		char b_name[MAX_CHAR_INPUT];
		char b_pass[MAX_CHAR_INPUT];
		char b_city[MAX_CHAR_INPUT];
		char b_state[MAX_CHAR_INPUT];
		char b_street[MAX_CHAR_INPUT];
		Cart bmy_cart;
		cout << "Hello Buyer, please enter full name:" << endl;
		cin.ignore(numeric_limits <streamsize> ::max(), '\n');
		cin.getline(b_name, MAX_CHAR_INPUT);
		cout << "please enter your password: (at least 6 digits) " << endl;
		cin.clear();
		cin.getline(b_pass, MAX_CHAR_INPUT);
		if (strlen(b_pass) < 6)
		{
			while (strlen(b_pass) < 6)
			{
				cout << "Your password didn't match the requierments! Please enter again :)" << endl;
				cin.clear();
				cin.getline(b_pass, MAX_CHAR_INPUT);
			}
		}
		cout << "please enter your Address: (1. state 2. city 3. street) " << endl;
		cin.getline(b_state, MAX_CHAR_INPUT);
		cin.getline(b_city, MAX_CHAR_INPUT);
		cin.getline(b_street, MAX_CHAR_INPUT);
		Address my_address(b_city, b_state, b_street);
		Buyer my_buyer(b_name, b_pass, my_address, bmy_cart);
		user.addBuyer(&my_buyer);
	} break;
	//----------------------------------------------------------------------------------------//
	case 2:
	{
		char s_name[MAX_CHAR_INPUT];
		char s_pass[MAX_CHAR_INPUT];
		char s_city[MAX_CHAR_INPUT];
		char s_state[MAX_CHAR_INPUT];
		char s_street[MAX_CHAR_INPUT];
		Cart smy_cart;
		cout << "Hello Seller, please enter full name:" << endl;
		cin.ignore(numeric_limits <streamsize> ::max(), '\n');
		cin.getline(s_name, MAX_CHAR_INPUT);
		cout << "please enter your password: (at least 6 digits) " << endl;
		cin.clear();
		cin.getline(s_pass, MAX_CHAR_INPUT);
		if (strlen(s_pass) < 6)
		{
			while (strlen(s_pass) < 6)
			{
				cout << "Your password didn't match the requierments! Please enter again :)" << endl;
				cin.clear();
				cin.getline(s_pass, MAX_CHAR_INPUT);
			}
		}
		cout << "please enter your Address: (1. state 2. city 3. street) " << endl;
		cin.getline(s_state, MAX_CHAR_INPUT);
		cin.getline(s_city, MAX_CHAR_INPUT);
		cin.getline(s_street, MAX_CHAR_INPUT);
		Address my_address(s_city, s_state, s_street);
		Seller my_seller(s_name, s_pass, my_address, smy_cart);
		user.addSeller(&my_seller);
	}break;
	//----------------------------------------------------------------------------------------//
	case 3:
	{
		char name[MAX_CHAR_INPUT];
		char pass[MAX_CHAR_INPUT];
		cout << "Please Log in first to add a product" << endl;
		cout << "Please enter your name: " << endl;
		cin.ignore(numeric_limits <streamsize> ::max(), '\n');
		cin.getline(name, MAX_CHAR_INPUT);
		cout << "Please enter your password: " << endl;
		cin.getline(pass, MAX_CHAR_INPUT);
		if (user.approveLogIn(name, pass, 1) == 0)
		{ // couldn't find the requested user
			while (user.approveLogIn(name, pass, 1) == 0)
			{
				cout << "Your input didn't match, please enter again:" << endl;
				cout << "Please enter your name: " << endl;
				cin.getline(name, MAX_CHAR_INPUT);
				cout << "Please enter your password: " << endl;
				cin.getline(pass, MAX_CHAR_INPUT);
			}
		}
		else
		{
			Product my_product;
			char pName[MAX_CHAR_INPUT];
			char pCategory[MAX_CHAR_INPUT];
			int pPrice;
			Seller * my_seller = user.findSeller(name);
			cout << "Welcome, " << my_seller->getName() << endl;
			cout << "Please enter the product's name: " << endl;
			cin.getline(pName, MAX_CHAR_INPUT);
			cin.clear();
			cout << "Please enter the product category: (KIDS,CLOTHES,ELECTRONICS,OFFICE)" << endl;
			cin.getline(pCategory, MAX_CHAR_INPUT);
			while (strcmp(pCategory, "KIDS") != 0 && strcmp(pCategory, "OFFICE") != 0 && strcmp(pCategory, "ELECTRONICS") != 0 && strcmp(pCategory, "CLOTHES") != 0)
			{
				cout << "Please enter again the product category: (KIDS,CLOTHES,ELECTRONICS,OFFICE)" << endl;
				cin.getline(pCategory, MAX_CHAR_INPUT);
			}
			cout << "Please enter the price:" << endl;
			cin >> pPrice;
			my_product.setName(pName);
			my_product.setPrice(pPrice);
			if (strcmp(pCategory, "KIDS") == 0)
			{
				my_product.setCategory(Product::KIDS);
			}
			else if (strcmp(pCategory, "OFFICE") == 0)
			{
				my_product.setCategory(Product::OFFICE);
			}
			else if (strcmp(pCategory, "CLOTHES") == 0)
			{
				my_product.setCategory(Product::CLOTHES);
			}
			else if (strcmp(pCategory, "ELECTRONICS") == 0)
			{
				my_product.setCategory(Product::ELECTRONICS);
			}
			my_seller->addProductToSeller(&my_product);
		}
	}break;//Add a product for seller
		   //----------------------------------------------------------------------------------------//
	case 4:
	{
		char name[MAX_CHAR_INPUT];
		char pass[MAX_CHAR_INPUT];
		cout << "Please Log in first to add a feedback" << endl;
		cout << "Please enter your name: " << endl;
		cin.ignore(numeric_limits <streamsize> ::max(), '\n');
		cin.getline(name, MAX_CHAR_INPUT);
		cout << "Please enter your password: " << endl;
		cin.getline(pass, MAX_CHAR_INPUT);
		if (user.approveLogIn(name, pass, 0) == 0)
		{ // couldn't find the requested user
			while (user.approveLogIn(name, pass,0) == 0)
			{
				cout << "Your input didn't match, please enter again:" << endl;
				cout << "Please enter your name: " << endl;
				cin.getline(name, MAX_CHAR_INPUT);
				cout << "Please enter your password: " << endl;
				cin.getline(pass, MAX_CHAR_INPUT);
			}
		}
		else
		{
			// להכניס בדיקה שהקונה ביצע הזמנה מהמוכר
			Buyer * my_buyer = user.findBuyer(name);
			char sellerName[MAX_CHAR_INPUT];
			int	purchaseDay;
			int orderNumber;
			int	purchaseMonth;
			int	purchaseYear;
			char description[MAX_DESCRIPTION_SIZE];
			cout << "Welcome, " << my_buyer->getName() << endl;
			cout << "Please enter the name of the seller you want to write a feedback to: " << endl;
			cin.getline(sellerName, MAX_CHAR_INPUT);
			cout << "Please enter the order number:" << endl;
			cin >> orderNumber;
			/*if (my_buyer->findOrder(orderNumber == 0))
			{
				cout << "We haven't found your'e order, returning to main menu" << endl;
				break;
			}*/
			// find order and confirm the buyer bought from this seller, then send a ref for this seller
			Seller * my_seller = user.findSeller(sellerName);
			cout << "Please enter the day,month and year you made the order :" << endl;
			cin >> purchaseDay;
			cin >> purchaseMonth;
			cin >> purchaseYear;
			Date purchaseDate(purchaseDay, purchaseMonth, purchaseYear);
			cout << "Please enter your feedback description : " << endl;
			cin.ignore(numeric_limits <streamsize> ::max(), '\n');
			cin.getline(description, MAX_DESCRIPTION_SIZE);
			Feedback my_feedback(my_buyer->getName(), purchaseDate, description);
			my_seller->addFeedback(&my_feedback);
		}
	}break;
	//----------------------------------------------------------------------------------------//
	case 5:
	{// add product for buyer's cart
		char name[MAX_CHAR_INPUT];
		char pass[MAX_CHAR_INPUT];
		cout << "Please Log in first to add a product" << endl;
		cout << "Please enter your name: " << endl;
		cin.ignore(numeric_limits <streamsize> ::max(), '\n');
		cin.getline(name, MAX_CHAR_INPUT);
		cout << "Please enter your password: " << endl;
		cin.getline(pass, MAX_CHAR_INPUT);
		if (user.approveLogIn(name, pass, 0) == 0)
		{ // couldn't find the requested user
			while (user.approveLogIn(name, pass, 0) == 0)
			{
				cout << "Your input didn't match, please enter again:" << endl;
				cout << "Please enter your name: " << endl;
				cin.getline(name, MAX_CHAR_INPUT);
				cout << "Please enter your password: " << endl;
				cin.getline(pass, MAX_CHAR_INPUT);
			}
		}
		else
		{
			Product my_product;
			char pName[MAX_CHAR_INPUT];
			char pCategory[MAX_CHAR_INPUT];
			int pPrice;
			Buyer * my_buyer = user.findBuyer(name);
			cout << "Welcome, " << my_buyer->getName() << endl;
			cout << "Please enter the product's name: " << endl;
			cin.getline(pName, MAX_CHAR_INPUT);
			cin.clear();
			cout << "Please enter the product category: (KIDS,CLOTHES,ELECTRONICS,OFFICE)" << endl;
			cin.getline(pCategory, MAX_CHAR_INPUT);
			while (strcmp(pCategory, "KIDS") != 0 && strcmp(pCategory, "OFFICE") != 0 && strcmp(pCategory, "ELECTRONICS") != 0 && strcmp(pCategory, "CLOTHES") != 0)
			{
				cout << "Please enter again the product category: (KIDS,CLOTHES,ELECTRONICS,OFFICE)" << endl;
				cin.getline(pCategory, MAX_CHAR_INPUT);
			}
			cout << "Please enter the price:" << endl;
			cin >> pPrice;
			my_product.setName(pName);
			my_product.setPrice(pPrice);
			if (strcmp(pCategory, "KIDS") == 0)
			{
				my_product.setCategory(Product::KIDS);
			}
			else if (strcmp(pCategory, "OFFICE") == 0)
			{
				my_product.setCategory(Product::OFFICE);
			}
			else if (strcmp(pCategory, "CLOTHES") == 0)
			{
				my_product.setCategory(Product::CLOTHES);
			}
			else if (strcmp(pCategory, "ELECTRONICS") == 0)
			{
				my_product.setCategory(Product::ELECTRONICS);
			}
			my_buyer->addToCart(&my_product);
		}
	}break;
	//----------------------------------------------------------------------------------------//
	}
}
