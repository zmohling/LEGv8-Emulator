#!/bin/bash

set -e

### Set up name and directory variables ###

PROJECT_NAME="LEGv8-Emulator"
SCRIPT_DIR="$(dirname $0)"

cd $SCRIPT_DIR/.. 

ROOT_DIR="$(pwd)" 

### Copy directory, remove unrelated files, and make tarball ###

cp -r "$ROOT_DIR" "${ROOT_DIR}_copy"

mv "${ROOT_DIR}_copy" "${ROOT_DIR}/${PROJECT_NAME}"

cd "${ROOT_DIR}/${PROJECT_NAME}"

make clean > /dev/null
rm -rf .git/ .gitignore

cd ..

tar -cvf "${PROJECT_NAME}.tar" "${PROJECT_NAME}"
gzip "${PROJECT_NAME}.tar"

### Clean up ###

rm -rf "${PROJECT_NAME}"
echo "Tarball created at ${ROOT_DIR}/${PROJECT_NAME}.tar.gx"
