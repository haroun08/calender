#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <WinCon.h>
#include "calender.h"
#define MAX_VALID_YR 2050
#define MIN_VALID_YR 1930
#define LMonth 31
#define SMonth 30
#define VMonth 28

int isLeap(int year)
{

return (((year % 4 == 0) &&
         (year % 100 != 0)) ||
         (year % 400 == 0));
}

int isValidDate(int d, int m, int y)
{

    if (y > MAX_VALID_YR ||
        y < MIN_VALID_YR)
    return 0;
    if (m < 1 || m > 12)
    return 0;
    if (d < 1 || d > 31)
    return 0;


    if (m == 2)
    {
        if (isLeap(y))
            return (d <= 29);
        else
            return (d <= 28);
    }


    if (m == 4 || m == 6 ||
        m == 9 || m == 11)
            return (d <= 30);

    return 1;
}


int julian_day( struct tm* date ) {
    int Julian_A[12] = { 1, 1, 0 };
    int Julian_M[12] = { 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int a = Julian_A[date->tm_mon];
    int m = Julian_M[date->tm_mon];
    int y = date->tm_year + 1900 + 4800 - a;

    return date->tm_mday + ((153*m + 2) / 5) + 365*y + y/4 - y/100 + y/400 - 32045;
}

void printMonHead(void)
{
   printf("    LUN    MAR    MER    JEU    VEN    SAM    DIM\n");
}

void  printMonth(const WEEK firstDay, int length ,int a,int y,event cal [],int nbrevent)
{
     WEEK weekDay = firstDay % 7;

     int i,j;

     printMonHead();

     for (i=0; i<weekDay;++i)
     {
         printf("       ");
     }

    for(i=1;i<=length;++i)
    {
          weekDay ++;
          weekDay%=7;
          for(j=0;j<nbrevent;j++)
        {
            if ((cal[j].debut.aa==y) &&(cal[j].debut.mm==a)&&(cal[j].debut.jj==i))
        {
        printf("\e[0;31m");
        break;
        }

        }
        printf("%7d", i);
        printf("\e[0;32m");

          if(weekDay==0) printf("\n");
    }

    printf("\n");
}


int isLeapYear(const int yr)
{
    return ( yr%( yr%100 ? 4:400) ? 0 : 1);
}


int getYearDay(const int year)
{

    int lastYear = year-1;
    int yearNum = lastYear-1899;

    int walker,counter=0;
    for(walker=1900; walker < year; ++walker)
    {
        if(isLeapYear(walker)==1)
            ++counter;
    }

    return (365*yearNum+counter+1)%7;
}


void printYear(const int y,event cal [],int nbrevent)
{
    WEEK yDay = getYearDay(y);
    int  vDay = isLeapYear(y);

    int monWeeks[13];
    int monLen  [13];

    monLen[0]=0;
    monLen[January]=31;     monLen[February]=28+vDay;   monLen[Match]=31;
    monLen[Apirl]=30;       monLen[May]=31;             monLen[June]=30;
    monLen[July]=31;        monLen[August]=31;          monLen[September]=30;
    monLen[October]=31;     monLen[November]=30;        monLen[December]=31;

    monWeeks[0]=0;
    monWeeks[January]   = yDay;
    monWeeks[February]  = ((monWeeks[January]       +monLen[January]        )%7);
    monWeeks[Match]     = ((monWeeks[February]      +monLen[February]       )%7);
    monWeeks[Apirl]     = ((monWeeks[Match]         +monLen[Match]          )%7);
    monWeeks[May]       = ((monWeeks[Apirl]         +monLen[Apirl]          )%7);
    monWeeks[June]      = ((monWeeks[May]           +monLen[May]            )%7);
    monWeeks[July]      = ((monWeeks[June]          +monLen[June]           )%7);
    monWeeks[August]    = ((monWeeks[July]          +monLen[July]           )%7);
    monWeeks[September] = ((monWeeks[August]        +monLen[August]         )%7);
    monWeeks[October]   = ((monWeeks[September]     +monLen[September]      )%7);
    monWeeks[November]  = ((monWeeks[October]       +monLen[October]        )%7);
    monWeeks[December]  = ((monWeeks[November]      +monLen[November]       )%7);

    int i;
    for(i=January; i<=December; ++i)
    {
        printf("\n-------------------------------------------------\n");
        printf("                     %d, %d                      \n",y,i);
        printf("-------------------------------------------------\n");
        printMonth(monWeeks[i],monLen[i],i,y,cal,nbrevent);
        printf("\n");
    }

    return;
}

void affichage_graphique(event cal[],int nbrevent)
 {
    int y;
    int quit=0;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
  do
    {
        printf("Entrez l'ann%ce a afficher(Superieure a %d)[0 pour quitter]: ",130,tm.tm_year+1900);
        while(1)
        {
        if(((scanf("%d",&y)==1) && (y<MAX_VALID_YR) && (y>=tm.tm_year+1900)) ||(y==0))
            {
            fflush(stdin);
            break;
            }

        fflush(stdin);
        system("cls");
        printf("R%cessayez de saisir une ann%ce:",130,130);
    }
        printf("\n");


        if(y==0)
            quit = 1;
        else
           {
            system("cls");
            printf("\t\n-------------AFFICHAGE EN COURS .... ------------\n");
            printYear(y,cal,nbrevent);  }

    }while(!quit);
}



void saisirdate(char type[],date *dat)
{int i=0;
    do{
    if (i==1)
        printf("Date saisie non valide R%cssayez!!!!:\n",130);
    printf("Donnez le jour de %s",type);
    while(1)
    {
        if(scanf("%d",&dat->jj)==1)
        {
            fflush(stdin);
            break;
        }

        fflush(stdin);
        printf("R%cessayez de donner le jour de %s",130,type);

    }
    printf("Donnez le mois de %s",type);
    while(1)
    {
        if(scanf("%d",&dat->mm)==1)
            {
            fflush(stdin);
            break;
            }

        fflush(stdin);
        printf("R%cessayez de donner le mois de %s",130,type);

    }
    printf("Donnez l'ann%ce de %s",130,type);
    while(1)
    {
        if(scanf("%d",&dat->aa)==1)
            {
            fflush(stdin);
            break;
            }

        fflush(stdin);
        printf("R%cessayez de donner l'ann%ce de %s",130,130,type);

    }
    i=1;
}while (!isValidDate(dat->jj,dat->mm,dat->aa));
}

void ajout_eventannif(event *evenement,contact personne)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char tmp[125]="";
    strcpy(tmp,"Anniversaire de ");
    strcat(tmp,personne.nom);
    strncpy(evenement->type,tmp,strlen(tmp)-1);
    strcat(evenement->type," ");
    strcat(evenement->type,personne.prenom);
    strncpy(tmp,evenement->type,strlen(evenement->type)-1);
    strcpy(evenement->type,tmp);
   if (personne.anniversaire.mm > tm.tm_mon + 1 ||((personne.anniversaire.mm==tm.tm_mon + 1)&&(personne.anniversaire.jj>=tm.tm_mday)))
    {
    evenement->debut.jj=personne.anniversaire.jj;
    evenement->debut.mm=personne.anniversaire.mm;
    evenement->debut.aa=tm.tm_year + 1900;
    evenement->fin.jj=personne.anniversaire.jj;
    evenement->fin.mm=personne.anniversaire.mm;
    evenement->fin.aa=tm.tm_year + 1900;}
   else
    {
    evenement->debut.jj=personne.anniversaire.jj;
    evenement->debut.mm=personne.anniversaire.mm;
    evenement->debut.aa=tm.tm_year + 1901;
    evenement->fin.jj=personne.anniversaire.jj;
    evenement->fin.mm=personne.anniversaire.mm;
    evenement->fin.aa=tm.tm_year + 1901;
    }
    evenement->nbrinvites=1;
    strcpy(evenement->repertoire[0].nom,personne.nom);
    strcpy(evenement->repertoire[0].prenom,personne.prenom);
    evenement->repertoire[0].anniversaire.jj=personne.anniversaire.jj;
    evenement->repertoire[0].anniversaire.mm=personne.anniversaire.mm;
    evenement->repertoire[0].anniversaire.aa=personne.anniversaire.aa;

}
void saisirdatedenaiss(date *dat)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int i=0;
    do{
    if (i==1)
            printf("Date saisie non valide R%cessayez!!!!:\n",130);
    printf("Donnez le jour de naissance:");
    while(1)
    {   fflush(stdin);
        if(scanf("%d",&dat->jj)==1)
        {
            break;
        }

        fflush(stdin);
        printf("R%cessayez de donner le jour de naissance:",130);

    }
    printf("Donnez le mois de naissance:");
   while(1)
    {
        if(scanf("%d",&dat->mm)==1)
        {
            break;
        }

        fflush(stdin);
        printf("R%cessayez de donner le mois de naissance:",130);

    }
     printf("Donnez l'ann%ce de naissance:",130);
    while(1)
    {
        if(scanf("%d",&dat->aa)==1)
        {
            break;
        }

        fflush(stdin);
        printf("Ressayez de donner l'ann%ce de naissance:",130);

    }
    i=1;
}while (!isValidDate(dat->jj,dat->mm,dat->aa+MAX_VALID_YR-tm.tm_year-1900));
}

void saisircontact(contact *personne)
{   fflush(stdin);
    printf("Donnez le nom du contact:");
    fgets(personne->nom,20,stdin);
    fflush(stdin);
    printf("Donnez le pr%cnom du contact:",130);
    fgets(personne->prenom,20,stdin);
    fflush(stdin);
    saisirdatedenaiss(&personne->anniversaire);
}

void saisirevennement(event *evennement)
{   int i,n,d;
    char typeev[30];
    fflush(stdin);
    printf("Donner la Nature de l'%cv%cnemnt:",130,130);
    fgets(typeev,30,stdin);
    strncpy(evennement->type,typeev,strlen(typeev)-1);
    while(1)
    {
    printf("Combien de personnes a inviter %c(max 10):",63);
    fflush(stdin);
    if((scanf("%d",&n)==1)&& (n>=0) && (n<=10))
        break;
    }
    evennement->nbrinvites=n;
    fflush(stdin);
    for(i=0;i<n;i++)
    {
        saisircontact(&evennement->repertoire[i]);
    }
    saisirdate("debut de l'evenement:",&evennement->debut);
    fflush(stdin);
    while(1)
    {
    printf("Saisir la dur%ce de l'%cv%cnnement en jours:",130,130,130);
    fflush(stdin);
    if((scanf("%d",&d)==1)&& (d>0))
        break;
    }
    struct tm t = { .tm_year=evennement->debut.aa-1900, .tm_mon=evennement->debut.mm-1, .tm_mday=evennement->debut.jj };
    t.tm_mday +=d-1;
    mktime(&t);
    evennement->fin.aa=t.tm_year+1900;
    evennement->fin.mm=t.tm_mon+1;
    evennement->fin.jj=t.tm_mday;
    system("cls");
    printf("\n-- AJOUT AVEC SUCCES! --\n");
}
void affich_contact(contact personne)
{
    printf("Nom:%s",personne.nom);
    printf("Pr%cnom:%s",130,personne.prenom);
    printf("Date de naissance:%d/%d/%d",personne.anniversaire.jj,personne.anniversaire.mm,personne.anniversaire.aa);
}
void affich_event(event cal)
{       int i=0;
        char placeholder[100];
        char tmp[200]="Evenement ";
        if (cal.debut.jj==cal.fin.jj&&cal.debut.mm==cal.fin.mm&&cal.debut.aa==cal.fin.aa)
            {
                strcat(tmp,cal.type);
                sprintf(placeholder," dans la date %d/%d/%d ",cal.debut.jj,cal.debut.mm,cal.debut.aa);
                strcat(tmp,placeholder);
                puts(tmp);
            }
        else
            {
                 strcat(tmp,cal.type);
                sprintf(placeholder," entre la date %d/%d/%d et %d/%d/%d ",cal.debut.jj,cal.debut.mm,cal.debut.aa,cal.fin.jj,cal.fin.mm,cal.fin.aa);
                strcat(tmp,placeholder);
                puts(tmp);
            }
        printf("%d Invit%c(s)",cal.nbrinvites,130);
        if(cal.nbrinvites!=0)
        {
            printf(":\n");
            for (i=0;i<cal.nbrinvites;i++)
               {
                   printf("%d)",i+1);
                   affich_contact(cal.repertoire[i]);
                   printf("\n");
               }
        }

}


void modifie_event(event *evt)
{
    int reponse;
    struct tm date1, date2;
    date2.tm_year=evt->fin.aa-1900;
    date2.tm_mon=evt->fin.mm-1;
    date2.tm_mday=evt->fin.jj;
    date1.tm_year=evt->debut.aa-1900;
    date1.tm_mon=evt->debut.mm-1;
    date1.tm_mday=evt->debut.jj;
    int  n=julian_day(&date2)-julian_day(&date1);
    while(reponse !=4  )
    {
        printf("\nQuel champs voulez vous %cditer (1:jour | 2:mois | 3:annee |4:Aucun) >>>>>",130);
        scanf("%d",&reponse);
        switch(reponse)
            {
            case 1:
                printf("\nDonnez le nouveau jour :");
                scanf("%d",&evt->debut.jj);
                break;
            case 2:
                printf("\nDonnez le nouveau mois :");
                scanf("%d",&evt->debut.mm);
                break;
            case 3:
                printf("\nDonnez l'ann%ce :",130);
                scanf("%d",&evt->debut.aa);
                break;
            case 4:
                printf("\nChangements r%calis%cs.",130,130);
                break;
            default:
                printf("\nEntr%ce invalide",130);
                break;
            }
        date1.tm_year=evt->debut.aa-1900;
        date1.tm_mon=evt->debut.mm-1;
        date1.tm_mday=evt->debut.jj;
        date1.tm_mday +=n;
        mktime(&date1);
        evt->fin.aa=date1.tm_year+1900;
        evt->fin.mm=date1.tm_mon+1;
        evt->fin.jj=date1.tm_mday;
    }

}
int rech_event(event cal[],int N,date dat,int o)
{
    int tab[50];
    int i,t=0;
    int b=0;
        for(i=0;i<N;i++)
        if((cal[i].debut.jj==dat.jj)&&(cal[i].debut.mm==dat.mm)&&(cal[i].debut.aa==dat.aa))
            {
            if(b==0)
                {
                    b=1;
                    printf("Les %cv%cnements corr%cspondents %c la date %d/%d/%d sont :",130,130,130,224,dat.jj,dat.mm,dat.aa);
                    printf("\n-------------------------------------------------------------------\n");

                }
            tab[t]=i;
            printf("\n%d--->",t+1);
            affich_event(cal[i]);
            printf("\n");
            t++;
            }
            if(b==0)
                {
                printf("Pas d'%cv%cnements corr%cspondents a la date %d/%d/%d ",130,130,130,dat.jj,dat.mm,dat.aa);
                return -1;
                }
            if  (o==1)
            {
            printf("\nChoisir l'%cv%cnement :",130,130);
            while(1)
            {   fflush(stdin);
                if(scanf("%d",&b)==1 && b>0 && b<=t)
                {
                    break;
                }
                fflush(stdin);
                printf("\nChoisir l'entier correspondent a l'%cv%cnement desir%c:",130,130,130);
            }


            return (tab[b-1]);
            }
            return 0;
}
void rech_event_1(event cal[],int N,date dat)
{
    struct tm date1, date2;
    int i,n,t=0;
    int b=0;
        for(i=0;i<N;i++)
       {
        date2.tm_year=cal[i].debut.aa-1900;
        date2.tm_mon=cal[i].debut.mm-1;
        date2.tm_mday=cal[i].debut.jj;
        date1.tm_year=dat.aa-1900;
        date1.tm_mon=dat.mm-1;
        date1.tm_mday=dat.jj;
        n=julian_day(&date2)-julian_day(&date1);
        if(n>=0 && n<8)
            {
            if(b==0)
                {
                    b=1;
                    printf("Les %cv%cnements corr%cspondents a la semaine commen%cant par la date %d/%d/%d sont :",130,130,130,135,dat.jj,dat.mm,dat.aa);
                    printf("\n---------------------------------------------------------------------\n");

                }
            t++;
            printf("\n%d--->",t+1);
            affich_event(cal[i]);
            printf("\n");

            }
        }
            if(b==0)
                {
                printf("Pas d'%cv%cnements planifi%cs pour cette semaine.\n",130,130,130);
                return;
                }
}
void supprimer(event cal[],int *N,int indice)
{
   int i;
   for(i=indice;i<*N-1;i++)
        cal[i]=cal[i+1];
   *N=*N-1;
}
