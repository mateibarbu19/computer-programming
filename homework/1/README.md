# Homework 1

## Problem 1 - On the fly analysis (Ninel)

In this problem we will identify the special trees by going through the string
of numbers, element by element, and remembering a triplet of numbers
(penultimate, last, x). The penultimate represents the penultimate read element,
the last represents the last read element and x the current element. If in this
triplet the last one is bigger than the penultimate one and than the current
element then it is a special tree. We add to the sum of the special trees the
value from the last variable and check according to the parity of the position
occupied in the row, if it is a minimum or maximum tree. At the end we calculate
the average according to the variable amount and the number of special trees and
we treat the special cases.

## Problem 2 - Properties of natural numbers (Vectsecv)

We create a function of constructing the numbers n_descending and n_increasing
called construieste. It uses a frequency vector to sort the digits of the
transmitted number as a parameter in linear time (depending on the number of
digits). We calculate the difference between n_decreasing and n_increasing and
retain it in a vector. In a respective structure starting from the new
difference we repeat the procedure described above as long as the difference
between the values n_descending and n_inreasing acts is not repeated. When a
difference is repeated, we display the index of the first occurrence and the
elements up to it.

## Problem 3 - Improving scores (Codeinvim)

For each subject we calculate the difference between the possible score obtained
by Mihai if he would increase his current grade to 10 and the current score he
has. We sort the difference vector ascending and we go through it in descending
order by adding element by element from the vector to Mihai's total score until
it reaches at least p_min points and we display the number of subjects to which
it was enlarged. If unfortunately he can't get the minimum score we display -1.

## Problem 4 - Nonogram checker

We read the input data and store it in two-dimensional arrays.
For each part of the table read, we check if it respects the rules of the game
with an algorithm similar to the one for determining the number of words in a
string.

Algorithm:

1. We use an ok flag variable, which retains the value 1 if the nomogram is
correct so far, 0 otherwise.
2. We use three variables in_secv, poz and nr_caract that remember if for the
current element on the line its previous element was in a sequence of 1, the
position in the number of groups k of that line, respectively the number of
characters in the last such grouping.
3. Then, based on their values, we process the current element on the line.
4. Thus, going through each element on the line and according to these three
	variables:
	- we continue a sequence of 1 increasing the number of characters
	- we end it when a 0 appears
	- or we start a new sequence, if we were not in the previous sequence and we
		find a 1
5. We check each time whether the number of characters at the end of a sequence
	is equal to the number of characters in the corresponding group and whether
	the number of groups has not been exceeded. Otherwise we assign the value 0
	to the ok flag.

We repeat this algorithm analogously and in columns.
We will implement the traversal of the table on rows, respectively on columns in
two different functions.