# FCFS-Based OS Process Scheduling Simulator (C)

## 📌 Project Overview
This project implements a **First-Come-First-Serve (FCFS)** based CPU process scheduling simulator in **C**, mimicking the behavior of a simplified operating system scheduler.

The simulator manages processes using a **Process Control Block (PCB)** and schedules them across different states using **queues**. It supports **CPU execution, I/O blocking, I/O completion, and kill events**, while tracking execution time and performance metrics.

---

## 🎯 Objectives
- Simulate FCFS CPU scheduling
- Handle I/O blocking and parallel I/O execution
- Support runtime process termination (KILL events)
- Track execution timeline using a system clock
- Compute turnaround time and waiting time for each process

---

## 🧠 Key Concepts Used
- CPU Burst
- I/O Burst
- Process States (Ready, Running, Waiting, Terminated, Killed)
- Queues (Array-based)
- HashMap-like PID → PCB mapping
- Time-based simulation (tick-driven)

---

## 🏗️ System Architecture

### 1. Process Control Block (PCB)
Each process stores:
- Process name
- PID
- CPU burst time
- I/O start time
- I/O duration
- Execution state and timing details

### 2. Queues
- **Ready Queue**: Processes ready to execute (FCFS order)
- **Waiting Queue**: Processes performing I/O

### 3. Scheduler
- Picks the next process from the Ready Queue
- Executes one CPU tick at a time
- Handles I/O and kill events

### 4. System Clock
- Advances in discrete time units (ticks)
- Drives CPU execution and I/O progression

---

## 📥 Input Format

5
chrome 101 10 4 3
vscode 102 8 3 2
terminal 103 6 2 3
spotify 104 5 0 0
notepad 105 7 5 2
2
102 7
105 10

### Number of Processes
