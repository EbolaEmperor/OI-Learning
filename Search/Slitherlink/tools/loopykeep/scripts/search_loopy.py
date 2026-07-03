import argparse
import pathlib
import subprocess
import time


def parse_blocks(text):
    cur_id = None
    cur = []
    for raw in text.splitlines():
        line = raw.strip()
        if not line:
            continue
        if line.startswith("ID "):
            cur_id = line[3:]
            cur = []
        elif line == "END":
            if cur_id is not None:
                yield cur_id, cur
            cur_id = None
            cur = []
        else:
            cur.append(line)


def solve_time(slink, grid, timeout_s):
    inp = ("\n".join(grid) + "\n").encode()
    start = time.perf_counter()
    try:
        proc = subprocess.run(
            [slink],
            input=inp,
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
            timeout=timeout_s,
            check=False,
        )
        elapsed = time.perf_counter() - start
        return elapsed, proc.returncode, False
    except subprocess.TimeoutExpired:
        return timeout_s, None, True


def load_existing(paths):
    for path in paths:
        p = pathlib.Path(path)
        grid = [line.strip() for line in p.read_text().splitlines() if line.strip()]
        yield str(p), grid


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--slink", default="./slink")
    ap.add_argument("--loopygen", default=None)
    ap.add_argument("--mode", choices=["loopy", "keep"], default="loopy")
    ap.add_argument("--keep", type=int, default=80)
    ap.add_argument("--nozero", action="store_true")
    ap.add_argument("--outdir", default="tools/loopykeep/generated")
    ap.add_argument("--timeout", type=float, default=5.0)
    ap.add_argument("--count", type=int, default=30)
    ap.add_argument("--width", type=int, default=28)
    ap.add_argument("--height", type=int, default=28)
    ap.add_argument("--seed", default="codex-loopy-search")
    ap.add_argument("--existing", nargs="*", default=[])
    args = ap.parse_args()
    if args.loopygen is None:
        args.loopygen = (
            "tools/loopykeep/build/loopykeep"
            if args.mode == "keep"
            else "tools/loopykeep/build/loopygen"
        )

    outdir = pathlib.Path(args.outdir)
    outdir.mkdir(parents=True, exist_ok=True)

    results = []
    if args.existing:
        print("existing baseline:", flush=True)
        for name, grid in load_existing(args.existing):
            elapsed, rc, timed_out = solve_time(args.slink, grid, args.timeout)
            clues = sum(ch != "." for row in grid for ch in row)
            cells = len(grid) * len(grid[0])
            print(f"{name}\t{elapsed:.3f}s\ttimeout={timed_out}\tclues={clues}/{cells}", flush=True)

    print(f"generating {args.count} {args.mode} {args.width}x{args.height} puzzles...", flush=True)
    if args.mode == "loopy":
        gen_cmd = [
            args.loopygen,
            str(args.width),
            str(args.height),
            "h",
            str(args.count),
            args.seed,
        ]
    else:
        gen_cmd = [
            args.loopygen,
            str(args.width),
            str(args.height),
            str(args.keep),
            str(args.count),
            args.seed,
        ]
        if args.nozero:
            gen_cmd.append("nozero")
    gen = subprocess.run(
        gen_cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        check=True,
    )

    for idx, (gid, grid) in enumerate(parse_blocks(gen.stdout), 1):
        elapsed, rc, timed_out = solve_time(args.slink, grid, args.timeout)
        clues = sum(ch != "." for row in grid for ch in row)
        cells = len(grid) * len(grid[0])
        results.append((timed_out, elapsed, idx, gid, grid, clues, cells, rc))
        status = "TIMEOUT" if timed_out else f"{elapsed:.3f}s"
        print(f"{idx:03d}\t{status}\tclues={clues}/{cells}\t{gid}", flush=True)

        if timed_out or elapsed >= args.timeout * 0.8:
            path = outdir / f"loopy-{args.width}x{args.height}-{idx:03d}.txt"
            path.write_text("\n".join(grid) + "\n")
            meta = outdir / f"loopy-{args.width}x{args.height}-{idx:03d}.meta"
            meta.write_text(
                f"id={gid}\ntimeout={timed_out}\nelapsed={elapsed:.6f}\n"
                f"clues={clues}\ncells={cells}\nreturncode={rc}\n"
            )

    print("top candidates:", flush=True)
    for timed_out, elapsed, idx, gid, grid, clues, cells, rc in sorted(
        results, key=lambda x: (x[0], x[1]), reverse=True
    )[:10]:
        status = "TIMEOUT" if timed_out else f"{elapsed:.3f}s"
        print(f"{idx:03d}\t{status}\tclues={clues}/{cells}\t{gid}", flush=True)


if __name__ == "__main__":
    main()
