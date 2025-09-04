# 数回谜题求解器

这是一个数回谜题求解器，使用 `make` 一键编译。

### 求解器用法

```bash
./slink < [input]
```

其中 `[input]` 是输入文件名，输入格式参考 `example` 里的文件。

### 生成器用法：根据字符画生成数回

你可以自己创建一个由 `.` 和 `*` 构成的字符画，其中 `*` 构成一个无洞的连通区域，参考 `input-genPuzzle` 里的文件。文件里的第一个数表示 puzzle 里面数字的保留比例，通常建议设为 $0.8$ 以上，否则很容易导致你的 puzzle 解不唯一。

当你创建好字符画文件后，用下面的命令生成谜题：

```bash
./genAlpha < [input] > [output]
```

### 生成器用法：生成随机数回谜题

本项目提供一个随机 puzzle 生成器，使用方法：

```bash
./genBeta [H] [W] [rate] > [output]
```

其中 `H` 表示 puzzle 的高度，`W` 表示宽度，`rate` 表示数字保留比例（默认为 $0.5$）。

### 读取器用法

一个有强度的数回 puzzle 是很难生成的，本项目提供的 puzzle 生成器实际上很弱，也无法保证解的唯一性。

我强烈建议你在 [这个网站](https://slitherlink.neocities.org/) 自行生成 puzzle，然后导出为 `svg` 格式。本项目里的 `reader.py` 可以读取上述网站导出的 `svg` 图片，并转化为求解器能够读取的格式。

文件夹 `input-reader` 里有一些从上述网站导出的 `svg` 图片，你可以参考它们。

读取器由 ChatGPT 生成，用法如下：

```bash
python3 reader.py --svg [input].svg --txt [output].txt
```