//
//  Bruteforce.c
//  150-Final-Project
//
//  Created by Wilson Brown on 11/28/18.
//  received help from William Wright
//
#include <stdio.h> //default libary
#include <unistd.h>//to handle the crypting
#include <string.h> //to handle the parseing of the file
#include <time.h>//to get the time in our program

void GeneratePasswords(){//this function allows the user to create encripted passwords
    char password[20];//this is where the user defined password is stored
    printf("Enter a Password To Encrypt Ex Aaaaa1\nPassword: ");//tell the user
    scanf("%*c%[^\n]",password);//look for use inout
    printf("encrypting [%s]",password);//tell user
    char *currentcheck = crypt(password,"pw");//this is where we encrpyt the users password
    printf("You Encripted Password Is: %s\n\n",currentcheck);//tell the user
    printf("Would You Like To Add this Password to the File\n1 Yes, 2 No\nChoice: ");//inform
    int choice=0;//this is the menu deffanation
    scanf("%d",&choice);//scan for use inout
    char username[100];//this is where we will store the user entered username
    if(choice==1){//if the user tells the program to store the password in the file it will run this
        printf("Enter a Username for the password you encrypted\nUsername: ");
        scanf("%s",username);
        FILE *fp;//create the file
         char filename[] = "cw2.dat";//set the filename
        fp = fopen(filename, "a");//open the file
        fprintf(fp, "%s:%s\n",username,currentcheck);//prin the usename and pasdsword to the file
        printf("User [%s:%s] Added to File %s]\n",username,currentcheck,filename);//inform the user
        fclose(fp);//close the file
    }
    return;//return to the main menu
}

struct Userinfo {
    char passwordsalt[3];//added for a later adation of custom salts
    char username[100];//the username of the user account
    char encryptedpassword[100];//the encripted password of the user
    char decriptedpassword[100];//the decripted password of the user
    int Passwordstried;//the amount of passwords tried untill decripted
    double runtime;//how long it took to find the password in secconds
};
int main(int argc, const char * argv[]) {
    int choice;
    do{
        printf("|-----------------------------------------------|\n");
        printf("|          Welcome To The Decripter             |\n");
        printf("|   Press 1 To Generate Passwords From Input    |\n");
        printf("|   Press 2 To Decript Passwords From The File  |\n");
        printf("|   Press 3 To Exit The Program                 |\n");
        printf("|-----------------------------------------------|\n");
        printf("Option: ");
        scanf("%d",&choice);
        if(choice==1){
            GeneratePasswords();//call to our create method
        }
        if(choice==3){
            _Exit(1);//exit
        }
    }while(choice!=2);
    FILE *fp;//our file
    int totalusers = 0;  // the total amount of users in the file
    char filename[] = "cw2.dat";
    char c;  // To store a character read from file
    // Open the file
    fp = fopen(filename, "r");
    // Check if file exists
    if (fp == NULL)//we check for the file containg the users
    {
        printf("Please make sure the File %s Containing the users in Included\n", filename);//if the file isnt there we tell the log
        _Exit(1);//exit program
    }
    for (c = getc(fp); c != EOF; c = getc(fp))//keep going through each line of the file
        if (c == '\n') // Increment PasswordTriedCounter if this character is newline
            totalusers = totalusers + 1;//every line of the file we increment a user
    fclose(fp);// Close the file
    char testpass[]="Aaaaa1";//this is the varable that is going to get changed based on the brute force loops
    static const char alphupper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";//our alphabet of uppercase letters
    static const char alphlow[] = "abcdefghijklmnopqrstuvwxyz";//our alphabet of lower letters
    static const char numa[] = "123456789";//our alphabet of numbers
    static const int aupperlen = sizeof(alphupper) - 1;//the size of the uppercase letter aplphabet for the for loops
    static const int alowerlen = sizeof(alphlow) - 1;//the size of the lower letter aplphabet for the for loops
    static const int numlen = sizeof(numa) - 1;//the size of the number alphabet for the for loops
    struct Userinfo Accounts[totalusers];//this is where we declare the array of the structure allowing for us to save each person from the file seperatly
    memset(Accounts, totalusers, 0);    // clear object
    int LineCounter=0;//this is the counter used to tell our line in the file
    int PasswordsCracked=0;//this is the counter to tell how many passwords have been cracked
    char line[256];//the buffer for the line
    bzero(line, sizeof(line));//here we call memory to clear the buffer
    FILE *file = fopen(filename, "r");//here we reopen the file containing the users
    if ( file != NULL )//check if the file exists
    {
        while (fgets(line, sizeof line, file) != NULL) //this while loop go's through the file line by line
        {
            sscanf(line,"%80[^:]:%s",Accounts[LineCounter].username,Accounts[LineCounter].encryptedpassword);//parse the current line for the information on the user
            printf("found New User [%s:%s]\n",Accounts[LineCounter].username,Accounts[LineCounter].encryptedpassword);//print the information that we found in the file
            LineCounter++;//increment the counter for the line
        }
        fclose(file);//close the file
    }
    else//if the file dosent exist then we call this
    {
        printf("The File %s Is Corrupt.\nThe program loaded the file but couldnt acess it a seccond time.\n make sure the file isnt corrupt and rerun the program\n", filename);//if the file isnt there we tell the log
        _Exit(1);//exit program
    }
    printf("------------------------------------------------");//make it look nicer
    int PasswordTriedCounter=0;//the counter for the total amount of passwords tried
    clock_t start = clock();//this is where we start the timer for cracking passwords
    for(int i=0;i<aupperlen;i++){//the first for loop increments the first charactor in the string with an uppercase letter from the aplhabet
        testpass[0]=alphupper[i];//add/change the letter
        printf("\ncurrently Trying Password: [%s], %d Passwords Already Tried]\n",testpass,PasswordTriedCounter);//print the current password we are trying
        clock_t end = clock();//stop the clock to see the current time
        printf("current time Solving %lf Seconds\n",(end-start)/(double)CLOCKS_PER_SEC);//print the current time
        printf("Trying Passwords.");//make it look nicer
        for(int i=0;i<alowerlen;i++){//this adds/changes the lowercase value of the string at index[i]
            testpass[1]=alphlow[i];//add/change the letter
            printf(".");//add a peirod so we can see the progress
            for(int i=0;i<alowerlen;i++){//this adds/changes the lowercase value of the string at index[i]
                testpass[2]=alphlow[i];//add/change the letter
                for(int i=0;i<alowerlen;i++){//this adds/changes the lowercase value of the string at index[i]
                    testpass[3]=alphlow[i];//add/change the letter
                    for(int i=0;i<alowerlen;i++){//this adds/changes the lowercase value of the string at index[i]
                        testpass[4]=alphlow[i];//add/change the letter
                        for(int i=0;i<numlen;i++){//this adds/changes the number value of the string at index[i]
                            testpass[5]=numa[i];//add/change the number
                            //everytime we loop through we take the decripted value we have currently from the for loops
                            //we encript it to check of the encripted password is the same as the one we have from the file
                            //if the values match then we save that password, time, and amount of tries to the structure value for that user
                            char *currentcheck = crypt(testpass,"pw");//encript the current string
                            for(int i=0;i<totalusers;i++){//run through the structure of users
                                if(strcmp(Accounts[i].encryptedpassword,currentcheck) == 0){//check for each user if the values match
                                    sprintf(Accounts[i].decriptedpassword,"%s",testpass);//if the values match we add the decripted value to the structure
                                    clock_t end = clock();//stop the clock for time
                                    Accounts[i].runtime = (end-start)/(double)CLOCKS_PER_SEC;//save the current time it took to the users struct
                                    Accounts[i].Passwordstried = PasswordTriedCounter;//save the current tries to the users struct
                                    PasswordsCracked++;//increment the total cracked value
                                    printf("\nfound password:[%s] for Account %s\n",Accounts[i].decriptedpassword,Accounts[i].username);//tell the user
                                    printf("%d/%d Passwords Cracked\n",PasswordsCracked,totalusers);//print how mant we have found and how many we have left
                                    printf("------------------------------------------------\n");
                                    printf("Trying Passwords.");//added to make it look nicer
                                }
                            }
                            if(PasswordsCracked==totalusers){//this is the final check to see if we have all the users passwords when all are decripted this wil run and print all the info for the users
                                printf("\n----------------------------------------------------------\n");
                                printf("All Passwords have been Cracked\n");
                                for(int i=0;i<totalusers;i++){//run throught all the users in the structure
                                    printf("User %d.) Username: %s Password: %s\n",i+1,Accounts[i].username,Accounts[i].decriptedpassword);//print the username and password to the log
                                    printf("it took %lf Sec To Find Password\n",Accounts[i].runtime);//print the runtime
                                    printf("total amount of passwords tried: %d\n",Accounts[i].Passwordstried);//print the total amount of passwords tried
                                    printf("----------------------------------------------------------\n");
                                }
                                _Exit(1);//exit the program
                            }
                            //if the password didnt match we increment the counter
                            PasswordTriedCounter++;//incremnt the counter of passworss tied
                        }
                    }
                }
            }
        }
    }
    
    //if the forloop reaches here one of the passwords couldnt be cracked and the file needs to be checked to make sure it is correct
    printf("one of the passwords couldnt be cracked make sure that it was entered correcly into the file\n");\
    printf("each line of the file should look like this here is an example\nUSERNAME:PASSWORD\n");
    printf("please check the file and rerun the program\n");
    printf("----------------------------------------------------------\n");
    printf("A Password couldnt be Cracked\n");
    for(int i=0;i<totalusers;i++){//run throught all the users in the structure
        printf("User %d.) Username: %s Password: %s\n",i+1,Accounts[i].username,Accounts[i].decriptedpassword);//print the username and password to the log
        printf("----------------------------------------------------------\n");
    }
    return 0;//if the forloop finnishes "highly unlikely" then exit the program
}
