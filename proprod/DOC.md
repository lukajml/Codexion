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

- ### 