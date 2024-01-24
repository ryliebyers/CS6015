//
//  expr.h
//  HW2ExpressionClasses
//
//  Created by Rylie byers on 1/22/24.
//

#ifndef expr_h
#define expr_h
#pragma once
#include <string>



//Class for expressions
class Expr {
public:
    virtual bool equals(Expr *e) = 0;
};

//Subclass for number expressions
class Num : public Expr {
public:
    int val;
    Num(int val);

    bool equals(Expr *e);
};

//Subclass for addition expressions
class Add : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    Add(Expr *lhs, Expr *rhs);

    bool equals(Expr *e);
};

//Subclass for multiplication expressions
class Mult : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    Mult(Expr *lhs, Expr *rhs);

    bool equals(Expr *e);
};

//Subclass for variable expressions
class Var : public Expr {
public:
    std::string varName;
    Var( const std::string &varName);

    bool equals(Expr *e);
};



#endif /* expr_h */
