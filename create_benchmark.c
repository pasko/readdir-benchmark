
#include <dirent.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

uint64_t g_iterations = 100000ULL;
char g_buf[256];

void
__attribute__((noinline))
create_and_delete_unique_file(int file_index) {
  if (sprintf(g_buf, "fffa" PRIu64, file_index) <= 0) {
    fprintf(stderr, "sprintf failed");
    abort();
  }
  int fd = open(g_buf, O_RDWR|O_CREAT);
  if (fd == -1) {
    perror("open");
    abort();
  }
  close(fd);
  if (unlink(g_buf) == -1) {
    perror("unlink");
    abort();
  }
}

int main() {

  int64_t total_entries = 0;
  for (uint64_t i = 0; i < g_iterations; i++) {
    create_and_delete_unique_file(i);
  }
  printf("Created and deleted this number of files: %" PRIu64 "\n", g_iterations);
}
