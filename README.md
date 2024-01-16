# TCP Ping-Pong

Simple TCP ping-pong game.


## Build

Build the project with `make`.

```bash
$ make
```


## Usage

To run the program, you need to start the server and two clients.

### Server

In one terminal, run the server with `./server <port>`.

Example:

```bash
$ ./server 80000
```

### Client

With the server running, run the client with `./client <host> <port>` in another terminal.

Example:

```bash
$ ./client localhost 80000
```