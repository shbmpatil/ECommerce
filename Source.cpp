// seekp.cpp : Defines the entry point for the console application.
//

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 

using namespace std;
static void printCusotmerInfo(string name, string address);
int main()
{
	int i = 27; //counter of location on line of file
	int row = 0; //row counter
	int col = 0; //collumn counter
	ifstream ProductFile("ProductData.csv"); //open file
	string ProductData[145][4]; //product data array
	for (int j = 0; j <= 723; j++)
	{
		ProductFile.seekg(i);
		string line; //line in file
		string output; //output to string
		getline(ProductFile, line);
		int fileSize = line.size();
		for (int k = 0; k < fileSize; ++k)
		{
			if (line[k] != ',') {
				output += line[k];
				i++;

			} //check for coma
			else
				break;
		} //check line in file
		i++;
		if (col == 4)
		{
			col = 0;
			row++;
		}	 //reset after end of row
		else {
			ProductData[row][col] = output;
			col++;
		} //next collumn
	}
	ProductFile.close();
	string name; //customer name
	string address; //customer address
	cout << "Enter name: ";
	getline(cin, name);
	cout << "Enter address: ";
	getline(cin, address);
	bool loop = true; //while num != 0
	int qty; //qty of purchase
	double total = 0; //total cost
	string shoppingCart[100][5]; //shopping cart array
	int y = 0; //shopping cart row
	while (loop) {
		bool found = false; //found item
		int itemNum; //item number
		cout << "Input item number: ";
		cin >> itemNum;
		if (itemNum == 0) //if item entered is 0 exit
			break;
		for (i = 0; i < 145; i++) {
			if (itemNum == stoi(ProductData[i][0]))
			{
				found = true;
				cout << "Name: " << ProductData[i][1] << endl << "Cost: $" << ProductData[i][2] << endl;
			qtynum:
				cout << "Enter quantity: ";
				cin >> qty;
				if (qty <= stoi(ProductData[i][3]))
				{
					shoppingCart[y][0] = ProductData[i][0];
					shoppingCart[y][1] = ProductData[i][1];
					shoppingCart[y][2] = to_string(qty);
					shoppingCart[y][3] = ProductData[i][2];
					shoppingCart[y][4] = to_string(stod(ProductData[i][2])*qty);
					total += stod(shoppingCart[y][4]);
					ProductData[i][3] = to_string(stoi(ProductData[i][3]) - qty);
					y++;
				} //load cart
				else if (stoi(ProductData[i][3]) == 0)
					cout << "item is out of stock" << endl; //if item is out of stock
				else {
					cout << "We don't have that many in stock, please reenter quantity" << endl;
					goto qtynum;
				} //if customer orders too much
			} //if item is found
		} //loop through data
		if (!found) //if not found return error
			cout << "Error: item not found" << endl;
	} //looop until customer exits
	//PRINT OUT RECIEPT
	ofstream invoice("invoice.txt");
	printCusotmerInfo(name, address);
	cout << setw(20) << "Item Number" << setw(21) << "Item Name" << setw(22) << "Qty" << setw(21) << "Unit Cost" << setw(20) << "Total" << endl;
	invoice << setw(20) << "Item Number" << setw(21) << "Item Name" << setw(22) << "Qty" << setw(21) << "Unit Cost" << setw(20) << "Total" << endl;
	cout << "........................................................................................................." << endl;
	invoice << "........................................................................................................." << endl;
	for (int x = 0; x < y; x++) {
		for (int w = 0; w < 5; w++) {
			cout << setw(20) << shoppingCart[x][w] << " ";
			invoice << setw(20) << shoppingCart[x][w] << " ";
		} //print cart
		if (x == y - 1)
		{
			cout << endl << "........................................................................................................." << endl;
			invoice << endl << "........................................................................................................." << endl;
		}
		else
		{
			cout << endl << "..." << endl;
			invoice << endl << "..." << endl;
		}
	} //print entire shopping cart
	cout << setw(100) << "Total: $" << total << endl;
	invoice << setw(100) << "Total: $" << total << endl;
	system("pause");
}
static void printCusotmerInfo(string name, string address) {
	ofstream invoice("invoice.txt");
	cout << "Customer Name: " << name << endl;
	cout << "Customer Address: " << address << endl;
	invoice << "Customer Name: " << name << endl;
	invoice << "Customer Address: " << address << endl;
}