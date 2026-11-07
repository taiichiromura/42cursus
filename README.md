# 42cursus

My project work from the [42 Tokyo](https://42tokyo.jp/) Common Core — low-level systems programming in **C and C++**, built from scratch with no external libraries and peer-evaluated.

## About 42

42 is a project-based, peer-to-peer engineering school with no lectures and no teachers. The Common Core covers computer fundamentals — memory, processes, sockets, algorithms, graphics, OOP, concurrency, networking — by implementing them from the ground up in C/C++.

## Projects

| Project | Area | What it demonstrates |
|---|---|---|
| `libft` | C / library | Reimplementation of core libc functions (memory, strings, linked lists). The foundation reused across later projects. |
| `ft_printf` | C / library | A variadic `printf` from scratch — format parsing, variable arguments. |
| `get_next_line` | C / I/O | Reading a file line by line with a static buffer — stream handling, memory management. |
| `pipex` | Unix | Reproduces shell pipelines — `fork`/`execve`, `pipe`, `dup2`, file redirection. |
| `minishell` | Unix | A minimal Bash-like shell — lexer/parser (AST), pipes, redirection, env vars, builtins, signal handling. |
| `push_swap` | Algorithms | Sorting with a restricted instruction set, optimized for a minimal number of operations (chunk/radix). |
| `philosophers` | Concurrency | The dining philosophers problem — threads, mutexes, deadlock/starvation avoidance, precise timing. |
| `so_long` | Graphics | A small 2D tile game (MiniLibX) — sprites, map parsing, event handling. |
| `cub3d` | Graphics | A raycasting engine (MiniLibX) — a Wolfenstein-style 3D view from a 2D map, textures, DDA. |
| `webserv` | Networking | An HTTP/1.1 server in C++98 — non-blocking I/O (`poll`), nginx-style config parsing, CGI, static files. |
| `cpp00`–`cpp09` | C++ / OOP | The C++ modules — OOP fundamentals through templates, the STL, exceptions, casts, and memory management. |
| `ft_transcendence` | Full-stack | Capstone single-page web application (group project). |

## Build

Each project is self-contained with its own `Makefile`:

```bash
cd minishell && make && ./minishell
```

## Tech

C · C++98 · Unix system calls · POSIX threads · sockets · MiniLibX · Make
