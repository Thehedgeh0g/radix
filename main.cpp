#include <iostream>
#include <ranges>
#include <sstream>
#include <cstdlib>
#include <vector>

int CharToDigit(char c) {
    if (isdigit(c)) {
        return c - '0';
    } else if (isalpha(c)) {
        return std::toupper(c) - 'A' + 10;
    }
    return -1;
}

int StringToInt(const std::string& str, int base, bool &wasError) {
    int result = 0;
    for (char c: str) {
        int digit = CharToDigit(c);
        if (digit < 0 || digit >= base) {
            wasError = true;
            return 0;
        }
        result = result * base + digit;
    }
    return result;
}

std::string ConvertToBase(long long decimalNumber, int base) {
    if (decimalNumber == 0) {
        return "0";
    }

    std::vector<char> digits;
    while (decimalNumber > 0) {
        int remainder = decimalNumber % base;
        char digit = (remainder < 10) ? '0' + remainder : 'A' + (remainder - 10);
        digits.push_back(digit);
        decimalNumber /= base;
    }

    std::ostringstream result;
    for (char &digit: std::ranges::reverse_view(digits)) {
        result << digit;
    }

    return result.str();
}

std::string ConvertRadix(const std::string& number, int fromBase, int toBase, bool& wasError) {
    int decimalNumber;

    decimalNumber = StringToInt(number, fromBase, wasError);

    if (wasError) {
        std::cout << "Invalid value's source notation\n"
                  << "value's must be source notation - '" << fromBase << "' got\n";
        return "";
    }
    std::ostringstream result;
    result << ConvertToBase(decimalNumber, toBase);

    return result.str();
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Invalid argument count\n"
                  << "Usage: radix.exe <source notation> <destination notation> <value>\n";
        return EXIT_FAILURE;
    }

    bool wasError = false;

    int fromBase = StringToInt(argv[1], 10, wasError);
    if (wasError) {
        std::cout << "Invalid <source notation> type\n"
                  << "<source notation> must be decimal - '" << argv[1] << "' got\n";
        return EXIT_FAILURE;
    }

    int toBase = StringToInt(argv[2], 10, wasError);
    if (wasError) {
        std::cout << "Invalid <destination notation> type\n"
                  << "<destination notation> must be decimal - '" << argv[2] << "' got\n";
        return EXIT_FAILURE;
    }
    std::string number(argv[3]);
    if (fromBase < 2 || fromBase > 36 || toBase < 2 || toBase > 36) {
        std::cout << "Invalid base.\n"
                  << "Bases should be between 2 and 36.\n";
        return EXIT_FAILURE;
    }

    std::string result = ConvertRadix(number, fromBase, toBase, wasError);
    if (wasError) {
        return EXIT_FAILURE;
    }

    std::cout << "Converted number: " << result << std::endl;

    return EXIT_SUCCESS;
}
