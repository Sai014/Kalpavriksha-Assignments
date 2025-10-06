#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_USERS 100

typedef struct {
    int id;
    char name[50];
    int age;
}user;

int isDuplicateID(int id) {
    FILE *fp = fopen("user.txt","r");
    if(!fp) return 0;

    user u;
    while(fscanf(fp,"%d\t%[^\t]\t%d\n",&u.id,u.name,&u.age)==3){
        if(u.id == id){
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

user getUser(int id){
    user u;
    u.id = id;

    while(getchar() != '\n');

    printf("Enter Name: ");
    fgets(u.name, sizeof(u.name), stdin);
    printf("Enter Age: ");
    scanf("%d",&u.age);
    u.name[strcspn(u.name, "\n")] = 0;
    return u;
}

int countUsers(FILE *fp,user u[]){
    int count=0;
    while(fscanf(fp,"%d\t%[^\t]\t%d\n",&u[count].id,u[count].name,&u[count].age)==3){
        count++;
    }
    return count;
}





//Function to Add User.
void AddUser(){
    int ID;
    printf("Enter ID: ");
    scanf("%d",&ID);

    if(isDuplicateID(ID)){
        printf("User with ID=%d already exists.\n",ID);
        return;
    }

    FILE *fp=fopen("user.txt","a+");
    if(!fp){
        printf("Error: Unable to create file!\n");
        return;
    }

    user u=getUser(ID);
    
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
    while(fscanf(fp,"%d\t%[^\t]\t%d\n",&u.id,u.name,&u.age)==3){
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

    user u[MAX_USERS];
    int count=countUsers(fp,u);
    fclose(fp);

    int found=0;
    fp=fopen("user.txt","w");
    for(int i=0;i<count;i++){
        if(u[i].id==ID){
            u[i]=getUser(ID);
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

    user u[MAX_USERS];
    int count=countUsers(fp,u);
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
        printf("5.Exit\n");
        printf("Enter your choice: ");
        if(scanf("%d",&option) != 1){
            printf("Invalid Input! Enter a number.\n");
            while(getchar()!='\n');
            continue;
        }
        switch(option){
            case 1: AddUser();break;
            case 2: DisplayUsers();break;
            case 3: UpdateUser();break;
            case 4: DeleteUser();break;
            case 5: exit(0);
            default: printf("Invalid Option!");
        }
    }
}
