/*******************************************************************************
Operating System Coursework 2015:
Producer-Consumer Problem

Header File: helper.h
Author: Chris Snowden
Last Modified: 11/12/15
 
* Header file for the helper functions. This file includes the
* required header files, as well as the structures and the shared
* memory/semaphore values (which are to be changed as needed).

* Added functionality to header files as part of the exercise

*******************************************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/sem.h>
# include <sys/time.h>
# include <math.h>
# include <errno.h>
# include <signal.h>
# include <string.h>

# define SHM_KEY 0x54 // Change this number as needed
# define SHM_W 0200
# define SHM_R 0400
# define SHM_MODE (SHM_R | SHM_W)
# define SHM_SIZE 10000 // Change this number as needed
# define SEM_KEY 0x56 // Change this number as needed
# define ITEMS 0
# define SPACES 1
# define MUTEX 2

union semun {
    int val;               /* used for SETVAL only */
    struct semid_ds *buf;  /* used for IPC_STAT and IPC_SET */
    ushort *array;         /* used for GETALL and SETALL */
};

typedef struct jobtype
{
  int id;
  int duration;
} JOBTYPE;

typedef struct queue 
{
  int size; 
  int front;
  int end;
  JOBTYPE job[500]; // Can assume this to be maximum queue size
} QUEUE;

int check_arg (char *);
int sem_create (key_t, int);
int sem_attach (key_t);
int sem_init (int, int, int);
bool sem_wait (int, short unsigned int); //returns false if the semaphores cannot be found
int sem_timewait (int, short unsigned int, int); //returns -2 if the semaphores cannot be found
bool sem_signal (int, short unsigned int); // returns false if the semaphores cannot be found
int sem_close (int);

//=========================================================

//1 If newMem is unset, returns the memory ID of the existing shared memory,
//terminated process if not found.
//2 If newMem is set creates new shared memoryand returns the ID
int shareMemID(bool newMem, const char* name);

//1 If newSems is unset, returns the semaphore ID of an existing semaphore set,
//terminated process if not found.
//2 If newSems is set creates a semaphore set and returns the ID
int semaphoreID(bool newSems, const char* name);

//Returns a pointer to the queue in the shared memory with ID
QUEUE* getQueue(int ID, const char* name);

//Detach from the queue in shared memory specified by the pointer
void detachFromQueue(QUEUE* shr, const char* name);

//Returns true if the shared memory is cleared otherwise retrun false
bool deleteQueue(int ID, const char* name);

//Returns true if the semaphore is deleted, otherwise return false
bool deleteSem(int ID, const char* name = "Error");

//Returns the number of processes attached to shared memory, return -1 if no
//shared memory found
int numberAttached(int ID, const char* name);

//Calculates the time since t0 in seconds
int timeSince(struct timeval& t0);

//Wait for all the processes attached to the shared memory with memID, 
//there is a min and max time to allow other processes to attach to the memory
//and to ensure that there is no infinite loop:
void wait(int memID, const char* name);

// Clean up the memory and semaphores
void clean(int memID, int semID, struct timeval t, const char* names);

//Exits and prints a message with the calling process' name
void cannotFindSems(const char* name, struct timeval t);
