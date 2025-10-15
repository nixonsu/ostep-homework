1. CPU util should be 100%, since there is no I/O operations.

2. It will take 11 ticks to complete both processes. It is assumed each IO operation will take 5 ticks. First process kicks off taking 4 ticks to execute 4 instructions. After first process is done, second process will kick off an IO operation which takes 5 ticks to complete. Therefore total time taken is 11 ticks.

-l 4:100,1:0

Time    PID 1       PID 2
1       RUN:cpu     READY
2       RUN:cpu     READY
3       RUN:cpu     READY
4       RUN:cpu     READY
5       DONE        RUN:io
6       DONE        BLOCKED
7       DONE        BLOCKED
8       DONE        BLOCKED
9       DONE        BLOCKED
10      DONE        BLOCKED
11      DONE        RUN:io_done


3. If swapped, it will take 7 ticks to complete both processes, which is faster than the previous simulation. Once first process is BLOCKED due to I/O initiation, second process can start using the CPU. This shows that switching the order matters as it is a more effective use of resources. We initiate the I/O operation first and while it's blocked, another process can leverage the CPU to complete its instructions, reducing the overall time for both processes to finish.

-l 1:0,4:100

Time    PID 1       PID 2
1       RUN:io      READY
2       BLOCKED     RUN:cpu
3       BLOCKED     RUN:cpu
4       BLOCKED     RUN:cpu
5       BLOCKED     RUN:cpu
6       BLOCKED     DONE
7       RUN:io_done DONE
