#include "main.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/**
 * append_text_to_file-appends text to a file
 * @filename:filename
 * @text_content:text to be written
 * Return:returns -1 on error 1 on success
 */

int append_text_to_file(const char *filename, char *text_content)
{
	int fd;
	ssize_t w;
	size_t len = 0;

	if (filename == NULL)
		return (-1);

	fd = open(filename, O_WRONLY | O_APPEND);
	if (fd == -1)
		return (-1);

	if (text_content == NULL)
	{
		close(fd);
		return (1);
	}

	len = strlen(text_content);
	w = write(fd, text_content, len);

	if (w == -1 || (size_t)w != len)
	{
		close(fd);
		return (-1);
	}

	close(fd);
	return (1);
}
