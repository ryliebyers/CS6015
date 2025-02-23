#ifndef ENV_H
#define ENV_H
#include <QApplication>
#include "pointer.h"
#include "val.h"
#include "expr.h"
#include "val.h"
#include <memory>

class Env {
public:

    virtual PTR(Val) lookup(std::string find_name) = 0;
};

class emptyEnv : public Env {
    PTR(Val) lookup(std::string find_name) override;
};

class ExtendedEnv : public Env {
public:
    ExtendedEnv(std::string name, PTR(Val) val, PTR(Env) env) {
        this->val = val;
        this->name = name;
        this->env = env;
    }
    std::string name;
    PTR(Val) val;
    PTR(Env) env;
    PTR(Val) lookup(std::string find_name)override;

};



#endif //ENV_H
