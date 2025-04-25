# Book Manager 

## Overview
Book Manager is a simple, terminal-based application written in C that allows users to manage a database of books stored in a `.csv` file.  
Users can add new books or search for existing ones based on the author's name, book title, or publication year.

## Features
- Add new book entries to the database
- Search and retrieve book entries based on:
  - Author
  - Title
  - Publication year
- Validate user input (integers, floats)
- Store and retrieve data from a `.csv` file
- Simple and clean Bash terminal interface

## Project Structure
- **book_manager.c** — Main program source code
- **books.csv** — Sample database file (CSV format)
- **book_manager.exe** — Precompiled executable (optional)

## How to Compile
To compile the program, use the following command in your terminal:

```bash
gcc -o book_manager book_manager.c
