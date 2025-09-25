#!/bin/bash

# Comparison script between system nm and ft_nm
# Usage: ./compare_nm.sh [options] <elf_file>

# Check if a parameter is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 [options] <elf_file>"
    echo "Example: $0 /bin/ls"
    echo "Example: $0 -u obj/main.o"
    echo "Example: $0 -g -u /bin/ls"
    exit 1
fi

# All arguments will be passed to both nm and ft_nm
ARGS="$@"



# Check if ft_nm exists and is executable
if [ ! -x "./ft_nm" ]; then
    echo "Error: ft_nm does not exist or is not executable."
    echo "Make sure to compile the project with 'make' first."
    exit 1
fi

echo "=== Comparison between nm and ft_nm ==="
echo "Arguments: $ARGS"
echo

# Create temporary files for output comparison
NM_OUTPUT=$(mktemp)
FT_NM_OUTPUT=$(mktemp)

# Execute system nm
echo "--- System nm output ---"
nm $ARGS 2>&1 | tee "$NM_OUTPUT"
echo

# Execute ft_nm
echo "--- ft_nm output (own implementation) ---"
./ft_nm $ARGS 2>&1 | tee "$FT_NM_OUTPUT"
echo

# Color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Show differences
echo "--- Differences (diff nm ft_nm) ---"
if diff "$NM_OUTPUT" "$FT_NM_OUTPUT" > /dev/null; then
    echo -e "${GREEN}No differences found! Outputs are identical.${NC}"
else
    echo -e "${RED}Differences found:${NC}"
    diff -u "$NM_OUTPUT" "$FT_NM_OUTPUT" || true
fi

# Clean up temporary files
rm -f "$NM_OUTPUT" "$FT_NM_OUTPUT"

echo
echo "=== End of comparison ==="