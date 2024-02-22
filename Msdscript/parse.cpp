
#include "parse.hpp"


Expr *parse_str(const std::string& input) {
    // Check if the input consists only of whitespace characters and parentheses
    if (input.find_first_not_of(" \t\n()") == std::string::npos) {
        // Return a default expression, for example, a zero expression
        throw std::runtime_error("invalid input");
    }

    // Check if '_' is followed by 'in' or 'let'
    size_t underscorePos = input.find('_');
    if (underscorePos != std::string::npos) {
        size_t nextPos = underscorePos + 1;
        size_t nextWordPos = input.find_first_not_of(" \t", nextPos);
        if (nextWordPos != std::string::npos) {
            std::string nextWord = input.substr(nextWordPos, 3); // Check the next 3 characters
            if (nextWord != "in" && nextWord != "let") {
                throw std::runtime_error("invalid input: 'in' or 'let' expected after '_'");
            }
        } else {
            throw std::runtime_error("invalid input: 'in' or 'let' expected after '_'");
        }
    }

    // Proceed with parsing
    std::istringstream iss(input);
    
    if (iss.peek() == EOF) {
        throw std::runtime_error("empty input");
    }
    
    return parse_expr(iss);
}




Expr *parse_num(std::istream &inn) {
    int n = 0;
    bool negative = false;
    
    if (inn.peek() == '-') {
        negative = true;
        consume (inn, '-');
        
    }

    while (1) {
        int c = inn.peek();
        if (isdigit(c))
        {
            consume(inn, c);
            n = n*10 + (c - '0');
        }
        else
            break;
    }
    
    if (negative)
        n = -n;
  
    return new Num(n);
}


Expr *parse_expr(std::istream& in) {
    skip_whitespace(in);
    Expr *e = parse_multicand(in); // Parse the left multicand
    skip_whitespace(in);
    int c = in.peek();
    
    // Check for addition or multiplication operator
    while (c == '+' || c == '*') {
        if (c == '+') {
            consume(in, '+'); // Consume the '+'
            Expr *rhs = parse_multicand(in); // Parse the right multicand
            e = new Add(e, rhs); // Create an addition expression
        } else if (c == '*') {
            consume(in, '*'); // Consume the '*'
            Expr *rhs = parse_multicand(in); // Parse the right multicand
            e = new Mult(e, rhs); // Create a multiplication expression
        }
        skip_whitespace(in);
        c = in.peek();
    }
    return e;
}




Expr *parse_addend(std::istream &in) {
    Expr *e = parse_multicand(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c == '*') {
        consume(in, '*');
        Expr *rhs = parse_expr(in);
        return new Mult(e, rhs);
    } else {
        return e;
    }
}



Expr *parse_multicand(std::istream &in) {
    skip_whitespace(in);
    int c = in.peek();

    // Check if the expression is enclosed in parentheses
    if (c == '(') {
        consume(in, '(');
        Expr *e = parse_expr(in);
        skip_whitespace(in);
        c = in.get();
        if (c != ')') {
            throw std::runtime_error("missing close parenthesis");
        }
        return e;
    }

    // If not enclosed in parentheses, parse as a number or variable
    if (c == '-') {
        consume(in, '-');
        if (isdigit(in.peek())) {
            return new Num(-parse_num(in)->interp());
        } else {
            throw std::runtime_error("invalid input");
        }
    } else if (isdigit(c)) {
        return parse_num(in);
    } else if (isalpha(c)) {
        // Parse variable
        return new Var(parse_variable(in));
    } 
    else if (c == '_') {
           // Check if it's the beginning of a let expression
           std::string keyword;
           in >> keyword;
           if (keyword == "_let") {
               return parse_let(in);
           } else {
               // If not a let expression, put back the characters read
               in.putback('_');
               in.putback(keyword.back());
               return parse_expr(in);
           }
       }
    else {
        throw std::runtime_error("invalid input");
    }
}




std::string parse_variable(std::istream& in) {
    std::string varName;
    skip_whitespace(in);

    // Read characters until a non-alphanumeric character is encountered
    int c;
    while ((c = in.peek()) != EOF && isalnum(c)|| c == '_') {
        varName += in.get();
    }
    return varName;
}

Expr *parse_let(std::istream& in) {
    // Assuming the let expression starts with the keyword "let"
    consume(in, '_');
    consume(in, 'l');
    consume(in, 'e');
    consume(in, 't');

    // Parse variable name
    std::string varName = parse_variable(in);

    // Consume '='
    consume(in, '=');

    // Parse body expression
    Expr *body = parse_expr(in);

    // Consume '_in'
    consume(in, '_');
    consume(in, 'i');
    consume(in, 'n');

    // Parse rhs expression
    Expr *rhs = parse_expr(in);

    return new Let(varName, body, rhs);
}


static void consume(std::istream &in, int expect) {
    int c = in.get();
    if (c!=expect) {
        throw std::runtime_error("consume mismatch");
    }
}

void skip_whitespace(std::istream &in) {
  while (1) {
    int c = in.peek();
    if (!isspace(c))
      break;
    consume(in, c);
      }
}


