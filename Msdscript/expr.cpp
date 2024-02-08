
/**
 * \file  expr.cpp
 * \brief Implementation file for the Expr class and its subclasses.
 *
 * This file contains the implementation of the Expr class and its subclasses: Num, Add, Mult, and Var.
 * The Expr class represents an arithmetic expression, and its subclasses represent different types of expressions,
 * such as numbers, addition, multiplication, and variables.
 *
 * \author Rylie Byers
 * \date Created on January 22, 2024
 */

#include "expr.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

//==============Expr subclass================

/**
 * \brief Returns a string representation of the expression.
 * \param none
 * \return A string representing the expression.
 */


std::string Expr::to_string() const {
    std::stringstream st("");
    this->print(st);
    return st.str();
}

/**
 * \brief Prints the expression to the output stream.
 * \param os The output stream to print to.
 *
 */
void Expr::print(std::ostream& os) const {
    os << "Expr";
}

/**
 * \brief Pretty printsthe expression with varying parentheses.
 *
 * \param  os The output stream to print to.
 * \param prec_parent The precedence of the parent expression.
 *
 */
void Expr::pretty_print_at(std::ostream& os, precedence_t prec_parent) const {
    precedence_t prec_current = prec_none;
    
    if (dynamic_cast<const Add*>(this)) {
        prec_current = prec_add;
    } else if (dynamic_cast<const Mult*>(this)) {
        prec_current = prec_mult;
    }
    
    bool needs_parentheses = false;
    
    if (prec_current == prec_add) {
        needs_parentheses = (prec_parent >= prec_current);
    }
    else if(prec_current <= prec_none ){
        needs_parentheses = (prec_parent <= prec_current);
    }
    else if (prec_current == prec_mult) {
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

/**
 * \brief calls recursive method pretty_print_at
 *
 * \param  os The output stream to print to.
 *
 */
 void Expr::pretty_print(std::ostream& os) const {
    pretty_print_at(os, prec_none);
}

/**
 * \brief Returns a pretty string representation of the expression.
 * \param none
 * \return A string representing the expression.
 */
 std::string Expr::to_pretty_string() const {
    //std::stringstream ss("");
    std::stringstream ss;
  // this->pretty_print(ss);
    return ss.str();
}
//==============Num subclass================

/**
 * \brief Constructs a Num object with the specified value.
 *
 * \param val The value of the Num object.
 */
Num::Num(int val) : val(val) {}


/**
 * \brief Checks if the given expression equals this Num object.
 *
 * \param e The expression to compare with.
 * \return True if the expressions are equal, false otherwise.
 */
bool Num::equals(Expr* e) {
    Num* numPtr = dynamic_cast<Num*>(e);
    if (numPtr == nullptr) {
        return false;
    } else {
        return (val == numPtr->val);
    }
}


/**
 * \brief Evaluates the Num expression and returns its value.
 * \param none
 * \return The value of the Num expression.
 */
int Num::interp() const {
    return val;
}

/**
 * \brief Checks if the Num expression has a variable.
 * \param none
 * \return True if the Num expression has a variable, false otherwise.
 */
bool Num::has_variable() const {
    return false;
}

/**
 * \brief Substitutes a variable in the Num expression with a replacement expression.
 *
 * \param  var The variable to substitute.
 * \param replacement The expression to replace the variable with.
 * \return A new expression after substitution.
 */
Expr* Num::subst(const std::string& var, Expr* replacement) const {
    return new Num(val);
}

/**
 * \brief Clones the Num expression.
 *
 * \return A new copy of the Num expression.
 */
Expr* Num::clone() const {
    return new Num(val);
}

/**
 * \brief Prints the Num expression to the output stream.
 *
 * \param os The output stream to print to.
 */
void Num::print(std::ostream& os) const {
    os << std::to_string(val);
}

/**
 * \brief Returns a string representation of the Num expression.
 *
 * \return A string representing the Num expression.
 */
std::string Num::to_string() const {
    return std::to_string(val);
}

//==============Add subclass================


/**
 * \brief Constructs an Add expression with the specified left and right expressions.
 *
 * \param lhs The left expression.
 * \param rhs The right expression.
 */
Add::Add(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}


/**
 * \brief Checks if the given expression equals this Add expression.
 *
 * \param e The expression to compare with.
 * \return True if the expressions are equal, false otherwise.
 */
bool Add::equals(Expr* e) {
    Add* addPtr = dynamic_cast<Add*>(e);
    if (addPtr == nullptr) {
        return false;
    } else {
        return lhs->equals(addPtr->lhs) && rhs->equals(addPtr->rhs);
    }
}
/**
 * \brief Evaluates the Add expression and returns its value.
 *
 * \return The value of the Add expression.
 */
int Add::interp() const {
    return lhs->interp() + rhs->interp();
}

/**
 * \brief Checks if the Add expression has a variable.
 *
 * \return True if the Add expression has a variable, false otherwise.
 */
bool Add::has_variable() const {
    return lhs->has_variable() || rhs->has_variable();
}
/**
 * \brief Substitutes a variable in the Add expression with a replacement expression.
 *
 * \param var The variable to substitute.
 * \param replacement The expression to replace the variable with.
 * \return A new expression after substitution.
 */
Expr* Add::subst(const std::string& var, Expr* replacement) const {
    return new Add(lhs->subst(var, replacement), rhs->subst(var, replacement));
}
/**
 * \brief Clones the Add expression.
 *
 * \return A new copy of the Add expression.
 */
Expr* Add::clone() const {
    return new Add(lhs->clone(), rhs->clone());
}
/**
 * \brief Prints the Add expression to the output stream.
 *
 * \param os The output stream to print to.
 */
void Add::print(std::ostream& os) const  {
   // os << "(";
    lhs->print(os);
    os << " + ";
    rhs->print(os);
  //  os << ")";
}
/**
 * \brief Pretty prints the Add expression.
 *
 * \param os The output stream to print to.
 */
void Add::pretty_print(std::ostream& os) const{
    lhs->pretty_print_at(os, prec_add);
    os << " + ";
    rhs->pretty_print_at(os, prec_add);
}

/**
 * \brief Returns a pretty string representation of the Add expression.
 *
 * \return A string representing the Add expression.
 */
std::string Add::to_pretty_string() const  {
    std::stringstream ss;
    this->pretty_print(ss);
    return ss.str();
}

//==============Mult subclass================
/**
 * \brief Constructs a Mult expression with the specified left and right expressions.
 *
 * \param lhs The left expression.
 * \param rhs The right expression.
 */
Mult::Mult(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}

/**
 * \brief Checks if the given expression equals this Mult expression.
 *
 * \param e The expression to compare with.
 * \return True if the expressions are equal, false otherwise.
 */
bool Mult::equals(Expr* e) {
    Mult* multPtr = dynamic_cast<Mult*>(e);
    if (multPtr == nullptr) {
        return false;
    } else {
        return lhs->equals(multPtr->lhs) && rhs->equals(multPtr->rhs);
    }
}
/**
 * \brief Evaluates the Mult expression and returns its value.
 *
 * \return The value of the Mult expression.
 */
int Mult::interp() const {
    return lhs->interp() * rhs->interp();
}
/**
 * \brief Checks if the Mult expression has a variable.
 *
 * \return True if the Mult expression has a variable, false otherwise.
 */
bool Mult::has_variable() const {
    return lhs->has_variable() || rhs->has_variable();
}
/**
 * \brief Substitutes a variable in the Mult expression with a replacement expression.
 *
 * \param var The variable to substitute.
 * \param replacement The expression to replace the variable with.
 * \return A new expression after substitution.
 */
Expr* Mult::subst(const std::string& var, Expr* replacement) const {
    return new Mult(lhs->subst(var, replacement), rhs->subst(var, replacement));
}
/**
 * \brief Clones the Mult expression.
 *
 * \return A new copy of the Mult expression.
 */
Expr* Mult::clone() const {
    return new Mult(lhs->clone(), rhs->clone());
}

/**
 * \brief Prints the Mult expression to the output stream.
 *
 * \param os The output stream to print to.
 */

void Mult::print(std::ostream& os) const  {
  //  os << "(";
    lhs->print(os);
    os << " * ";
    rhs->print(os);
   // os << ")";
}
/**
 * \brief Pretty prints the Mult expression.
 *
 * \param os The output stream to print to.
 */
void Mult::pretty_print(std::ostream& os) const {
    lhs->pretty_print_at(os, prec_mult);
    os << " * ";
    rhs->pretty_print_at(os, prec_mult);
}
/**
 * \brief Returns a pretty string representation of the Mult expression.
 *
 * \return A string representing the Mult expression.
 */
std::string Mult::to_pretty_string() const  {
    std::stringstream ss;
    this->pretty_print(ss);
    return ss.str();
}

//==============Var subclass================

/**
 * \brief Constructs a Var expression with the specified variable name.
 *
 * \param varName The name of the variable.
 */
Var::Var(const std::string& varName) : varName(varName) {}
/**
 * \brief Checks if the given expression equals this Var expression.
 *
 * \param e The expression to compare with.
 * \return True if the expressions are equal, false otherwise.
 */
bool Var::equals(Expr* e) {
    Var* varPtr = dynamic_cast<Var*>(e);
    if (varPtr == nullptr) {
        return false;
    } else {
        return (varName == varPtr->varName);
    }
}
/**
 * \brief Evaluates the Var expression. Throws an exception as there's no value for the variable.
 *
 * \return This function throws a std::runtime_error.
 */
int Var::interp() const {
    throw std::runtime_error("no value for variable");
}
/**
 * \brief Checks if the Var expression has a variable.
 *
 * \return True if the Var expression has a variable, false otherwise.
 */
bool Var::has_variable() const {
    return true;
}

/**
 * \brief Substitutes a variable in the Var expression with a replacement expression.
 *
 * If the variable name matches the name of this Var expression, it returns a clone of the replacement expression.
 * Otherwise, it returns a new Var expression with the same name as this Var expression.
 *
 * \param var The variable to substitute.
 * \param replacement The expression to replace the variable with.
 * \return A new expression after substitution.
 */
Expr* Var::subst(const std::string& var, Expr* replacement) const {
    if (var == varName) {
        return replacement->clone();
    } else {
        return new Var(varName);
    }
}
/**
 * \brief Clones the Var expression.
 *
 * \return A new copy of the Var expression.
 */
Expr* Var::clone() const {
    return new Var(varName);
}
/**
 * \brief Prints the Var expression to the output stream.
 *
 * \param os The output stream to print to.
 */
void Var::print(std::ostream& os) const {
    os << varName;
}
