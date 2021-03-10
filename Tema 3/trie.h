#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef TRIE2
#define TRIE2


typedef struct cel
{
    int capat;
    struct cel * caracter[38];
} NodTrie, *Trie;


int atrib(char c) // regula de atribuire a indicilor caracterelor necesare
{
    if(c == '.') // . -> 0
        return 0;
    else if(c == '/') // / -> 1
        return 1;
    else if(c >= 'a' && c <= 'z')
        return c - 'a' + 2; // a-z -> 2-27
    else if(c >= '0' && c <= '9')
        return c - '0' + 28; // 0-9 -> 28-37

    return -1;
}

char atrib_revers(int x)
{
    if(x == 0)
        return '.';
    else if(x == 1)
        return '/';
    else if(x >= 2 && x <= 27)
        return 'a' + x - 2;
    else if(x >= 28 && x <= 37)
        return '0' + x - 28;
    else
        return '\0';
}

Trie initNod()
{
    Trie nod = (Trie)malloc(sizeof(NodTrie));
    if(!nod)
        return NULL;

    nod->capat = 0;
    
	int i;
	for(i = 0; i < 38; i++)
        nod->caracter[i] = NULL;
    return nod;
}

Trie subarbore(Trie t, char locatie[50])
{
    int i;
    Trie aux = t;
    for(i = 0; i < strlen(locatie); i++)
        aux = aux->caracter[atrib(locatie[i])];
    return aux;
}

int cauta(Trie head, char *str)
{
    if(!head)
        return 0;

    for(; *str; str++)
    {
        head = head->caracter[atrib(*str)];
        if(!head)
            return 0;
    }
    return head->capat;
}

int inserare(Trie* head, char *str)
{
    if(cauta(*head, str))
        return -1;

    int k;
    Trie crt = *head;
    for(; *str; str++)
    {
        k = atrib(*str);
        if(!(crt->caracter[k]))
        {
            crt->caracter[k] = initNod();
            if(!(crt->caracter[k]))
                return 0;
        }
        crt = crt->caracter[k];
    }
    crt->capat = 1;
    return 1;
}

int mostenitori(Trie head)
{
	int i;
    for(i = 0; i < 38; i++)
        if(head->caracter[i])
            return 1;
    return 0;
}

int stergere(Trie* crt, char *str)
{
    if(!(*crt))
        return 0;

    if(*str)
    {
        int k = atrib(*str);
        if((*crt) // daca nu am depasit trie-ul
        && ((*crt)->caracter[k]) // daca exista caracterul respectiv
        && stergere(&((*crt)->caracter[k]), str + 1) 
        && !((*crt)->capat)) // nu e capat de cuvant
        {
            if(!mostenitori(*crt))
            {
                free(*crt);
                *crt = NULL;
                return 1; // stergere cu succes
            }
            else
                return 0;
        }
    }

    if(*str == '\0' && (*crt)->capat) // capat de cuvant
    {
        if(!mostenitori(*crt))
        {
            free(*crt);
            *crt = NULL;
        }
        else
            (*crt)->capat = 0;
    }
    return 1;
}

void eliberare(Trie *head)
{
    int i;
    if(!(*head))
        return;

    for(i = 0; i < 38; i++)
    {
        if((*head)->caracter[i])
            eliberare(&((*head)->caracter[i]));
    }
	
	free(*head);
	*head = NULL;
}


void afisare(Trie head, char str[20], int l)
{
    if(head->capat == 1)
    {
        str[l] = '\0';

        if(str[l-1] == '/')
        {
            str[l - 1] = '\0';
            printf("%s ", str);
            return;
        }
        else
            printf("%s ", str);
    }

    int i;
    for(i = 0; i < 38; i++)
        if(head->caracter[i])
        {
            str[l] = atrib_revers(i);
            afisare(head->caracter[i], str, l + 1);
        }
}

void afisare_detaliata(Trie head, char str[20], int l)
{
    if(head->capat == 1)
    {
        str[l] = '\0';

        if(str[l-1] != '/') // fisier
        {
            strcat(str, "*");
            printf("%s ", str);
        }
        else // director
        {
            printf("%s ", str);
            return;
        }
    }

    int i;
    for(i = 0; i < 38; i++)
        if(head->caracter[i])
        {
            str[l] = atrib_revers(i);
            afisare_detaliata(head->caracter[i], str, l + 1);
        }
}


#endif
