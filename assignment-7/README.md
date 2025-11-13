# ICC ODI Player Performance Analyzer

This **C program** simulates an internal **ICC data analysis system** that manages and analyzes **ODI player performance statistics** for 10 international cricket teams.  
It uses **Linked Lists, Searching, and Sorting algorithms** to efficiently store, retrieve, and process large player datasets.

The system demonstrates practical applications of **data structures, performance computation, and analytical reporting**, aligning with real-world sports data management.

---

## Features

### 1. **Data Initialization**
- Automatically loads data for **200 players across 10 teams** from the provided header file `Players_data.h`.
- Includes predefined arrays of team names and player attributes.

### 2. **Player & Team Management**
- Add new players to existing teams using team IDs.
- Each player record includes:
  - `PlayerId`, `Name`, `TeamName`, `Role`, `TotalRuns`, `BattingAverage`, `StrikeRate`, `Wickets`, `EconomyRate`, and `PerformanceIndex`.
- Each team maintains:
  - `TeamId`, `TeamName`, `TotalPlayers`, and `AverageBattingStrikeRate`.

### 3. **Performance Index Calculation**
Performance Index is calculated based on player **Role**:

| Role | Formula |
|------|----------|
| **Batsman** | (BattingAverage × StrikeRate) / 100 |
| **Bowler** | (Wickets × 2) + (100 − EconomyRate) |
| **All-Rounder** | ((BattingAverage × StrikeRate) / 100) + (Wickets × 2) |

>  Note: Performance indices are **role-specific** — not directly comparable across roles.

### 4. **Search & Sort Functionalities**
- **O(log n)** team searching using efficient algorithms.
- Sort teams by **average batting strike rate**.
- Sort players within or across teams by **performance index** using role-based filters.

### 5. **Menu-Driven Operations**

==============================================================================

ICC ODI Player Performance Analyzer

1.Add Player to Team

2.Display Players of a Specific Team

3.Display Teams by Average Batting Strike Rate

4.Display Top K Players of a Specific Team by Role

5.Display All Players Across All Teams by Role

6.Exit

==============================================================================

