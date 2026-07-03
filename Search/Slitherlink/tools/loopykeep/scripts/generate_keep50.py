import argparse
import pathlib
import subprocess


DATASETS = (
    ("keep50-set", 20, "codex-keep-50", "keep50-28x28"),
    ("keep50-extra", 40, "codex-keep-50-extra", "keep50-extra-28x28"),
    ("keep50-regression-b", 60, "codex-regression-b", "keep50-regression-b-28x28"),
)


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


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--width", type=int, default=28)
    ap.add_argument("--height", type=int, default=28)
    ap.add_argument("--keep", type=int, default=50)
    ap.add_argument("--outdir", default="tools/loopykeep/generated")
    ap.add_argument("--loopykeep", default="tools/loopykeep/build/loopykeep")
    ap.add_argument("--skip-build", action="store_true")
    args = ap.parse_args()

    if not args.skip_build:
        subprocess.run(["make", "-C", "tools/loopykeep"], check=True)

    outdir = pathlib.Path(args.outdir)
    outdir.mkdir(parents=True, exist_ok=True)

    for dataset, count, seed, prefix in DATASETS:
        cmd = [
            args.loopykeep,
            str(args.width),
            str(args.height),
            str(args.keep),
            str(count),
            seed,
        ]
        generated = subprocess.check_output(cmd, text=True)
        (outdir / f"{dataset}.blocks").write_text(generated)

        dataset_dir = outdir / dataset
        dataset_dir.mkdir(parents=True, exist_ok=True)
        for idx, (_, grid) in enumerate(parse_blocks(generated), 1):
            path = dataset_dir / f"{prefix}-{idx:03d}.txt"
            path.write_text("\n".join(grid) + "\n")
        print(f"{dataset}: wrote {count} puzzles to {dataset_dir}")


if __name__ == "__main__":
    main()
