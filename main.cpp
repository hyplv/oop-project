#include <iostream>
#include <vector>
using namespace std;


// ======================================================================================= //

class Product {
private:

	string id;
	string name;
	double price;
	int quantity;
	double discount;

public:
	Product() { cout << "whatever" << endl; };

	Product(string id, string name, double price, int quantity = 0, double discount = 0.0) {
		this->id = id;
		this->name = name;
		this->price = price;
		this->quantity = quantity;
		this->discount = discount;
	}; 
	
	// getters
	string get_id() const { return id; }
	string get_name() const { return name; }
	double get_price() const { return price; }
	int get_quantity() const { return quantity; }
	double get_discounted_price() const { return (price - price * discount / 100); }
	
	// setters
	void set_quantity(int amount) { quantity = amount; };
	void set_discount(double percentage) { discount = percentage; };

	bool operator==(const Product& other) const { return id == other.id; };
	
	Product operator+(int quantity) {
		Product result = *this;
		result.quantity += quantity;
		return result;
	};
};

// ======================================================================================= //

class Cart {
private:

	vector<Product> items;

public:

	void add_product(const Product& p) { items.push_back(p); };
	/*
	void remove_product(const string& id) {
		int position = items.size();
		for (int i = 0; i < items.size(); i++) {
			cout << items[i].get_name() << endl;
			cout << items.size() << endl;
			if (items[i].get_id() == id)
				position = i;
		}
		if (position != items.size()) items.erase(position);
	};
	*/
	double get_total() const {
		return 
	};
	
	void display_cart() const {
		for (int i = 0; i < items.size(); ) {
			cout << items[i].get_name() 
				 << items[i].get_id() 
				 << items[i].get_quantity()
				 << items[i].get_price() 
				 << items[i].get_discounted_price() 
				 << endl;
		}
		if (items.size() == 0) cout << "The cart is empty" << endl;
	};
	
	void clear() { items.clear(); };
};


// ======================================================================================= //
class Transaction {
private:

	string id;
	string customer_username;
	vector<Product> purchased_items;
	double total_amount;
	string timestamp;

public:

	Transaction(string id, string customer_username, vector<Product> purchased_items, double total_amount, string timestamp) {
		this->id = id;
		this->customer_username = customer_username;
		this->purchased_items = purchased_items;
		this->total_amount = total_amount; // mayber use get_total or smth
		this->timestamp = timestamp; // should replace with the current date using some library or smth
	}

	void generate_receipt() const {
		cout << "" << endl; // print out all the data prettily
	}

	string get_time_stamp() const { return timestamp; }
};
// ======================================================================================= //
class Balance {
private:

	double amount;

public:

	Balance(double initial = 0) : amount(initial) {}

	void deposit(double value) { amount += value; }
	
	bool withdraw(double value) {
		if (value <= amount)
			amount -= value;
		else
			return false;
	}

	double get_amount() const { return amount; };
	
	void display() const {
		cout << "" << endl;
	};
};

// ======================================================================================= //

class User {
protected:

	string username;
	string password;

public:

	virtual void display_menu() = 0;

	virtual void login() {
		string tmp_usrname, tmp_passwd;
		cout << "Enter username:";
		cin >> tmp_usrname;
		cout << "Enter password:";
		cin >> tmp_passwd;
		if (username == tmp_usrname and password == "tmp_passwd")
			display_menu();
		else
			cout << "Either username or password is wrong" << endl;
	};

	virtual void logout() {
		cout << "Loggin out... " << endl;
	};
	// virtual ~User();
};

// ======================================================================================= //

class Customer : virtual public User {
private:
	Balance wallet;
	Cart cart;
public:
	void display_menu() override;
	void add_to_cart(const Product& p) { cart.add_product(p); };
	void checkout();
	void top_up_balance(double amount);
	void view_order_history();
	void view_balance() const;
};

// ======================================================================================= //

class Seller : virtual public User {
private:
	Balance earnings;
public:
	void display_menu() override;
	void process_sale();
	void view_sales_history();
	void apply_discount(Product& p, double amount);
	void view_earnings() const;
};

// ======================================================================================= //

class CustomerSeller : public Customer, public Seller {
public:
	void display_menu() override;
};

// ======================================================================================= //

class Admin : User {
	void display_menu() override;
	void add_product(Product& p);
	void edit_product(Product& p);
	void delete_product(Product& p);
	void manage_users();
	void view_inventory();
	void view_sales_report();
};

// ======================================================================================= //

class FileHandler {
public:
	static vector<User*> load_users(const string& filename);
	static void save_users(const vector<User*>& users, const string& filename);
	
	static vector<Product> load_products(const string& filename);
	static void save_products(const vector<Product>& products, const string& filename);
	
	static void log_transactions(const Transaction& t, const string& filename);
	static vector<Transaction> load_transactions(const string& filename);

	static void generate_receipt(const Transaction& t);
	static bool file_exists(const string& filename);
};
// ======================================================================================= //

int main() {

}
