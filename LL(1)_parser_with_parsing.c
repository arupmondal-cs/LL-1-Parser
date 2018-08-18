#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void add_symbol(char *,char);
void FIND_FIRST(char *,char);
void FIND_FOLLOW(char *,char);
void FIRST_SHOW();
void FOLLOW_SHOW();
int  CREATE_LL1_TABLE();
void PARSING_TABLE_SHOW(int);
void LL1_PARSER(char *);

int top=0;
int t,nt,ch,cr,count;
char FIRST[100][100],FOLLOW[100][100];
char T[100],NT[100],G[100][100],STACK[100];
int LL1[100][100];

void main()
{
    int i,j,flag,fl,ch1;
    char STR[100];
    printf("Enter production rules of grammar in the form A->B\n\n");
    flag=1;
    fl=1;
    while(flag==1)
    {
        printf("\n1) Insert Production Rules\n2) Show Grammar\n3) Exit");
        printf("\nEnter your choice: ");
        scanf("%d",&ch1);
        switch(ch1)
        {
            case 1:printf("Enter number %d rules of grammar: ",cr+1);
                    scanf("%s",G[cr++]);
                    for(i=0;i<nt && fl==1;i++)
                    {
                        if(NT[i]==G[cr-1][0])
                            fl=0;
                    }
                    if(fl==1)
                        NT[nt++]=G[cr-1][0];
                    fl=1;
                    for(i=3;G[cr-1][i]!='\0';i++)
                    {
                        if(!isupper(G[cr-1][i]) && G[cr-1][i]!='!')
                        {
                            for(j=0;j<t && fl==1;j++)
                            {
                                if(T[j]==G[cr-1][i])
                                    fl=0;
                            }
                            if(fl==1)
                                T[t++]=G[cr-1][i];
                            fl=1;
                        }
                    }
                    break;

            case 2:if(cr>0)
                    {
                        printf("\nGrammar");
                        printf("\nStarting symbol is: %c",G[0][0]);
                        printf("\nNon-terminal symbol is: ");
                        for(i=0;i<nt;i++)
                            printf("%c  ",NT[i]);
                        printf("\nTerminal symbol is: ");
                        for(i=0;i<t;i++)
                            printf("%c  ",T[i]);
                        printf("\nProduction rules: ");
                        for(i=0;i<cr;i++)
                            printf("%s  ",G[i]);
                        printf("\n");
                    }
                    else
                    {
                        printf("!enter at least one production rules");
                    }
                    break;

            case 3:flag=0;
        }
    }
    FIRST_SHOW();
    FOLLOW_SHOW();

    T[t++]='$';
    T[t]='\0';

    flag=CREATE_LL1_TABLE();
    PARSING_TABLE_SHOW(flag);

    if(flag==0)
    {
        printf("Enter string for parsing: ");
        scanf("%s",STR);
        LL1_PARSER(STR);
    }
}

void FIRST_SHOW()
{
    int i,j;
    char arr[100];
    for(i=0;i<nt;i++)
    {
        arr[0]='\0';
        FIND_FIRST(arr,NT[i]);
        for(j=0;arr[j]!='\0';j++)
        {
            FIRST[i][j]=arr[j];
        }
        FIRST[i][j]='\0';
        count=0;
    }
    printf("\nFIRST:\n\n");
    for(i=0;i<nt;i++)
    {
        printf("FIRST( %c ): { ",NT[i]);
        for(j=0;FIRST[i][j+1]!='\0';j++)
            printf(" %c,",FIRST[i][j]);
        printf(" %c }",FIRST[i][j]);
        printf("\n");
    }
}
void FOLLOW_SHOW()
{
    int i,j;
    char arr[100];
    for(i=0;i<nt;i++)
    {
        count=0;
        arr[0]='\0';
        FIND_FOLLOW(arr,NT[i]);
        for(j=0;arr[j]!='\0';j++)
        {
            FOLLOW[i][j]=arr[j];
        }
        FOLLOW[i][j]='\0';
    }
    printf("\nFOLLOW:\n\n");
    for(i=0;i<nt;i++)
    {
        printf("FOLLOW( %c ): { ",NT[i]);
        for(j=0;FOLLOW[i][j+1]!='\0';j++)
            printf(" %c,",FOLLOW[i][j]);
        printf(" %c }",FOLLOW[i][j]);
        printf("\n");
    }
}

void PARSING_TABLE_SHOW(int flag)
{
    int i,j;
    if(flag==0)
    {
        printf("\n\nPredictive Parsing Table:\n\n\t");
        for(j=0;j<t;j++)
        {
            printf("\t%c\t",T[j]);
        }
        printf("\n----------------------------------------------------------------------------------------");
        printf("\n\n");
        for(i=0;i<nt;i++)
        {
            printf("%c\t|\t",NT[i]);
            for(j=0;j<t;j++)
            {
                if(LL1[i][j]!=0)
                    printf("%s\t\t",G[LL1[i][j]-1]);
                else
                    printf("%c\t\t",'_');
            }
            printf("\n\n");
        }
    }
}


void FIND_FIRST(char *arr,char ch)
{
    int i;
    if(!isupper(ch))
        add_symbol(arr,ch);
    else
    {
        for(i=0;i<cr;i++)
        {
            if(ch==G[i][0])
            {
                if(G[i][3]=='!')
                    add_symbol(arr,G[i][3]);
                else
                    FIND_FIRST(arr,G[i][3]);
            }
        }
    }
}

void FIND_FOLLOW(char arr[],char ch)
{
    int i,j,k,l,fl=1,flag=1;
    if(ch==G[0][0])
        add_symbol(arr,'$');
    for(i=0;i<cr;i++)
    {
        for(j=3;G[i][j]!='\0' && flag==1;j++)
        {
            if(ch==G[i][j])
            {
                flag=0;
                if(G[i][j+1]!='\0' && isupper(G[i][j+1]))
                {
                    for(k=0;k<nt;k++)
                    {
                        if(NT[k]==G[i][j+1])
                        {
                            for(l=0;FIRST[k][l]!='\0';l++)
                            {
                                if(FIRST[k][l]!='\0' && FIRST[k][l]!='!')
                                {
                                    add_symbol(arr,FIRST[k][l]);
                                }
                                if(FIRST[k][l]=='!')
                                    fl=0;
                            }
                            break;
                        }
                    }
                }
                else if(G[i][j+1]!='\0' && !isupper(G[i][j+1]))
                {
                    add_symbol(arr,G[i][j+1]);
                }
                if((G[i][j+1]=='\0' || fl==0) && G[i][0]!=ch)
                {
                    fl=1;
                    FIND_FOLLOW(arr,G[i][0]);
                }
            }
        }
    }
}

void add_symbol(char *arr,char ch)
{
    int i,flag=0;
    for(i=0;arr[i]!='\0';i++)
    {
        if(ch==arr[i])
        {
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        arr[count++]=ch;
        arr[count]='\0';
    }
}

int CREATE_LL1_TABLE()
{
    int i,j,k,fl,pos,flag=0;
    char arr[100];
    for(i=0;i<cr;i++)
    {
        arr[0]='\0';
        count=0;
        FIND_FIRST(arr,G[i][3]);
        for(j=0;j<count;j++)
        {
            if(arr[j]=='!')
            {
                FIND_FOLLOW(arr,G[i][0]);
                break;
            }
        }
        for(k=0;k<nt;k++)
        {
            if(NT[k]==G[i][0])
            {
                pos=k;
                break;
            }
        }
        for(j=0;j<count;j++)
        {
            if(arr[j]!='!')
            {
                for(k=0;k<t;k++)
                {
                    if(arr[j]==T[k])
                    {
                        if(LL1[pos][k]>0)
                        {
                            printf("\n\nConflict occur between %s and %s rules!",G[LL1[pos][k]-1],G[i]);
                            printf("\nGiven grammar is not LL(1) grammar!\n");
                            flag=1;
                            return flag;
                        }
                        else
                            LL1[pos][k]=i+1;
                        break;
                    }
                }
            }
        }
    }
    return flag;
}

void LL1_PARSER(char *STR)
{
    int i=0,j,pos,pos1,n,k;

    STR[strlen(STR)]='$';
    STACK[top++]='$';
    STACK[top]=G[0][0];

    printf("\nParsing sequence and actions\n\n");
    printf("STACK\t\t\tINPUT\t\t\tACTION");
    printf("\n------------------------------------------------------------------------------------\n");

    i=0;
    while(STACK[top]!='$')
    {
        for(j=0;STACK[j]!='\0';j++)
            printf("%c  ",STACK[j]);
        printf("\t\t");

        for(j=i;STR[j]!='\0';j++)
            printf("%c  ",STR[j]);

        if(STR[i]==STACK[top])
        {
            printf("\t\tReduced: %c",STACK[top]);
            STACK[top]='\0';
            top=top-1;
            i=i+1;
        }
        else
        {
            for(j=0;j<nt;j++)
            {
                if(STACK[top]==NT[j])
                {
                    pos=j;
                    break;
                }
            }
            for(j=0;j<t;j++)
            {
                if(STR[i]==T[j])
                {
                    pos1=j;
                    break;
                }
            }
            n=LL1[pos][pos1];
            if(G[n-1][3]=='!')
            {
                STACK[top]='\0';
                top--;
            }
            else
            {
                for(j=3;G[n-1][j]!='\0';j++)
                    k=j;
                STACK[top]='\0';
                for(j=k;j>2;j--)
                    STACK[top++]=G[n-1][j];
                top--;
            }
            printf("\t\tShift: %s",G[n-1]);
        }
        printf("\n");
    }
    for(j=0;STACK[j]!='\0';j++)
        printf("%c  ",STACK[j]);
    printf("\t\t");

    for(j=i;STR[j]!='\0';j++)
        printf("%c  ",STR[j]);

    printf("\n");
    if(STACK[top]=='$' && STR[i]=='$')
        printf("\nParsing successfully\n");
}
