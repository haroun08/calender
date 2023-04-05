//BARHOUMI HAROUN & CHAMLI AHMED AMINE
#include <stdio.h>
#include <stdlib.h>
#define max_event 50
#include "calender.h"
#include <string.h>
#include <windows.h>
#include <conio.h>
int main()
{
    system("COLOR 0A");
    char motdepasse[20]="";
    int pos=-1;
    int i,nb,choix,choix1,N,choix2,choix3,choix4,reponse,nbrdecontact=0,nbrdeevent=0;
    event cal[max_event];
    contact repertoire[max_event];
    date dat;
    int j=0;
    printf("----DONNER LE MOT DE PASSE:\n ");
    int p,tent=0;

    while(strcmp(motdepasse,"ADMIN"))
    {    p=0;

        if  (strcmp(motdepasse,""))
            {system("cls");
            printf("Mot de passe incorr%ccte-RESSAYEZ!\n---------------------------------\n---IL VOUS RESTE %d tentatives----\n",130,3-tent);
            printf("---------------------------------\n");
            tent++;
            if (tent==4)
            {  system("cls");
               printf("------------------AU REVOIR------------------------");
               exit( EXIT_FAILURE);
            }

            }
        do//%M
	{
		motdepasse[p] = getch();
		if(motdepasse[p] == 13 )
		{
			break;
		}
		else if(motdepasse[p]==8 && p>0)
		{
			printf("%c%c%c",8,32,8);
			p--;
		}
		else
		{//NNN

			printf("*");
			p++;
		}
	}while(motdepasse[p]!=13);
	motdepasse[p] = '\0';
    fflush(stdin);
    }
    FILE *f=NULL,*c=NULL;
    //extraction des contacts du fichier
    c=fopen("Liste_contacts.txt","rt");//r:read,t:txt //creer ou ouvrir fichier
    if (c==NULL)
        printf("Fichier_inexistant");
    else
        while(!feof(c))
    {
        fscanf(c,"%[^:]:%[^:]:%d:%d:%d\n",repertoire[nbrdecontact].nom,repertoire[nbrdecontact].prenom,&repertoire[nbrdecontact].anniversaire.jj,&repertoire[nbrdecontact].anniversaire.mm,&repertoire[nbrdecontact].anniversaire.aa);
        nbrdecontact++;
    }
    fclose(c);
    f=fopen("Liste_evenements.txt","rt");//r:read,t:txt //creer ou ouvrir fichier
    if (f==NULL)
        printf("Fichier_in%cxistant",130);
    else
        while(!feof(f))
    {
        fscanf(f,"%[^:]:%d:%d:%d:%d:%d:%d:%d",cal[nbrdeevent].type,&cal[nbrdeevent].debut.jj,&cal[nbrdeevent].debut.mm,&cal[nbrdeevent].debut.aa,&cal[nbrdeevent].fin.jj,&cal[nbrdeevent].fin.mm,&cal[nbrdeevent].fin.aa,&cal[nbrdeevent].nbrinvites);
        for(i=0;i<cal[nbrdeevent].nbrinvites;i++)
            fscanf(f,"\n%[^:]:%[^:]:%d:%d:%d\n",cal[nbrdeevent].repertoire[i].nom,cal[nbrdeevent].repertoire[i].prenom,&cal[nbrdeevent].repertoire[i].anniversaire.jj,&cal[nbrdeevent].repertoire[i].anniversaire.mm,&cal[nbrdeevent].repertoire[i].anniversaire.aa);
        nbrdeevent++;
    }
    fclose(f);
 do
    {   system("cls");
        printf("Realis%c par: HAROUN BARHOUMI - AHMED AMINE CHAMLI\n",130);
        printf("\n|-------------------------------------------------------------------|\n");
        printf("\n|------------------------|| Menu  ||--------------------------------|\n");
        printf("\n|-------------------------------------------------------------------|\n");
        printf("1. MENU AJOUT\n");
        printf("2. MENU AFFICHAGE\n");
        printf("3. MENU SUPPRESSION/MODIFICATION\n");
        printf("4. QUITTER\n");
        printf("\nChoisir une option:");
        while(1)
            {
                fflush(stdin);
                if(scanf("%d",&choix)==1 && choix>0 && choix<5)
                    {
                    fflush(stdin);
                    break;
                    }
                printf("Saisie incorrecte:");
            }
        system("cls");
        switch (choix) {
            case 1:
                do {
                    printf("\n\n| MENU AJOUTER|\n\n");
                    printf("1. AJOUTER UN CONTACT \n");
                    printf("2. AJOUTER UN EVENEMENT \n");
                    printf("3. RETOURNER AU MENU PRINCIPAL. \n");
                    printf("\nChoisir une option:");
                    while(1)
                            {
                            fflush(stdin);
                            if(scanf("%d",&choix1)==1 && choix1>0 && choix1<4)
                                {
                                fflush(stdin);
                                break;
                                }
                            printf("Saisie incorrecte:");
                            }
                        switch (choix1) {
                        case 1: // ajouter un contact
                            system("cls");
                            printf("\nCombien de contacts voulez vous saisir ---------> ");
                            while(1)
                            {
                            fflush(stdin);
                            if(scanf("%d",&nb)==1 && (nb>=0))
                            {
                                fflush(stdin);
                                break;
                            }

                            fflush(stdin);
                            printf("\nEntrez un entier positif:\n");
                            }

                            for(i=nbrdecontact;i<nbrdecontact+nb;i++)
                                {saisircontact(&repertoire[i]);
                                ajout_eventannif(&cal[nbrdeevent],repertoire[i]);
                                nbrdeevent++;
                                printf("\n");
                                }
                            nbrdecontact+=nb;
                            system("cls");
                            printf("\n-- AJOUT AVEC SUCCES! --\n");
                            break;

                         case 2: // ajouter event
                            system("cls");
                            printf("\nCombien d'%cv%cnements voulez vous saisir >>>>> ",130,130);
                            while(1)
                            {
                            if(scanf("%d",&N)==1 && (N>=0) && (N<max_event-nbrdeevent))
                            {
                                fflush(stdin);
                                break;
                            }
                            fflush(stdin);
                            if(N>=max_event-nbrdeevent)
                                printf("\nCalendrier Satur%c,videz de l'%cspace pour pouvoir ajouter %d nouveaux %cv%cnements \n",130,130,N,130,130);
                            else
                            printf("\nEntr%ce non valide , saisissez un entier positif:",130);
                            }
                            for(i=nbrdeevent;i<nbrdeevent+N;i++)
                                {saisirevennement(&cal[i]);
                                printf("\n");}
                            nbrdeevent+=N;
                            system("cls");
                            printf("\n-- AJOUT AVEC SUCCES! --\n");
                            break;

                        case 3:
                            system("cls");
                            break;
                        default:
                            system("cls");
                            printf("\nFaites un choix parmi les options present%ces.\n\n\n",130);
                            break;
                    }
                } while (choix1!= 3);
                break;
            case 2:
                do {
                    system("cls");
                    printf("\n\n| MENU AFFICHAGE |\n\n");
                    printf("1. AFFICHER LE REPERTOIRE.\n");
                    printf("2. AFFICHER LA CALENDRIER \n");
                    printf("3. RETOURNER AU MENU PRINCIPAL. \n");
                    while(1)
                            {
                                fflush(stdin);
                                if(scanf("%d",&choix2)==1 && choix2>0 && choix2<4)
                            {
                                fflush(stdin);
                                break;
                            }
                            printf("Saisie incorrecte:");
                            }
                    switch (choix2) {
                        case 1:
                            system("cls");
                            printf("\nLe repertoire contient  %d contact(s)\n",nbrdecontact);
                            printf("\n--------------------------------------------------------------------\n");
                            for (i=0;i<nbrdecontact;i++)
                                {
                                affich_contact(repertoire[i]);
                                printf("\n\n");
                                }
                            system("pause");
                            break;
                        case 2: // afficher
                          do {
                            system("cls");
                            printf("\n\n| AFFICHAGE DU CALENDRIER |\n\n");
                            printf("1. AFFICHER TOUS LES EVENEMENTS\n");
                            printf("2. AFFICHER LES EVENEMENTS AVEC UNE DATE SPECIFIQUE\n");
                            printf("3. AFFICHER LES EVENEMENTS DANS UN SEMAINE COMMENCANT AVEC UNE DATE SPECIFIQUE\n");
                            printf("4. AFFICHAGE GRAPHIQUE\n");
                            printf("5. RETOURNER AU MENU D'AFFICHAGE \n");
                            while(1)
                            {
                                fflush(stdin);
                                if(scanf("%d",&choix3)==1 && choix3>0 && choix3<6)
                            {
                                fflush(stdin);
                                break;
                            }
                            printf("saisie incorrecte:");
                            }
                            switch(choix3)
                            {
                            case 1:
                                system("cls");
                                printf("\nLe calendrier contient  %d evenement(s):\n",nbrdeevent);
                                printf("\n------------------------------------------\n");
                                for (i=0;i<nbrdeevent;i++)
                                    {printf("\n");
                                    affich_event(cal[i]);
                                    printf("\n");}
                                printf("\n\n");
                                system("pause");
                                break;
                            case 2:
                                system("cls");
                                printf("\nDonnez la date des %cv%cnements a afficher:\n",130,130);
                                saisirdate("debut de l'evenement:",&dat);
                                rech_event(cal,nbrdeevent,dat,0);
                                system("pause");
                                break;
                            case 3:
                                system("cls");
                                printf("\nDonnez la date de debut de semaine des %cv%cnements a afficher:\n",130,130);
                                saisirdate("debut de la semaine:",&dat);
                                rech_event_1(cal,nbrdeevent,dat);
                                system("pause");
                                break;
                            case 4:
                                system("cls");
                                affichage_graphique(cal,nbrdeevent);
                                system("pause");
                                break;
                            case 5:
                                system("cls");
                                break;
                            default:
                            system("cls");
                            printf("\nFaites une choix parmi les options present%ces:\n\n\n",130);
                            break;
                            }
                            break;
                            } while (choix3 != 5);
                        case 3:
                            system("cls");
                            break;
                        default:
                            system("cls");
                            printf("\nFaites une choix parmi les options present%ces.\n\n\n",130);
                            break;
                    }
                } while (choix2 != 3);
                break;

            case 3:
                do {
                    printf("\n\n| MENU SUPPRESSION/MODIFICATION |\n\n");
                    printf("1. SUPPRIMER UN EVENEMENT PAR SA DATE \n");
                    printf("2. MODIFIER LA DATE D'UN EVENEMENT.\n");
                    printf("3. RETOURNER AU MENU PRINCIPAL.\n");
                    while(1)
                            {
                                fflush(stdin);
                                if(scanf("%d",&choix4)==1 && choix4>0 && choix4<4)
                            {
                                fflush(stdin);
                                break;
                            }
                            printf("saisie incorrecte:");
                            }
                    switch (choix4)
                    { system("cls");
                        case 1:
                            system("cls");
                            printf("\nDonner la date de debut de l'%cv%cnement a supprimer:\n",130,130);
                            saisirdate("debut de l'evenement:",&dat);
                            pos=rech_event(cal,nbrdeevent,dat,1);
                            if (pos==-1)
                                {   system("cls");
                                    printf("\n--------L'%cv%cnement n'%cxiste pas-------\n",130,130,130);
                                    system("pause");
                                    system("cls");
                                    printf("---PAS DE SUPPRESSION---");
                                }
                            else
                                {
                                //
                                printf("\nVoulez vous supprimer l'%cv%cnement (non:0 /oui:1) >>>>>",130,130);
                                scanf("%d",&reponse);
                                if (reponse)
                                    {
                                        supprimer(cal,&nbrdeevent,pos);
                                        printf("\nLe calendrier comporte %d %cv%cnement(s)",nbrdeevent,130,130);
                                        system("cls");
                                        printf("\n-- SUPRESSION AVEC SUCCES! --\n");
                                    }
                                }

                            break;
                        case 2:
                            system("cls");
                            printf("\nDonnez la date de debut de l'%cv%cnement a modifier :\n",130,130);
                            saisirdate("debut de l'evenement:",&dat);
                            system("cls");
                            pos=rech_event(cal,nbrdeevent,dat,1);
                            if (pos==-1)
                                {
                                    printf("\nL'%cv%cnement n'exsiste pas\n",130,130);
                                    system("pause");
                                    system("cls");
                                }
                            else
                               {
                            modifie_event(&cal[pos]);
                            system("cls");
                            printf("----------MODIFICATION AVEC SUCCES----------\n");}
                            break;
//jj
                        case 3:
                            system("cls");
                            break;
                        default:
                            system("cls");
                            printf("\nFaites un choix parmi les options present%ces:\n\n\n",130);
                            break;
                    }
                } while (choix4 != 3);
                break;
            case 4:
                    f=fopen("Liste_evenements.txt","wt");//write
                    for(j=0;j<nbrdeevent;j++)
                        {
                            fprintf(f,"%s:%d:%d:%d:%d:%d:%d:%d",cal[j].type,cal[j].debut.jj,cal[j].debut.mm,cal[j].debut.aa,cal[j].fin.jj,cal[j].fin.mm,cal[j].fin.aa,cal[j].nbrinvites);
                            for(i=0;i<cal[j].nbrinvites;i++)
                                fprintf(f,"\n%s:%s:%d:%d:%d\n",cal[j].repertoire[i].nom,cal[j].repertoire[i].prenom,cal[j].repertoire[i].anniversaire.jj,cal[j].repertoire[i].anniversaire.mm,cal[j].repertoire[i].anniversaire.aa);
                        }
                    fclose(f);
                    c=fopen("Liste_contacts.txt","wt");//write
                    for(i=0;i<nbrdecontact;i++)
                        fprintf(c,"%s:%s:%d:%d:%d\n",repertoire[i].nom,repertoire[i].prenom,repertoire[i].anniversaire.jj,repertoire[i].anniversaire.mm,repertoire[i].anniversaire.aa);
                    fclose(c);
                    exit(0);

            default:
                printf("\nEntr%ce invalide\n",130);
                system("cls");
                break;
        }
    } while (choix != 4);
        return 0;
}
