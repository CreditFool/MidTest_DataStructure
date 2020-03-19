#include <iostream>
#include <stdlib.h>

using namespace std;

struct Node {
    int value;
    Node* next;
    Node* prev;
};

class doubleLinkedList {
    private:
        Node* head;
        Node* tail;

        bool isEmpty(Node* node) {
            return node == NULL;
        }

    public:
        doubleLinkedList() {
            head = NULL;
            tail = NULL;
        }

        void printList() {
            Node* node = head;
            
            if (node == NULL) 
                cout << "Null" << endl;
            
            else {
                do {
                    cout << node->value << " ";
                    node = node->next;
                } while (node != head);
                cout << endl;
            } 
        }

        void printListRev() {
            Node* node = tail;
            
            if (node == NULL) 
                cout << "Null" << endl;
            
            else {
                do {
                    cout << node->value << " ";
                    node = node->prev;
                } while (node != tail);
                cout << endl;
            } 
        }

        void insertHead(int val) {
            Node* newNode = new Node;
            newNode->value = val;

            if(isEmpty(head)) 
            {
                newNode->next = newNode;
                newNode->prev = newNode;
                tail = newNode;
            } 
            else 
            {
                newNode->next = head;
                newNode->prev = tail;
                head->prev = newNode;
            }

            head = newNode;
            tail->next = head;
        }

        void insertTail(int val) {
            Node* newNode = new Node;
            newNode->value = val;

            if (isEmpty(head)) 
                insertHead(val);
            else
            {
                tail->next = newNode;
                newNode->prev = tail;
                newNode->next = head;

                head->prev = newNode;
                tail = newNode;
            }
        }

        void removeHead() {
            if (isEmpty(head)) {
                cout << "Null" << endl;
            }
            else {
                Node* del = head;
                
                if (head == tail) 
                {
                    head = NULL;
                    tail = NULL;
                }
                else 
                {
                    head = head->next;
                    head->prev = tail;
                    tail->next = head;
                }

                delete del;
            }
        }

        void removeTail() {
            if (isEmpty(head)) {
                cout << "Null" << endl;
            }
            else {
                Node* del = tail;

                if (head == tail) 
                {
                    head = NULL;
                    tail = NULL;
                }
                else 
                {
                    tail = tail->prev;
                    tail->next = head;
                    head->prev = tail;
                }

                delete del;
            }
        }

        void clear() {
            tail->next = NULL;
            while (head != NULL) {
                Node *del = head;
                head->prev = NULL;
                head = head->next;
                tail = head;
                del->next = NULL;
                
                delete del;
            }
        }

        int length() {
            int len = 0;

            if (head != NULL) {
                Node* node = head;
                do {
                    len++;
                    node = node->next;
                } while (node != head);
            }
            return len;
        }

        void insert(int i, int val) {
            Node* newNode = new Node;
            newNode->value = val;

            unsigned int index = 0;

            if (i == 0)
                insertHead(val);

            else if (i > 0 && i <= length()-1) {
                Node* body = head;

                do {
                    body = body->next;
                    index++;
                } while(index != i);

                newNode->next = body;
                newNode->prev = body->prev;
                body->prev->next = newNode;
                body->prev = newNode;
            }

            else if (i == length())
                insertTail(val);

            else 
                cout << "Error: Index tidak ditemukan" << endl;
        }

        void remove(int i) {
            unsigned int index = 0;
            
            if (i == 0)
                removeHead();

            else if (i > 0 and i < length()-1) {
                Node* body = head;
                Node* del;

                do {
                    body = body->next;
                    index++;
                } while(index != i);

                del = body;

                body->next->prev = body->prev;
                body->prev->next = body->next;
                
                delete del;
            }

            else if (i == length()-1)
                removeTail();

            else 
                cout << "Error: Index tidak ditemukan" << endl;
        }
};