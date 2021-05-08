#include "structs.h"
#include "dijikstra.c"
#include"graph.h"
#include"string-hash.h"


void update_cars(struct Graph* g,int i,int time,StrHash hash){
    if(time=car[i].time_to_change && car[i].location_ptr<car[i].num_streets){ //if the car has reached the end of the edge and it still has more edge(s) to cover
        //**Naval->  update_edge(car[i].names_of_streets[location_ptr]) decrease by 1
        long long index = Find_StrHash(hash,car[i].names_of_streets[car[i].location_ptr]) ;
        decreaseCongestion(g,hash->bkt_arr[index].v1,hash->bkt_arr[index].v2);
        car[i].location_ptr++;
        //**Naval->  update_edge(car[i].names_of_streets[location_ptr]) increase by 1
        increaseCongestion(g,hash->bkt_arr[index].v1,hash->bkt_arr[index].v2);
        car[i].time_to_change+= calc_time((long long)hash->bkt_arr[index].congestion,(long long)hash->bkt_arr[index].length);/* obtain using car[i].names_of_streets[location_ptr])*/
    }
}

int update_myloc(struct Graph*g ,int time,int dest,StrHash hash){
    if(time=me.time_to_change){ //if my car has reached the end of a street
        //me.curr_street=
        //me.curr_node= //update, obtain the current node from street end
        int currindex = Find_StrHash(hash,me.curr_street); 
        StrHash_NODE  a = hash->bkt_arr[currindex] ;
        decreaseCongestion(g,a.v1,a.v2);
        me.curr_node = a.v2;

        Stack s = dijikstra(g,me.curr_node,dest);
        int new;
        struct Edge* e  = g->array[me.curr_node].head;
        while(e!=NULL)
        {
            if(e->dest == peek(&s))
            {
                break;
            }
            e = e->next;
        }
        strcpy(me.curr_street,e->name);

     

        //update congestion values for both nodes 
        int next_index = Find_StrHash(hash,me.curr_street);
        StrHash_NODE next = hash->bkt_arr[next_index];
        me.time_to_change+= calc_time(next.congestion,next.length);/* obtain using car[i].names_of_streets[location_ptr])*/

        increaseCongestion(g,next.v1,next.v2);

        printf("Our path is %s\n",next.str);
        return 1;
    }
    return 0;
}

long long int calc_time(long long int cars,long long int length){
    long long int factora=1000;
    long long int factorb= 1;
    long long int time = cars*cars/factora + length*factorb;
    return time;
}

void routing(struct Graph* g,StrHash hash){
    long long int time=0;
    int dest=10;        // we still have to take dest as input (main --> routing -->update_myloc)
    int have_i_reached_node=0; //a flaf varriable to know if we've crossed a street or not
    while(1){
        time++;
        for(int i=0;i<number_of_vehicles;i++){               //number_of_vehicles stands for the number of cars
            update_cars(i,time,hash);            //updates the location of each individual car and the edge weights accordingly
        }
        have_i_reached_node=update_myloc(g,time,dest,hash); //update 'me' variable, i.e. details of my car
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

