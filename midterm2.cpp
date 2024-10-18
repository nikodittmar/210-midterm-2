// COMSC 210 | Midterm #2 | Niko Dittmar
#include <fstream>
#include <iostream>
using namespace std;

class Line {
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
    Line() { head = nullptr; tail = nullptr; size = 0;}

    // insert_after() adds a person in line after the specified position.
    // arguments: name - the name of the person to add, position - the position to add them after.
    // returns: void
    void insert_after(string name, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(name);
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

    // pop_back() removes a person in line by name.
    // arguments: name - the name of the person to remove.
    // returns: void
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

    // pop_back() deletes a person at the specified position. Also notifies the user.
    // arguments: pos - the position of the person to remove.
    // returns: true if the person was successfully deleted, false if otherwise
    bool delete_pos(int pos) {
        if (!head) {
            return false;
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
            return true;
        }
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return false;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return false;
        }
    
        if (!temp->next) {
            return pop_back();;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        cout << "   " << temp->name << " left the line" << endl;
        delete temp;
        size--;
        return true;
    }

    // pop_back() adds someone to the back of the line. Notifies the user.
    // arguments: name - the name of the person to add.
    // returns: void
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
    
    // push_front() adds a VIP to the front of the line. Notifies the user.
    // arguments: name - the name of the VIP
    // returns: void
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
    
    // pop_back() serves the first person in line. Also notifies the user.
    // arguments: none
    // returns: true if the person was successfully deleted, false if otherwise
    bool pop_front() {

        if (!head) {
            return false;
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
        return true;
    }

    // pop_back() removes the last person in line. Also notifies the user.
    // arguments: none
    // returns: true if the person was successfully deleted, false if otherwise
    bool pop_back() {
        if (!tail) {
            return false;
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
        return true;
    }

    ~Line() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // print() prints the contents of the line.
    // arguments: none
    // returns: void
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

    // print_reverse() prints the contents of the line in reverse order.
    // arguments: none
    // returns: void
    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "The line is empty" << endl << endl;
            return;
        }
        cout << "Resulting line:" << endl;
        while (current) {
            cout << "      " << current->name << endl;
            current = current->prev;
        }
        cout << endl;
    }

    // getSize() returns the size of the line.
    // arguments: none
    // returns: the size of the line (int)
    int getSize() {
        return size;
    }
};


int main() {
    // Create names vector.
    vector<string> names;

    ifstream inputFile("names.txt");

    string name;

    // Add names from the file into the names vector.
    while (getline(inputFile, name)) {
        names.push_back(name);
    }

    // Set random seed.
    srand(time(0));

    // Initialize the line.
    Line line;

    cout << "Store opens:" << endl;

    // Add initial 5 customers.
    for (int i = 0; i < 5; i++) {
        int random_index = rand() % names.size();
        string randomName = names[random_index];
        line.push_back(randomName);
    }

    // Print the line.
    line.print();

    int prob = 0;

    // Simulate the 20 timesteps.
    for (int i = 1; i < 20; i++) {
        cout << "Time step #" << (i + 1) << ":" << endl;

        // Keep track if an event has occurred.
        bool event = false;

        // Check if someone was served (40% probabilty)
        prob = rand() % 100 + 1;
        if (prob <= 40 && line.pop_front()) {
            event = true;
        }

        // Check if someone was frustrated and left the line (20% probabilty)
        prob = rand() % 100 + 1;
        if (prob <= 20 && line.pop_back()) {
            event = true;
        }

        // Check if a particular person in line decided to leave (10% probabilty)
        prob = rand() % 100 + 1;
        if (prob <= 10) {
            int random_pos = (rand() % line.getSize()) + 1;
            if (line.delete_pos(random_pos)) {;
                event = true;
            }
        }

        // Check if someone joined the line (60% probabilty)
        prob = rand() % 100 + 1;
        if (prob <= 60) {
            int random_index = rand() % names.size();
            string randomName = names[random_index];
            line.push_back(randomName);
            event = true;
        }

        // Check if a VIP has arrived (10% probability)
        prob = rand() % 100 + 1;
        if (prob <= 10) {
            int random_index = rand() % names.size();
            string randomName = names[random_index];
            line.push_front(randomName);
            event = true;
        }

        // If no event happened, let the user know.
        if (!event) {
            cout << "   " << "Nothing happened" << endl;
        }

        // Print the status of the line.
        line.print();
    }


    return 0;
}