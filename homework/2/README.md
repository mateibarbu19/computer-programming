# Homework 2 - Star_Dust

For this problem we will use dynamic allocation to store the matrix. The number
of items on each row will be stored in the first position on each column.

## Task 1

We build a medie_gard (fence mean) function that returns the degree of charge of
that shield. It goes through all the bytes on the first and last line, only the
first byte of each item on the first column and only the last byte of each item
on the last column, and then averages them.

## Task 2

The main idea of this task was to work with the size in bytes of each type of
data in the given operations, and not always implement three cases using
conversions, so just generalize the operations and they can be extended to other
types of data if needed, such as long long. Thus, the size function returns the
number of bytes corresponding to the letter of that data type.
To delete, I called the change function and set the new value to 0.

## Task 3

We go through all the bytes on the line and check that there is a black hole.
From that column we start a fill algorithm. We use the recursive fill function
to move left, right, up or down in the matrix and turn the number of black holes
in an area.
