1. python3 ./fork.py -s 10
                           Process Tree:
                               a

Action: a forks b
                               a
                               |-b
Action: a forks c
                               a
                               |-b
                               |-c
Action: c EXITS
                               a
                               |-b

Action: a forks d
                               a
                               |-b
                               |-d
Action: a forks e
                               a
                               |-b
                               |-d
                               |-e

2. python3 ./fork.py -f 0.1 -a 100

At 10% fork percentage, the final process tree will just contain the initial process. Since there is a high chance of processes exiting on each action, the end result will just be the parent process. 

At 90% fork percentage, the final process tree will have many children since there is a higher chance each next action will be fork. This means the end result will be a bunch of forked processes that haven't exited.

3. python3 ./fork.py -s 8 -t

                           Process Tree:
                               a

Action? a forks b
                               a
                               └── b
Action? b forks c
                               a
                               └── b
                                   └── c
Action? a forks d
                               a
                               ├── b
                               │   └── c
                               └── d
Action? b forks e
                               a
                               ├── b
                               │   ├── c
                               │   └── e
                               └── d
Action? c forks f
                               a
                               ├── b
                               │   ├── c
                               │   │   └── f
                               │   └── e
                               └── d

4. python3 ./fork.py -A a+b,b+c,c+d,c+e,c- -c

Process tree looks like below. Forks d and e become children of the initial parent a after c exits.

                               a
                               ├── b
                               ├── d
                               └── e

python3 ./fork.py -A a+b,b+c,c+d,c+e,c- -R -c

Process tree looks like below. Forks d and e become children of the next parent up, which is b after c exits.


                               a
                               ├── b
                                   ├── d
                                   └── e

An orphaned process is a process which has had it's parent process terminated. The OS will by default reparent the orphaned process to the system special process (init). With the -R flag, all orphaned processes can be reparented to the local parent as shown in the second diagram. This feature is known as the "Subreaper mechanism" in Linux systems, which allow a process to set itself as a subreaper using a prctl(PR_SET_CHILD_SUBREAPER) system call, preventing orphaned processes from being reparented to the special system process (init) and instead being reparented to it.

5. python3 ./fork.py -F

                           Process Tree:
                               a

Action: a forks b
Action: b forks c
Action: a forks d
Action: d forks e
Action: e EXITS

                        Final Process Tree?


                               a
                               |--b
                               |  |-c
                               |--d


6.

                           Process Tree:
                               a

Action? a forks b
Action? b forks d
Action? a forks c
Action? c forks e
Action? c forks f

                        Final Process Tree:
                               a
                               ├── b
                               │   └── d
                               └── c
                                   ├── e
                                   └── f


There are other cases such as:

                        Final Process Tree:
                               a
                               └── d


Where many there could be many possibilities such as:

a forks d

OR

a forks b
b EXITS
a forks c
c EXITS
a forks d

In reality any final process tree could have limitless possibilities prior to it and one cannot tell what exactly has taken place based on just the final process tree.