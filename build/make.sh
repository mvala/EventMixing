#!/bin/bash

if [ ! -f Makefile ];then
  cmake ../
fi

make $*
