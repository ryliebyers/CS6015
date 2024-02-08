**
* \mainpage MSDScript
* \author Rylie Byers
* \date 01-24-2024
*/

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

