*This activity has been created as part of the 42 curriculum by lulauren.*

# Description

This activity teaches us how to use threads in C, as well as how to handle data races that comes with them.
It is a new version of the Philosophers problem.
# Instructions

To run the program, you first need to clone the repo with the url below :

```bash
git clone git@github.com:42learners/Common-Core---Codexion-2bc5c7aa-1d0f-4c02-94ee-5d9f16ff3e12.git
```

Once cloned, with the help of the included makefile, you can build the project with the following makefile rules :

| **Make rules** | **Descriptions**                                                                          |
| -------------- | ----------------------------------------------------------------------------------------- |
| make           | builds the project.                                                                       |
| burnout        | builds the project and executes it with arguments that triggers a burnout.                |
| done           | builds the project and executes it with arguments that runs the simulation to completion. |
| tests          | builds the project and runs a sequence of 100 simulations with one set of arguments.      |
| valgrind       | builds the project and tests it for memory leaks with valgrind.                           |
| helgrind       | builds the project and tests it for data races with helgrind.                             |
| clean          | removes the object files.                                                                 |
| fclean         | removes the object files and the executable for a clean tree.                             |
| re             | runs the makefile rules `fclean` and `make`, for a clean version of the program.          |

You can also run the program manually after having it build with *make* :

```bash
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

For exemple :

```bash
./codexion 4 1000 50 50 50 5 0 edf
```

# Blocking cases handled

- **Deadlock:** even coders grab their *left* dongle first, odd coders grab their *right* one first (`take_both`). Neighbors therefore ask for dongles in a different order, so nobody can end up holding one dongle while waiting forever for the other. If the second dongle is not found, the first one is dropped right away.
- **Starvation:** every dongle keeps a waiting list sorted with a min-heap (by arrival time in `fifo`, or by time left before burnout in `edf`). Only the first waiter in line can take the dongle, even when it looks free, so nobody can cut the line. A cooldown after each drop stops the same coder from grabbing it straight back.
- **Burnout and logs:** the monitor checks every coder every 1 ms, reading `compiles_done` and `last_compile` under the coder's mutex. If a coder takes too long, the monitor sets a shared `stop` flag and every loop stops too. All printing goes through `log_event`, protected by `log_mutex`, so lines never get mixed together.

# Thread synchronization mechanisms

- Every shared thing has its own `pthread_mutex_t`: one per dongle (`status`, `last_release` and the waiter heap), one per coder (`compiles_done`, `last_compile`), plus `log_mutex` and `stop_mutex`. Nobody reads or writes shared data without holding the mutex that owns it — for example, the coder writes and the monitor reads `last_compile` while holding the same `coder->mutex`.
- Coders and the monitor never share locks directly; they talk through protected data. The monitor reads each coder's progress, and it can tell everyone to stop with the `stop` flag, which ends the whole simulation on burnout or completion.
- To get a dongle, a coder unlocks, sleeps 1 ms with `usleep`, and re-locks until it wins or the simulation stops. This simple poll re-checks all three things it might be waiting for (a drop, the cooldown, the stop flag), which a condvar could not do reliably — a waiter blocked only by the cooldown would sleep forever.

# Resources
> [!NOTE]
**No AI was used for this project**

Several links that helped me on this journey :

https://embeddedprep.com/pthreads-tutorial/  
https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2  
https://my-portfolio-lilac-three-li2p7umtsx.vercel.app/work/codexion
https://perso.ens-lyon.fr/francois.schwarzentruber/teaching/l3-prog/book/c_thread.html

My dear friends who also helped me on this project :

- [brouzaud](https://github.com/Bjmrzd)
- [jmangeot](https://github.com/jolyne-mangeot)
- [aupeuget](https://github.com/Audreypgt)
- [adgiraud](https://github.com/adylantes)