#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include "game.h"

void initGame(board board, unitsArray nb_unite)
{
    int compt=0,n,x,False=1,a,b;
    //Initialisation du board
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            board[i][j]='0';
        }
    }
    while(compt<=8)
    {
        x=rand() % 7 ;
        n=1 + rand() % 5;
        if(board[x][n] == '0') 
        {
            board[x][n]='X';
            board[x][12-n]='X';
            compt++;
        } 
    }
    //Initialisation unitsArray
    nb_unite->numOfUnits=MAX_UNITS;
    for(int i=0;i<MAX_UNITS;i++)
    {
        nb_unite->units[i].unitId=i;
        nb_unite->units[i].hp=MAX_HP;
        if(i==MAX_UNITS-2) //Initialisation leader 1
        {
            nb_unite->units[i].owner=0;
            nb_unite->units[i].unit_type=1;
            nb_unite->units[i].x=3;
            nb_unite->units[i].y=0;
            //board[nb_unite->units[i].x][nb_unite->units[i].y]='1';
        }
        else if(i==MAX_UNITS-1) //Initialisation leader 2
        {
            nb_unite->units[i].owner=1;
            nb_unite->units[i].unit_type=1;
            nb_unite->units[i].x=3;
            nb_unite->units[i].y=12;
            //board[nb_unite->units[i].x][nb_unite->units[i].y]='2';
        }
        else
        {
            nb_unite->units[i].owner=2;
            //nb_unite->units[i].unit_type=0;
            if(i>= MAX_UNITS/2)
            {
                nb_unite->units[i]=nb_unite->units[i-MAX_UNITS/2];
		        nb_unite->units[i].unitId=i;
                nb_unite->units[i].y=12-nb_unite->units[i].y;
                //board[nb_unite->units[i].x][nb_unite->units[i].y]='u';
            }
            else 
            {
                while(False)
                {
                    a=rand() % 7 ;
                    b=1 + rand() % 5;
                    if(board[a][b] == '0') 
                    {
                        nb_unite->units[i].x=a;
                        nb_unite->units[i].y=b;
                        //board[a][b]='u'; //commande qui permet de savoir ou sont les unit??s
                        False = 0;
                    } 
                }
            False = 1;
            } 
        }
    }
}

void printBoard(board board)
{
    assert(board);
	printf("\n");
    printf("    u unit??s neutres - 1 et 2 leaders - X obstacles\n");
    for (int j=0; j<WIDTH; j++)
    {
        if(j>=10) printf("  %d",j);
        else printf("   %d",j);
    } 
    printf("\n");
	for (int j=0; j<WIDTH; j++)
    {
        if (j==0) printf("  ___");
        else printf("____");
    } 
    printf("\n");
    for(int i=0;i<HEIGHT;i++)
    {
        printf("%d",i);
        for(int j=0;j<WIDTH;j++)
        {
            if(j%WIDTH == 0) printf("|");
            if(board[i][j]=='0') printf("   |");
            else printf(" %c |", board[i][j]);
        }
        printf("\n");
        for (int j=0; j<WIDTH; j++)
        {
            if (j==0) printf("  ___");
            else printf("____");
        } 
        printf("\n");
        
    }
}

int algo_Bresenham(board board, int x1, int y1, int x2, int y2,tab_shoot tableau_mouv)
{
    int dx,dy,compt=0;
    if((dx=x2-x1)!=0)
    {
        if(dx>0)
        {
            if((dy=y2-y1)!=0)
            {
                if(dy>0)
                {
                    if(dx>=dy)
                    {
                        int e;
                        e=dx;
                        dx=e*2;
                        dy=dy*2;
                        while(1)
                        {
                            tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                            tableau_mouv[compt][1]=y1;
                            compt++;
                            if((x1=x1+1)==x2) break;
                            if((e=e-dy)<0)
                            {
                                y1++;
                                e=e+dx;
                            }
                        }
                    }
                    else
                    {
                        int e;
                        e=dy;
                        dy=e*2;
                        dx=dx*2;
                        while(1)
                        {
                            tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                            tableau_mouv[compt][1]=y1;
                            compt++;
                            if((y1++)==y2) break;
                            if((e=e-dx)<0)
                            {
                                x1++;
                                e=e+dy;
                            }
                        }
                    }
                }
                else
                {
                    if(dx>=-dy)
                    {
                        int e;
                        e=dx;
                        dx=e*2;
                        dy=dy*2;
                        while(1)
                        {
                            tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                            tableau_mouv[compt][1]=y1;
                            compt++;
                            if((x1++)==x2) break;
                            if((e=e+dy)<0)
                            {
                                y1++;
                                e=e+dx;
                            }
                        }
                    }
                    else
                    {
                        int e;
                        e=dy;
                        dy=e*2;
                        dx=dx*2;
                        while(1)
                        {
                            tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                            tableau_mouv[compt][1]=y1;
                            compt++;
                            if((y1--)==y2) break;
                            if((e=e+dx)>0)
                            {
                                x1++;
                                e=e+dy;
                            }
                        }
                    }
                }
            }
            else
            {
                do
                {
                    tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                    tableau_mouv[compt][1]=y1;
                    compt++;
                } while ((x1++)!=x2);
            }
        }
        else
        {
            if((dy=y2-y1)!=0)
            {
                if(dy>0)
                {
                    if(-dx>=dy)
                    {
                        int e;
                        e=dx;
                        dx=e*2;
                        dy=dy*2;
                        while(1)
                        {
                            tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                            tableau_mouv[compt][1]=y1;
                            compt++;
                            if((x1--)==x2) break;
                            if((e=e+dy)<0)
                            {
                                y1++;
                                e=e+dx;
                            }
                        }
                    }
                    else
                    {
                        int e;
                        e=dy;
                        dy=e*2;
                        dx=dx*2;
                        while(1)
                        {
                            tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                            tableau_mouv[compt][1]=y1;
                            compt++;
                            if((y1++)==y2) break;
                            if((e=e+dx)>0)
                            {
                                x1--;
                                e=e+dy;
                            }
                        }
                    }
                }
                else
                {
                    if(dx<=dy)
                    {
                        int e;
                        e=dx;
                        dx=e*2;
                        dy=dy*2;
                        while(1)
                        {
                            tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                            tableau_mouv[compt][1]=y1;
                            compt++;
                            if((x1--)==x2) break;
                            if((e=e-dy)<0)
                            {
                                y1--;
                                e=e+dx;
                            }
                        }
                    }
                    else
                    {
                        int e;
                        e=dy;
                        dy=e*2;
                        dx=dx*2;
                        while(1)
                        {
                            tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                            tableau_mouv[compt][1]=y1;
                            compt++;
                            if((y1--)==y2) break;
                            if((e=e-dx)>0)
                            {
                                x1--;
                                e=e+dy;
                            }
                        }
                    }
                }
            }
            else
            {
                do
                {
                    tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                    tableau_mouv[compt][1]=y1;
                    compt++;
                } while ((x1--)!=x2);
            }
        }
        
    }
    else
    {
        if((dy=y2-y1)!=0)
        {
            if(dy>0)
            {
                do
                {
                    tableau_mouv[compt][0]=x1;
                    tableau_mouv[compt][1]=y1;
                    //board[x1][y1]='T';
                    compt++;
                } while ((y1++)!=y2);
            }
            else
            {
                do
                {
                    tableau_mouv[compt][0]=x1;
                    tableau_mouv[compt][1]=y1;
                    //board[x1][y1]='T';
                    compt++;
                } while ((y1--)!=y2);   
            }
        }
    }
    /* //Pour voir quelles sont les valeurs dans le tableau des coordonn??es
    for(int i=0;i<compt;i++)
    {
        printf("%d %d\n",tableau_mouv[i][0],tableau_mouv[i][1]);
    }*/
    return compt;
}
void print_unitsArray(unitsArray nb_unite)
{
    printf("\n");
    for(int i=0;i<MAX_UNITS;i++)
    {
        printf("Unit?? n??%d, hp:%d,x=%d, y=%d\n",nb_unite->units[i].unitId,nb_unite->units[i].hp,nb_unite->units[i].x,nb_unite->units[i].y);
    }
}
void shoot(board board, unitsArray nb_unite, int uniteId, int targetId,tab_shoot tableau_mouv)
{
    int x1,y1,x2,y2,compt,False = 1,j=0; 

    x1 = nb_unite->units[uniteId].x;
    y1 = nb_unite->units[uniteId].y;
    x2 = nb_unite->units[targetId].x;
    y2 = nb_unite->units[targetId].y;

    if((compt = algo_Bresenham(board,x1,y1,x2,y2,tableau_mouv)) <= 7)
    {
        while(False)
        {
            if(board[tableau_mouv[j][0]][tableau_mouv[j][1]] == 'X')
            {
                printf("Le tir a touch?? un obstacle.\n");
                False = 0;
            }
            j++;
        }
        nb_unite->units[targetId].hp = nb_unite->units[targetId].hp-compt;

    }
}
void move(board plateau, unitsArray nb_unite, int uniteId, int x, int y)
{
    int x1 = nb_unite->units[uniteId].x,y1 = nb_unite->units[uniteId].y;
    if(abs(x1-x)<=1 && abs(y1-y)<=1 && (abs(x1-x)==abs(y1-y))!=1 /*&&*/ )/*plateau[x][y] == '0')*/
    {
        //plateau[x1][y1]='0';
        //plateau[x][y]='u';
        //printBoard(plateau);
    }
    else
    {
        printf("\n////////////L'unit?? ne peut pas ce d??placer.////////////\n");
    }
}
void convert(board plateau, unitsArray nb_unite, int unitId, int targetId)
{
    int x=nb_unite->units[unitId].x,y=nb_unite->units[unitId].y,x1=nb_unite->units[targetId].x,y1=nb_unite->units[targetId].y;
    if(abs(x1-x)<=1 && abs(y1-y)<=1 && (abs(x1-x)==abs(y1-y))!=1 && nb_unite->units[targetId].owner!=nb_unite->units[unitId].owner)
    {
        if(nb_unite->units[unitId].owner == 0) 
        {
            nb_unite->units[targetId].owner = 0;
            //plateau[x1][y1]='A';
        }
        else 
        {
            nb_unite->units[targetId].owner = 1;
            //plateau[x1][y1]='B';
        }
        //printBoard(plateau);
    }
    else
    {
        printf("\n////////////Le leader ne peut pas convertir.////////////\n");
    }
}
int main(){
    board plateau;
    unitsArray nb_unite = malloc(sizeof(struct unitsArray_s));
    tab_shoot tableau_coord;
    /* //Cela permet d'initialiser le tableau des coordonn??es (inutile en C++)
    for(int i=0;i<MAX_TURNS;i++)
    {
        tableau_coord[i][0]=0;
        tableau_coord[i][1]=0;
    }*/
    initGame(plateau,nb_unite);
    //int compt=algo_Bresenham(plateau,0,0,5,8,tableau_coord);
    print_unitsArray(nb_unite);
    printBoard(plateau);
    //move(plateau,nb_unite,6,0,0);
    //convert(plateau,nb_unite,12,0);
    printf("\n");
    return 0;
}
