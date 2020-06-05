
                                                                     ///HOSTEL ROOM BOOKING SYSTEM

#include <stdio.h> ///for input output functions like printf, scanf
#include <stdlib.h>
#include <conio.h>
#include <windows.h> ///for windows related functions
#include <string.h>  ///string operations

/** List of Global Variable */
COORD coord = {0,0}; /// top-left corner of window

/**
    function : gotoxy
    @param input: x and y coordinates
    @param output: moves the cursor in specified position of console
*/
void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

/** Main function started */

int main()
{
    FILE *fp, *ft; /// file pointers
    char another, choice;
    int i,j,seat;
    /** structure that represent a employee */
    struct book
    {
        char name[40]; ///name of student
        char roll_num[8]; /// roll number of student
        char ref_no[60];///fees payment id
		char contact_no[25];///contact number
		char depart[75];///department of student
		int year;///year of study
		int room;//room number student want to book 
    };
    struct book e,f; /// structure variable creation
	char roll[8]; /// string to store  roll number of student
    long int recsize; /// size of each record of employee
    /** open the file in binary read and write mode
    * if the file EMP.DAT already exists then it open that file in read write mode
    * if the file doesn't exit it simply create a new copy
    */
    fp = fopen("book1.DAT","rb+");
    if(fp == NULL)
    {
        fp = fopen("book1.DAT","wb+");
        if(fp == NULL)
        {
            printf("Connot open file");
            exit(1);
        }
    }
    /// sizeo of each record i.e. size of structure variable e
    recsize = sizeof(e);
    /// infinite loop continues untile the break statement encounter
    while(1)
    {
        system("cls");///clear the console window
		gotoxy(23,7); 
		printf("******************************"); 
		gotoxy(23,8); /// move the cursor to postion 30, 10 from top-left corner
        printf("WELCOME TO ROOM BOOKING SYSTEM");
		gotoxy(23,9); 
		printf("******************************");
		gotoxy(30,10); /// move the cursor to postion 30, 10 from top-left corner
        printf("1. Book Room"); /// option for add record
        gotoxy(30,12);
        printf("2. List all booking"); /// option for showing existing record /// option for editing record
        gotoxy(30,14);
        printf("3. Cancel room"); /// option for deleting record
        gotoxy(30,16);
        printf("4. Exit"); /// exit from the program
        gotoxy(30,18);
        printf("Your Choice: "); /// enter the choice 1, 2, 3, 4, 5
        fflush(stdin); /// flush the input buffer
        choice  = getche(); /// get the input from keyboard
        switch(choice)
        {
        case '1':  /// if user press 1
            system("cls");///clear the console window
            fseek(fp,0,SEEK_END); /// search the file and move cursor to end of the file
            /// here 0 indicates moving 0 distance from the end of the file
            another = 'y';
            while(another == 'y')  /// if user want to add another record
            {
                printf("\nENTER YOUR DETAILS:\nEnter name: ");
                scanf("%s",f.name);
				printf("\nEnter roll number(7digit)(example=1713241): ");
                scanf("%s",f.roll_num);
                printf("\nEnter contact number(10 digit): ");
                scanf("%s", f.contact_no);
                printf("\nEnter payment reference number(12digit):");
                scanf("%s",f.ref_no);
                printf("\nEnter department(like CSE/EEE): ");
                scanf("%s", f.depart);
                printf("\nEnter year of study(1/2/3/4): ");
                scanf("%d", &f.year);
			    system("cls");	 
			    gotoxy(30,3);
				///loop for creating hostel building structure 
			    for(i=3;i<=30;i++)
			    {
				   for(j=7;j<=70;j++)
			       { if(((i%3==0)||(j%7==0))&&(((j<=21)||(j>=56))||((i<=9)||(i>=24))))      
				       printf("*");
				     else
				       printf(" ");
			       }
			        gotoxy(30,i+1);
			    }
			    gotoxy(31,4);
			    seat=1; 
			    printf("%d",seat);
			    ///for printing the room number
			    for(i=0;i<63;i=i+7)
			    {
			       for(j=0;j<27;j=j+3)
			       { gotoxy(31+i,4+j);
			          if((i<14)||(i>42)||(j<6)||(j>18))
				      {
				        if((i==0&&j==0)||(i==7&&j==3)||(i==0&&j==24)||(i==7&&j==21)||(i==56&&j==0)||(i==49&&j==3)||(i==56&&j==24)||(i==49&&j==21))
				        {
				  	       printf("TOILET");
				  	       gotoxy(31+i,4+j+1);
				        }
				        else if(i==28&&j==24)
				        {
				  	       printf("EXIT");
				  	       gotoxy(31+i,4+j+1);
				        }   	
				       else
				       {
				           printf("%d",seat);
				           fseek(fp,0,SEEK_SET);
				           ///printing status of booking of all the room
                           while(fread(&e,recsize,1,fp) == 1)  /// read all records from file
                           {
                              if(e.room==seat)  /// if the entered record match
                              {
                              gotoxy(31+i,4+j+1);
         				      printf("YES");
         				      break;
                   /// move all records except the one that is to be deleted to temp file
                              }
                           } 
				        seat++;
			           }
			          }
			       }    				  
		       }printf("\nNOTE:");        
		        printf("\nInner square=First floor");
                printf("\nOuter square=Ground floor"); 
                printf("\nBooked room=YES"); 
				printf("\nTake above picture as reference");    
	            printf("\n\nEnter room number you want to book which is NOT marked with YES: ");
                scanf("%d",&f.room);//read room number the student want to book
				fseek(fp,0,SEEK_END);
				fwrite(&f,recsize,1,fp); /// write the record in the file
				printf("\nDo you want to book another room(y/n) ");
                fflush(stdin);
                another = getche();
            }
            break;
        case '2':
            system("cls");///clear the console window
            rewind(fp); ///this moves file cursor to start of the file
            printf("ROLL_NO||  CONTACT ||ROOM||FEES_PAYMENT_ID||YEAR OF STUDY||BRANCH||NAME");           
		    while(fread(&e,recsize,1,fp)==1)  /// read the file and fetch the record one record per fetch
            {
                printf("\n%s  %s   %d      %s        %d           %s   %s",e.roll_num,e.contact_no,e.room,e.ref_no,e.year,e.depart,e.name);
            }
            getch();
            break;
        case '3':
            system("cls");///clear the console window
            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter your correct roll number to delete booked seat:");
                scanf("%s",roll);
                ft = fopen("tem.dat","wb");  /// create a intermediate file for temporary storage
                rewind(fp); /// move record to starting of file
				while(fread(&e,recsize,1,fp) == 1)  /// read all records from file
                {
                    if(strcmp(e.roll_num,roll)!= 0)  /// if the entered record match
                    {  
                        fwrite(&e,recsize,1,ft); /// move all records except the one that is to be deleted to temp file
                    }
                }
               fclose(fp);
               fclose(ft);
    		   remove("book1.DAT"); /// remove the orginal file
               rename("tem.dat","book1.DAT"); /// rename the temp file to original file name
               fp = fopen("book1.DAT", "rb+");/// remove the orginal file 
               printf("\nDelete Again(y/n)");
               fflush(stdin);
               another = getche();
            }
            break;
        case '4':
            fclose(fp);  /// close the file
            exit(0); /// exit from the program
        }
    }
    return 0;
}
