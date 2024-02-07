//
//  expr.cpp
//  HW2ExpressionClasses
//
//  Created by Rylie byers on 1/22/24.
//
#include "expr.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

std::string Expr::to_string() const {
    std::stringstream st("");
    this->print(st);
    return st.str();
}
void Expr::print(std::ostream& os) const {
    os << "Expr";
}


void Expr::pretty_print_at(std::ostream& os, precedence_t prec_parent) const {
    precedence_t prec_current = prec_none;
    
    if (dynamic_cast<const Add*>(this)) {
        prec_current = prec_add;
    } else if (dynamic_cast<const Mult*>(this)) {
        prec_current = prec_mult;
    }
    
    bool needs_parentheses = false;
    
    if (prec_current == prec_add) {
        // For addition, add parentheses if parent precedence is lower than current precedence
        needs_parentheses = (prec_parent >= prec_current);
    }
    else if(prec_current <= prec_none ){
        needs_parentheses = (prec_parent <= prec_current);
    }
    else if (prec_current == prec_mult) {
        // For multiplication, add parentheses if parent precedence is lower or equal to current precedence
        needs_parentheses = (prec_parent <= prec_current);
    }
    
    if (needs_parentheses) {
        os << "(";
    }
    
    print(os);
    
    if (needs_parentheses) {
        os << ")";
    }
}








// Implement the pretty_print method for Expr class
 void Expr::pretty_print(std::ostream& os) const {
    pretty_print_at(os, prec_none);
}
 std::string Expr::to_pretty_string() const {
    //std::stringstream ss("");
    std::stringstream ss;
  // this->pretty_print(ss);
    return ss.str();
}
//==============Number================


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
void Num::print(std::ostream& os) const {
    os << std::to_string(val);
}
std::string Num::to_string() const {
    return std::to_string(val);
}

//==============Addition================

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

void Add::print(std::ostream& os) const  {
   // os << "(";
    lhs->print(os);
    os << " + ";
    rhs->print(os);
  //  os << ")";
}

void Add::pretty_print(std::ostream& os) const{
    lhs->pretty_print_at(os, prec_add);
    os << " + ";
    rhs->pretty_print_at(os, prec_add);
}

std::string Add::to_pretty_string() const  {
    std::stringstream ss;
    this->pretty_print(ss);
    return ss.str();
}

//==============Multiplication================

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
//void Mult::print(std::ostream& os) const {
//    os << "(" << lhs->to_string() << " * " << rhs->to_string() << ")";
//}
void Mult::print(std::ostream& os) const  {
  //  os << "(";
    lhs->print(os);
    os << " * ";
    rhs->print(os);
   // os << ")";
}

void Mult::pretty_print(std::ostream& os) const {
    lhs->pretty_print_at(os, prec_mult);
    os << " * ";
    rhs->pretty_print_at(os, prec_mult);
}
std::string Mult::to_pretty_string() const  {
    std::stringstream ss;
    this->pretty_print(ss);
    return ss.str();
}

//==============Variable================
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
void Var::print(std::ostream& os) const {
    os << varName;
}
