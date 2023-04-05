#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED
typedef struct date{
int jj;
int mm;
int aa;
}date;
typedef struct contact {
char nom[20];
char prenom[20];
date anniversaire;
}contact;
typedef struct event {
char type[50];
int nbrinvites;
contact repertoire[10];
date debut;
date fin;
}event;
typedef enum {
    Sun,
    Mon,
    Jue,
    Wed,
    Thu,
    Fri,
    Sat
} WEEK;

typedef enum {
    January = 1,
    February,
    Match,
    Apirl,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
} MONTH;
#endif // STRUCTURE_H_INCLUDED
