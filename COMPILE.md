# AgDev - compile instructions

Broadly speaking, compiling AgDev entails cloning CEdev, then copying AgDev source files on top of that repo, and then building CEdev, with some additional cleanup work performed afterwards. However, there's a lot of ways this can go wrong, so build scripts are provided to make this process easier. These scripts will place the AgDev build inside the `AgDev_build` folder relative to where they're called. They take an optional argument which points to a local copy of the AgDev git repo; if this is not provided it will pull from the main branch on GitHub instead.

If you run into issues, try installing the CEdev prerequisite libraries (fasmg, ez80-clang, and MinGW for Windows users) as described in the [CEdev compilation instructions](https://ce-programming.github.io/toolchain/static/contributing.html).

## Windows

`compile.bat [path\to\agdev\repo]`

## Linux

`sudo sh compile.sh [path/to/agdev/repo/]`
