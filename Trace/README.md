# Strace

|                              Language                               | Duration |                         Concept                         |                Mark                 |                                                  Author                                                  |
| :-----------------------------------------------------------------: | :------: | :-----------------------------------------------------: | :---------------------------------: | :------------------------------------------------------------------------------------------------------: |
| [![Languages](https://skillicons.dev/icons?i=c)](https://c.org/en/) | 3 Weeks  | Understand debuggers and disassemblers function in UNIX | ![27%](https://progress-bar.dev/27) | [@titi0267](https://github.com/titi0267) <br> [@TristanHourtoulle](https://github.com/TristanHourtoulle) |

### Description

strace traces a prgram in real time and displays all of the system calls it executes in their order of appearance.

### Notation

### Launch

On linux:

- `make` to generate binary.
- `./strace --help` to see usage.

# Ftrace

|                              Language                               | Duration |                         Concept                         |                Mark                 |                                                                            Author                                                                            |
| :-----------------------------------------------------------------: | :------: | :-----------------------------------------------------: | :---------------------------------: | :----------------------------------------------------------------------------------------------------------------------------------------------------------: |
| [![Languages](https://skillicons.dev/icons?i=c)](https://c.org/en/) | 1 month  | Understand debuggers and disassemblers function in UNIX | ![66%](https://progress-bar.dev/66) | [@titi0267](https://github.com/titi0267) <br> [@ludovic-str](https://github.com/ludovic-str) <br> [@TristanHourtoulle](https://github.com/TristanHourtoulle) |

### Description

ftrace allows to list all of the different inputs and outputs of a program’s function.

Therefore, you must list the following:

- system calls
- a program’s internal function calls with their name and address
- signals received from other programs
- function calls contained in the shared libraries (.so)

### Launch

On linux:

- `make` to generate binary.
- `./ftrace --help` to see usage.
