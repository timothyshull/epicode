// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <numeric>
#include <stack>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::stack;
using std::string;
using std::vector;

bool directed_expression_synthesis(const vector<int>&, int, int, int,
                                   vector<int>*, vector<char>*);

int remaining_int(const vector<int>&, int);

int evaluate(const vector<int>&, const vector<char>&);

// @include
bool expression_synthesis(const vector<int>& digits, int target)
{
    vector<char> operators;
    vector<int> operands;
    return directed_expression_synthesis(digits, target, 0, 0, &operands,
                                         &operators);
}

bool directed_expression_synthesis(const vector<int>& digits, int target,
                                   int current_term, int offset,
                                   vector<int>* operands,
                                   vector<char>* operators)
{
    current_term = current_term * 10 + digits[offset];
    if (offset == digits.size() - 1) {
        operands->emplace_back(current_term);
        if (evaluate(*operands, *operators) == target) {  // Found a match.
            // @exclude
            auto operand_it = operands->cbegin();
            cout << *operand_it++;
            for (char oper : *operators) {
                cout << ' ' << oper << ' ' << *operand_it++;
            }
            cout << " = " << target << "\n";
            // @include
            return true;
        }
        operands->pop_back();
        return false;
    }

    // No operator.
    if (directed_expression_synthesis(digits, target, current_term, offset + 1,
                                      operands, operators)) {
        return true;
    }
    // Tries multiplication operator '*'.
    operands->emplace_back(current_term), operators->emplace_back('*');
    if (directed_expression_synthesis(digits, target, 0, offset + 1, operands,
                                      operators)) {
        return true;
    }
    operands->pop_back(), operators->pop_back();
    // Tries addition operator '+'.
    operands->emplace_back(current_term);
    // First check feasibility of plus operator.
    if (target - evaluate(*operands, *operators) <=
        remaining_int(digits, offset + 1)) {
        operators->emplace_back('+');
        if (directed_expression_synthesis(digits, target, 0, offset + 1, operands,
                                          operators)) {
            return true;
        }
        operators->pop_back();
    }
    operands->pop_back();
    return false;
}

// Calculates the int represented by digits[idx : digits.size() - 1].
int remaining_int(const vector<int>& digits, int idx)
{
    int val = 0;
    for (int i = idx; i < digits.size(); ++i) {
        val = val * 10 + digits[i];
    }
    return val;
}

int evaluate(const vector<int>& operands, const vector<char>& operators)
{
    stack<int> intermediate_operands;
    int operand_idx = 0;
    intermediate_operands.push(operands[operand_idx++]);
    // evaluates '*' first.
    for (char oper : operators) {
        if (oper == '*') {
            int product = intermediate_operands.top() * operands[operand_idx++];
            intermediate_operands.pop();
            intermediate_operands.push(product);
        } else {  // oper == '+'.
            intermediate_operands.push(operands[operand_idx++]);
        }
    }

    // evaluates '+' second.
    int sum = 0;
    while (!intermediate_operands.empty()) {
        sum += intermediate_operands.top();
        intermediate_operands.pop();
    }
    return sum;
}
// @exclude

int main(int argc, char* argv[])
{
    vector<int> A = {2, 3, 4};
    int k = 4;
    assert(!expression_synthesis(A, k));
    A = {1, 2, 3, 4};
    k = 11;
    assert(expression_synthesis(A, k));
    A = {1, 2, 3, 2, 5, 3, 7, 8, 5, 9};
    k = 995;
    assert(expression_synthesis(A, k));
    A = {5, 2, 3, 4, 1};
    k = 20;
    assert(expression_synthesis(A, k));
    A = {1, 1, 2, 3};
    k = 124;
    assert(expression_synthesis(A, k));
    return 0;
}
