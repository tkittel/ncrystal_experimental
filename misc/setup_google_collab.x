#!/bin/bash
set +x
set -e
NCRYSTAL_SRC="$( cd -P "$( dirname "${BASH_SOURCE[0]}" )"/.. && pwd )"
BASEDIR="$PWD/ncrystal"
NCRYSTAL_BLD="$BASEDIR/ncrystal-bld"
NCRYSTAL_INST="$BASEDIR/ncrystal-install"

CMAKEVERSION=3.23.1
echo "====> Getting modern CMake"
wget https://github.com/Kitware/CMake/releases/download/v$CMAKEVERSION/cmake-$CMAKEVERSION-linux-x86_64.sh
sh ./cmake-$CMAKEVERSION-linux-x86_64.sh --prefix=/usr/local/ --exclude-subdir
which cmake
cmake --version
echo "====> Configuring NCrystal"
mkdir -p $NCRYSTAL_BLD
mkdir -p $NCRYSTAL_INST
cd $NCRYSTAL_BLD
cmake -DCMAKE_INSTALL_PREFIX="$NCRYSTAL_INST" "$NCRYSTAL_SRC" "$@"
echo "====> Building NCrystal"
make -j4
echo "====> Installing NCrystal"
make -j4 install
echo "====> Testing NCrystal"
$NCRYSTAL_INST/bin/ncrystal-config --summary
