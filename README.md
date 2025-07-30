
# Big Integer in C++

this is ***not*** a solution to a course assignment for Intro to Data Structures for sure : 33333

So the goal of this project is really simple, implement a BigInteger class in C++ where numbers are initially given as a `std::string`, numbers may or may not be signed with a **-** or **+**.

I decided to represent a big integer `N` as a doubly linked list of base `10 ^ p` digits, for example:

1123456 when `p = 3` becomes (1)<->(123)<->(456)

I chose doubly cause it kind of made to_stringing easier and also for one bit of subtraction I had to remove leading zeroes 

something something I'll explain later 


And with that base setup we can implement basic arithmetic operations `add(), subtract(), and multiply`

# Constructor Method

Although I think I could've realistically just used a vector to hold all the digits, and it'd likely outperform my own dodgy linked list implementation, and it'd also be way easier, uhhh idk mane I'm learning C++

So like previously said we initialize BigInteger objects with an input String `s` and we can just perform a `O(n)` pass over `s` grouping up digits of size `p` to form nodes within the underlying linked list.

The only added complexity is the signage of `s` but that's a simple if statement check.

# Addition (and Subtraction)

Basic positive addition / subtraction is a pretty simple `O(max(m,n))` operation where m,n are the lengths of the two Big Integers, I literally stole my Leetcode #2 solution to implement this.

The problem is you get a mix in signs like subtraction a negative etc.

To avoid writing a bunch of extra stuff I set to handle the `add()` method to only handle same sign operations
and `subtract()` to hand cases where the signs are different

Since adding two negatives is the same as adding two positives, and it's easy for my elementary school brain to think positive - negative


## Table of signs where p = positive, n = negative

| Use Addition         | Use Subtraction                                                              |
| ----------------- | ------------------|
| p + p | n - n|
| p - n | p + n|
| n + n | p - p|
| n - p | n + p|

So using conditional logic junk I compare signs to flip flop between the right function to use according to the Table

And just do Leetcode #2, go through each node, combine, and do any carryover to the next node.

# Multiplication

So while researching for this implementation I saw a lot of fuckass algorithims that I didn't want to bother learning

So I just went for the elementary school style `O(m * n)` operations style.

Let's do an example, imagine multiplying 12 with 12

Using standard algorithim with 2 multiply it with every digit resulting in 24, then you'd go to 1 do the same thing

but shift it left 1 digit with a 0 resulting in 120

and it'd look like

          13

        x 12
       --------------
          26
         13<-
         156 :3

But seeing this we can observe that the product of a digit at index `i` from 12 and a digit at `j` from 13 gets added with the product of any pair of digits at indicies `p` and `k` such that `i + j == p + k` 

Or like if we were storing the results of digit to digit products in a vector 
```
    std::vector<int> res(m + n); //where m,n are lengths of 2 numbers
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++) res[i + j] += num1[i] * num2[j]
    }
```

So that's literally what I did since it applies to numbers with base `10 ^ p` digits and probably any base digits idk

After storing all those products in a vector I just went through created nodes for the list and return a new BigInteger object ;3

It could be considered cheap to use a seperate ADT in my own ADT, but this way is really easy :3333

Without using a vector I'd think you'd have to manage another linked list where you're continously shifting it left by `p` digits
 
and like the vector way wins out on readablity and performance (probably) so yiayyyy

# Final stuff

Some things about the project is it was compiled using msys64 on windows with g++, for some reason the long max value is the same as int so to avoid overflow I had to use long long. On your machine you'll likely be fine using just long though.

Also I was mostly using the to_string() to check proper creation of objects, since it's called a lot and initializing is usually started with a string it would've made more sense to just return an `origin` string and whenever I was arithmeticing it and by it I mean my BigInteger just construct the string there, but this is all committed so pluh :3333.




