#define _GNU_SOURCE
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
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

  if (mount("proc", "myroot/proc", "proc", 0, NULL) != 0) {
    perror("proc");
  }
  if (mount("sysfs", "myroot/sys", "sysfs", 0, NULL) != 0) {
    perror("sysfs");
  }
  if (mount("none", "myroot/tmp", "tmpfs", 0, NULL) != 0) {
    perror("tmp");
  }
  if (mount("udev", "myroot/dev", "devtmpfs", 0, NULL) != 0) {
    perror("dev");
  }
  if (mount("shm", "myroot/dev/shm", "tmpfs", 0, NULL) != 0) {
    perror("dev/shm");
  }
  if (mount("tmpfs", "myroot/run", "tmpfs", 0, NULL) != 0) {
    perror("run");
  }

  if (chdir("myroot") != 0 || chroot("./") != 0) {
    perror("chdir/chroot");
  }
  execv(container_args[0], container_args);
  INFO("wrong\n");
  return 1;
}

int main(int argc, char const *argv[]) {
  INFO("parent\n");
  int container_pid = clone(container_main, container_stack + STACK_SIZE, CLONE_NEWUTS | CLONE_NEWPID | CLONE_NEWNS | CLONE_NEWIPC | SIGCHLD, NULL);
  waitpid(container_pid, NULL, 0);
  INFO("stop\n");
  return 0;
}
