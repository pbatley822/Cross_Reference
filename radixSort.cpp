//*************************************************************************************************//
//****																						   ****//
//**							----==== Radix Sort ====----									 **//
//**																							 **//
//**								  Gabriel Prestemon											 **//
//****																						   ****//
//*************************************************************************************************//

#include "doubleLinkedList.h"
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>

using namespace std;


//Sort function
void radixSort(list *l);

//calculates the number of passes the radix sort must take to sort all the numbers
int calculatePasses(list *l);

//obtains the largest number in the list
int findLargest(list *l);

//distributes the numbers into bins relating to the digit of the pass that the sort is on
void binDistribution(list *l, int pass, list* bins[]);

//returns the number of the bin which the number should be sorted into
int calculateBinNumber(int pass, int itemBeingSorted);

//returns all numbers to the  original list
void returnToOriginalList(list *mainList, list *numBin);



int main()
{
	list* toSort = newList();

	cout << "Welcome to RadixSort!" << endl;
	cout << "This program will sort a list of posititve integers up to base 10." << endl;

	//ask the user for a random list or inputted list, loop if choice is improper
	bool properInput = false;
	while (!properInput){
		//ask user if the list will be random or inputted
		cout << "Enter \"random\" for a random list, or \"input\" to input your own list." << endl;
		string userChoice;
		cin >> userChoice;

		if (userChoice == "random"){
			cout << "\nFilling the list with random numbers, base 10...\n";

			//fill the list with random numbers
			srand(time(NULL));
			for (int i = 0; i < 100; i++){
				pushFront(toSort, rand() % 10000);
			}
			displayList(toSort);

			//input is good, break from the loop
			properInput = true;
		}
		else if (userChoice == "input"){
			cout << "\nPlease enter 20 positive numbers.\n";
			int userIn;

			//fill the list with user input
			for (int i = 0; i < 20; i++){
				cin >> userIn;
				pushBack(toSort, userIn);
			}

			//input is good, break from the loop
			properInput = true;
		}
		else {
			//input is not good, ask for input again
			cout << "\nChoice not recognized, sorry, please try again.\n\n";
			properInput = false;
		}
	}

	radixSort(toSort);

	cout << endl << "The list has been sorted!" << endl;
	displayList(toSort);
	cout << "\n\n\nThank you, and have a nice day!\n\n";

	cout << "\n\n\n";
	system("pause");
	return 0;
}

//Sort function
void radixSort(list *l)
{
	//create a list of bins to sort numbers into
	list* bins[10];
	for (int i = 0; i < 10; i++){
		bins[i] = newList();
	}

	//set up pass counts (current pass and number of passes)
	int passes = calculatePasses(l);
	int pass = 0;

	while (pass < passes){
		//for every pass, sort the numbers into their corresponding bins according
		//to the current digit for the pass and return them to the list
		binDistribution(l, pass, bins);
		pass++;
	}

	//deletes the list from memory after the sort has finished
	for (int i = 0; i < 10; i++){
		freeList(bins[i]);
	}
}


//calculates the number of passes the radix sort must take to sort all the numbers
int calculatePasses(list *l)
{
	int largest = findLargest(l);
	//passes = number of digits of the largest number, count the digits of the largest number
	int passes = 0;

	//divide the largest by 10, every operation is a digit and a pass
	while (largest > 0){
		largest /= 10;
		passes++;
	}
	return passes;
}


//obtains the largest number in the list
int findLargest(list *l)
{
	int largest = l->front->content;
	node* hold = l->front->next;

	//cycle through the list until the end
	while (hold != NULL){
		if (hold->content > largest){
			largest = hold->content;
		}
		hold = hold->next;
	}
	return largest;
}



//distributes the numbers into bins relating to the digit of the pass that the sort is on
void binDistribution(list *l, int pass, list* bins[])
{
	//loop to empty the entire list
	while (!isEmpty(l)){

		//obtain the next number in the list to be sorted
		int numberToBeSorted = popFront(l);

		//obtain the bin number in which the number will be sorted into
		int binNumber = calculateBinNumber(pass, numberToBeSorted);	

		//inserts the number into it's corresponding bin
		pushBack(bins[binNumber], numberToBeSorted);
	}

	//returns all numbers to the original list
	for (int i = 0; i < 10; i++){
		returnToOriginalList(l, bins[i]);
	}
}


//returns the number of the bin which the number should be sorted into
int calculateBinNumber(int pass, int numberToBeSorted)
{
	int placeValue = pow(10, pass);
	int binNumber = (numberToBeSorted / placeValue) % 10;
	return binNumber;
}


//returns all numbers to the original list
void returnToOriginalList(list *mainList, list *numBin)
{
	while (!isEmpty(numBin)){
		pushBack(mainList, popFront(numBin));
	}
}