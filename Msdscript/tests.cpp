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
#include "parse.hpp"

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
      //Need to add some
        
        

}
/* Some ideas for parse tests, probably not enough. Also, you may need
   to adjust these tests, and there may even be mistakes here. */

TEST_CASE("parse") {
  CHECK_THROWS_WITH( parse_str("()"), "invalid input" );
  
  CHECK( parse_str("(1)")->equals(new Num(1)) );
  CHECK( parse_str("(((1)))")->equals(new Num(1)) );
  
  CHECK_THROWS_WITH( parse_str("(1"), "missing close parenthesis" );
  
  CHECK( parse_str("1")->equals(new Num(1)) );
  CHECK( parse_str("10")->equals(new Num(10)) );
  CHECK( parse_str("-3")->equals(new Num(-3)) );
  CHECK( parse_str("  \n 5  ")->equals(new Num(5)) );
  CHECK_THROWS_WITH( parse_str("-"), "invalid input" );

  // This was some temporary debugging code:
  //  std::istringstream in("-");
  //  parse_num(in)->print(std::cout); std::cout << "\n";
  
  CHECK_THROWS_WITH( parse_str(" -   5  "), "invalid input" );
  
  CHECK( parse_str("x")->equals(new Var("x")) );
  CHECK( parse_str("xyz")->equals(new Var("xyz")) );
  CHECK( parse_str("xYz")->equals(new Var("xYz")) );
  CHECK_THROWS_WITH( parse_str("x_z"), "invalid input: 'in' or 'let' expected after '_'" );
  
  CHECK( parse_str("x + y")->equals(new Add(new Var("x"), new Var("y"))) );

  CHECK( parse_str("x * y")->equals(new Mult(new Var("x"), new Var("y"))) );

  CHECK( parse_str("z * x + y")
        ->equals(new Add(new Mult(new Var("z"), new Var("x")),
                         new Var("y"))) );
  
  CHECK( parse_str("z * (x + y)")
        ->equals(new Mult(new Var("z"),
                          new Add(new Var("x"), new Var("y"))) ));

}
