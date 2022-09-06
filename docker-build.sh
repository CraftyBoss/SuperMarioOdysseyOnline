#!/bin/bash

ISEMU=${1:-0}

export DOCKER_BUILDKIT=1
docker  build  .  -t smoo-client-build
docker  run  --rm       \
  -u $(id -u):$(id -g)  \
  -v "/$PWD/":/app/     \
  -e ISEMU=${ISEMU}     \
  smoo-client-build     \
;
docker  rmi  smoo-client-build

cp  -r  ./romfs/  ./starlight_patch_*/atmosphere/contents/0100000000010000/.
