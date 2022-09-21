/*
    Program description:
        This program is an ecryption decryption program. It displays a menu of services for the user, 
        the user gets to choose the srvice they want. The user can enter a number and encrypt it to verify
        if it is the correct code. The user can decrypt as well after encryption. After that the user can 
        display the number of successful/unsuccessful verification. Final service is to end the program. 
        Each service including displaying the menu has a different function. 
        
        This program will not verify an encrypted code more than once. Encryption can only happen if code was
        entered. Decryption happen only if code was already encrypted. The program checks with user if they are 
        are sure they want to end the program. 

        This program validates input for user in menu choice, it also does not allow the user to enter a digit that
        is larger than 9 or smaller than 0.

    Author:
        Raghd Al Juma
    Date:
        22/02/2021
    Compiler: 
        VSC
*/

//Libraries
#include <stdio.h>

//Defined values
#define SIZE 4
#define SWAP1 0
#define SWAP2 1
#define SWAP3 2
#define SWAP4 3

//Prototypes
void displayMenu(char*);
void input(int*);
void encrypt(const int*,int*,int*,int*,int*);
void decrypt(int*);
void display_codeInfo(int*, int*);
void exitProgram(int*);

int main()
{
    //Declared variables
    const int access_code[SIZE] = {4,5,2,3};
    int input_code[SIZE] = {0} ;
    char menu_choice;
    int input_status = 0;
    int encryption_status = 0;
    int valid = 0;
    int decryption_status = 0;
    int successful = 0;//successful code encryption
    int failed = 0;//failed code encryption
    int i;
    int end = 1;

    //do while loop for displaying menu and rest of services
    do
    { 
        //display the menu
        displayMenu(&menu_choice);

        //switch case for user menu's choice
        switch (menu_choice)
        {
            case '1': 
            {
                // make valid = 0, so that successful code can be incremented
                valid = 0;
                //input status becomes 1 (True)
                input_status = 1;

                //encryption status is 0 (False)
                encryption_status = 0;

                //call function for code input
                input(input_code);

                break;

            }//end case 1

            case '2': 
            {
                //encryption happen only if user entered a code and did not encrypt already
                if (input_status == 1 && encryption_status == 0)
                { 
                  //call encryption function
                  encrypt(access_code, input_code, &successful, &failed, &valid); 

                  //encryption becomes 1 and decryption becomes 0
                  encryption_status = 1;
                  decryption_status = 0;

                }//end if

                //if user already encrypted or did not enter a code first, inform user
                else
                {
                  printf("\n Please input code first and make sure code has not been already encypted!\n");
                }//end else

                break;

            }//end case 2

            case '3': 
            {
                //decrypt only if encryption happned already and decryption did not.
                if (encryption_status == 1 && decryption_status == 0)
                {
                  //call decryption function
                  decrypt(input_code);

                  //encryption becomes 0 (false) and decryption becomes 1 (true)
                  encryption_status = 0;
                  decryption_status = 1;

                }//end if

                //inform user that encrypted code does not exist to decrypt it.
                else
                {
                  printf("\n Please encrypt first!\n");

                }//end else

                break;

            }//end case 3

            case '4':
            {
                //call function for displaying successful and failed codes
                display_codeInfo( &successful, &failed);

                break;

            }// end case 4

            case '5':
            { 
                //call exiting function
                exitProgram(&end);

                break;

            }//end case 5

        }//end switch
    } 
    while (end != 0);//When user chooses to exit program.

    return 0;

}//end main

/*
    A function that when called, it displays the Menu of 
    which the user can choose and allow user to enter their
    choice. User input is verified for invalid input.
*/
void displayMenu(char *menu)
{

    //Print menu to user 
    printf("\n Please choose the service you would like:\n");
    printf("1. Enter any code\n");
    printf("2. Encrypt code entered and verify if correct (i.e., matches the authorised access code, i.e., 4523)\n");
    printf("3. Decrypt code\n");
    printf("4. Display the number of times the encrypted code entered matches them authorised code (i) Successfully (ii) Incorrectly\n");
    printf("5. Exit Program\n");
    
    //do loop to scan and verify user input
    do
    {   
        //scan choice
        *menu = getchar();
        
        //if input is not valid inform user
        if(*menu != '1' && *menu != '2' && *menu != '3' && *menu != '4' && *menu != '5')
        {
          printf("\nPlease make sure your choice is between 1 - 5\n");

        }//end if

    }//end do
    //keep looping while input is incorrect
    while(*menu != '1' && *menu != '2' && *menu != '3' && *menu != '4' && *menu != '5');

}// end displayMenu function

/*
    This function allows the user to enter their code of 4 digits, it validates input
    to make sure digit is not larger than 9 or smaller than 0.
*/
void input(int *input)
{   
    //declared variables
    int i;//index
    int valid = 0;

    //Ask user to enter code
    printf("\nEnter the 4-digit code...\n");

    //scan code
    for(i = 0; i < SIZE; i++)
    {
        //do while loop to validate the user input
        do
        {
            if (*(input + i) < 0 || *(input + i) > 9)
            {
                printf("\nPlease enter only 1 digit\n");
            }

            //scan digit by digit
            printf("\nEnter digit number %d \n",(i+1));
            scanf("%d", & *(input + i));

        }//end do
        //keep looping while input digit is invalid
        while (*(input + i) < 0 || *(input + i) > 9);
    }//end for
    
}//end input function

/*
    This function takes in a 4 digit number and encrypt it by 
    swapping and adding numbers. It check s the validation with 
    the constant access code and count number of succes in validation.
*/
void encrypt(const int *access_code,int *input_code,int *successful, int *failed, int *check)
{
    //declared variables
    int temp,i;
    int valid = 0;

    //swap 1st with 3rd
    temp = *(input_code + SWAP1);
    *(input_code + SWAP1) = *(input_code + SWAP3);
    *(input_code + SWAP3) = temp;

    //swap 2nd with 4th
    temp = *(input_code + SWAP2) ;
    *(input_code + SWAP2) = *(input_code + SWAP4);
    *(input_code + SWAP4) = temp;

    //Add 1 to all digits
    for (i = 0; i < SIZE; i++)
    {
        *(input_code + i) = *(input_code + i) + 1;

        //if outcome is = 10, make digit = 0
        if (*(input_code + i) == 10)
        {
            *(input_code + i) = 0;

        }//end if

    }//end if

    //check each digit from encrypted input with access code digits
    for (i = 0; i < SIZE; i++)
    {
        //if input code digit = access code digit, increment valid
        if (*(input_code + i) == *(access_code + i))
        {
            //count valid numbers
            valid = valid + 1;

        }//end if

    }//end for

    // Validate code with access code, if valid = 4. code is correct
    if ( valid == SIZE && *check == 0)
    {
        //increment successful codes
        *successful = *successful + 1;

        //make check = 1 so that if encryption happen again to the same code, successful attepts will not be incremented
        *check = 1;

        //inform user
        printf("\nCorrect code entered\n");

    }//end if

    else if (valid != SIZE && *check == 0)
    {
        //increment failed codes
        *failed = *failed + 1;

        //make check = 1 so that if encryption happen again to the same code, successful attepts will not be incremented
        *check = 1;

        //inform user
        printf("\nWrong code entered\n");

    }//end else

    //print encrypted code
    printf("\nThe encrypted code is:\n"); 
    for (i = 0; i < SIZE; i++)
    {
      printf("%d",*(input_code + i));
    }//end if

}//end encryption function

/*
    This function takes in a 4 digit number and decrypt it by 
    swapping and substracting numbers. 
*/
void decrypt(int* input_code)
{
    //declared variables
    int temp,i;

    //swap 1st with 3rd
    temp = *(input_code + SWAP1) ;
    *(input_code + SWAP1) = *(input_code + SWAP3);
    *(input_code + SWAP3) = temp;

    //swap 2nd with 4th
    temp = *(input_code + SWAP2) ;
    *(input_code + SWAP2) = *(input_code + SWAP4);
    *(input_code + SWAP4) = temp;

    //substract 1 from all digits
    for (i = 0; i < SIZE; i++)
    {
        *(input_code + i) = *(input_code + i) - 1;

        //if digit = -1 , make it 9
        if (*(input_code + i) == -1)
        {
            *(input_code + i) = 9;

        }//end if

    }//end for

    //print decrypted code
    printf("\nThe decrypted code is\n");
    for (i = 0; i < SIZE; i++)
    {
      printf("%d",*(input_code + i));
    }//end for

}//end decryption function

/*
  This function displays the number of successful and failed codes encrypted
*/
void display_codeInfo(int* successful, int* failed)
{
    printf("\n The number of successful attempts is %d\n", *successful);
    printf("\n The number of failed attempts is %d\n", *failed);

}//end display function

/*
    This function checks with user if they want to end the program or not, The user reply is validated
*/
void exitProgram(int *choice)
{   
    char answer;
    int finish = 0;

    while(1)
    {
        //display message
        printf("\nAre you sure you want to end the program Please enter Y for yes and N for No (Y/N) ? \n ");

        //buffer catch for scanf
        while (getchar () != '\n' );
        scanf("%c", & answer);
        
        if (answer == 'Y' || answer == 'y')
        {
            //make choice 0, so program ends in main function
            *choice = 0;

            //display message
            printf("\n Program ends now.\n");

            break;

        }//end if

        if (answer == 'N' || answer == 'n')
        {
            //make choice = 1 so program resumes in main function
            *choice = 1;

            //display message
            printf("\nProgram resumes\n");

            break;

        }//end if

        //if input is invalid, inform user
        if (answer != 'Y' && answer != 'N')
        {
            printf("\n Invalid input\n");

        }//end if

    }//end while loop

}//end exitProgram function