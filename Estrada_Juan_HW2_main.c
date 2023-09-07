/**************************************************************
* Class:  CSC-415-03 Fall 2023
* Name: Juan Estrada
* Student ID: 923058731
* GitHub Name: jjestrada2
* Project: Assignment 2 – Command Line Arguments
*
* File: Estrada_Juan_HW2_main.c
*
* Description: In the main function, command-line arguments are 
used to populate a personalInfo structure with personal details, 
such as the first and last name, student ID, grade level, knowl-
edge of various programming languages, and a message. These deta-
ils are then written using the writePersonalInfo function. The 
program proceeds to allocate a buffer and processes a series of 
strings obtained from the getNext function. It copies these strings
into the buffer, ensuring that the buffer does not exceed a specified 
block size. When the buffer is full or all strings have been 
processed, it commits the data using the commitBlock function. 
The final step is to call the checkIt function to validate the
stored personal information. After freeing allocated memory, 
the function returns an exit code based on the success of the 
checkIt function, providing feedback on the execution of the program.
*
**************************************************************/
#include <assignment2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int main( int argc, char* argv[]){
   //Allocate Memory for Personal Info
    personalInfo *myInfo = (personalInfo*)malloc(sizeof(personalInfo));
    if(myInfo==NULL){
        printf("Proble allocating memory");
        exit(1);
    }
    //copy first argument (name) to struct
    myInfo->firstName = argv[1];
    //copy second argument (Last name) to struct
    myInfo->lastName = argv[2];
    //Set my student ID in the struct 
    myInfo->studentID = 923058731;
    //Set my grade level to SENIOR
    myInfo->level = SENIOR;
    //set the Languages using the bitmap
    myInfo->languages = KNOWLEDGE_OF_C | KNOWLEDGE_OF_JAVA | 
    KNOWLEDGE_OF_JAVASCRIPT | KNOWLEDGE_OF_INTEL_ASSEMBLER 
    | KNOWLEDGE_OF_HTML| KNOWLEDGE_OF_CPLUSPLUS| KNOWLEDGE_OF_PYTHON|
    KNOWLEDGE_OF_SQL;


    //Copy message from argument[3] to the struct
    strncpy(myInfo->message, argv[3], sizeof(myInfo->message));
    

    //Check information was successfully written with the function provided 
    int result = writePersonalInfo(myInfo);
    if(result == 0){
        printf("Personal information successfully written. \n");
    }else{
        printf("Error failed to write personal information. \n");
    }

   //Allocate a buffer
    char *buffer = (char*)malloc(BLOCK_SIZE);
    const char* nextString;
    size_t indx = 0;


    //Process and commit strings
    while((nextString = getNext()) != NULL){
    
        size_t stringLength = strlen(nextString);
        // If current string fits in the buffer copy it
        if(indx + stringLength <= BLOCK_SIZE){
            memcpy(buffer + indx,nextString,stringLength);
            indx += stringLength;
           
        }else{
            
        // If the current string doesn't fit 
            size_t spaceLeft= BLOCK_SIZE - indx; 
            memcpy(buffer+indx ,nextString, spaceLeft);
           
            commitBlock(buffer);
            indx = 0;
            // Copy the remaining portion of nextString to the buffer from indx 0
            
            memcpy(buffer+indx, nextString + spaceLeft, stringLength-spaceLeft);
            indx = stringLength-spaceLeft;    
        
        }


    }

    if (indx != 0) {
    commitBlock(buffer);
}
    
    int solution = checkIt();
    free(myInfo);
    free(buffer);
    //return 0 successful execution
    return solution;
}