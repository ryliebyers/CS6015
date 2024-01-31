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
       
        
                
        
        //Interp tests
        CHECK( (new Mult(new Num(3), new Num(2)))
                ->interp()==6 );
        CHECK( (new Mult(new Num(-3), new Num(-2)))
                ->interp()==6 );
        CHECK( (new Mult(new Num(-3), new Num(2)))
                ->interp()==-6 );
        CHECK( (new Mult(new Num(0), new Num(2)))
                ->interp()==0 );
        
        CHECK( (new Add(new Add(new Num(10), new Num(15)),new Add(new Num(20),new Num(20))))
                ->interp()==65);
        
        //has_variable tests
        CHECK( (new Add(new Var("x"), new Num(1)))->has_variable() == true );
        
        CHECK( (new Mult(new Num(2), new Num(1)))->has_variable() == false );
        
        
        CHECK( (new Add(new Var("!@;"), new Num(1)))->has_variable() == true );

        CHECK( (new Add(new Num(0), new Num(1)))->has_variable() == false );
        
        
        CHECK( (new Add(new Var("X"), new Num(1)))->has_variable() == true );

        
        //Subst tests
        CHECK( (new Add(new Var("x"), new Num(7)))
               ->subst("x", new Var("y"))
               ->equals(new Add(new Var("y"), new Num(7))) );
        
        CHECK( (new Var("x"))
               ->subst("x", new Add(new Var("y"),new Num(7)))
               ->equals(new Add(new Var("y"),new Num(7))) );
        
        CHECK( (new Add(new Var("x"), new Num(7)))
               ->subst("x", new Var("xy2!"))
               ->equals(new Add(new Var("xy2!"), new Num(7))) );
        
        CHECK( (new Add(new Var("Y"), new Var("Y")))
               ->subst("Y", new Var("x"))
               ->equals(new Add(new Var("x"), new Var("x"))) );
        
        CHECK( (new Add(new Var("X"), new Var("Y")))
               ->subst("X", new Var("1"))
               ->equals(new Add(new Var("1"), new Var("Y"))) );
    }

