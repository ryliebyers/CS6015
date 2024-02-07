//
//  main.cpp
//  HW2ExpressionClasses
//
//  Created by Rylie byers on 1/24/24.
//

#include <stdio.h>
#define CATCH_CONFIG_RUNNER
#include "expr.h"
#include "catch.h"
#include <iostream>
#include <cstdlib>
#include "cmdline.hpp"




int main(int argc, char* argv[]) {
    
    use_arguments(argc, argv);
        
    // Create the expression
       Expr* expression = new Mult(
           new Add(new Num(3), new Num(5)),
           new Mult(new Num(6), new Num(1))
       );

       // Print the pretty string representation of the expression
       std::cout << expression->to_pretty_string() << std::endl;

       // Clean up memory
       delete expression;
    
    if(use_arguments(argc, argv) == true){
        Catch::Session().run() ;
        exit(1);
    }
    
    return 0;
}

