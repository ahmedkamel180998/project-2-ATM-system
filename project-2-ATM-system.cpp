#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;
const string clientsFileName = "clients.txt";
void showLoginScreen();
void showAtmMainMenuScreen();

// ATM Project Original Version Before Update

string readString(string message)
{
	string userText;
	cout << message;
	getline(cin >> ws, userText);
	return userText;
}

char readCharacter(string message)
{
	char userCharacter;
	do
	{
		cout << message;
		cin >> userCharacter;
	} while (userCharacter != 'Y' && userCharacter != 'y' && userCharacter != 'N' && userCharacter != 'n');
	return userCharacter;
}

short readNumberInRange(string message, short from, short to)
{
	short userNumber = 0;
	do
	{
		cout << message;
		cin >> userNumber;
	} while (userNumber < from || userNumber > to);
	return userNumber;
}

void printGeneralHeader(string message)
{
	cout << "=======================================================================================================" << endl;
	cout << "\t\t\t\t\t" << message << endl;
	cout << "=======================================================================================================" << endl;
}

// Fundamentals 
enum enAtmMainMenuOptions
{
	quickWithdraw = 1,
	normalWithdraw = 2,
	deposit = 3,
	checkBalance = 4,
	logout = 5,
};

struct stClientData
{
	string accountNumber;
	string pinCode;
	string name;
	string phone;
	double accountBalance = 0;
	bool markForDeletion = false;
	bool markForUpdate = false;
};

stClientData loginClient;

vector<string> split(string client, string delimiter = "#//#")
{
	vector<string> splitWords;
	string splitWord = "";
	size_t delimiterPosition = 0;

	while ((delimiterPosition = client.find(delimiter)) != client.npos)
	{
		splitWord = client.substr(0, delimiterPosition);
		if (splitWord != "")
			splitWords.push_back(splitWord);
		client.erase(0, delimiterPosition + delimiter.length());
	}
	if (client != "")
		splitWords.push_back(client);
	return splitWords;
}

stClientData saveVectorToStructure(vector<string> splitWords)
{
	stClientData client;
	client.accountNumber = splitWords[0];
	client.pinCode = splitWords[1];
	client.name = splitWords[2];
	client.phone = splitWords[3];
	client.accountBalance = stod(splitWords[4]);
	return client;
}

vector<stClientData> loadClientsDataFromFile(string fileName)
{
	vector<stClientData> clients;

	fstream myFile;
	myFile.open(fileName, ios::in);
	if (myFile.is_open())
	{
		string client = "";
		while (getline(myFile, client))
		{
			if (client != "")
				clients.push_back(saveVectorToStructure(split(client)));
		}
		myFile.close();
	}
	return clients;
}

bool findClientByAccountNumber(string accountNumber, vector<stClientData> clients, stClientData& client)
{
	for (stClientData& c : clients)
	{
		if (c.accountNumber == accountNumber)
		{
			client = c;
			return true;
		}
	}
	return false;
}

stClientData validateClientLogin()
{
	system("cls");
	printGeneralHeader("Login Screen");
	vector<stClientData> clients = loadClientsDataFromFile("clients.txt");
	stClientData loginClient;

	// validate Account Number
	string accountNumber = readString("Enter Your Account Number ?   ");
	while (!findClientByAccountNumber(accountNumber, clients, loginClient))
	{
		cout << "\nClient [" << accountNumber << "] is invalid, Please Enter Another One!" << endl;
		accountNumber = readString("\nEnter A Valid Account Number ?   ");
	}

	// validate Pin Code
	string pinCode = readString("Enter Your Pin Code ?   ");
	while (!(pinCode == loginClient.pinCode))
	{
		cout << "\nPinCode [" << pinCode << "] is invalid For Client [" << accountNumber << "] , Please Enter Another One!" << endl;
		pinCode = readString("\nEnter A Valid Pin Code ?   ");
	}

	system("cls");
	return loginClient;
}

void goBackToAtmMainMenuScreen()
{
	cout << "\nPress Any Key to go back to The Main Menu...  ";
	system("pause >nul");
	system("cls");
	showAtmMainMenuScreen();
}

// 1 - Quick Withdraw Screen

enum enQuickWithdrawOptions
{
	withdraw20 = 1,
	withdraw50 = 2,
	withdraw100 = 3,
	withdraw200 = 4,
	withdraw400 = 5,
	withdraw600 = 6,
	withdraw800 = 7,
	withdraw1000 = 8,
	exitQuick = 9,
};

string convertClientStructureToRecord(stClientData client, string delimiter = "#//#")
{
	string record = "";
	record += client.accountNumber + delimiter;
	record += client.pinCode + delimiter;
	record += client.name + delimiter;
	record += client.phone + delimiter;
	record += to_string(client.accountBalance);
	return record;
}

void saveClientsToFile(vector<stClientData>& clients)
{
	fstream myFile;
	myFile.open(clientsFileName, ios::out);
	if (myFile.is_open())
	{
		string client = "";
		for (stClientData& c : clients)
		{
			if (c.markForDeletion == false)
			{
				client = convertClientStructureToRecord(c);
				myFile << client << endl;
			}
		}
		myFile.close();
	}
}

void validateWithdraw(double withdraw)
{
	vector<stClientData> clients = loadClientsDataFromFile("clients.txt");
	char checkTransaction = 'Y';

	while (withdraw > loginClient.accountBalance)
	{
		cout << "\nThe Amount Exceeds The Balance, Make Another Choice." << endl;
		goBackToAtmMainMenuScreen();
	}

	checkTransaction = readCharacter("\nAre You Sure You Want To Perform This Transaction ? [Y/N] ?  ");
	if (toupper(checkTransaction) == 'Y')
	{
		for (stClientData& c : clients)
		{
			if (c.accountNumber == loginClient.accountNumber)
			{
				c.accountBalance += (withdraw * -1);
				loginClient = c;
				break;
			}
		}
	}
	// Update File After Withdraw
	saveClientsToFile(clients);

	cout << "\nDone Successfully. Your Balance After Withdraw = " << loginClient.accountBalance << endl;
}

void printQuickWithdrawScreenBody()
{
	cout << "\t\t\t[1]  20 \t\t\t[2]  50" << endl;
	cout << "\t\t\t[3]  100\t\t\t[4]  200" << endl;
	cout << "\t\t\t[5]  400\t\t\t[6]  600" << endl;
	cout << "\t\t\t[7]  800\t\t\t[8]  1000" << endl;
	cout << "\t\t\t[9]  Exit" << endl;
	cout << "=======================================================================================================" << endl;
}

void performQuickWithdrawOptions(enQuickWithdrawOptions quickWithdrawOptions)
{
	switch (quickWithdrawOptions)
	{
	case enQuickWithdrawOptions::withdraw20:
		validateWithdraw(20);
		goBackToAtmMainMenuScreen();
		break;
	case enQuickWithdrawOptions::withdraw50:
		validateWithdraw(50);
		goBackToAtmMainMenuScreen();
		break;
	case enQuickWithdrawOptions::withdraw100:
		validateWithdraw(100);
		goBackToAtmMainMenuScreen();
		break;
	case enQuickWithdrawOptions::withdraw200:
		validateWithdraw(200);
		goBackToAtmMainMenuScreen();
		break;
	case enQuickWithdrawOptions::withdraw400:
		validateWithdraw(400);
		goBackToAtmMainMenuScreen();
		break;
	case enQuickWithdrawOptions::withdraw600:
		validateWithdraw(600);
		goBackToAtmMainMenuScreen();
		break;
	case enQuickWithdrawOptions::withdraw800:
		validateWithdraw(800);
		goBackToAtmMainMenuScreen();
		break;
	case enQuickWithdrawOptions::withdraw1000:
		validateWithdraw(1000);
		goBackToAtmMainMenuScreen();
		break;
	case enQuickWithdrawOptions::exitQuick:
		goBackToAtmMainMenuScreen();
		break;
	default:
		break;
	}
}

void showQuickWithdrawScreen()
{
	printGeneralHeader("Quick Withdraw Screen");
	printQuickWithdrawScreenBody();
	cout << "Your Balance is " << loginClient.accountBalance << endl;
	performQuickWithdrawOptions((enQuickWithdrawOptions)readNumberInRange("\nChoose What Do You Want To Withdraw From ? [1 To 8]  ?   ", 1, 9));
}

// 2 - Normal Withdraw screen

double getDepositOrWithdraw(string message)
{
	double amountOfMoney = 0;
	do
	{
		cout << message;
		cin >> amountOfMoney;
	} while (amountOfMoney <= 0);
	return amountOfMoney;
}

unsigned validateWithdrawMultipleOfFive()
{
	unsigned amountOfWithdraw = getDepositOrWithdraw("\nPlease Enter An Amount Multiple Of 5's ?  ");
	while (amountOfWithdraw % 5 != 0)
	{
		amountOfWithdraw = getDepositOrWithdraw("\nPlease Enter An Amount Multiple Of 5's ?  ");
	}
	return amountOfWithdraw;
}

void showNormalWithdrawScreen()
{
	printGeneralHeader("Normal Withdraw Screen");
	cout << "Your Balance is " << loginClient.accountBalance << endl;
	validateWithdraw(validateWithdrawMultipleOfFive());
}

// 3 - Deposit Screen

void validateDeposit(double deposit)
{
	vector<stClientData> clients = loadClientsDataFromFile("clients.txt");
	char checkTransaction = readCharacter("\nAre You Sure You Want To Perform This Transaction ? [Y/N] ?  ");
	if (toupper(checkTransaction) == 'Y')
	{
		for (stClientData& c : clients)
		{
			if (c.accountNumber == loginClient.accountNumber)
			{
				c.accountBalance += deposit;
				loginClient = c;
				break;
			}
		}
	}
	// update File After Deposit
	saveClientsToFile(clients);

	cout << "\nDone Successfully, Your Balance After Deposit = " << loginClient.accountBalance << endl;
}

void showDepositScreen()
{
	printGeneralHeader("Deposit Screen");
	cout << "Your Balance is " << loginClient.accountBalance << endl;
	validateDeposit(getDepositOrWithdraw("\nPlease Enter A Positive Amount ?  "));
}

// 4 - Check Balance Screen

void showCheckBalanceScreen()
{
	printGeneralHeader("Check Balance Screen");
	cout << "Your Balance is :  " << loginClient.accountBalance << endl;
}

// ATM Main Menu Homepage

void printAtmMainMenuScreenBody()
{
	cout << "\t\t[1] Quick Withdraw." << endl;
	cout << "\t\t[2] Normal Withdraw." << endl;
	cout << "\t\t[3] Deposit." << endl;
	cout << "\t\t[4] Check Balance." << endl;
	cout << "\t\t[5] Logout." << endl;
	cout << "=======================================================================================================" << endl;
}

void performAtmMainMenuOptions(enAtmMainMenuOptions atmMainMenuOptions)
{
	switch (atmMainMenuOptions)
	{
	case enAtmMainMenuOptions::quickWithdraw:
		system("cls");
		showQuickWithdrawScreen();
		break;
	case enAtmMainMenuOptions::normalWithdraw:
		system("cls");
		showNormalWithdrawScreen();
		goBackToAtmMainMenuScreen();
		break;
	case enAtmMainMenuOptions::deposit:
		system("cls");
		showDepositScreen();
		goBackToAtmMainMenuScreen();
		break;
	case enAtmMainMenuOptions::checkBalance:
		system("cls");
		showCheckBalanceScreen();
		goBackToAtmMainMenuScreen();
		break;
	case enAtmMainMenuOptions::logout:
		system("cls");
		showLoginScreen();
		break;
	default:
		break;
	}
}

void showAtmMainMenuScreen()
{
	printGeneralHeader("ATM Main Menu Screen");
	printAtmMainMenuScreenBody();
	performAtmMainMenuOptions((enAtmMainMenuOptions)readNumberInRange("Choose What Do You Want To Do ? [1 To 5]  ?   ", 1, 5));
}

// Login Screen Homepage

void showLoginScreen()
{
	loginClient = validateClientLogin();
	showAtmMainMenuScreen();
}

int main()
{
	showLoginScreen();
	system("pause>nul");
	return 0;
}