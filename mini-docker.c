#define _GNU_SOURCE
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "utils.h"

#define STACK_SIZE (1024 * 1024)

static char container_stack[STACK_SIZE];
const char cname[] = "wkx-container";
char *const container_args[] = {"/usr/bin/bash", NULL};

int container_main(void *arg) {
  INFO("child\n");
  if (sethostname(cname, strlen(cname)) != 0) {
    INFO("sethostname failed\n");
  }
  system("mount -t proc proc /proc");
  execv(container_args[0], container_args);
  INFO("wrong\n");
  return 1;
}

int main(int argc, char const *argv[]) {
  INFO("parent\n");
  int container_pid = clone(container_main, container_stack + STACK_SIZE, CLONE_NEWUTS | CLONE_NEWPID | CLONE_NEWIPC | SIGCHLD, NULL);
  waitpid(container_pid, NULL, 0);
  INFO("stop\n");
  return 0;
}
