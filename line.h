#ifndef LINE_H
#define LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char *value;
	struct Node *next;
} Node;

typedef struct Line {
	Node *front;
	Node *rear;
	int size;
} Line;

void init_Line(Line **l)
{
	*l = (Line *) malloc(sizeof(Line));

	(*l)->size = 0;
	(*l)->front = NULL;
	(*l)->rear = NULL;
}

int is_empty_Line(Line *l)
{
	return l->front == NULL ? 1 : 0;
}

void enqueue(Line *l, char *word)
{
	Node *new_node = (Node *) malloc(sizeof(Node));

	new_node->value = (char *)malloc(100*sizeof(char));

	strcpy(new_node->value, word);

	if (is_empty_Line(l)) {
		l->front = new_node;
		l->rear = new_node;
	} else {
		l->rear->next = new_node;
		l->rear = new_node;
	}
	l->size++;
}

void split_text(Line *l, char *text)
{
	char *word;

	word = strtok(text, " ");
	while (word != NULL) {
		enqueue(l, word);
		word = strtok(NULL, " ");
	}
}

#endif
