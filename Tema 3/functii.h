#include "trie.h"

#ifndef FUNCTII
#define FUNCTII

int nr_parametri(char cmd[70]) // Cati parametrii are comanda citita?
{
    int n;
    char aux[70];
    strcpy(aux, cmd);
    char *p = strtok(aux, " ");
    for(n = 0; p; p = strtok(NULL, " "), n++);
    return n;
}

// cand avem ".." la inceput de comanda
char* dir_parinte(char* locatie)
{
    int i;
    /*
    char rez[50];
    for(i = 0; i < 50; i++)
        rez[i] = 'N';
    */
	char *rez = (char*)calloc(50, sizeof(char));
    if(!rez)
        return NULL;
    

    if(!strcmp(locatie, "/") || !strcmp(locatie, ""))
    {
        strcpy(rez, "Q");
        return rez;
    }

	for(i = strlen(locatie) - 2; locatie[i] != '/'; i--);
	//for(j = 0; j <= i; rez[j] = locatie[j], j++);
    memcpy(rez, locatie, i + 1);

    rez[i + 1] = '\0';
	return rez;

}

// locatie + (director/fisier curent) + tip (0 - director, 1 - fisier)
char* asamblare_cale(char* locatie, char* A, int tip)
{
    /* AICI E BINE
    char D[50]; // directorul parinte al locatiei curente
    strcpy(D, dir_parinte(locatie));
    */

    if((!strcmp(locatie, "/") && !strcmp(A, ".."))
       || !strcmp(locatie, "Q"))
        return "Q";


    char *D;/* = dir_parinte(locatie);
    if(!D)
        return NULL;*/

    char *path = (char*)calloc(50, sizeof(char)), *aux;
    if(!path)
        return NULL;

    // cale absoluta
    if(!strncmp(A, "/", 1))
        strncpy(path, A, strlen(A));

    else // cale relativa
    {
        if(!strcmp(A, "."))
            strncpy(path, locatie, strlen(locatie));

        else if(!strncmp(A, "./", 2))
        {
            aux = asamblare_cale(locatie, A + 2, 1);
            strncpy(path, aux, strlen(aux));
            free(aux);
        }

        else if(!strcmp(A, ".."))
        {
            D = dir_parinte(locatie);
            if(!D)
            {
                free(path); path = NULL;
                return NULL;
            }
            strncpy(path, D, strlen(D));
            free(D);
        }

		else if(!strncmp(A, "../", 3))
        {
            D = dir_parinte(locatie);
            if(!D)
            {
                free(path); path = NULL;
                return NULL;
            }
            aux = asamblare_cale(D, A + 3, 1);
            strncpy(path, aux, strlen(aux));
            free(aux);
            free(D);
        }
        else
        {
            strncpy(path, locatie, strlen(locatie));
            strcat(path, A);
        }
    }

    if(!tip && path[strlen(path) - 1] != '/') // pentru mkdir
        strcat(path, "/");

    //free(D); D = NULL;
    return path;
}

#endif
