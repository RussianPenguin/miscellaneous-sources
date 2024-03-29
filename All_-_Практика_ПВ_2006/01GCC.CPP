#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>

#define MAXCHAR 256
#define MAXBUF 30

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*************************  ���������� ����� ������ length � ������ buf �� ��������� f ***************************//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int fscanfn(FILE*t,char buf[],long length)
{
	int ret = 1, count = 0;
	buf[0] = '\0';
	static char ch = '\0';
	while((ch <= 32)&&(ret!=EOF))
		ret = fscanf(t,"%c",&ch);
	while((ret != EOF) && (ch > 32) && (count < length-1))
	{
		buf[count] = ch;
		buf[++count] = '\0';
		ret = fscanf(t,"%c",&ch);
	}
	if(ret == EOF)
		ch = '\0';
	else if(count == length - 1)
		return 0;
	return ret;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//****************************  ���������� ����� �� ��������� f �� ��������� str   ********************************//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getword(FILE*f,char *&str)
{
	static char buf[MAXBUF];
	int ret = 1;
	ret = fscanfn(f,buf,MAXBUF);
	if((buf[0]!='\0') && ((str = (char*)malloc(sizeof(char)*(strlen(buf)+1)))!=NULL))
	{
		char *tmp;
		strcpy(str,buf);
		while(ret == 0)
		{
			ret = fscanf(f,buf,MAXBUF);
			if((tmp = (char*)realloc(str,sizeof(char)*(strlen(str)+strlen(buf)+1)))!=NULL)
			{
				str = tmp;
				strcat(str,buf);
			}
			else
			{
        free(str);
        str = NULL;
				return -2;
			}
		}
	}
	else
		str = NULL;
	return ret;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void initset(char set[],int length)
{	for(;length>=0;set[length--]=0); }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fillset(char set[],char str[])
{	for(int i = strlen(str);i>=0;set[str[i--]]=1); }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void removestr(char **arr)
{
	while(*arr!=NULL)
	{
		*arr=*(arr+1);
		arr++;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int scan(char **arr,char *set)
{
	int ret = 0, rem = 0;
	while(*arr!=NULL)
	{
		char *t;
		t = *arr;
		ret = 1;
		while((*t)!='\0')
		{
			if(set[*(t++)]==0)
				ret = 0;
		}
		if(ret == 1)
		{
			removestr(arr);
			rem = 1;
		}
		else
			arr++;
	}
	return rem;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void remove(char **arr)
{
	char set[MAXCHAR];
	while(*arr!=NULL)
	{
		initset(set,MAXCHAR);
		fillset(set,*arr);
		if(scan((arr+1),set) == 1)
		{
			removestr(arr);
		}
		else
			arr++;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc,char **argv)
{
	FILE *f;
	char **arr;
	int ret = 0;
	unsigned long count = 2;
	if((f = fopen("temp.txt","r")) != 0)
	{
		char **tmp;
		if((arr = (char**)malloc(sizeof(char*)))!=NULL)
		{
			arr[0]=NULL;
			char *str;
			char **tmp;
			do{
				ret = getword(f,str);
				if(str!=NULL)
				{
					if((tmp = (char**)realloc(arr,sizeof(char*)*count)) != NULL)
					{
						arr = tmp;
						arr[count-2] = str;
						arr[count-1] = NULL;
						count++;
					}
					else
					{
						ret = -3;
						break;
					}
				}
			}while(ret > -1);
		}
		else
			ret = -4;
	}
	else
		ret = -5;
	switch(ret)
	{
		case -1:
			{
				count = 0;
				while(arr[count] != NULL)
				{
					puts(arr[count++]);
				}
				getch();
				remove(arr);
				count = 0;
				puts("New array");
				while(arr[count] != NULL)
				{
					puts(arr[count]);
					free(arr[count++]);
				}
				free(arr);
				break;
			}
		case -2:
			puts("Error while getting string!");
		case -3:
			{
				count = 0;
				while(arr[count] != NULL)
					free(arr[count++]);
				free(arr);
			}
		case -4:
			{
				puts("Not available memory!");
				break;
			}
		case -5:
			puts("File not found!");
	}
	fclose(f);
	puts("Press any key.");
	getch();
	return 0;
}
