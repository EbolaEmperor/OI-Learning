# LoopyKeep Adversarial Slitherlink Generator

This directory contains a self-contained generator used to create adversarial
Slitherlink benchmarks for this repository's `slitherlink.cpp` solver.

It vendors the minimal source files needed from Simon Tatham's Portable Puzzle
Collection `Loopy` implementation. The vendored code is MIT licensed; see
`vendor/LICENCE`.

## Build

Run from the repository root:

```bash
make slink
make -C tools/loopykeep
```

This creates:

- `tools/loopykeep/build/loopykeep`: generate full-loop boards and randomly
  keep a clue percentage.
- `tools/loopykeep/build/loopygen`: generate Tatham `Loopy` hard puzzles.
- `tools/loopykeep/build/loopysolver`: Tatham's standalone Loopy solver/grade
  checker.

## Generate 50% Keep Benchmarks

The current solver benchmark set uses 28x28 square-grid Loopy full-loop boards
with 50% of clues retained. Regenerate the deterministic local benchmark files
from the repository root with:

```bash
python3 tools/loopykeep/scripts/generate_keep50.py
```

This builds the project-local LoopyKeep tool and writes:

- `tools/loopykeep/generated/keep50-set/`
- `tools/loopykeep/generated/keep50-extra/`
- `tools/loopykeep/generated/keep50-regression-b/`

The generator also writes the corresponding `.blocks` files so the split
inputs can be reproduced exactly from the recorded seeds in
`scripts/generate_keep50.py`.

Benchmark the generated files with:

```bash
make slink
python3 tools/loopykeep/scripts/bench_files.py --timeout 8 \
  tools/loopykeep/generated/keep50-set/keep50-28x28-*.txt
python3 tools/loopykeep/scripts/bench_files.py --timeout 8 \
  tools/loopykeep/generated/keep50-extra/keep50-extra-28x28-*.txt
python3 tools/loopykeep/scripts/bench_files.py --timeout 8 \
  tools/loopykeep/generated/keep50-regression-b/keep50-regression-b-28x28-*.txt
```

`tools/loopykeep/generated/` is ignored by git because these files are
deterministic generated data.

## Search For Adversarial Cases

The adversarial examples currently checked in were found with a 45% clue keep
rate and filtered by `./slink` runtime:

```bash
python3 tools/loopykeep/scripts/search_loopy.py \
  --mode keep --timeout 5 --count 30 \
  --width 28 --height 28 --keep 45 --seed codex-keep-45

python3 tools/loopykeep/scripts/search_loopy.py \
  --mode keep --timeout 5 --count 30 \
  --width 20 --height 20 --keep 45 --seed codex-keep-20x20-45
```

Candidates that time out, or are close to the timeout, are written to
`tools/loopykeep/generated/`.

To re-test selected files with a longer timeout:

```bash
python3 tools/loopykeep/scripts/bench_files.py --timeout 30 \
  tools/loopykeep/generated/loopy-28x28-004.txt
```

## Direct Generator Usage

```bash
tools/loopykeep/build/loopykeep 28 28 45 30 codex-keep-45
```

Arguments are:

```text
loopykeep <width> <height> <keep_percent> <count> <seed> [nozero]
```

The output format is blocks:

```text
ID keep:28x28:45:1
... puzzle rows ...
END
```

Rows are already in the same `.` / digit format accepted by `./slink`.

## Caveat

These puzzles are generated from explicit single loops, so they have at least
one valid solution. Random clue thinning does not guarantee uniqueness.
Treat them as solver stress tests, not curated human-quality puzzles.
