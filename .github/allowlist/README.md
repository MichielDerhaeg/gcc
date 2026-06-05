# GCC testsuite allowlist

Known-acceptable testsuite results, used by
[`.github/scripts/testsuite-filter`](../scripts/testsuite-filter) to
distinguish *new* regressions from pre-existing failures. This replaces the
old flat `*-baseline/unexpected-*.txt` set-diff model and follows the
[riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain)
`test/allowlist/` design.

## Format

Each line is a single normalised result:

```
<STATUS>: <testpath>
```

where `STATUS` is one of `FAIL`, `XPASS`, `UNRESOLVED`, `ERROR` and `testpath`
is the test identifier (the second whitespace token of the `.sum` line). Lines
beginning with `#` are comments.

Matching is two-level: the `testpath` must match exactly *and* the full `.sum`
result line must start with the allowlist entry. Because the entry omits the
per-variation suffix (e.g. `-std=gnu++20 (test for excess errors)`), one entry
covers every option/standard variation of that test — but a *status* change
(e.g. a `FAIL` that becomes an `XPASS`) is still reported, since the status is
part of the entry.

## File layout

```
<tool>/common.log
<tool>/[<libc>.][<arch>.][<abi>.]log
```

`testsuite-filter` is told the target `(libc, arch, abi)` and loads every
applicable file that exists, layered from most general to most specific:

- `common.log` — failures shared by **every** target (RISC-V and ARC alike).
- `<libc>.log` — e.g. `newlib.log`.
- `<arch>.log` / `<abi>.log` / `<arch>.<abi>.log` — e.g. `rv32.ilp32d.log`,
  `arc-em.log`, `arc-hs38_linux.log`. For RISC-V, `<arch>` is the base arch
  (`rv32`/`rv64`); extension-specific permutations are also consulted.

Current targets and their per-target files:

| Workflow job              | arch / abi passed    | files loaded                        |
| ------------------------- | -------------------- | ----------------------------------- |
| `rv32gc` / `ilp32d`       | `rv32gc` / `ilp32d`  | `common.log`, `rv32.ilp32d.log`     |
| `rv64gc` / `lp64d`        | `rv64gc` / `lp64d`   | `common.log`, `rv64.lp64d.log`      |
| `arc` / `em`              | `arc-em` / (none)    | `common.log`, `arc-em.log`          |
| `arc` / `hs38_linux`      | `arc-hs38_linux`     | `common.log`, `arc-hs38_linux.log`  |

## Updating the allowlist

When trunk legitimately changes the set of acceptable failures, edit the
relevant `.log` file:

- A failure now fixed → a fixed test simply drops out of the `.sum`, so its
  stale allowlist line is harmless, but prune it to keep the list honest.
- A new acceptable/expected failure → add a `<STATUS>: <testpath>` line. Put it
  in `common.log` if it affects every target, otherwise in the most specific
  per-target file. The PR comment / `regressions.txt` artifact from a failing
  run lists the exact lines to add.

The initial contents were seeded from the legacy baselines: `common.log` is the
intersection of all four targets' failures, and each per-target file holds that
target's remainder.
