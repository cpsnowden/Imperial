/*******************************************************************************
Operating System Coursework 2015:
Producer-Consumer Problem

Implementation File: start.cc
Author: Chris Snowden
Last Modified: 11/12/15

Should be run as ./start queueSize &

Program for setting up semaphores/shared memory before running the Producer and
Consumer. Waits for all the processes to detach from the shared memory, then
cleans up both the memory and the semaphores

ALWAYS RUN THIS IN THE BACKGROUND AS IT WILL CLEAR UP MEMORY FROM PRODUCERS AND
CONSUMERS
*******************************************************************************/

# include "helper.h"
# include <iostream>

//Initialise the queue start, end and size variables
QUEUE* initQueue(int size, int memID, const char* name) {

  QUEUE* queue = getQueue(memID,name);
 
  queue->size = size;
  queue->front = 0;
  queue->end = queue->front;
  return queue;
}

//Clean up if start is interupted
void interuptHandler(int signum)
{
  printf("Signal %d found, cleaning up semaphores and shared memory, \n", signum);
  int semID = sem_attach(SEM_KEY);
  int shmid = shmget(SHM_KEY, SHM_SIZE, 0666);	
  
  if(shmid != -1) {
    printf("Shared memory with ID %d found, attempting to clean\n",shmid);
    if(shmctl(shmid, IPC_RMID, NULL) == -1)
      perror("Could not clean up the shared memory, shmctl:");
  }
  
  if(semID != -1) {
    printf("Semaphore set with ID %d found, attempting to clean\n",semID);
    if(!deleteSem(semID))
      perror("Could not clean up the semaphores");
  }

  exit(1);
}

//Waits for all processes to finish and then cleans up, if timeout is set limit
//set on maximum time allowed to wait
void waitAndClean(int memID, int semID, struct timeval t, const char* name, bool timeout) {
 
  int wait = 0, maxWaits = 100, waitTime = 2, n;
  bool processStarted = false;

  while(true) {
    
    n = numberAttached(memID,name);

    //If shared memory cannot be found, break as it has been cleaned up outside the
    //process
    if(n < 0)
      break;

    //If the number of attached is not zero, then either a producer or consumer
    //has started
    if(n != 0)
      processStarted = true;

    //If no process is attached and a process has been attached in the past
    //break 
    if(processStarted &&  n == 0)
      break;  
    
    //If no process has started and have been waiting for a while, prompt the
    //user 
    if(!processStarted && wait != 0 && wait%(maxWaits / 20) == 0)
      fprintf(stderr,"%s: has been waiting for %ds "
	      "ensure a producer and consumer have been started correctly\n"
	      , name, wait * waitTime);
    
    //If have been waiting too long, timeout
    if(timeout && wait >= maxWaits ) {
      fprintf(stderr,"%s: has been waiting for %ds "
	      ", timed out and clearing up\n"
	      , name, wait * waitTime);
      break;
    }
    
    sleep(waitTime);
    ++wait;
  } 

  //Clean up the shared memory and semaphores
  clean(memID, semID, t, name);

}

/* ALWAYS RUN THIS IN THE BACKGROUND AS WILL CLEAR UP MEMORY FROM PRODUCERS
   AND CONSUMERS */
int main (int argc, char **argv) {

  signal(SIGINT, interuptHandler);
  signal(SIGTERM, interuptHandler);	  
  
  //Process name used in error outputs
  char name[6] = "Start";

  //Initial process time
  struct timeval t0;
  gettimeofday(&t0, NULL);
  
  //Parse arguments
  if(argc != 2) {
    fprintf(stderr,"%s: usage ./start #queueSize\n",name);
    exit(1);
  }
  int queueSize= check_arg(argv[1]);
  if(queueSize <=0 || queueSize > 500 ) {
    fprintf(stderr, "%s: The first argument %s, the queue size,"
	    " should be a positive integer < 501 \n", name ,argv[1]);
    exit(1);	
  } 

  //Setup shared memory and semaphores
  int memID = shareMemID(true,name); 
  QUEUE* queue = initQueue(queueSize, memID,name);
  int semID = semaphoreID(true,name);

  //#Items
  if(sem_init(semID, ITEMS, 0) == -1) {
    fprintf(stderr,"%s: Could not initialise Items semaphore\n",name);
    exit(1);
  }
  //#Spaces
  if(sem_init(semID, SPACES, queueSize) == -1) {
    fprintf(stderr,"%s: Could not initialise Spaces semaphore\n",name);
    exit(1);
  }
  //Mutex
  if(sem_init(semID, MUTEX, 1) == -1) {
    fprintf(stderr,"%s: Could not initialise Mutex semaphore\n",name);
    exit(1);
  }

  detachFromQueue(queue,name);

  waitAndClean(memID, semID, t0, name, true);

  return 0;
}
