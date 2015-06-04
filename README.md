# CSample
A sample of programs written in C, and C++

The code contained in this repo is a small selection of some of that I've written in C/C++.

The majority was undertaken in the form of homework assignments for lower division
study in Computer Science at Regis University; essentially, control and data structures, and 
modular programming.

It is intended to present a basic understanding of: memory management, type casting and definitions,
file IO, basic data-structures (independent of the c++ standard library classes).

The following files are included:
bezierCurve.c/h      -- C files for creating a bezier curve of optional order, and storing the resulting curve components
                        (x, y, and z) in an array of type float, based on the number of segments chosen.
crcProgram.cpp       -- A Regis U. homework assignment for a networking course to imitate the crc performed on TCP and IP 
                        header contents
doubleLinkedList.cpp -- A Regis U. homework assignment for a data-structures course to gain experience building linked-lists.
                        two text files accompany (doubleIn/doubleFind.txt), and passed as command line arguments. The program
                        reads doubleIn, and attempts to match the integers stored within with those present in doubleFind.
networkSimulator.cpp -- A Regis U. homework assignment for a networking course to simulate network traffic according to a given 
                        finite-state machine.
residentInfo.cpp     -- A Regis U. homework assignment for a data-structures course. The user is prompted for a filename, which
                        will be used to populate a list of residents per the program's schema. The user then may select
                        from a menu of options: add, remove, exit, and match--which reads a pre-defined file, and matches 
                        goods to a user in the list. The user maintains an option on exit to update a file of their choice.
