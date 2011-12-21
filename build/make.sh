#!/bin/bash

if [ ! -f Makefile ];then
  cmake ../ $USER_CMAKE_EXTRA_OPTIONS
fi

nice -n 15 make $*
