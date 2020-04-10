#ifndef __FILE_H__
#define __FILE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct FileList FileList;
typedef struct DirectoryList DirectoryList;
typedef struct NodeF NodeF;
typedef struct NodeD NodeD;

typedef struct Directory {
	// The name of the directory
	char *name;

	// TODO: The list of files of the current directory
	FileList *files;

	// TODO: The list of directories of the current directory
	DirectoryList *directories;

	// The parent directory of the current directory (NULL for the root
	// directory)
	struct Directory *parentDir;
} Directory;

// DO NOT MODIFY THIS STRUCTURE
typedef struct File {
	// The name of the file
	char *name;

	// The size of the file
	int size;

	// The content of the file
	char *data;

	// The directory in which the file is located
	Directory *dir;
} File;

typedef struct FileList {
	NodeF *first;
	NodeF *last;
} FileList;

typedef struct DirectoryList {
	NodeD *first;
	NodeD *last;
} DirectoryList;

typedef struct NodeF {
	struct NodeF *next;
	struct NodeF *prev;
	File *new_file;
} NodeF;

typedef struct NodeD {
	struct NodeD *next;
	struct NodeD *prev;
	Directory *new_dir;
} NodeD;

// creates root
void create_FS(Directory **root)
{
	*root = (Directory *) malloc(sizeof(Directory));

	(*root)->parentDir = NULL;
	(*root)->name = "/";
	(*root)->files = NULL;
	(*root)->directories = NULL;
}

// deletes root (!not the whole file system)
void delete_FS(Directory *root)
{
	root = NULL;
	free(root);
}

// adds new file
File *touch(Directory *root, char *nume, char *content)
{
	NodeF *new = (NodeF *) malloc(sizeof(NodeF));

	new->new_file = (File *) malloc(sizeof(File));

	new->new_file->name = (char *)malloc(100*sizeof(char));

	new->new_file->data = (char *)malloc(100*sizeof(char));

	strcpy(new->new_file->name, nume);
	strcpy(new->new_file->data, content);

	if (root->files == NULL) {
		// lista nu contine nimic => trebuie alocata
		// mem pt lista de files si pt first si last
		root->files = (FileList *) malloc(sizeof(FileList));
		root->files->first = (NodeF *) malloc(sizeof(NodeF));
		root->files->last = (NodeF *) malloc(sizeof(NodeF));
		// new devine atat primul cat si ultimul element
		root->files->first = new;
		root->files->last = new;
	} else if (strcmp(root->files->first->new_file->name,
						new->new_file->name) > 0) {
		// e inaintea primului,
		// adaug la inceput
		// primul fisier devine nextul celui adaugat,
		// new ul devine first
		new->next = root->files->first;
		root->files->first = new;
	} else if (strcmp(root->files->last->new_file->name,
						new->new_file->name) < 0) {
		// dupa ultimul
		// nextul ultimului pica pe new, new devine last
		new->prev = root->files->last;
		root->files->last->next = new;
		root->files->last = new;
		root->files->last->next = NULL;
	} else {
		NodeF *i = root->files->first;

		while (i != root->files->last) {
			// merg pana cand numele depaseste
			// lexicografic ce e inaintea lui
			if (strcmp(i->next->new_file->name,
					new->new_file->name) > 0) {
				new->next = i->next;
				i->next->prev = new;
				new->prev = i;
				i->next = new;
				break;
			}
			i = i->next;
		}
	}
	return new->new_file;
}

// new directory
Directory *mkdir(Directory *parent, char *name)
{
	// la fel ca la touch
	NodeD *new = (NodeD *) malloc(sizeof(NodeD));

	new->new_dir = (Directory *) malloc(sizeof(Directory));

	new->new_dir->name = (char *)malloc(100*sizeof(char));

	strcpy(new->new_dir->name, name);
	new->new_dir->parentDir = parent;

	if (parent->directories == NULL) {
		// lista nu contine nimic
		parent->directories = (DirectoryList *)
						malloc(sizeof(DirectoryList));
		parent->directories->first = (NodeD *) malloc(sizeof(NodeD));
		parent->directories->last = (NodeD *) malloc(sizeof(NodeD));
		parent->directories->first = new;
		parent->directories->last = new;
	} else if (strcmp(parent->directories->first->new_dir->name,
						new->new_dir->name) > 0) {
		// e inaintea primului,
		// adaug la inceput
		new->next = parent->directories->first;
		parent->directories->first->prev = new;
		new->prev = NULL;
		parent->directories->first = new;
	} else if (strcmp(parent->directories->last->new_dir->name,
						new->new_dir->name) < 0) {
		// dupa ultimul
		new->prev = parent->directories->last;
		parent->directories->last->next = new;
		parent->directories->last = new;
		parent->directories->last->next = NULL;
	} else {
		NodeD *i = parent->directories->first;

		while (i != parent->directories->last) {
			// merg pana cand numele depaseste
			// lexicografic ce e inaintea lui
			if (strcmp(i->next->new_dir->name,
					new->new_dir->name) > 0) {
				new->next = i->next;
				i->next->prev = new;
				new->prev = i;
				i->next = new;
				break;
			}
			i = i->next;
		}
	}
	return new->new_dir;
}

// prints the content of the directory
void ls(Directory *parent)
{
	// ma plimb prin lista, afisez numele fisierelor
	//si apoi ale directoarelor
	if (parent->files != NULL) {
		NodeF *i;

		for (i = parent->files->first; i != NULL; i = i->next)
			printf("%s ", i->new_file->name);
	}

	if (parent->directories != NULL) {
		NodeD *j;

		for (j = parent->directories->first; j != NULL; j = j->next)
			printf("%s ", j->new_dir->name);
	}

	printf("\n");
}

// prints working directory - uses '/'
void pwd(Directory *dir)
{
	if (dir->parentDir == NULL)
		return;
	if (dir->parentDir != NULL) {
		pwd(dir->parentDir);
		printf("/%s", dir->name);
	}
}

// goes to named directory if exists.
// Else prints: “Cannot move to ‘<directoryname>’: No such directory!”
Directory *cd(Directory *dir, char *where)
{
	if (strcmp(where, "..") == 0 && dir->parentDir != NULL) {
		// daca primeste '..' si nu este root
		// returneaza directorul parinte
		return dir->parentDir;
	} else if (dir->directories == NULL)
		printf("Cannot move to '%s': No such directory!\n", where);
		// daca nu exista alte directoare in directorul actual
	else {
		NodeD *it = dir->directories->first;

		while (it != NULL) {
			// compar fiecare nume de director cu numele primit
			if (strcmp(it->new_dir->name, where) == 0) {
				dir = it->new_dir;
				break;
			}
			it = it->next;
		}
		if (it == NULL)
			printf("Cannot move to '%s': No such directory!\n",
					where);
	}
	return dir;
}

// first prints filenames, after subdirectorys with their contents
void tree(Directory *parent, int i)
{
	// la prima intrare in functie se
	// printeaza numele directorului
	// initial
	if (i == 1)
		printf("%s\n", parent->name);
	if (parent->files != NULL) {
		NodeF *it;

		// se afiseaza mai intai fisierele
		for (it = parent->files->first; it != NULL; it = it->next) {
			int j;

			for (j = 0; j < i; j++)
				printf("    ");
			printf("%s\n", it->new_file->name);
		}
	}
	if (parent->directories != NULL) {
		NodeD *it = parent->directories->first;

		while (it != NULL) {
			// se printeaza toate diectoarele
			//si se reapeleaza functia pentru
			// urmatoarele directoare
			int j;

			for (j = 0; j < i; j++)
				printf("    ");
			printf("%s\n", it->new_dir->name);
			i = i + 1;
			tree(it->new_dir, i);
			it = it->next;
			i = i - 1;
		}
	}
}

// delets file if exists. Else prints: "Cannot remove ‘<filename>’: No
// such file!"
void rm(Directory *parent, char *who)
{
	if (parent->files == NULL) {
		printf("Cannot remove '%s': No such file!\n", who);
		return;
	} else if (strcmp(parent->files->first->new_file->name, who) == 0) {
		parent->files->first =
				parent->files->first->next;
		return;
	} else if (strcmp(parent->files->last->new_file->name, who) < 0) {
		printf("Cannot remove '%s': No such file!\n", who);
		return;
	} else if (strcmp(parent->files->first->new_file->name, who) > 0) {
		printf("Cannot remove '%s': No such file!\n", who);
		return;
	} else if (strcmp(parent->files->last->new_file->name, who) == 0) {
		parent->files->last = parent->files->last->prev;
		parent->files->last->next = NULL;
	} else {
		NodeF *it = parent->files->first->next;

	// caut iterativ fisierul, daca il gasesc sterg legaturile
		while (it != parent->files->last) {
			if (strcmp(it->new_file->name, who) == 0) {
				it->next->prev = it->prev;
				it->prev->next = it->next;
				return;
			}
			it = it->next;
		}
		if (it->next == NULL) {
			printf("Cannot remove '%s': No such file!\n", who);
			return;
		}
	}
}

// deletes directory and everything inside it.
// Else pints: “Cannot remove ‘<directoryname>’: No such directory!”
void rmdir(Directory *parent, char *who)
{
	// same as rm
	if (parent->directories == NULL) {
		printf("Cannot remove '%s': No such directory!\n", who);
		return;
	} else if (strcmp(parent->directories->first->new_dir->name,
						who) == 0) {
		parent->directories->first =
				parent->directories->first->next;
		return;
	} else if (strcmp(parent->directories->last->new_dir->name, who) < 0) {
		printf("Cannot remove '%s': No such directory!\n", who);
		return;
	} else if (strcmp(parent->directories->first->new_dir->name, who) > 0) {
		printf("Cannot remove '%s': No such directory!\n", who);
		return;
	} else if (strcmp(parent->directories->last->new_dir->name, who) == 0) {
		parent->directories->last = parent->directories->last->prev;
		parent->directories->last->next = NULL;
	} else {
		NodeD *it = parent->directories->first->next;

	// caut iterativ directorul, daca il gasesc sterg legaturile
		while (it != parent->directories->last) {
			if (strcmp(it->new_dir->name, who) == 0) {
				it->next->prev = it->prev;
				it->prev->next = it->next;
				return;
			}
			it = it->next;
		}
		if (it->next == NULL) {
			printf("Cannot remove '%s': No such directory!\n", who);
			return;
		}
	}
}

#endif /* __FILE_H__ */

