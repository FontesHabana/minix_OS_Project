#!/bin/sh

# Create necessary directories
mkdir -p bin
mkdir -p results/original
mkdir -p results/new

echo "--- Compiling Test Suite ---"

# Compile the monitor (tester)
cc priority_tester.c -o tester
if [ $? -eq 0 ]; then echo "[OK] Tester compiled"; else echo "[ERROR] Tester failed"; exit 1; fi

# Compile all test programs
cc tests/cpu_bound.c -o bin/cpu_bound
cc tests/io_bound.c -o bin/io_bound
cc tests/mixed_burst.c -o bin/mixed_burst
cc tests/fork_compete.c -o bin/fork_compete
cc tests/disk_io.c -o bin/disk_io

echo "[OK] All test binaries are in /bin folder."
chmod +x tester