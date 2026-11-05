*This project has been created as part of the 42 curriculum by tmura, shshinod.*

# webserv

## Description

### Purpose

This project implements an HTTP/1.1 server in C++98 based on the behavior of NGINX and the relevant RFC specifications. The server is built around a single non-blocking, event-driven architecture using `epoll`, and its behavior is configured through an NGINX-like configuration file.

### Features

* Handles GET, POST, and DELETE requests according to the semantics of RFC 7230/7231, returning appropriate HTTP status codes (e.g., 200 for success, 4xx/5xx for client/server errors, and 301 for redirects).
* Serves static files, generates directory listings (autoindex), and executes CGI scripts (supporting both GET query strings and POST request bodies) via `fork`/`execve`. Communication with CGI processes is performed through non-blocking pipes registered to the same `epoll` instance as client sockets.
* Supports both `Content-Length`-based request bodies and chunked transfer encoding.
* Supports persistent connections (HTTP/1.1 keep-alive by default), with configurable idle client and CGI execution timeouts.
* Supports multiple virtual hosts and listening ports, location-based method restrictions, custom error pages, redirects, and client body size limits, all configured through a single configuration file.
* Includes simple cookie/session management using `Set-Cookie: session_id=...` and a visit counter.
* Performs graceful shutdown on `SIGINT` and `SIGTERM`.

---

## Instructions

### Build

```bash
make          # Build
make re       # Rebuild from scratch
make clean    # Remove object files
make fclean   # Remove object files and executable

```

### Run

```bash
./webserv <config_file>
```

Example:

```bash
./webserv default.conf
```

A configuration file must be provided when starting the server.

### Shutdown

Press `Ctrl+C` (`SIGINT`) or send `SIGTERM` to gracefully terminate the server. Before exiting, the server cleans up all listening sockets, the `epoll` instance, and any running CGI processes.

---

## Configuration

The configuration file consists of one or more NGINX-style `server { ... }` blocks. Multiple servers can share the same listening port by specifying different `server_name` values, enabling virtual hosting.

| Directive                   | Description                                                         |
| --------------------------- | ------------------------------------------------------------------- |
| `listen <port>;`            | Listening port (1–65535)                                            |
| `server_name <name>;`       | Virtual host name used to distinguish servers sharing the same port |
| `root <path>;`              | Default document root for the server                                |
| `location <path> { ... }`   | Path prefix configuration block (multiple allowed)                  |
| `error_page <code> <path>;` | Custom error page for a specific status code                        |

### Known Limitations

* Comments (`#`) are only recognized **inside** `server {}` and `location {}` blocks. Comments outside these blocks (e.g., between `server` blocks) cause a parsing error because they are treated as unknown tokens.
* Unknown directives, including misspelled ones, are silently ignored instead of producing an error.
* Omitting the trailing `;` after a server-level `error_page` directive causes the following directive to be ignored.
* Status codes specified in `error_page` are not range-checked.
* Repeating the same directive multiple times is allowed; the last occurrence overrides previous ones.

---

## Resources

### References

* RFC 9110 – HTTP Semantics
* RFC 9112 – HTTP/1.1
* RFC 3875 – The Common Gateway Interface (CGI) Version 1.1
* NGINX Official Documentation
* A Linux and Unix System Programming Handbook

### Articles

* Prerequisites for Understanding Web Servers and Building One from Scratch in C++
  https://qiita.com/hayashier/items/73168c08451896914da5

* Understanding NGINX from Scratch
  https://zenn.dev/sonicmoov/articles/2f5e2573c64572

* Processes, Threads, and I/O Multiplexing
  https://zenn.dev/yutaro1031/scraps/19a9a9fa9af38a

* HTTP Server: Everything You Need to Know to Build a Simple HTTP Server from Scratch
  https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa

* Using epoll (Compared with select)
  https://qiita.com/homo_lucens_gorilla_gorilla/items/3a97a0e4952f20e5b0c8

* Reading the NGINX Source Code (Part 1: Startup)
  https://qiita.com/cubicdaiya/items/65d7cb967024958e82d2

* Building an HTTP Server in C++
  https://jun-networks.hatenablog.com/entry/2022/12/05/234522

* Writing an Nginx-like Web Server from Scratch in C++
  https://www.alimnaqvi.com/blog/webserv

---

## Use of AI

For this project, AI assistance (Claude) was used **only for reviewing and refactoring code that had already been fully implemented and functionally completed**. AI was **not** used for the design or implementation of core components such as the HTTP parser, CGI processing, or configuration file parser.
