# Student Record Management System

A C++ command-line application for managing student records, subjects, templates, and can exports data to CSV

## Features

- Add, open, modify, and delete student records
- Auto-assign student ID and roll number
- Track student details (name, DOB, gender, course, section, fee, contact, address)
- Manage subject data (name, code, marks, credits)
- Create and manage reusable subject templates
- View recent records, all records, and records by roll number
- Export all records or course-wise records to CSV

## Project Structure

- `source/` - Source files
- `headers/` - header files
- `files/` - binary/session data storage
- `templates/` - stored subject templates
- `export/` - generated CSV output
- `ARCHITECTURE.md` - notes about the fucntions and structure 
- `NOTES.md` - development notes/issues

## Compile And Run

```
g++ source/*.cpp -I headers/ -I run ; ./run  

```

The program open a menu where you can :

```
┌──────┬──────────────────────────────────────────────┐
|  1   │  Show Recent Records                         │
│  2   │  Show All Records                            │
│  3   │  Show All Records Subject Details            │
│  4   │  Show Records by Roll No                     │
│  5   │  Show Records Subject Details by Roll No     │
│  6   │  Show Status                                 │
├──────┼──────────────────────────────────────────────┤
│  7   │  Show Templates                              │
│  8   │  Show Template Data                          │
│  9   │  Add Template                                │
│  10  │  Delete Template                             │
│  11  │  Modify Template                             │
├──────┼──────────────────────────────────────────────┤
│  12  │  Delete Record                               │
│  13  │  Export All Records                          │
│  14  │  Export Records by Course                    │
│  15  │  Add Record                                  │
│  16  │  Open Record                                 │
├──────┼──────────────────────────────────────────────┤
│   0  │  Exit                                        |
└──────┴──────────────────────────────────────────────┘
```

## Clone 

```
git clone https://github.com/notdgx/StudentRecordsProject.git 
```

## Branches 

- The Project has two branches
    - `main`
    - `tui`

> The only differnce in these branches is that the TUI contais a menu design containing ┴ ┘ ┤ ┼ ├ -> , This is not supported by PS by default , but bash do 

## Data and Output

- Main data file: `files/record`
- Session data file: `files/session_data`
- Exported files are created in `export/` (for example `all_students.csv`, `BCA_subjects.csv`)
- Templates Binary files in `templates/`


