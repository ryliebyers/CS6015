//
//  tests.cpp
//  HW2ExpressionClasses
//
//  Created by Rylie byers on 1/23/24.
//

#include <stdio.h>
#include "catch.h"
#include "expr.h"

    TEST_CASE("Expression tests") {
        //Number expression tests
        CHECK((new Num(1))->equals(new Num(1)) == true);
        CHECK((new Num(-1))->equals(new Num(1)) == false);
        
        
        // Addition expression tests
        CHECK((new Add(new Num(1), new Num(2)))->equals(new Add(new Num(1), new Num(2))) == true);
        CHECK((new Add(new Num(1), new Num(2)))->equals(new Add(new Num(2), new Num(1))) == false);
        
        
        //Multiplication expression tests
        CHECK((new Mult(new Num(1), new Num(2)))->equals(new Mult(new Num(1), new Num(2))) == true);
        CHECK((new Mult(new Num(2), new Num(1)))->equals(new Mult(new Num(1), new Num(2))) == false);
        
        
        //Variable expression tests
        CHECK((new Var("x"))->equals(new Var("x")) == true);
        CHECK((new Var("x"))->equals(new Var("y")) == false);
        CHECK((new Num(1))->equals(new Var("x")) == false);
        
        
        //Mixed expression tests
        CHECK((new Add(new Num(2), new Mult(new Var("x"), new Num(3))))
              ->equals(new Add(new Num(2), new Mult(new Var("x"), new Num(3)))) == true);
        
        CHECK((new Add(new Num(2), new Mult(new Var("x"), new Num(3))))
              ->equals(new Add(new Num(2), new Mult(new Var("y"), new Num(3)))) == false);
        
    }

