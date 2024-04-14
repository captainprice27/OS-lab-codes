Shared memory is a feature of an operating system that allows multiple programs to access memory simultaneously, which allows for communication between them or avoids redundant copies. Shared memory is an efficient way to pass data between programs, and it reduces memory usage and disk I/O. 

Shared memory is the fastest inter-process communication mechanism. The operating system maps a memory segment in the address space of several processes to read and write in that memory segment without calling operating system functions. -- javatpoint

Functions of IPC Using Shared Memory
Two functions shmget() and shmat() are used for IPC using shared memory. shmget() function is used to create the shared memory segment, while the shmat() function is used to attach the shared segment with the process's address space.

1. shmget() Function


The first parameter specifies the unique number (called key) identifying the shared segment. The second parameter is the size of the shared segment, e.g., 1024 bytes or 2048 bytes. The third parameter specifies the permissions on the shared segment. On success, the shmget() function returns a valid identifier, while on failure, it returns -1.

Syntax
```
#include <sys/ipc.h>   
#include <sys/shm.h>   
int shmget (key_t key, size_t size, int shmflg);
```

2. shmat() Function

shmat() function is used to attach the created shared memory segment associated with the shared memory identifier specified by shmid to the calling process's address space. The first parameter here is the identifier which the shmget() function returns on success. The second parameter is the address where to attach it to the calling process. A NULL value of the second parameter means that the system will automatically choose a suitable address. The third parameter is '0' if the second parameter is NULL. Otherwise, the value is specified by SHM_RND.

Syntax
```
#include <sys/types.h>  
#include <sys/shm.h>  
void *shmat(int shmid, const void *shmaddr, int shmflg);
```
