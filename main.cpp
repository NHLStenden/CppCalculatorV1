#include <iostream>
#include <regex>
#include <string>

double calculate(double operand1, char op, double operand2) {
    switch (op) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/':
            if (operand2 == 0) {
                throw std::runtime_error("Error: Division by zero is not allowed.");
            }
        return operand1 / operand2;
        default:
            throw std::runtime_error("Error: Unknown operator.");
    }
}

int main() {
    std::string input;
    std::regex expression_regex("\\s*(-?\\d*\\.?\\d+)\\s*([+\\-*/])\\s*(-?\\d*\\.?\\d+)\\s*");
    std::smatch match;

    std::cout << "Enter an expression (e.g., 5.5 + 3.2) or press Ctrl+D to exit: " << std::endl;

    while (std::getline(std::cin, input)) {
        if (std::regex_match(input, match, expression_regex)) {
            double operand1 = std::stod(match[1]);
            char op = match[2].str()[0];
            double operand2 = std::stod(match[3]);

            try {
                double result = calculate(operand1, op, operand2);
                std::cout << operand1 << " " << op << " " << operand2 << " = " << result << std::endl;
            } catch (const std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
            }
        } else {
            std::cerr << "Invalid input format. Use the format: number operator number (e.g., 5.5 + 3.2)" << std::endl;
        }
        std::cout << "Enter another expression or press Ctrl+D to exit: " << std::endl;
    }

    std::cout << "Goodbye!" << std::endl;
    return 0;
}