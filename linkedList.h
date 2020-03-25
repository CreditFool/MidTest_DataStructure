#include <iostream>
#include <stdlib.h>

using namespace std;

template<typename T>
class singgleLinkedList {
    private:
        struct Node {
            T value;
            Node* next;
        };

        Node* head;
        Node* tail;

        bool isEmpty(Node* val) {
            return val == NULL;
        }

    public:
        singgleLinkedList() {
            head = NULL;
            tail = NULL;
        }

        int size() {
            int len = 0;

            Node* val = head;
            while (val != NULL) {
                len++;
                val = val->next;
            }

            return len;
        }

        void printList() {
            Node* val = head;
            if (isEmpty(val)) 
                cout << "Null" << endl;
            
            else {
                do {
                    cout << val->value << " ";
                    val = val->next;
                } while (val != NULL);
                cout << endl;
            }
        }

        void insertHead(T val) {
            Node* body = new Node;
            body->value = val;

            if (isEmpty(head)) {
                head = body;
                head->next = NULL;
                tail = head;
            }
            else {
                body->next = head;
                head = body;
            }
        }

        void insertTail(T val) {
            Node* body = new Node;
            body->value = val;
            body->next = NULL;

            if (isEmpty(head)) {
                tail = body;
                head = tail;
            }
            else {
                tail->next = body;
                tail = body;
            }
        }

        void removeHead() {
            if (isEmpty(head)) {
                cout << "Null" << endl;
            }
            else {
                Node* del = head;
                head = head->next;
                delete del;
                del = NULL;
            }
        }

        void removeTail() {
            if (isEmpty(head)) {
                cout << "Null" << endl;
            }
            else {
                Node* del;
                if (isEmpty(head->next)) {
                    del = head;
                    delete del;
                    del = NULL;
                    head = NULL;
                }
                else {
                    del = tail;
                    tail = head;
                    while (tail->next->next != NULL) {
                        tail = tail->next;
                    }
                    tail->next = NULL;
                    delete del;
                    del = NULL;
                }
            }
        }

        void clear() {
            while (head != NULL) {
                Node* del = head;
                head = head->next;
                delete del;
                del = NULL;
            }
        }

        void insert(int i, T val) {
            Node* newBody = new Node;
            newBody->value = val;

            unsigned int index = 0;

            if (i == 0)
                insertHead(val);

            else if (i == size())
                insertTail(val);

            else if (i > size()) {
                if (isEmpty(head))
                    insertHead(0);
                
                index = size()-1;
                while (index != i-1) {
                    Node* body = new Node;
                    body->value = 0;
                    tail->next = body;
                    tail = tail->next;
                    index++;
                }
                tail->next = newBody;
                tail = tail->next;
                tail->next = NULL;
            }

            else if (i > 0 && i < size()) {
                Node* body = head;
                while (index != i-1) {
                    body = body->next;
                    index++;
                }
                newBody->next = body->next;
                body->next = newBody;
            }

            else 
                cout << "Error: Index tidak ditemukan" << endl;
        }

        void remove(int i) {
            unsigned int index = 0;
            
            if (i == 0)
                removeHead();

            else if (i == size()-1)
                removeTail();

            else if (i > 0 and i < size()-1) {
                Node* body = head;
                Node* del;
                while (index != i-1) {
                    body = body->next;
                    index++;
                }
                del = body->next;
                body->next = body->next->next;
                delete del;
                del = NULL;
            }

            else 
                cout << "Error: Index tidak ditemukan" << endl;
        }

        T getData(int i) {
            unsigned index = 0;
            Node* indexData = head;
            
            while (index != i) {
                indexData = indexData->next;
                index++;
            }

            return indexData->value;
        }

        int getIndex(T val) {
            int index = -1;
            Node *body = head;
            for (int i=0; i<size(); i++) {
                if (body->value == val) {
                    index = i;
                    break;
                }
                else {
                    body = body->next;
                }
            }
            return index;
        }

        void change(int index, T val) {
            Node *body = head;
            for (int i=0; i<index; i++) {
                body = body->next;
            }
            body->value = val;
        }
};

template<typename T>
class doubleLinkedList {
    private:
        struct Node {
            T value;
            Node* next;
            Node* prev;
        };

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

        void insertHead(T val) {
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

        void insertTail(T val) {
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
            if (head != NULL) {
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
        }

        int size() {
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

        void insert(int i, T val) {
            Node* newNode = new Node;
            newNode->value = val;

            unsigned int index = 0;

            if (i == 0)
                insertHead(val);

            else if (i > 0 && i <= size()-1) {
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

            else if (i == size())
                insertTail(val);

            else 
                cout << "Error: Index tidak ditemukan" << endl;
        }

        void remove(int i) {
            unsigned int index = 0;
            
            if (i == 0)
                removeHead();

            else if (i > 0 and i < size()-1) {
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

            else if (i == size()-1)
                removeTail();

            else 
                cout << "Error: Index tidak ditemukan" << endl;
        }

        T getData(int i) {
            unsigned index = 0;
            Node* indexData = head;
            
            while (index != i) {
                indexData = indexData->next;
                index++;
            }

            return indexData->value;
        }

        int getIndex(T val) {
            int index = -1;
            Node *body = head;
            for (int i=0; i<size(); i++) {
                if (body->value == val) {
                    index = i;
                    break;
                }
                else {
                    body = body->next;
                }
            }
            return index;
        }

        void change(int index, T val) {
            Node *body = head;
            for (int i=0; i<index; i++) {
                body = body->next;
            }
            body->value = val;
        }
};