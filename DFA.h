//
//  DFA.h
//  173_HW
//
//  Created by Matthew Lee on 9/19/17.
//  Copyright © 2017 Matthew Lee. All rights reserved.
//

#ifndef DFA_h
#define DFA_h
#define TRUE -1;
#define FALSE -2;


#include <stdio.h>

typedef int BOOLEAN;



//finds the accepting states from our transition table
extern int* FindAcceptingStates(int m, int n, int table[m][n]);

//find the transition state we are at once all of the input has been read
extern int GetStringTransitionState(int m, int n, int table[m][n]);

//tells us whether we can find a match or not from our transition table
extern BOOLEAN CannotFindMatch(int input,int m, int n, int table[m][n]);

//checks to see if we have gotten an accepting state
extern BOOLEAN CheckIfAccState(int value);





//methods outside of calculations:

//to clear our accept array for other future procedures
extern int* resetAcceptArray(int acceptArray[]);

//the thing "start" button for the program
extern void runDfaProgram();




#endif /* DFA_h */
