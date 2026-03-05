*This project has been created as part of the 42 curriculum by caide-so.*

# Philosophers

> *I never thought philosophy would be so deadly*

---

## Description

**Philosophers** is a classic concurrency problem — the [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) — implemented in C as part of the 42 school curriculum.

One or more philosophers sit at a round table with a large bowl of spaghetti in the center. Each philosopher alternates between three states: **eating**, **sleeping**, and **thinking**. There is one fork between each pair of adjacent philosophers, meaning a philosopher must acquire both their left and right fork before they can eat.

The simulation ends when either a philosopher dies of starvation, or — if a meal limit is provided — all philosophers have eaten the required number of times.

The goal of this project is to explore **threading**, **mutual exclusion**, and **synchronization** concepts in C:

- **Mandatory part** (`philo/`): Each philosopher is a **thread**, and each fork is protected by a **mutex**.
- **Bonus part** (`philo_bonus/`): Each philosopher is a **process**, and forks are represented by a **semaphore** shared across processes.

---

## Instructions

### Requirements

- A Unix-based OS (Linux or macOS)
- `cc` compiler
- `make`

### Compilation

**Mandatory part:**
```bash
cd philo
make
```

**Bonus part:**
```bash
cd philo_bonus
make
```

To remove object files:
```bash
make clean
```

To remove object files and the binary:
```bash
make fclean
```

To recompile from scratch:
```bash
make re
```

### Execution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` | Time (ms) before a philosopher dies without eating |
| `time_to_eat` | Time (ms) a philosopher takes to eat |
| `time_to_sleep` | Time (ms) a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | *(Optional)* Simulation stops when all philosophers reach this meal count |

### Usage Examples

```bash
# 5 philosophers, none should die
./philo 5 800 200 200

# 4 philosophers, each must eat 7 times
./philo 4 410 200 200 7

# 1 philosopher — will die (only one fork available)
./philo 1 800 200 200
```

### Expected Output

Each state change is logged in the following format:

```
timestamp_in_ms philosopher_id action
```

For example:
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
...
```

---

## Technical Notes

### Deadlock Prevention

To prevent deadlocks, philosophers are staggered based on their ID parity:
- **Odd-numbered** philosophers pick up their right fork first.
- **Even-numbered** philosophers pick up their left fork first and are briefly delayed with `usleep`.

### Death Detection

- In the **mandatory** version, the main thread acts as a monitor, polling each philosopher's `last_meal_time` and flagging `simulation_ended` if starvation is detected.
- In the **bonus** version, each process self-monitors via the `look_up()` function, checking its own `death_time` timestamp after each action and calling `exit(EXIT_FAILURE)` if it has starved.

### Thread Safety

- All shared state (meal counters, last meal time, simulation flag) is protected by mutexes in the mandatory part.
- Log output is serialized through a dedicated `write_mutex` / `write` semaphore to prevent interleaved messages.

---

## Resources

### Core Reading

- [Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming — Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/)
- [pthread_mutex_lock man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [sem_overview — POSIX semaphores](https://man7.org/linux/man-pages/man7/sem_overview.7.html)
- [gettimeofday man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)

### Tutorials & Articles

- [Unix Threads in C — CodeVault (YouTube playlist)](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
- [Mutex vs Semaphore — GeeksforGeeks](https://www.geeksforgeeks.org/mutex-vs-semaphore/)
- [Understanding Data Races](https://en.wikipedia.org/wiki/Race_condition)

### Debugging Tools

- `valgrind --tool=helgrind` — detects data races in threaded programs
- `valgrind --leak-check=full` — checks for memory leaks

### AI Usage

**Claude (Anthropic)** was used as a supporting tool during this project in the following ways:

- **Generating this README**: The structure, content, and formatting of this file were drafted with AI assistance and reviewed for accuracy.
- **Clarifying concepts**: AI was used to explain threading concepts (mutexes, semaphores, race conditions) and cross-check understanding — not to replace it.
- **Code review assistance**: AI was consulted to review logic in the monitor and death-detection functions, with all suggestions manually evaluated and tested before use.

All code was written, understood, and is fully explainable by the author.
