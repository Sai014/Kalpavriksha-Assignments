#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

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
        case '/':if(b==0){
            printf("\nError: Division by Zero!\n");
            exit(0);
        }
        return a/b;
        default:return 0;
    }
}

int main(){
    char expression[100];
    int numbers[100];
    int ntop=-1, otop=-1;
    char operators[100];

    printf("Enter the expression: ");
    fgets(expression,100,stdin);

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
        else if(expression[i]=='+' || expression[i]=='-' || expression[i]=='*' || expression[i]=='/'){
            while(otop>=0 && precedence(operators[otop])>=precedence(expression[i])){    //Higher precedence operation will take place. 
                int b=numbers[ntop--];
                int a=numbers[ntop--];
                char op=operators[otop--];
                numbers[++ntop]=solve(a,b,op);
            }
            operators[++otop]=expression[i];
        }
        else if(expression[i]!='\n'){
            printf("Error: Invalid Expression!");
            return 0;
        }
    }

    while(otop>=0){       //For the remaining operations.
        int b=numbers[ntop--];
        int a=numbers[ntop--];
        char op=operators[otop--];
        numbers[++ntop]=solve(a,b,op);
    }
    printf("%d\n",numbers[ntop]); //Returning the top value of numbers which contains the answer.
    return 0;

}