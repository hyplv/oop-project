#include <iostream>
#include <vector>
using namespace std;

// -------------------------------------------------------------
class Balance {
private:
	float balance;

public:
	Balance(float amount=0) {
		if (amount >= 0) 
			balance = amount;
	};
	void show() {
		cout << "Balance: " << balance << endl;
	}

	void top_up(float amount) {
		balance += amount;
	}

	void tranfer(float amount) {
		if (amount <= balance)
			balance -= amount;
	}

	Balance& operator-=(float amount) {
		balance -= amount;
		return *this;
	}

	friend ostream& operator<<(ostream& out, Balance obj) {
		out << obj.balance;
		return out;
	}
};

// -------------------------------------------------------------
class Product {
private:
	string name;
	float price;
	string description;

public:
	Product(string name = "", float price = 0.0, string description = "") {
		this->name = name;
		this->price = price;
		this->description = description;
	}

	float get_price() {
		return price;
	}

	string get_name() {
		return name;
	}
	
	string get_description() {
		return description;
	}

	void show() {
		cout << "\nProduct: " << name << endl;
		cout << "Price: " << price << endl;
		cout << "Description:\n" << description << endl;
	}

	void change_info() {
		cout << "Enter name: ";
		cin >> name;
		cout << "Enter price: ";
		cin >> price;
		cout << "Enter description: ";
		cin >> description;
	}

};

// -------------------------------------------------------------
class Customer {
	Balance balance;
	//vector<Product> wishlist;
	
	vector<Product> history;
	vector<Product> cart;

public:
	Customer() : balance(999) {}

	void add_to_cart(Product prod) {
		cart.push_back(prod);
		cout << "The following item has been added to your cart: " << prod.get_name() << endl;
	}

	void buy() {
		for (int i = 0; i < cart.size(); i++) {
			history.push_back(cart[i]);
			balance -= cart[i].get_price();
		}
		cart = {};
	}

	void show() {
		cout << "\nCustomer Info: " << endl;
		cout << "Balance: " << balance << endl;
		cout << "History: " << endl;
		for (int i = 0; i < history.size(); i++) {
			cout << history[i].get_name() << " " << history[i].get_price() << " " << history[i].get_description() << endl;
		}
		cout << "Cart:" << endl;
		for (int i = 0; i < cart.size(); i++) {
			cout << cart[i].get_name() << " " << cart[i].get_price() << " " << cart[i].get_description() << endl;
		}
	}
};

/*
class Seller {
	
	// add, remove, update, show product announcements
	// discount, profit
};

class User : public Seller, public Customer {
	// login, register, logout, change password
};
*/
int main() {
	Customer customer1;
	Product soap = {"Soap", 12.99, "Ordinary soap for everyday use"};
	Product water = { "Water Bottle 1L", 5.99, "A bottle of fresh water" };
	Product knife = { "Kitchen Knife", 25.99, "A beautiful kitchen knife that is too sharp" };
	customer1.add_to_cart(soap);
	customer1.add_to_cart(water);
	customer1.add_to_cart(knife);
	customer1.show();
	customer1.buy();
	customer1.show();
}
