//
//  DFA.c
//  173_HW
//
//  Created by Matthew Lee on 9/19/17.
//  Copyright © 2017 Matthew Lee. All rights reserved.
//

#include "DFA.h"
#include <stdio.h>
#include <string.h>
#define TRUE -1;
#define FALSE -2;
typedef int BOOLEAN;



int transitionState = 0;
int acceptArrayDFA[10]={-2,-2,-2,-2,-2,-2,-2,-2,-2,-2};
BOOLEAN alreadyAsked = FALSE;



int* FindAcceptingStates(int m, int n, int table[m][n]);
BOOLEAN CheckIfAccStateDFA(int value);
int* resetacceptArrayDFA(int acceptArrayDFA[]);
int GetStringTransitionState(int m, int n, int table[m][n]);
BOOLEAN CannotFindMatch(int input,int m, int n, int table[m][n]);
void runDfaProgram();

//the table is designed in a to have its values as...
// a's transition, a-value, b's transition, b-value, non a or b transitions, accepting state marked by #(35) symbol ASCII value

//transition table for string ab
int transTableAB[4][6]= {{1,97,3,98,3, },{3,97,2,98,3, },{3,97,3,98,3,35},{3,97,3,98,3, }};

//transition table for strings starting with ab
int startAB[4][6]={{1,97,3,98,3, }, {3,97,2,98,3, },{2,97,2,98,2,35},{3,97,3,98,3, }};

//transition table for strings  with an even number of 1's
int bin1Even[2][5]={{0,48,1,49,35},{1,48,0,49, }};

//transition table for strings  with an even number of 0's
int bin0Even[2][5]={{1,48,0,49,35},{0,48,1,49, }};

//transition table for strings ending with ab
int endAB[3][6]= {{1,97,0,98,0, },{1,97,2,98,0, },{1,97,0,98,0,35},};

int type;


//finds the accepting states from our transition table
int* FindAcceptingStates(int m, int n, int table[m][n])
{
    //acceptArrayDFA[m];
    int counter=0;
    for(int i=0; i<m;i++)
    {
        if(table[i][n-1] != '\0')
        {
            acceptArrayDFA[counter] = i;
            counter++;
        }
        
    }
    return acceptArrayDFA;
}


//checks to see if we have gotten an accepting state
BOOLEAN CheckIfAccStateDFA(int value)
{
    for(int i=0;i<10;i++)
    {
        
        if(value==acceptArrayDFA[i])
        {
            
            return TRUE;
        }
        
    }
    
    
    return FALSE;
}

//to clear our accept array for other future procedures
int* resetacceptArrayDFA(int acceptArrayDFA[])
{
    for(int i=0;i<10;i++)
    {
        acceptArrayDFA[i] = -2;
    }
    
    return acceptArrayDFA;
}



int GetStringTransitionState(int m, int n, int table[m][n])
{
    
    int length;
    char letters[length];
    
    
    if(alreadyAsked==-2)
    {
        printf("Enter the length of your 'string'...\n");
        scanf("%d", &length);
        
        printf("Enter the 'string'...\n");
        scanf("%s", letters);
    }
    
    int ascii[length];
    
    //we now have our string converted to the correct ASCII values
    for(int i=0;i<length;i++)
    {
        int value = letters[i];
        ascii[i]= value;
        printf(" %c = %d\n", letters[i], ascii[i] );
        
        
    }
    
    printf("Our ascII table has been filled!\n");
    
    
    
    for(int i=0;i<length;i++)
    {
        for(int j=0;j<n;j++)
        {
            
            if(ascii[i]==table[transitionState][j])
            {
                transitionState = table[transitionState][j-1];
                
            }
            
        }
        
        if((CannotFindMatch(ascii[i], m, n, table)==-2))
        {
            transitionState = table[transitionState][n-2];
        }
        
    }
    
    
    printf("we found our transition state value: %d\n", transitionState);
    
    
    return transitionState;
}


BOOLEAN CannotFindMatch(int input, int m, int n, int table[m][n])
{
    for(int i=0; i<n;i++)
    {
        if(input==table[transitionState][i])
        {
            return TRUE;
        }
        
        
        
    }
    
    
    return FALSE;
    
}

void runDfaProgram()
{
    printf("Please enter the NUMBER for the type of automata you would like to test?\n 1) just string ab\n 2) strings that start ab\n 3) Binary string w/ even numbers of 1's\n 4) Binary string w/ even numbers of both 1's and 0's\n 5) strings that end with ab\n");
    scanf("%d", &type);
    
    
    //for just string "ab"
    if(type==1)
    {
        FindAcceptingStates(4, 6, transTableAB);
        GetStringTransitionState(4, 6, transTableAB);
        if(CheckIfAccStateDFA(transitionState)==-1)
        {
            printf("Your string has been ACCEPTED\n");
        }
        else
        {
            printf("Your string has NOT been accepted\n");
        }
    }
    else if(type==2)
    {
        FindAcceptingStates(4, 6, startAB);
        GetStringTransitionState(4, 6, startAB);
        if(CheckIfAccStateDFA(transitionState)==-1)
        {
            printf("Your string has been ACCEPTED\n");
        }
        else
        {
            printf("Your string has NOT been accepted\n");
        }
        
        
        
    }
    else if(type==3)
    {
        FindAcceptingStates(2, 5, bin1Even);
        GetStringTransitionState(2, 5, bin1Even);
        if(CheckIfAccStateDFA(transitionState)==-1)
        {
            printf("Your string has been ACCEPTED\n");
        }
        else
        {
            printf("Your string has NOT been accepted\n");
        }
        
        
    }
    else if(type==4)
    {
        
        FindAcceptingStates(2, 5, bin1Even);
        GetStringTransitionState(2, 5, bin1Even);
        if(CheckIfAccStateDFA(transitionState)==-1)
        {
            alreadyAsked = TRUE;
            
            resetacceptArrayDFA(acceptArrayDFA);
            transitionState =0;
            FindAcceptingStates(2, 5, bin0Even);
            
            
            
            //problem lies here in where i ask
            GetStringTransitionState(2, 5, bin0Even);
            if(CheckIfAccStateDFA(transitionState)==-1)
            {
                
                printf("Your string has been ACCEPTED\n");
                
            }
            else
            {
                printf("Your string has NOT been accepted\n");
            }
            
            
        }
        else
        {
            printf("Your string has NOT been accepted\n");
        }
        
        
    }
    else
    {
        FindAcceptingStates(3, 6, endAB);
        GetStringTransitionState(3, 6, endAB);
        if(CheckIfAccStateDFA(transitionState)==-1)
        {
            printf("Your string has been ACCEPTED\n");
        }
        else
        {
            printf("Your string has NOT been accepted\n");
        }
        
        
        
    }
    
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
int main(int argc, const char * argv[]) {
    
    
    runDfaProgram();

    
}

*/













