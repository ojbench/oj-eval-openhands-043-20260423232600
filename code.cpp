
#include <iostream>
#include <cstdio>
using namespace std;

namespace LIST
{

struct NODE
{
    int data;
    NODE* prev;
    NODE* next;
};

NODE *head = nullptr, *tail = nullptr;
int len = 0;

void Pre()
{
    // Initialize the list
    head = nullptr;
    tail = nullptr;
    len = 0;
}

NODE* move(int i)
{
    // Move to the i-th node (0-based)
    if (i < 0 || i >= len) return nullptr;
    
    NODE* current;
    // Choose direction based on i
    if (i < len / 2) {
        // Start from head
        current = head;
        for (int j = 0; j < i; j++) {
            current = current->next;
        }
    } else {
        // Start from tail
        current = tail;
        for (int j = len - 1; j > i; j--) {
            current = current->prev;
        }
    }
    return current;
}

void insert(int i, int x)
{
    NODE* new_node = new NODE;
    new_node->data = x;
    new_node->prev = nullptr;
    new_node->next = nullptr;
    
    if (len == 0) {
        // Empty list
        head = new_node;
        tail = new_node;
    } else if (i == 0) {
        // Insert at head
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    } else if (i == len) {
        // Insert at tail
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    } else {
        // Insert in middle
        NODE* current = move(i);
        new_node->next = current;
        new_node->prev = current->prev;
        current->prev->next = new_node;
        current->prev = new_node;
    }
    
    len++;
}

void remove(int i)
{
    if (len == 0 || i < 0 || i >= len) return;
    
    NODE* to_remove;
    
    if (i == 0) {
        // Remove head
        to_remove = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            // List becomes empty
            tail = nullptr;
        }
    } else if (i == len - 1) {
        // Remove tail
        to_remove = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            // List becomes empty
            head = nullptr;
        }
    } else {
        // Remove from middle
        to_remove = move(i);
        to_remove->prev->next = to_remove->next;
        to_remove->next->prev = to_remove->prev;
    }
    
    delete to_remove;
    len--;
}

int Get_length()
{
    return len;
}

int Query(int i)
{
    if (i < 0 || i >= len) return -1;
    
    NODE* current = move(i);
    return current->data;
}

void Print()
{
    if (len == 0) {
        cout << -1 << endl;
        return;
    }
    
    NODE* current = head;
    while (current) {
        cout << current->data;
        if (current->next) {
            cout << " ";
        }
        current = current->next;
    }
    cout << endl;
}

void Clear()
{
    // Delete all nodes
    while (head) {
        NODE* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    len = 0;
}

}
int n;
int main()
{
    cin >> n;
    int op, x, p, ans;
    LIST::Pre();
    for (int _=0;_<n;++_)
    {
        cin >> op;
        switch(op)
        {
            case 0:
                ans = LIST::Get_length();
                cout << ans << endl;
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p,x);
                break;
            case 2:
                cin >> p;
                ans = LIST::Query(p);
                cout << ans << endl;
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                LIST::Print();
                break;
        }
    }
    LIST::Clear();
    return 0;
}
