#ifndef singly_linked_list_h
#define singly_linked_list_h

#include <stdlib.h>
#include <stdio.h>

struct node {
    char data;
    struct node *next;
};

struct node *append(struct node *head, char data) {
    struct node *p1 = head;
    struct node *p2 = malloc(sizeof(*p2));
    p2->data = data;
    p2->next = NULL;
    if (!p1)
        return p2;

    while (p1->next)
        p1 = p1->next;
    p1->next = p2;

    return head;
}

struct node *prepend(struct node *head, char data) {
    struct node *p = malloc(sizeof(*p));
    p->data = data;
    p->next = head;
    return p;
}

struct node *reverse(struct node *head) {
    struct node *prev = NULL;
    struct node *curr = head;

    while (curr) {
        struct node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

void print(struct node *head) {
    while (head) {
        printf("%c ", head->data);
        head = head->next;
    }
    printf("\n");
}

/*
int main() {
    struct node *head = NULL;
    head = append(head, '1');
    head = append(head, '2');
    head = append(head, '3');
    head = append(head, '4');
    head = append(head, '5');
    print(head);
    head = reverse(head);
    print(head);
    return 0;
}

// 1 2 3 4 5
// 5 4 3 2 1
*/

#endif
