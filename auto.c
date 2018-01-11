//
//  auto.c
//  173_HW
//
//  Created by Matthew Lee on 9/21/17.
//  Copyright © 2017 Matthew Lee. All rights reserved.
//



#include <stdio.h>
#include "DFA.c"
#include "Converter.c"


int optionNum;

int main(int argc, const char * argv[]) {
    
    printf("Hi there! This program is designed to determine whether your string input is to be accepted by specific types of automata.\n With that what would you like to do (PLEASE ENTER IN THE OPTION'S NUMERICAL VALUE):\n 1) test strings on DFA automatas\n 2) test strings on NFA automatas\n ");
    
    scanf("%d", &optionNum);
    
    
    if(optionNum==1)
    {
        runDfaProgram();
    }
    else if(optionNum==2)
    {
        runNfaProgram();
    }
    
    
    
    
    
    
    
    
}

