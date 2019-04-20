#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 

using namespace std;

struct Item {
	string itemNum;
	string name;
	double cost;
	int qty;
};

void shoppingcart(Item* sc, int size)
{
	//cout cart
	double total = 0;
	//format the headings for the cart
	cout << setw(20) << "Item Number" << setw(21) << "Item Name" << setw(21) << "Qty" << setw(25) << "Unit Cost" << setw(18) << "Total" << endl;
	cout << "........................................................................................................." << endl;
	for (int x = 0; x < size; x++) {
		cout << setw(20) << sc[x].itemNum << " "; //print Item number
		cout << setw(20) << sc[x].name << " "; //print name
		cout << setw(20) << sc[x].qty << " "; //print qty
		cout << setw(20) << sc[x].cost << " "; //print cost
		cout << setw(20) << sc[x].cost * sc[x].qty << " "; //print total
		if (x == size - 1)
		{
			cout << endl << "........................................................................................................." << endl;
		}
		else
		{
			cout << endl << "..." << endl;
		}
		//keep running total
		total += sc[x].qty * sc[x].cost;
	} //print order total
	cout << setw(98) << "Total: $" << total << endl;
	system("pause");
}
void invoice(Item* sc, int size) {
	//PRINT OUT RECIEPT
	double total = 0;
	ofstream invoice("invoice.txt");
	//format heading for reciept
	invoice << setw(20) << "Item Number" << setw(21) << "Item Name" << setw(21) << "Qty" << setw(25) << "Unit Cost" << setw(20) << "Total" << endl;
	invoice << "........................................................................................................." << endl;
	for (int x = 0; x < size; x++) {
		invoice << setw(20) << sc[x].itemNum << " "; //print Item number
		invoice << setw(20) << sc[x].name << " "; //print name
		invoice << setw(20) << sc[x].qty << " "; //print qty
		invoice << setw(20) << sc[x].cost << " "; //print cost
		invoice << setw(20) << sc[x].cost * sc[x].qty << " "; //print total
		if (x == size - 1)
		{
			invoice << endl << "........................................................................................................." << endl;
		}
		else
		{
			invoice << endl << "..." << endl;
		}
		total += sc[x].qty * sc[x].cost;
	} 
	//print total
	invoice << setw(98) << "Total: $" << total << endl;
	system("pause");
}
void updateFile(Item* ShoppingCart, int size)
{
	fstream outputFile;
	//open file in input and ouput mode
	outputFile.open("ProductData.csv",ios::in|ios::out);
	string item_num;
	int qty;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; !(outputFile.eof()); j++)
		{
			char ch = ' ';
			string line;
			outputFile.seekg(30 + (29 * j));
			while (ch != ',')
			{
				outputFile >> ch;
				if (ch != ',')
				{
					line = line + ch;

				}
			}
			string itemNum = line;
			if (itemNum == ShoppingCart[i].itemNum)
			{
				outputFile.seekg(56 + (29 * j));
				int qty;
				outputFile >> qty;
				qty = qty - ShoppingCart[i].qty;
				if(qty<100)
				{
					outputFile.seekp(57 + (29 * j));
					outputFile << qty;
				}
				else
				{
					outputFile.seekp(56 + (29 * j));
					outputFile << qty;
				}
				break;
			}
		}
	}
	outputFile.close();
}
int main() {
	Item *data; //pointer
	Item *shoppingCart; //pointer
	int num;
	int qty;
	int flag = 0;
	string choice="n";
	// open file in input mode (to read)
	ifstream ProductFile("ProductData.csv");
	ProductFile >> num;
	data = new Item[200];
	shoppingCart = new Item[200];
	int size = 0;
	int datasize = 0;
	for (int i = 0; i < num; i++)
	{
		char ch = ' ';
		string line;
		//find Item Number
		ProductFile.seekg(30 + (29 * i));
		while (ch != ',')
		{
			ProductFile >> ch;
			if (ch != ',')
			{
				line = line + ch;

			}
		}
		data[i].itemNum = line; //enter into struct
		//find item Name
		ProductFile.seekg(38 + (29 * i));
		ch = ' ';
		line = " ";
		while (ch != ',')
		{
			ProductFile >> ch;
			if (ch != ',')
			{
				line = line + ch;

			}
		}
		data[i].name = line; //enter into struct
		//find item Cost
		ProductFile.seekg(50 + (29 * i));
		ch = ' ';
		line = " ";
		while (ch != ',')
		{
			ProductFile >> ch;
			if (ch != ',')
			{
				line = line + ch;

			}
		}
		data[i].cost = stod(line); //enter into struct
		//find item QTY
		ProductFile.seekg(56 + (29 * i));
		ProductFile >> data[i].qty;
		datasize++;
	}
	ProductFile.close();
	string name; //customer name
	string address; //customer address
	cout << "Enter name: ";
	getline(cin, name);
	cout << "Enter address: ";
	getline(cin, address);
	string ItemNumber;
	do
	{
		cout << "Input Item Number: "; //ask user to enter Item Number
		cin >> ItemNumber;
		//cout cart 
		if (ItemNumber == "cart")
		{
			shoppingcart(shoppingCart, size); 
		}
		else
		{
			//search array of structs for Item Number
			for (int i = 0; i < datasize; i++)
			{
				if (ItemNumber == data[i].itemNum)
				{
					do
					{
						cout << "Enter Quantity: "; //ask user to enter QTY
						cin >> qty;
						if (qty <= data[i].qty) //check if there is enough QTY
						{
							flag = 0;
							for (int j = 0; j < size; j++)
							{
								//update qty
								if (ItemNumber == shoppingCart[j].itemNum)
								{
									flag = 1;
									shoppingCart[j].qty += qty;
									data[i].qty -= qty;
									break;
								}
							}
							if (flag == 1)
							{
								break;
							}
							if (flag == 0)
							{
								//add item to shopping cart
								shoppingCart[size] = data[i];
								shoppingCart[size].qty = qty;
								data[i].qty -= qty;
								size++;
								break;
							}
						}
						
						else
						{
							//prompt user with error
							cout << "Not Enough Quantity!" << endl;
							if (data[i].qty == 0)
								break;
						}
					} while (qty > data[i].qty); //loop if QTY too much
				}
			}
		}
	} 
	while (ItemNumber != "0");
	//call invoice function
	invoice(shoppingCart, size);
	//call update function
	updateFile(shoppingCart, size);
	system("pause");
	return 0;
}
//get name and address from user
static void printCusotmerInfo(string name, string address) {
	ofstream invoice("invoice.txt");
	cout << "Customer Name: " << name << endl;
	cout << "Customer Address: " << address << endl;
	invoice << "Customer Name: " << name << endl;
	invoice << "Customer Address: " << address << endl;
}
