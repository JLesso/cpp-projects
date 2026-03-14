#include <iostream>
#include <fstream>  // to read and write files
#include <sstream>
#include <algorithm>
using namespace std;
class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode(int val) { // Constructor
        value = val;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    int getValue() { 
        return value;
    }
};

class QueueNode {
public:
    TreeNode* n;
    QueueNode* next;

    QueueNode(TreeNode* node) {// Constructor
        n = node;
        next = nullptr;
    }

};

class Queue {
private:
    QueueNode* front;
    QueueNode* rear;

public:
    int size() {
        int count = 0;
        QueueNode* current = front;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
    void enqueue(TreeNode* q) { // Add to end
        QueueNode* nn = new QueueNode(q);
        if (!front)
        {
            front = rear = nn;
        }
        else
        {
            rear->next = nn;
            rear = nn;
        }
    }
    TreeNode* dequeue() {      // Remove from front
        if (!front) {
            cout << "Queue is empty.\n";
            return nullptr; // or throw exception
        }
        QueueNode* temp = front;
        TreeNode* max = front->n;
        front = front->next;
        delete temp;
        if (front == nullptr)
        {
            rear = nullptr;
        }
        return max;
    }
    bool isEmpty() {// Check if queue is empty
        if (front == nullptr) {
            return true;
        }
        return false;
    }           
    Queue() {    // Constructor
        front = nullptr;
        rear = nullptr;
    }
};


class Heap {
private:
    TreeNode* root;

    TreeNode* findInsertParent() {  // Find spot to insert (BFS)

        TreeNode* last = getLastNode();
        if (last) {
            return last->parent;
        }
        return nullptr;
    }
    TreeNode* getLastNode() {// Find last node for deletion

        if (root == nullptr)
            return nullptr;
        Queue temp;
        temp.enqueue(root);
        TreeNode* last = nullptr;
        while (!temp.isEmpty()) {
            last = temp.dequeue();
            if (last->left)
                temp.enqueue(last->left);
            if (last->right)
                temp.enqueue(last->right);
        }
        return last;
    }
    void siftUp(TreeNode* n) {        // Maintain heap after insert
        
        while (n && n->parent && n->value > n->parent->value) {
            swapValues(n, n->parent);
            n = n->parent;
        }
    }
    void siftDown(TreeNode* n) {      // Maintain heap after delete
        TreeNode* max;
        while (n && n->right && n->left) {
            max = n->left;
            if (n->right->value > max->value){
                max = n->right;
            }
            swapValues(n, max);
            n = max;
            
        }
    }
    void swapValues(TreeNode* n1, TreeNode* n2) { // Swap values only
        int temp = n1->value;
        n1->value = n2->value;
        n2->value = temp;
    }

public:
    Heap() {    // Constructor
        root = nullptr;
    }
    void insert(int value) {       // Insert a new value
        TreeNode* newNode = new TreeNode(value);
        if (root == NULL){ 
            root = newNode;
            return;
        }
        Queue temp;
        temp.enqueue(root);
        while (true)
        {
            TreeNode* curr = temp.dequeue();
            if (!curr->left) {
                curr->left = newNode;
                newNode->parent = curr;
                break;
            }
            else {
                temp.enqueue(curr->left);
            }
            if (!curr->right) {
                curr->right = newNode;
                newNode->parent = curr;
                break;
            }
            else {
                temp.enqueue(curr->right);
            }
        }
        siftUp(newNode);
            
    }
    void deleteMax() {             // Remove max (root)
        if (!root)
        {
            cout << "root empty" << endl;
            return;
        }
        TreeNode* last;
        last = getLastNode();
        if (last == root) {
            delete root;
            root = nullptr;
            return;
        }
        swapValues(root, last);
        TreeNode* parent = last->parent;
        if (parent->left == last) {
            parent->left = nullptr;
        }
        else {
            parent->right = nullptr;
        }

        delete last;
            
        siftDown(root);
    }
    void print( ofstream& out) {       // Print tree level by level
        if (!root) return;
        Queue q;
        q.enqueue(root);
        while (!q.isEmpty()) {
            size_t levelSize = q.size();
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* n = q.dequeue();
                out <<"(" << n->value << ") ";
                if (n->left) {
                    q.enqueue(n->left);
                }
                if (n->right) {
                    q.enqueue(n->right);
                }
            }
            out << "\n";
        }
    }
};

int main() {
    ifstream inFile; // input file stream to read the data
    ofstream outFile;// output file stream to write the data
    // open the input.txt and create output.txt
    inFile.open("input.txt");
    outFile.open("output.txt");
    //Error check to see if files opened
    if (!inFile || !outFile) {
        cout << "Error" << endl;
        return 1;
    }
    Heap n1;
    string inp;
    while (inFile >> inp) {
        // assume each is an integer key
        // ignore non-numeric
        int key = stoi(inp);
        n1.insert(key);
    }
    n1.print(outFile);// prints Heap
    outFile << "==============\n";
    n1.deleteMax();
    n1.print(outFile);
    outFile << "==============\n";
    n1.deleteMax();
    n1.print(outFile);
    outFile << "==============\n";
    inFile.close(); //closes inputfile
    outFile.close();//closes outputfile

    return 0;
}