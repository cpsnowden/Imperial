/*******************************************************************************
Operating System Coursework 2015:
Producer-Consumer Problem

Implementation File: consumer.cc
Author: Chris Snowden
Last Modified: 11/12/15

Retrieves jobs from the queue stored in shared memory and executes them.  Access
to the queue is protected using semaphores. Will wait 10s if the queue remains
empty and then detach from the queue. If the semaphores cannot be found, will
also exit. When all jobs are completed, waits for all processes to complete
before exiting.
*******************************************************************************/

# include "helper.h"
# include <cstring>

void executeJob(jobtype& job) {
 
  if((job.duration > 7) || (job.duration < 2)) {
    perror("Attempting to execute job with invalid duration");
    return;
  }

  sleep(job.duration);
}

int main (int argc, char *argv[])
{
  //Primitive name for stream outputs until arguments checked
  char name[15] = "Consumer";

  //Initial process time
  struct timeval t0;
  gettimeofday(&t0, NULL);

  //Parse Arguments
  if(argc != 2) {
    fprintf(stderr,"%s: usage ./consumer consumerID\n", name);
    exit(1);
  }
  int consID = check_arg(argv[1]);
  if(consID <= 0) {
    fprintf(stderr,"%s: The first argument (%s), the consumer ID,"
	    " should be a positive integer\n", name, argv[1]);
    exit(1);
  } else {
   //Add checked consumer ID to the process name
    std::strcat(name,"(");
    std::strcat(name,argv[1]);
    std::strcat(name,")");
  }

  //Get semaphores and queue
  int memID = shareMemID(false, name); 
  QUEUE* queue = getQueue(memID, name);
  int semID = semaphoreID(false, name);
  
  JOBTYPE job;

  while(true) {
    
    //Wait until there is an item in the queue. If waiting for more than 10s
    //break
    int items = sem_timewait(semID,ITEMS,10);
    if(items == -1)
      break;
    if(items == -2)
      cannotFindSems(name, t0);
    
    //Mutex
    if(!sem_wait(semID,MUTEX))
      cannotFindSems(name,t0);
    
    //Critical Section Begins
    
    int qFront = queue->front;
    job = queue->job[qFront];
    qFront = (qFront + 1) % (queue->size);
    queue->front = qFront;
    //Critical Section Ends

    //Mutex
    if(!sem_signal(semID,MUTEX))
      cannotFindSems(name,t0);

    //#Empty Spaces
    if(!sem_signal(semID,SPACES))
      cannotFindSems(name,t0);

    //Print status
    printf("%s time %d:"
	   " Job id %d executing sleep duration %d \n",
	   name, timeSince(t0), job.id, job.duration);
    
    executeJob(job);  
 
    //Print status
    printf("%s time %d:"
	   " Job id %d completed \n",
	   name, timeSince(t0), job.id);
    
  }

  //Print Status
  printf("%s time %d: No Jobs Left\n",
	 name, timeSince(t0));

  detachFromQueue(queue, name);
  
  //Wait until all processes have finished
  wait(memID, name);

  return 0;
}
