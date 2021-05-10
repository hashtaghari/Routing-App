#include "structs.h"
#include "dijikstra.c"
#include"graph.h"
#include"string-hash.h"

long long int calc_time(int cars,int length){
    long long int factora=1;
    long long int factorb= 1;
    long long int time = (long long int)cars*(long long int)cars/factora + (long long int)length*factorb;
    return time;
}

void update_cars(struct Graph* g,int i,int time,StrHash hash){
    if(time==car[i].time_to_change && car[i].location_ptr<car[i].num_streets){ //if the car has reached the end of the edge and it still has more edge(s) to cover
        //**Naval->  update_edge(car[i].names_of_streets[location_ptr]) decrease by 1
        long long index = Find_StrHash(hash,car[i].names_of_streets[car[i].location_ptr]) ;//finding the index of the edge where the car currently is at using a hash function

        hash->bkt_arr[index].congestion--;//decreasing the traffic at the street(edge) by 1 as the car has crossed it(in hash table)
        decreaseCongestion(g,hash->bkt_arr[index].v1,hash->bkt_arr[index].v2);//decreasing the traffic at the street(edge) by 1 as the car has crossed it(in the graph)

        car[i].location_ptr++;//updating the car's location to it's next path

       
        index = Find_StrHash(hash,car[i].names_of_streets[car[i].location_ptr]) ;//finding the index of the edge where the car currently is at using a hash function

        hash->bkt_arr[index].congestion++;//increasing the traffic at the street(edge) by 1 as the car has just entered it(in hash table)
        increaseCongestion(g,hash->bkt_arr[index].v1,hash->bkt_arr[index].v2);//increasing the traffic at the street(edge) by 1 as the car has just entered it(in the graph)
        car[i].time_to_change+= calc_time((long long)hash->bkt_arr[index].congestion,(long long)hash->bkt_arr[index].length);//updating the time it'll take for the car to cross the current street as a function of congestion and length of the street
    }
}

int update_myloc(struct Graph*g ,int time,StrHash hash,int dest){
    char is_free;
    is_free='y';
    StrHash_NODE n_node;
    FILE * fp = fopen(".\\data\\curr_edge.txt","w");
    if(time==me.time_to_change){ //if my car has reached the end of a street
        
        do{
            if(is_free=='n' || is_free=='N'){
                //printf("modified**");
                updateEdge(g,me.curr_node,n_node.v2,100);//updating the newly obtained congestion information(in graph)
                long long node_ind = Find_StrHash(hash,me.curr_street);
                hash->bkt_arr[node_ind].congestion = 100;//updating the newly obtained congestion information(in graph)
            }
        int currindex = Find_StrHash(hash,me.curr_street); //obtaing the index of the information stored about the edge using hash function via the edge name
        StrHash_NODE  a = hash->bkt_arr[currindex];//saving the deatils about the edge in the variable 'a'

        hash->bkt_arr[currindex].congestion--;//decreasing the congestion of the road we crossed by 1 in the hash table
        decreaseCongestion(g,a.v1,a.v2);//decreasing the congestion of the road we crossed by 1 in the graph

        me.curr_node = a.v2;//updating the current node we are at
        // printf("a.v2 = %d \n",a.v2);

        Stack s = dijikstra(g,me.curr_node,dest);//applying dijkstra's algorithm between current node and the destination node to find out the best route 
        
        struct Edge* e  = g->array[me.curr_node].head;//finding out the name of the edge using current node and next node to travel
        while(e!=NULL)
        {
            if(e->dest == peek(&s))
            {
                break;
            }
            e = e->next;
        }
        strcpy(me.curr_street,e->name);//updating information about the current node
      
        
        int next_index = Find_StrHash(hash,me.curr_street);//obtaining information about the next street to travel using the hash function and saving it to the variable 'next'
        StrHash_NODE next = hash->bkt_arr[next_index];
       
        me.time_to_change+= calc_time(next.congestion,next.length);//updating the time it'll take to reach the end of this street as a function of length and congestion
        
        hash->bkt_arr[next_index].congestion++;//increasing congestion by 1 in new street (hash table)
        increaseCongestion(g,next.v1,next.v2);//increasing congestion by 1 in new street (graph)

        printf("\n\nYou are currently at intersection : %d",me.curr_node);//printing the current location
        printf("\nThe next route  you must take is : %s",me.curr_street);//suggesting the next path to tread
        
        fprintf(fp,"%s\n",me.curr_street);//writing the name of the next edge on a file so that it can be used by visualise.py to highlight suggested path
        fclose(fp);
        
        if(g->V <= 100 || g->E <=100 ) //printing the graph if the number of nodes/edges isn't too large
        {
            system("python .\\visualize.py");
        }
        else
        {
            getch();
        }
        printf("\n Is the path ahead avalible to travel? (Y/N): ");
        scanf(" %c",&is_free);
        n_node.v2=next.v2;
        } while(is_free=='N'||is_free=='n'); //loop runs again with updated congestion information obtained just now and tries to find  a new path if it exists
          
        
        if(n_node.v2==dest)//if the next node is our destination return 1, else return 0
        return 1;
        else
        return 0;
    }
    return 0;
}



void routing(struct Graph* g,StrHash hash,int dest){
    StrHash_NODE n_node;
    FILE* fp = fopen(".\\data\\curr_edge.txt","w"); //opening text file to give information to visualise.py
    system("cls");
    // initialising conditions for simulation time 'time'=0
    
    for (int i = 0; i < Ncars; i++)//updating the initial information about each car
    {
        car[i].location_ptr = 1; //updating the initial location of the car
        int index = Find_StrHash(hash,car[i].names_of_streets[car[i].location_ptr]) ;//finding the details of the edge by using a hashing function
        hash->bkt_arr[index].congestion++;//increasing the traffic on that street(edge) by 1 on the hash table
        increaseCongestion(g,hash->bkt_arr[index].v1,hash->bkt_arr[index].v2);//increasing the traffic on that street(edge) by 1 on the graph

        car[i].time_to_change = calc_time((long long)hash->bkt_arr[index].congestion,(long long)hash->bkt_arr[index].length);//calculating the time it'll take for the car to reach 
        
    }
    char is_free;
    is_free='y';
    do{
            if(is_free=='n' || is_free=='N'){
                 //printf("modified**");
                updateEdge(g,me.curr_node,n_node.v2,100);//updating the newly obtained congestion information(in graph)
                long long node_ind = Find_StrHash(hash,me.curr_street);
                hash->bkt_arr[node_ind].congestion = 100;
            }
    Stack s3 = dijikstra(g,me.curr_node,dest) ;//applying dijkstra's algorithm to find out the best possible route from starting node to destinartion
    //the following ~30 lines are the same as the update_myloc funciton, except that this is filling up the data for initial conditions when time t=0
    //please refer to update_myloc(___) function to understand what each command achieves 
    struct Edge* e1  = g->array[me.curr_node].head;
    while(e1!=NULL)
    {
        if(e1->dest == peek(&s3))
        {
            break;
        }
        e1 = e1->next;
    }
    strcpy(me.curr_street,e1->name);
    
    //update congestion values for both nodes 
    int next_index = Find_StrHash(hash,me.curr_street);
    StrHash_NODE next = hash->bkt_arr[next_index]; //next has information about the edge
    me.time_to_change= calc_time(next.congestion,next.length);/* obtain using car[i].names_of_streets[location_ptr])*/
    hash->bkt_arr[next_index].congestion++;
    increaseCongestion(g,next.v1,next.v2);
    printf("\n\nYou are currently at intersection : %d",me.curr_node);
    printf("\nThe next route you must take is : %s",me.curr_street);
    // printf("\n initalised conditions");
    fprintf(fp,"%s\n",me.curr_street);
    fclose(fp);
    
    if(g->V <= 100 || g->E <=100 )
    {
    system("python .\\visualize.py");
    }
    else
    {
        printf("\nMap size is too large to be depicted.\n");
    }
    printf("\n Is the path ahead avalible to travel? (Y/N): ");
        scanf(" %c",&is_free);
        n_node.v2=next.v2;
        } while(is_free=='N'||is_free=='n');
    long long int time=0; //setting the simulation time to 0
    int have_i_reached_node=0; //a flag varriable to know if we've crossed a street or not
    // printf("%d %d %lld\n",me.curr_node,me.end_node,me.time_to_change);
    if(n_node.v2==dest)
        goto L1;
    while(1){
        time++;//increasing the time unit by 1
        // printf("\n %lld",time);
        have_i_reached_node = 0;
        for(int i=0;i<Ncars;i++){               //updates the location for every car and the changes in edge weights are accounted for in this loop
            update_cars(g,i,time,hash);            //updates the location of each individual car and the edge weights accordingly
        }
        // printf("\n%d %d %lld\n",me.curr_node,me.end_node,me.time_to_change);
        have_i_reached_node=update_myloc(g,time,hash,dest); //update 'me' variable, i.e. details of my car

        if(have_i_reached_node==1){
            L1:
            printf("\n\nYou are currently at intersection : %d",me.curr_node);
            printf("\nYou have reached your destination");
            printf("\n(Press any key to continue)");
            getch();
            break;
        }
    }
}

