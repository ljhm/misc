// list.cpp
// singly linked list

//
// "This person doesn't understand pointers"
//        Linus
//

#include <cstddef>
#include <iostream>
using namespace std;

struct node
{
    node *next;
    char ch;
};

#define list_print(head)                     \
    do                                       \
    {                                        \
        cout << __LINE__ << ": ";            \
        node *ptr = head;                    \
        while (ptr)                          \
        {                                    \
            cout << " [" << ptr->ch << "] "; \
            ptr = ptr->next;                 \
        }                                    \
        cout << endl;                        \
    } while (0)

void list_create(node **head, const string &str)
{
    node **indirect = head;
    while (*indirect)
    {
        indirect = &(*indirect)->next;
    }

    for (auto ch : str)
    {
        *indirect = new node{NULL, ch};
        list_print(*head);
        indirect = &(*indirect)->next;
    }
}

void list_destroy(node **head)
{
    node **indirect = head;
    while (*indirect)
    {
        node *next = (*indirect)->next;
        delete *indirect;
        *indirect = next;
        list_print(*head);
    }
}

int main()
{
    node *head = NULL;
    list_create(&head, "hello 123");
    list_print(head);
    list_destroy(&head);
    list_print(head);
}

/*
$ make && ./a.out
make: 'a.out' is up to date.
43:  [h]
43:  [h]  [e]
43:  [h]  [e]  [l]
43:  [h]  [e]  [l]  [l]
43:  [h]  [e]  [l]  [l]  [o]
43:  [h]  [e]  [l]  [l]  [o]  [ ]
43:  [h]  [e]  [l]  [l]  [o]  [ ]  [1]
43:  [h]  [e]  [l]  [l]  [o]  [ ]  [1]  [2]
43:  [h]  [e]  [l]  [l]  [o]  [ ]  [1]  [2]  [3]
64:  [h]  [e]  [l]  [l]  [o]  [ ]  [1]  [2]  [3]
56:  [e]  [l]  [l]  [o]  [ ]  [1]  [2]  [3]
56:  [l]  [l]  [o]  [ ]  [1]  [2]  [3]
56:  [l]  [o]  [ ]  [1]  [2]  [3]
56:  [o]  [ ]  [1]  [2]  [3]
56:  [ ]  [1]  [2]  [3]
56:  [1]  [2]  [3]
56:  [2]  [3]
56:  [3]
56:
66:
$
*/
