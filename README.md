# Philosophers Project

## Description

The Philosophers project at 42Malaga is an assignment that challenges students to implement a solution to the dining philosophers problem—a classic problem in concurrent programming. The project aims to reinforce knowledge of multithreading, synchronization mechanisms, and concurrent programming concepts.

## Key Concepts

- **Dining Philosophers Problem:**
  - The dining philosophers problem illustrates the challenges of resource sharing among multiple threads.

- **Concurrency:**
  - Implement a solution using multiple threads to represent the philosophers.

- **Mutex and Semaphores:**
  - Utilize mutexes or semaphores to ensure exclusive access to shared resources (e.g., forks) and avoid race conditions.

- **Resource Management:**
  - Model the shared resources (forks) and implement logic to prevent deadlock and ensure fair access.

- **Thread Communication:**
  - Implement communication between philosopher threads to coordinate their actions and avoid conflicts.

- **Timing and Deadlock Avoidance:**
  - Incorporate timing mechanisms to simulate the passing of time and avoid potential deadlocks.

## Getting Started

### Prerequisites

Ensure you have the following installed on your system:

- [GCC](https://gcc.gnu.org/)
- [Make](https://www.gnu.org/software/make/)
- ...

### Installation

Clone the repository and compile the Philosophers project.

```bash
git clone https://github.com/yourusername/philosophers.git
cd philosophers
make

# Example command
./philosophers 5 200 200 200
