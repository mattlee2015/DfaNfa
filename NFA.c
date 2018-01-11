//
//  NFA.c
//  173_HW
//
//  Created by Matthew Lee on 9/20/17.
//  Copyright © 2017 Matthew Lee. All rights reserved.
//

#include "NFA.h"

#define MAX 20
#define NONACCEPT 34
#define ACCEPT 35
#define NONE -3
#define lamba -4
#define TRUE -1;
#define FALSE -2;
typedef int BOOLEAN;


int subsetState[MAX] = {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};
int acceptArrayNFA[MAX] = {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};
int strlength;
int ascii[MAX] = {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};
int currTranState = 0;

char letters[MAX] = {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};
int type;


BOOLEAN again = FALSE;
BOOLEAN noMatchFound = FALSE;
void resetINTArray(int test[]);
void resetCHARArray(char test[]);
BOOLEAN isEmpty(int array[]);
BOOLEAN currentSetStateHoldsMoreThanOne(int ourArr[]);
void findInputsTransitionState(int x, int y, int z, int table[x][y][z], int state, int asciiNum, int arrToHoldStates[]);
void findCurrSetStateEND(int x, int y, int z, int table[x][y][z]);
void findCurrSetStateCONTAIN(int x, int y, int z, int table[x][y][z]);
void copyArr1ToArr2(int arr1[], int arr2[]);
BOOLEAN noDuplicatesInArray(int arr1Num, int arr2[]);
BOOLEAN notADuplicate(int num1, int num2);
int howManyElements(int arr[]);
BOOLEAN ascIINotListed(int x, int y, int z, int asciiNum, int table[x][y][z], int state);
void runNfaProgram();

int endMan [4][4][6]= {
   
    //     m            |   a           |  n                |      Λ-(man)
     //represent the 0-state
    {{109,0,1,-3,-3, NONACCEPT},{97,0,-3,-3,-3, NONACCEPT},{110,0,-3,-3,-3, NONACCEPT},{-4,0,-3,-3,-3, NONACCEPT}},
    //     m            |   a               |  n                |      Λ-(man)
     //represent the 1-state
    {{109,-3,-3,-3,-3, NONACCEPT},{97,2,-3,-3,-3, NONACCEPT},{110,-3,-3,-3,-3, NONACCEPT},{-4,-3,-3,-3,-3, NONACCEPT}},
    //     m            |   a               |  n                |      Λ-(man)
     //represent the 2-state
    {{109,-3,-3,-3,-3, NONACCEPT},{97,-3,-3,-3,-3, NONACCEPT},{110,3,-3,-3,-3, NONACCEPT},{-4,-3,-3,-3,-3, NONACCEPT}},
    //     m            |   a                  |  n                 |      Λ-(man)
     //represent the 3-state
    {{109,-3,-3,-3,-3, ACCEPT},{97,-3,-3,-3,-3,ACCEPT},{110,-3,-3,-3,-3,ACCEPT},{-4,-3,-3,-3,-3,ACCEPT}}
    
};

int washington[20][10][4]={
    
    //0
    // w                  |     a            | s                | h                 |   i                 |n                    |   g           |   t                   | o                 | Λ-(washinto)
    {{119,0,18,NONACCEPT},{97,0,1,NONACCEPT},{115,0,14,NONACCEPT},{104,0,5,NONACCEPT},{105,0,7,NONACCEPT},{110,0,9,NONACCEPT},{103,0,3,NONACCEPT},{116,0,16,NONACCEPT},{111,0,12,NONACCEPT},{-4,0,-3,NONACCEPT}},
    //1
    // w                  |     a            | s                    | h                 |   i                 |n                    |   g           |   t                   | o                 | Λ-(washinto)
    {{119,1,-3,NONACCEPT},{97,2,-3,NONACCEPT},{115,1,-3,NONACCEPT},{104,1,-3,NONACCEPT},{105,1,-3,NONACCEPT},{110,1,-3,NONACCEPT},{103,1,-3,NONACCEPT},{116,1,-3,NONACCEPT},{111,1,-3,NONACCEPT},{-4,1,-3,NONACCEPT}},
    //2
    // w                  |     a            | s           | h                 |   i                 |n               |   g           |   t                   | o              | Λ-(washinto)
    {{119,-3,-3,ACCEPT},{97,-3,-3,ACCEPT},{115,-3,-3,ACCEPT},{104,-3,-3,ACCEPT},{105,-3,-3,ACCEPT},{110,-3,-3,ACCEPT},{103,-3,-3,ACCEPT},{116,-3,-3,ACCEPT},{111,-3,-3,ACCEPT},{-4,-3,-3,ACCEPT}},
    //3
    // w                  |     a            | s                    | h                 |   i                 |n               |   g                    |   t                | o              | Λ-(washinto)
    {{119,3,-3,NONACCEPT},{97,3,-3,NONACCEPT},{115,3,-3,NONACCEPT},{104,3,-3,NONACCEPT},{105,3,-3,NONACCEPT},{110,3,-3,NONACCEPT},{103,4,-3,NONACCEPT},{116,3,-3,NONACCEPT},{111,3,-3,NONACCEPT},{-4,3,-3,NONACCEPT}},
    //4
    // w                  |     a            | s           | h                 |   i                 |n               |   g           |   t                   | o              | Λ-(washinto)
    {{119,-3,-3,ACCEPT},{97,-3,-3,ACCEPT},{115,-3,-3,ACCEPT},{104,-3,-3,ACCEPT},{105,-3,-3,ACCEPT},{110,-3,-3,ACCEPT},{103,-3,-3,ACCEPT},{116,-3,-3,ACCEPT},{111,-3,-3,ACCEPT},{-4,-3,-3,ACCEPT}},
    //5
    // w                  |     a            | s                    | h                 |   i                 |n               |   g                    |   t                | o              | Λ-(washinto)
    {{119,5,-3,NONACCEPT},{97,5,-3,NONACCEPT},{115,5,-3,NONACCEPT},{104,6,-3,NONACCEPT},{105,5,-3,NONACCEPT},{110,5,-3,NONACCEPT},{103,5,-3,NONACCEPT},{116,5,-3,NONACCEPT},{111,5,-3,NONACCEPT},{-4,5,-3,NONACCEPT}},
    //6
    // w                  |     a            | s           | h                 |   i                 |n               |   g           |   t                   | o              | Λ-(washinto)
    {{119,-3,-3,ACCEPT},{97,-3,-3,ACCEPT},{115,-3,-3,ACCEPT},{104,-3,-3,ACCEPT},{105,-3,-3,ACCEPT},{110,-3,-3,ACCEPT},{103,-3,-3,ACCEPT},{116,-3,-3,ACCEPT},{111,-3,-3,ACCEPT},{-4,-3,-3,ACCEPT}},
    //7
    // w                  |     a            | s                    | h                 |   i                 |n               |   g                    |   t                | o              | Λ-(washinto)
    {{119,7,-3,NONACCEPT},{97,7,-3,NONACCEPT},{115,7,-3,NONACCEPT},{104,7,-3,NONACCEPT},{105,8,-3,NONACCEPT},{110,7,-3,NONACCEPT},{103,7,-3,NONACCEPT},{116,7,-3,NONACCEPT},{111,7,-3,NONACCEPT},{-4,7,-3,NONACCEPT}},
    //8
    // w                  |     a            | s           | h                 |   i                 |n               |   g           |   t                   | o              | Λ-(washinto)
    {{119,-3,-3,ACCEPT},{97,-3,-3,ACCEPT},{115,-3,-3,ACCEPT},{104,-3,-3,ACCEPT},{105,-3,-3,ACCEPT},{110,-3,-3,ACCEPT},{103,-3,-3,ACCEPT},{116,-3,-3,ACCEPT},{111,-3,-3,ACCEPT},{-4,-3,-3,ACCEPT}},
    //9
    // w                  |     a            | s                    | h                 |   i                 |n                    |   g               |   t                | o              | Λ-(washinto)
    {{119,9,-3,NONACCEPT},{97,9,-3,NONACCEPT},{115,9,-3,NONACCEPT},{104,9,-3,NONACCEPT},{105,9,-3,NONACCEPT},{110,10,-3,NONACCEPT},{103,9,-3,NONACCEPT},{116,9,-3,NONACCEPT},{111,9,-3,NONACCEPT},{-4,9,-3,NONACCEPT}},
    //10
    // w                  |     a            | s                    | h                     |   i                 |n                    |   g               |   t                | o                    | Λ-(washinto)
    {{119,10,-3,NONACCEPT},{97,10,-3,NONACCEPT},{115,10,-3,NONACCEPT},{104,10,-3,NONACCEPT},{105,10,-3,NONACCEPT},{110,11,-3,NONACCEPT},{103,10,-3,NONACCEPT},{116,10,-3,NONACCEPT},{111,10,-3,NONACCEPT},{-4,10,-3,NONACCEPT}},
    //11
    // w                  |     a            | s           | h                 |   i                 |n               |   g           |   t                   | o              | Λ-(washinto)
    {{119,-3,-3,ACCEPT},{97,-3,-3,ACCEPT},{115,-3,-3,ACCEPT},{104,-3,-3,ACCEPT},{105,-3,-3,ACCEPT},{110,-3,-3,ACCEPT},{103,-3,-3,ACCEPT},{116,-3,-3,ACCEPT},{111,-3,-3,ACCEPT},{-4,-3,-3,ACCEPT}},
    //12
    // w                  |     a            | s                    | h                     |   i                 |n                    |   g               |   t                | o                    | Λ-(washinto)
    {{119,12,-3,NONACCEPT},{97,12,-3,NONACCEPT},{115,12,-3,NONACCEPT},{104,12,-3,NONACCEPT},{105,12,-3,NONACCEPT},{110,12,-3,NONACCEPT},{103,12,-3,NONACCEPT},{116,12,-3,NONACCEPT},{111,13,-3,NONACCEPT},{-4,12,-3,NONACCEPT}},
    //13
    // w                  |     a            | s           | h                 |   i                 |n               |   g           |   t                   | o              | Λ-(washinto)
    {{119,-3,-3,ACCEPT},{97,-3,-3,ACCEPT},{115,-3,-3,ACCEPT},{104,-3,-3,ACCEPT},{105,-3,-3,ACCEPT},{110,-3,-3,ACCEPT},{103,-3,-3,ACCEPT},{116,-3,-3,ACCEPT},{111,-3,-3,ACCEPT},{-4,-3,-3,ACCEPT}},
    //14
    // w                  |     a            | s                    | h                     |   i                 |n                    |   g               |   t                | o                    | Λ-(washinto)
    {{119,14,-3,NONACCEPT},{97,14,-3,NONACCEPT},{115,15,-3,NONACCEPT},{104,14,-3,NONACCEPT},{105,14,-3,NONACCEPT},{110,14,-3,NONACCEPT},{103,14,-3,NONACCEPT},{116,14,-3,NONACCEPT},{111,14,-3,NONACCEPT},{-4,14,-3,NONACCEPT}},
    //15
    // w                  |     a            | s           | h                 |   i                 |n               |   g           |   t                   | o              | Λ-(washinto)
    {{119,-3,-3,ACCEPT},{97,-3,-3,ACCEPT},{115,-3,-3,ACCEPT},{104,-3,-3,ACCEPT},{105,-3,-3,ACCEPT},{110,-3,-3,ACCEPT},{103,-3,-3,ACCEPT},{116,-3,-3,ACCEPT},{111,-3,-3,ACCEPT},{-4,-3,-3,ACCEPT}},
    //16
    // w                  |     a            | s                    | h                     |   i                 |n                    |   g               |   t                | o                    | Λ-(washinto)
    {{119,16,-3,NONACCEPT},{97,16,-3,NONACCEPT},{115,16,-3,NONACCEPT},{104,16,-3,NONACCEPT},{105,16,-3,NONACCEPT},{110,16,-3,NONACCEPT},{103,16,-3,NONACCEPT},{116,17,-3,NONACCEPT},{111,16,-3,NONACCEPT},{-4,16,-3,NONACCEPT}},
    //17
    // w                  |     a            | s           | h                 |   i                 |n               |   g           |   t                   | o              | Λ-(washinto)
    {{119,-3,-3,ACCEPT},{97,-3,-3,ACCEPT},{115,-3,-3,ACCEPT},{104,-3,-3,ACCEPT},{105,-3,-3,ACCEPT},{110,-3,-3,ACCEPT},{103,-3,-3,ACCEPT},{116,-3,-3,ACCEPT},{111,-3,-3,ACCEPT},{-4,-3,-3,ACCEPT}},
    //18
    // w                  |     a            | s                    | h                     |   i                 |n                    |   g               |   t                | o                    | Λ-(washinto)
    {{119,19,-3,NONACCEPT},{97,18,-3,NONACCEPT},{115,18,-3,NONACCEPT},{104,18,-3,NONACCEPT},{105,18,-3,NONACCEPT},{110,18,-3,NONACCEPT},{103,18,-3,NONACCEPT},{116,18,-3,NONACCEPT},{111,18,-3,NONACCEPT},{-4,18,-3,NONACCEPT}},
    //19
    // w                  |     a            | s           | h                 |   i                 |n               |   g           |   t                   | o              | Λ-(washinto)
    {{119,-3,-3,ACCEPT},{97,-3,-3,ACCEPT},{115,-3,-3,ACCEPT},{104,-3,-3,ACCEPT},{105,-3,-3,ACCEPT},{110,-3,-3,ACCEPT},{103,-3,-3,ACCEPT},{116,-3,-3,ACCEPT},{111,-3,-3,ACCEPT},{-4,-3,-3,ACCEPT}}
};

int ab[2][3][4] ={
    {{97,0,1,NONACCEPT},{98,0,1,NONACCEPT},{-4,-3,-3,NONACCEPT}},
    {{97,1,-3,ACCEPT},{98,1,-3,ACCEPT},{-4,-3,-3,ACCEPT}}
    
    
};












//table[currTranState][0-3][0]

//this returns the state-value that are considered accepted into an array that holds the values if multiple accepted states were to be present
int* findAcceptingStates(int x, int y, int z, int table[x][y][z])
{
    int counter = 0;
    for(int i=0;i<x;i++)
    {
      if((table[i][y-1][z-1])!=NONACCEPT)
      {
          acceptArrayNFA[counter] = i;
          counter++;
      }
    }
    
    
    //for debugging purposes
    //printf("our accepting state are...\n");
    /*
    for(int i=0; i<x;i++)
    {
        if(acceptArrayNFA[i]!=NONE)
        {
            printf("accept counter %d = state %d\n", i, acceptArrayNFA[i]);
        }
        
    }
    */
    return acceptArrayNFA;
}


//our subsetState[] will go into this...thus allowing us to see if we have an accepted state
BOOLEAN CheckIfAccStateNFA(int fsubset[])
{
    for(int i=0;i<MAX;i++)
    {
        if(acceptArrayNFA[i]!=NONE)
        {
            for(int j=0;j<MAX;j++)
            {
                if(acceptArrayNFA[i]==fsubset[j])
                {
                    return TRUE;
                }
            }
        
        }
        else
        {
            return FALSE;
        }
        
    }
    
    
    return FALSE;
}



void questionPrompt()
{
    
    printf("Please tell us the length of the string you wish to enter...\n");
    scanf("%d", &strlength);
    
    printf("Please enter in the string...\n");
    scanf("%s", letters);
    
    
}

void letterToASCII(char letters[])
{
    for(int i=0;i<strlength;i++)
    {
    
        int val = letters[i];
        ascii[i] = val;
        
        
        if(letters[i]!=-3)
        {
          printf("%c = %d\n", letters[i], ascii[i]);
        }
       
        
        
    }
    
    //printf("Our ascII table has been filled!\n");
    
    
}


void resetTry()
{
    if(again==-1)
    {
        //reset the currTranState value to 0
        currTranState = 0;
        
        //have the letters[] array with empty elements
        resetCHARArray(letters);
        
        //have ascii[] with empty elements
        resetINTArray(ascii);
        
        //have subsetState[] erased and filled with empty elements
        resetINTArray(subsetState);
        
        //have acceptArrayNFA[] erased and filled with empty elements
        resetINTArray(acceptArrayNFA);
        
        //have strlength = 0
        strlength = 0;
        
        
    }
}

void resetINTArray(int test[])
{
    for(int i=0;i<strlength;i++)
    {
        if(test[i]!=NONE)
        {
            test[i] = NONE;
            
            
        }
    }
    
    //printf("resetINTArray has been performed\n");
}

void resetCHARArray(char test[])
{
    for(int i=0;i<strlength;i++)
    {
        if(test[i]!=NONE)
        {
            test[i] = NONE;
            
            
        }
    }
    
     //printf("resetCHARArray has been performed\n");
}

//////////////////////////////////////////////////////////////////////////////




//this goes inside our 3D array to find all possible state values and stores them into the subsetState array
void findInputsTransitionState(int x, int y, int z, int table[x][y][z], int state, int asciiNum, int arrToHoldStates[])
{
    
    //we use y so that it changes between the letter's ascii options
    for(int i=0; i<y;i++)
    {
        //printf("findInputsTransitionState: we are on testing on STATE %d\n", state);
        //matching the first value in the z-dimension to the ascii value of the letter
        if(asciiNum==table[state][i][0])
        {
            
            noMatchFound = FALSE;
            //printf("findInputsTransitionState: found MATCH of %d and %d\n", asciiNum, table[state][i][0]);
            //i need to fill the subsetState[] with the numbers other than -3
            for(int j=1;j<z;j++)
            {
                //we dont want it to record the -3 for they represent "none/empty" values
                if((table[state][i][j]!=-3)&&(table[state][i][j]!=NONACCEPT)&&(table[state][i][j]!=ACCEPT))
                {
                
                    arrToHoldStates[j-1]=table[state][i][j];
                }
                
            }
            
        }
        else if((ascIINotListed(x, y, z, asciiNum, table, state))==-1)
        {
           //printf("findInputsTransitionState: NO MATCH FOUND for %d\n", asciiNum);
            
            noMatchFound = TRUE;
            
            
            
            for(int j=1;j<z;j++)
            {
                //match with the lamba section and if the value is not a -3 and not a NONACCEPT and not an ACCEPT
                if((table[state][y-1][j]!=-3)&&(table[state][y-1][j]!=NONACCEPT)&&(table[state][y-1][j]!=ACCEPT))
                {
                    
                    arrToHoldStates[j-1]=table[state][y-1][j];
                    
                    //printf("findInputsTransitionState:A value was stored for the lamba\n");
                }
                /*
                else
                {
                    printf("findInputsTransitionState:A value was NOT stored for the lamba\n");
                }
                 */
                
            }
            
            
        }
        
        
        
    }
   
    //printf("findInputsTransitionState: Values have been put into the array\n");
    /*
    for(int i=0; i<x;i++)
    {
        if(arrToHoldStates[i]!=NONE)
        {
            printf("index %d = state %d\n", i, arrToHoldStates[i]);
        }
        
    }
    */
    
    
}

BOOLEAN ascIINotListed(int x, int y, int z, int asciiNum, int table[x][y][z], int state)
{
    for(int i=0; i<z;i++)
    {
     if(asciiNum==table[state][i][0])
     {
         return FALSE;
     }
         
    }
    return TRUE;
}



// finds the current state of the letter (which is converted to its acsii value) given a state value (since we can have multiple transitions to other states)
// this is all found inside our subsetState[]

//used on automata that end with a particular pattern
void findCurrSetStateEND(int x, int y, int z, int table[x][y][z])
{
    
   
    int currArr[MAX]={NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};
    
    int unionArr[MAX]={NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};
    
    
    int inputCounter = 1;
    for(int j=0;j<strlength+1;j++)
    {
      //printf("findCurrSetState: j=%d\n", j);
        //printf("findCurrSetState: inputCounter=%d\n", inputCounter);
        if(j==0)
        {
            subsetState[0]=0;
            //printf("findCurrSetState: we did the 'if' method for j=%d\n", j);
            
        }
        else
        {
            //printf("findCurrSetState: we did the 'else' method for j=%d\n", j);
            
            //in the case our subset[] contains only 1 value (FALSE result)
            if(currentSetStateHoldsMoreThanOne(subsetState)==-2)
            {
                //printf("findCurrSetState: we only found one state in the array for j=%d and the value is %d\n", j, subsetState[0]);
                findInputsTransitionState(x, y, z, table, subsetState[0], ascii[inputCounter-1], subsetState);
                inputCounter++;
            }
            //if our subset[] contains more than 1 value
            else
            {
                //printf("findCurrSetState: we found MORE than 1 state in the array for j=%d\n", j);
                //for how many states there are possible
                
                
                int numOfEleInSubset = howManyElements(subsetState);
                
                
                for(int i=0; i<numOfEleInSubset;i++)
                {
                    if(subsetState[i]!=-3)
                    {
                        
                        //printf("findCurrSetState: performing UNION of set construction for j=%d and i=%d\n", j, i);
                        findInputsTransitionState(x, y, z, table, subsetState[i], ascii[inputCounter-1], currArr);
                        
                        
                        //copy the values to unionArr --> check to see if there are duplicated values
                        copyArr1ToArr2(currArr, unionArr);
                        
                        //printf("findCurrSetState: copied currARR to unionARR for j=%d and i=%d\n", j, i);
                        /*
                        for(int i=0; i<MAX;i++)
                        {
                            printf("findCurrSetState: unionArr INDEX %d = %d\n", i, unionArr[i]);
                            
                            
                            
                            
                        }
                        */
                        resetINTArray(currArr);
                        
                    }
                    
                    
                    
                }
                inputCounter++;
                
                //erase the subsetState[] and copy the values from the unionArr into it
                resetINTArray(subsetState);
                
                
                
                copyArr1ToArr2(unionArr, subsetState);
                resetINTArray(unionArr);
               
                /*
                printf("findCurrSetState: copied unionArr to subsetState for j=%d\n", j);
                for(int i=0; i<MAX;i++)
                {
                    printf("findCurrSetState: subsetState INDEX %d = %d\n", i, subsetState[i]);
                }
                */
                
            }
        }
        
    }
    
    //printf("the findCurrSetState method finished performing\n");
    
    
    
    
}


//used for automata with a specific pattern in containing specific things
void findCurrSetStateCONTAIN(int x, int y, int z, int table[x][y][z])
{
    
    
    int currArr[MAX]={NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};
    
    int unionArr[MAX]={NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};
    
    
    int inputCounter = 1;
    for(int j=0;j<strlength+1;j++)
    {
        
        if(j==0)
        {
            subsetState[0]=0;
            
            
        }
        else
        {
           
            
            //in the case our subset[] contains only 1 value (FALSE result)
            if(currentSetStateHoldsMoreThanOne(subsetState)==-2)
            {
                
                findInputsTransitionState(x, y, z, table, subsetState[0], ascii[inputCounter-1], subsetState);
                inputCounter++;
            }
            //if our subset[] contains more than 1 value
            else
            {
                
                //for how many states there are possible
                
                
                int numOfEleInSubset = howManyElements(subsetState);
                
                
                for(int i=0; i<numOfEleInSubset;i++)
                {
                    if(subsetState[i]!=-3)
                    {
                        
                        
                        findInputsTransitionState(x, y, z, table, subsetState[i], ascii[inputCounter-1], currArr);
                        
                        
                        //copy the values to unionArr --> check to see if there are duplicated values
                        copyArr1ToArr2(currArr, unionArr);
                        
                        resetINTArray(currArr);
                        
                    }
                    
                    
                    
                }
                inputCounter++;
                
                //Only difference is that we dont want it to erase all of it but instead as long as it cotains it we are fine
                
                
                copyArr1ToArr2(unionArr, subsetState);
                resetINTArray(unionArr);
                
                
                
            }
        }
        
    }
    
    
    
    
}



BOOLEAN isEmpty(int array[])
{
    for(int i=0;i<MAX;i++)
    {
        if(array[i]!=NONE)
        {
          return FALSE;
        }
        
    }
    
    return TRUE;
}

BOOLEAN currentSetStateHoldsMoreThanOne(int ourArr[])
{
    int counter=0;
    for(int i=0; i<MAX;i++)
    {
       if(ourArr[i]!=NONE)
       {
           counter++;
       }
        
    }
  
    //printf("currentSetStateHoldsMoreThanOne: counter value is %d\n", counter);
   
    
    if(counter>1)
    {
        return TRUE;
    }
    
    return FALSE;
    
    
}

//////////////////////////////// possibility in deleting (BELOW) ////////////////////////////////////////////////

void copyArr1ToArr2(int arr1[], int arr2[])
{
    
    for(int i=0;i<MAX;i++)
    {
        if(arr1[i]!=NONE)
        {
            
            
                if(noDuplicatesInArray(arr1[i], arr2)==-1)
                {
                 
                    int numOfEle = howManyElements(arr2);
                    arr2[numOfEle] =arr1[i];
                  
                   
                    
                
                }
            
        }
        
        
        
        
    }
    
    
    //printf("copyARR1ToArr2: method performed and copied...\n");
    
    
}

BOOLEAN noDuplicatesInArray(int arr1Num, int arr2[])
{
    int numEle=howManyElements(arr2);

    for(int i=0;i<numEle;i++)
    {
        //if this is false
     if(notADuplicate(arr1Num, arr2[i])==-2)
     {
         return FALSE;
     }
        
    }
    
    return TRUE;
    
}



BOOLEAN notADuplicate(int num1, int num2)
{	
    
    if(num1==num2)
    {
        return FALSE
        
    }
    else if((num2==NONE)||(num2==NONACCEPT)||(num2==ACCEPT))
    {
        return FALSE
    }	
    
    
    
    return TRUE;
}




int howManyElements(int arr[])
{
    int elements = 0;
    
    for(int i=0; i<MAX;i++)
    {
        if(arr[i]!=-3)
        {
            elements++;
        }
        
        
    }
    
    return elements;
    
    
}

void runNfaProgram()
{
    printf("Please enter the NUMBER for the type of NFA automata you would like to test?\n 1) string that ends with 'man'\n 2) Strings with more than one a, g, h, i, o, s, t, or w, or more than two n’s\n 3) a string consisting of ONLY a's and/or b's\n");
    scanf("%d", &type);
    
    if(type==1)
    {
        findAcceptingStates(4, 4, 6, endMan);
        questionPrompt();
        letterToASCII(letters);
        
        findCurrSetStateEND(4,4,6,endMan);
        if(CheckIfAccStateNFA(subsetState)==-1)
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
        findAcceptingStates(20, 10, 4, washington);
        questionPrompt();
        letterToASCII(letters);
        
        findCurrSetStateCONTAIN(20,10,4,washington);
        if(CheckIfAccStateNFA(subsetState)==-1)
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
        
            findAcceptingStates(2, 2, 4, ab);
            questionPrompt();
            letterToASCII(letters);
        
            findCurrSetStateEND(2,2,4,ab);
            
    
        
        if(noMatchFound==-1)
        {
            printf("Your string has NOT been accepted\n");
        }
        
        else if((CheckIfAccStateNFA(subsetState)==-1) && (noMatchFound==-2) )
        {
            printf("Your string has been ACCEPTED\n");
        }
        else
        {
            printf("Your string has NOT been accepted\n");
        }
        
        
        
    }
        
    
    
}


//////////////////////////////// //////////////////////////////// ////////////////////////////////////////////////



/*

int main(int argc, const char * argv[]) {
    
    
    runNfaProgram();
    
    
    
    
    
    
}
*/

    
    
















