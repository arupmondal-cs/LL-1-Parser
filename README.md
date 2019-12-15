## LL(1) Parser


In this project I am implement the LL(1) parser in **C**.

Here the 1st L represents that the scanning of the Input will be done from Left to Right manner and second L shows that in this Parsing technique we are going to use Left most Derivation Tree. and finally the 1 represents the number of look ahead, means how many symbols are you going to see when you want to make a decision.

**Construction of LL(1) Parsing Table:**

  To construct the Parsing table, we have two functions:
  
   1.  [First()](https://www.geeksforgeeks.org/first-set-in-syntax-analysis/): If there is a variable, and from that variable if we try to drive all the strings then the beginning Terminal Symbol is called the first.
   
   2.  [Follow()](https://www.geeksforgeeks.org/follow-set-in-syntax-analysis/): What is the Terminal Symbol which follow a variable in the process of derivation.
