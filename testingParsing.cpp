// uses shunting yard algorithm
// https://en.wikipedia.org/wiki/Shunting-yard_algorithm

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cctype>
#include <cassert>

using namespace std;

// a single parsed token: either a number or a binary operator
struct Token {
	bool isNumber;
	int value; // valid when isNumber is true
	char op;   // valid when isNumber is false
};

// returns operator precedence (higher binds tighter); 0 for non-operators
int precedence(char op) {
	if (op == '+' || op == '-') return 1;
	if (op == '*') return 2;
	return 0;
}

// applies a binary operator to two operands, writing the result to out;
// returns false for an unsupported operator
bool applyOperator(int a, int b, char op, int &out) {
	switch (op) {
		case '+': out = a + b; return true;
		case '-': out = a - b; return true;
		case '*': out = a * b; return true;
	}
	return false;
}

// tokenizes and evaluates an integer arithmetic equation using the
// shunting-yard algorithm (supports +, -, * with standard precedence and
// left-associativity). Returns true and writes the value to result on
// success; returns false on malformed input or an unsupported character.
bool parseEquation(string equation, int &result) {
	// --- shunting-yard: build the RPN output queue ---
	queue<Token> output;
	vector<char> operators; // operator stack
	int i = 0;
	int n = (int)equation.length();
	bool expectOperand = true; // operand and operator must alternate
	while (i < n) {
		char c = equation[i];
		if (isspace((unsigned char)c)) { i++; continue; }
		if (isdigit((unsigned char)c)) {
			int num = 0;
			while (i < n && isdigit((unsigned char)equation[i])) {
				num = num * 10 + (equation[i] - '0');
				i++;
			}
			output.push({true, num, 0});
			expectOperand = false;
			continue;
		}
		if (c == '+' || c == '-' || c == '*') {
			if (expectOperand) return false; // operator with no preceding operand
			// pop operators of higher-or-equal precedence (left-associative)
			while (!operators.empty() && precedence(operators.back()) >= precedence(c)) {
				output.push({false, 0, operators.back()});
				operators.pop_back();
			}
			operators.push_back(c);
			expectOperand = true;
			i++;
			continue;
		}
		return false; // unsupported character
	}
	if (expectOperand) return false; // empty input or trailing operator
	while (!operators.empty()) {
		output.push({false, 0, operators.back()});
		operators.pop_back();
	}

	// --- evaluate the RPN output queue ---
	vector<int> values;
	while (!output.empty()) {
		Token t = output.front();
		output.pop();
		if (t.isNumber) {
			values.push_back(t.value);
		} else {
			if (values.size() < 2) return false; // malformed expression
			int b = values.back(); values.pop_back();
			int a = values.back(); values.pop_back();
			int r;
			if (!applyOperator(a, b, t.op, r)) return false;
			values.push_back(r);
		}
	}
	if (values.size() != 1) return false;
	result = values.back();
	return true;
}

// runs expected/actual checks against parseEquation; aborts on any mismatch
void runSelfTest() {
	int result = 0;

	// valid expressions
	assert(parseEquation("2+2", result) && result == 4);
	assert(parseEquation("42", result) && result == 42);          // bare number
	assert(parseEquation("10-3", result) && result == 7);
	assert(parseEquation("2*3*4", result) && result == 24);
	assert(parseEquation("1+2+3", result) && result == 6);
	assert(parseEquation("2+3*4", result) && result == 14);       // precedence
	assert(parseEquation("2*3+4", result) && result == 10);       // precedence
	assert(parseEquation("7-2-1", result) && result == 4);        // left-associative
	assert(parseEquation(" 5 + 6 ", result) && result == 11);     // whitespace tolerated

	// malformed input / unsupported characters
	assert(!parseEquation("", result));      // empty
	assert(!parseEquation("2+", result));    // trailing operator
	assert(!parseEquation("+2", result));    // leading operator
	assert(!parseEquation("2#3", result));   // unsupported character
	assert(!parseEquation("2 3", result));   // two operands, no operator

	cout << "All parser self-tests passed.\n";
}

int main() {
	runSelfTest();

	cout << "Enter equation to parse:\n";
	string equation;
	getline(cin, equation);
	cout << "The equation entered is: '" << equation << "'\n";
	int answer = 0;
	bool success = parseEquation(equation, answer);
	if (success) {
		cout << "Answer: " << answer << "\n";
	}
	else {
		cout << "There was an error.\n";
	}
}
