#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <string.h>

int main(int argc, char **argv) {
  int fd;
  ssize_t nr;
  if (argc < 3){
    printf("Not enough arguments.\n");
    syslog(LOG_ERR, "Not enough arguments\n");
    exit(1);
  }
    
  fd = open(argv[1], O_CREAT|O_EXCL|O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IRGRP|S_IROTH);
  if (fd == -1) {
    printf("Error opening file.\n");
    syslog(LOG_ERR, "File failed to create or open.\n");
    exit(1);

  }
  nr = write (fd, argv[2], strlen(argv[2]));
  if (nr == -1) {
    printf("Error writing to file.\n");
    syslog(LOG_ERR, "Error writing to file.\n");
    exit(1);
  }


  printf("We've made it this far. This is the end.\n");
  exit(0);
}
