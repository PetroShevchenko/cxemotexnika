#!/bin/bash

RED=`tput setaf 1`
GREEN=`tput setaf 2`
YELLOW=`tput setaf 3`
BLUE=`tput setaf 4`
GRAY=`tput setaf 8`
RESET=`tput sgr0`

PROMPT_COLOUR=$GRAY
INFO_COLOUR=$GREEN
WARNING_COLOUR=$YELLOW
ERROR_COLOUR=$RED

PROMPT="$PROMPT_COLOUR[$0] :$RESET"

print_done()
{
    echo "$PROMPT ${INFO_COLOUR}done${RESET}"
}

create_project()
{
    pico_project.py --gui
}

build_project()
{
    mkdir -p build && cd build
    cmake .. && make -j$(nproc) && print_done
}

clean_project()
{
    rm -rf build && print_done
}

upgrade_firmware()
{
    echo "${WARNING_COLOUR}DO NOT FORGET TO HOLD DOWN THE BOOTSEL BUTTON BEFORE POWERING ON THE BOARD!!!${RESET}"
    cp $(find ./build -name *.uf2) /media/$USER/RPI-RP2 && print_done
}

run_openocd()
{
    openocd -f interface/picoprobe.cfg -f target/rp2040.cfg -s tcl
}

run_minicom()
{
    if dmesg | grep ttyACM0; then
        minicom -D /dev/ttyACM0 -b 115200
    else
        echo "$PROMPT ${ERROR_COLOUR}There is no a plugged picoprobe device${RESET}"
    fi
}

run_tree()
{
    tree -L 2 && print_done
}

usage()
{
    echo "$PROMPT ${INFO_COLOUR}use \"${0} create\" to launch pico_project.py in GUI mode${RESET}"
    echo "$PROMPT ${INFO_COLOUR}use \"${0} build\" to compile the project${RESET}"
    echo "$PROMPT ${INFO_COLOUR}use \"${0} clean\" to remove temporary files${RESET}"
    echo "$PROMPT ${INFO_COLOUR}use \"${0} upgrade\" to copy the firmware to the device${RESET}"
    echo "$PROMPT ${INFO_COLOUR}use \"${0} debug\" to launch openocd${RESET}"
    echo "$PROMPT ${INFO_COLOUR}use \"${0} monitor\" to launch minicom${RESET}"
    echo "$PROMPT ${INFO_COLOUR}use \"${0} show\" to show a tree of current directory${RESET}"
}

if [ "$1" = "create" ];then
    create_project
elif [ "$1" = "build" ];then
    build_project
elif [ "$1" = "clean" ];then
    clean_project
elif [ "$1" = "upgrade" ];then
    upgrade_firmware
elif [ "$1" = "debug" ];then
    run_openocd
elif [ "$1" = "monitor" ];then
    run_minicom
elif [ "$1" = "show" ];then
    run_tree
else
    usage
fi