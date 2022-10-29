#pragma once


int C_InputBox(char* Input, int Limit, int x, int y, const char* Default);

int C_InputBox(char* Input, int Limit, int x, int y, int Lsize, int Hsize, const char* Default);

int CR_InputBox(char* Input, int Limit, int x, int y, int Lsize, int Hsize, const char* Default);

int CHR_InputBox(char* Input, int Limit, int x, int y, int Lsize, int Hsize, const char* Default);

int CheckID(char* input_UserName, char* input_PassWord);

int calaulate_part_total_price(int OrderID);
