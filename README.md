This project includes two primary components: (1) Jones Family Simulation: A multithreaded simulation of the Jones family's daily activities, demonstrating thread synchronization using custom and standard barriers, and (2) Benchmarking Tool: A program to compare the performance of a custom barrier implementation (my_barrier_t) with the standard pthread barrier implementation (pthread_barrier_t).

The project is organized into the following files:
-my_barrier.h & my_barrier.c: Custom implementation of a barrier synchronization mechanism.
-jones_family.h, jones_family.c, and main_jones_family.c: Code for simulating the activities of the Jones family, including thread synchronization.
-main_benchmark.c: A benchmarking program comparing the execution times of my_barrier_t and pthread_barrier_t.
-results_benchmark.xlsx: Benchmarking results, including execution times for different thread counts (NUMTHREADS) and repetition values (REPEATS). The file also contains average times and their differences.

To compile the project, run the following commands in the terminal:
For the Jones Family Simulation: gcc -Wall -o jones_family_simulation main_jones_family.c jones_family.c my_barrier.c -lpthread
For the Benchmark Program: gcc -Wall -o benchmark main_benchmark.c my_barrier.c -lpthread

To execute the Jones Family Simulation, use the command: ./jones_family_simulation
The program simulates the activities of the Jones family, and the results will be written to a file named results_jones_family.txt.

To execute the Benchmark, use the command: ./benchmark
The program compares the performance of my_barrier_t and pthread_barrier_t. Execution times for the two implementations will be displayed in the console.

Benchmark data is saved in results_benchmark.xlsx, which contains execution times for various numbers of threads (NUMTHREADS) and repetition counts (REPEATS), calculated averages for each barrier implementation, and differences between the average times of the custom and pthread barriers.

Key features of this project include demonstrating synchronization and multithreading using custom barriers, providing a detailed performance comparison between custom and standard synchronization mechanisms, and logging results for further analysis and performance evaluation.
