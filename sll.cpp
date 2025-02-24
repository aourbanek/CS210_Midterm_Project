#include <iostream>
using namespace std;

template<typename T>
struct Node
{
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
};

template<typename T>
class SinglyLinkedList
{
    Node<T>* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    void append(T data)
    {
        Node<T>* newNode = new Node<T>(data);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node<T>* temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    void printList()
    {
        Node<T>* temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }
};