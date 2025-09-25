# FT_NM - Unix nm Command Recreation

A 42 School project that recreates the Unix `nm` command for reading symbol tables from ELF binaries.

##  Overview

**ft_nm** is a reimplementation of the standard Unix `nm` utility that examines ELF files and displays their symbol table information. It handles x86_32, x64, object files, and shared libraries (.so).

##  Quick Start

### Installation
```bash
git clone <repository_url>
cd ft_nm
make
```

### Basic Usage
```bash
./ft_nm <binary_file>
./ft_nm /bin/ls
./ft_nm file.o
./ft_nm library.so
```

##  Supported Options (Bonus)

| Flag | Description |
|------|-------------|
| `-a` | Display all symbols including debug symbols |
| `-g` | Display only global (external) symbols |
| `-u` | Display only undefined symbols |
| `-r` | Reverse the order of the sort |
| `-p` | Don't sort; display symbols in original order |

### Examples with Options
```bash
./ft_nm -u program        # Show undefined symbols
./ft_nm -g library.so     # Show global symbols
./ft_nm -r -a file.o      # Show all symbols in reverse order
```

##  Testing

Use the included comparison script to validate against system `nm`:

```bash
./compare_nm.sh /bin/ls           # Basic test
./compare_nm.sh -u file.o         # Test with flags
./compare_nm.sh -g -r program     # Multiple flags
```

The script will show both outputs and highlight any differences in **green** (identical) or **red** (different).

##  Project Structure

```
ft_nm/
├── src/                # Source files
├── includes/           # Header files
├── libft/             # Custom C library
├── Makefile           # Build configuration
├── compare_nm.sh      # Testing script
└── README.md
```

##  Technical Details

### Supported File Types
- **x86_32** ELF binaries
- **x64** ELF binaries  
- **Object files** (.o)
- **Shared libraries** (.so)

### Symbol Types
| Symbol | Type | Description |
|--------|------|-------------|
| `T`/`t` | Text | Code section (global/local) |
| `D`/`d` | Data | Initialized data (global/local) |
| `B`/`b` | BSS | Uninitialized data (global/local) |
| `U` | Undefined | External symbol |
| `W`/`w` | Weak | Weak symbol (global/local) |

### Build Commands
```bash
make        # Compile project
make clean  # Remove object files  
make fclean # Remove all generated files
make re     # Full rebuild
```

## Project Goals

✅ Exact symbol output matching system `nm`  
✅ Handle all ELF architectures (x86_32, x64)  
✅ Support object files and shared libraries  
✅ Robust error handling  
✅ Memory safety (no leaks, crashes)  
✅ Bonus flags implementation  