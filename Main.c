int Ncars; //The number of cars.
#include "UI.c"
#include "graph.h"
#include "routing.c"
#include "stack.h"
#include "Heap.h"
#include "string-hash.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

struct Graph *add_map();
void about_us();

int main()
{
    int dest; //destination node to obtain input and send to routing function
    // restore_values();//restores all the variable information from txt files.
    int menu_entry;
    struct Graph *g;
    StrHash hash = Init_StrHash((int)10e5);
    // loading_animation();
    // intro_animation();
    do
    {
        main_menu();
        scanf("%d", &menu_entry);
        // printf("%d",menu_entry);
        switch (menu_entry)
        {
        case 1:
            g = add_map();
            for (int i = 0; i < g->V; i++)
            {
                struct Edge *e = g->array[i].head;
                while (e != NULL)
                {
                    Insert_StrHash(hash, e->name, i, e->dest, e->Length, e->Length);
                    e = e->next;
                }
            }
            break;
        case 2:
            // modify_map_usr(g);
            break;
        case 3:
            system("cls");
            printf("\n Enter Your Start Node:");
            scanf("%d", &me.start_node);
            me.curr_node = me.start_node;
            printf("\n Enter Your Destination Node:");
            scanf("%d", &dest);
            me.end_node = dest;
            routing(g, hash, dest);
            break;
        case 4:
            system("README.md");
            break;
        case 5:
            about_us();
            break;
        case 6:
            printf("\nThank you for using our Routing Guide!");
            // delay(1500);
            break;
        default:
            printf("\n Invalid Entry! (Press any key to continue)");
            getch();
            break;
        }
    } while (menu_entry != 6);
    //save all the required variable data in different files as per the plan so that it can be retained after the program is closed.
    return 0;
}

struct Graph *add_map()
{

    //Keeping the code interactive to a point such that the user has the option to decide how they wish to input the necessary deails.
    printf("Choose as to how you wish to input:\n\t1.\tManually\n\t2.\tFile\n");
    struct Graph *graph;
    //Inputting the value of choice which will be used for splitting the code depending upon the way the information wiil be inputted.
    int choice;
    scanf("%d", &choice);
    //The two main choice given are by file, shown by '2' or done manually, pointed by '1'.
    if (choice == 1)
    { // In case the user wishes to input the information themselves.

        //Maps out the duration of the simulation.
        int D;
        //The number of intersections in the graph.
        int I;
        //The number of streets.
        int S;
        //Scores the bonus points for cars reaching their destination before the duration D.
        int F;
        //Intersection at the start of a given street.
        //To be inputted S times.
        int B;
        //Intersection at the end of a given street.
        //To be inputted S times.
        int E;
        //Time taken for a car reach from the beginning to the end of the given street.
        //To be inputted S times.
        int L;
        //The number of streets the car wants to travel.
        //To be inputted V times.
        int P;

        //The name of each individual street.
        //To be inputted S times.
        char streetName[31];

        //We first need 5 integer inputs.
        printf("Input the 5 values:\n");
        scanf("%d %d %d %d %d", &D, &I, &S, &Ncars, &F);
        printf("5 values inputted\n");

        graph = createGraph(I);

        //For the next S lines, we need 1 string and 3 integer inputs.
        for (int y = 0; y < S; ++y)
        {
            printf("Input details for street %d:\n", y);
            scanf("%d %d %s %d", &B, &E, streetName, &L);
            addEdge(graph, B, E, L, streetName, 0);
            printf("Added details for street %d\n", y);
        }

        //For the next V lines, we need a varying number of inputs, which depend on the first input, which is an integer.
        for (int y = 0; y < Ncars; ++y)
        {
            printf("Input details for car %d:\n", y);
            scanf("%d", &P);
            car[y].num_streets = P;
            for (int z = 0; z < P; ++z)
            {
                scanf("%s", streetName); //Takes in each individual name of the street a said car will travel through.
                strcpy(car[y].names_of_streets[z], streetName);
            }
            // car[y].location_ptr = car[y].names_of_streets[0];
            car[y].time_to_change = 0;
            printf("Added details for car %d\n", y);
        }
    }
    else if (choice == 2)
    { //In case the user wishes the information to be inputted by the use of a file.

        //Just like how int is used for integer value and float is used for float values,
        //FILE format is used for files.
        //A FILE pointer is made in the following line of code and is named fpointer.
        FILE *fPointer;

        //We have given the user the option to input either through the terminal or by file.
        //In this particular case, the input is done through a file.
        //Due to the fact that the file name is not known earlier on, the name and location or path
        //of the file needs to inputted onto the terminal when the code is being run.
        //The path will be inputted in the form of a string.
        char ext[6] = ".txt";
        char path[100] = "./data/";
        char fNameNLoc[200];
        printf("Enter file name : ");
        scanf("%s", fNameNLoc);

        strcat(path, fNameNLoc);
        strcat(path, ext);

        // printf("complete path : %s",path);

        //The FILE pointeer created earlier points to a the file with the path fNameNLoc.
        //The fopen function opens the file.
        //The second parameter which says "r" signifies that the file has been opened in a read ode.
        fPointer = fopen(path, "r");

    
        //This variable, abbreviation of "Number of Lines", keeps track of which line of file
        //is being read by the processor at that present moment.

        //Maps out the duration of the simulation.
        int D;
        //The number of intersections in the graph.
        int I;
        //The number of streets.
        int S;

        //Scores the bonus points for cars reaching their destination before the duration D.
        int F;
        //Intersection at the start of a given street.
        //To be inputted S times.
        int B;
        //Intersection at the end of a given street.
        //To be inputted S times.
        int E;
        //Time taken for a car reach from the beginning to the end of the given street.
        //To be inputted S times.
        int L;
        //The number of streets the car wants to travel.
        //To be inputted V times.
        int P;

        //The name of each individual street.
        //To be inputted S times.
        char streetName[31];

        //The file pointer begins at the exact start of the file.
        //The while loop runs and goes through each individual line to read the entire file.

        int y = 0;
        fscanf(fPointer, "%d %d %d %d %d", &D, &I, &S, &Ncars, &F);
        graph = createGraph(I);
        for (int y = 0; y < S; ++y)
        {
            fscanf(fPointer, "%d %d %s %d", &B, &E, streetName, &L);
            addEdge(graph, B, E, L, streetName, 0);            
        }

    
        for (int y = 0; y < Ncars; ++y)
        {
            fscanf(fPointer, "%d", &P);
            car[y].num_streets = P;
            for (int z = 0; z < P; ++z)
            {
                fscanf(fPointer, "%s", streetName); //Takes in each individual name of the street a said car will travel through.
                strcpy(car[y].names_of_streets[z], streetName);
            }

            car[y].time_to_change = 0;
        }

        fclose(fPointer);
    }
    saveGraph(graph, "g2");
    return graph;
}

void about_us(){
    system("cls");
    printf("This application was created by:\n\n");

    delay(750);
    printf("Hariharan Kalimuthu");
    delay(250);
    printf(" (2020115015)\n\n");
    
    delay(750);
    printf("Naval Surange");
    delay(250);
    printf(" (202011318)\n\n");

    delay(750);
    printf("Priyansh");
    delay(250);
    printf(" (2020101056)\n\n");
    
    delay(750);
    printf("Rajarshi Ray");
    delay(250);
    printf(" (2020101127)\n\n");
    
    delay(750);
    printf("Rohan Reddy B");
    delay(250);
    printf(" (2020102039)\n\n");
    getch();
}