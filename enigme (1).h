#ifndef ENIGME_H
#define ENIGME_H

#define MAX_QUESTIONS 20
#define MAX_TEXT 256

typedef struct
{
    char question[MAX_TEXT];
    char repA[MAX_TEXT];
    char repB[MAX_TEXT];
    char repC[MAX_TEXT];
    int bonneReponse;
} Enigme;

int chargerEnigmes(Enigme Q[], const char *nomFichier);
int tirerQuestion(Enigme Q[], int nbQ);

#endif
