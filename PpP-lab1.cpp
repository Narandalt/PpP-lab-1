#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <windows.h>
#include <climits>

using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

#define DATA 1
#define INFO 2
#define REVENUE 3
#define EXIT 4

void textColor(string text, int color);

// цвета
enum colors
{
	WHITE = 15,
	RED = 12,
	GREEN = 10
};

class Provider
{
private:
	string name; // название оператора
	int price; // стоимость тарифа
	int quantity; // количество абонентов
public:
	Provider(const string& name, int price, int quantity)
		: name(name), price(price), quantity(quantity) {}

	long long total_revenue()
	{
		long long revenue = (long long)price;
		revenue *= (long long)quantity;
		return revenue; // подсчет выручки
	}

	void displayInfo()
	{
		cout << "Provider's name: ";
		textColor(name, GREEN);
		cout << "\nThe price of the tariff: ";
		textColor(to_string(price), GREEN);
		cout << "\nQuantity of subscribers: ";
		textColor(to_string(quantity), GREEN);

		cin.ignore();
		cin.get();
	}
};

// защита от неправильного ввода
bool defender(string str)
{
	const string INT_MAX_VALUE = to_string(INT_MAX);

	for (int i = 0; i < str.length(); i++)
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return false;
	}

	// проверка на большие числа
	if (str.length() > INT_MAX_VALUE.length())
		return false;
	else if (str.length() == INT_MAX_VALUE.length())
	{
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] > INT_MAX_VALUE[i])
				return false;
		}
	}

	return true;
}

// меняет цвет текста
void textColor(string text, int color)
{
	SetConsoleTextAttribute(hConsole, color);

	cout << text;

	SetConsoleTextAttribute(hConsole, WHITE);
}

// показывает меню выбора
void showMenu()
{
	textColor("Database Administrator Console:\n\n1. To add a new provider to the database.\n2. Current information about the provider.\n3. Calculating total revenue.\n4. Exit.\n\nEnter your choice: ", WHITE);
}

// ошибка "отсутствие базы данных"
void errorNoData()
{
	textColor("\nNo provider data available. Please add an provider first.", RED);
	cin.ignore();
	cin.get();
}

// ошибка "неправильный ввод числа"
void errorUncorrectNumber()
{
	textColor("\nWARNING! Enter a correct number", RED);
	cin.ignore();
	cin.get();
}

string inputColor()
{
	string text;

	SetConsoleTextAttribute(hConsole, GREEN);
	cin >> text;
	SetConsoleTextAttribute(hConsole, WHITE);

	return text;
}

int main()
{
	Provider* provider = nullptr;
	string userChoice = "0";
	string provName, provPrice, provQuantity;

	while (stoi(userChoice) != EXIT)
	{

		system("cls");

		showMenu();
		userChoice = inputColor();

		while (!defender(userChoice))
		{
			errorUncorrectNumber();
			system("cls");

			showMenu();
			userChoice = inputColor();
		}

		if (stoi(userChoice) == DATA)
		{
			system("cls");

			cout << "Enter the name of the provider: ";
			provName = inputColor();

			cout << "Enter the subscribe price: ";
			provPrice = inputColor();

			while (!defender(provPrice))
			{
				errorUncorrectNumber();
				system("cls");

				cout << "Enter the name of the provider: ";
				textColor(provName, GREEN);
				cout << "\nEnter the subscribe price: ";
				provPrice = inputColor();
			}

			cout << "Enter the subscribers count: ";
			provQuantity = inputColor();

			while (!defender(provQuantity))
			{
				errorUncorrectNumber();
				system("cls");

				cout << "Enter the name of the provider: ";
				textColor(provName, GREEN);
				cout << "\nEnter the subscribe price: ";
				textColor(provPrice, GREEN);
				cout << "\nEnter the subscribers count: ";
				provQuantity = inputColor();
			}

			provider = new Provider(provName, stoi(provPrice), stoi(provQuantity));

			textColor("\n\nProvider added successfully!", GREEN);

			cin.ignore();
			cin.get();
		}
		else if (stoi(userChoice) == INFO)
		{
			system("cls");

			if (provider)
				provider->displayInfo();
			else
				errorNoData();

		}
		else if (stoi(userChoice) == REVENUE)
		{
			system("cls");

			if (provider)
			{
				cout << "Total revenue: ";
				textColor(to_string(provider->total_revenue()), GREEN);
				cin.ignore();
				cin.get();
			}
			else
				errorNoData();
		}
	}

	if (provider)
		delete provider;

	return 0;
}