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
    virtual int interp() const = 0;
        virtual bool has_variable() const = 0;
        virtual Expr* subst(const std::string& var, Expr* replacement) const = 0;
        virtual Expr* clone() const = 0;
        virtual ~Expr() {}
};

//Subclass for number expressions
class Num : public Expr {
public:
    int val;

    Num(int val);

    bool equals(Expr* e) override;
    int interp() const override;
    bool has_variable() const override;
    Expr* subst(const std::string& var, Expr* replacement) const override;
    Expr* clone() const override;
};

//Subclass for addition expressions
class Add : public Expr {
public:
    Expr* lhs;
    Expr* rhs;

    Add(Expr* lhs, Expr* rhs);

    bool equals(Expr* e) override;
    int interp() const override;
    bool has_variable() const override;
    Expr* subst(const std::string& var, Expr* replacement) const override;
    Expr* clone() const override;
};

//Subclass for multiplication expressions
class Mult : public Expr {
public:
    Expr* lhs;
    Expr* rhs;

    Mult(Expr* lhs, Expr* rhs);

    bool equals(Expr* e) override;
    int interp() const override;
    bool has_variable() const override;
    Expr* subst(const std::string& var, Expr* replacement) const override;
    Expr* clone() const override;
};

//Subclass for variable expressions

class Var : public Expr {
public:
    std::string varName;

    Var(const std::string& varName);

    bool equals(Expr* e) override;
    int interp() const override;
    bool has_variable() const override;
    Expr* subst(const std::string& var, Expr* replacement) const override;
    Expr* clone() const override;
};


#endif /* expr_h */
