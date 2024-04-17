## Assignment to implement an interface (a set of functions) at the top of file(s) to maintain files as a collection of blocks.

Assignment to implement an interface (a set of functions) at the top of file(s) to achieve the following!

A file is conceived as collection of n  fixed sized  blocks of s bytes. For example, a file named "dd1" can be conceived as a collection of 2048 (n = 2048) blocks, where each block is of 4096 (s = 4096) bytes.
The n blocks in a file are numbered as 0 through n-1.
The blocks in a file can be in 2 states, namely "free" and "used". Functions to be written for (i) getting a free block and use it, (ii) freeing a used block.
A guideline for implementation of the functions are given below.
Say, the file dd1 is to contain 2048 number of blocks, each of size 4096 Bytes. The file can be conceived as shown in the following figure.

![image](https://github.com/captainprice27/OS-lab-codes/assets/128576227/e6cc6bd7-100e-4158-9d0b-85d7a678dbcf)

Note that the first 1024 Bytes is  kept for storing information like n (total number of blocks), s (size of each block), ubn (number of used blocks), fbn (number of free blocks), ub (a bitmap showing which blocks are used), etc. Please note that,  in ub  there should be  n number of bits, one bit for each block in the file. An 1 (one) in a bit of ub reflects that the corresponding block is in used state. Whereas, a 0 (zero) in a bit of ub reflects that the corresponding block is in free state.

Write a function **"int init_File_dd(const char *fname, int bsize, int bno)"** that creates a file (if it does not exist) called fname of appropriate size (1024 + bsize*bno Bytes) in your folder. The function initializes the first 1024 Byes putting proper values for n, s, ubn, fbn, and ub. If for some reason this functions fails, it returns -1. Otherwise it returns 0.  

Write a function **int get_freeblock(const char *fname)** that reads the 1st 1024 Bytes (containing n, s, ubn, fbn, ub) from the file fname  and finds and returns the block-number of the 1st free block (starting from the 0th bloc) in that file. This function sets the corresponding  bit in ub and fills up the free block with 1's.  ubn and fbn too  are modified appropriately.  On failure this function returns -1. Please  note that all the modifications done by this function have to be written back to the file fname.  

Write a function **"int free_block(const char *fname, int bno)"** that reads the 1st 1024 Bytes (containing n, s, ubn, fbn, ub) from the file fname  and frees the block bno, that is,  resets the bit corresponding to the block bno in ub. This function  fills up the  block bno with 0's.  ubn and fbn too  are modified appropriately.  On success  this function returns 1. It returns 0 otherwise.  Please note that all the modifications done by this function have to be written back to the file fname.   

Write a function **"int check_fs(const char *fname)"** that checks the integrity of the file fname with respect to n, s, ubn, hbn, ub and the contents of the blocks. In case of any inconsistency (say, ubn+fbn ≠  n, ub does not contain ubn number of 1's, etc.), this function returns 1. It returns 0 otherwise.
Write a main function to demonstrate that your functions are working as desired.
