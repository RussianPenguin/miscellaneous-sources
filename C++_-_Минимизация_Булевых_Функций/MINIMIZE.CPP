/*********************************************************/
/*                  Author: S7a1k3r                      */
/*              E-mail: S7a1k3r@mail.ru                  */
/*               WWW: S7a1k3r.narod.ru                   */
/*********************************************************/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <mem.h>

#define SIZE 16

#undef DEBUG
/*********************************************************/
/*               Описание типов для работы               */
/*********************************************************/
//Указатель на типичный элемент списка
typedef struct elem t_elemptr;
//Типичный элемент списка
typedef struct elem
{
	//Вектор вхождений и обращений в "одном лице"
	char in[SIZE];
	char obr[SIZE];
	//Результатом склеивания каких элементов стал текущий
	char *psklei;
	//Оно ва-а-аще минимизировалось?
	char min;
	//Указатель на следующий элемент
	t_elemptr *next;
	//Какой уровень склейки?
	char level;
} node;
typedef struct
{
	int n;
	t_elemptr* p;
} arel;

void printel(t_elemptr* p)
{
  int i,x,y;
	for(i=0;i<SIZE;i++)
	{
		if(p->in[i]==1)
		{
			printf("X%d",i+1);
			if(p->obr[i]==1)
			{
				x=wherex();y=wherey();
				gotoxy(x-2,y-1);
        printf("__");
        gotoxy(x,y);
       }
     }
	}
  x=wherex();y=wherey();
	if(x>=75-SIZE)
    printf("\n\n");
  printf("\\/");
}

void conec()
{
	gotoxy(wherex()-2,wherey());
  printf("  ");
}
/*********************************************************/
/*                    Вывод ДНФ функции                  */
/*********************************************************/
void OutputDNF(t_elemptr *p)
{
  printf("\n\nF=");
  if(p==NULL)
  {
    printf("0");
    getch();
    exit(0);
  }
  while(p!=NULL)
  {
		printel(p);
    p = p->next;
	}
	conec();
}
/*********************************************************/
/*              Удаление списка из памяти                */
/*********************************************************/
void remfromem(t_elemptr *first)
{
	t_elemptr *cur;
	while(cur != NULL)
	{
		cur = first->next;
		free(first->psklei);
		free(first);
		first = cur;
	}
}
/*********************************************************/
/*     Создаем вектор вхождений и вектор обращений       */
/*********************************************************/
void extract(t_elemptr *t,int res, int length)
{
	for(int i = length-1; i>=0; i--)
	{
		t->in[i] = 1;
		(res % 2 == 0)?(t->obr[i] = 1):(t->obr[i] = 0);
		res/=2;
	}
	for(i = length;i < SIZE; i++)
		t->in[i] = 0;
}
/*********************************************************/
/*                 Получаем ДНФ из файла                 */
/*********************************************************/
t_elemptr* getdnf(FILE*f,int &length)
{
	t_elemptr *first = NULL, *cur = NULL;
	if(fscanf(f,"%d",&length) > EOF)
  {
		int res, curel = 0,count = 0;
		while(fscanf(f,"%d",&res) > EOF)
		{
			curel++;
			if(res == 1)
			{
				count++;
				if(cur == NULL)
				{
					first = new node;
					cur = first;
				}
				else
				{
					cur->next = new node;
					cur = cur->next;
				}
				extract(cur,curel-1,length);
				if((cur->psklei = (char*)malloc(sizeof(char)))== NULL)
					break;
				cur->psklei[0] = count;
				cur->min = 0;
				cur->level = 1;
				cur->next = NULL;
			}
		}
		if(curel != 1<<length)
			remfromem(first);
	}
	return first;
}
/*********************************************************/
/*              Проверка на "склеивомость"               */
/*********************************************************/
t_elemptr* sklei(t_elemptr *t1, t_elemptr *t2, int length)
{
	char flag = 0, pos;
	int i = 0;
	while((i < length) && (t1->in[i] == t2->in[i]))
	{
		if(t1->obr[i] != t2->obr[i])
		{
			pos = i;
			flag++;
		}
		i++;
	}
	if((i == length) && (flag == 1))
	{
		t_elemptr *one = new node;
		t1->min = 1;
		t2->min = 1;
		one->level = t1->level + 1;
		int i;
		for(i = 0; i < SIZE; i++)
		{
			one->in[i] = t1->in[i];
			one->obr[i] = t1->obr[i];
		}
		one->in[pos] = 0;
		one->level = t1->level+1;
		char size1 = 1 << one->level-1;
		one->psklei = (char*)malloc(sizeof(char)*size1);
		for(i = 0; i<size1/2;i++)
			one->psklei[i] = t1->psklei[i];
		int j;
		for(i = size1/2 ,j = 0; i < size1; i++,j++)
			one->psklei[i] = t2->psklei[j];
		one->next = NULL;
		one->min = 0;
		return one;
	}
	return NULL;
}
/*********************************************************/
/*      Склеиваем ДНФ функцию в несколько проходов       */
/*********************************************************/
t_elemptr* getsdnf(t_elemptr *&sdnf,t_elemptr *cur, int length)
{
	t_elemptr *nstep = NULL, *t1, *t2, *temp = NULL, *t;
	t1 = cur;
	while(t1->next != NULL)
	{
		t2 = t1->next;
		while(t2 != NULL)
		{
			if(nstep == NULL)
			{
				nstep = sklei(t1,t2,length);
				temp = nstep;
			}
			else
			{
				t = sklei(t1,t2,length);
				if(t!=NULL)
				{
					temp->next = t;
					temp = temp->next;
				}
			}
			t2 = t2->next;
		}
		t1 = t1->next;
	}
	t1 = cur;
	t2 = sdnf;
	if(sdnf != NULL)
		while(t2->next!=NULL)
			t2 = t2->next;
	while(t1 != NULL)
	{
		if(t1->min == 0)
		{
			if(sdnf == NULL)
			{
				sdnf = t1;
				t2 = sdnf;
			}
			else
			{
				t2->next = t1;
				t2 = t2->next;
			}
			t1 = t1->next;

		}
		else
		{
			temp = t1;
			t1 = t1->next;
			free(temp->psklei);
			free(temp);
		}
	}
	return nstep;
}
/*********************************************************/
/*                  Сочетания из n по k                  */
/*********************************************************/
int soch(int n,int k,arel *x)
{
  int i,j;
  j = k;
  while(x[j].n>=n-k+j)
    j--;
  x[j].n++;
  x[j].p = x[j].p->next;
	for(i=j+1;i<=k;i++)
  {
    x[i].n = x[i-1].n+1;
		x[i].p = x[i-1].p->next;
	}
	return j;
}
/*********************************************************/
/*               Проверка минимальной ДНФ                */
/*********************************************************/
int testdnf(arel*arr,int count,int length)
{
	int *mas = (int*)malloc(sizeof(int)*count);
	int i;
	for(i = 0; i < count; i++)
		mas[i]=i+1;
	length++;
	for(;length>0;length--)
		for(i = 1<<(arr[length].p->level-1);i>=0;i--)
			mas[arr[length].p->psklei[i]]=0;
	for(i=0;i<count;i++)
	  if(mas[i]>0)
	  {
			free(mas);
			return 0;
		}
	free(mas);
	return 1;
}
/*********************************************************/
/*              Получение минимальной ДНФ                */
/*********************************************************/
void makednf(arel*arr, int length)
{
	int i = 1;
	for(;i<=length+1;i++)
		printel(arr[i].p);
  conec();
}
/*********************************************************/
/*              Получение минимальной ДНФ                */
/*********************************************************/
int getmdnf(t_elemptr *sdnf, int count)
{
	if(count == 0)
		return 0;
	static int length = 1;
	static arel *arr;
	static int flag = 0;
	static j=0;
	if(flag == 0)
	{
		while(1)
		{
			arr = (arel*)malloc(sizeof(arel)*(length+1));
			int i = 0;
			arr[1].n = 1;
			arr[1].p = sdnf;
			j = 1;
			for(i = 2 ;i<=length;i++)
			{
				arr[i].n = i;
				arr[i].p = arr[i-1].p->next;
			}
			while(j != 0)
			{
				if(testdnf(arr,count,length)==1)
				{
					flag = 1;
					j = soch(count,length,arr);
					makednf(arr,length);
					return 1;

				}
				j = soch(count,length,arr);
			}
			length++;
			free(arr);
			if(length>count)
				return 0;
		}
	}
	else if((j!=0) && (flag == 1))
	{
		while(j!=0)
		{
			if(testdnf(arr,count,length)==1)
			{
				j = soch(count,length,arr);
				makednf(arr,length);
				return 1;
			}
			j = soch(count,length,arr);
		}
	}
	else
	{
		free(arr);
		return 0;
	}
	return 0;
}
/*********************************************************/
/*              Тут-то все и начинается...               */
/*********************************************************/
int main(int argc, char **argv)
{
	clrscr();
	FILE*f;
	t_elemptr *dnf, *sdnf;
	int length;
	if((f = fopen("temp.txt","r")) != NULL)
	{
		if((dnf = getdnf(f,length))!=NULL)
		{
			t_elemptr *cur = dnf;
			sdnf = NULL;
#ifdef DEBUG
			while(cur != NULL)
			{
				for(int i = 0;i < (1<<cur->level-1);i++)
					printf("%i",cur->psklei[i]);
				puts("");
				cur = cur->next;
			}
			cur =dnf;
#endif
			puts("\n\nDNF");
			do
				OutputDNF(cur);
			while((cur = getsdnf(sdnf,cur,length))!=NULL);
			puts("\n\nSDNF");
			OutputDNF(sdnf);
			int count = 0;
			cur = sdnf;
/*			while(cur!=NULL)
			{
				cur = cur->next;
				count++;
			}
			while((getmdnf(sdnf,count))!=0);*/
#ifdef DEBUG
			cur = sdnf;
			puts("\n");
			while(cur != NULL)
			{
				for(int i = 0;i < (1<<cur->level-1);i++)
					printf("%i ",cur->psklei[i]);
				puts("");
				cur = cur->next;
			}
#endif
			remfromem(sdnf);
		}
	}
	getch();
	return 0;
}
/*********************************************************/
/*                    EOF {2006}                         */
/*********************************************************/
