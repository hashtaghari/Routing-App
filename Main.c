#include "Main.h"
#include "UI.c"
#include"graph.h"
#include"routing.c"
#include"stack.h"
#include"Heap.h"
#include"string-hash.h"

int main(){
    restore_values();//restores all the variable information from txt files.
    int menu_entry;
    struct Graph *g;
    StrHash hash = Init_StrHash((int)10e5);
    loading_animation();
    intro_animation();
    do{
        main_menu();
        scanf("%d",menu_entry);
        switch(menu_entry){
            case 1:
                g = add_map();
                for(int i=0;i<g->V;i++)
                {
                    struct Edge*e = g->array[i].head;
                    while (e!=NULL)
                    {
                        Insert_StrHash(hash,e->name,i,e->dest,e->Length,e->Length);
                        e=e->next;
                    }
                }
                break;
            case 2:
                modify_map_usr(g);
                break;
            case 3:
                routing(g,hash);
                break;
            case 4:
                instruction();
                break;
            case 5:
                about_us();
                break;
            case 6:
                printf("\nThank you for using our Routing Guide!");
                delay(1500);
                break;
            default:
                printf("\n Invalid Entry! (Press any key to continue)");
                getch();
                break;
        }
    }while(menu_entry!=6);
    //save all the required variable data in different files as per the plan so that it can be retained after the program is closed.
    return 0;
}

struct Graph* add_map(){
    system("cls");
    printf("How do you want to enter input?");
}



