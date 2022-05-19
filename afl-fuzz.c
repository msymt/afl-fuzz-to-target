#include "debug.h"

int main(int argc, char *argv[]){
  int pid;
  int status;
  int out_fd;

  char *target_path = "./target";
  char *fuzz = "Hello,World!";
  char *out_file = "./.cur_input";

  // afl: setup_stdio_file()
  // make .cur_input
  FILE *fp;
  fp = fopen(out_file, "w");
  fclose(fp);
  out_fd = open(out_file, O_RDWR | O_CREAT, 0600);
  unlink(out_file);

  // afl: write_to_testcase()
  lseek(out_fd, 0, SEEK_SET); // 先頭
  write(out_fd, fuzz, strlen(fuzz));
  lseek(out_fd, 0, SEEK_SET); // 先頭

  // afl: run_target()
  pid = fork();

  if(pid < 0) {
    printf("fork error\n");
    return 1;
  }
  else if(pid == 0) {
    printf("child process\n");

    setsid();
    dup2(out_fd, 0);
    close(out_fd);
    execv(target_path, argv);
    exit(0);
  }
  else {
    printf("parent process\n");
    wait(&status);
    printf("child process exit\n");
  }
  return 0;
}