#!/usr/bin/env python3
import os
import re
import sys

all_fnames = [h for h in os.listdir(".") if h[-2:] in [".h", ".c"]]

header_re = re.compile(r'\s*#include\s+"([^"]+)"')

def find_includes(fname):
    with open(fname) as f:
        headers = (header_re.match(l) for l in f.readlines())
    headers = [str(m.group(1)) for m in headers if m]

    return fname, headers

find_all = (find_includes(n) for n in all_fnames)
dependency_map = {n:h for n, h in find_all}

def add_child_deps(deps, source_deps, travelled):
    for fname in source_deps:
        if fname in travelled:
            continue
        
        deps += (d for d in dependency_map[fname] if d not in deps)
        travelled.append(fname)

        add_child_deps(deps, dependency_map[fname], travelled)

c_files = [n for n in dependency_map.keys() if n.endswith(".c")]
c_files.sort()

with open("makefile.in", "w") as f:
    f.write(f"# Generated with {sys.argv[0]}\n# DO NOT EDIT!\n\n")

    for fname in c_files:
        dependencies = list(dependency_map[fname])
        add_child_deps(dependencies, dependency_map[fname], [])
        dependencies.sort()

        f.write(fname[:-2] + ".o: ")
        f.write(" ".join(dependencies))
        f.write("\n")