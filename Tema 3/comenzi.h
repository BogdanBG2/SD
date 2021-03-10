#include "functii.h"

#ifndef COMENZI
#define COMENZI

void mkdir(Trie* asdf, char locatie[50], char cmd[70], FILE *e)
{
    char *p, *dir, *c, *c2;
    int np = nr_parametri(cmd), sem;
    if(np < 2)
    {
        fprintf(e, "%s: missing operand\n", cmd);
        return;
    }

    p = strtok(cmd, " ");
    for(p = strtok(NULL, " "); p; p = strtok(NULL, " "))
    {
        dir = asamblare_cale(locatie, p, 0);
        if(!dir)
            return;

        if(cauta(*asdf, dir))
        {
            fprintf(e, "%s: already exists\n", p);
            continue;
        }

        sem = 1;
        c = dir_parinte(dir);
        if(!c)
        {
            free(dir); dir = NULL;
            return;
        }

        while(strcmp(c, "/") && sem)
        {
            sem = cauta(*asdf, c);
            if(!sem)
            {
                fprintf(e, "%s: No such file or directory\n", p);
                break;
            }

            c2 = dir_parinte(c);
            if(!c2)
            {
                free(c); c = NULL;
                free(dir); dir = NULL;
                return;
            }
            free(c);
            c = c2;
        }

        if(!sem)
            continue;

        free(c); c = NULL;
        
        inserare(asdf, dir);
        free(dir); dir = NULL;
    }
}

void touch(Trie* asdf, char locatie[50], char cmd[70], FILE* e)
{
    char *p, *fisier;
    int np = nr_parametri(cmd);
    if(np < 2)
    {
        fprintf(e, "%s: missing operand\n", cmd);
        return;
    }

    p = strtok(cmd, " ");
    for(p = strtok(NULL, " "); p; p = strtok(NULL, " "))
    {
        fisier = asamblare_cale(locatie, p, 1);
        if(!fisier)
            return;
        //strcpy(fisier, asamblare_cale(locatie, p, 1));
        if(cauta(*asdf, fisier))
        {
            fprintf(e, "%s: already exists\n", p);
            continue;
        }

        inserare(asdf, fisier);
        free(fisier); fisier = NULL;
    }
}

void pwd(Trie sdf, char locatie[50], char cmd[70], FILE* e)
{
    char aux[50];

    if(nr_parametri(cmd) > 1)
    {
        fprintf(e, "%s: too many arguments\n", cmd);
        return;
    }

	if(strcmp(locatie, "/") && locatie[strlen(locatie) - 1] == '/')
    {
		strncpy(aux, locatie, strlen(locatie) - 1);
        aux[strlen(locatie) - 1] = '\0';
    }
	else
		strcpy(aux, "/");

	printf("%s\n", aux);
}

void cd(Trie sdf, char* locatie, char cmd[70], FILE* e)
{
    int np = nr_parametri(cmd);
    char *p, *dir, *aux;

    if(np < 2)
	{
		fprintf(e, "%s: missing operand\n", cmd);
		return;
	}
	else if(np > 2)
	{
		fprintf(e, "%s: too many arguments\n", cmd);
		return;
	}

	p = strtok(cmd, " "); // aici e cd
	p = strtok(NULL, " "); // parametrul necesar

    aux = asamblare_cale(locatie, p, 1);
    if(!aux)
        return;
    
    dir = asamblare_cale(locatie, p, 0);
    if(!dir)
    {
        free(aux); aux = NULL;
        return;
    }
    /*/strcpy(aux, asamblare_cale(locatie, p, 1));
	strcpy(dir, aux);
	if(dir[strlen(dir) - 1] != '/')
		strcat(dir, "/");
    */
	if(!cauta(sdf, dir) && cauta(sdf, aux))
    {
		fprintf(e, "%s: Not a directory\n", p);
    }
	else if(!cauta(sdf, dir) && strcmp(dir, "/"))
    {
        fprintf(e, "%s: No such file or directory\n", p);
    }
    else
    {
    	strcpy(locatie, dir);
    }

    free(dir); dir = NULL;
    free(aux); aux = NULL;
}

void mv(Trie* asdf, char locatie[50], char cmd[70], FILE* e)
{
    int np = nr_parametri(cmd), i;
    char *p, *r, sursa[50], dest[50], fisier[50], aux[50], auxp[50];
    if(np < 3)
    {
        fprintf(e, "%s: missing operand\n", cmd);
        return;
    }

    char M[np - 1][50];
    strcpy(aux, cmd);
    p = strtok(aux, " ");
    p = strtok(NULL, " ");
    for(i = 0; i < np - 2 && p; i++, p = strtok(NULL, " "))
    {
        strcpy(auxp, p);
        strcpy(M[i], asamblare_cale(locatie, p, 1));
        if(!cauta(*asdf, M[i]))
        {
            fprintf(e, "%s: No such file or directory\n", auxp);
            return;
        }
    }

    strcpy(aux, asamblare_cale(locatie, p, 1));
    strcpy(M[i], aux);
    strcpy(auxp, p);
    if(M[i][strlen(M[i]) - 1] != '/')
        strcat(M[i], "/");

    if(!cauta(*asdf, M[i]) && !cauta(*asdf, aux) && strcmp(aux, "/"))
    {
        fprintf(e, "%s: No such file or directory\n", auxp);
        return;
    }
    else if(!cauta(*asdf, M[i]) && cauta(*asdf, aux))
    {
        fprintf(e, "%s: Not a directory\n", auxp);
        return;
    }

    p = strtok(cmd, " ");
    p = strtok(NULL, " ");
    for(i = 0; i < np - 2; p = strtok(NULL, " "), i++)
    {
        strcpy(sursa, M[i]);
        strcpy(dest, M[np - 2]);
        for(r = strtok(p, "/"); r; strcpy(fisier, r), r = strtok(NULL, "/"));
        strcat(dest, fisier);

        stergere(asdf, sursa);
        inserare(asdf, dest);
    }
}

void cp(Trie* asdf, char locatie[50], char cmd[70], FILE* e)
{
	int np = nr_parametri(cmd), i;
	char *p, *r, sursa[50], dest[50], fisier[50], aux[50], auxp[50];
	if(np < 3)
	{
		fprintf(e, "%s: missing operand\n", cmd);
		return;
	}

    char M[np - 1][50];
    strcpy(aux, cmd);
    p = strtok(aux, " ");
	p = strtok(NULL, " ");
	for(i = 0; i < np - 2 && p; i++, p = strtok(NULL, " "))
    {
        strcpy(auxp, p);
        strcpy(M[i], asamblare_cale(locatie, p, 1));
        if(!cauta(*asdf, M[i]))
        {
            fprintf(e, "%s: No such file or directory\n", auxp);
            return;
        }
    }

    strcpy(aux, asamblare_cale(locatie, p, 1));
    strcpy(M[i], aux);
    strcpy(auxp, p);
    if(M[i][strlen(M[i]) - 1] != '/')
        strcat(M[i], "/");

    if(!cauta(*asdf, M[i]) && !cauta(*asdf, aux) && strcmp(aux, "/"))
    {
        fprintf(e, "%s: No such file or directory\n", auxp);
        return;
    }
    else if(!cauta(*asdf, M[i]) && cauta(*asdf, aux))
    {
        fprintf(e, "%s: Not a directory\n", auxp);
        return;
    }

    p = strtok(cmd, " ");
    p = strtok(NULL, " ");
    for(i = 0; i < np - 2; p = strtok(NULL, " "), i++)
    {
        strcpy(sursa, M[i]);
        strcpy(dest, M[np - 2]);
        for(r = strtok(p, "/"); r; strcpy(fisier, r), r = strtok(NULL, "/"));
        strcat(dest, fisier);

        inserare(asdf, dest);
    }
}

void rm(Trie* asdf, char locatie[50], char cmd[70], FILE* e)
{
	int np = nr_parametri(cmd);
	char *p, *fisier;

	if(np < 2)
	{
		fprintf(e, "%s: missing operand\n", cmd);
		return;
	}

	p = strtok(cmd, " ");
	p = strtok(NULL, " ");
	for(; p; p = strtok(NULL, " "))
	{
		// asamblare cale
		fisier = asamblare_cale(locatie, p, 1);
        if(!fisier)
            return;

		if(!cauta(*asdf, fisier))
		{
			fprintf(e, "%s: No such file or directory\n", p);
			continue;
		}

		stergere(asdf, fisier);
	   free(fisier); fisier = NULL;
    }
}

void rmdir(Trie* asdf, char locatie[50], char cmd[70], FILE* e)
{
	int np = nr_parametri(cmd);
	char *p, *aux, dir[50];

	if(np < 2)
	{
		fprintf(e, "%s: missing operand\n", cmd);
		return;
	}

	p = strtok(cmd, " ");
	for(p = strtok(NULL, " "); p; p = strtok(NULL, " "))
	{
		// asamblare cale
		aux = asamblare_cale(locatie, p, 1);
        if(!aux)
            return;

		strcpy(dir, aux);
		if(strcmp(dir, "/"))
			strcat(dir, "/");

        if(!cauta(*asdf, dir))
        {
           fprintf(e, "%s: No such file or directory\n", p);
            continue;
        }
		// nu e director
		if(!cauta(*asdf, dir) && cauta(*asdf, aux))
		{
			fprintf(e, "%s: Not a directory\n", p);
			p = strtok(NULL, " ");
			continue;
		}

		if(mostenitori(subarbore(*asdf, dir)))
		{
			fprintf(e, "%s: Directory not empty\n", p);
			continue;
		}

		stergere(asdf, dir);
	}

    free(aux);
    aux = NULL;
}

void ls(Trie sdf, char locatie[50], char cmd[70], FILE* e)
{
    int np = nr_parametri(cmd);
    char str[20], aux[50], L[50], *p;
    Trie sdf2;
    if(np > 3)
    {
        fprintf(e, "%s: too many arguments\n", cmd);
        return;
    }

    strcpy(aux, locatie);
    strcpy(L, cmd);
    if((!strncmp(cmd, "ls", 2) && strncmp(cmd, "ls -F", 5))
    || (!strncmp(cmd, "ls -F", 5) && np == 3))
    {
        p = strtok(L, " ");
        p = strtok(NULL, " ");
        if(np == 3)
            p = strtok(NULL, " ");
        if(p)
        {
            strcpy(aux, asamblare_cale(locatie, p, 0));
            if(!cauta(sdf, aux))
            {
                fprintf(e, "%s: No such file or directory\n", p);
                return;
            }
        }
    }

    sdf2 = subarbore(sdf, aux);
    sdf2->capat = 0;

    if(!strncmp(cmd, "ls -F", 5))
        afisare_detaliata(sdf2, str, 0);
    else
        afisare(sdf2, str, 0);
    printf("\n");

    sdf2->capat = 1;
}


#endif
