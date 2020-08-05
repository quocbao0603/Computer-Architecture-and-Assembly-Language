#pragma once
#include "QInt.h"
#include "QFloat.h"

string process_IntUnaryOp(string a ,int oper, int inp_type);
string process_IntBinaryOp(string a, string b, int oper, int inp_type);
string process_FloUnaryOp(string a, int oper);
string process_FloBinaryOp(string a, string b, int oper, int inp_type);