#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <Windows.h>
#define garbage_collector() cin.ignore(cin.rdbuf()->in_avail())

using namespace std;

struct Date {
	short day;
	short month;
	short year;
	bool isCorrect();
};

bool Date::isCorrect()
{
	bool result = false;
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
	{
		if ((day <= 31) && (day > 0))
			result = true;
		break;
	}

	case 4:
	case 6:
	case 9:
	case 11:
	{
		if ((day <= 30) && (day > 0))
			result = true;
		break;
	}

	case 2:
	{
		if (year % 4 != 0)
		{
			if ((day <= 28) && (day > 0))
				result = true;
		}
		else
			if (year % 400 == 0)
			{
				if ((day <= 29) && (day > 0))
					result = true;
			}
			else
				if ((year % 100 == 0) && (year % 400 != 0))
				{
					if ((day == 28) && (day > 0))
						result = true;
				}
				else
					if ((year % 4 == 0) && (year % 100 != 0))
						if ((day <= 29) && (day > 0))
							result = true;
		break;
	}

	default:
		result = false;
	}

	return result;
}

struct Person
{
	char FirstName[15],
		SecondName[15],
		LastName[15],
		Sex[7],
		Nationality[56],
		Address[255],
		
		Number[56];

	int Age;

	float AverageMark;

	Date Birthday;
};
//TODO:возвращяет указатель на масив структур размерности Dimension
Person* InitArray(int Dimension);
Person InitPerson();
void DisplayArray(Person* Massive, int Dimaension);
void DisplayChoise(Person*, int, char*, int, int);
void DisplayPerson(Person);
void SortFirstName(Person*, int);
int& CheckCorectDigitValue(int&);

void main(int argc, char* argv)
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setlocale(0, "");

	int Dimension;
	char SexTag[7];
	int LowAge, UpperAge;
	bool begin = true;
tryagain:
	Person* MassiveStruct = nullptr;
	do
	{
		cout << "\nEnter the number of persons:  ";
		do {
			cin >> Dimension;
			if (cin.fail())
			{
				cout << "[!]Previous input failed, please re-enter !!!" << endl;
				cin.clear();
				cin.ignore(32222, '\n');
			}
			else
				break;
		} while (true);
		MassiveStruct = InitArray(Dimension);
		if (MassiveStruct == nullptr)
		{
			cout << "\n[!]Dynamic array don't exist!\n";

			do {
				cout << "[!]Введите '+' для того чтобы повторить попытку или нажмите '-' чтобы выйти из програмы... ";
				char symbol;
				symbol = getchar();
				(symbol == '+') ? begin == true : begin == false;
				if (symbol == '+')
					goto tryagain;
				exit(777);

			} while (!begin);
		}


	} while (begin != true);

	cout << "\n------------FULL INFORMATION------------" << endl;
	DisplayArray(MassiveStruct, Dimension);

	cout << "\n[!]Enter the sex-tag: ";
	do {
		cin >> SexTag;
	} while (isdigit((char)SexTag[1]));
	cout << "\nEnter of boundary of age: ";
	do
	{
		cin >> LowAge >> UpperAge;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32222, '\n');
		}
		else
			break;
	} while (true);

	cout << "\n[!]The list of choice-persons: ";
	DisplayChoise(MassiveStruct, Dimension, SexTag, LowAge, UpperAge);

	cout << "\n[!]The sorting list of persons: ";
	SortFirstName(MassiveStruct, Dimension);
	DisplayArray(MassiveStruct, Dimension);

	delete MassiveStruct;
}
Person InitPerson()
{
	Person Man;

	cout << "\nEnter first name: ";
	garbage_collector();
	cin.getline(Man.FirstName, 255);

	cout << "Enter second name: ";
	garbage_collector();
	cin.getline(Man.SecondName, 255);

	cout << "Enter last name: ";
	garbage_collector();
	cin.getline(Man.LastName, 255);

	cout << "Enter the age: ";
	garbage_collector();
	cin >> Man.Age;

	cout << "Enter sex: ";
	garbage_collector();
	cin.getline(Man.Sex, 255);

	cout << "Enter nationality: ";
	garbage_collector();
	cin.getline(Man.Nationality, 255);

	

	do {
		cout << "Enter birthday: ";
		garbage_collector();
		cin >> Man.Birthday.day >> Man.Birthday.month >> Man.Birthday.year;
	} while (!Man.Birthday.isCorrect());

	cout << "Enter telephone number: ";
	garbage_collector();
	cin.getline(Man.Number, 56);

	cout << "Enter address: ";
	garbage_collector();
	cin.getline(Man.Address, 255);

	return Man;
}

Person* InitArray(int Dimension)
{
	Person* Massive = new Person[Dimension];
	if (Massive == nullptr)
		return nullptr;
	for (size_t i = 0; i < Dimension; i++)
	{
		printf("\n[!]Enter the information about %d person ", i + 1);
		Massive[i] = InitPerson();
	}
	return Massive;
}

void DisplayArray(Person* Massive, int Dimension)
{
	for (size_t i = 0; i < Dimension; i++) { DisplayPerson(Massive[i]); }
}

void DisplayChoise(Person* Massive, int Dimension, char* SexTag, int LowAge, int UpperAge)
{
	for (size_t i = 0; i < Dimension; i++)
	{
		if (
			strcmp(Massive[i].Sex, SexTag) == 0 &&
			Massive[i].Age <= UpperAge &&
			Massive[i].Age >= LowAge
			)
		{
			DisplayPerson(Massive[i]);
		}
	}
}

void DisplayPerson(Person Man)
{
	cout << "Full name: " << Man.FirstName << " " << Man.SecondName << " " << Man.LastName << endl;
	cout << "Age: " << Man.Age << endl;
	cout << "Gender: " << Man.Sex << endl;
	cout << "Birthday: " << Man.Birthday.year << "." << Man.Birthday.month << "." << Man.Birthday.day << endl;
	cout << "Telephone number: " << Man.Number << endl;
	cout << "Address: " << Man.Address << "\n\n";
}
void SortFirstName(Person* Massive, int Dimension)
{
	Person Temp;
	for (size_t i = 0; i <= Dimension; i++)
	{
		for (size_t q = Dimension - 1; q > i; q--)
		{
			if (strcmp(Massive[q].FirstName, Massive[q - 1].FirstName) < 0)

				Temp = Massive[q];
			Massive[q] = Massive[q - 1];
			Massive[q - 1] = Temp;

		}
	}
}
int& CheckCorectDigitValue(int& value)
{
	bool flag = false;
	do {
		if (flag) {
			cout << "[!]Please re-enter!!!";
		}flag = false;
		cin >> value;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32222, '\n');
		}
		else
		{
			return value;
		}
	} while (true);
}