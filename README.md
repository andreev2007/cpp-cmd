# 🐚 Custom Shell Implementation

A high-performance, POSIX-compliant shell implementation in C++ featuring:

## Features

- **Command Parsing**: Advanced shell command parsing with support for builtins and external executables
- **PATH Resolution**: Intelligent PATH traversal with executable permission validation
- **Built-in Commands**: Native implementation of `echo`, `type`, `exit`
- **External Execution**: Seamless execution of system binaries with full argument passthrough
- **Cross-Platform**: Support for both Windows and Unix-like systems

## Technical Highlights

- Uses C++17 `std::filesystem` for portable directory traversal
- Efficient PATH parsing with `std::stringstream`
- Robust error handling with exception management
- Permission checking using filesystem permissions API

## Building

```bash
g++ -std=c++17 -o shell src/main.cpp
```

## Usage

```bash
./shell
$ echo Hello World
Hello World
$ type echo
echo is a shell builtin
$ type ls
ls is /usr/bin/ls
$ exit
```

## Skills Demonstrated

- C++17 & Modern C++ Programming
- Filesystem API Mastery
- Cross-Platform Development
- Shell Command Processing
- Memory Management & Performance Optimization
