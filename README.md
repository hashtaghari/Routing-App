# Routing-Grp-26
##How to use the code.

This is the Github Repository of the DSA mini project of Group 26, UG2K20, IIIT Hyderabad 
To compile, use gcc Main.c .\graph.c .\stack.c .\string-hash.c .\heap.c 
Make sure you have python installed and the graphing library installed (using pip install networkx matplotlib as root)

When you open the program, it will show the main menu. Enter "1" in the main menu to enter the details in order to create the map of the city with the traffic data. You will be redirected to a sub-menu which then asks how you wish to enter your input. You have the option to either manually enter the input or fill in the input directly from a text file. We have provided some sample txt files in the "data" folder which you may use as sample inputs to test the code(a,b,c,d,f are from a google hashcode problem, proof1a,proof1b,sampletc1-sampletc5 are some test cases we've provided). If you choose to enter the details from let's say the input file "a.txt", enter "a" to read the graph input from the file. Given below is the input format if you wish to enter the details manually. You will be sent back to the main menu after you sucessfully fill in the map data.

##Input format:
The first input line contains five numbers:

      an integer D ( 1 ≤ D ≤ 10 4 ) - the duration of the simulation, in seconds,//We won't be making use of this input, but we take it in as we're using test cases from Google Hashcode
      an integer I (2 ≤ I ≤ 10 5) - the number of intersections (with IDs from 0 to I -1) ,
      an integer S (2 ≤ S ≤ 1 0 5) - the number of streets,
      an integer V (1 ≤ V ≤ 1 0 3) - the number of cars,
      an integer F (1 ≤ F ≤ 103 ) - the bonus points for each car that reaches its destination before time D.//We won't be making use of this input, but we take it in as we're using test cases from Google Hashcode
     
The next S lines contain descriptions of streets. Each line contains:

      two integers B and E (0 ≤ B < I , 0 ≤ E < I) - the intersections at the start and the end of the street, respectively,
      the street name (a string consisting of between 3 and 30 lowercase ASCII characters a - z and the character -),
      an integer L (1 ≤ L ≤ D ) - the time i t takes a car to get from the beginning to the end of that street.
      
The next V lines describe the paths of each car. Each line contains:

      an integer P (2 ≤ P ≤ 103 ) - the number of streets that the car wants to travel,
      followed by P names of the streets: The car start at the end of the first street (i.e. it waits for the green light to move to the next street) and follows the path until the end of the last street. The path of a car is always valid, i.e. the streets will be connected by intersections.

##Using the map and the traffic data to find the best route for you to travel

Enter "3" in the main menu to enter the routing function
It will ask you to enter the Starting intersection you are at and your destination. Enter the two integer numbers (0<= inputs <I)
Then the algorthms will compute the most optimal path and show you the next road you must take. An imaage will pop out which contains the pictorical representation of the graph. The road you must tread will be highlighted in in the graph showing the map of the city. Once you close the prompt, it will show you the name of the next node you must take. All the traffic data is updated in real time and this program will take you to your destination in the minimum possible time (as this program keeps account of the total distance as well as the congestion of every road in mind). 
##Additional feature: Suppose a node is blocked due to any unforeseen circumstances, the program will ask you if the road ahead is free. If you say that it is not, it will compute a different path for you if a better path exists. 
