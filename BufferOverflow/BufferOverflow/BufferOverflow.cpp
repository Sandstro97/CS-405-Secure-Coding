#include <iomanip>
#include <iostream>

int main()
{
    std::cout << "Buffer Overflow Example" << std::endl;

    // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
    //  even though it is a constant and the compiler buffer overflow checks are on.
    //  You need to modify this method to prevent buffer overflow without changing the account_order
    //  variable, and its position in the declaration. It must always be directly before the variable used for input.

    const std::string account_number = "CharlieBrown42";
    char user_input[20];
    std::cout << "Enter a value: ";
    //std::cin >> user_input; - EDIT: This code was unsafe
    // Using getline we can limit the amount of input using one line of code and use cin.fail() to detect if a user typed more than the 20 char limit!
    std::cin.getline(user_input, 20);
    if (std::cin.fail()) {
        std::cout << "Detected a potential overflow! The input has been limited to 20 characters!" << std::endl;
    }

    std::cout << "You entered: " << user_input << std::endl;
    std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
