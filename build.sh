#!/bin/bash

set -xe

declare -a dynamic_option=()

if [ "$1" = "clean" ];then
    rm musializer
    exit
fi


for arg in "$@"
do
    case "$arg" in 
        "--with-debug")
            dynamic_option+=("-g")
            ;;
        "-Wno-unused-variable")
            dynamic_option+=("-Wno-unused-variable")
            ;;
        "-Wno-unused-parameter")
            dynamic_option+=("-Wno-unused-parameter")
            ;;
        *)
            ;;
    esac
done

# declare -a static_options=("-Wall" "-Wextra")

# CFLAGS="-Wall -Wextra  `pkg-config --cflags raylib` -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -DPLATEFORM_DESKTOP"    
CFLAGS="-Wall -Wextra  `pkg-config --cflags raylib`"
LIBS="`pkg-config --libs raylib` -lglfw -lm -ldl -lpthread -ldl -lrt -lX11 -DPLATEFORM_DESKTOP" 


gcc $CFLAGS -o musializer main.c  "${dynamic_option[@]}" $LIBS