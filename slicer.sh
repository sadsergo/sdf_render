#!/bin/bash

../kernel_slicer/cmake-build-release/kslicer "./render/render.cpp" \
  -mainClass Renderer -stdlibfolder "../kernel_slicer/TINYSTL" \ 
  -pattern rtv -reorderLoops YX -Iexternal/LiteMath ignore -shaderCC GLSL -DKERNEL_SLICER -v