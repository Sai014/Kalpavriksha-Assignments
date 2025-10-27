# Dynamic Inventory Management System

This C program implements a **Dynamic Inventory Management System** for a shop.  
Since the number of products is not known in advance, the program makes extensive use of **dynamic memory allocation** to efficiently manage inventory data.

The system supports core inventory operations including adding, viewing, updating, searching, and deleting products — making it a practical demonstration of pointers, heap memory management, and dynamic data handling in C.

---

## Features

### Product Structure
Each product contains:
- **Product ID** (integer)
- **Product Name** (string)
- **Price** (float)
- **Quantity** (integer)

### Inventory Operations (Menu Driven)
| Option | Operation Description |
|--------|------------------------|
| 1 | Add New Product (uses `realloc()` when expanding storage) |
| 2 | View All Products |
| 3 | Update Quantity of a Product |
| 4 | Search Product by ID |
| 5 | Search Product by Name (partial text match supported) |
| 6 | Search Products by Price Range |
| 7 | Delete a Product by ID |
| 8 | Exit Program (memory is freed before exit) |

---

## Memory Management Concepts Used
| Function | Purpose |
|---------|---------|
| `calloc()` | Allocates initial memory for product list |
| `realloc()` | Expands memory when adding more products |
| `malloc()` | May be used for internal temporary allocation |
| `free()` | Releases allocated memory before program termination |

---

## Input Format
1. Enter initial number of products.
2. Enter details for each product:
   - Product ID
   - Product Name
   - Price
   - Quantity
3. Use the menu to perform desired operations.

---

## Output Format
Product details are displayed as:
Product ID: <id> | Name: <name> | Price: <price> | Quantity: <quantity>

---

## Compile & Run

```bash
gcc assignment-3/inventory.c -o inventory
./inventory
