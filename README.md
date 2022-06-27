# C++ AVL Tree
---

While studying computer science at Dakota State University in 2021, I created this AVL Tree as part
of an assignment for Advanced Data Structures.

Original code was written during that class. After graduating in 2022, I refactored the project and
updated the git structure. Feel free to use any of this code in learning AVL Trees in C++.

### Compilation

The included Makefile contains 2 basic targets (aside from constructing .o files).

To compile the project run...

    make all
To remove all .o files and the executable run...

    make clean

To run the AVL Tree program you will need to have a data file that follows the pattern defined in
the next section. The program takes one command line argument of the desired command data file.

    ./Bauer_CodeChallenge2 data/sample.dat

### [Command and Data Files](data/README.md)

This implementation of an AVL-Tree utilizes a dat file containing commands and values.  
The commands are in the form of Integers as follows...

| Command | Action                                  |
|---------|-----------------------------------------|
|0        | Insert the following number             |
|1        | Remove the following number             |
|2        | Print the current state of the tree     |
|8        | Deletes the entire current working tree |
|9        | Quits the program loop                  |

These commands are read and interpreted from the command line provided data file. The structure of a
data file should follow...

    # data.sample.dat

    0
    1
    0
    4
    0
    18
    1
    4
    0
    7
    2
    8
    9

All commands must be followed up by a newline.

Dan Bauer - 2021
