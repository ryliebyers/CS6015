/**
* \file expr.h
* \brief brief Defines classes for mathematical expressions.
*
* There is the expr class. Add, mult, and var subclasses. All of the expr calls get overridden by Add, mult, and var subclasses
*/

#ifndef expr_h
#define expr_h
#pragma once
#include <string>
#include <iostream>

typedef enum {
    prec_none, //0
    prec_add, //1
    prec_mult //1
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
    std::string to_string() const;
    virtual void print(std::ostream& os) const;
    virtual void pretty_print(std::ostream& os, precedence_t prec) const;
    virtual std::string to_pretty_string() const;

        

};

//=========Subclass for number expressions=========
class Num : public Expr {
public:
    int val;//!< represents a number

    Num(int val);

    bool equals(Expr* e) override;
    int interp() const override;
    bool has_variable() const override;
    Expr* subst(const std::string& var, Expr* replacement) const override;
    Expr* clone() const override;
    std::string to_string() const;
    void print(std::ostream& os) const override;
    void pretty_print(std::ostream& os, precedence_t prec) const override;
};

//========Subclass for addition expressions========
class Add : public Expr {
public:
    Expr* lhs; //!< Represents left hand side
    Expr* rhs; //!< Represents right hand side

    Add(Expr* lhs, Expr* rhs);

    bool equals(Expr* e) override;
    int interp() const override;
    bool has_variable() const override;
    Expr* subst(const std::string& var, Expr* replacement) const override;
    Expr* clone() const override;
    void print(std::ostream& os) const override;

    void pretty_print(std::ostream& os, precedence_t prec) const override;
    
    std::string to_pretty_string() const override;
  
};

//========Subclass for multiplication expressions========
class Mult : public Expr {
public:
    Expr* lhs;//!< Represents left hand side
    Expr* rhs;//!< Represents right hand side

    Mult(Expr* lhs, Expr* rhs);

    bool equals(Expr* e) override;
    int interp() const override;
    bool has_variable() const override;
    Expr* subst(const std::string& var, Expr* replacement) const override;
    Expr* clone() const override;
      void print(std::ostream& os) const override;
       void pretty_print(std::ostream& os, precedence_t prec) const override;

    std::string to_pretty_string() const override;
 
};

//========Subclass for variable expressions========

class Var : public Expr {
public:
    std::string varName; //!< Represents a varible

    Var(const std::string& varName);

    bool equals(Expr* e) override;
    int interp() const override;
    bool has_variable() const override;
    Expr* subst(const std::string& var, Expr* replacement) const override;
    Expr* clone() const override;
    void print(std::ostream& os) const override;
     void pretty_print(std::ostream& os, precedence_t prec) const override;
};
//========Subclass for Let expressions========
class Let : public Expr {
public:
    std::string varName; //!< Represents a variable
        Expr* lhs; //!< Represents the left-hand side expression
        Expr* body; //!< Represents the body expression
        Expr* rhs; //!< Represents the right-hand side expression
    bool let_needs_parentheses;
//        Let(const std::string& var, Expr* lhs_expr, Expr* body_expr, Expr* rhs_expr);

   Let(const std::string& var, Expr* lhs_expr, Expr* body_expr, Expr* rhs_expr);

    
    bool equals(Expr* e) override;
        int interp() const override;
        bool has_variable() const override;
    Expr* subst(const std::string& var, Expr* replacement) const override;
    Expr* clone() const override;
    std::string to_pretty_string() const override;
    void print(std::ostream& os) const override;
    void pretty_print(std::ostream& os, precedence_t prec) const override;
   
    
};
#endif /* expr_h */
