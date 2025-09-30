#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int id;
    char name[50];
    int age;
}user;

//Function to Add User.
void AddUser(){
    FILE *fp=fopen("user.txt","a+");
    if(!fp){
        printf("Error: Unable to create file!\n");
        return;
    }

    int ID;
    user u;
    printf("Enter ID: ");
    scanf("%d",&ID);

    rewind(fp);
    while(fscanf(fp,"%d\t%s\t%d\n",&u.id,u.name,&u.age)==3){
        if(u.id==ID){
            printf("User with ID=%d already exists.\n",ID);
            fclose(fp);
            return;
        }
    }
    u.id=ID;
    printf("Enter Name: ");
    scanf("%s",u.name);
    printf("Enter Age: ");
    scanf("%d",&u.age);
    
    fprintf(fp,"%d\t%s\t%d\n",u.id,u.name,u.age);
    printf("Added Successfully!\n");
    fclose(fp);
}

//Function to Display Users.
void DisplayUsers(){
    FILE *fp=fopen("user.txt","r");
    if(!fp){
        printf("No users added!\n");
        return;
    }

    user u;
    printf("ID\tNAME\tAGE\n");
    while(fscanf(fp,"%d\t%s\t%d\n",&u.id,u.name,&u.age)==3){
        printf("%d\t%s\t%d\n",u.id,u.name,u.age);
    }

    printf("All Details Displayed!\n");
    fclose(fp);
}

//Function to Update Users.
void UpdateUser(){
    FILE *fp=fopen("user.txt","r");
    if(!fp){
        printf("No users added!\n");
        return;
    }

    int ID;
    printf("Enter user ID to be updated: ");
    scanf("%d",&ID);

    user u[100];
    int count=0;
    while(fscanf(fp,"%d\t%s\t%d\n",&u[count].id,u[count].name,&u[count].age)==3){
        count++;
    }
    fclose(fp);

    int found=0;
    fp=fopen("user.txt","w");
    for(int i=0;i<count;i++){
        if(u[i].id==ID){
            printf("Enter name: ");
            scanf("%s",u[i].name);
            printf("Enter age: ");
            scanf("%d",&u[i].age);
            found=1;
        }
        fprintf(fp,"%d\t%s\t%d\n",u[i].id,u[i].name,u[i].age);
    }
    fclose(fp);

    if(found==0){
        printf("User not found!\n");
    }
    else{
        printf("Updated Successfully!\n");
    }
}

//Function to Delete Users.
void DeleteUser(){
    FILE *fp=fopen("user.txt","r");
    if(!fp){
        printf("No users added!\n");
        return;
    }

    int ID;
    printf("Enter user ID to be Removed: ");
    scanf("%d",&ID);

    user u[100];
    int count=0;
    while(fscanf(fp,"%d\t%s\t%d\n",&u[count].id,u[count].name,&u[count].age)==3){
        count++;
    }
    fclose(fp);

    int found=0;
    fp=fopen("user.txt","w");
    for(int i=0;i<count;i++){
        if(u[i].id==ID){
            found=1;
            continue;
        }
        fprintf(fp,"%d\t%s\t%d\n",u[i].id,u[i].name,u[i].age);
    }
    fclose(fp);

    if(found==0){
        printf("User not found!\n");
    }
    else{
        printf("Deleted Successfully!\n");
    }
}




int main(){
    int option;

    while(1){
        printf("\n\n---------USER FILE----------\n");
        printf("1.Add a new user to the file.\n");
        printf("2.Display all users stored in the file.\n");
        printf("3.Modify the details based on ID.\n");
        printf("4.Remove the user based on ID.\n");
        printf("Enter your choice: ");
        scanf("%d",&option);
        switch(option){
            case 1: AddUser();break;
            case 2: DisplayUsers();break;
            case 3: UpdateUser();break;
            case 4: DeleteUser();break;
            default: printf("Invalid Option!");
        }
    }
}
