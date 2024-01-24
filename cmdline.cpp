//
//  cmdline.cpp
//  HW2ExpressionClasses
//
//  Created by Rylie byers on 1/24/24.
//

#include "cmdline.hpp"

#include <stdio.h>
#include "expr.h"
#include "catch.h"
#include <iostream>
#include <cstdlib>



bool use_arguments(int argc, char* argv[]) {
    bool runTestsFlag = false;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--help") == 0) {
            std::cout << "Help text describing allowed arguments.\n";
            std::cout << "--help : get help\n";
            std::cout << "--test : run tests\n";
            exit(0);
        } else if (strcmp(argv[i], "--test") == 0) {
            if (runTestsFlag) {
                std::cerr << "Error: --test already seen.\n";
                exit(1);
            } else {
                runTestsFlag = true;
                
            }
        } else {
            std::cerr << "Error: Unknown argument - " << argv[i] << "\n";
            exit(1);
        }
    }

    return runTestsFlag;
}

