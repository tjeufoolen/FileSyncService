# CPPLS2 Eindopdracht

Elaboration of final assessment for the CPPLS2 module.

## Prerequisites

- CMake >= 3.17
- C++ compiler
- [optional] valgrind (for testing leak detections) 

## Getting Started

1. Clone this project
2. Be sure to add the asio library (version 1.18.x) in the root of the project under `asio-1.18.0`.
3. Open the client & server projects seperatly.
4. Run the server project.
5. Run the client project.
5. Execute commands in the client :tada:

## Client/Server Protocol

| Command syntax               | Server response                                     |
|------------------------------|-----------------------------------------------------|
| `info`                       | Dropbox server 1.0, copyright (c) 2021 Tjeu Foolen. |
| `dir <path>`                 | `F|file1.txt|2020-03-05 23:45:18|34107`             |
|                              | `D|Private|2020-03-05 23:45:18|0`                   |
|                              | `*|my_symlink|2020-03-05 23:45:18|0`                |
|                              | Error: no such directory                            |
| `get <path>`                 | Actual file                                         |
|                              | Error: no such file                                 |
|                              | Error: no permission                                |
| `put <path> <bytes>`         | OK                                                  |
|                              | Error: invalid path                                 |
|                              | Error: no permission                                |
|                              | Error: not enough disk space                        |
| `ren <path> <name>`          | OK                                                  |
|                              | Error: no such file or directory                    |
|                              | Error: no permission                                |
| `del <path>`                 | OK                                                  |
|                              | Error: no such file or directory                    |
|                              | Error: no permission                                |
| `mkdir <parent-path> <name>` | OK                                                  |
|                              | Error: no such directory                            |
|                              | Error: no permission                                |
| `quit`                       |                                                     |


## Authors

- [Tjeu Foolen](https://github.com/tjeufoolen)
