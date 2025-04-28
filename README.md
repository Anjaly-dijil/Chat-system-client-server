# Chat System - Client Server Application (C++)

This project is a simple client-server chat system using Winsock on Windows. Designed for learning purposes — basic error handling and simple user interactions.

## Features
- Client registration
- Chat request/response between clients
- Server maintains active client list
- Multithreaded client handling

## How to Build

1. Open Terminal (or Command Prompt).
2. Compile the server:
    ```bash
    g++ mainServer.cpp S_connectionHandler.cpp S_clientRegistry.cpp S_requestProcessor.cpp -o server.exe -lws2_32
    ```
3. Compile the client:
    ```bash
    g++ mainClient.cpp C_connectionManager.cpp C_registrationModule.cpp -o client.exe -lws2_32
    ```

## How to Run

1. First, **start the server**:
    ```bash
    ./server.exe
    ```
2. Then, in a new terminal window, **start the client**:
    ```bash
    ./client.exe
    ```

## Technologies
- C++
- Winsock2
- Multithreading
- Basic Networking Concepts (Socket Programming)

## Example

- Client connects and registers username.
- Client sends a chat request to another username.
- If recipient responds `ok`, chat starts.
- If `notnow`, chat request is declined.

## Notes
- This project currently runs on **Windows** only (because it uses Winsock2).
