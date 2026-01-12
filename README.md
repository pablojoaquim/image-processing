# Project Name
IMAGE PROCESSING

---
## Table of Contents
- [Project Name](#project-name)
  - [Table of Contents](#table-of-contents)
  - [About](#about)
  - [Features](#features)
  - [Tech Stack](#tech-stack)
  - [Project Structure](#project-structure)
  - [Getting Started](#getting-started)
    - [Clone the repository](#clone-the-repository)
    - [Install dependencies](#install-dependencies)
  - [Build \& Run](#build--run)
    - [Build](#build)
    - [Run the executable](#run-the-executable)
  - [Running Tests](#running-tests)
  - [Code Coverage](#code-coverage)
  - [Configuration](#configuration)
  - [Common Makefile variables you can customize:](#common-makefile-variables-you-can-customize)

---
## About
This project is mainly to develop image processing use cases. 

---
## Features
* Fast and lightweight
* Unit tests included
* Code coverage support
* Modular and extendable

---
## Tech Stack

| Component    | Technology          |
| ------------ | ------------------- |
| Language     | C / C++             |
| Build System | Make                |
| Testing      | Your test framework |
| Coverage     | gcov / gcovr        |

---
## Project Structure
```
project/
├── src/            # Source code
├── test/           # Unit tests
├── build/          # Build and output folder
├── Makefile        # Build system
└── README.md
```

---
## Getting Started
### Clone the repository
```bash
git clone https://github.com/pablojoaquim/image-processing.git
```
### Install dependencies
sudo apt install libopencv-dev
sudo apt install libmatplotplusplus-dev


---
## Build & Run
### Build
```bash
make
```
### Run the executable
```bash
make run
```

---
## Running Tests
```bash
make tests
make run-tests
```

---
## Code Coverage
```bash
make coverage
```
Reports are generated in:
```
build/coverage/coverage.html
```

---
## Configuration
Common Makefile variables you can customize:
---



