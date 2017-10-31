#include <stdio.h>
#include <stdlib.h>

struct list{
	int count;
	double value; 
	struct list * next; }; 


void addToList(double value,struct list **list)
{
	if(*list==NULL)
	{
		*list=malloc(sizeof(struct list));
		(*list)->value=value;
		(*list)->next=NULL;
	        (*list)->count=1;
	}
	else
	{
		struct list *listN=*list;
		while(listN->next!=NULL)
		{
			listN->count++;
			listN=listN->next;
		}
		listN->count++;
		listN->next=malloc(sizeof(struct list));
		listN->next->next=NULL;
		listN->next->value=value; 
		listN->next->count=1;
	}
}
void printList(struct list *list)
{
	while(list!=NULL)
	{
		printf("%f\n",list->value);
		list=list->next;
	}
}
int main(int argc,char *argv[] )
{
	char* fileName;
	if(argc>1)
		fileName=argv[1];
	else
	{
		printf("enter file path and name: ");
		scanf("%s",&fileName);
	}
	FILE *file;
    	file = fopen(fileName,"r");
	/*fileName = fgets(fileName,100,file);
    printf("first string- %s",fileName);*/
	struct list *l;
	l=NULL;
	float fl,buff;
	int x=0;
	while(!feof(file))
	{
		fscanf(file,"%f",&buff);
		if(x++!=0)
		    addToList(fl,&l);
		fl=buff;
	}	
	/*addToList(1,&l);
	addToList(2,&l);
	addToList(5,&l);
	addToList(4,&l);
	addToList(10,&l)*/;
	printList(l);
	printf("\ncountyourefaggot -  %d\n",l->count);
}
