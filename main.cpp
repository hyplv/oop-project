#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// TODO: if have time implement Seller and payment in instalments

// ======================================================================================= //

class Product {
private:

	string id;
	string name;
	int quantity;
	double price;
	double discount;

public:

	// Product() { cout << "whatever" << endl; };

	Product(string id, string name, int quantity = 0, double price = 0.0, double discount = 0.0) {
		this->id = id;
		this->name = name;
		this->price = price;
		this->quantity = quantity;
		this->discount = discount;
	}; 
	
	// getters
	string get_id() const { return id; }
	string get_name() const { return name; }
	int get_quantity() const { return quantity; }
	double get_price() const { return price; }
	double get_discount() const { return discount; };
	double get_discounted_price() const { return (price - price * discount / 100); }
	
	// setters
	void set_quantity(int amount) { quantity = amount; }
	void set_price(double amount) { price = amount; }
	void set_discount(double percentage) {
		if (percentage > 0 and percentage < 100)
			discount = percentage;
		else
			cout << "Discount percentage should be between 0-100!" << endl;
	}

	bool operator==(const Product& other) const { return id == other.id; }
	
	Product operator+(int quantity) {
		this->quantity += quantity;
		return *this;
	}
	friend ostream& operator<<(ostream& out, Product obj) {
		cout << "ID: " << obj.id << endl;
		cout << "Name: " << obj.name << endl;
		cout << "Price: " << obj.price << endl;
		cout << "Discount: " << obj.discount << endl;
		cout << "Discounted Price: " << obj.get_discounted_price() << endl;
		return out;
	}
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
		double result = 0.0;
		for (int i = 0; i < items.size(); i++) {
			result += items[i].get_discounted_price() * items[i].get_quantity();
		}
		return result;
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
	string timestamp;

public:

	Transaction(string id, string customer_username, vector<Product> purchased_items, string timestamp) {
		this->id = id;
		this->customer_username = customer_username;
		this->purchased_items = purchased_items;
		this->timestamp = timestamp; // should replace with the current date using some library or smth
	}

	// getters
	string get_id() const { return id; }
	string get_customer_username() const { return customer_username; }
	vector<Product> get_purchased_items() const { return purchased_items; }
	double total_amount() const {
		double result = 0;
		for (int i = 0; i < purchased_items.size(); i++) {
			result += purchased_items[i].get_discounted_price() * purchased_items[i].get_quantity();
		}
		return result;
	}
	string get_timestamp() const { return timestamp; }


	void generate_receipt() const {
		cout << "ID: " << id << endl;
		cout << "Customer username: " << customer_username << endl;
		cout << "Purchased items:" << endl;
		for (int i = 0; i < purchased_items.size(); i++) {
			cout << "\t\t" << purchased_items[i] << endl;
		}
		cout << "Total Amount: " << total_amount() << endl;
		cout << "Timestamp: " << endl;
	}
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
		cout << "Balance: " << amount << endl;
	};
};

// ======================================================================================= //

class User {
protected:
	string username;
	string password;

public:
	User() {}
	User(string u, string p) : username(u), password(p) {}
	
	virtual string get_username() { return username; }
	virtual string get_password() { return password; }
	
	virtual void display_menu() = 0;

	virtual void signin() {
		cout << "\n\t\t\t\tRegistration" << endl;
		string usrnm, passwd1, passwd2;
		
		cout << "Enter username:";
		cin >> usrnm;
		cout << "Enter password:";
		cin >> passwd1;
		cout << "Enter password again:";
		cin >> passwd2;
		
		if (passwd1 == passwd2) {
			username = usrnm;
			password = passwd1;
			cout << "Registration successful!" << endl;
		}
		else {
			cout << "Password did not match!" << endl;
		}
	}

	virtual void login() {
		cout << "\n\t\t\t\tLogging in" << endl;
		string tmp_usrname, tmp_passwd;

		cout << "Enter username:";
		cin >> tmp_usrname;
		cout << "Enter password:";
		cin >> tmp_passwd;
		cout << tmp_usrname << " " << tmp_passwd << endl;
		
		if (username == tmp_usrname && password == tmp_passwd)
			display_menu();
		else
			cout << "Either username or password is wrong. Try again!" << endl;
	};

	virtual void logout() {
		cout << "Loggin out... " << endl;
	};
};

// ======================================================================================= //

class Customer : virtual public User {
private:
	Balance wallet;
	Cart cart;

public:
	Customer() {}
	Customer(string u, string p) : User(u, p) {}

	void display_menu() override {
		int choice;
		while (1) {
			cout << "\t\t\tUSER PANEL" << endl;
			cout << "[1] View Products" << endl;
			cout << "[2] View History" << endl;
			cout << "[3] View Balance" << endl;
			cout << "[4] Logout" << endl;
			cout << "$";
			cin >> choice;
			switch (choice) {
			case 1:
				cout << "\t\t\tPRODUCTS" << endl;
				cout << "\t\t\tIt is empty here..." << endl << endl;
				cout << "[1] Add to Cart" << endl;
				cout << endl;
				//cout << shop.show();  //or whatever
				break;
			case 2:
				break;
			case 3:
				cout << "\t\t\tBALANCE" << endl;
				wallet.display();
				cout << "[1] Top up Wallet" << endl;
				cout << "[2] to Main Menu" << endl;
				cout << "$";
				cin >> choice;
				
				switch (choice) {
				case 1:
					double amount;
					cout << "Enter the Amount to Top up Your Balance With:";
					cin >> amount;
					top_up_balance(amount);
					break;
				default:
				case 2:
					cout << "Going Back..." << endl;
					break;
				}
				break;
			case 4:
				logout();
				return;
			}
		}
	}

	void add_to_cart(const Product& p) { cart.add_product(p); }
	
	void checkout() {
		wallet.withdraw(cart.get_total());
		cart.clear();
	}
	
	void top_up_balance(double amount) {
		wallet.deposit(amount);
		wallet.display();
	}
	
	void view_order_history() {}
	
	void view_balance() const { wallet.display(); }
};

// ======================================================================================= //

class Admin : public User {
	void display_menu() override {
		cout << "\t\t\t\tADMIN PANEL:\t\t" << endl;
		cout << "[1] manage products" << endl;
		cout << "[2] manage users" << endl;
		cout << "[3] view inventory" << endl;
		cout << "[4] view sales report" << endl;
	}
	void add_product(Product& p) {
		
	}
	void edit_product(Product& p);
	void delete_product(Product& p);
	void manage_users();
	void view_inventory();
	void view_sales_report();
};

// ======================================================================================= //

class FileHandler {
private:

	static vector<string> parse(string mess, char delimiter) {
		vector<string> parsed;
		stringstream ss(mess);
		string line;
		
		while (getline(ss, line, delimiter)) {
			parsed.push_back(line);
		}
		return parsed;
	}

public:

	static void save_users(const vector<User*>& users, const string& filename) {
		fstream file;
		file.open(filename, ios::out, ios::trunc);
		for (int i = 0; i < users.size(); i++) {
			file << users[i]->get_username() << ":" << users[i]->get_password() << "\n";
		}
	}

	static vector<User*> load_users(const string& filename) {
		vector<User*> result;
		fstream file;
		file.open(filename, ios::in);
		
		if (!file.is_open()) {
			cerr << "Failed to open " << filename << endl;
			return {};
		}
		
		string line;
		while (getline(file, line)) {
			vector<string> parsed = parse(line, ':');
			result.push_back(new Customer(parsed[0], parsed[1]));
		}
		return result;
	}



	static void save_products(const vector<Product>& products, const string& filename) {
		fstream file;
		file.open(filename, ios::out, ios::trunc);
		file << "ID::NAME::QUANTITY::PRICE::DISCOUNT" << endl;
		for (int i = 0; i < products.size(); i++) {
			file << products[i].get_id() << ":"
				 << products[i].get_name() << ":"
				 << products[i].get_quantity() << ":"
				 << products[i].get_price() << ":"
				 << products[i].get_discount() << endl;
		}
	}
	
	static vector<Product> load_products(const string& filename) {
		vector<Product> result;
		fstream file(filename, ios::in);
		string line;

		if (!file.is_open()) {
			cerr << "Error! Couldn't open " << filename << endl;
			return {};
		}
		
		while (getline(file, line)) {
			vector<string> parsed = parse(line, ':');
			if (parsed.size() == 5) {
				result.push_back(Product(parsed[0], parsed[1], stoi(parsed[2]), stoi(parsed[3]), stoi(parsed[4])));
			}
		}
		return result;
	}


	// whatever will rewrite it later
	static void log_transactions(const Transaction& t, const string& filename) { // vector<>
		fstream file(filename, ios::out, ios::trunc);
		vector<Product> purchased = t.get_purchased_items();

		if (!file.is_open()) {
			cerr << "Error! Couldn't open " << filename << endl;
			return;
		}

		file << t.get_id() << ":" << t.get_customer_username() << ":";
		
		for (int i = 0; i < purchased.size(); i++) {
			file << purchased[i].get_name() << ","
				 << purchased[i].get_price() << ","
				 << purchased[i].get_quantity() << "|";
		}

		file << ":" << t.total_amount() << ":" << t.get_timestamp() << endl;
	}

	static void load_transactions(const string& filename) {
		fstream file(filename, ios::in);
		string line;
		string line_line;
		string line_line_line;
		int i = 1;
		while (getline(file, line, ':')) {
			stringstream ss(line);
			while (getline(ss, line_line, '|')) {
				// cout << line_line << '\n';
					stringstream ssss(line_line);
					while (getline(ssss, line_line_line, ','))
						cout << line_line_line << '\n';
			}
			//cout << line << endl;
		}
	}
	/*
	static void generate_receipt(const Transaction& t) {}
	*/
};

// ======================================================================================= //

class Shop {};

// ======================================================================================= //

int main() {
	Product p1("123", "knife", 12, 99.99);
	Product p2("124", "soap", 15, 9.99);
	Product p3("125", "shampoo", 18, 45.99);

	vector<Product> purchased;
	purchased.push_back(p1);
	purchased.push_back(p2);
	purchased.push_back(p3);

	Transaction t("TX_1234.txt", "john doe", purchased, "28.04.2025");
	FileHandler::log_transactions(t, "t.txt");
	FileHandler::load_transactions("t.txt");
}
