#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "main.h"

#define BUFFER_SIZE 1024

/**
 * error- prints error from posix error output
 * @code: an integer
 * @msg: a message
 * @file: file that failed to copy
 */

void error(int code, const char *msg, const char *file)
{
	dprintf(STDERR_FILENO, msg, file);
	exit(code);
}

/**
 * main- copies a file to another file, creating it if it does not exist
 * @argc: arg count
 * @argv: arguments
 * Return: returns 97 on incorrect use, 98 if cant read,
 * 99 if cant write, and 100 if cant close, else 0
 */

int main(int argc, char *argv[])
{
	int fd_from, fd_to, r, w;
	char buffer[BUFFER_SIZE];

	if (argc != 3)
		error(97, "Usage: cp file_from file_to\n", "");

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
		error(98, "Error: Can't read from file %s\n", argv[1]);

	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
		error(99, "Error: Can't write to %s\n", argv[2]);

	while ((r = read(fd_from, buffer, BUFFER_SIZE)) > 0)
	{
		w = write(fd_to, buffer, r);
		if (w != r)
			error(99, "Error: Can't write to %s\n", argv[2]);
	}

	if (r == -1)
		error(98, "Error: Can't read from file %s\n", argv[1]);

	if (close(fd_from) == -1)
		error(100, "Error: Can't close fd %d\n", argv[1]);

	if (close(fd_to) == -1)
		error(100, "Error: Can't close fd %d\n", argv[2]);

	return (0);
}
