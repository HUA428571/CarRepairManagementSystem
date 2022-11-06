#pragma once

#ifndef HEAD
#define HEAD

#include <time.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
using namespace std;

#include <graphics.h>
#include <easyx.h>
#include <conio.h>
#include <mysql.h>

#include "MENU.h"
#include "Match.h"
#include "print.h"
#include "MENUchoose.h"
#include "Function.h"

#endif // !HEAD

extern MYSQL mysql;
extern int UserID;
// extern char UserName[46];
// extern int Role;

#ifndef STYLE
#define STYLE

#define tPRICE 150

#define FONT "黑体"
//注意！是BBGGRR不是RRGGBB！！！！！
#define COLOR_BG        0xF9F9F9
#define COLOR_WHITE     0xFFFFFF
#define COLOR_GREY_3    0xC7C7C7
#define COLOR_GREY_2    0x696969
#define COLOR_GREY_1    0x404040
#define COLOR_RED       0x303BFF
#define COLOR_BLUE      0xFF7A00
#define COLOR_GREEN     0x59C734
#define COLOR_ORANGE    0x0095FF
#define COLOR_PURPLE    0xDE52AF
#define COLOR_DEEP_BLUE 0xD65658
#define COLOR_YELLOW    0x00CCFF

#endif // !STYLE