#pragma once
// --------------------------------------------------
// Copyright 2022 HuaCL
// 匹配函数，用于数字状态和输出文字的匹配与计算
// --------------------------------------------------

//匹配订单状态（状态代码，输出字符串）
void MatchStatus(int status, char* STATUS);
//匹配人员类型（人员代码，输出字符串）
void MatchRole(int role, char* ROLE);
//匹配人员类型 并调整相应的突出色（人员代码，输出字符串）
void MatchRole_with_color(int role, char* ROLE);
//匹配负荷MySQL标准的日期
void MatchDate(char* buffer_Date);
