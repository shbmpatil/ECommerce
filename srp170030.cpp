#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
#include <stdlib.h>
#include <cstdlib>

using namespace std;

struct node {
	string itemNum;
	string name;
	double cost;
	int qty;
	struct node* next;   
};

//read in ProductData file
void read(struct node* &headref) {
	struct node *current = headref;
	ifstream ProductFile("ProductData.csv");
	string line;
	char delim = ',';
	//find iteum num
	while (!ProductFile.eof()) {
		string num = "";
		string itemName = "";
		string itemCost = "";
		string itemQty = "";
		int count = 0;
		int i = 0;
		getline(ProductFile, line);
		//use switch statements to delimit commas
		for (i=0; i<line.size(); i++) {
			switch (count) {
			case 0: 
				if (line[i] != delim)
					num += line[i];
				else
					count++;
					break;
			case 1:
				if (line[i] != delim)
					itemName += line[i];
				else
					count++;
					break;
			case 2:
				if (line[i] != delim)
					itemCost += line[i];
				else
					count++;
					break;
			case 3:
				if (line[i] != delim)
					itemQty += line[i];
				else
					count++;
					break;
			}
		}

		//cout << num << " " << itemName << " " << itemCost << " " << itemQty << endl;

		struct node *temp = new struct node;
		temp->itemNum = num;
		temp->name = itemName;
		temp->cost = atof(itemCost.c_str());
		temp->qty = atoi(itemQty.c_str());
		temp->next = nullptr;
		if (headref == nullptr) {
			headref = temp;
			current = headref;
		}
		else {
			current->next = temp;
			current = current->next;
		}
	}
	ProductFile.close();
}


void invoice(struct node* head) 
{
	//PRINT OUT RECIEPT
	double total = 0;
	ofstream invoice("invoice.txt");
	//format heading for reciept
	cout << setw(20) << "Item Number" << setw(21) << "Item Name" << setw(21) << "Qty" << setw(25) << "Unit Cost" << setw(20) << "Total" << endl;
	invoice << setw(20) << "Item Number" << setw(21) << "Item Name" << setw(21) << "Qty" << setw(25) << "Unit Cost" << setw(20) << "Total" << endl;
	cout << "........................................................................................................." << endl;
	invoice << "........................................................................................................." << endl;
	struct node *current = head;
	while (current != NULL)						//Loop through the list until we find the end
	{					
		cout << setw(20) << current->itemNum << " "; //print Item number
		cout << setw(20) << current->name << " "; //print name
		cout << setw(20) << current->qty << " "; //print qty
		cout << setw(20) << current->cost << " "; //print cost
		cout << setw(20) << current->cost * current->qty << " "; //print total
		cout << endl << "..." << endl;
		invoice << setw(20) << current->itemNum << " "; //print Item number
		invoice << setw(20) << current->name << " "; //print name
		invoice << setw(20) << current->qty << " "; //print qty
		invoice << setw(20) << current->cost << " "; //print cost
		invoice << setw(20) << current->cost * current->qty << " "; //print total
		total += current->cost*current->qty;
		current = current->next;				//Set the current node to the next node
		invoice << endl << "..." << endl;
	}
	cout << endl << "........................................................................................................." << endl;
	cout << setw(98) << "Total: $" << total << endl;
	invoice << endl << "........................................................................................................." << endl;
	invoice << setw(98) << "Total: $" << total << endl;
	system("pause");
}

void printlist(struct node* head) {
	struct node *current = head;
	while (current != NULL) {					//Loop through the list until we find the end
		cout << current->itemNum << " ";
		cout << current->name << " ";
		cout << current->cost << " ";
		cout << current->qty << "\n";
		current = current->next;				//Set the current node to the next node
	}
}

void Append(struct node*& head, string newItemNum, string newName, double newCost, int newQty) {
	//create new current node
	struct node* current = new struct node;	
	//Create a new node
	struct node* newNode = new struct node;	

	newNode->itemNum = newItemNum;		//Set itemnum
	newNode->name = newName;		//Set name
	newNode->cost = newCost;		//Set cost
	newNode->qty = newQty;		//Set qty
	newNode->next = nullptr;

	if (!head) //not head node
	{			
		head = newNode;	//equate head to newnode
	}
	else 
	{
		current = head;		//Set the current node to the head node

		while (current->next)	//go through linkedlist
		{		
			current = current->next;
		}
		current->next = newNode;	//current points to new node.
	}
	head = head;     //head = head
}

//delete function
void delet(struct node* head) 
{
	string ItemNumber;
	cout << "Enter Item Number of the Item to be Deleted" << endl;
	cin >> ItemNumber;
	struct node *current = head;
	struct node *prevNode = head;
	current = current->next;
	while (current != NULL) //Loop through the list until we find the end
	{					
		if (current->itemNum == ItemNumber)
		{
			if (current->next == nullptr)
			{
				current = nullptr;
				delete current;
				break;
			}
			else
			{
				prevNode->next = current->next;
				delete current;
				break;
			}
		}
		current = current->next;				//Set the current node to the next node
		prevNode = prevNode->next;
	}
}

//update function
void updateQty(struct node* head)
{
	int quantity;
	string ItemNumber;
	cout << "Enter Item Number of the Item to be Updated" << endl;
	cin >> ItemNumber;
	cout << "Enter New Quantity" << endl;
	cin >> quantity;
	struct node *current = head;
	while (current != NULL) //Loop through the list until we find the end
	{
		if (current->itemNum == ItemNumber)
		{
			current->qty = quantity;
			break;
		}
	}
}

//update file
void updateFile(struct node* head)
{
	fstream outputFile;
	outputFile.open("ProductData.csv", ios::in | ios::out);
	struct node *current = head;
	while (current != NULL) //Loop through the list until we find the end
	{
		outputFile << current->itemNum << "," << current->name << "," << current->cost << "," << current->qty << endl;
		current = current->next;
	}
	
}

//delete function
void DeleteList(struct node*& head) {
	//current node to go throguh function
	struct node* current = head;

	//next node to keep track
	struct node* nextNode = head;

	while (current != nullptr) {		//go till end
		nextNode = current->next;	//point next node to next
		delete current;				//delete current
		current = nextNode;			//Set current to to nextnode
	}
	head = nullptr;		//Return nullptr 
}
int main() {

	struct node *head = nullptr;
	struct node *schead = nullptr;
	read(*&head);
	int qty;
	int flag;
	string ItemNumber;
	int size = 0;
	int datasize = 0;
	string custname; //customer name
	string custaddress; //customer address
	cout << "Enter name: ";
	getline(cin, custname);
	cout << "Enter address: ";
	getline(cin, custaddress);
	char choice;
	//admin node
	cout << "Do you Want to Access Admin Mode? (y/n)" << endl;
	cin >> choice;
	if (choice == 'y' || choice == 'Y')
	{
		//add product
		cout << "1. Add New Product" << endl;
		//delete product
		cout << "2. Delete A Product" << endl;
		//update quantity
		cout << "3. Update Quantity" << endl;
		char choice2;
		cin >> choice2;
		string tempitemNumber;
		string tempitemName;
		double tempitemCost;
		int tempQty;
		char temporary;
		switch (choice2)
		{
		//case 1
		case '1': 
			cout << "Enter Product Item Number" << endl;
			cin >> tempitemNumber;
			cout << "Enter Product Name" << endl;
			cin.ignore();
			getline(cin,tempitemName);
			cout << "Enter Product Cost" << endl;
			cin >> tempitemCost;
			cout << "Enter Product Qty" << endl;
			cin >> tempQty;
			Append(head, tempitemNumber, tempitemName, tempitemCost, tempQty);
			cout << "Append Successful" << endl;
			break;
		//case 2
		case '2':
			delet(head);
			printlist(head);
			cout << "Delete Successful" << endl;
			break;
		//case 3
		case '3':
			updateQty(head);
			cout << "Update Successful" << endl;
			printlist(head);
			break;
		default: cout << "Sorry" << endl;
		}
	}
	else
	{
		
		do
		{
			cout << "Input Item Number: "; //ask user to enter Item Number
			cin >> ItemNumber;
			//cout cart 
			if (ItemNumber == "cart")
			{
				//output invoice using function
				invoice(schead);
			}
			else
			{
				//search linked lists for Item Number
				//struct node *temp = new struct node;
				int outflag = 0;
				struct node* temp = head;
				while (temp != nullptr)
				{
					if (ItemNumber == temp->itemNum)
					{
						outflag = 1;
						do
						{
							cout << "Enter Quantity: "; //ask user to enter QTY
							cin >> qty;
							if (qty <= temp->qty) //check if there is enough QTY
							{
								temp->qty = temp->qty - qty;
								flag = 0;
								if (schead == nullptr)
								{
									struct node* newNode = new struct node;
									newNode->itemNum = temp->itemNum;
									newNode->name = temp->name;
									newNode->cost = temp->cost;
									newNode->qty = qty;
									newNode->next = nullptr;
									schead = newNode;
									break;
								}
								else
								{
									struct node* current = schead;

									while (current != nullptr)
									{
										if (current->itemNum == ItemNumber)
										{
											flag = 1;
											current->qty = current->qty + qty;
											break;
										}
										current = current->next;
									}

									if (flag == 0)
									{
										struct node* newNode = new struct node;
										newNode->itemNum = temp->itemNum;
										newNode->name = temp->name;
										newNode->cost = temp->cost;
										newNode->qty = qty;
										newNode->next = nullptr;
										current = newNode;
										struct node* temp1 = new struct node;
										temp1 = schead;		//Set the current node to the head node
										while (temp1->next) {		//Traverse the linked list until you reach the end
											temp1 = temp1->next;
										}
										temp1->next = newNode;		//At the end set the current to point to the new node.
									}
									break;
								}
							}

							else
							{
								//prompt user with error
								cout << "Not Enough Quantity!" << endl;
								if (temp->qty == 0)
									break;
							}
						} while (qty > temp->qty); //loop if QTY too much
						if (outflag == 1)
						{
							break;
						}
					}
					temp = temp->next;
				}
			}
		} while (ItemNumber != "0");
		//call invoice function
		invoice(schead);
	}
	//call update function
	updateFile(head);
	system("pause");
	DeleteList(head);
	DeleteList(schead);
	return 0;

}
	

