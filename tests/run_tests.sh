#!/usr/bin/env bash
# ---------------------------------------------------------------
# SortFunctions Test Suite - Linux/macOS Build Script
# Usage: bash tests/run_tests.sh   (from project root)
#    OR  cd tests && bash run_tests.sh
# Requires: g++ (install via: sudo apt install g++)
# ---------------------------------------------------------------

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SRC_DIR="$SCRIPT_DIR/../src"
OUT="$SCRIPT_DIR/test_runner"

echo ""
echo "================================================================"
echo "  SortFunctions Library - Test Suite  [Linux/macOS]"
echo "================================================================"
echo ""

# Check compiler is available
if ! command -v g++ &>/dev/null; then
    echo " ERROR: g++ not found."
    echo " Install with:"
    echo "   Debian/Ubuntu : sudo apt install g++"
    echo "   Fedora/RHEL   : sudo dnf install gcc-c++"
    echo "   macOS         : xcode-select --install"
    echo ""
    exit 1
fi

echo " Compiler : $(g++ --version | head -1)"
echo " Source   : $SRC_DIR/SortFunctions.cpp"
echo " Tests    : $SCRIPT_DIR/test_main.cpp"
echo " Output   : $OUT"
echo ""

# ---- Step 1: Compile ----
echo "[1/2] Compiling..."
g++ -std=c++11 -Wall \
    -I "$SCRIPT_DIR" -I "$SRC_DIR" \
    "$SCRIPT_DIR/test_main.cpp" "$SRC_DIR/SortFunctions.cpp" \
    -o "$OUT"

COMPILE_EXIT=$?
if [ $COMPILE_EXIT -ne 0 ]; then
    echo ""
    echo " [FAIL] Compilation failed. See errors above."
    echo ""
    exit 1
fi
echo "       Compilation succeeded."
echo ""

# ---- Step 2: Run ----
echo "[2/2] Running tests..."
echo ""

"$OUT"
TEST_EXIT=$?

echo ""
if [ $TEST_EXIT -eq 0 ]; then
    echo " Build and tests completed successfully."
else
    echo " Build succeeded but one or more tests FAILED."
fi

rm -f "$OUT"
echo ""
exit $TEST_EXIT
