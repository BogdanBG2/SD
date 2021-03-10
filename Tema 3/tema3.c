#include "trie.h"
#include "functii.h"
#include "comenzi.h"

int main()
{
    FILE *e = fopen("error.out", "w");
    int nr_comenzi, i;
    char rand[70], cmd[7], aux[70], *p,
    locatie[50] = "/";

    // Initializare sdf
    Trie sdf = initNod(); // Sistem De Fisiere
    if(!sdf)
        return -1;

    inserare(&sdf, "/");

    scanf("%d", &nr_comenzi);
    fgetc(stdin);
    for(i = 1; i <= nr_comenzi; i++)
    {
        fgets(rand, 70, stdin);
        if(rand[strlen(rand) - 1] == '\n')
            rand[strlen(rand) - 1] = '\0';
        strcpy(aux, rand);
        p = strtok(aux, " ");
        strcpy(cmd, p);

        if(!strcmp(cmd, "mkdir"))
            mkdir(&sdf, locatie, rand, e);

        else if(!strcmp(cmd, "touch"))
            touch(&sdf, locatie, rand, e);

        else if(!strcmp(cmd, "ls"))
            ls(sdf, locatie, rand, e);

        else if(!strcmp(cmd, "pwd"))
            pwd(sdf, locatie, rand, e);

        else if(!strcmp(cmd, "cd"))
            cd(sdf, locatie, rand, e);

        else if(!strcmp(cmd, "mv"))
            mv(&sdf, locatie, rand, e);

        else if(!strcmp(cmd, "cp"))
            cp(&sdf, locatie, rand, e);

        else if(!strcmp(cmd, "rm"))
            rm(&sdf, locatie, rand, e);

        else if(!strcmp(cmd, "rmdir"))
            rmdir(&sdf, locatie, rand, e);

        else
        {
            p = strtok(rand, " ");
            fprintf(e, "%s: command not found\n", p);
            continue;
        }
    }

    fclose(e);
    eliberare(&sdf);

    return 0;
}

