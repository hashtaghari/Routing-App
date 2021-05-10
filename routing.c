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
        long long index = Find_StrHash(hash,car[i].names_of_streets[car[i].location_ptr]) ;

        hash->bkt_arr[index].congestion--;
        decreaseCongestion(g,hash->bkt_arr[index].v1,hash->bkt_arr[index].v2);

        car[i].location_ptr++;

        //**Naval->  update_edge(car[i].names_of_streets[location_ptr]) increase by 1
        index = Find_StrHash(hash,car[i].names_of_streets[car[i].location_ptr]) ;

        hash->bkt_arr[index].congestion++;
        increaseCongestion(g,hash->bkt_arr[index].v1,hash->bkt_arr[index].v2);
        car[i].time_to_change+= calc_time((long long)hash->bkt_arr[index].congestion,(long long)hash->bkt_arr[index].length);/* obtain using car[i].names_of_streets[location_ptr])*/
    }
}

int update_myloc(struct Graph*g ,int time,StrHash hash,int dest){
    char is_free;
    FILE * fp = fopen(".\\data\\curr_edge.txt","w");
    if(time==me.time_to_change){ //if my car has reached the end of a street
        //me.curr_street=
        //me.curr_node= //update, obtain the current node from street end
        int currindex = Find_StrHash(hash,me.curr_street); 
        StrHash_NODE  a = hash->bkt_arr[currindex];

        hash->bkt_arr[currindex].congestion--;
        decreaseCongestion(g,a.v1,a.v2);

        me.curr_node = a.v2;
        // printf("a.v2 = %d \n",a.v2);

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
        
        hash->bkt_arr[next_index].congestion++;
        increaseCongestion(g,next.v1,next.v2);

        printf("\n\nYou are currently at intersection : %d",me.curr_node);
        printf("\nThe next route  you must take is : %s",me.curr_street);
        // printf("\n Is the path ahead avalible to travel? (Y/N)");
        fprintf(fp,"%s\n",me.curr_street);
        fclose(fp);

        // scanf("%c",is_free);
        
        // while (is_free=='N' || 'n')
        // {
        //     updateEdge(g,me.curr_node,me.end_node,10000);
        //     dijikstra(g,a.v2,dest);

        // }
        
            // if(is_free=='N' || 'n'){
            //     //modify the suggested path edge weight->infinity
            //     //dijikstra(me.curr_node,destination) // if no path available say->can't find any path 
            // }
        // printf("Our path is %s\n",next.str);
        system("python .\\visualize.py");

        if(next.v2==dest)
        return 1;
        else
        return 0;
    }
    return 0;
}



void routing(struct Graph* g,StrHash hash,int dest){

    FILE* fp = fopen(".\\data\\curr_edge.txt","w");
    system("cls");
    // printf("Entered Rounting");
    for (int i = 0; i < Ncars; i++)
    {
        car[i].location_ptr = 1;
        int index = Find_StrHash(hash,car[i].names_of_streets[car[i].location_ptr]) ;
        hash->bkt_arr[index].congestion++;
        increaseCongestion(g,hash->bkt_arr[index].v1,hash->bkt_arr[index].v2);

        car[i].time_to_change = calc_time((long long)hash->bkt_arr[index].congestion,(long long)hash->bkt_arr[index].length);
        
    }

    Stack s3 = dijikstra(g,me.curr_node,dest) ;
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
    
    system("python .\\visualize.py");

    long long int time=0;
    int have_i_reached_node=0; //a flag varriable to know if we've crossed a street or not
    // printf("%d %d %lld\n",me.curr_node,me.end_node,me.time_to_change);
    if(next.v2==dest)
        goto L1;
    while(1){
        time++;
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
            getch();
            break;
        }
    }
}

