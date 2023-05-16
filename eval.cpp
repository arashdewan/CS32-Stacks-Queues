//
//  eval.cpp
//  CS32 HW2
//
//  Created by Arash Dewan on 5/3/23.
//

#include <iostream>
#include <string>
#include <stack>
#include <cassert>

using namespace std;

int evaluate(string infix, string& postfix, bool& result);
bool infix_check_convert(string& infix, string& postfix);


  // Evaluates a boolean expression
  //   If infix is a syntactically valid infix boolean expression,
  //   then set postfix to the postfix form of that expression, set
  //   result to the value of the expression, and return zero. If
  //   infix is not a syntactically valid expression, return 1; in
  //   that case, postfix may or may not be changed, but result must
  //   be unchanged.

int evaluate(string infix, string& postfix, bool& result)
{
    //check if infix is a valid operation and convert
    if (!infix_check_convert(infix, postfix))
        return 1;
    //evaluate expression
    stack<bool> opd_stack;
    for (int i = 0; i < postfix.size(); i++)
    {
        if(postfix[i] == 'T' || postfix[i] == 'F')
        {
            switch (postfix[i])
            {
                case 'T':
                    opd_stack.push(true);
                    break;
                case 'F':
                    opd_stack.push(false);
                    break;
            }
        }
        else if (postfix[i] == '&' || postfix[i] == '^')
        {
            bool temp_op1 = opd_stack.top();
            opd_stack.pop();
            bool temp_op2 = opd_stack.top();
            opd_stack.pop();
            switch (postfix[i])
            {
                case '&':
                    opd_stack.push(temp_op1 & temp_op2);
                    break;
                case '^':
                    opd_stack.push(temp_op1 ^ temp_op2);
                    break;
            }
        }
        else if (postfix[i] == '!')
        {
            bool temp_op = opd_stack.top();
            opd_stack.pop();
            opd_stack.push(!temp_op);
        }
        else
        {
            return 1;
        }
    }
    result = opd_stack.top();
    return 0;
}

bool infix_check_convert(string& infix, string& postfix)
{

    //checks for spaces
    string clean_infix = "";
    postfix = "";
    for (int i = 0; i < infix.size(); i++)
    {
        if(infix[i] == ' ')
        {
            continue;
        }
        clean_infix += infix[i];
    }
    infix = clean_infix;
    
    if(infix == "")
    {
        return false;
    }
    //checks for incorrect symbol placing
    stack<char> opd_stack;
    switch (infix[0])
    {
        case ')':
        case '^':
        case '&':
            return false;
        default:
            break;
    }
    switch (infix[infix.size() - 1])
    {
        case '(':
        case '^':
        case '&':
        case '!':
            return false;
        default:
            break;
    }

    //check for invalid operations
    for (int i = 0; i<infix.size(); i++)
    {
        switch(infix[i])
        {
            case 'T':
            case 'F':
                if (i + 1 < infix.size())
                {
                 switch (infix[i+1])
                 {
                    case 'T':
                    case 'F':
                    case '(':
                    case '!':
                         return false;
                    default:
                         break;
                 }
                }
                postfix += infix[i];
                break;
                
            case '!':
            case '(':
                if (i + 1 < infix.size())
                {
                    switch (infix[i+1])
                    {
                        case ')':
                        case '&':
                        case '^':
                            return false;
                        default:
                            break;
                    }
                }
                opd_stack.push(infix[i]);
                break;
    
            case ')':
                if (i + 1 < infix.size())
                {
                    switch(infix[i+1])
                    {
                        case 'T':
                        case 'F':
                        case '(':
                            return false;
                        default:
                            break;
                    }
                }
                while(!opd_stack.empty() && opd_stack.top() != '(')
                {
                    postfix += opd_stack.top();
                    opd_stack.pop();
                }
                if(opd_stack.empty())
                {
                    return false;
                }
                opd_stack.pop();
                break;
            case '&':
            case '^':
                if (i + 1 < infix.size())
                {
                    switch (infix[i+1])
                    {
                        case '&':
                        case '^':
                        case ')':
                            return false;
                        default:
                            break;
                    }
                }
                while (!opd_stack.empty() && opd_stack.top() != '(' &&
                       opd_stack.top() <= infix[i])
                {
                    postfix += opd_stack.top();
                    opd_stack.pop();
                }
                opd_stack.push(infix[i]);
                break;
            default:
                return false;
        }
    }
    while(!opd_stack.empty())
    {
        if(opd_stack.top() == '(' || opd_stack.top() == ')')
        {
            return false;
        }
        postfix += opd_stack.top();
        opd_stack.pop();
    }
    return true;
}

//int main()
//{
//    string pf;
//    bool answer;
//    assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
//    assert(evaluate("T^", pf, answer) == 1);
//    assert(evaluate("F F", pf, answer) == 1);
//    assert(evaluate("TF", pf, answer) == 1);
//    assert(evaluate("()", pf, answer) == 1);
//    assert(evaluate("()T", pf, answer) == 1);
//    assert(evaluate("T(F^T)", pf, answer) == 1);
//    assert(evaluate("T(&T)", pf, answer) == 1);
//    assert(evaluate("(T&(F^F)", pf, answer) == 1);
//    assert(evaluate("T|F", pf, answer) == 1);
//    assert(evaluate("", pf, answer) == 1);
//    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
//                            &&  pf == "FF!TF&&^"  &&  !answer);
//    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
//    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
//    cout << "Passed all tests" << endl;
//    return 0;
//}

