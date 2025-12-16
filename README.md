# Bouncing Ball Terminal Animation

A simple bouncing ball animation rendered in the terminal using C.

## Demo

The ball bounces around a bordered play area, losing 10% of its energy on each collision while being constantly pulled down by gravity.

## Requirements

- GCC compiler
- POSIX-compliant system (Linux, macOS, WSL)
- Terminal with ANSI escape code support

## Building

```bash
make
```

## Running

```bash
./main
```

Press `Ctrl+C` to exit.

## Configuration

You can adjust the physics parameters in `main.c`:

```c
#define COLS 100        // Play area width
#define ROWS 30         // Play area height
#define FPS 24          // Frames per second
#define LOSS 0.10f      // Energy loss per collision (10%)
#define GRAVITY 0.25f   // Gravitational acceleration
```

## Cleaning Up

```bash
make clean
```

This removes all compiled object files and the executable.
