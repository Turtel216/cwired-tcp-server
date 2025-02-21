# TCP Server in C

This repository contains a configurable TCP server implemented in C. The project is intended for educational purposes, showcasing how to build a simple, yet flexible, server using C's low-level networking capabilities.

## Features

- **Configurable Port and Address:** Easily customize the server's listening address and port.  
- **Concurrent Connections:** Accepts multiple client connections concurrently using threads.  
- **File Content Retrieval:** Reads and returns the content of the file specified in the client's request.  
- **Lightweight and Efficient:** Built with C's minimal runtime and efficient memory management.  

## Prerequisites

- GCC or Clang compiler  
- CMake
- A working internet connection if you plan to test across networks  

## Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/Turtel216/cwired-tcp-server.git
cd cwired-tcp-server
```

### 2. Build the Project

```bash
mkdir build 
cd build 
cmake ../ 
cmake --build .
```

### 3. Run the Server

The server defaults to `localhost:8080`. You can override these defaults using command-line arguments.

```bash
./cw [host] [port]
```

**Examples:**

```bash
# Run with default settings (localhost:8080)
./cw

# Run on a custom port
./cw 127.0.0.1 9090
```

### 4. Test the Server

You can test the server using tools like `telnet` or `netcat`.

```bash
nc 127.0.0.1 8080
```

Type the file path you wish to retrieve, and the server will return the content of the file if it exists.

## Configuration

The server can be configured by passing arguments at startup. Options include:

- `host`: The IP address to bind the server to (default: `127.0.0.1`).  
- `port`: The port number to listen on (default: `8080`).  
- `max_connections`: Maximum number of simultaneous clients (default: `10`).  

## Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request if you'd like to improve the codebase or documentation.

## License

This project is licensed under the [MIT License](LICENSE).
