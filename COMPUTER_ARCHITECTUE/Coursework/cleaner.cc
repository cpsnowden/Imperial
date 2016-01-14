/*******************************************************************************
Operating System Coursework 2015:
Producer-Consumer Problem

Implementation File: cleaner.cc
Author: Chris Snowden
Last Modified: 11/12/15

Cleaner Program to remove semaphores and shared memory with IDs given
in helper.h. 
*******************************************************************************/

# include "helper.h"
# include <iostream>


int main() {
  
  int memID = shareMemID(false,"Cleaner"); 
  int semID = semaphoreID(false,"Cleaner");
  deleteQueue(memID,"Cleaner");  
  deleteSem(semID,"Cleaner");
  return 0;


}
