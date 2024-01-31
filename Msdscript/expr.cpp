//
//  expr.cpp
//  HW2ExpressionClasses
//
//  Created by Rylie byers on 1/22/24.
//
#include "expr.h"
#include <iostream>
#include <stdexcept>



Num::Num(int val) : val(val) {}

bool Num::equals(Expr* e) {
    Num* numPtr = dynamic_cast<Num*>(e);
    if (numPtr == nullptr) {
        return false;
    } else {
        return (val == numPtr->val);
    }
}

int Num::interp() const {
    return val;
}

bool Num::has_variable() const {
    return false;
}

Expr* Num::subst(const std::string& var, Expr* replacement) const {
    return new Num(val);
}

Expr* Num::clone() const {
    return new Num(val);
}


Add::Add(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}

bool Add::equals(Expr* e) {
    Add* addPtr = dynamic_cast<Add*>(e);
    if (addPtr == nullptr) {
        return false;
    } else {
        return lhs->equals(addPtr->lhs) && rhs->equals(addPtr->rhs);
    }
}

int Add::interp() const {
    return lhs->interp() + rhs->interp();
}

bool Add::has_variable() const {
    return lhs->has_variable() || rhs->has_variable();
}

Expr* Add::subst(const std::string& var, Expr* replacement) const {
    return new Add(lhs->subst(var, replacement), rhs->subst(var, replacement));
}

Expr* Add::clone() const {
    return new Add(lhs->clone(), rhs->clone());
}


Mult::Mult(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}

bool Mult::equals(Expr* e) {
    Mult* multPtr = dynamic_cast<Mult*>(e);
    if (multPtr == nullptr) {
        return false;
    } else {
        return lhs->equals(multPtr->lhs) && rhs->equals(multPtr->rhs);
    }
}

int Mult::interp() const {
    return lhs->interp() * rhs->interp();
}

bool Mult::has_variable() const {
    return lhs->has_variable() || rhs->has_variable();
}

Expr* Mult::subst(const std::string& var, Expr* replacement) const {
    return new Mult(lhs->subst(var, replacement), rhs->subst(var, replacement));
}

Expr* Mult::clone() const {
    return new Mult(lhs->clone(), rhs->clone());
}




Var::Var(const std::string& varName) : varName(varName) {}

bool Var::equals(Expr* e) {
    Var* varPtr = dynamic_cast<Var*>(e);
    if (varPtr == nullptr) {
        return false;
    } else {
        return (varName == varPtr->varName);
    }
}

int Var::interp() const {
    throw std::runtime_error("no value for variable");
}

bool Var::has_variable() const {
    return true;
}

Expr* Var::subst(const std::string& var, Expr* replacement) const {
    if (var == varName) {
        return replacement->clone();
    } else {
        return new Var(varName);
    }
}

Expr* Var::clone() const {
    return new Var(varName);
}
