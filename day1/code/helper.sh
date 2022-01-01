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

function umountRootFS() {
    cd $START_DIR/myroot
    sudo umount --quiet proc
    sudo umount --quiet sys
    sudo umount --quiet tmp
    sudo umount --quiet -R dev
    sudo umount --quiet run
}

function miniDocker() {
    cd $START_DIR
    rm -f *.out
    gcc -Og -o miniDocker.out mini-docker.c
    # sethostname need super power
    umountRootFS

    cd $START_DIR
    sudo ./miniDocker.out
    umountRootFS
    # showIPC
}

function debug(){
    # sudo apt search debootstrap
    # sudo apt install debootstrap
    # debootstrap --help
    rm -f *.patch
    git format-patch -5
    # git format-patch --help
    exit 0
    arch
    ls /usr/share/debootstrap/scripts
    sudo debootstrap --no-check-gpg --verbose --arch amd64 bullseye myroot https://mirrors.tuna.tsinghua.edu.cn/debian/
}
$@
