/**
* \file tests.cpp
* \Has tests to test methods in expr.cpp
*
*
* Theres tests for var, num, add, and mult subclasses.
* \author Rylie Byers
*/

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
        
        //Print tests
        
        CHECK( (new Num(10))->to_string() == "10" );
        CHECK( (new Num(0))->to_string() == "0" );
        CHECK( (new Num(-1))->to_string() == "-1" );
        
        CHECK ( (new Mult(new Num(1), new Add(new Num(2), new Num(3))))->to_pretty_string() ==  "1 * (2 + 3)" );
        CHECK ( (new Mult(new Mult(new Num(8), new Num(1)), new Var("y")))->to_pretty_string() ==  "(8 * 1) * y" );
        CHECK ( (new Mult(new Add(new Num(3), new Num(5)), new Mult(new Num(6), new Num(1))))->to_pretty_string() ==  "(3 + 5) * 6 * 1" );
        CHECK ( (new Mult(new Mult(new Num(7), new Num(7)), new Add(new Num(9), new Num(2))) )->to_pretty_string() ==  "(7 * 7) * (9 + 2)" );
        CHECK ( (new Mult(new Mult(new Var("x"), new Num(7)), new Add(new Num(9), new Num(2))) )->to_pretty_string() ==  "(x * 7) * (9 + 2)" );
        CHECK( (new Mult(new Mult(new Mult(new Num(7), new Num(7)), new Add(new Num(9), new Num(2))), new Add(new Num(9), new Num(2))))->to_pretty_string() == "((7 * 7) * (9 + 2)) * (9 + 2)" );

      //Let tests
      
        //equals
        // Create two Let expressions with the same structure
            Let* let7 = new Let("x", new Var("y"), new Var("z"), new Var("w"));
            Let* let6 = new Let("x", new Var("y"), new Var("z"), new Var("w"));

            // Check if they are equal
            CHECK(let7->equals(let6) == true);

            // Clean up
            delete let7;
            delete let6;
        
        //interp
        // Create a Let expression: let x = 5 in x + 2
        Let* letExpr1 = new Let("x", new Num(5), new Add(new Var("x"), new Num(2)), new Num(5));



            // Expected result: 5 + 2 = 7
            CHECK(letExpr1->interp() == 7);

            // Clean up
            delete letExpr1;
        
        //has_variable
        
        // do a has varible one should return false ans one true rhs and lhs
        // Create a Let expression with variables in lhs and body
            Let* let3 = new Let("x", new Var("y"), new Var("z"), new Var("w"));
            // Create a Let expression without variables
            Let* let4 = new Let("x", new Num(5), new Num(10), new Num(15));

            // Check if has_variable returns true for let1 and false for let2
            CHECK(let3->has_variable() == true);
            CHECK(let4->has_variable() == false);

            // Clean up
            delete let3;
            delete let4;
        
        //subst
//        // Create a Let expression
         Let* let2 = new Let("x", new Var("y"), new Var("x"), new Var("w"));
         // Substitute variable "y" with a Num expression
         Expr* substExpr = let2->subst("y", new Num(5));

         // Check if the substitution is correct
         CHECK(substExpr->to_string() == "(_let x = 5 _in w)");

         // Clean up
         delete let2;
         delete substExpr;
       
        
        //clone
        // Create a Let expression
            Let* let1 = new Let("x", new Var("y"), new Var("z"), new Var("w"));
            // Clone the Let expression
            Expr* clonedLet = let1->clone();

            // Check if the cloned Let expression is equal to the original one
            CHECK(clonedLet->equals(let1) == true);

            // Clean up
            delete let1;
            delete clonedLet;
        
        //pretty print
        Let* letExprstring = new Let("x", new Num(5),new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2)), new Var("x")),new Var("x")),new Var("x"));


        std::string expected_output_string = "_let x = 5\n_in  (_let y = 3\n      _in  y + 2) + x";

            CHECK(letExprstring->to_pretty_string() == expected_output_string);

            delete letExprstring;
        
        
    }

