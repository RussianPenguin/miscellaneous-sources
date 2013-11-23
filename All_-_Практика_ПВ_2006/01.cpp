#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Прототипы
int GetWord(FILE*f,char*wrd);

void main(void)
{
  FILE*f;
  char **wrds;
  fopen(f,"r+w","text.txt");
  if((wrds = malloc(sizeof(pointer)))!=NULL)
  {
    wrds[0]=NULL;
    int count=0;
    int err;
    while((err = GetWord(f,wrds[count]))>0)
    {
      char **t;
      if((t = realloc(f,sizeof(char*)*(count+2)))!=NULL)
      {
        wrds[++count]=NULL;
        f=t;
      }
      else
      {
        for(/* */;count>=0;free(wrds[count]),count--);
        puts("Not available memory!\nProgram halted.");
        free(wrds);
        return;
      }
    }
    if(err == 0)
    {
      int cur1 = 0;
      char*a;
      a
      while(wrds[cur1]!=NULL)
      {
        cur1++;
      }
    }
    for(/* */;count>=0;free(wrds[count]),count--);
    free(wrds);
  }
}

//  1 - Успешное выполнение
//  0 - Конец файла
// -1 - Недостаточно места в памяти для размещения всего текста
// -2 - В памяти нет места для начала работы
// -3 - В памяти нет места для корректного завершения
int GetWord(FILE*f,char*wrd)
{
  char c;
  char*t;
  if((wrd = malloc(sizeof(char)))!=NULL)
  {
    wrd[0]='\0';
    int eof = 1, count = 0;
    fscanf(f,"%c",&c);
    
    while((c<=32)&&(!feof(f)))
      fscanf(f,"%c",&c);
    
    while((c>32)&&(!feof(f)))
    {
      fscanf(f,"%c",&c);
      if((t = realloc(f,sizeof(char)*(count+2)))!=NULL)
      {
        f=t;
        f[count]=c;
        f[++count]='\0';
      }
      else
      {
        eof=-1;
        break;
      }
    }
    
    if(feof(f))
    {
      eof=0;
      fscanf(f,"%c",&c);
      if(c>32)
      {
        if((t = realloc(f,sizeof(char)*(count+2)))!=NULL)
        {
          f=t;
          f[count]=c;
          f[++count]='\0';
        }
        else
          eof=-1;
      }
    }
  }
  else
    eof=-2;
  return eof;
}