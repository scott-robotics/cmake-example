#!/bin/bash

set -e

LIB_BUILD_DIR=$(pwd)/build-lib
APP_BUILD_DIR=$(pwd)/build-app
LIB_INSTALL_DIR=$(pwd)/install

rm -rf $LIB_BUILD_DIR ; mkdir -p $LIB_BUILD_DIR
rm -rf $APP_BUILD_DIR ; mkdir -p $APP_BUILD_DIR
rm -rf $LIB_INSTALL_DIR ; mkdir -p $LIB_INSTALL_DIR


# Build and install the library
pushd $LIB_BUILD_DIR

cmake ../mylib -DCMAKE_INSTALL_PREFIX=$LIB_INSTALL_DIR
make
make install

popd


# Build and install the app (dependent project)
pushd $APP_BUILD_DIR

cmake ../app -DCMAKE_INSTALL_PREFIX=$LIB_INSTALL_DIR -DCMAKE_PREFIX_PATH=$LIB_INSTALL_DIR
make

popd

# Check that the app can run!
$APP_BUILD_DIR/MyApp || echo "Errors occured!"
