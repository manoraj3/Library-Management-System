# Library Management System (LMS) in C

A **console-based Library Management System** written in C. It manages the full lifecycle of a library's book catalog and lending activity — adding, updating, searching, and removing books; issuing and returning books to/from users; automatic due-date tracking; and fine calculation for late returns. Data is persisted to disk so the catalog and issue history survive between runs.

---

## Features

- 📚 **Book Catalog Management** — add, update, remove, search, and list all books.
- 🔄 **Sort Books** — reorder the catalog (e.g. by title/ID, depending on implementation in `sort_books()`).
- 🧾 **Issue / Return Workflow** — issue a book to a user, automatically stamping the issue date and a due date, and record the return date when it comes back.
- 💰 **Automatic Fine Calculation** — computes a late fee based on how many days overdue a return is.
- 📋 **Issued Books Report** — view all currently/previously issued records in one place.
- 💾 **Persistent Storage** — loads existing data on startup (`load_data()`) and saves it back to disk (`save_data()` / `save_books()`) on exit or on demand.
- ⌨️ **Simple Letter-Driven Menu** — single-keystroke (upper- or lower-case) menu navigation with a "return to menu or exit" prompt after every action.

---

## Menu Reference

The running application presents this main menu (from `main()`):

```
 ____________________________________
|                                    |
|  **** LIBRARY MANAGEMENT MENU **** |
|____________________________________|
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

Each option is triggered by a single case-insensitive letter. After completing an action, the program prompts:

> `Do you want to go back to menu(if yes enter 'y' (or) exit - enter 'e')`

Entering anything other than `y` or `e` re-prompts until valid input is given. Choosing `e` (either at this prompt or from the main menu) automatically saves all data before exiting.

> 📝 **Note:** The original module specification also describes richer submenus (e.g. *Update Book* and *Remove Book* by ID/Name, *Search* by ID/Name/Author — see [Submenus](#submenus-per-specification) below). The current `main()` routes each of these to a single dedicated function (`edit_book()`, `del_book()`, `search_book()`, etc.); any ID/Name/Author sub-selection is expected to happen *inside* those functions.

---

## Data Model

### Book Record

| Field | Description |
|---|---|
| Book ID | Unique identifier for the book |
| Title | Book name |
| Author | Author name |
| Quantity | Number of available copies |

### Issue Record

| Field | Description |
|---|---|
| Issue ID | Unique identifier for the issue transaction |
| Book ID | ID of the book issued |
| User ID | Borrower's ID |
| User Name | Borrower's name |
| Issue Date | Date the book was issued (auto-generated) |
| Due Date | Deadline for return (typically 7 days after issue) |
| Return Date | Actual date the book was returned |
| Fine Amount | Fee charged for a late return |

Both record types are maintained in-memory as **linked lists**, rooted at the global head pointers `bhead` (books) and `ihead` (issue records), with running counters `book_count` and `issue_count` kept in sync with whatever is loaded from disk at startup.

---

## Issue & Return Logic

### Issuing a Book
1. Select the book and the borrowing user.
2. Verify the book has available quantity.
3. Record Book ID, User ID, User Name, and an auto-generated Issue Date.
4. Compute the Due Date (default: **7 days** from the issue date).
5. Decrement the book's available quantity.
6. Persist the new issue record.

### Returning a Book
1. Locate the matching issue record via Book ID + User ID.
2. Stamp the Return Date automatically.
3. Compare Return Date against Due Date.
4. If overdue, calculate the fine:

   ```
   Fine Amount = Number of Late Days × 5   (₹5 per day late)
   ```
5. Update the Fine Amount on the record.
6. Increment the book's available quantity back up.
7. Mark the issue record as returned.

---

## Source File Structure

```
├── main.c        # Entry point — menu loop, dispatches to feature functions
├── struct.h       # Shared struct definitions (book, issue) and function prototypes
├── (bookops.c / issueops.c / io.c, etc.)  # Implementation of add_book(), del_book(),
│                    view_books(), edit_book(), issue_book(), return_book(),
│                    list_issued(), sort_books(), search_book(), save_books(),
│                    load_data(), save_data() — file names depend on your project layout
```

> The excerpt available in this repository shows `main()` and its dispatch logic; the bodies of the individual feature functions (`add_book`, `issue_book`, fine calculation, file I/O, etc.) live in the rest of the source tree / `struct.h`.

### Key Functions Referenced by `main()`

| Function | Menu Key | Purpose |
|---|---|---|
| `add_book()` | A/a | Add a new book to the catalog |
| `del_book()` | D/d | Remove a book record |
| `view_books()` | S/s | Display all books |
| `edit_book()` | U/u | Update an existing book's details |
| `issue_book()` | I/i | Issue a book to a user |
| `return_book()` | R/r | Process a book return and fine calculation |
| `list_issued()` | L/l | List all issued book records |
| `sort_books()` | T/t | Sort the book catalog |
| `search_book()` | F/f | Search for a book |
| `save_books()` | V/v | Save current book data to file |
| `load_data()` | *(startup)* | Load persisted books/issues from disk |
| `save_data()` | *(exit)* | Persist all books/issues to disk on exit |

---

## Build Instructions

This is a standard C console application (no external dependencies beyond the C standard library and `unistd.h` for `system("clear")`, which assumes a POSIX-like terminal — see notes below).

```bash
gcc main.c -o lms
./lms
```

If your implementation is split across multiple `.c` files (e.g. `bookops.c`, `issueops.c`), compile them together:

```bash
gcc main.c bookops.c issueops.c -o lms
./lms
```

---

## Known Issues / Notes

- **`system("clear")` is POSIX/Linux/macOS-specific.** On Windows, replace with `system("cls")` or guard it with a preprocessor check (`#ifdef _WIN32`) for cross-platform compatibility.
- **`goto`-based control flow** (`menu:`, `label:`, `cases:`) works but can be replaced with a `do...while` loop for improved readability and maintainability.
- **No admin/login authentication** — anyone running the binary has full access to all operations, as noted in the specification's improvement suggestions.
- **Single fixed fine rate (₹5/day)** — the specification suggests differentiated rates (e.g. ₹10/day for reference books), which isn't yet reflected in the fine formula shown.
- **Input validation** — ensure `scanf(" %c", &ch)` and any numeric/date entry elsewhere in the codebase properly reject invalid input (e.g. negative quantities, malformed IDs) to avoid corrupt records.
- **Date handling** — confirm issue/due/return dates are generated using real date/time functions (e.g. `time.h`) rather than manual entry, to avoid invalid or inconsistent dates.

---

## Suggested Enhancements (from the Module Specification)

1. **Improve data structures** — ensure consistent use of `struct` for books/issues (already reflected via linked lists here) and consider whether arrays vs. linked lists better suit your performance needs.
2. **Add an admin login system** (username & password) to restrict access.
3. **Improve date handling** — use real date functions and validate date entries.
4. **Better search** — support partial and case-insensitive matching.
5. **Tiered fine rules** — e.g. ₹5/day for normal books, ₹10/day for reference books.
6. **Reporting** — most-issued books, overdue books list, total fines collected.
7. **Separate data files** — split storage into distinct files for books, users, and issue records to reduce risk of data loss/corruption.
8. **Stronger input validation** — reject negative quantities, invalid IDs, and other malformed input with clear error handling.
9. **Polish the UI/UX** — clearer menus and success/failure messaging.

---

## License

Add your preferred license here (e.g. MIT, GPL-3.0).

## Author

Add author/maintainer details here.
