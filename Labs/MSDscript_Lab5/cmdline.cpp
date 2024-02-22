/**
* \file cmdline.cpp
* \Checks user inputs
*
*
* If user inserts --test all tests run, If they enter --help lists all calls. And returns error if the correct call isnt entered.
* \author Rylie Byers
*/

#include "cmdline.hpp"

#include <stdio.h>
#include "expr.h"
#include "catch.h"
#include <iostream>
#include <cstdlib>


/**
* \brief Parses command-line arguments to determine if tests should be run.
* \param argc The number of command-line arguments
* \param argv The array of command-line arguments.
* \return  bool True if the "--test" flag is present, indicating that tests should be run; false otherwise
*/

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

