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

