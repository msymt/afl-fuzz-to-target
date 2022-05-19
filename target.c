#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  char *output = "./out.txt";
  char str[256];
  scanf("%s", str);
  printf("%s\n", str);

  FILE *fp;
  fp = fopen(output, "w");
  fclose(fp);

  int fd = open(output, O_RDWR | O_CREAT, 0644);
  write(fd, str, strlen(str));
  close(fd);
  return 0;
}
