# angel-computer-graphics

Exercises following along with the book [Interactive Computer Graphics: A Top-Down Approach, 6th Edition](https://www.cs.unm.edu/~angel/BOOK/INTERACTIVE_COMPUTER_GRAPHICS/SIXTH_EDITION/), by Edward Angel and Dave Shreiner.

Header files inside [angel/](https://github.com/benwiley4000/angel-computer-graphics/tree/master/angel) directory, as well as [InitShader.cpp](https://github.com/benwiley4000/angel-computer-graphics/blob/master/InitShader.cpp) are copied nearly verbatim. Other files are based on book exercises, but may have inconsistencies with the book prompts, as well as changes to ensure system compatibility.

*Works for macOS and Linux. Other systems not currently supported, but you can probably get it working if you try!*

## install dependencies

In addition to the dependencies listed below, you should have `make` and `g++` installed on your system (which you might already). If you're on macOS, just install Xcode command line tools. If you're not sure how to do that, [this guide might help](http://railsapps.github.io/xcode-command-line-tools.html).

### macOS

You should already have the required frameworks for building.

### linux

You'll need to install freeglut and glew.

For freeglut, if you're on Debian/Ubuntu, you can try:

```bash
sudo apt-get update
sudo apt-get install freeglut3-dev
```

Or you can [build and install freeglut from source](http://freeglut.sourceforge.net/docs/install.php).

For glew, you should probably [build and install from source](https://github.com/nigels-com/glew#using-gnu-make).

## build programs

```bash
make
```

## run programs

Compiled programs will be output to the `bin/` directory. Execute one of them (the files with no extension, not `.glsl` files) to see its output.
