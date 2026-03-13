#include <iostream>  // for input and output
#include <fstream>  // to read and write files
#include <string>  // To use string data type 
#include <cctype> // For toLower()
using namespace std;

class node { // node class for doubly linked list

public:
    string name;
    node* next;
    node* prev;
    node(string name) { // Constructor with initialization 
        this->name = name;
        next = NULL;
        prev = NULL;
    }
};
class DoublyLinkedList { // Doubly linked list class

public:
    DoublyLinkedList() { head = nullptr, tail = nullptr; }// Constructor with initialization for an empty list
    void insert(string name); // Inserts node sorted
    void deleteNode(string name);// Deletes a node by name
    void traverseAscending(ofstream& outFile); //prints in Ascending order
    void traverseDescending(ofstream& outFile);//prints in Descending order


private:
    node* head;
    node* tail;

};
void DoublyLinkedList::insert(string n) {// Function that inserts a node in sorted order
    node* newNode = new node(n);
    if (!head) { // checks if empty,then set newnode as head and tail
        head = tail = newNode; return;
    }//no other nodes
    if (n < head->name) {//Inserts at the head
        newNode->next = head; head->prev = newNode; head = newNode; 
    }//smaller than head
    else if (n > tail->name) {//Inserts at the tail
        tail->next = newNode; newNode->prev = tail; tail = newNode;
    } //larger than tail 
    else { //Inserts somewhere in the middle
        node* current = head;
        while (current != nullptr && current->name < n) {
            current = current->next;
        }
        newNode->prev = current->prev;
        newNode->next = current; 
        if (current->prev != nullptr) {
            current->prev->next = newNode;
        }
        current->prev = newNode;
    }
}

void DoublyLinkedList::deleteNode(string n) {// Function that deletes a node by name
    if (!head) return; //empty list nothing to delete
    node* current = head;
    while (current != nullptr && current->name != n) {
        current = current->next;
    }
    if (current == nullptr) return; // Node not found
   
    if (current == head) //if node to delete is head
    {   
        head = head->next;
        if (head) head->prev = nullptr;
        else { tail = nullptr; }// List becomes empty
    }
    else if (current == tail)//if node to delete is tail
    {   
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else { head = nullptr; }// List becomes empty
    }
    else 
    {   // if node toDelete is somewhere in the middle
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }
    delete current; //deallocates memory
}
// Function that traverses the list in ascending order and write it to the outputfile
void DoublyLinkedList::traverseAscending(ofstream& outFile) {
    if (!head) { //empty list, nothing to traverse
        return;
    }
    node* current = head;
    while (current != nullptr)//prints in Ascending order
    {
        outFile << current->name << endl;
        current = current->next;
    }
    if (current == nullptr)
    {
        return;
    }
}
// Function that traverses the list in Descending order and write it to the outputfile
void DoublyLinkedList::traverseDescending(ofstream& outFile) {
    if (!tail) { //empty list, nothing to traverse
        return;
    }
    node* current = tail;
    while (current != nullptr)//prints in Descending order
    {
        outFile << current->name << endl;
        current = current->prev;
    }
    if (current == nullptr)
    {
        return;
    }
}
string toLower(string n)//converts input line to lowerCase
{
    for (int i = 0; i < n.length(); i++) {
        n[i] = tolower(n[i]);
    }
    return n;
}
int main() {
    DoublyLinkedList list; //Creates the  doubly linked list
    ifstream inFile; // input file stream to read the data
    ofstream outFile;// output file stream to write the data
    // open the input.txt and create output.txt
    inFile.open("input.txt");
    outFile.open("output.txt");
    //Error check to see if files opened
    if (!inFile || !outFile) {
        cerr << "Error" << endl;
        return 1;
    }
    string line; //string to hold each line from inputfile
    while (getline(inFile, line)) {//reads each line form input file
        line = toLower(line);//converts each line to lowercase using lowercase fuction
        if (line.substr(0, 7) == "delete ")//checks if line starts with delete 
        {
            string nameToDelete = line.substr(7);// get the name after delete
            list.deleteNode(nameToDelete);// deletes name/node from list
        }
        else {
            list.insert(line);// other if delete not found it inserts into list in sorted order
        }
    }
    list.traverseAscending(outFile);// print list in Ascending order on output file
    outFile << "==============\n";
    list.traverseDescending(outFile);// print list in Descending order on output file
    inFile.close(); //closes inputfile
    outFile.close();//closes outputfile

    return 0;
}