# Adversarial LoopyKeep Slitherlink Samples

Source: Simon Tatham's Portable Puzzle Collection, `loopy.c` / `loopgen.c`
using the square-grid loop generator. The generated full clue boards were
randomly thinned to keep about 45% of clues, then filtered by this repository's
`./slink` runtime.

Generation command used from the project-local wrapper:

```bash
make -C tools/loopykeep
tools/loopykeep/build/loopykeep 28 28 45 30 codex-keep-45
tools/loopykeep/build/loopykeep 20 20 45 30 codex-keep-20x20-45
```

Baseline on this machine:

- Existing `example/hard-28x28-*.txt`: 0.07s to 0.24s.
- Existing `example/beta-28x28-*.txt`: about 0.01s.
- The three 28x28 samples: timed out at 5s during search and each of the
  first three re-tested candidates also timed out at 30s.
- `adversarial-loopykeep-20x20-1.txt` also timed out at 30s, so this method
  is not relying only on the maximum 28x28 size.
- Tatham's own `loopysolver -g` reports these samples as `harder than Hard,
  or ambiguous`.

The puzzles are valid because clues are derived from an explicit generated
single loop. They are not guaranteed unique after random thinning; they are
intended as adversarial solver benchmarks rather than human-quality Nikoli
puzzles.
