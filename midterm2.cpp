#include <fstream>
#include <iostream>
using namespace std;

class DoublyLinkedList {
private:
    struct Node {
        string name;
        Node* prev;
        Node* next;
        Node(string s, Node* p = nullptr, Node* n = nullptr) {
            name = s; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; size = 0;}

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            size++;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
        size++;
    }

    void delete_val(string name) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->name != name)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
        size--;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;
    
        if (pos == 1) {
            if (head->next) {
                head = head->next;
                head->prev = nullptr;
            }
            else
                head = tail = nullptr;
            delete temp;
            size--;
            cout << "   " << temp->name << " left the line" << endl;
            return;
        }
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        cout << "   " << temp->name << " left the line" << endl;
        delete temp;
        size--;
        
    }

    void push_back(string name) {
        Node* newNode = new Node(name);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        cout << "   " << name << " joins the line" << endl;
        size++;
    }
    
    void push_front(string name) {
        Node* newNode = new Node(name);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
        cout << "   " << name << " (VIP) joins the front of the line" << endl;
    }
    
    void pop_front() {

        if (!head) {
            return;
        }

        Node * temp = head;
        cout << "   " << temp->name << " is served" << endl;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
        size--;
    }

    void pop_back() {
        if (!tail) {
            return;
        }
        Node * temp = tail;
        cout << "   " << temp->name << " (at the rear) left the line"  << endl;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
        size--;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "The line is empty" << endl << endl;
            return;
        }
        cout << "Resulting line:" << endl;
        while (current) {
            cout << "      " << current->name << endl;
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "The line is empty" << endl << endl;
            return;
        }
        while (current) {
            cout << current->name << " ";
            current = current->prev;
        }
        cout << endl;
    }

    int getSize() {
        return size;
    }
};



int main() {
    vector<string> names;

    ifstream inputFile("names.txt");

    string name;

    while (getline(inputFile, name)) {
        names.push_back(name);
    }

    srand(time(0));


    DoublyLinkedList line;

    cout << "Store opens:" << endl;

    for (int i = 0; i < 5; i++) {
        int random_index = rand() % names.size();
        string randomName = names[random_index];
        line.push_back(randomName);
    }

    line.print();
    int prob = 0;

    for (int i = 1; i < 20; i++) {
        cout << "Time step #" << (i + 1) << ":" << endl;
        bool event = false;
        prob = rand() % 100 + 1;
        if (prob <= 40) {
            line.pop_front();
            event = true;
        }
        prob = rand() % 100 + 1;
        if (prob <= 60) {
            int random_index = rand() % names.size();
            string randomName = names[random_index];
            line.push_back(randomName);
            event = true;
        }
        prob = rand() % 100 + 1;
        if (prob <= 20) {
            line.pop_back();
            event = true;
        }
        prob = rand() % 100 + 1;
        if (prob <= 10) {
            int random_pos = (rand() % line.getSize()) + 1;
            line.delete_pos(random_pos);
            event = true;
        }
        prob = rand() % 100 + 1;
        if (prob <= 10) {
            int random_index = rand() % names.size();
            string randomName = names[random_index];
            line.push_front(randomName);
            event = true;
        }
        if (!event) {
            cout << "   " << "Nothing happened" << endl;
        }
        line.print();
    }


    return 0;
}