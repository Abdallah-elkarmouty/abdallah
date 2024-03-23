#include <iostream>
#include <vector>
#include<time.h>
#include <sstream>
#include <string>
#include<fstream>
#include <cstdlib>
using namespace std;

int p = 11, q = 13, n, e, d;
const string filePath = "allPasswords.txt";

struct PasswordInfo{
	string owner;
	string secureNumber;
	string encryptedPassword;
};

vector <PasswordInfo> allPasswords;

/**
 * Computes the greatest common divisor (GCD) of two numbers using Euclid's algorithm.
 * 
 * @param a The first number.
 * @param b The second number.
 * @return The GCD of the two numbers.
 */
int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

/**
 * Generates private and public keys for encryption and decryption.
 * 
 * This function calculates the private (d) and public (e) keys based on given prime numbers (p and q).
 * It also calculates the modulus (n) used in encryption and decryption.
 */
void createPrivateAndPublicKeys() {
	n = p * q;
	int h = (p - 1) * (q - 1);
	e = 2;
	while (e < h && (gcd(e, h) != 1)) {
		e++;
	}
	d = 2;
	while(d < h && (((d * e) % h) != 1)) {
		d++;
	}
}

/**
 * Computes modular exponentiation.
 * 
 * @param b The base.
 * @param e The exponent.
 * @param m The modulus.
 * @return The result of b^e mod m.
 */
long long int computeModulus(long long int b, long long int e, long long int m) {
	long long int r = 1;
	b = b % m;
	for (;e > 0;) {
		if (e % 2 == 1)
			r = (r * b) % m;
		e = e >> 1;
		b = (b * b) % m;
	}
	return r;
}

/**
 * Encrypts a password using RSA encryption.
 * 
 * @param password The password to be encrypted.
 * @param encryptedPassword A reference to store the encrypted password.
 */
void encrypt(const string& password, string &encryptedPassword){
	encryptedPassword = "";
	int i = 0;
	while(i < password.length()) {
		long long int ch = computeModulus(int(password[i]), e, n);
		encryptedPassword += to_string(ch) + " ";
		i++;
	}
}

/**
 * Decrypts an encrypted password using RSA decryption.
 * 
 * @param encryptedPassword The encrypted password.
 * @param password A reference to store the decrypted password.
 */
void decrypt(const string& encryptedPassword, string &password) {
	password = "";
	int i = 0;
	while(i < encryptedPassword.length()) {
		string temp = "";
		while (encryptedPassword[i] != ' ' && i < encryptedPassword.length()) {
			temp += encryptedPassword[i];
			i++;
		}
		long long int c = stoll(temp);
		long long int ch = computeModulus(c, d, n);
		password += char(ch);
		i++;
	}
	cout<<"password  "<<password<<endl;
}

/**
 * Adds a password to the password manager.
 * 
 * This function prompts the user to enter the password owner, password, and a secure number.
 * It then encrypts the password and stores it along with other details in the password manager.
 */
void addPassword(){
	PasswordInfo passwordInfo;
	string password;
	string secureNumber;
	 cout << "Enter Password Owner:  ";
	getline(cin,passwordInfo.owner);
    cout << "Enter Password: ";
	getline(cin,password);
	cout << "Enter Secure Number to use it when decrypt password: ";
	getline(cin,secureNumber);
	encrypt(password,passwordInfo.encryptedPassword);
	encrypt(secureNumber,passwordInfo.secureNumber);
	allPasswords.push_back(passwordInfo);
    cout << "Password added successfully.\n";
}


void getPassword(const string owner, int &index){
	index = -1;
	for (int i = 0; i < allPasswords.size(); ++i) {
        if (allPasswords[i].owner == owner) {
            index = i;
			break;
        }
    }
}

/**
 * Retrieves a password from the password manager.
 * 
 * This function prompts the user to enter the password owner and the secure number.
 * If the owner and secure number match, it decrypts and displays the password.
 */
void retrievePassword(){
	string password = "", secureNumber="";
	string owner="";
	 cout << "Enter Password Owner:  ";
	getline(cin,owner);
	int index = -1;
	getPassword(owner, index);
	if(index == -1){
		cout<<"This password Owner not exist in our system yet\n";
		return;
	}
	cout<<"Encrypted password for "<<owner<<" is: "<<allPasswords[index].encryptedPassword<<endl;
	cout<<"Enter Secure Number to decrypt password: ";
	getline(cin,secureNumber);
	string mysecureNumber;
	decrypt(allPasswords[index].secureNumber, mysecureNumber);
	if(mysecureNumber == secureNumber){
		decrypt(allPasswords[index].encryptedPassword, password);
		cout<<"Decrypted password for "<<owner<<" is: "<<password<<endl;
	}
	else{
		cout<<"Invalid Secure Number Number for "<<owner<<", sorry you not allowed to decrypt the password\n";
	}
}

/**
 * Generates a random password of specified length.
 * 
 * This function prompts the user to enter the length of the password and generates
 * a random password consisting of uppercase and lowercase letters, digits, and symbols.
 */
void generateRandomPassword(){
	int length;
    cout << "Enter password length: ";
    cin >> length;
	cin.ignore();
	string generatedPassword;
	string possibleValues = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;:,.<>?";
    for (int i = 0; i < length; ++i) {
        int index = rand() % possibleValues.size();
        generatedPassword += possibleValues[index];
    }
    cout << "Generated Password: " << generatedPassword << "\n";
                
}

/**
 * Loads passwords from a file into the password manager.
 * 
 * This function reads password information from a file and populates the password manager.
 */
void loadPasswordsFromFile(){
	ifstream file(filePath);
	if (!(file.is_open())) {
		return ;// file not created yet
	}
	cout<<"Loading Passwords from DataBase ...\n";
	string line;
	PasswordInfo passwordInfo;
	while (getline(file, line)) {
		stringstream ss(line);
		string temp;
		getline(ss, passwordInfo.owner, ',');
		getline(ss, passwordInfo.encryptedPassword, ',');
		getline(ss, passwordInfo.secureNumber, ',');
		allPasswords.push_back(passwordInfo);
	}
	file.close();
}

/**
 * Saves passwords from the password manager to a file.
 * 
 * This function writes password information from the password manager to a file.
 */
void savePasswordsToFile(){
	ofstream file(filePath);
	if (!(file.is_open())) {
		return ;// can not create file
	}
	for(int index = 0 ; index < allPasswords.size(); index++){
		file << allPasswords[index].owner << "," << allPasswords[index].encryptedPassword << "," << allPasswords[index].secureNumber<<"\n";
	}
	file.close();
	cout<<"You have successfully written the data to the file.\n";
}

/**
 * The main function.
 * 
 * This function initializes necessary components, loads existing passwords,
 * and presents a menu for the user to interact with the password manager.
 */
int main() {
	createPrivateAndPublicKeys();
	allPasswords.clear();
	loadPasswordsFromFile();
    string choice;
	bool exit = false;
    srand(time(NULL));
	cout<<"Welcome in Our Application that implements a secure password manager\n\n"; 
	while(!exit) {
		cout<<"****  Secure Password Manager Menu  ****\n";
        cout << "1. Add Password\n";
        cout << "2. Retrieve Password\n";
        cout << "3. Generate Random Password\n";
        cout << "4. Exit\n";
        cout << "Enter your choice [1-4]: ";
		getline(cin,choice);
		// 1. Add Password
        if(choice == "1")
            addPassword();
		// 2. Retrieve Password
		else if(choice == "2")
			retrievePassword();
		// 3. Generate Random Password
		else if(choice == "3")
            generateRandomPassword();
		// 4. Exit
        else if(choice == "4"){
			exit = true;
            cout << "Exiting Our Application Thanks...\n";
			savePasswordsToFile();
		}
		else
			cout << "Invalid choice. Please try again [1-4] only.\n";
	}
	system("pause");
    return 0;
}
