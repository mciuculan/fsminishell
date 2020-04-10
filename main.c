#include "file.h"
#include "line.h"

int main(int argc, char const *argv[])
{
	Directory *root, *actual_dir, *current_dir;
	char buffer[100];

	while (fgets(buffer, 100, stdin)) {
		int len = strlen(buffer);

		if (buffer[len - 1] == '\n')
			buffer[len - 1] = '\0';

		Line *l;

		init_Line(&l);
		split_text(l, buffer);

		if (strcmp(l->front->value, "create") == 0
			&& strcmp(l->rear->value, "fs") == 0) {
			create_FS(&root);
			actual_dir = root;
			current_dir = actual_dir;
		}
		if (strcmp(l->front->value, "touch") == 0)
			touch(current_dir, l->front->next->value,
			l->rear->value);
		if (strcmp(l->front->value, "mkdir") == 0)
			mkdir(actual_dir, l->front->next->value);
		if (strcmp(l->front->value, "ls") == 0)
			ls(actual_dir);
		if (strcmp(l->front->value, "cd") == 0) {
			current_dir = cd(actual_dir, l->rear->value);
			actual_dir = current_dir;
		}
		if (strcmp(l->front->value, "tree") == 0)
			tree(actual_dir, 1);
		if (strcmp(l->front->value, "pwd") == 0) {
			if (actual_dir == root)
				printf("/");
			else
				pwd(actual_dir);
			printf("\n");
		}
		if (strcmp(l->front->value, "rm") == 0)
			rm(actual_dir, l->rear->value);
		if (strcmp(l->front->value, "rmdir") == 0)
			rmdir(actual_dir, l->rear->value);
		if (strcmp(l->front->value, "delete") == 0
			&& strcmp(l->rear->value, "fs") == 0) {
			delete_FS(root);

			break;
		}
		free(l);
	}

	return 0;
}

