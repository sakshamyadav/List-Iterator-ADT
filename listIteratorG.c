/* SetG.c ... Generic List Iterator - ADT implementation
   Written by Saksham Yadav, August-September 2017 
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorG.h"

/*
Definition of a 'Node' in the iterator
*/
typedef struct Node {

 	void *value; 
  	struct Node *next; 
	struct Node *prev; 

} Node;
/*
Definition of an iterator, including pointers to important nodes
*/
typedef struct IteratorGRep {

	Node *current;  
	Node *head;
	Node *tail; 
	Node *set_delete; 
	int nitems;

 	ElmCompareFp  cmpElm;
	ElmNewFp  newElm; 
	ElmFreeFp  freeElm;

} IteratorGRep;

//variable to check whether condition for set/delete functions have been met
int delete_set_condition = 0;

/*
----------Local functions--------
*/

//Create a new empty list iterator 
IteratorG IteratorGNew(ElmCompareFp cmp, ElmNewFp new, ElmFreeFp free){

	IteratorG newIt; 

	newIt = malloc(sizeof(struct IteratorGRep));
	
	newIt->current = NULL;
	newIt->head = NULL;
	newIt->tail = NULL;
	newIt->set_delete = NULL; 
	newIt->nitems = 0;

	newIt->cmpElm = cmp; 
	newIt->newElm = new; 
	newIt->freeElm = free;

	return newIt; 

}

//Add values to the iterator 
int add(IteratorG it, void *vp){

	Node *new; 

	if ((new = malloc(sizeof(Node))) == NULL) { 
		return 0; 
	}

	int success = 0; 

	new->value = it->newElm(vp);

	if(it->head == NULL && it->tail == NULL){
		it->head = new;
		it->tail = new; 
		new->next = new->prev = NULL; 
		it->current = NULL; 
		it->nitems++;
		success = 1;
	}
	else if(it->current == NULL){
		it->tail->next = new;
		new->prev = it->tail;
		it->tail = new;
		new->next = NULL;
		it->nitems++;
		success = 1; 
	}
	else if(it->current == it->head){
		it->head->prev = new; 
		new->next = it->head;
		new->prev = NULL;
		it->head = new;
		it->nitems++;
		success = 1;
	}
	else{
		new->next = it->current; 
		new->prev = it->current->prev; 
		new->prev->next = new; 
		new->next->prev = new; 
		it->nitems++;
		success = 1; 
	}
	
	return success;
	
}

//Check whether elements exist to the right of the cursor
int hasNext(IteratorG it){

	if(it->current != NULL){
		return 1;
	}
	else{
		return 0;
	}
}

//Check whether elements exist to the left of the cursor
int hasPrevious(IteratorG it){

	if(it->current != it->head){
		return 1; 
	}
	else{
		return 0; 
	}
}

//Move the cursor one position to the right and return a pointer to the value of the next node 
void *next(IteratorG it){

	Node *cur = it->current; 
	delete_set_condition = 1;

	if(cur == it->head && it->nitems == 1){
		it->current = NULL;
		it->set_delete = cur; 
		return cur->value;
	}
	else if(cur == it->head){
		it->current = it->current->next; 
		it->set_delete = cur; 
		return cur->value; 
	}
	else if(cur == it->tail){
		it->current = NULL; 
		it->set_delete = cur; 
		return cur->value;
	}
	else if(cur != NULL){
		it->current = it->current->next; 
		it->set_delete = cur; 
		return cur->value; 
	}
	else{
		delete_set_condition = 0;
		return NULL;
	}
}

//Move the cursor one position to the left and return a pointer to the value of the previous node 
void *previous(IteratorG it){

	Node *cur = it->current; 
	delete_set_condition = 1;

	if(cur == NULL && it->nitems == 1){
		it->current = it->head; 
		cur = it->head; 
		it->set_delete = cur; 
		return cur->value; 
	}
	else if(cur == NULL){
		it->current = it->tail; 
		cur = it->current; 
		it->set_delete = cur; 
		return cur->value; 
	}
	else if(cur != it->head){
		it->current = it->current->prev; 
		cur = it->current; 
		it->set_delete = cur; 
		return cur->value;
	}
	else{
		delete_set_condition = 0;
		return NULL;
	}
	
}

/*
Search all elements to the right of the cursor to find a particular value. 
If found, return a pointer to the value of the node and advance the cursor to the right of the node
*/
void *findNext(IteratorG it, void *vp){

	Node *checker = it->current; 
	Node *cur = it->current;
	delete_set_condition = 1;
	int found = 0; 

	if(hasNext(it)){
		while(checker->next != NULL){
			if(it->cmpElm(checker->value, vp)==0){
				found = 1;
			}
			checker = checker->next;
		}
		if(it->cmpElm(checker->value, vp)==0){
			found = 1;
		}

		if(found){
			while(it->cmpElm(cur->value, vp) !=0 ){
				cur = cur->next;
			}
			it->current = cur->next;
			it->set_delete = cur; 
			return cur->value; 
		}

		else{
			delete_set_condition = 0;
			return NULL;
		}
	}
	else{
		delete_set_condition = 0;
		return NULL;
	}
}

/*
Search all elements to the left of the cursor to find a particular value. 
If found, return a pointer to the value of the node and advance the cursor to the left of the node
*/
void *findPrevious(IteratorG it, void *vp){

	Node *checker = it->current; 
	Node *cur = it->current; 
	delete_set_condition = 1;
	int found = 0; 

	if(hasPrevious(it)){
		if(it->current == NULL){
			checker = it->tail; 
			cur = it->tail;
		}
		else{
			checker = checker->prev;
			cur = cur->prev;
		}
		while(checker->prev != NULL){
			if(it->cmpElm(checker->value, vp)==0){
				found = 1; 
			}
			checker = checker->prev; 
		}
		if(it->cmpElm(checker->value, vp)==0){
			found = 1;
		}

		if(found){
			while(it->cmpElm(cur->value, vp) !=0){
				cur = cur->prev; 
			}
			it->current = cur; 
			it->set_delete = cur; 
			return cur->value;
		}
		else{
			delete_set_condition = 0;
			return NULL;
		}
	}
	else{
		delete_set_condition = 0;
		return NULL;
	}
}

//Delete an element from the iterator. 
int delete(IteratorG it){

	Node *temp = it->set_delete; 

	if(delete_set_condition){
		if(it->nitems == 1){
			it->set_delete = NULL;
			it->head = NULL;
			it->tail = NULL;
			it->current = NULL;
			it->freeElm(temp->value);
			free(temp);
		}
		else if(it->set_delete == it->head){
			temp->next->prev = NULL;
			it->head = temp->next; 
			it->current = it->head;
			it->freeElm(temp->value);
			free(temp);
		}
		else if(it->set_delete == it->tail){
			temp->prev->next = NULL;
			it->tail = temp->prev; 
			it->current = NULL; 
			it->freeElm(temp->value);
			free(temp);
		}
		else{
			temp->next->prev = temp->prev; 
			temp->prev->next = temp->next; 
			it->current = temp->next; 
			it->freeElm(temp->value);
			free(temp);
		}
		delete_set_condition = 0;
		it->nitems--;
		return 1;
	}
	else{
		return 0; 
	}
}

//Update the value of the current node 
int set(IteratorG it, void *vp){

	if(delete_set_condition){
		it->set_delete->value = it->newElm(vp);
		delete_set_condition = 0;
		return 1; 
	}
	else{
		return 0;
	}
}

//Move the cursor to the start of the list 
void reset(IteratorG it){

	it->current = it->head;
}

//Delete all nodes in the iterator, followed by the iterator itself 
void freeIt(IteratorG it){
	
	it->nitems = 0;

	struct Node *cur;
	struct Node *temp;


	for(cur = it->head; cur != NULL; cur = temp){
		temp = cur->next; 
		it->freeElm(cur->value);
		free(cur);
	}

	it->current = NULL;
	it->head = NULL;
	it->set_delete = NULL;
	it->tail = NULL;

	free(it);
	
}





void printstuff(IteratorG it){
  
if(it->head == NULL){
  printf(" ^ ");
}
else{
  Node *cur = it->head; 

  int this;



  while(cur->next != NULL){
      this = *(int * ) cur->value;
      if(cur == it->current){
        printf(" ^ ");
      }
    
      printf("%d ", this);
      
      cur = cur->next; 
    }
    if(cur == it->current){
      printf(" ^ ");
    }
    this = *(int *) cur->value; 
    printf("%d ", this);
    if(it->current == NULL){
      printf(" ^ ");
    }
}
}


// 25 34 

