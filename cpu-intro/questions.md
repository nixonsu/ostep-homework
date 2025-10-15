1. CPU util should be 100%, since there is no I/O operations.

2. It will take 11 ticks to complete both processes. It is assumed each IO operation will take 5 ticks. First process kicks off taking 4 ticks to execute 4 instructions. After first process is done, second process will kick off an IO operation which takes 5 ticks to complete. Therefore total time taken is 11 ticks.

```
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
```

3. If swapped, it will take 7 ticks to complete both processes, which is faster than the previous simulation. Once first process is BLOCKED due to I/O initiation, second process can start using the CPU. This shows that switching the order matters as it is a more effective use of resources. We initiate the I/O operation first and while it's blocked, another process can leverage the CPU to complete its instructions, reducing the overall time for both processes to finish.

```
-l 1:0,4:100

Time    PID 1       PID 2
1       RUN:io      READY
2       BLOCKED     RUN:cpu
3       BLOCKED     RUN:cpu
4       BLOCKED     RUN:cpu
5       BLOCKED     RUN:cpu
6       BLOCKED     DONE
7       RUN:io_done DONE
```

4. If SWITCH_ON_END flag is set, the total processing time will take 11 ticks. It takes 2 ticks for CPU to initiate and and finish the I/O operation. I/O operation itself takes 5 ticks. Finally the second process takes the CPU 4 ticks to complete 4 instructions. Total is therefore 11 ticks.

```
Time      PID 1         PID 2     
1         RUN:io        READY
2         BLOCKED       READY
3         BLOCKED       READY
4         BLOCKED       READY
5         BLOCKED       READY
6         BLOCKED       READY
7         RUN:io_done   READY
8         DONE          RUN:cpu
9         DONE          RUN:cpu      
10        DONE          RUN:cpu      
11        DONE          RUN:cpu
```

5. If SWITCH_ON_IO is set, total processing time will take 7 ticks. 1 tick for CPU to initiate first process I/O operation. Then while it is BLOCKED, second process takes CPU and executes 4 instructions within 4 ticks. Finally CPU is switched back to first process after I/O operation finishes (5 ticks), taking an additional tick. Therefore total: 1 + 5 + 1 = 7 ticks.

```
Time      PID 1         PID 2     
1         RUN:io        READY
2         BLOCKED       RUN:cpu
3         BLOCKED       RUN:cpu
4         BLOCKED       RUN:cpu
5         BLOCKED       RUN:cpu
6         BLOCKED       DONE
7         RUN:io_done   DONE
```

6. If IO_RUN_LATER policy is set, this means that when I/O completes, the process that issues it is not run right away, instead whatever was running at the time keeps running. This means that when PID 0 I/O task finishes at 7 ticks, PID1 is run instead, as it was the next thing scheduled. This laeds to the total processing time taking 31 ticks, an inefficient usage of resources as for each CPU bound task (PID 1, 2, 3), CPU could have initiated each I/O bound task in PID 0, before running each one leading to a reduced processing time.

```
Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
  1         RUN:io         READY         READY         READY             1
  2        BLOCKED       RUN:cpu         READY         READY             1             1
  3        BLOCKED       RUN:cpu         READY         READY             1             1
  4        BLOCKED       RUN:cpu         READY         READY             1             1
  5        BLOCKED       RUN:cpu         READY         READY             1             1
  6        BLOCKED       RUN:cpu         READY         READY             1             1
  7*         READY          DONE       RUN:cpu         READY             1
  8          READY          DONE       RUN:cpu         READY             1
  9          READY          DONE       RUN:cpu         READY             1
 10          READY          DONE       RUN:cpu         READY             1
 11          READY          DONE       RUN:cpu         READY             1
 12          READY          DONE          DONE       RUN:cpu             1
 13          READY          DONE          DONE       RUN:cpu             1
 14          READY          DONE          DONE       RUN:cpu             1
 15          READY          DONE          DONE       RUN:cpu             1
 16          READY          DONE          DONE       RUN:cpu             1
 17    RUN:io_done          DONE          DONE          DONE             1
 18         RUN:io          DONE          DONE          DONE             1
 19        BLOCKED          DONE          DONE          DONE                           1
 20        BLOCKED          DONE          DONE          DONE                           1
 21        BLOCKED          DONE          DONE          DONE                           1
 22        BLOCKED          DONE          DONE          DONE                           1
 23        BLOCKED          DONE          DONE          DONE                           1
 24*   RUN:io_done          DONE          DONE          DONE             1
 25         RUN:io          DONE          DONE          DONE             1
 26        BLOCKED          DONE          DONE          DONE                           1
 27        BLOCKED          DONE          DONE          DONE                           1
 28        BLOCKED          DONE          DONE          DONE                           1
 29        BLOCKED          DONE          DONE          DONE                           1
 30        BLOCKED          DONE          DONE          DONE                           1
 31*   RUN:io_done          DONE          DONE          DONE             1
```


7. When run with the IO_RUN_IMMEDIATE policy, it'll take 22 seconds instead. Each time an I/O operation finishes in PID 0, CPU control is taken to initiate the subsequent I/O operation, before being used again in PID 1, 2, 3. The result is an efficient use of resources, ensuring I/O tasks are run concurrently with CPU bound tasks.

```
Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
  1         RUN:io         READY         READY         READY             1
  2        BLOCKED       RUN:cpu         READY         READY             1             1
  3        BLOCKED       RUN:cpu         READY         READY             1             1
  4        BLOCKED       RUN:cpu         READY         READY             1             1
  5        BLOCKED       RUN:cpu         READY         READY             1             1
  6        BLOCKED       RUN:cpu         READY         READY             1             1
  7*   RUN:io_done          DONE         READY         READY             1
  8         RUN:io          DONE         READY         READY             1
  9        BLOCKED          DONE       RUN:cpu         READY             1             1
 10        BLOCKED          DONE       RUN:cpu         READY             1             1
 11        BLOCKED          DONE       RUN:cpu         READY             1             1
 12        BLOCKED          DONE       RUN:cpu         READY             1             1
 13        BLOCKED          DONE       RUN:cpu         READY             1             1
 14*   RUN:io_done          DONE          DONE         READY             1
 15         RUN:io          DONE          DONE         READY             1
 16        BLOCKED          DONE          DONE       RUN:cpu             1             1
 17        BLOCKED          DONE          DONE       RUN:cpu             1             1
 18        BLOCKED          DONE          DONE       RUN:cpu             1             1
 19        BLOCKED          DONE          DONE       RUN:cpu             1             1
 20        BLOCKED          DONE          DONE       RUN:cpu             1             1
 21*   RUN:io_done          DONE          DONE          DONE             1
```

8. It's obeserved that scenarios run with IO_RUN_IMMEDIATE & SWITCH_ON_IO vs. IO_RUN_LATER & SWITCH_ON_IO give the exact same output. Similarly IO_RUN_IMMEDIATE & SWITCH_ON_END vs IO_RUN_LATER & SWITCH_ON_END give the same output. This implies that SWITCH_ON_X policy is what's influencing the results here.

```
> python3 process-run.py -s 1 -l 3:50,3:50 -c -p -I IO_RUN_IMMEDIATE -S SWITCH_ON_IO
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2         RUN:io         READY             1
  3        BLOCKED       RUN:cpu             1             1
  4        BLOCKED       RUN:cpu             1             1
  5        BLOCKED       RUN:cpu             1             1
  6        BLOCKED          DONE                           1
  7        BLOCKED          DONE                           1
  8*   RUN:io_done          DONE             1
  9         RUN:io          DONE             1
 10        BLOCKED          DONE                           1
 11        BLOCKED          DONE                           1
 12        BLOCKED          DONE                           1
 13        BLOCKED          DONE                           1
 14        BLOCKED          DONE                           1
 15*   RUN:io_done          DONE             1

Stats: Total Time 15
Stats: CPU Busy 8 (53.33%)
Stats: IO Busy  10 (66.67%)

> python3 process-run.py -s 1 -l 3:50,3:50 -c -p -I IO_RUN_IMMEDIATE -S SWITCH_ON_END
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2         RUN:io         READY             1
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7        BLOCKED         READY                           1
  8*   RUN:io_done         READY             1
  9         RUN:io         READY             1
 10        BLOCKED         READY                           1
 11        BLOCKED         READY                           1
 12        BLOCKED         READY                           1
 13        BLOCKED         READY                           1
 14        BLOCKED         READY                           1
 15*   RUN:io_done         READY             1
 16           DONE       RUN:cpu             1
 17           DONE       RUN:cpu             1
 18           DONE       RUN:cpu             1

Stats: Total Time 18
Stats: CPU Busy 8 (44.44%)
Stats: IO Busy  10 (55.56%)


> python3 process-run.py -s 1 -l 3:50,3:50 -c -p -I IO_RUN_LATER -S SWITCH_ON_IO
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2         RUN:io         READY             1
  3        BLOCKED       RUN:cpu             1             1
  4        BLOCKED       RUN:cpu             1             1
  5        BLOCKED       RUN:cpu             1             1
  6        BLOCKED          DONE                           1
  7        BLOCKED          DONE                           1
  8*   RUN:io_done          DONE             1
  9         RUN:io          DONE             1
 10        BLOCKED          DONE                           1
 11        BLOCKED          DONE                           1
 12        BLOCKED          DONE                           1
 13        BLOCKED          DONE                           1
 14        BLOCKED          DONE                           1
 15*   RUN:io_done          DONE             1

Stats: Total Time 15
Stats: CPU Busy 8 (53.33%)
Stats: IO Busy  10 (66.67%)

> python3 process-run.py -s 1 -l 3:50,3:50 -c -p -I IO_RUN_LATER -S SWITCH_ON_END
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2         RUN:io         READY             1
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7        BLOCKED         READY                           1
  8*   RUN:io_done         READY             1
  9         RUN:io         READY             1
 10        BLOCKED         READY                           1
 11        BLOCKED         READY                           1
 12        BLOCKED         READY                           1
 13        BLOCKED         READY                           1
 14        BLOCKED         READY                           1
 15*   RUN:io_done         READY             1
 16           DONE       RUN:cpu             1
 17           DONE       RUN:cpu             1
 18           DONE       RUN:cpu             1

Stats: Total Time 18
Stats: CPU Busy 8 (44.44%)
Stats: IO Busy  10 (55.56%)
```
