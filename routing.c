#include "structs.h"
#include "dijikstra.c"


void update_cars(int i,int time){
    if(time=car[i].time_to_change && car[i].location_ptr<car[i].num_streets){ //if the car has reached the end of the edge and it still has more edge(s) to cover
        //**Naval->  update_edge(car[i].names_of_streets[location_ptr]) decrease by 1
        car[i].location_ptr++;
        //**Naval->  update_edge(car[i].names_of_streets[location_ptr]) increase by 1
        car[i].time_to_change+= calc_time(/*length,congestion*/);/* obtain using car[i].names_of_streets[location_ptr])*/
    }
}

int update_myloc(int time){
    if(time=me.time_to_change){ //if my car has reached the end of a street
        //me.curr_street=
        //me.curr_node= //update, obtain the current node from street end

        //update congestion values for both nodes 
        me.time_to_change+= calc_time(/*length,congestion*/);/* obtain using car[i].names_of_streets[location_ptr])*/
    }
}

long long int calc_time(long long int cars,long long int length){
    long long int factora=1000;
    long long int factorb= 1;
    long long int time = cars*cars/factora + length*factorb;
    return time;
}

void routing(){
    long long int time=0;
    int have_i_reached_node=0; //a flaf varriable to know if we've crossed a street or not
    while(1){
        time++;
        for(int i=0;i<v;i++){               //v stands for the number of cars
            update_cars(i,time);            //updates the location of each individual car and the edge weights accordingly
        }
        have_i_reached_node=update_myloc(time); //update 'me' variable, i.e. details of my car
        if(me.curr_node==destination){
            printf("You have reached your destination");
            break;
        }
        if(have_i_reached_node){
            //**apply dijikstra**  @naval  dijikstra(me.curr_node,destination)
            //print next path 
            printf("\n Is the path ahead avalible to travel? (Y/N)");
            scanf("%c",is_free);
            if(is_free=='N' || 'n'){
                //modify the suggested path edge weight->infinity
                //dijikstra(me.curr_node,destination) // if no path available say->can't find any path 
            }
        }
    }
}

