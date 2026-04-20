#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enigme.h"

static int questionsUtilisees[MAX_QUESTIONS];
static int nbQuestionsUtilisees = 0;
static int nbQuestionsMemoire = 0;

static void enleverRetourLigne(char *texte)
{
    size_t len = strlen(texte);

    while (len > 0 && (texte[len - 1] == '\n' || texte[len - 1] == '\r'))
    {
        texte[len - 1] = '\0';
        len--;
    }
}

int chargerEnigmes(Enigme Q[], const char *nomFichier)
{
    FILE *f;
    char ligne[1024];
    char *token;
    int i = 0;

    f = fopen(nomFichier, "r");
    if (f == NULL)
    {
        return 0;
    }

    while (i < MAX_QUESTIONS && fgets(ligne, sizeof(ligne), f) != NULL)
    {
        enleverRetourLigne(ligne);

        if (ligne[0] == '\0')
        {
            continue;
        }

        token = strtok(ligne, "|");
        if (token == NULL)
        {
            continue;
        }
        snprintf(Q[i].question, MAX_TEXT, "%s", token);

        token = strtok(NULL, "|");
        if (token == NULL)
        {
            continue;
        }
        snprintf(Q[i].repA, MAX_TEXT, "%s", token);

        token = strtok(NULL, "|");
        if (token == NULL)
        {
            continue;
        }
        snprintf(Q[i].repB, MAX_TEXT, "%s", token);

        token = strtok(NULL, "|");
        if (token == NULL)
        {
            continue;
        }
        snprintf(Q[i].repC, MAX_TEXT, "%s", token);

        token = strtok(NULL, "|");
        if (token == NULL)
        {
            continue;
        }

        Q[i].bonneReponse = atoi(token);

        if (Q[i].bonneReponse >= 1 && Q[i].bonneReponse <= 3)
        {
            i++;
        }
    }

    fclose(f);
    return i;
}

int tirerQuestion(Enigme Q[], int nbQ)
{
    (void)Q;
    int disponibles[MAX_QUESTIONS];
    int nbDisponibles;
    int i;

    if (nbQ <= 0)
    {
        return 0;
    }

    if (nbQuestionsMemoire != nbQ || nbQuestionsUtilisees >= nbQ)
    {
        nbQuestionsUtilisees = 0;
        nbQuestionsMemoire = nbQ;
    }

    nbDisponibles = 0;
    for (i = 0; i < nbQ; i++)
    {
        int dejaUtilisee = 0;
        int j;

        for (j = 0; j < nbQuestionsUtilisees; j++)
        {
            if (questionsUtilisees[j] == i)
            {
                dejaUtilisee = 1;
                break;
            }
        }

        if (!dejaUtilisee)
        {
            disponibles[nbDisponibles] = i;
            nbDisponibles++;
        }
    }

    if (nbDisponibles == 0)
    {
        nbQuestionsUtilisees = 0;
        nbQuestionsMemoire = nbQ;

        for (i = 0; i < nbQ; i++)
        {
            disponibles[i] = i;
        }
        nbDisponibles = nbQ;
    }

    i = disponibles[rand() % nbDisponibles];
    questionsUtilisees[nbQuestionsUtilisees] = i;
    nbQuestionsUtilisees++;
    return i;
}
