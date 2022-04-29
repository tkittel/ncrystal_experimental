#!/bin/bash
set +x
cd /content
CMAKEVERSION=$CMAKEVERSION
echo "Getting modern CMake"
wget https://github.com/Kitware/CMake/releases/download/v$CMAKEVERSION/cmake-$CMAKEVERSION-linux-x86_64.sh
./cmake-$CMAKEVERSION-linux-x86_64.sh --prefix=/usr/local/ --exclude-subdir
which cmake
cmake --version
