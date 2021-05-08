#include "Main.h"
#include "UI.c"

int main(){
    restore_values();//restores all the variable information from txt files.
    int menu_entry;
    loading_animation();
    intro_animation();
    do{
        main_menu();
        scanf("%d",menu_entry);
        switch(menu_entry){
            case 1:
                add_map();
                break;
            case 2:
                modify_map_usr();
                break;
            case 3:
                route();
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

void add_map(){
    system("cls");
    printf("How do you want to enter input?");
}


