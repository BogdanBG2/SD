******************************************************************************
Bogdan-Andrei Buga, 312CB
******************************************************************************

Fisierul "trie.h"

	Pentru sistemul de fisiere necesar, am folosit un arbore (Trie)cu 38 de 
ramuri (unul pentru '.', altul pentru '/', 26 pentru caracterele de la 'a' la
'z', 10 pentru caracterele de la '0' la '9') si variabila 'capat', care 
marcheaza daca nodul respectiv este sau nu capatul unui sir de caractere ce
se gaseste in arborele nostru.

Functii:
int atrib(char c)
	Pentru fiecare caracter mentionat mai sus, asociem un indice de la 0 la
	37, necesar pentru parcurgerea arborelui.

char atrib_revers(int x)
	Daca notam prima functie cu f, aceasta functie joaca rolul lui 
	f^(-1).

Trie initNod()
	Initializeaza un nod de trie fara mostenitori(toate ramurile goale) si
	capatul 0.
	
Trie subarbore(Trie t, char locatie[50])
	Trie-ul dat ca parametru este parcurs pe caracterele sirului "locatie",
	rezultatul returnat fiind subarborele nodului la care am ajuns.
	
int cauta(Trie head, char *str)
	Returneaza daca exista sau nu sirul "str" in trie-ul "head".
	
int inserare(Trie* head, char *str)
	Daca "str" nu este deja in "head", parcurgem trie-ul dupa caracterele lui
	"str", creem noduri noi unde este cazul si marcam capatul ultimului nod
	parcurs cu 1.

int mostenitori(Trie head)
	Returneaza 0 daca exista macar o ramura nenula in "head" si 1 in caz
	contrar.
	
int stergere(Trie* crt, char *str)
	Prin apelul recursiv, ajungem la nodul corespunzator ultimului caracter.
	Daca acesta nu are mostenitori, poate fi sters.
	
void eliberare(Trie *head)
	Elibereaza trie-ul alocat dinamic.
	
void afisare(Trie head, char str[20], int l)
	Afiseaza in stdout sirurile existente in trie.
	
void afisare_detaliata(Trie head, char str[20], int l)
	La fel ca la "afisare", cu urmatoarea diferenta:
		- daca sirul se termina cu "/", il va afisa cu "/" la final si nu il
		va sterge ca la "afisare"
		- in caz contrar, sirul se va afisa cu "*" in capat.

******************************************************************************

Fisierul "functii.h"

Functii:
int nr_parametri(char cmd[70])
	Returneaza numarul de cuvinte din comanda citita de la tastatura.

char* dir_parinte(char* locatie)
	Returneaza:
	- un sir de eroare "Q", daca locatia data este "/"
	- directorul parinte al locatiei date ca parametru, in caz contrar
	
char* asamblare_cale(char* locatie, char* A, int tip)
	Returneaza calea asamblata dupa locatia curenta si parametrul A citit
	in comanda. Se vor parcurge cazurile caii absolute si caii relative cu
	si fara ".", "./", "..", "../". Daca tip este 0, se va returna calea unui
	director, iar daca e 1, se va returna calea unui fisier.
	
******************************************************************************

Fisierul "comenzi.h"

	Modul de lucru al acestui proiect presupune lucrul in paralel cu un trie si
cu locatia retinuta separat, functiile prezentate mai jos avand ca parametrii
trie-ul in care retinem fisierele si directoarele din sistemul nostru de
fisiere, locatia curenta, comanda citita de la tastatura si fisierul in care
vom pune mesajele de eroare(daca este cazul).

	Fiecare funcite are un numar (minim, maxim sau exact) de parametrii ce
trebuie respectat.

1) mkdir
	Parcurgem parametrii din comanda, carora le asamblam caile de directoare
	(tip = 0). Daca nu exista sau daca exista directoarele din care fac parte,
	directoarele pot fi inserate cu succes.

2) touch
	La fel ca la mkdir, cu diferenta ca asamblam cai de fisiere (tip = 1).

3) pwd
	Afisam locatia curenta.
	
4) cd
	Daca parametrul dat in comanda exista ca director, locatia curenta va fi
	schimbata in calea corespunzatoare acestui parametru.
	
5) mv
	Retinem caile tuturor parametrilor comenzii intr-un vector de siruri de
	caractere M, ultimul element al acestui vector reprezentand calea unui
	director. Creem caile noilor fisiere concatenand fisierele din toate
	elementele vectorului de la primul la penultimul la directorul din ultimul
	element si stergem sursele din care am creat noile cai, care vor fi
	ulterior inserate in trie.

6) cp
	La fel ca la mv, cu diferenta ca sursele nu vor fi sterse.
	
7) rmdir
	Parcurgem parametrii din comanda, carora le asamblam caile de directoare
	(tip = 0). Daca exista si daca nu contin alte fisiere/directoare, aceste 
	directoare pot fi sterse cu succes.

8) rm
	La fel ca la rmdir, cu diferenta ca asamblam cai de fisiere (tip = 1).

9) ls
	Afiseaza toate fisierele si directoarele din calea prezenta sau calea
	data ca parametru. Putem vedea care dintre acestea sunt fisiere si care
	sunt directoare cu "ls -F".
