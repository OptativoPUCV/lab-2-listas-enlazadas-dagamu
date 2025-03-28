#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* L = (List*) malloc(sizeof(List));
    L->head = NULL;
    L->current = NULL;
    L->tail = NULL;
    return L;
}

void * firstList(List * list) {
    if(list->head == NULL)
        return NULL;
    
    void* FirstData = list->head->data;
    list->current = list->head;
    return FirstData;
}

void * nextList(List * list) {
    if(list->head == NULL || list->current == NULL || list->current->next == NULL)
        return NULL;
    
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if(list->head == NULL)
        return NULL;
    
    list->current = list->head;
    while(list->current->next != NULL)
        list->current = list->current->next;
    
    return list->current->data;
}

void * prevList(List * list) {
    if(list->current == NULL || list->head == NULL || list->current->prev == NULL)
        return NULL;
    
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* NewNode = createNode(data);
    NewNode->prev = NULL;
    NewNode->next = list->head;

    if(list->head != NULL)
        list->head->prev = NewNode;
    else
        list->tail = NewNode;
    
    list->head = NewNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list, data);
}

void pushCurrent(List * list, void * data) {
    Node* newNode = createNode(data);
    newNode->prev = list->current;

    list->current->next = newNode;
    newNode->next = list->current->next;

    list->current = newNode;
    list->tail = newNode;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if(list->current == NULL)
        return NULL;
    
    Node* Aux = list->current;
    void* Dato = list->current->data;

    if(Aux->prev != NULL)
        Aux->prev->next = Aux->next;
    else
        list->head = Aux->next;
    
    if(Aux->next != NULL){
        Aux->next->prev = Aux->prev;
        list->current = Aux->next;
    } else {
        list->tail = Aux->prev;
        list->current = NULL;
    }
    
    free(list->current);
    return Dato;
}

void cleanList(List * list) {
    while (list->head != NULL)
        popFront(list);
}