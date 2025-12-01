#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct {
  char *_buf; // Allocated input buffer. Preserved for freeing.
  char **lines;
  size_t lines_count;
} Input;

Input read_input(const char *filename) {
  struct stat attr;
  if (stat(filename, &attr) == -1) {
    perror("stat");
    exit(1);
  };
  size_t file_size = attr.st_size;

  int fd = open(filename, O_RDWR | O_CREAT, 0644);
  if (fd == -1) {
    perror("open");
    exit(1);
  }

  void *addr = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (addr == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }
  close(fd);

  char *input = (char *)addr;
  assert(input[file_size - 1] == '\n');
  assert(input[file_size] == '\0');

  size_t line_count = 0;
  for (char *c = (char *)addr; c < (char *)addr + file_size; c++) {
    if (*c == '\n') {
      line_count++;
    }
  }

  char *buf = malloc(file_size);
  if (buf == NULL) {
    perror("malloc");
    exit(1);
  }
  memcpy(buf, addr, file_size);
  munmap(addr, file_size);

  char **lines = malloc(sizeof(char *) * line_count);
  if (lines == NULL) {
    perror("malloc");
    exit(1);
  }

  Input result = {
      ._buf = buf,
      .lines = lines,
      .lines_count = 0,
  };

  char *c = buf;
  for (size_t i = 0; i < line_count; i++) {
    result.lines[i] = c;
    result.lines_count++;
    while (*c != '\n') {
      c++;
    }
    *c = '\0';
    c++;
  }
  assert(result.lines_count == line_count);

  return result;
}

void free_input(Input *input) {
  free(input->_buf);
  free(input->lines);
}