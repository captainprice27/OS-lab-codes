## Implementation of functions for linked lists to be accessed by multiple threads of a processes

We are aware of linked list data structure which we have been implementing and using since our early days of  programming. Under the present assignment, we shall attempt to build linked lists which can be used (shared) by multiple concurrent threads of a process. We shall try to define functions which can be called from within different threads of a "program" for creation (or selection) of a linked list, adding node(s) to it, deleting its node(s), searching for a particular node in the linked list, etc.

Moreover, at the beginning, assume that every node (struct in C) of the linked list has only one integer data field (obviously other than the fields we need for implementing the linked list). Subsequently, we shall attempt to provide support for generic linked list, that is, where arbitrary data can be kept in a node. Following features are to be implemented for this shared link-list assignment.

1.At a time, multiple linked lists may be present (created and being used). 
2.Try to identify the functions (Interface, API,,...) that we are to implement along with the global variables, if any, we need.
3.Identify the Data Structures needed - for individual linked lists, as well as for the common (to be used for all linked lists) ones, if any.
4.Since multiple tgreads may attempt to modify (add a node, delete a node, etc.) a linked list, race condition may occur. Judicious identification and handling of critical section(s) is of utmost importance. For example, deletion of a node involves the following steps.
    a.Find out the previous node of the node to be deleted. This step does not  involve any modification but takes most of the time.
    b.Modify the previous node which has been identified in the previous step so that it points to the next to next node.
    c.Destroy the node to be deleted.
This is shown in the following figure.  

![image](https://github.com/captainprice27/OS-lab-codes/assets/128576227/6ed17690-1803-4b4f-9242-3d202a6a54f0)


Please note that treating the code for all 3 steps together as a critical section will unnecessarily block all other deserving threads.
5.Propose an efficient scheme for handling critical sections so that race conditions can be avoided, there is no chances for deadlock, and waiting is minimalized.
