*This activity has been created as part of the 42 curriculum by lulauren.*

# Description

# Instructions

./codexion 4 1000 50 50 50 5 0 edf -> all done
./codexion 4 100 50 50 50 5 0 edf -> one burnout
./codexion 1 200 500 50 50 5 0 edf -> one coder burnout mid routine
./codexion 7 1000 50 50 50 2 0 edf -> odd table, no deadlock

# Resources

# Blocking cases handled

# Thread synchronization mechanisms

### Lock order and the `dongle → stop` edge

The protection map is: `coder->mutex` guards `last_compile` and
`compiles_done`; each `dongle->mutex` guards its own `status`,
`last_release` and waiter heap; `log_mutex` serializes stdout. Coder
state is touched first and the dongle second, so only one edge —
`coder->mutex → dongle->mutex` — exists, and the two are never held
together (the deadline snapshot in `take_dongle` releases the coder
mutex before locking the dongle).

One deliberate exception: `take_dongle` calls `should_stop` (which
locks `stop_mutex`) while holding `dongle->mutex`, to bail out of the
poll loop as soon as the simulation stops. This adds a
`dongle->mutex → stop_mutex` edge. It is safe because the edge is
one-directional: `stop_mutex` is a leaf lock — nothing ever acquires a
dongle, a coder mutex or the log mutex *while holding* `stop_mutex`, so
a cycle (`dongle → stop → dongle` or similar) cannot form. By
contrast, `log_event` in the success path is called after the dongle
unlock, keeping `log_mutex` out of every dongle critical section.