#!/usr/bin/env python3

import subprocess;
import platform;

build_dir = "build"
system = platform.system()

if system == "Darwin" or system == "Linux":
    subprocess.run(["mkdir", build_dir])
    subprocess.run(["cmake", "-DCMAKE_BUILD_TYPE=Debug", "-B", build_dir, "."])
elif system == "Windows":
    print("TODO: windows support")

