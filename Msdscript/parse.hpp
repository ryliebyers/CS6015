
#ifndef PARSE_HPP
#define PARSE_HPP

#include <iostream>
#include <cctype>
#include <sstream>
#include "expr.h"
#include "catch.h"
#include "expr.h"
#include "cmdline.hpp"
#pragma once




Expr *parse_str(const std::string& input);
Expr *parse_expr(std::istream &in);
Expr *parse_addend(std::istream &in);
Expr *parse_multicand(std::istream &in);
Expr *parse_num(std::istream &in);
Expr *parse_let(std::istream& in);
std::string parse_variable(std::istream& in);
static void consume(std::istream &in, int expect);
void skip_whitespace(std::istream &in);

#endif // PARSE_HPP
