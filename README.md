# CS401--Computer-Architecture-and-Parallel-Computing
Threads Project  
A thread is a semi-process, that has its own stack, and executes a given piece of code. Unlike a real
process, the thread normally shares its memory with other threads (where as for processes we usually
have a different memory area for each one of them). A Thread Group is a set of threads all executing
inside the same process. They all share the same memory, and thus can access the same global
variables, same heap memory, same set of file descriptors, etc. All these threads execute in parallel
(i.e. using time slices, or if the system has several processors, then really in parallel).
In goal of this assignment is to become familiar with basic thread life-cycle operations. Particularly:
• Creating Threads
• Terminating Thread Execution
• Passing Arguments To Threads
• Thread Identifiers
• Joining Threads
• Detaching / Attaching Threads 
