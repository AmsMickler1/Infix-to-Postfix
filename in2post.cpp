#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <stdexcept>
#include "stack.h"

using namespace std;
using namespace cop4530;

typedef struct {
    Stack<string> operators;
    string infix;
    string postfix;
    double eval;
    bool simplify = true;
    bool error1 = false;            // operand error
    bool error2 = false;            // parenthetical error
    bool error3 = false;            // operator error
}Equation;

void convert(Equation & eq);
void evaluate(Equation & eq);

int main() {
    string temp;
    cout << "Enter infix expression (\"exit\" to quit): ";
    while (getline(cin,temp)) {
        Equation eq;
        if (temp == "exit")
            break;
        eq.infix = temp;                                                        // grabs whole line
        convert(eq);
        if (eq.error1)
            cout << "Error: Missing operand." << endl;
        if (eq.error2)
            cout << "Error: Mismatching parentheses." << endl;
        if (eq.error3)
            cout << "Error: Missing operator." << endl;
        if (!eq.error1 && !eq.error2 && !eq.error3) {
            cout << "Postfix expression: " << eq.postfix << endl;               // cout postfix expression
            evaluate(eq);
            cout << "Postfix evaluation: " << eq.postfix << " = ";
            if (eq.simplify)
                cout << eq.eval << endl;
            else
                cout << eq.postfix << endl;
            }

        std::cout << "Enter infix expression (\"exit\" to quit): ";
    }
}

void convert(Equation & eq) {
    bool syntax = false;                                                        // for tracking to catch syntax errors
    string psf;
    string inf = eq.infix;
    istringstream stream (inf);
    stream >> inf;
    while (stream) {
        if (inf == "(") {
            eq.operators.push(inf);
            syntax = false;                                                     // last character in expression was NOT an operand
        }
        // if inf is ")" pop operators until top = "(" and then pop it away
        else if (inf == ")") {
            if (!syntax) {
                eq.error1 = true;
                eq.simplify = false;
                if (eq.operators.top() == "(")
                    eq.operators.pop();
                }
            else {
                while (eq.operators.top() != "(") {
                    if (eq.operators.empty()) {
                        eq.error2 = true;
                        eq.simplify = false;
                        break;
                    }
                    psf.append(eq.operators.top());
                    psf.append(" ");
                    eq.operators.pop();
                }
                if (!eq.operators.empty()) {
                    eq.operators.pop();                                         // pop & discard "(" from operator stack
                }
            }
            syntax = true;                                                      // ")" followed by an operator is syntactically correct
        }
        else if (inf == "+" || inf == "-" || inf == "*" || inf == "/") {
            if (!syntax) {
                eq.operators.push(inf);
                eq.error1 = true;
                eq.simplify = false;
            }
            else {
                if (eq.operators.empty() || eq.operators.top() == "(") {
                    eq.operators.push(inf);
                }
                // top has higher precedence, pop it to psf then push inf to stack
                else if ((eq.operators.top() == "*" || eq.operators.top() == "/") && (inf == "+" || inf == "-")) {
                    psf.append(eq.operators.top());
                    psf.append(" ");
                    eq.operators.pop();
                    // if new tops are lower precedence, print them too
                    while (eq.operators.top() == "+" || eq.operators.top() == "-") {
                        psf.append(eq.operators.top());
                        psf.append(" ");
                        eq.operators.pop();
                    }
                    eq.operators.push(inf);
                }
                // inf has higher precedence, push inf to stack
                else if ((eq.operators.top() == "+" || eq.operators.top() == "-") && (inf == "*" || inf == "/")) {
                    //cout << "pushing " << inf << " to stack" << endl;
                    eq.operators.push(inf);
                }
                // else operators have same precedence
                // pop & print previous operator then push new operator to stack
                else {
                    psf.append(eq.operators.top());
                    psf.append(" ");
                    eq.operators.pop();
                    eq.operators.push(inf);
                }
                syntax = false;                                                 // last character in expression was NOT an operand
            }
        }   // end of operators IF
        else {
            if (syntax) {
                eq.error3 = true;
                eq.simplify = false;
            }
            psf.append(inf);
            psf.append(" ");
            syntax = true;                                                      // last character in expression was an operand
        }   // end of operand IF
        stream >> inf;
        if (stream.fail())
            cout << endl;
    }   // end of input while loop

    while (!eq.operators.empty()) {
        if (eq.operators.top() == "(") {
            eq.error2 = true;
            eq.simplify = false;
            eq.operators.pop();
            if (eq.operators.empty())
            break;
        }
        psf.append(eq.operators.top());
        psf.append(" ");
        eq.operators.pop();
    }
    if (!syntax)
        eq.error1 = true;
    eq.postfix = psf;
}   // end of convert function

void evaluate(Equation & eq) {
    Stack<double> result;
    double temp1;
    double temp2;
    string psf = eq.postfix;
    istringstream stream (psf);
    stream >> psf;

    while (eq.simplify && stream) {
        if (psf == "+" || psf == "-" || psf == "*" || psf == "/") {
            if (result.empty())
                cout << "Oops, something went wrong." << endl;
            temp2 = result.top();
            result.pop();
            temp1 = result.top();
            result.pop();
            if (psf == "+")
                temp1 += temp2;
            else if (psf == "-")
                temp1 -= temp2;
            else if (psf == "*")
                temp1 *= temp2;
            else if (psf == "/")
                temp1 /= temp2;
            result.push(temp1);
        }
        else {
            try {
                result.push(stod(psf));
            } catch (const std::invalid_argument) {
                eq.simplify = false;
            }
        }
        stream >> psf;
    }
    if (eq.simplify)
        eq.eval = result.top();
}
