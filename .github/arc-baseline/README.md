# ARC GCC test baseline

Same idea as `../riscv-baseline/`: stores the expected
`FAIL/XPASS/UNRESOLVED/ERROR` lines for each ARC target so the
`arc-test.yml` workflow can highlight only *new* regressions.

- `unexpected-<target>-<cpu>.txt` — one line per unexpected result,
  prefixed with the `.sum` filename (e.g. `gcc.sum: FAIL: ...`).
- `summary-<target>-<cpu>.txt` — the `# of ...` totals from each `.sum`
  file, kept for human reference.

Refresh by copying `unexpected.txt` / `summary.txt` from a known-good
`arc-gcc-testsuite-results-<target>-<cpu>` artifact over the files in
this directory.
