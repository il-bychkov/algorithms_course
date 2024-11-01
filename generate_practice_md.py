import argparse
import os

# сейчас работает только как генератор навигации
# коглда решу проблему с энкодингом - обучу генерить оглавление

parser = argparse.ArgumentParser()


parser.add_argument("dir")
parser.add_argument('--add_nav', action=argparse.BooleanOptionalAction, default=False)

args = parser.parse_args()

dir_path = os.path.dirname(os.path.realpath(__file__))

work_dir = os.path.join(dir_path, args.dir)
md_dir = os.path.join(work_dir, "md")

mds = os.listdir(md_dir)

mds = list(filter(lambda x: "md" in x, mds))

mds.sort(key = lambda x: int(x.split(".")[0]))

print(mds)

print(args.add_nav)

for md in mds:
    print(md)

    if args.add_nav:
        index = int(md.split(".")[0])

        nav_line = ""

        prev_md = "{}.md".format(index - 1)
        next_md = "{}.md".format(index + 1)

        if prev_md in mds:
            nav_line = nav_line + "[<]({})".format(prev_md) + " | "

        nav_line = nav_line + "[plan](../practice.md)"

        if next_md in mds:
            nav_line = nav_line + " | [>]({})".format(next_md)

        with open(os.path.join(md_dir, md), "a") as file:
            file.write("\n")
            file.write(nav_line)
            file.write("\n")
