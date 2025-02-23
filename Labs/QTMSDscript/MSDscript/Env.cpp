#include "Env.h"





    PTR(Val) emptyEnv::lookup(std::string find_name) {
        throw std::runtime_error("free variable: "
                                 + find_name);
    }



    PTR(Val) ExtendedEnv::lookup(std::string find_name) {
        if (find_name == name)
            return val;
        else
            return env->lookup(find_name);
    }


