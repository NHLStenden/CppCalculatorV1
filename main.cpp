#include <iostream>
#include <regex>
#include <string>
#include <iomanip>

/**
 * Perform a calculation based on the parameters supplied.
 * @param operand1 the left operand
 * @param op the operation to perform. must be '+', '-', '*' or '/' for addition, subtraction, multiplication or division
 * @param operand2 the right operand
 * @return the calculated value
 */
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
    /** The user input .\n You should input decimal numbers using a dot (.) and not a comma (,) ! */
    std::string input;

    /** A regular expression to parse the input. \n
     * Decimal numbers are only detected when using a dot (.) and not a comma (,)
     * */
    std::regex expression_regex("\\s*(-?\\d*\\.?\\d+)\\s*([+\\-*/])\\s*(-?\\d*\\.?\\d+)\\s*");

    /** holds the matches found by parsing the input using the regular expression
     * @see expression_regex */
    std::smatch match;

    /** a boolean to indicate the the user has entered and EOF or EOT char (typical CTRL+D or CTRL+Z)
     * Must be set to TRUE if the input has ended
     * */
    bool eofDetected = false;

    while (! eofDetected) {
        std::getline(std::cin, input);
        eofDetected = std::cin.eof();
        if (!eofDetected) {
            if (std::regex_match(input, match, expression_regex)) {

                /** holds the first operand found in the input, as parsed using the regular expression .@refitem input @refitem expression_regex */
                double operand1 = std::stod(match[1]);
                /** holds the operator extracted from the input. @refitem input @refitem expression_regex */
                char op = match[2].str()[0];
                /** holds the second operand found in the input, as parsed using the regular expression */
                double operand2 = std::stod(match[3]);

                try {
                    /** result holds the result of the calculation as performed by the function calculate()
                     * @see calculate() */
                    double result = calculate(operand1, op, operand2);
                    std::cout << std::fixed << std::setprecision(3) << operand1 << " " << op << " " << operand2 << " = " << result << std::endl;
                } catch (const std::runtime_error &e) {
                    std::cerr << e.what() << std::endl;
                }
            } else {
                std::cerr << "Invalid input format. Use the format: number operator number (e.g., 5.5 + 3.2)"
                          << std::endl;
            }
        }
    }

    return 0;
}