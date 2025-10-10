#include<stdio.h>
#include<stdlib.h>

#define MAX_STUDENTS 100
#define MAX_MARKS 100

//Structure for student.
typedef struct
{
    int RollNo;
    char Name[20];
    int Marks1;
    int Marks2;
    int Marks3;
}students;

void fetchDetails(const int numberOfStudents, students Student[]);
void displayDetails(const int numberOfStudents, students Student[]);
void displayRollNumbers(const int numberOfStudents,int initial);
char gradeCalculator(float Average);
int performanceCalculator(char Grade);
void printPerformance(float Average, int Performance);



int main()
{
    int numberOfStudents;
    printf("Enter the number of students: ");
    scanf("%d",&numberOfStudents);
    if(numberOfStudents<1 || numberOfStudents>MAX_STUDENTS)
    {
        printf("Enter a valid size! (1-100)");
        return 1;
    }
    students Student[numberOfStudents];

    fetchDetails(numberOfStudents,Student);
    displayDetails(numberOfStudents,Student);
    printf("List of Roll numbers(via recurssion): ");
    displayRollNumbers(numberOfStudents,1);
    printf("\n");
    return 0;
}




//Function to fetch all the details of students.
void fetchDetails(const int numberOfStudents, students Student[])
{
    printf("Enter Details: \n");
    for(int i = 0; i < numberOfStudents; i++) {
        do {
            scanf("%d %s %d %d %d", &Student[i].RollNo, Student[i].Name,&Student[i].Marks1, &Student[i].Marks2, &Student[i].Marks3);
            if(Student[i].Marks1 < 0 || Student[i].Marks1 > MAX_MARKS ||
               Student[i].Marks2 < 0 || Student[i].Marks2 > MAX_MARKS ||
               Student[i].Marks3 < 0 || Student[i].Marks3 > MAX_MARKS) 
            {
                printf("Invalid marks! Enter again (0-100):\n");
            }
        } while(Student[i].Marks1 < 0 || Student[i].Marks1 > MAX_MARKS ||
                Student[i].Marks2 < 0 || Student[i].Marks2 > MAX_MARKS ||
                Student[i].Marks3 < 0 || Student[i].Marks3 > MAX_MARKS);
    }
    printf("\n");
}

//Function to display all the details of students.
void displayDetails(const int numberOfStudents, students Student[])
{
    for(int i=0;i<numberOfStudents;i++)
    {
        int Total=Student[i].Marks1+Student[i].Marks2+Student[i].Marks3;
        float Average=Total/3.0;
        char Grade=gradeCalculator(Average);
        int Performance=performanceCalculator(Grade);

        printf("Roll No: %d\n", Student[i].RollNo);
        printf("Name: %s\n", Student[i].Name);
        printf("Total: %d\n", Total);
        printf("Average: %.2f\n", Average);
        printf("Grade: %c\n", Grade);
        printPerformance(Average,Performance);
    }
}

//Recursive function to print all the RollNo.
void displayRollNumbers(const int numberOfStudents,int initial)
{
    if(initial>numberOfStudents)return;
    printf("%d ",initial);
    displayRollNumbers(numberOfStudents,initial+1);
}



//HELPER FUNCTIONS
//Function to calculate grade based on average.
char gradeCalculator(float Average)
{
    if(Average>=85)return 'A';
    else if(Average>=70)return 'B';
    else if(Average>=50)return 'C';
    else if(Average>=35)return 'D';
    else return 'F';
}

//Function to calculate performance based on grade.
int performanceCalculator(char Grade)
{
    switch(Grade)
    {
        case 'A':return 5;
        case 'B':return 4;
        case 'C':return 3;
        case 'D':return 2;
        case 'F':return 0;
        default:return 0;
    }
}

//Function to print the performance with *
void printPerformance(float Average, int Performance)
{
    if(Average>=35)
    {
        printf("Performance: ");
        for(int j=0;j<Performance;j++)
        {
            printf("*");
        }
        printf("\n");
    }
    else 
    {
        printf("\n");
    }
    printf("\n");
}
