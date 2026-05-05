# RISC-V GCC test baseline

These files capture the expected unexpected results from the RISC-V GCC
test workflow (`.github/workflows/riscv-test.yml`). They are used to
distinguish *new* regressions from pre-existing failures so that PR
authors only get pinged about results their changes actually caused.

Layout:

- `unexpected-<arch>-<abi>.txt` — list of `FAIL/XPASS/UNRESOLVED/ERROR`
  lines, one per `.sum` file, as produced by the workflow's collection
  step.
- `summary-<arch>-<abi>.txt` — the `# of ...` totals from each `.sum`
  file, kept for human reference.

## Updating the baseline

When trunk legitimately changes the set of unexpected results (e.g.
after fixing or adding tests), refresh the baseline by downloading the
`gcc-testsuite-results-<arch>-<abi>` artifact from a successful trunk
run and copying its `unexpected.txt` / `summary.txt` over the files in
this directory.
