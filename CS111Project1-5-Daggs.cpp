// CS111Project1-Daggs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define MAX_SIZE 20

typedef string BoatNames[MAX_SIZE];
typedef string BoatOwnerNames[MAX_SIZE];
typedef double BoatSizes[MAX_SIZE];

//preconditions: --
//postconditions: all array elements are intialized as follows:
//              string: ""
//              int: -1
void initArrays(BoatOwnerNames ownerNames, BoatNames boatNames, BoatSizes sizes, int size);

//preconditions: --
//postconditions: writes content of arrays bounded by size in the following order: boatname, 
//                ownerName, size
void printBoatData(BoatOwnerNames ownerNames, BoatNames boatNames, BoatSizes sizes, int size);

//preconditions:  all arrays have been initialized
//postconditions: arrays are filled with data from data.tx. 
//                File format is: owner name, boat size, boat name
 //               The parameter size is the number of lines in the file
//Notes: assumes a single string for owner name or boat name. Woods 320 Privacy is valid,
//       Tiger Woods 320 Privacy is not valid (line has three strings)
//       all file operations--opening, checking, reading, closing--must occur in readData(...)
//       It is possible that size may be one more than the number of data lines depending on
//       how the EOF character is represented.
void readData(BoatOwnerNames ownerNames, BoatNames boatNames, BoatSizes sizes, int& size);

//preconditions:  all arrays have valid data
//postconditions: prints data associated with target (boat owner); 
//                if not found, print Owner target not found
void findDataByOwnerName(BoatOwnerNames ownerNames, BoatNames boatNames, BoatSizes sizes, int size, string target);

//precondition: all arrays have valid data
//postcondition: all arrays are sorted in ascending order by boat size using bubblesort
void sortByBoatSize(BoatOwnerNames ownerNames, BoatNames boatNames, BoatSizes sizes, int size);

//precondition: --
//postcondition: values are swapped
void swap(double& a, double& b);
void swap(string& a, string& b);


int main()
{
    BoatNames boatNames;
    BoatOwnerNames ownerNames;
    BoatSizes boatSizes;

    initArrays(ownerNames, boatNames, boatSizes, MAX_SIZE);

    int arraySize = 0;
    readData(ownerNames, boatNames, boatSizes, arraySize);
    cout << "Number of lines read: " << arraySize << endl;

  /*  string target;
    if (!(!arraySize)) {
        cout << "Enter name of owner: ";
        cin >> target;
        findDataByOwnerName(ownerNames, boatNames, boatSizes, arraySize, target);
    }
    cout << endl;*/

    printBoatData(ownerNames, boatNames, boatSizes, arraySize);
    if (!(!arraySize)) {
        sortByBoatSize(ownerNames, boatNames, boatSizes, arraySize);
        printBoatData(ownerNames, boatNames, boatSizes, arraySize);
    }
}

void initArrays(BoatOwnerNames ownerNames, BoatNames boatNames, BoatSizes sizes, int size) {

    for (int i = 0; i < size; i++) {
        sizes[i] = i;
        boatNames[i] = i;
        ownerNames[i] = i;
    }


}

void readData(BoatOwnerNames ownerNames, BoatNames boatNames, BoatSizes sizes, int& size) {
    ifstream inFile;

    inFile.open("Data.txt");
    if (inFile.fail()) {
        cout << "Couldnt open data file\n";
        return;
    }

    string name = " ";
    string boatName = " ";
    int boatSize = -1;

    while (inFile >> name && size < MAX_SIZE) {
        inFile >> boatSize;
        inFile >> boatName;
        ownerNames[size] = name;
        sizes[size] = boatSize;
        boatNames[size] = boatName;
        size++;
    }
    if (!inFile.eof() && size == MAX_SIZE)
    {
        cout << "Some file contents may not have been read. \n";
    }
    inFile.close();
}

void findDataByOwnerName(BoatOwnerNames ownerNames, BoatNames boatNames, BoatSizes sizes, int size, string target) {
    for (int j = 0; j < size; j++)
    {
        if (ownerNames[j] == target) {
            cout << "Boat " << boatNames[j] << " owned by " << ownerNames[j] << " size " << sizes[j] << endl;
            return;
        }

    }
    cout << "Owner's name not found in the array." << endl;
}

void printBoatData(BoatOwnerNames ownerNames, BoatNames boatNames, BoatSizes sizes, int size) {
    if (!size) {
        cout << "file was empty\n";
    }
    for (int i = 0; i < size; i++) {
        cout << "Boat " << boatNames[i] << " owned by " << ownerNames[i] << " size " << sizes[i] << endl;
    }
    cout << "\n";
}

void sortByBoatSize(BoatOwnerNames ownerNames, BoatNames boatNames, BoatSizes sizes, int size) {
    int top = size - 1;
    bool done = false;
    int swaps = 0;

    while (!done && top > 0) {
        done = true;
        for (int k = 0; k < top; k++) {
            if (sizes[k] < sizes[k + 1]) {   
                done = false;
                swaps++;
                swap(sizes[k], sizes[k + 1]); 
                swap(ownerNames[k], ownerNames[k + 1]);
                swap(boatNames[k], boatNames[k + 1]);
            }
        }
        top--;
    }
   // cout << "Swaps: " << swaps << endl;
}

void swap(double& a, double& b) {
    int temp = a;
    a = b;
    b = temp;
}

void swap(string& a, string& b) {
    string temp = a;
    a = b;
    b = temp;
}

