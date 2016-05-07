To Compile:

make clean
make

To run:

sudo ./ipc_bench



-------
Example Output:


Follower began FILES transfer
Leader began FILES transfer
Follower began PIPE transfer
Leader began PIPE transfer
Follower began SHARED_MEMORY transfer
Leader began SHARED_MEMORY transfer

Leader, Average time (microsecs) per send:

FILES          ->    798182
PIPE           ->    366654
SHARED_MEMORY  ->      2961

Follower, Average time (microsecs) per send:

FILES          ->    786136
PIPE           ->    375622
SHARED_MEMORY  ->      2952

---------

The program will print when both of the processes begin a new set of transfers for a given method. After all of the transfers have been completed, the Leader/Follower will print the average time (microseconds) that it took for a single send for each of the three methods. The Follower then does the same.

The time required to send is reported. You can imagine the time it takes for a single cycle by simply doubling the time (i.e. two sends = 1 cycle). All 3 methods perform the "write" function by iterating through all 2^20 integers, and performing a separate write call (PIPE and FILES) or assignment (SHM). I think it would probably be faster to assign of the integers to an array in a loop, and then executing a single write call (PIPE and FILES) or memcpy call (SHM). The overhead associated with the 2^20 write calls may have exaggerated the inferiority (longer run time) of the PIPE and FILES methods.

In the event that the last element of the communication medium does not contain the expected integer value, and error is printed:

Error!!
Expected Last element:	<some number>
Actual Last Element:	<a different number>



------------

Explanation of code layout:

I decided to store most of the code in ipc_bench.c. The leader and follower functions are very similar, so I did not see the need for having a file for each function. Most of the remainder of the code is categorized based on the communication method:


Main functions (including follower/leader): ipc_bench.c, ipc_bench.h

PIPES: 		ipc_pipe.c, ipc_pipe.h
FILE:  		ipc_file.c, ipc_file.h
SHARED MEMORY:	ipc_shm.c,  ipc_shm.h

Semaphore creation:  ipc_sem.c, ipc_sem.h
Misc. Utilities:     ipc_utilities.c, ipc_utilities.h


