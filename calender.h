#ifndef CALENDER_H_INCLUDED
#define CALENDER_H_INCLUDED
#include "structure.h"
void printYear(const int y,event CAL [],int nbrevent);
int getYearDay(const int year);
int isLeapYear(const int yr);
void  printMonth(const WEEK firstDay, int length ,int a,int y,event CAL [],int nbrevent);
void printMonHead(void);
void affichage_graphique(event cal[],int nbrevent);
int julian_day( );
void modifie_event(event *cal);
int rech_event(event cal[],int N,date dat,int o);
void rech_event_1(event cal[],int N,date dat);
int rech_contacst(contact repertoire[],int N,contact personne);
void supprime_event(event cal[],int *N,int indice);
void saisirdate(char type[],date *dat);
void saisirdatedenaiss(date *dat);
void saisircontact(contact *personne);
void saisirevennement(event *evennement);
void affich_event(event cal);
void affich_contact(contact personne);
void ajout_eventannif(event *evenement,contact personne);
int isLeap(int year);
int isValidDate(int d, int m, int y);
void supprimer(event cal[],int *N,int indice);



#endif // CALENDER_H_INCLUDED
