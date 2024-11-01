import argparse
import os
import shutil

parser = argparse.ArgumentParser()


parser.add_argument("dir")
args = parser.parse_args()

dir_path = os.path.dirname(os.path.realpath(__file__))

work_dir = os.path.join(dir_path, args.dir)
src_dir = os.path.join(work_dir, "src")

srcs = os.listdir(src_dir)


with open(os.path.join(work_dir, "CMakeLists.txt"), "w") as file:

    file.write("cmake_minimum_required(VERSION 3.16)\n")
    file.write('project("practice")\n')
    file.write("\n")
    file.write("set(SRC_PREFIX src)\n")
    file.write("set(INSTAL_DIR bin)\n")
    file.write("\n")

    for src in srcs:
        file.write("add_executable(" + src.split(".")[0] + " " + "${SRC_PREFIX}"+"/{src}".format(src = src) + ")\n")

    file.write("\n")
    file.write("INSTALL(\n")
    file.write("    TARGETS\n")

    for src in srcs:
        file.write("    " + src.split(".")[0] + "\n")

    file.write("    DESTINATION\n")
    file.write("    ${CMAKE_CURRENT_SOURCE_DIR}/${INSTAL_DIR}\n")
    file.write(")\n")
    file.write("\n")

shutil.copyfile(os.path.join(dir_path, "config/presets/build.sh"), os.path.join(work_dir, "build.sh"))