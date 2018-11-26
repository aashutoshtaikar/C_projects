#include<stdio.h>
#include <iostream>

void userInput();
void arrayElement();
void FinalCrypt();
int userIp[4];
char temp[10000];
int code;

char zero[]="===.===.===.===.===";
char one[]= "=.===.===.===.===";
char two[]= "=.=.===.===.===";
char three[]= "=.=.=.===.===";
char four[]= "=.=.=.=.===";
char five[]= "=.=.=.=.=";
char six[]= "===.=.=.=.=";
char seven[]= "===.===.=.=.=";
char eight[]= "===.===.===.=.=";
char nine[]= "===.===.===.===.=";

int main()
{
	userInput();
	arrayElement();
	FinalCrypt();
	return 0;
}

void userInput()
{
	printf("Enter your code\n");
	std::cin>>code;
	for (int i = 3; i >= 0; i--) 
	{
    	userIp[i] = code % 10;
    	code /= 10;
	}
};

void arrayElement()
{
	for( int i = 0; i < 4; i++ )
    {
    	if(userIp[i]==0)
    	for (int j = 0; j < 19; j++)
    	{
    		temp[j]=zero[j];
    	}
  		else if(userIp[i]==1)
  	  	for (int j = 0; j < 19; j++)
    	{
    		temp[j]=one[j];
    	}
		else if(userIp[i]==2)
		for (int j = 0; j < 19; j++)
    	{
    		temp[j]=two[j];
    	}
		else if(userIp[i]==3)
		for (int j = 0; j < 19; j++)
    	{
    		temp[j]=three[j];
    	}
    	else if(userIp[i]==4)
		for (int j = 0; j < 19; j++)
    	{
    		temp[j]=four[j];
    	}
    	else if(userIp[i]==5)
		for (int j = 0; j < 19; j++)
    	{
    		temp[j]=five[j];
    	}
		else if(userIp[i]==6)
		for (int j = 0; j < 19; j++)
    	{
    		temp[j]=six[j];
    	}
		else if(userIp[i]==7)
		for (int j = 0; j < 19; j++)
    	{
    		temp[j]=seven[j];
    	}
		else if(userIp[i]==8)
		for (int j = 0; j < 19; j++)
    	{
    		temp[j]=eight[j];
    	}
		else if(userIp[i]==9)
		for (int j = 0; j < 19; j++)
    	{
    		temp[j]=nine[j];
    	}
     }
}


void FinalCrypt()
{
printf("morse code:%s\n",temp);
};