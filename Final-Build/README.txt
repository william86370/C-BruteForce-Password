{\rtf1\ansi\ansicpg1252\cocoartf1671
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 README\
\
I included This Readme to clarify everything that you said from my last submission.\
to make sure we were on the same page and everything works as intended \
\
1.) HOW-TO-RUN\
this program was designed on MacOS and built for UNIX it will compile on MacOS And Linux \
 \
To Compile the program open a terminal and cd to the current directory that you have the Bruteforce.c program saved in. then type \'93make\'94 this will compile your program. \
after you compile the program all you have to do is type is ./Bruteforce and the program will launch\
\
2.) Running-The-Program\
Please make sure you have cw.dat included inside the directory that you are running the program from if you currently do not have the file there and attempt to decrypt the program will exit\
\
once you open the application you will have 3 options \
1.) Is to encrypt a new string \
the user will enter a string to encrypt the string you enter should be 1 Capitol-4 lowercase and 1 Number for a total of 6 characters and example is Baaaa1\
after encrypting a string you can add to to the cw.dat file by pressing 1 all it will ask for is a username and it will add the username and password to the file for decrypting. if you press 2 you will return to the main menu for other selections. \
\
2.)will start the decrypting processes\
it will add the users that you have in the file to a structure array and will start testing all the possible combinations of letters and numbers to find the right answer it will notify you for each password it cracks until all passwords are cracked or the program tries all passwords \
\
\
\
\
}