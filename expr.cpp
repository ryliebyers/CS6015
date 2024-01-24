//
//  expr.cpp
//  HW2ExpressionClasses
//
//  Created by Rylie byers on 1/22/24.
//
#include "expr.h"
#include <iostream>
#include "expr.h"


Num::Num(int val) {
    this->val = val;
}

bool Num::equals(Expr *e) {
    Num *numPtr = dynamic_cast<Num *>(e);
    if (numPtr == nullptr) {
        return false;
    } else {
        return (val == numPtr->val);
    }
}

Add::Add(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Add::equals(Expr *e) {
    Add *addPtr = dynamic_cast<Add *>(e);
    if (addPtr == nullptr) {
        return false;
    } else {
        return lhs->equals(addPtr->lhs) && rhs->equals(addPtr->rhs);
    }
}

Mult::Mult(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Mult::equals(Expr *e) {
    Mult *multPtr = dynamic_cast<Mult *>(e);
    if (multPtr == nullptr) {
        return false;
    } else {
        return lhs->equals(multPtr->lhs) && rhs->equals(multPtr->rhs);
    }
}

Var::Var( const std::string &varName) : varName(varName) {
}

bool Var::equals(Expr *e) {
    Var *varPtr = dynamic_cast<Var *>(e);
    if (varPtr == nullptr) {
        return false;
    } else {
        return (varName == varPtr->varName);
    }
}
