A semaphore is a synchronization primitive used in concurrent programming to control access to a common resource by multiple processes or threads. It's essentially a counter with two fundamental operations: wait (also known as P operation) and signal (also known as V operation).

Semaphores can be broadly categorized into two main types based on their behavior and usage:

<h3>Binary Semaphore:</h3>

A binary semaphore, also known as a mutex (mutual exclusion), is a semaphore that can only take on the values 0 and 1.
It is primarily used for synchronization between two processes or threads to ensure mutual exclusion, meaning that only one process or thread can access a resource at a time.
Binary semaphores are often used to protect critical sections of code where shared resources are accessed, preventing race conditions and ensuring that only one process or thread executes the critical section at any given time.

<h3>Counting Semaphore:</h3>

A counting semaphore is a semaphore that can take on multiple integer values, typically greater than or equal to zero.
It is used to control access to a pool of identical resources where there may be more than one available instance of the resource.
Counting semaphores are useful for scenarios where multiple processes or threads can simultaneously access a shared resource up to a certain limit. Each time a process or thread acquires the semaphore, the semaphore's value decreases, and when released, the value increases.
They are employed in scenarios such as managing a fixed-size resource pool (e.g., a fixed number of database connections) or implementing producer-consumer problems with multiple producers and consumers.

![image](https://github.com/captainprice27/OS-lab-codes/assets/128576227/c1ba0e5a-5d37-4bdd-977a-a8fbd2f4ba28)

![image](https://github.com/captainprice27/OS-lab-codes/assets/128576227/ae85bd1b-560e-42fd-aa5f-9a4b04e8fdee)



<h2>semaphore operations</h2>

**Semaphore Initialization:** Functions/methods for initializing a semaphore with an initial value.

**Semaphore Wait/P (Proberen) Operation:**

**wait() or P()**: This function/method decrements the semaphore's value. If the value becomes negative, the process/thread may be blocked until the semaphore's value becomes positive again.

**Semaphore Signal/V (Verhogen) Operation:**

**signal() or V():** This function/method increments the semaphore's value, potentially unblocking a process/thread that is waiting for a resource.
**Semaphore Destruction/Cleanup:** Functions/methods for releasing the semaphore and freeing associated resources.
