#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#define MAX_SIZE 100

//Function to check the precendence of the operators.
int precedence(char op){
    if(op=='+' || op=='-')return 1;
    if(op=='*' || op=='/')return 2;
    return 0;
}

//Function to solve the expression.
int solve(int a,int b,char op){
    switch(op){
        case '+':return a+b;
        case '-':return a-b;
        case '*':return a*b;
        case '/':return a/b;
        default:return 0;
    }
}

//Checks if it is an operator
int isOperator(char op){
    return op=='+' || op=='-' || op=='*' || op=='/';
}

int main(){
    char expression[MAX_SIZE];
    int numbers[MAX_SIZE];
    int ntop=-1, otop=-1;
    char operators[MAX_SIZE];

    printf("Enter the expression: ");
    fgets(expression,sizeof(expression),stdin);

    for(int i=0;expression[i];i++){
        if(expression[i]==' ')continue;   //Ignoring all the whitespaces.
        if(isdigit(expression[i])){       //Taking the number and adding it to the stack.
            int val=0;
            while(isdigit(expression[i])){    
                val=val*10+(expression[i] - '0');
                i++;
            }
            i--;
            numbers[++ntop]=val;
        }
        else if(isOperator(expression[i])){
            while(otop>=0 && precedence(operators[otop])>=precedence(expression[i])){    //Higher precedence operation will take place. 
                int b=numbers[ntop--];
                int a=numbers[ntop--];
                char op=operators[otop--];
                if(b==0 && op=='/'){
                    printf("Error: Division by zero!\n");
                    return 1;
                }
                else{
                    numbers[++ntop]=solve(a,b,op);
                }
            }
            operators[++otop]=expression[i];
        }
        else if(expression[i]!='\n'){
            printf("Error: Invalid Expression!\n");
            return 0;
        }
    }

    while(otop>=0){       //For the remaining operations.
        int b=numbers[ntop--];
        int a=numbers[ntop--];
        char op=operators[otop--];
        if(b==0 && op=='/'){
            printf("Error: Division by zero!\n");
            return 1;
        }
        numbers[++ntop]=solve(a,b,op);
    }
    printf("Result: %d\n",numbers[ntop]); //Returning the top value of numbers which contains the answer.
    return 0;

}