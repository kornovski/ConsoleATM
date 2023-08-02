#include <iostream>
#include <string>

class Node {
public:
    int CardNumber;
    std::string Password;
    int Balance;
    Node* Next;
};

bool existingAccountCkeck(Node* head, int cardNumber) {
    Node* current = head;
    while (current != NULL) {
        if (current->CardNumber == cardNumber) {
            return true;
        }
        current = current->Next;
    }
    return false;
}

void addAccount(Node**head) {

    // !!ADD VALID PASSWORD CHECK!!

    int cardNumber;
    std::string password;

    std::cout << "Enter Card Number: ";
    std::cin >> cardNumber;

    // Existing account check
    if (existingAccountCkeck(*head, cardNumber)) {
        std::cout << "Account with card number " << cardNumber << " already exists.\n";
        return;
    }

    std::cout << "Enter Password: ";
    std::cin >> password;
    
    // Make new node
    Node* newNode = new Node();
    newNode->CardNumber = cardNumber;
    newNode->Password = password;
    newNode->Balance = 0;
    newNode->Next = NULL;

    // Check for emptyness of linked list
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    // Find last node
    Node* last = *head;
    while (last->Next != NULL) {
        last = last->Next;
    }
    // Insert node after last node
    last->Next = newNode;

    std::cout << "Congratulations. Account has been registered!\n";
}

Node* login(Node* head) {
    int cardNumber;
    std::string password;

    std::cout << "Enter Card Number: ";
    std::cin >> cardNumber;

    std::cout << "Enter Password: ";
    std::cin >> password;

    Node* current = head;
    while (current != NULL) {
        if (current->CardNumber == cardNumber && current->Password == password) {
            std::cout << "Login successful!" << std::endl;
            return current;
        }
        current = current->Next;
    }

    std::cout << "Invalid credentials. Please try again." << std::endl;
    return nullptr;
}

// Show all existing accounts for checking
void display(Node* n) {
    while (n != NULL) {
        std::cout << n->CardNumber << " ";
        std::cout << n->Password << " ";
        std::cout << n->Balance << " ";
        n = n->Next;
    }
    std::cout << std::endl;
}

// Main loop
void runATM() {
    Node* head = new Node();
    
    int choice;
    Node* current = head; // This variable existing for freeing memory !!! ADD ACCOUNT DELETING !!!
    Node* currentUser = nullptr;

    do {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Add new account" << std::endl;
        std::cout << "2. Login" << std::endl;
        std::cout << "3. Show all existing accounts" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            addAccount(&head); // Add new account
            break;
        case 2:
            currentUser = login(head); // Login
            break;
        case 3:
            display(head); // Show all existing accounts
            break;
        case 4:
            // Free memory (Optional, but recommended)
            while (current != NULL) {
                Node* next = current->Next;
                delete current;
                current = next;
            }
            head = NULL;
            std::cout << "Exiting the program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }

        // Logged-in menu
        while (currentUser != nullptr) {
            std::cout << "Logged-in Menu:" << std::endl;
            std::cout << "1. Check your current balance" << std::endl;
            std::cout << "2. Add money to Balance" << std::endl;
            std::cout << "3. Transfer money to another CardNumber" << std::endl;
            std::cout << "4. Back to previous menu" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
            case 1:
                std::cout << "Your current balance is: " << currentUser->Balance << std::endl;
                break;
            case 2:
                int amountToAdd;
                std::cout << "Enter the amount to add to your balance: ";
                std::cin >> amountToAdd;
                currentUser->Balance += amountToAdd;
                std::cout << "Balance updated. Your new balance is: " << currentUser->Balance << std::endl;
                break;
            case 3:
                int transferAmount, targetCardNumber;
                std::cout << "Enter the amount to transfer: ";
                std::cin >> transferAmount;
                std::cout << "Enter the target Card Number: ";
                std::cin >> targetCardNumber;

                // Check if the target card number exists
                if (!existingAccountCkeck(head, targetCardNumber)) {
                    std::cout << "Target Card Number does not exist." << std::endl;
                    break;
                }

                // Check if the user has enough balance to transfer
                if (currentUser->Balance >= transferAmount) {
                    Node* targetAccount = head;
                    while (targetAccount != nullptr && targetAccount->CardNumber != targetCardNumber) {
                        targetAccount = targetAccount->Next;
                    }
                    if (targetAccount != nullptr) {
                        currentUser->Balance -= transferAmount;
                        targetAccount->Balance += transferAmount;
                        std::cout << "Transfer successful. Your new balance is: " << currentUser->Balance << std::endl;
                    }
                    else {
                        std::cout << "Error: Target Account not found." << std::endl;
                    }
                }
                else {
                    std::cout << "Error: Insufficient balance for transfer." << std::endl;
                }
                break;
            case 4:
                currentUser = nullptr; // Back to previous menu
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    } while (true); // FIX THING WITH EXITING
}


int main()
{
    runATM();

    system("pause>0");
}