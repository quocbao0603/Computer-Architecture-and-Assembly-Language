#pragma once
#include "QInt.h"
#include "QFloat.h"

//Tinh toan QInt vs cac toan tu 1 ngoi
string process_IntUnaryOp(string a ,int oper, int inp_type);
//Tinh toan QInt vs cac toan tu 2 ngoi
string process_IntBinaryOp(string a, string b, int oper, int inp_type);
//Tinh toan QFloat vs cac toan tu 1 ngoi
string process_FloUnaryOp(string a, int oper, int inp_type);
//Tinh toan QFloat vs cac toan tu 2 ngoi
string process_FloBinaryOp(string a, string b, int oper, int inp_type);