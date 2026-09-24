# CODEXION

## Global rules

- ### No Global variables

- ### Arguments (all mandatory)

  - number_of_coders: nb of coders and dongles.
  - time_to_burnout: in milliseconds, if a coder did not start compiling within this time since the beginning of their last compile or the beginning of the simulation, they burn out.
  - time_to_compile: in milliseconds, the time it takes for a coder to compile. they must hold 2 dongles during that time.
  - time_to_debug: in milliseconds, the time a coder will spend debugging.
  - time_to_refactor: in milliseconds, the time a coder will spend refactoring. after completing the refactor, the coder will immediately attempt to acquire dongles and start compiling.
  - number_of_compiles_required: if all coders have compiled at least this many times the simulation stops, otherwise it stops when a coder burns out.
  - dongle_cooldown: in milliseconds, after being released, a dongle is unavailable until its cooldown has passed.
  - scheduler: the policy used by dongles to decide who gets them when multiple coders request them. must be exactly fifo (first in first out) or edf (earliest deadline first with deadline = last_compile_start + time_to_burnout).

- ### Each coder has a nb from 1 to number_of_coders

- ### Coder nb 1 sits next to coder nb number_of_coders, any other coder nb sits between coder nb N - 1 and coder nb N +1.

- ### About the logs:
  - Any state change of a coder must be formatted as follows:
    - timestamp_in_ms X has taken a dongle
    - timestamp_in_ms X is compiling
    - timestamp_in_ms X is debugging
    - timestamp_in_ms X is refactoring
    - timestamp_in_ms X burned out
  
  - a displayed state message should not be mixed up with another message
  - a message announcing that a coder burned out should be displayed no more than 10 ms after the burnout
  - coders should avoid burning out!

## Arguments 

number_of_coders, time_to_burnout, time_to_compile,
time_to_debug, time_to_refactor, number_of_compiles_required,
dongle_cooldown, scheduler

## External Functions

pthread_create, pthread_join, pthread_mutex_init, pthread_mutex_lock,
pthread_mutex_unlock, pthread_mutex_destroy, pthread_cond_init,
pthread_cond_wait, pthread_cond_timedwait, pthread_cond_signal,
pthread_cond_broadcast, pthread_cond_destroy, gettimeofday, clock_gettime,
usleep, write, malloc, free, printf, fprintf, strcmp,
strlen, atoi, memset

## Description

Coders with threads and mutexes (C)

## Specific rules

- Each coder must be represented by a thread using pthread_create
- There is one dongle for each pair of coders, if there are several coders, each coder should have a dongle to their left and their right. If there is only one coder there should be on one dongle.
- To prevent duplicating dongles, they need to be protected with a mutex, pthread_mutex_t. A condition variable, pthread_cond_t, may be used to manage waiting queues.
- Dongle cooldown is mandatory.
- Fair arbitration is mandatory, when multiple coders request the same dongle, the scheduler must grant access according to the fifo or edf.
- The program should garantee liveness, no coder should be starved of dongles and burn out under edf scheduling, provided the parameters are feasible.
- A seperated monitor thread must detect burnout precisely and stop the simulation.
- Logging must be serialized so that two messages never interleave on a single line, use a mutex to protect output.
- The simulation stop either when a coder burns out or when every coder has compiled