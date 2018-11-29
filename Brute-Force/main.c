//
//  main.c
//  Bruteforce
//
//  Created by Wilson Brown on 11/28/18.
//  received help from William Wright
//
#include <stdio.h> //default libary
#include <unistd.h>//to handle the crypting
#include <string.h> //to handle the parseing of the file
#include <time.h>//to get the time in our program
struct Userinfo {
    char username[100];//the username of the user account
    char encryptedpassword[100];//the encripted password of the user
    char decriptedpassword[100];//the decripted password of the user
    int Passwordstried;//the amount of passwords tried untill decripted
    double runtime;//how long it took to find the password in secconds
};
int main(int argc, const char * argv[]) {
    FILE *fp;//our file
    int totalusers = 0;  // the total amount of users in the file
    char filename[] = "cw.dat";
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
    char salt[] = "pw";//our "salt" password to use with decripting
    char testpass[10];//this is the varable that is going to get changed based on the brute force loops
    static const char alphupper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";//our alphabet of uppercase letters
    static const char alphlow[] = "abcdefghijklmnopqrstuvwxyz";//our alphabet of lower letters
    static const char numa[] = "123456789";//our alphabet of numbers
    static const int aupperlen = sizeof(alphupper) - 1;//the size of the uppercase letter aplphabet for the for loops
    static const int alowerlen = sizeof(alphlow) - 1;//the size of the lower letter aplphabet for the for loops
    static const int numlen = sizeof(numa) - 1;//the size of the number alphabet for the for loops
  struct Userinfo Accounts[totalusers];//this is where we declare the array of the structure allowing for us to save each person from the file seperatly
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
   int PasswordTriedCounter=0;//the counter for the total amount of passwords tried
    clock_t start = clock();//this is where we start the timer for cracking passwords
        for(int i=0;i<aupperlen;i++){//the first for loop increments the first charactor in the string with an uppercase letter from the aplhabet
            testpass[0]=alphupper[i];//add/change the letter
            for(int i=0;i<alowerlen;i++){//this adds/changes the lowercase value of the string at index[i]
                testpass[1]=alphlow[i];//add/change the letter
                for(int i=0;i<alowerlen;i++){//this adds/changes the lowercase value of the string at index[i]
                    printf("Currenly Trying Passwqord: [%s], %d Passwords Already Tried]\n",testpass,PasswordTriedCounter);//print the current password we are trying
                    clock_t end = clock();//stop the clock to see the current time
                    printf("current time Solving %lf\n",(end-start)/(double)CLOCKS_PER_SEC);//print the current time
                    printf("Trying Passwords......\n");
                    testpass[2]=alphlow[i];//add/change the letter
                    for(int i=0;i<alowerlen;i++){//this adds/changes the lowercase value of the string at index[i]
                        testpass[3]=alphlow[i];//add/change the letter
                        for(int i=0;i<alowerlen;i++){//this adds/changes the lowercase value of the string at index[i]
                            testpass[4]=alphlow[i];//add/change the letter
                            for(int i=0;i<alowerlen;i++){//this adds/changes the lowercase value of the string at index[i]
                                testpass[5]=alphlow[i];//add/change the letter
                                for(int i=0;i<alowerlen;i++){//this adds/changes the lowercase value of the string at index[i]
                                    testpass[6]=alphlow[i];//add/change the letter
                                    for(int i=0;i<numlen;i++){//this adds/changes the number value of the string at index[i]
                                        testpass[7]=numa[i];//add/change the number
                                        //everytime we loop through we take the decripted value we have currently from the for loops
                                        //we encript it to check of the encripted password is the same as the one we have from the file
                                        //if the values match then we save that password, time, and amount of tries to the structure value for that user
                                        char *currentcheck = crypt(testpass, salt);//encript the current string
                                        for(int i=0;i<totalusers;i++){//run through the structure of users
                                            if(strcmp(Accounts[i].encryptedpassword,currentcheck) == 0){//check for each user if the values match
                                                sprintf(Accounts[i].decriptedpassword,"%s",testpass);//if the values match we add the decripted value to the structure
                                                clock_t end = clock();//stop the clock for time
                                                Accounts[i].runtime = (end-start)/(double)CLOCKS_PER_SEC;//save the current time it took to the users struct
                                                Accounts[i].Passwordstried = PasswordTriedCounter;//save the current tries to the users struct
                                                PasswordsCracked++;//increment the total cracked value
                                                printf("found password:[%s] for Account %s\n",Accounts[i].decriptedpassword,Accounts[i].username);//tell the user
                                                printf("%d/%d Passwords Cracked\n",PasswordsCracked,totalusers);//print how mant we have found and how many we have left
                                            }
                                        }
                                        if(PasswordsCracked==totalusers){//this is the final check to see if we have all the users passwords when all are decripted this wil run and print all the info for the users
                                            printf("----------------------------------------------------------\n");
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
