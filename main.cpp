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
        
    if(use_arguments(argc, argv) == true){
        Catch::Session().run() ;
        exit(1);
    }
    return 0;
}

