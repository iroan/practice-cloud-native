#! /usr/bin/bash
set -x
START_DIR=$PWD

function showIPC() {
    ipcs --limits  --human
    ipcs --creator
    ipcs --pid
    ipcs --shmems
    ipcs --queues
    ipcs --semaphores
}

function envDiff() {
    uname -a
    showIPC
    # top
    # echo $$
}

function miniDocker() {
    cd $START_DIR
    rm -f *.out
    gcc -Og -o miniDocker.out mini-docker.c
    # sethostname need super power
    sudo ./miniDocker.out
    # showIPC
}

function debugCgroup(){
    mount -t cgroup    
    cd /sys/fs/cgroup/cpu/
    sudo mkdir wkx-demo
}
$@
