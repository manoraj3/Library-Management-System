# 📚 Library Management System (C)

A console-based **Library Management System** written in C that manages a full book catalog and lending workflow using singly linked lists. Supports adding, editing, searching, and sorting books, issuing and returning them to users, computing late fines, and exporting the catalog to file — all from a clean, menu-driven CLI.

---

## Overview

This project models a real-world library workflow in portable C. Two parallel singly linked lists — one for books (`struct book`) and one for issue records (`struct issue`) — are managed in memory for the duration of the session. On issuing a book, the system records the borrower, auto-computes the issue date and a 7-day due date using `time.h`, and decrements stock. On return, stock is restored and any late fine (₹2 per day) is calculated automatically.

---

## Features

| # | Feature | Details |
|---|---------|---------|
| 1 | **Add Book** | Add one or more books with auto-incrementing ID, title, author, and quantity |
| 2 | **Delete Book** | Remove by Book ID or title; shows a preview and asks for confirmation |
| 3 | **View All Books** | Displays the full catalog in a formatted ASCII table |
| 4 | **Edit Book** | Modify title, author, or quantity — search by ID or title |
| 5 | **Issue Book** | Issue to a named user; auto-records issue date and 7-day due date; decrements stock |
| 6 | **Return Book** | Matches by Book ID + User ID; marks returned; restores stock; calculates late fine |
| 7 | **List Issued Books** | Shows all issue records (active and returned) with dates and status |
| 8 | **Search** | Case-insensitive search by Book ID, Title, or Author |
| 9 | **Sort** | Display-sort by Title (A–Z) or Quantity (high → low) |
| 10 | **Save to File** | Exports the current book catalog to `library_data.txt` |

---

## Tech Stack

- **Language:** C (C99)
- **Standard Libraries:** `stdio.h`, `stdlib.h`, `string.h`, `time.h`, `unistd.h`
- **POSIX Extensions:** `strings.h` — `strcasecmp`, `strncasecmp` (case-insensitive search and sort)
- **Build:** `gcc` — no external build system or third-party dependencies required

> ⚠️ **Platform Note:** `system("clear")`, `sleep()`, `strcasecmp()`, and `strncasecmp()` are POSIX/Linux-specific. The project compiles and runs correctly on Linux and macOS. Windows users will need WSL, MinGW with POSIX shims, or minor porting changes.

---

## Project Structure

```
.
├── struct.h          # Shared type definitions: struct book, struct issue, extern head pointers
├── main.c            # Entry point — global list heads (bhead, ihead), menu loop, dispatcher
├── add.c             # Add new book records to the linked list
├── del.c             # Delete books by ID or title with confirmation
├── edit.c            # Modify book fields (title / author / qty) by ID or title search
├── view.c            # Display full book catalog
├── print.c           # Shared ASCII table row renderer for books
├── issue.c           # Issue a book: create issue record, decrement qty, compute due date
├── return.c          # Return a book: restore qty, mark returned, compute late fine
├── list_issued.c     # Display all issue records with status (Active / Returned)
├── search.c          # Search by ID, title, or author (case-insensitive)
├── sort.c            # Display-sort by title (A–Z) or quantity (high → low)
└── save.c            # Export book catalog to library_data.txt
```

### Data Structures

```c
/* struct.h */

struct book {
    int   id;           /* auto-incremented unique book ID */
    char  title[50];
    char  author[50];
    int   qty;          /* available stock */
    struct book *next;
};

struct issue {
    int  issue_id;          /* auto-incremented */
    int  book_id;
    int  user_id;
    char user_name[30];
    char issue_date[12];    /* DD-MM-YYYY */
    char due_date[12];      /* issue_date + 7 days */
    char return_date[12];   /* empty until returned */
    int  is_returned;       /* 0 = active, 1 = returned */
    struct issue *next;
};

extern struct book  *bhead;   /* defined in main.c */
extern struct issue *ihead;   /* defined in main.c */
```

---

## Installation

### Prerequisites

- GCC (version 7 or later recommended)
- A POSIX-compatible OS: Linux, macOS, or Windows with WSL/MinGW

### Build

Clone the repository and compile all source files in a single command:

```bash
git clone https://github.com/<your-username>/library-management-c.git
cd library-management-c

gcc main.c add.c del.c edit.c view.c print.c issue.c return.c \
    list_issued.c search.c sort.c save.c -o library
```

Run:

```bash
./library
```

---

## Usage Guide

On launch you will see the main menu:

```
 ____________________________________
|                                    |
|  **** LIBRARY MANAGEMENT MENU **** |
|____________________________________|
|      |                             |
| A/a  |   Add New Book              |
| D/d  |   Remove a Book             |
| S/s  |   Show All Books            |
| U/u  |   Update Book details       |
| I/i  |   Issue a Book              |
| R/r  |   Return a Book             |
| L/l  |   List Issued Books         |
| T/t  |   Sort Books                |
| F/f  |   Search a Book             |
| V/v  |   Save to File              |
| E/e  |   Exit                      |
|______|_____________________________|
```

Enter the corresponding letter (upper or lower case) to select an option. After each operation, you will be prompted to return to the menu (`y`) or exit (`e`).

### Typical Workflow

```
A  → Add books to the catalog
I  → Issue a book to a user (requires a valid Book ID with qty > 0)
L  → View all active and returned issue records
R  → Return a book (enter Book ID + User ID; fine calculated automatically)
V  → Save the current catalog to library_data.txt
E  → Exit
```

### Late Fine Calculation

The fine rate is **₹2.00 per day** after the due date (7 days from issue date). The return module computes the day difference using `difftime()` over `mktime()`-converted dates and prints a summary:

```
Return Date : 15-07-2025
Due Date    : 10-07-2025
Late by 5 day(s). Fine: Rs. 10.00
```

### Saved Output

`V/v → Save to File` writes the book catalog to **`library_data.txt`** in the current working directory in the same formatted table layout.

---

## Configuration

There are no configuration files. Two parameters can be changed directly in source:

| Parameter | File | Default | Description |
|-----------|------|---------|-------------|
| Loan period | `issue.c` — `ts += 7*86400` | 7 days | Days before a book becomes overdue |
| Late fine rate | `return.c` — `fee = late * 2.0f` | ₹2.00/day | Fine charged per overdue day |

---

## Known Limitations

- **No persistence on startup** — Records exist only for the current session. The saved `library_data.txt` is human-readable but is not reloaded on next launch.
- **ID counters reset on restart** — `book.id` and `issue.issue_id` restart from 1 each session.
- **Sort is display-only** — `T/t Sort` does not reorder the underlying linked list; it performs a bucket-scan display pass.
- **Single-title delete** — When deleting by title, if multiple books share the same title, only one deletion is prompted per call.
- **No multi-user / concurrent access** — Single-threaded, single-session design.

---

## Contributing

Contributions are welcome! Please follow these steps:

1. **Fork** the repository and create a feature branch:
   ```bash
   git checkout -b feature/your-feature-name
   ```
2. **Make your changes.** If fixing a bug, add a comment describing the root cause.
3. **Compile and test** manually with at least Add → Issue → Return → Save.
4. **Open a Pull Request** with a clear description of what changed and why.

### Good First Issues for Contributors

- Add file persistence — load `library_data.txt` on startup using `fscanf`
- Replace `goto`-based retry loops with `while(1)` + `break` for readability
- Guard `print_book()` column padding against titles/authors longer than the column width
- Add a `Makefile` for cleaner, reproducible builds
- Make the fine rate and loan period configurable via `#define` in `struct.h`
- Replace `system("clear")` with the portable ANSI escape sequence `printf("\033[H\033[J")`
- Add a proper `free_all()` cleanup on exit

---

## License

This project is licensed under the terms specified in the `LICENSE` file.  
*(Add your chosen license here — e.g., MIT, GPL-3.0, Apache 2.0)*

---

## Suggested GitHub Metadata

**Repository Description:**
> A console-based Library Management System in C — manages books and lending records using singly linked lists, with issue/return tracking, due dates, late fines, and file export.

**Topics / Tags:**
`c` `linked-list` `cli` `library-management` `data-structures` `console-application` `crud` `posix` `beginner-project` `student-project`

**Short Project Summary:**
> Menu-driven C program for managing a library catalog and lending workflow. Supports adding/editing/deleting books, issuing to users with auto-computed due dates, returning with late fine calculation, case-insensitive search, display-sort, and catalog export — all backed by two in-memory singly linked lists.
