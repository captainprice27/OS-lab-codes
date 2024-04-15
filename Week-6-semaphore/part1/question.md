Let there be a circular queue (holding at most 10 integer items) shared between two independent processes, one executing producer.c (the producer process)  and the other consumer.c (the consumer process). The producer process, in an infinite loop, reads one integer from the user and adds that to the queue. The consumer process, on the other hand, in an infinite loop, "consumes" one integer from the queue.  

![image](https://github.com/captainprice27/OS-lab-codes/assets/128576227/35ef8441-ad1b-471d-8f22-7b1c6761fd30)

Write the program producer.c and consumer.c ensuring the following points.

Producer and consumer processes to be run independently (at 2 different terminals).
Since the circular queue is shared by both producer and consumer processes, there are possibilities for race conditions to occur. Ensure that there is no race condition.
The Producer process cannot add an item if the queue is full and should wait for the consumer process to "consume" one item. This must not be a "busy waiting", that is, the producer process, in that case, should "go" into wait-state.
The Consumer process, on the other hand,  cannot "consume" an item if the queue is empty, and should wait for the producer process to add one item. This too must not be a "busy waiting", that is, the consumer process, in that case, should "go" into wait-state.
Your programs must be user-friendly and well-documented!
