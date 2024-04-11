#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <graphics.h>
#include <filesystem>

enum //button index
{
    //menu
    COMPRESS = 0,
    DECOMPRESS,
    MORE_INFO,
    TEST,

    //global
    STOP,
    BACK,
    DONE,

    //explorer
    SELECT,
    MKDIR,
    FOPEN,
    DELETE,

    //algorithm
    HUF,
    LZW,
};
