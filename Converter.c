//
//  Converter.c
//  173_HW
//
//  Created by Matthew Lee on 9/21/17.
//  Copyright © 2017 Matthew Lee. All rights reserved.
//

#include "Converter.h"
#include "NFA.c"





 // we ask them for an input in string form..... and then we have it tested on all 3 of the NFA
    //then we create a method that creates an 2d array of that type of NFA and
    //then use that array and have it use the DFA methods

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int typeOfNFA=0;

void takingInputStringForConversion();
void determineNFAType1();
void determineNFAType2();
void determineNFAType3();
void runConverter();


//i determined the set construction's value by using the powers of 2
// i.e.) {0} = 2^0 = 1
//       {0,1} = (2^0) + (2^1) = 1+2 = 3
//       {0,2} = (2^0) + (2^2) = 1+4=5
// basically add them up by the powers of 2 in respective order to get their "state" value


int abDFA[2][6] = {{3,97,3,98,1,NONACCEPT},{3,97,3,98,1,ACCEPT}};

int manDFA[4][8] ={{3,109,1,97,1,110,1,NONACCEPT},{3,109,5,97,1,110,1,NONACCEPT},{3,109,1,97,1,110,1,NONACCEPT},{3,109,1,97,1,110,1,ACCEPT}};



void takingInputStringForConversion()
{
    printf("Please enter in the LEGNTH of your string...\n");
    scanf("%d", &strlength);
    
    printf("Now enter in your STRING that you would like to convert...\n");
    scanf("%s", letters);
    
    
}

void determineNFAType1()
{
    findAcceptingStates(4, 4, 6, endMan);
    letterToASCII(letters);
    
    findCurrSetStateEND(4,4,6,endMan);
    if(CheckIfAccStateNFA(subsetState)==-1)
    {
        
        typeOfNFA =1;
    }
    
    
    
    
    
}

void determineNFAType2()
{
    findAcceptingStates(20, 10, 4, washington);
    letterToASCII(letters);
    
    findCurrSetStateCONTAIN(20,10,4,washington);
    if(CheckIfAccStateNFA(subsetState)==-1)
    {
        
        typeOfNFA =2;
    }
    
    
    
    
    
}

void determineNFAType3()
{
    findAcceptingStates(2, 2, 4, ab);
    letterToASCII(letters);
    
    findCurrSetStateCONTAIN(2,2,4,ab);
    
    
    
    
    if((CheckIfAccStateNFA(subsetState)==-1) && (noMatchFound==-2) )
    {
        typeOfNFA=3;
    }

    
    
    
    
}

void runConverter()
{
    
    printf("Which type of NFA->DFA string would you like to test?\n \n 1) string that ends with 'man'\n 2) Strings with more than one a, g, h, i, o, s, t, or w, or more than two n’s\n 3) a string consisting of ONLY a's and/or b's\n");
    scanf("%d", &typeOfNFA);
    printf("Your string is of type %d\n", typeOfNFA);
    
    
}







//////////////////////////////////////////////////M A I N/////////////////////////////////////////////////////////////////

/*
int main(int argc, const char * argv[]) {
    
   
    
   
    
    
    
    
    
}
*/
