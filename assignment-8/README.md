# LRU Cache Implementation in C (Using HashMap + Doubly Linked List)

This project implements an **LRU (Least Recently Used) Cache** in C using two data structures:

- **HashMap** → Enables O(1) access to nodes  
- **Doubly Linked List (Queue)** → Maintains usage order (MRU → LRU)

The implementation strictly follows the requirement of supporting **O(1) get()** and **O(1) put()** operations.

---

## Overview

The LRU Cache stores key–value pairs and removes the **Least Recently Used** item when capacity is exceeded.

### Operations supported:
- **get(key)** → returns cached value or `NULL`
- **put(key, value)** → inserts/updates value  
  If cache is full → evicts **LRU element**

All operations run in **constant time** using:
- Direct-address HashMap → `Node* map[TABLE_SIZE]`
- Doubly Linked List → to reorder nodes based on usage

---

## Data Structures

### Node (Doubly Linked List)
Each node contains:
```c
typedef struct Node {
    int key;
    char value[20];
    struct Node* prev;
    struct Node* next;
} Node;

### Cache (Hash Map)
Cache contains:
```c
typedef struct Cache {
    int capacity;
    int size;
    Node* head;
    Node* tail;     
    Node* map[TABLE_SIZE];   
} Cache;