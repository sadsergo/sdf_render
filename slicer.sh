#!/bin/bash

start_dir=$PWD
echo "start_dir: $start_dir"

cd $1

$2 $start_dir/render/render.cpp \
  -mainClass Renderer -stdlibfolder $PWD/TINYSTL \ 
  -pattern rtv \
  -reorderLoops YX \
  -I$PWD/TINYSTL ignore  \ 
  -I$start_dir/external/LiteMath ignore  \
  -shaderCC GLSL -DKERNEL_SLICER -v

cd $start_dir