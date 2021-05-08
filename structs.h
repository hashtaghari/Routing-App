#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct car_info cars; //the datatype that contains the details of each individual car
typedef struct street_info streets;


int intersection_ID[100000];

struct car_info{ 
    int num_streets; //the number of streets a particular car is going to travel
    char names_of_streets[1001][31]; //the path of the car stored in an array
    int location_ptr;   // the indicator of the progress made in the path of the car(which is stored in the array names_of_streets[][])
    long long int time_to_change; //an idicator to check if the car has crossed the street
    // int car_ID; //the ID of each car, probably not required but here just in case
};

struct my_car{
    int stat_node; //starting intersection/node of our travel
    int end_node; //Destination node
    int curr_node;//the current node we're at/the previous node we were at if still on an edge
    long long int time_to_change;
};

struct street_info{
    int start_node;
    int end_node;
    long long int length;
    long long int congestion;
};


cars car[1000];
streets street[100000];
struct my_car me;
#endif