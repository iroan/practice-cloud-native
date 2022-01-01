#! /usr/bin/bash
set -x
START_DIR=$PWD

function miniDocker() {
    cd $START_DIR
    rm -f *.out
    gcc -Og -o miniDocker.out mini-docker.c
}

$@
