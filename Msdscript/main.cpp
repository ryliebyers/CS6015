/*
* mainpage MSDScript
* author Rylie Byers
* date 01-24-2024
*/

#include "expr.h"
#include "catch.h"
#include "cmdline.hpp"
#include "parse.hpp"



int main(int argc, char* argv[]) {
    run_mode_t mode = use_arguments(argc, argv);
    if (mode != do_nothing) {
        Expr *e = parse_expr(std::cin);
        switch (mode) {
            case do_nothing:
                break;
            case do_interp:
                std::cout << e->interp() << "\n";
                break;
            case do_print:
                e->print(std::cout);
                std::cout << "\n";
                break;
            case do_pretty_print:
                std::cout << e->to_pretty_string() << "\n";
                break;
        }
        delete e; // Clean up dynamically allocated memory
    }
    return 0;
}

