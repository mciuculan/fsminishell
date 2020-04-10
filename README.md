# fsminishell
Main-ul citeste linie cu linie si adauga fiecare cuvant intr-o lista pentru a avea acces la numele functiei si la eventuali parametri. Scoate ultimul '\n' din buffer. Apoi compara primul cuvant cu numele de functii pe care apoi le apeleaza.
Line.h este pentru crearea cozii de cuvinte respective.
In file.h am am creat pe langa structurile Directory si File, structurile FileList si DirectoryList care contin primul si ultimul element din listele respective. De asemenea am si NodeF si NodeD pe care le-am folosit pt a tine fisierul si directorul si urmatorul respectiv anteriorul nod. Folosesc liste dublu inlantuite. 
Create FS aloca memorie pentru Directorul root.
Delete FS sterge root-ul.
Touch verifica 4 cazuri: Lista de files nu exista deci aloca memorie pt ea si adauga noul fisier considerandu-l primul cat si ultimul fisier. Numele fisierului este mai mic lexicografic decat primul fisier deci il adaug inaintea lui, numele este mai mare decat ultimul, il adaug la final, sau se afla undeva intre. In acest ultim caz ma plimb prin lista si compar mereu cu urmatorul element. Daca urmatorul este mai mare lexicografic decat numele atunci inserez.
Pe acelasi principiu functioneaza si mkdir.
LS este o printare obisnuita de liste.
PWD intra recursiv de la directorul curent la radacina pentru a le putea afisa pe rand.
CD verifica mai intai daca i se cere sa mearca in directorul anterior prin "..". Dupa, verifica daca exista lista de directoare in care sa intre. Apoi parcurge lisa si intra daca gaseste numele restectiv si iese din while dupa ce schimba directorul. Daca nu il gaseste, da un mesaj de eroare. returneaza directorul in care se afla in urma operatiilor.
Tree este o functie recursiva. La prima intrare afiseaza directorul parinte. apoi afiseaza toate fisierele si apoi se reapeleaza functia pentru urmatoarele directoare.
RM si RMDIR cauta iterativ fisierul/directorul cerut iar daca il gasesc modifica legaturile. Daca se afla lexicografic inaintea primului sau dupa ultimul inseamna ca nu exista. De asemenea, daca este primul sau ultimul fisier, trebuie facute diferit legaturile fata de daca s-ar afla la inceput.
