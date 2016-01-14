/*******************************************************************************
Operating System Coursework 2015:
Producer-Consumer Problem

Implementation File: producer.cc
Author: Chris Snowden
Last Modified: 11/12/15

Should be run as ./producer prodID #jobs

Generates and adds jobs to the queue stored in shared memory.  Access to the
queue is protected using semaphores. If the semaphores cannot be found, will
also exit. When all jobs are completed, waits for all processes to complete
before exiting.

If the queue is full but there are no consumers then the producer would wait
indefinitely. Set allowTimeout,timeoutTime and maxWaits to give a timeout. After
each timeout, will print error message to ask for a consumer to be
started. After maxTimeouts, will break from loop.
*******************************************************************************/

# include "helper.h"
# include <cstring>

int getRandn(int low, int high) {

  return rand() % (high-1) + low;

}

int getAJobDuration() {
  
  return getRandn(2,7);

}

int main (int argc, char *argv[])
{
  //Set to allowTimeout to true, to allow the producer to timeout if the queue
  //if full for a long period of time
  bool allowTimeout = true;
  bool hasTimedOut = false;
  int timeouts = 0;
  int maxTimeouts = 3;
  int timeoutTime = 30;

  //Primitive name for stream outputs until arguments checked
  char name[15] = "Producer";

  //Initial process time
  struct timeval t0;
  gettimeofday(&t0, NULL);

  //Seed Random to stop getting the same results
  srand(t0.tv_sec);

  //Parse Arguments
  if(argc != 3) {
    fprintf(stderr,"%s - usage ./producer producerID #jobs\n",name);
    exit(1);
  }
  int prodID = check_arg(argv[1]);
  if(prodID <= 0) {
    fprintf(stderr,"%s - The first argument (%s), the producer ID,"
	    " should be a positive integer\n", name, argv[1]);
    exit(1);
  }  
  int nJobs = check_arg(argv[2]);
  if(nJobs <= 0) {
    fprintf(stderr,"%s - The second argument (%s), the number of jobs to produce,"
	    " should be a positive integer\n",name,argv[2]);

  } else {
    //Add checked producer ID to the process name
    std::strcat(name,"(");
    std::strcat(name,argv[1]);
    std::strcat(name,")");
  }

  //Get semaphores and queue
  int memID = shareMemID(false, name);
  QUEUE* queue = getQueue(memID, name);
  int semID = semaphoreID(false, name);
    
  JOBTYPE job;
  
  //Loop until all jobs produced
  while(nJobs > 0) {

    job.duration = getAJobDuration();
    
    //#Spaces
    int spc = sem_timewait(semID, SPACES, timeoutTime);
    if(spc == -2)
      cannotFindSems(name,t0);
    if(spc == -1) {
      ++timeouts;
      if(allowTimeout && timeouts >= maxTimeouts) {
	fprintf(stderr, "%s time %d: timeout, been waiting for %d\n",
		name, timeSince(t0), timeouts * timeoutTime);
	hasTimedOut = true;
	break;
      }
      fprintf(stderr,"%s time %d: stuck for %ds trying to add to queue,"
	      " ensure that a consumer has been started\n",
	      name, timeSince(t0), timeouts * timeoutTime);
      continue;
    }

    //Mutex
    if(!sem_wait(semID, MUTEX))
      cannotFindSems(name,t0);

    //==Critical Section Begins==

    int qEnd = queue->end;
    job.id = qEnd + 1;
    queue->job[qEnd] = job;
    qEnd = (qEnd + 1) % (queue->size);
    queue->end = qEnd; 

    //==Critical Section Ends==

    //Mutex
    if(!sem_signal(semID, MUTEX))
      cannotFindSems(name,t0);
    //#Items
    if(!sem_signal(semID, ITEMS))
      cannotFindSems(name,t0);
      
    printf("%s time %d: Job id %d duration %d \n"
	   , name, timeSince(t0) , job.id, job.duration);
  
    --nJobs;

    sleep(getRandn(2,4));
  }

  if(!hasTimedOut)
    printf("%s time %d: No more jobs to generate\n"
	   , name, timeSince(t0));
  
  detachFromQueue(queue,name);

  //Wait until all processes have finished
  wait(memID, name);
  
  return 0;
}
