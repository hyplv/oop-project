#include <iostream>
#include <vector>
using namespace std;

class User {
	string username, password;
public:
	User() {}
	User(string username, string password) {
		this->username = username;
		this->password = password;
		users.push_back({username, password});
	}

	bool operator==(User user) { return (username == user.username); }

	void display() {
		cout << "\nUser info: " << endl;
		cout << "Username: " << username << endl;
		cout << "Password: " << password << "\n\n";
	}
	static vector<vector<string>> users;
	
	bool is_existing() {
		for (int i = 0; i < users.size(); i++) {
			cout << users[i][0] << ":" << users[i][1] << endl;
			if (users[i][0] == username) return 1;
		}
		return 0;
	}
};

class Product {
private:
	string name;
	float price;
	string description;
public:
	Product(string name, float price, string description) {
		this->name = name;
		this->price = price;
		this->description = description;
	}
	void display() {
		cout << "\nProduct Info: " << endl;
		cout << "Name: " << name << endl;
		cout << "Price: " << price << endl;
		cout << "Description: " << description << endl;
	}
};

class Customer : public User {
public:
	void buy_product(Product product) {

	}
};

/*

class File {};

*/

vector<vector<string>> User::users = {};

int main() {
	User u1("name", "passwd");
	User u2("h4x0r", "uwillneverguess7h1s");
	User u3("bro", "whatdahell");
	cout << u3.is_existing();
}