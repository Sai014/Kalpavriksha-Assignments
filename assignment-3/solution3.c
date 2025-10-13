#include<stdio.h>
#include<stdlib.h>

#define MAX_STUDENTS 100
#define MAX_MARKS 100
#define Grade_A 85
#define Grade_B 70
#define Grade_C 50
#define Grade_D 35

//Structure for student.
typedef struct
{
    int RollNo;
    char Name[20];
    int Marks1;
    int Marks2;
    int Marks3;
}Student;

void fetchDetails(const int numberOfStudents, Student student[]);
void displayDetails(const int numberOfStudents, Student student[]);
void displayRollNumbers(const int numberOfStudents,int initial);
char gradeCalculator(float Average);
int performanceCalculator(char Grade);
void printPerformance(float Average, int Performance);
bool checkMarks(int Marks1,int Marks2,int Marks3);



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
    Student student[numberOfStudents];

    fetchDetails(numberOfStudents,student);
    displayDetails(numberOfStudents,student);
    printf("List of Roll numbers(via recurssion): ");
    displayRollNumbers(numberOfStudents,1);
    printf("\n");
    return 0;
}




//Function to fetch all the details of students.
void fetchDetails(const int numberOfStudents, Student student[])
{
    printf("Enter Details: \n");
    for(int i = 0; i < numberOfStudents; i++) {
        do {
            scanf("%d %s %d %d %d", &student[i].RollNo, student[i].Name,&student[i].Marks1, &student[i].Marks2, &student[i].Marks3);
            if(checkMarks(student[i].Marks1,student[i].Marks2,student[i].Marks3)) 
            {
                printf("Invalid marks! Enter again (0-100):\n");
            }
        } while(checkMarks(student[i].Marks1,student[i].Marks2,student[i].Marks3));
    }
    printf("\n");
}

//Function to display all the details of students.
void displayDetails(const int numberOfStudents, Student student[])
{
    for(int i=0;i<numberOfStudents;i++)
    {
        int Total=student[i].Marks1+student[i].Marks2+student[i].Marks3;
        float Average=Total/3.0;
        char Grade=gradeCalculator(Average);
        int Performance=performanceCalculator(Grade);

        printf("Roll No: %d\n", student[i].RollNo);
        printf("Name: %s\n", student[i].Name);
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
    if(Average>=Grade_A)return 'A';
    else if(Average>=Grade_B)return 'B';
    else if(Average>=Grade_C)return 'C';
    else if(Average>=Grade_D)return 'D';
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

//Function to check if marks are valid.
bool checkMarks(int Marks1,int Marks2,int Marks3)
{
    if(Marks1 < 0 || Marks1 > MAX_MARKS ||
    Marks2 < 0 || Marks2 > MAX_MARKS ||
    Marks3 < 0 || Marks3 > MAX_MARKS)return true;
    else return false;
}