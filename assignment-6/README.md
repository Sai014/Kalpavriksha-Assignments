# Virtual File System (VFS)

## Overview
The **Virtual File System (VFS)** simulates a simplified **in-memory file storage system** built in C.  
It mimics the behavior of a real operating system’s filesystem, including:
- File and directory management  
- Disk block allocation and deallocation  
- Navigation using commands like `cd`, `ls`, and `pwd`  
- Disk usage tracking via a virtual disk

This project demonstrates core OS-level concepts such as:
- Linked list–based memory management  
- Hierarchical directory structure  
- Block-level disk simulation  
- Stable data operations on an in-memory file system  

---

##  Core Features
###  Initialization
- On startup, a virtual disk (`virtualDisk[NUM_BLOCKS][BLOCK_SIZE]`) is created.  
- All free blocks are inserted into a **doubly linked list** of `FreeBlock` nodes.
- The root directory `/` is created and set as the **current working directory (cwd)**.

###  Directory & File Structure
- Each directory or file is represented by a `FileNode`.
- Directories use **circular doubly linked lists** to store their children.
- Files contain an array of `blockPointers[]` representing allocated disk blocks.

###  Free Block Management
- Disk divided into fixed-size blocks (`BLOCK_SIZE = 512 bytes`).
- All blocks are initially free.
- When writing to a file → blocks are removed from the free list (head).
- When deleting a file → blocks are returned to the free list (tail).
- If the disk is full → writing fails with an error message.

###  Navigation
- The `cwd` pointer tracks the current directory.
- `cd` and `cd ..` commands change context appropriately.
- Directories can only be deleted if empty.

---

##  Supported Commands

| Command | Description | Example |
|----------|--------------|----------|
| `mkdir <dir>` | Create a new directory under the current directory | `mkdir docs` |
| `create <file>` | Create a new file under the current directory | `create notes.txt` |
| `write <file> "<data>"` | Write data into a file (allocates disk blocks) | `write notes.txt "Hello world!"` |
| `read <file>` | Read and print file contents | `read notes.txt` |
| `delete <file>` | Delete a file and free its blocks | `delete notes.txt` |
| `rmdir <dir>` | Remove an empty directory | `rmdir docs` |
| `ls` | List all files and directories in the current directory | `ls` |
| `cd <dir>` | Change to a subdirectory | `cd projects` |
| `cd ..` | Move back to the parent directory | `cd ..` |
| `pwd` | Print the current working directory path | `pwd` |
| `df` | Display total, used, and free disk blocks | `df` |
| `exit` | Free memory and exit the program | `exit` |

---
