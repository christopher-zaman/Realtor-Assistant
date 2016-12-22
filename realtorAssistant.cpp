#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void AddProperty(int propID[], double propPrice[], int propRooms[], int &count)
{
	int id;
	cout << "Property ID:";
	cin >> id;
	if (id < 1 || id > 20000)
	{
		cout << "The ID must be between 1 and 20000." << endl;
		return;
	}

	double price;
	cout << "Price:";
	cin >> price;
	if (price < 50000 || price > 10000000)
	{
		cout << "Price must be greater than 50000 and less than 10000000." << endl;
		return;
	}

	int rooms;
	cout << "# of Room:";
	cin >> rooms;
	if (rooms < 1)
	{
		cout << "# of rooms must be greater than 1." << endl;
		return;
	}

	propID[count] = id;
	propPrice[count] = price;
	propRooms[count] = rooms;
	count++;
	return;
}

int main()
{
	int propID[100];
	double propPrice[100];
	int propRooms[100];
	int count = 0;

	string datafile = "C:\\Users\\christopherzaman\\Desktop\\Listings.txt";

	ifstream fileIn(datafile);
	// if the file exist and ready and goood.
	if (fileIn.good())
	{
		while (!fileIn.eof())
		{
			fileIn >> propID[count];
			fileIn >> propPrice[count];
			fileIn >> propRooms[count];
			count++;
		}
	}
	fileIn.close();

	while (true)
	{
		cout << "Welcome to Realtor Assist" << endl;
		cout << "1- Add a New Property" << endl;
		cout << "2- Price Reduction" << endl;
		cout << "3- Search Property" << endl;
		cout << "4- Report" << endl;
		cout << "0- Exit" << endl;

		int choice;
		cout << "Make a choice now!?";
		cin >> choice;

		if (choice == 1)
		{
			AddProperty(propID, propPrice, propRooms, count);
		}
		else if (choice == 2) 
		{
			int pID;
			cout << "Property ID: ";
			cin >> pID;

			double amount;
			cout << "Reduction Amount:";
			cin >> amount;

			for (int i = 0; i < count; i++) 
			{
				if (pID == propID[i]) 
				{
					propPrice[i] -= amount;
				}
			}
		}
		else if (choice == 3)
		{
			double budget;
			cout << "Budget:";
			cin >> budget;

			int minRooms;
			cout << "Minimum Rooms:";
			cin >> minRooms;

			bool found = false;

			for (int i = 0; i < count; i++)
			{
				if (propRooms[i] >= minRooms && propPrice[i] <= budget) 
				{
					cout << propID[i] << " " << propPrice[i] << " " << propRooms[i] << endl;
					found = true;
				}
			}

			if (found == false)
			{
				cout << "Could not find any matches." << endl;
			}
		}
		else if (choice == 4)
		{
			double sum = 0;
			for (int i = 0; i < count; i++)
			{
				cout << propID[i] << " " << propPrice[i] << " " << propRooms[i] << endl;
				sum += propPrice[i];
			}
			double avg = sum / count;
			cout << "Average is " << avg << endl;
		}
		else if (choice == 0)
		{
			break;
		}
	}

	ofstream fileOut(datafile);
	for (int i = 0; i < count; i++)
	{
		fileOut << propID[i] << " ";
		fileOut << propPrice[i] << " ";
		fileOut << propRooms[i];
		// make sure that we put new line at the end
		// of all records except the very last one.
		if (i < count - 1)
		{
			fileOut << endl;
		}
	}
	fileOut.close();

	system("PAUSE");
	return 0;
}
