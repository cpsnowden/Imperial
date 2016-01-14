/*******************************************************************************
Operating System Coursework 2015:
Producer-Consumer Problem

Implementation File: helper.cc
Author: Chris Snowden
Last Modified: 11/12/15
*******************************************************************************/

/******************************************************************
 * The helper file that contains the following helper functions:
 * check_arg - Checks if command line input is a number and returns it
 * sem_create - Create number of sempahores required in a semaphore array
 * sem_attach - Attach semaphore array to the program
 * sem_init - Initialise particular semaphore in semaphore array
 * sem_wait - Waits on a semaphore (akin to down ()) in the semaphore array
 * sem_timewait - Waits on a semaphore for a particular time
 * sem_signal - Signals a semaphore (akin to up ()) in the semaphore array
 * sem_close - Destroy the semaphore array
 ******************************************************************/

# include "helper.h"

int check_arg (char *buffer)
{
  int i, num = 0;
  for (i=0; i < (int) strlen (buffer); i++)
    {
      if ((0+buffer[i]) > 57)
	return -1;
      num += pow (10, strlen (buffer)-i-1) * (buffer[i] - 48);
    }
  return num;
}

int sem_attach (key_t key)
{
  int id;
  if ((id = semget (key, 1,  0)) < 0)
    return -1;
  return id;
}
 
int sem_create (key_t key, int num)
{
  int id;
  if ((id = semget (key, num,  0666 | IPC_CREAT | IPC_EXCL)) < 0)
    return -1;
  return id;
}

int sem_init (int id, int num, int value)
{
  union semun semctl_arg;
  semctl_arg.val = value;
  if (semctl (id, num, SETVAL, semctl_arg) < 0)
    return -1;
  return 0;
}

bool sem_wait (int id, short unsigned int num)
{
  struct sembuf op[] = {
    {num, -1, SEM_UNDO}
  };
  if(semop (id, op, 1) == -1)
    if (errno == EINVAL)  //If the semaphores have been removed
      return false;
  return true;
}

int sem_timewait (int id, short unsigned int num, int tim)
{
  struct timespec ts = {tim, 0};
  struct sembuf op[] = {
    {num, -1, SEM_UNDO}
  };
  if (semtimedop(id, op, 1, &ts ) == -1 ) {
    if (errno == EAGAIN)
      return -1;
    if (errno == EINVAL) //If the semaphores have been removed
      return -2;
  }
  return 0;
}

bool sem_signal (int id, short unsigned int num)
{
  struct sembuf op[] = {
    {num, 1, SEM_UNDO}
  };
  if(semop (id, op, 1) == -1)
    if (errno == EINVAL)
      return false;
  return true;
}

int sem_close (int id)
{
  if (semctl (id, 0, IPC_RMID, 0) < 0)
    return -1;
  return 0;
}

//===============================================

int shareMemID(bool newMem, const char* name) {

  int shmflag = 0666;
  if(newMem)
    shmflag = shmflag | IPC_CREAT;

  int shmid = shmget(SHM_KEY, SHM_SIZE, shmflag);

  if(shmid == -1) {
    if(errno == ENOENT && !newMem)
      fprintf(stderr,"%s: No shared memory found, "
	      "make sure you have run ./start \n", name);
    fprintf(stderr, "%s: shmget: ", name);
    perror("");
    exit(1);
  }

  return shmid;
}

int timeSince(struct timeval& t0) {
  struct timeval t1;
  gettimeofday(&t1, NULL);
  return (t1.tv_sec - t0.tv_sec);
}

int semaphoreID(bool newSems, const char* name) {

  int semID;
  if(newSems)
    semID = sem_create(SEM_KEY, 3);
  else 
    semID = sem_attach(SEM_KEY);
  if(semID == -1) {
    if (!newSems)
      fprintf(stderr,"%s: Could not attach to semaphores,"
	      " make sure you have run ./start \n", name);
    fprintf(stderr, "%s: Attempting to get the semaphores, semget: ", name);
    perror("");
    exit(1);
  }
  
  return semID; 
}

QUEUE* getQueue(int ID, const char* name) {

  QUEUE* queue = (QUEUE*)shmat(ID, (void *)0, 0);
  if((char*) queue == (char*) -1) {
     fprintf(stderr, "%s: Attempting to get the queue, shmat: ", name);
     perror("");
     exit(1);
  }

  return queue ;
}

int numberAttached(int ID, const char* name) {
  
  shmid_ds info;
  if(shmctl(ID, IPC_STAT, &info) < 0) {
    if(errno == EINVAL || errno == EIDRM) {
      return -1;
    } else {
      fprintf(stderr, "%s: Getting number of attached processes, shmtcl", name);
      perror("");      
      exit(1);
    }
  }
  shmatt_t nAttached = info.shm_nattch;
  return nAttached;
}

void wait(int memID, const char* name) {

  int wait = 0;
  int maxWaits = 100;
  int n;

  while(true) {
    
    n = numberAttached(memID,name);
    if(n == 0 || wait >= maxWaits )
      break;    
    if(n < 0)
      break;
    
    sleep(2);
    ++wait;
  } 
}

void clean(int memID, int semID, struct timeval t, const char* name) {
  if(deleteQueue(memID,name))
    printf("%s time %d: Cleaned shared memory \n", name, timeSince(t));
  else
    fprintf(stderr, "%s time %d: Could not clear up shared memory\n", name, timeSince(t));
  if(deleteSem(semID,name))
    printf("%s time %d: Cleaned semaphores\n", name, timeSince(t));
  else
    fprintf(stderr, "%s time %d: Could not clear up semaphores \n", name, timeSince(t));
}

bool deleteSem(int ID, const char* name) {

  if (semctl (ID, 0, IPC_RMID, 0) < 0) {
      fprintf(stderr, "%s: Trying to delete semaphores, semctl: ", name);
      perror("");      
      return false;
  }
  return true;
}

void detachFromQueue(QUEUE* queue, const char* name) {
  
  if(shmdt(queue) == -1) {
    fprintf(stderr, "%s: Detaching from queue, shmdt: ", name);
    perror(""); 
    exit(1);
  } 
}

bool deleteQueue(int ID, const char* name) {

  if(shmctl(ID, IPC_RMID, NULL) == -1) {
      fprintf(stderr, "%s: Trying to delete queue, shmctl: ", name);
      perror("");       
      return false;
    }
  return true; 
}

void cannotFindSems(const char* name, struct timeval t) {
  fprintf(stderr,"%s time %d: cannot find semaphores\n",
	  name, timeSince(t));
      exit(1);
}
