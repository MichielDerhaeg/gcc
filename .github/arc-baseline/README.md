# ARC GCC test baseline

Same idea as `../riscv-baseline/`: stores the expected
`FAIL/XPASS/UNRESOLVED/ERROR` lines for each ARC target so the
`arc-test.yml` workflow can highlight only *new* regressions.

- `unexpected-<target>.txt` — one line per unexpected result, prefixed
  with the `.sum` filename (e.g. `gcc.sum: FAIL: ...`).

Refresh by copying `unexpected.txt` from a known-good
`arc-gcc-testsuite-results-<target>` artifact over the file in this
directory.

No baseline files are committed yet — the workflow will simply report
all unexpected results until one is added.
