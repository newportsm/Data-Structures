// CS261 - Programming Assignment 2
// Author:          Sarah Newport
// Date Created:    4/15/2015
// Program:         Assignment 2


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynamicArray.h"
#include <assert.h>
#include <math.h>

#define PI	3.14159265  //constant for PI
#define E	2.7182818   //constant for E


/* param: s the string
 param: num a pointer to double
 returns: true (1) if s is a number else 0 or false.
 postcondition: if it is a number, num will hold
 the value of the number
 */

int isNumber(char *s, double *num)
{
    char *end;
    double returnNum;
    
    if(strcmp(s, "0") == 0)
    {
        *num = 0;
        return 1;
    }
    else
    {
        returnNum = strtod(s, &end);
        /* If there's anythin in end, it's bad */
        if((returnNum != 0.0) && (strcmp(end, "") == 0))
        {
            *num = returnNum;
            return 1;
        }
    }
    return 0;  //if got here, it was not a number
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their sum is pushed back onto the stack.
 */

void add (struct DynArr *stack)
{
    /* FIXME: You will write this function */
    
    assert(sizeDynArr(stack) >= 2); //to make sure that there are at least 2 values
    
    double temp = topDynArr(stack);
    popDynArr(stack);
    double add = topDynArr(stack) + temp;	//add numbers
    popDynArr(stack);						//pop it
    pushDynArr(stack, add);					//push sum to stack
    
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their difference is pushed back onto the stack.
 */

void subtract(struct DynArr *stack)
{
    /* FIXME: You will write this function */
    
    assert(sizeDynArr(stack) >= 2); //make sure there are at least two values
    
    double temp = topDynArr(stack);
    popDynArr(stack);
    double subtract = topDynArr(stack) - temp;	//subtract numbers
    popDynArr(stack);							//pop it
    pushDynArr(stack, subtract);				//push to stack
    
    
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their quotient is pushed back onto the stack.
 */
void divide(struct DynArr *stack)
{
    /* FIXME: You will write this function */
    
    assert(sizeDynArr(stack) >= 2); //make sure that there are at least two values
    
    double temp = topDynArr(stack);
    popDynArr(stack);
    double divide = (topDynArr(stack) / temp);	//divide numbers
    popDynArr(stack);							//pop it
    pushDynArr(stack, divide);					//push to stack
    
}

void multiply(struct DynArr *stack)
{

    assert(sizeDynArr(stack) >= 2); //make sure there are at least two values
    
    double temp = topDynArr(stack);
    popDynArr(stack);
    double multiply = (temp * topDynArr(stack));	//multiply numbers
    popDynArr(stack);								//pop it
    pushDynArr(stack, multiply);					//push to stack
}

void power(struct DynArr *stack)
{
    assert(sizeDynArr(stack) >= 2); //make sure there are at least two values
    
    double temp = topDynArr(stack);
    popDynArr(stack);
    double power = pow(topDynArr(stack), temp);		//get power
    popDynArr(stack);								//pop it
    pushDynArr(stack, power);						//push to stack
    
}

void squared(struct DynArr *stack)
{
    assert(sizeDynArr(stack) >= 1); //verify at least 1 value
    
    double square = pow(topDynArr(stack), 2);		//squared
    popDynArr(stack);								//pop it
    pushDynArr(stack, square);						//push to stack
    
}

void cubed(struct DynArr *stack)
{
    assert(sizeDynArr(stack) >= 1);
    
    double cube = pow(topDynArr(stack), 3);			//cubed operation
    popDynArr(stack);								//pop it
    pushDynArr(stack, cube);						//push to stack
}

void absolute(struct DynArr *stack)
{
    assert(sizeDynArr(stack) >= 1);
    
    double absolute = abs(topDynArr(stack));		//absolute value operation
    popDynArr(stack);								//pop it
    pushDynArr(stack, absolute);					//push to stack
}

void squareroot(struct DynArr *stack)
{
    assert(sizeDynArr(stack) >= 1);
    
    double squareroot = sqrt(topDynArr(stack));		//sqrt operation
    popDynArr(stack);								//pop it
    pushDynArr(stack, squareroot);					//push to stack
    
}

void exponential(struct DynArr *stack)
{
    assert(sizeDynArr(stack) >= 1);
    
    double expo = exp(topDynArr(stack));			//exponential operation
    popDynArr(stack);								//pop it
    pushDynArr(stack, expo);						//push to stack
}

void natlog(struct DynArr *stack)
{
    assert(sizeDynArr(stack) >= 1);
    
    double natlog = log(topDynArr(stack));			//base e operation
    popDynArr(stack);								//pop it
    pushDynArr(stack, natlog);						//push to stack
}

void logarithm(struct DynArr *stack)
{
    assert(sizeDynArr(stack) >= 1);
    
    double logarithm = log10(topDynArr(stack));		//base 10 operation
    popDynArr(stack);								//pop it
    pushDynArr(stack, logarithm);					//push to stack
    
}



double calculate(int numInputTokens, char **inputString)
{
    int i;
    double result = 0.0;
    char *s;
    struct DynArr *stack;
    
    double num;
    
    //set up the stack
    stack = createDynArr(20);
    
    // start at 1 to skip the name of the calculator calc
    for(i=1;i < numInputTokens;i++)
    {
        s = inputString[i];
        
        // Hint: General algorithm:
        // (1) Check if the string s is in the list of operators.
        //   (1a) If it is, perform corresponding operations.
        //   (1b) Otherwise, check if s is a number.
        //     (1b - I) If s is not a number, produce an error.
        //     (1b - II) If s is a number, push it onto the stack
        
        if(strcmp(s, "+") == 0)
            add(stack);
        else if(strcmp(s,"-") == 0)
            subtract(stack);
        else if(strcmp(s, "/") == 0)
            divide(stack);
        else if(strcmp(s, "x") == 0)
        /* FIXME: replace printf with your own function */
            
            multiply(stack);
        else if(strcmp(s, "^") == 0)
        /* FIXME: replace printf with your own function */
            
            power(stack);
        else if(strcmp(s, "^2") == 0)
        /* FIXME: replace printf with your own function */
            
            squared(stack);
        else if (strcmp(s, "^3") == 0)
        /* FIXME: replace printf with your own function */
            
            cubed(stack);
        else if (strcmp(s, "abs") == 0)
        /* FIXME: replace printf with your own function */
            
            absolute(stack);
        else if (strcmp(s, "sqrt") == 0)
        /* FIXME: replace printf with your own function */
            
            squareroot(stack);
        else if (strcmp(s, "exp") == 0)
        /* FIXME: replace printf with your own function */
            
            exponential(stack);
        else if (strcmp(s, "ln") == 0)
        /* FIXME: replace printf with your own function */
            
            natlog(stack);
        else if(strcmp(s, "log") == 0)
        /* FIXME: replace printf with your own function */
            
            logarithm(stack);
        else
        {
            // FIXME: You need to develop the code here (when s is not an operator)
            // Remember to deal with special values ("pi" and "e")
            
            //check if not a number
            if (isNumber(s, &num) == 0)
            {
                if (strcmp(s, "pi") == 0)			//pi
                {
                    num = PI;
                }
                
                else if (strcmp(s, "e") == 0)		//e
                {
                    num = E;
                }
                
                else								//wrong
                {
                    printf("%s is not valid (number or operator) \n", s);
                
                    break;
                }
           
            }
            
            pushDynArr(stack, num);
            
        }
   
    }	//end for
    
    /* FIXME: You will write this part of the function (2 steps below) 
     * (1) Check if everything looks OK and produce an error if needed.
     * (2) Store the final value in result and print it out.
     */
    
    if (sizeDynArr(stack) != 1)
    {
        printf("There are %d values on the stack. There should only be the one answer \n", sizeDynArr(stack));
    }
    
    else
    {
        result = topDynArr(stack);
    }
    
    return result;
}

int main(int argc , char** argv)
{
    
    // assume each argument is contained in the argv array
    // argc-1 determines the number of operands + operators
    if (argc == 1)
        return 0;
    
    double num = 0;
    num = calculate(argc, argv);
    printf("The answer = %f \n", num);
    
    return 0;
}