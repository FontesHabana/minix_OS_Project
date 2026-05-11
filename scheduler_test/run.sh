#!/bin/sh

# Check if the user provided the mode
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 [original|new]"
    exit 1
fi

MODE=$1

# Validate input
if [ "$MODE" != "original" ] && [ "$MODE" != "new" ]; then
    echo "Error: Argument must be 'original' or 'new'"
    exit 1
fi

echo "--- Running Tests in MODE: $MODE ---"
echo "Results will be saved in results/$MODE/"

# Run each test and redirect output to CSV
echo "Running CPU Bound..."
./tester bin/cpu_bound > results/$MODE/cpu_bound.csv

echo "Running IO Bound..."
./tester bin/io_bound > results/$MODE/io_bound.csv

echo "Running Mixed Burst..."
./tester bin/mixed_burst > results/$MODE/mixed_burst.csv

echo "Running Fork Compete..."
./tester bin/fork_compete > results/$MODE/fork_compete.csv

echo "Running Disk IO..."
./tester bin/disk_io > results/$MODE/disk_io.csv

echo "Running Hybrid Test..."
./tester bin/hybrid_test > results/$MODE/hybrid_test.csv

echo "--- All tests completed for $MODE ---"