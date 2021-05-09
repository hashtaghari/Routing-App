# Routing-Grp-26
This is the Github Repo of the DSA mini project of Group 26. 
To compile, use gcc Main.c .\graph.c .\stack.c .\string-hash.c .\heap.c

Input format:

The first contains five numbers:

      an integer D ( 1 ≤ D ≤ 10 4 ) - the duration of the simulation, in seconds,
      an integer I (2 ≤ I ≤ 10 5) - the number of intersections (with IDs from 0 to I -1) ,
      an integer S (2 ≤ S ≤ 1 0 5) - the number of streets,
      an integer V (1 ≤ V ≤ 1 0 3) - the number of cars,
      an integer F (1 ≤ F ≤ 103 ) - the bonus points for each car that reaches its destination before time D.
     
The next S lines contain descriptions of streets. Each line contains:

      two integers B and E (0 ≤ B < I , 0 ≤ E < I) - the intersections at the start and the end of the street, respectively,
      the street name (a string consisting of between 3 and 30 lowercase ASCII characters a - z and the character -),
      an integer L (1 ≤ L ≤ D ) - the time i t takes a car to get from the beginning to the end of that street.
      
The next V lines describe the paths of each car. Each line contains:

      an integer P (2 ≤ P ≤ 103 ) - the number of streets that the car wants to travel,
      followed by P names of the streets: The car start at the end of the first street (i.e. it waits for the green light to move to the next street) and follows the path until the end of the last street. The path of a car is always valid, i.e. the streets will be connected by intersections.
