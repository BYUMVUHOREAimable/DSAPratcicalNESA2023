# Rwanda Coding Academy Inventory System

A C++ implementation of an inventory management system for Rwanda Coding Academy (RCA) as part of the National Practical Examinations for TSS Level 5 assessment.

## Features

- **Add new items** to inventory with `itemadd` command
- **List all items** alphabetically with `itemslist` command
- **Interactive console interface** with command suggestions
- **CSV data storage** for persistent inventory records
- **Case-insensitive commands** for user convenience
- **Help system** with command documentation

## Commands

| Command | Syntax | Description |
|---------|--------|-------------|
| `itemadd` | `itemadd <item_id> <item_name> <quantity> <registration_date>` | Adds a new item to inventory |
| `itemslist` | `itemslist` | Displays all items sorted alphabetically |
| `help` | `help` | Shows available commands and usage |
| `exit` | `exit` | Exits the program |

## Getting Started

### Prerequisites

- C++ compiler (GCC, Clang, or MSVC)
- CMake (optional, for building)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/BYUMVUHOREAimable/DSAPratcicalNESA2023.git
   cd DSAPratcicalNESA2023
