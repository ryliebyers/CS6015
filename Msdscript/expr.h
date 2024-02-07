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
#include <iostream>
// Define the precedence enum
//typedef enum {
//  prec_none = 0,
//  prec_add = 1,
//  prec_mult = 2
//} precedence_t;
typedef enum {
    prec_none,
    prec_add,
    prec_mult
} precedence_t;

//=========Class for expressions=========
class Expr {

public:
    virtual bool equals(Expr *e) = 0;
    virtual int interp() const = 0;
    virtual bool has_variable() const = 0;
    virtual Expr* subst(const std::string& var, Expr* replacement) const = 0;
    virtual Expr* clone() const = 0;
    virtual ~Expr() {}
    //TODO CHECK TO STRING
    std::string to_string() const;
    virtual void print(std::ostream& os) const;
    virtual void pretty_print_at(std::ostream& os, precedence_t prec_current) const;
    virtual void pretty_print(std::ostream& os) const;
    
    virtual std::string to_pretty_string() const;
    
//    virtual void to_pretty_print(std::ostream& os) const =0;
    

};

//=========Subclass for number expressions=========
class Num : public Expr {
public:
    int val;

    Num(int val);

    bool equals(Expr* e) override;
    int interp() const override;
    bool has_variable() const override;
    Expr* subst(const std::string& var, Expr* replacement) const override;
    Expr* clone() const override;
    std::string to_string() const;
    void print(std::ostream& os) const override;
//    void to_pretty_print(std::ostream& os) const override;
};

//========Subclass for addition expressions========
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
//    std::string to_string() const;
    void print(std::ostream& os) const override;
    void pretty_print(std::ostream& os) const override;
    
    std::string to_pretty_string() const override;
//    void to_pretty_print(std::ostream& os) const override;
};

//========Subclass for multiplication expressions========
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
//    std::string to_string() const;
      void print(std::ostream& os) const override;
       void pretty_print(std::ostream& os) const override;
    std::string to_pretty_string() const override;
//    void to_pretty_print(std::ostream& os) const override;
};

//========Subclass for variable expressions========

class Var : public Expr {
public:
    std::string varName;

    Var(const std::string& varName);

    bool equals(Expr* e) override;
    int interp() const override;
    bool has_variable() const override;
    Expr* subst(const std::string& var, Expr* replacement) const override;
    Expr* clone() const override;
   
//    std::string to_string() const;
    void print(std::ostream& os) const override;
//    std::string to_pretty_string() const override;
//    void to_pretty_print(std::ostream& os) const override;
};


#endif /* expr_h */
