#!/bin/bash
set -e
set -x

# run cshtml
"${CSHTML_BIN}" \
    --cwe-names ""                                      \
    --diff-base "${TEST_SRC_DIR}/old/scan-results.json" \
    --diff-base-ignore-checkers "SHELLCHECK_WARNING"    \
    --plain-text-url "scan-results.err"                 \
    "${TEST_SRC_DIR}/scan-results.json"                 \
    > scan-results.html

diff -up "${TEST_SRC_DIR}/scan-results.html" "${PWD}/scan-results.html"
