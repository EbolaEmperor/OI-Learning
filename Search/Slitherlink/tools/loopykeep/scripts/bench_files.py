import argparse
import pathlib
import subprocess
import time


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--slink", default="./slink")
    ap.add_argument("--timeout", type=float, default=30.0)
    ap.add_argument("files", nargs="+")
    args = ap.parse_args()

    rows = []
    for name in args.files:
        path = pathlib.Path(name)
        grid = [line.strip() for line in path.read_text().splitlines() if line.strip()]
        inp = ("\n".join(grid) + "\n").encode()
        start = time.perf_counter()
        try:
            proc = subprocess.run(
                [args.slink],
                input=inp,
                stdout=subprocess.DEVNULL,
                stderr=subprocess.DEVNULL,
                timeout=args.timeout,
                check=False,
            )
            elapsed = time.perf_counter() - start
            timed_out = False
            rc = proc.returncode
        except subprocess.TimeoutExpired:
            elapsed = args.timeout
            timed_out = True
            rc = None

        clues = sum(ch != "." for row in grid for ch in row)
        cells = len(grid) * len(grid[0])
        rows.append((timed_out, elapsed, str(path), clues, cells, rc))
        status = "TIMEOUT" if timed_out else f"{elapsed:.3f}s"
        print(f"{path}\t{status}\tclues={clues}/{cells}\trc={rc}", flush=True)

    print("top:")
    for timed_out, elapsed, path, clues, cells, rc in sorted(rows, reverse=True)[:10]:
        status = "TIMEOUT" if timed_out else f"{elapsed:.3f}s"
        print(f"{path}\t{status}\tclues={clues}/{cells}\trc={rc}")


if __name__ == "__main__":
    main()
