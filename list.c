// list/list.c
// Implementation for linked list.
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() { 
  list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
}

void list_free(list_t *l) {
  // check if list is empty
  if (l == NULL) {
    return;
  } 
  node_t *currentNode = l -> head;
  node_t *nextNode = NULL;

  // traverse list and free nodes
  while (currentNode != NULL) {
    nextNode = currentNode -> next;
    free(currentNode);
    currentNode = nextNode;
  }

  // free list
  free(l);
  return;
}

void list_print(list_t *l) {
  // check if list is empty
  if (l == NULL) {
    return;
  } 

  // traverse list and print each node
  node_t *currentNode = l -> head;
  while (currentNode != NULL) {
    printf("%d ", currentNode -> value);
    currentNode = currentNode -> next;
  }
   printf("%s\n", "");
  return;
}

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 10024);
  char tbuf[20];

	node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) { 
  // check if list is empty
  if (l == NULL) {
    return 0;
  } 

  // traverse list and count each node
  int count = 0;
  node_t *currentNode = l -> head;
  while (currentNode != NULL) {
    count += 1;
    currentNode = currentNode -> next;
  }
  return count;
}

void list_add_to_back(list_t *l, elem value) {
  // if list is NULL
  if (l == NULL) {
    return;
  } 

  // create new node
  node_t *newNode = (node_t *)malloc(sizeof(node_t));
  if (newNode == NULL) {
    printf("%s", "Memory allocation failure.");
    return;
  }
  newNode -> value = value;
  newNode -> next = NULL;
  // if head is NULL
  if (l -> head == NULL) {
    l -> head = newNode;
    return;
  }
  node_t *currentNode = l -> head; 
  // traverse list to find last node
  while (currentNode -> next != NULL) {
    currentNode = currentNode -> next;
  }
  // add node to end
  currentNode -> next = newNode;
  return;
}

 

void list_add_to_front(list_t *l, elem value) {
  node_t *cur_node = (node_t *) getNode(value);

  /* Insert to front */
  node_t *head = l->head;  // get head of list

  cur_node->next = head;
  l->head = cur_node;
}

node_t * getNode(elem value) {
  node_t *mynode;

  mynode = (node_t *) malloc(sizeof(node_t));
  mynode->value = value;
  mynode->next = NULL;

  return mynode;
}

// assumes index starts at 1
void list_add_at_index(list_t *l, elem value, int index) {
  if (index == 0) return;

  // create new node
  node_t *newNode = (node_t *)malloc(sizeof(node_t));
  if (newNode == NULL) {
    printf("%s", "Memory allocation failure.");
    return;
  }
  newNode -> value = value;
  newNode -> next = NULL;

  if(index == 1){
    newNode ->next = l -> head;
    l -> head = newNode;
    return;
  }

  // set current and next node
  node_t *currentNode = l -> head;

  // traverse and update current until reaching correct spot for insertion
  int i;
  for (i = 1; i < index-1; i ++){
    if(currentNode == NULL){
      free(newNode);
      return;
    }
    if (i == index - 1) break;
    currentNode = currentNode -> next;
  }

  if(currentNode == NULL){
    free(newNode);
    return;
  }

  // Insert new node into list.
  newNode -> next = currentNode -> next;
  currentNode -> next = newNode;
}

elem list_remove_from_back(list_t *l) { 
  // empty list.
  if (l == NULL || l -> head == NULL) {
    return -1;
  } 

  // one node list
  if (l -> head -> next == NULL){
    elem value = l -> head ->value;
    free(l -> head);
    l -> head = NULL;
    return value;
  }

  // Set current node
  node_t *currentNode = l -> head; 
  // traverse list to find second to last node
  while (currentNode -> next -> next != NULL) {
    currentNode = currentNode -> next;
  }

  // Remove last node.
  node_t *nodeToRemove = currentNode -> next;
  elem value = nodeToRemove -> value;
  currentNode -> next = NULL;
  free(nodeToRemove);
  return value;
}

elem list_remove_from_front(list_t *l) { 
  // empty list.
  if (l == NULL || l -> head == NULL) {
    return -1;
  } 

  node_t *removeHead = l->head;  // get head of list
  elem value = removeHead -> value;
  l -> head = removeHead -> next;  
  free(removeHead);
  return value;
}

elem list_remove_at_index(list_t *l, int index) { 
  // empty list.
  if (l == NULL || l -> head == NULL || index <= 0) {
    return -1;
  } 
    
  if(index == 1){
    return list_remove_from_front(l);
  }

  // set current node
  node_t *currentNode = l -> head;
  node_t *prevNode = NULL;


  // traverse and update current until reaching correct spot for deletion
  int i;
  for (i = 1; i < index - 1; i ++){
    // if current node == NULL
    if(currentNode == NULL || currentNode -> next == NULL){
      return -1;
    }
    currentNode = currentNode -> next;
  }

  // Delete node from list.
  node_t *nodeToRemove = currentNode -> next;
  elem value = nodeToRemove -> value;

  currentNode -> next = nodeToRemove -> next;
  free(nodeToRemove);
  return value;
}
bool list_is_in(list_t *l, elem value) {
   // check if list is empty
  if (l == NULL) {
    return false;
  } 

  // traverse list and check for value
  bool isInList = false;
  node_t *currentNode = l -> head;
  while (currentNode != NULL) {
    if (currentNode -> value == value){
      return true;
    }
    currentNode = currentNode -> next;
  }
  return false;
}

elem list_get_elem_at(list_t *l, int index) { 
  // empty list.
  if (l == NULL || l -> head == NULL || index <= 0) {
    return -1; 
  } 
    
  if(index == 1){
    return l -> head -> value;
  }

  // set current node
  node_t *currentNode = l -> head;
  node_t *prevNode = NULL;

  // traverse and update current until reaching correct spot for capture
  int i;
  for (i = 1; i < index - 1; i ++){
    // if current node == NULL
    if(currentNode == NULL || currentNode -> next == NULL){
      return -1;
    }
    currentNode = currentNode -> next;
  }

  // Capture element.
  return currentNode -> next -> value;
 }
int list_get_index_of(list_t *l, elem value) {
  // if number is not in the list
  if (list_is_in(l, value) == false){
    return -1;
  } else {

    // traverse list and evaluate
    node_t *currentNode = l -> head;
    int count = 1;

    while (currentNode != NULL) {
      if (currentNode -> value == value){
        return count;
      }
      currentNode = currentNode -> next;
      count++;
    }
  }

}

