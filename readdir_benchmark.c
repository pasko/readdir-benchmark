
#include <dirent.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

int64_t g_iterations = 10000LL;

int
__attribute__((noinline))
get_total_entries() {
  DIR *d;
  if ((d = opendir(".")) == NULL) {
    perror("opendir");
    abort();
  }
  struct dirent *d_entry;
  int total = 0;
  while ((d_entry = readdir(d)) != NULL) {
    if (d_entry->d_type & DT_REG) {
      total++;
    }
  }
  if (errno) {
    perror("readdir");
    abort();
  }
  closedir(d);
  return total;
}

int main() {

  int64_t total_entries = 0;
  for (int i = 0; i < g_iterations; i++) {
    total_entries += get_total_entries();
  }
  printf("Regular files found: %d\n", total_entries / g_iterations);
}
