# EVT Validator Tests

This directory contains focused fixtures for `tools/build/evt_validate_obj.py`.

Layout:

- `pass/`: `.c` files that should compile to MIPS ELF objects and pass validation.
- `fail/`: `.c` files that should fail validation.
- `fail/*.stderr`: required stderr substrings for the matching failing `.c` file.

Run the suite with:

```sh
python3 tools/evt_test/run_tests.py
```

Useful options:

```sh
python3 tools/evt_test/run_tests.py --filter missing_end
python3 tools/evt_test/run_tests.py --keep-temp
```

When adding a new failing case, keep the source small and add a sibling `.stderr`
file with the important substrings to assert. Prefer matching the source path,
script symbol, and core error text rather than exact byte offsets or source line
numbers, unless the line number itself is the behavior under test.
