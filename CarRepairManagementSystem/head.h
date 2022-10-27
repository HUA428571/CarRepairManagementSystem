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

#include "RepairMENU.h"
#include "Match.h"
#include "print.h"
#include "MENUchoose.h"

#endif // !HEAD

//#ifndef STRUCT
//#define STRUCT
//
//MYSQL mysql;
//
//#endif // !STRUCT

extern MYSQL mysql;
extern int UserID;
extern char UserName[46];
extern int Role;

//extern MYSQL_RES* res; //查询结果集
//extern MYSQL_ROW row;  //记录结构体


#ifndef STYLE
#define STYLE

#define FONT "黑体"
#define COLOR_BG	 0xF9F9F9
#define COLOR_WHITE	 0xFFFFFF
#define COLOR_GREY_3 0xC7C7C7
#define COLOR_GREY_2 0x696969
#define COLOR_GREY_1 0x404040
//#define COLOR_RED 0xFF3B30
//#define COLOR_BLUE 0x007AFF
//#define COLOR_GREEN 0x34C759
//#define COLOR_ORANGE 0xFF9500
//注意！是BBGGRR不是RRGGBB！！！！！
#define COLOR_RED	 0x303BFF
#define COLOR_BLUE	 0xFF7A00
#define COLOR_GREEN  0x59C734
#define COLOR_ORANGE 0x0095FF
#define COLOR_PURPLE 0xDE52AF
#define COLOR_DEEP_BLUE 0xD65658
#define COLOR_YELLOW 0x00CCFF

#endif // !STYLE