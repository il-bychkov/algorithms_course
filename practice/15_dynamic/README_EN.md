## Dynamic Programming: Problems
### Good and Bad Binary String Problem
#### Condition:
A binary string is given. If there is no substring “00” in it, we will call it good. Otherwise it is bad.
We need to calculate how many good strings of length n exist.
#### Brute force:
Generate 2^n strings and check each one to see if it is a good string.
The complexity is O(2^n).
#### Using the dynamic programming paradigm
Let's imagine that we have 2 good lines of smaller size. Then they end one at 1, the other at 0. The one at 0 must have a one before that zero, otherwise it is bad. Then the formula to fill our array is: d[i] = d[i-1] + d[i-2].

##### Trivial Cases:
It remains to define the trivial cases. They can be counted by hand, the lines are not long.

d[2] = 3,
d[1] = 2
Then d[0] = 1
Indeed, d[3] = 3 + 2 = 5.

#### Good and Bad k-ary string problem

Now let's solve the problem in general form: the string is k-ary. We need to define the same.
#### Using the dynamic programming paradigm
If the string ends at 0, then there is anything other than zero before it, i.e. k-1 variants.

If the string ends with something other than 0, then anything stands before this character, no additional conditions can be imposed on it.

Total ratio d[i] = (d[i-1] + d [i-2]) * (k-1)

##### Trivial cases:

Let k=3, i.e. the string is 3-ary.

d[1] = 3, d[0] = 1. Then d[0] = 1

Indeed, d[2] = 4*2 = 8. If you calculate it by hand, it turns out exactly like this.

### Editing distance (Livenshtein distance, editing distance)
#### Condition:
Given 2 strings: A[1..n], B[1..m].

Available operations: delete, add and replace a letter. We need to determine for what minimum number of operations we can get string A from string B.

> Practical application: correcting typos in a text editor (like: *perhaps you meant this word: ...*).
>
Let's take the first i characters from A and the first j characters from B. Let's see how these strings can be arranged in the answer:

1 case:
```
a_i
b_j
```

2 case:
```
-
b_j
```
3 case:
```
a_i
-
```
Let D_{ij} be the answer matrix for row A of length i and row B of length j.

Then the first case can be calculated as follows:

`d[i-1][j-1] + diff(a_i, b_j)`, where diff will return 1 if the characters are different and 0 if equal.

Second case: `d[i-1][j] + 1`.

Third case: `d[i][j-1] + 1`.

And we need to choose the minimum of these three options in terms of cost.

### Knapsack Problem
#### 1 variant: fractional knapsack
Let's imagine that objects can be cut.

If the knapsack is unbounded, we take the most expensive item by weight/price ratio and fill the knapsack with it to the maximum.

If the backpack is 0-1, then first sort the items by weight/price ratio and take the best ones.

#### 2nd option: unbounded knapsack

Here we can take an unlimited number of items of each type.

Let's create a matrix d[Q] - the best price of a backpack that holds Q kg. Then we need to choose the maximum of the following options:

``d[Q - w_1] + P_1``.

``d[Q - w_2] + P_2`''

...

```d[Q - w_n] + P_n```.

Where P_i is the price of the i-th item.

Complexity: O(n * capacity) - so called pseudo polynomial complexity

#### 3 variant: 0-1 knapsack

Here we can only decide whether we take the item or not. We have 1 copy of each item.

It is solved in the same way as the previous variant, but with the help of a matrix. Let matrix D_{ij} store the maximum cost of a knapsack with current weight i, and items with indices no more than j are available for the knapsack. Then:

`d[i][j]= d[i][j-1]` (if the jth item is not taken)

`d[i][j]= d[i-w_j][j-1] + P_j` (if the jth item is taken)

Complexity: O(n * capacity)
