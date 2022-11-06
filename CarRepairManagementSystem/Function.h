#pragma once
// --------------------------------------------------
// Copyright 2022 HuaCL
// 辅助函数
// --------------------------------------------------

//输入框（输入内容，长度限制，输入框横轴位置，输入框纵轴位置，默认显示的内容）
int C_InputBox(char* Input, int Limit, int x, int y, const char* Default);
//输入框（输入内容，长度限制，输入框横轴位置，输入框纵轴位置，输入框总长度，字体高度，默认显示的内容）
int C_InputBox(char* Input, int Limit, int x, int y, int Lsize, int Hsize, const char* Default);
//输入框_登录界面（输入内容，长度限制，输入框横轴位置，输入框纵轴位置，输入框总长度，字体高度，默认显示的内容）
int InputBox_show(char* Input, int Limit, int x, int y, int Lsize, int Hsize, const char* Default);
//输入框_不显示字符_登录界面（输入内容，长度限制，输入框横轴位置，输入框纵轴位置，输入框总长度，字体高度，默认显示的内容）
int InputBox_no_show(char* Input, int Limit, int x, int y, int Lsize, int Hsize, const char* Default);
//检查ID信息
int CheckID(char* input_UserName, char* input_PassWord);
//计算配件总价
int calaulate_part_total_price(int OrderID);
