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
  - [Tesseract OCR Setup (C++)](#tesseract-ocr-setup-c)

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
## Tesseract OCR Setup (C++)
This project uses Tesseract OCR together with OpenCV to perform text recognition on images.
Tesseract is not header-only and requires system installation, development headers, and trained language data.

1. Install Tesseract OCR  
   ```
   sudo apt update
   sudo apt install tesseract-ocr
   ```
   Verify installation:
   ```
   tesseract --version
   ```
2. Install Language Data.  
   English is installed by default. For Spanish OCR:
   ```
   sudo apt install tesseract-ocr-spa
   ```
   Language data files (*.traineddata) are typically installed in: /usr/share/tesseract-ocr/4.00/tessdata/

3. Install Development Libraries (Required for C++).  
   These packages provide headers and libraries for linking:
   ```
   sudo apt install libtesseract-dev libleptonica-dev
   ```
   Check that headers are available:
   ```
   ls /usr/include/tesseract
   ls /usr/include/leptonica
   ```

4. Build Configuration (Makefile)  
   Relevant Makefile entries:
  `--libs tesseract lept`
  This automatically links against:
  - libtesseract
  - liblept
  - OpenCV
  If the program runs but OCR output is incorrect, verify:
  - the correct language code is used ("eng", "spa", etc.)
  - the image has sufficient contrast
  - preprocessing (grayscale / thresholding) is applied

Notes
- Tesseract expects clean, high-contrast images
- OCR accuracy strongly depends on preprocessing
- GetUTF8Text() returns dynamically allocated memory and must be freed by the caller

Architecture Overview
- OpenCV: image loading and preprocessing
- Tesseract: text recognition engine
- Leptonica: internal image handling used by Tesseract
---



