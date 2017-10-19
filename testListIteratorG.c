/*
  testListIteratorG.c ... client to test Generic List Iterator 
*/ 

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listIteratorG.h"
#include "positiveIntType.h"
#include "stringType.h" 

#define MAXARRAY 3

int main(int argc, char *argv[])
{
  
  
  /* =======================================
     --------- positiveIntType List Iterator ----------
  */
  
  IteratorG it1 = IteratorGNew(positiveIntCompare, positiveIntNew, positiveIntFree);
  
  int a[MAXARRAY] = {20, 54,34};
  
  int i;
  for(i=0; i<MAXARRAY; i++){
    int result = add(it1 , &a[i]); 
    printf("Inserting %d: %s \n", a[i], (result==1 ? "Success" : "Failed") );
  }
    printstuff(it1);
  printf("\n");

  int item_value = *(int *) previous(it1);

  printf("%d \n", item_value);


  int value; 

  value = 12; 

  add(it1, &value);
    printstuff(it1);
  printf("\n");


  value = 33; 

  add(it1, &value);
    printstuff(it1);
  printf("\n");


  value = 25; 

  add(it1, &value);
    printstuff(it1);
  printf("\n");


  previous(it1);
    printstuff(it1);
  printf("\n");


  previous(it1);
    printstuff(it1);
  printf("\n");


  next(it1);
    printstuff(it1);
  printf("\n");


  delete(it1);
    printstuff(it1);
  printf("\n");


  previous(it1);
    printstuff(it1);
  printf("\n");


  delete(it1);
    printstuff(it1);
  printf("\n");


  previous(it1);
    printstuff(it1);
  printf("\n");


  delete(it1);
    printstuff(it1);
  printf("\n");


  next(it1);
    printstuff(it1);
  printf("\n");


  delete(it1);
    printstuff(it1);
  printf("\n");


  value = 55; 


  add(it1, &value);
    printstuff(it1);
  printf("\n");


  value = 29; 

  add(it1, &value);
    printstuff(it1);
  printf("\n");


  reset(it1);
    printstuff(it1);
  printf("\n");


  next(it1);
    printstuff(it1);
  printf("\n");


  value = 62; 

  add(it1, &value);
    printstuff(it1);
  printf("\n");


  value = 44; 

  add(it1, &value);
    printstuff(it1);
  printf("\n");


  previous(it1);
    printstuff(it1);
  printf("\n");


  next(it1);
    printstuff(it1);
  printf("\n");


  delete(it1);
    printstuff(it1);
  printf("\n");


  previous(it1);
    printstuff(it1);
  printf("\n");


  next(it1);
    printstuff(it1);
  printf("\n");


  delete(it1);
    printstuff(it1);
  printf("\n");


  delete(it1);
    printstuff(it1);
  printf("\n");


  next(it1);
    printstuff(it1);
  printf("\n");


  delete(it1);
    printstuff(it1);
  printf("\n");


  previous(it1);
    printstuff(it1);
  printf("\n");


  delete(it1);


    printstuff(it1);
  printf("\n");

 next(it1);
 delete(it1);
 next(it1);
 delete(it1);
 freeIt(it1);

  printstuff(it1);
printf("\n");





}


