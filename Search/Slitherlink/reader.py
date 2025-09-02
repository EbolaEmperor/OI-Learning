# slitherlink_svg_to_chars.py
import os
import re
import argparse
import numpy as np
from lxml import etree
from collections import defaultdict

XLINK = "{http://www.w3.org/1999/xlink}"

# ---------- transform ----------
def parse_translate(transform):
    if not transform:
        return 0.0, 0.0
    m = re.search(r"translate\(\s*([\-0-9.]+)(?:\s*,\s*([\-0-9.]+))?\s*\)", transform)
    if not m:
        return 0.0, 0.0
    tx = float(m.group(1))
    ty = float(m.group(2)) if m.group(2) is not None else 0.0
    return tx, ty

def total_translate(elem):
    tx = ty = 0.0
    cur = elem
    while cur is not None:
        t = cur.get("transform")
        if t:
            dx, dy = parse_translate(t)
            tx += dx
            ty += dy
        cur = cur.getparent()
    return tx, ty

# ---------- ns-agnostic helpers ----------
def find_first_by_id(root, id_value):
    res = root.xpath(f'.//*[@id="{id_value}"]')
    if res:
        return res[0]
    res = root.xpath(f'.//*[local-name()="*"][@id="{id_value}"]')
    return res[0] if res else None

def iter_uses(root):
    for el in root.xpath('.//use|.//*[local-name()="use"]'):
        yield el

def iter_rects(root):
    for el in root.xpath('.//rect|.//*[local-name()="rect"]'):
        yield el

def iter_circles(root):
    for el in root.xpath('.//circle|.//*[local-name()="circle"]'):
        yield el

def get_attr(elem, name):
    v = elem.get(name)
    if v is None and name == "href":
        v = elem.get(XLINK + "href")
    return v

def unique_sorted(vals, tol=1e-6):
    arr = sorted(vals)
    out = []
    for v in arr:
        if not out or abs(v - out[-1]) > tol:
            out.append(v)
    return out

def nearest_index(centers, v):
    return int(np.argmin(np.abs(np.asarray(centers) - v)))

def build_centers(lines):
    return [(lines[i] + lines[i+1]) * 0.5 for i in range(len(lines)-1)]

# ---------- auto-detect grid points ----------
def detect_grid_points(root, board=None, tiny_threshold=5.5, min_points=16):
    target_root = board if board is not None else root

    # 1) try <g id="points">
    points_group = find_first_by_id(target_root, "points") or find_first_by_id(root, "points")
    px, py = [], []
    if points_group is not None:
        for use in iter_uses(points_group):
            x = get_attr(use, "x"); y = get_attr(use, "y")
            if x is None or y is None:
                continue
            tx, ty = total_translate(use)
            px.append(float(x) + tx)
            py.append(float(y) + ty)
        if len(px) >= min_points and len(py) >= min_points:
            return unique_sorted(px), unique_sorted(py)

    # 2) global scan <use> grouped by href
    href_groups = defaultdict(list)
    for use in iter_uses(target_root):
        href = get_attr(use, "href")
        if not href or not href.startswith("#"):
            continue
        x = get_attr(use, "x"); y = get_attr(use, "y")
        if x is None or y is None:
            continue
        tx, ty = total_translate(use)
        href_groups[href].append((float(x)+tx, float(y)+ty))

    best_href, best_list = None, []
    for href, pts in href_groups.items():
        if len(pts) > len(best_list):
            best_href, best_list = href, pts

    # 3) tiny rect / circle clustering
    rect_bins = defaultdict(list)
    for r in iter_rects(target_root):
        w = r.get("width"); h = r.get("height")
        x = r.get("x"); y = r.get("y")
        if None in (w,h,x,y):
            continue
        w = float(w); h = float(h)
        if w <= tiny_threshold and h <= tiny_threshold:
            tx, ty = total_translate(r)
            rect_bins[(round(w,1), round(h,1))].append((float(x)+tx, float(y)+ty))

    circle_bins = defaultdict(list)
    for c in iter_circles(target_root):
        rr = c.get("r"); cx = c.get("cx"); cy = c.get("cy")
        if None in (rr,cx,cy):
            continue
        rr = float(rr)
        if 2*rr <= tiny_threshold:
            tx, ty = total_translate(c)
            circle_bins[round(2*rr,1)].append((float(cx)+tx, float(cy)+ty))

    candidates = []
    if best_list:
        candidates.append(("use:"+best_href, best_list))
    if rect_bins:
        key, pts = max(rect_bins.items(), key=lambda kv: len(kv[1]))
        candidates.append(("rect:"+str(key), pts))
    if circle_bins:
        key, pts = max(circle_bins.items(), key=lambda kv: len(kv[1]))
        candidates.append(("circle:"+str(key), pts))

    if not candidates:
        raise RuntimeError("未找到网格点：没有 points 组，且也没能从 use/rect/circle 自动识别出点阵")

    label, pts = max(candidates, key=lambda kv: len(kv[1]))
    if len(pts) < min_points:
        raise RuntimeError(f"识别到的点数量过少（{len(pts)}）: {label}")

    xs = unique_sorted([p[0] for p in pts])
    ys = unique_sorted([p[1] for p in pts])
    if len(xs) < 2 or len(ys) < 2:
        raise RuntimeError(f"点阵坐标不足（xs={len(xs)}, ys={len(ys)}）：{label}")
    return xs, ys

def matrix_to_char_lines(matrix):
    # -1 -> '.', others -> digit char
    lines = []
    for row in matrix:
        s = ''.join('.' if v < 0 else str(int(v)) for v in row)
        lines.append(s)
    return lines

def main():
    ap = argparse.ArgumentParser(description="Parse Slitherlink SVG and print char matrix ('.' for empty).")
    ap.add_argument("--svg", required=True, help="Path to input SVG")
    ap.add_argument("--txt", default=None, help="Optional path to save char matrix as a .txt file")
    args = ap.parse_args()

    in_path = os.path.abspath(args.svg)
    with open(in_path, "rb") as f:
        tree = etree.parse(f)
    root = tree.getroot()

    board = find_first_by_id(root, "board")

    # 1) grid
    xs, ys = detect_grid_points(root, board)
    cols = len(xs) - 1
    rows = len(ys) - 1
    cx = build_centers(xs)
    cy = build_centers(ys)

    # 2) numbers map (extend if your defs differ)
    id_to_digit = {"n00": 0, "n01": 1, "n02": 2, "n03": 3, "n04": 4}

    # 3) numbers group
    numbers_group = (find_first_by_id(board if board is not None else root, "numbers")
                     or find_first_by_id(root, "numbers")
                     or (board if board is not None else root))

    matrix = np.full((rows, cols), -1, dtype=int)
    seen = set()

    for use in iter_uses(numbers_group):
        href = get_attr(use, "href")
        if not href or not href.startswith("#"):
            continue
        sym_id = href[1:]
        if sym_id not in id_to_digit:
            continue
        x = get_attr(use, "x"); y = get_attr(use, "y")
        if x is None or y is None:
            continue

        tx, ty = total_translate(use)
        gx, gy = float(x) + tx, float(y) + ty

        c = nearest_index(cx, gx)
        r = nearest_index(cy, gy)
        if 0 <= r < rows and 0 <= c < cols:
            key = (r, c, id_to_digit[sym_id])
            if key in seen:
                continue
            seen.add(key)
            if matrix[r, c] == -1:
                matrix[r, c] = id_to_digit[sym_id]

    # 4) print char matrix
    lines = matrix_to_char_lines(matrix)
    for line in lines:
        print(line)

    # optional save
    if args.txt:
        with open(os.path.abspath(args.txt), "w", encoding="utf-8") as f:
            for line in lines:
                f.write(line + "\n")

if __name__ == "__main__":
    main()