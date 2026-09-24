https://embeddedprep.com/pthreads-tutorial/
# What are threads?

it's like running several tasks at once, threads are mini programs inside a single process that let you multitask.

    - a process has its own memory space
    - a thread shares memory space with other threads in the same process

# What is pthread?

pthread is a library in C/C++ that helps create and manage threads.
functions start with pthread_

## How to create a thread:

```c
#include <stdio.h>
#include <pthread.h>

void*   myThreadFunction(void* arg)
{
    printf("Hello from the new thread!\n");
    return NULL;
}

int main()
{
    pthread_t threadId;
    
    //Create a new thread
    pthread_create(&threadId, NULL, myThreadFunction, NULL);
    
    //Wait for the thread to finish
    pthread_join(threadId, NULL);
    
    printf("Back in main thread.\n");
}
```

### How it works:

 - pthread_create(...) creates a thread and runs myThreadFunction in it.
 - pthread_join(...) waits until the thread finishes.