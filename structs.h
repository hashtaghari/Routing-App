#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct car_info cars; //the datatype that contains the details of each individual car
//typedef struct street_info streets;


int intersection_ID[100000];

struct car_info{ 
    int num_streets; //the number of streets a particular car is going to travel
    char names_of_streets[1001][31]; //the path of the car stored in an array
    int location_ptr;   // the indicator of the progress made in the path of the car(which is stored in the array names_of_streets[][])
    long long int time_to_change; //an idicator to check if the car has crossed the street
    // int car_ID; //the ID of each car, probably not required but here just in case
};

struct my_car{
    int start_node; //starting intersection/node of our travel
    int end_node; //Destination node
    int curr_node;//the current node we're at/the previous node we were at if still on an edge
    char curr_street[31];//the current edge we are at
    long long int time_to_change; //an idicator to check if the car has crossed the street
};

/* struct street_info{
    int start_node; //the starting node(intersection) of the street
    int end_node; //the ending node(intersection) of the street
    long long int length; //length of the street as given in the input, this stays constant throughout the program after initialisation
    long long int congestion;//the number of cars in the street at any given time 't'. This changes dynamically as the traffic moves across the map
};  */ //not using this data structure anymore


cars car[1000]; // an array containg all the informaion about each individual car on the street
//streets street[100000]; //an array containing the information of all the streets as entered by the user
struct my_car me;
#endif