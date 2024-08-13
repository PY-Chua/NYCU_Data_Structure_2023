#include <iostream>
#include <string>
#include <regex>

using namespace std;

// Define a structure to represent a term in a polynomial
struct Term {
    int coefficient, exponent;
    Term* next;

    Term(int coef, int exp) : coefficient(coef), exponent(exp), next(nullptr) {}
};

// Define a class for a polynomial
class Polynomial {
public:
    Term* head;

    Polynomial() : head(nullptr) {}

    // Destructor to free memory
    ~Polynomial() {
        clear();
    }

    // Copy constructor to perform deep copy
    Polynomial(const Polynomial& other) : head(nullptr) {
        if (other.head) {
            Term* current = other.head;
            while (current) {
                insertTerm(current->coefficient, current->exponent);
                current = current->next;
            }
        }
    }

    // Assignment operator to perform deep copy
    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            clear();
            if (other.head) {
                Term* current = other.head;
                while (current) {
                    insertTerm(current->coefficient, current->exponent);
                    current = current->next;
                }
            }
        }
        return *this;
    }

    // Function to insert a term into the polynomial in descending order of exponents
    void insertTerm(int coef, int exp) {
        Term* newTerm = new Term(coef, exp);
        if (!head || exp > head->exponent) {
            newTerm->next = head;
            head = newTerm;
        } else {
            Term* current = head;
            while (current->next && exp <= current->next->exponent) {
                current = current->next;
            }
            newTerm->next = current->next;
            current->next = newTerm;
        }
    }

    // Function to simplify the polynomial
    void simplify() {
        Term* current = head;
        Term* prev = nullptr;

        while (current) {
            Term* next = current->next;

            if (next && current->exponent == next->exponent) {
                // Combine terms with the same exponent
                next->coefficient += current->coefficient;
                if (prev) {
                    prev->next = current->next;
                    delete current;
                    current = prev->next;
                } else {
                    head = current->next;
                    delete current;
                    current = head;
                }
            } else {
                prev = current;
                current = next;
            }
        }
    }

// Function to add or subtract another polynomial from this polynomial
    void addOrSubtract(Polynomial& other, bool subtract) {
        Term* current1 = head;
        Term* current2 = other.head;
        Polynomial result;

        while (current1 && current2) {
            if (current1->exponent > current2->exponent) {
                result.insertTerm(current1->coefficient, current1->exponent);
                current1 = current1->next;
            } else if (current1->exponent < current2->exponent) {
                result.insertTerm(subtract ? -current2->coefficient : current2->coefficient, current2->exponent);
                current2 = current2->next;
            } else {
                int op = subtract ? (current1->coefficient - current2->coefficient) : (current1->coefficient + current2->coefficient);
                if (op != 0) {
                    result.insertTerm(op, current1->exponent);
                }
                current1 = current1->next;
                current2 = current2->next;
            }
        }

        while (current1) {
            result.insertTerm(current1->coefficient, current1->exponent);
            current1 = current1->next;
        }

        while (current2) {
            result.insertTerm(subtract ? -current2->coefficient : current2->coefficient, current2->exponent);
            current2 = current2->next;
        }

        // Delete the old linked list and set it to the new result
        clear();
        head = result.head;
        result.head = nullptr;
    }

    // Function to clear the polynomial and free memory
    void clear() {
        while (head) {
            Term* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Function to display the polynomial
    void display() {
        Term* current = head;
        if (!current) {
            std::cout << "0" << std::endl;
            return;
        }
        bool firstTerm = true;
        while (current) {
            if (current->coefficient != 0) {
                if (!firstTerm) {
                    if (current->coefficient > 0) {
                        std::cout << "+";
                    }
                }
                if (current->exponent > 1) {
                    if (current->coefficient != 1 && current->coefficient != -1) {
                        std::cout << current->coefficient;
                    } else if (current->coefficient == -1) {
                        std::cout << "-";
                    }
                    std::cout << "x^" << current->exponent;
                } else if (current->exponent == 1) {
                    if (current->coefficient != 1 && current->coefficient != -1) {
                        std::cout << current->coefficient;
                    } else if (current->coefficient == -1) {
                        std::cout << "-";
                    }
                    std::cout << "x";
                } else {
                    std::cout << current->coefficient;
                }
                firstTerm = false;
            }
            current = current->next;
        }
        std::cout << std::endl;
    }
};

// Function to parse and insert terms into a polynomial from an input string
void parseAndInsertTerms(const std::string& input, Polynomial& poly) {
    std::regex termRegex(R"(-?\d*x?\^?\d*)");
    std::sregex_iterator termIterator(input.begin(), input.end(), termRegex);
    std::sregex_iterator termEnd;

    for (; termIterator != termEnd; ++termIterator) {
        std::string term = termIterator->str();
        int coef = 0, exp = 0;

        if (term == "0") {
            return;  // The entire polynomial is zero
        }

        if (term.find("x^") != std::string::npos) {
            // Term contains "x^", indicating an exponent greater than 1
            if (sscanf(term.c_str(), "%dx^%d", &coef, &exp) == 2) {
                poly.insertTerm(coef, exp);
            } else if (sscanf(term.c_str(), "-x^%d", &exp) == 1) {
                poly.insertTerm(-1, exp);
            } else if (sscanf(term.c_str(), "x^%d", &exp) == 1) {
                poly.insertTerm(1, exp);
            }
        } else if (term.find("x") != std::string::npos) {
            // Term contains "x", indicating an exponent of 1
            if (sscanf(term.c_str(), "%dx", &coef) == 1) {
                poly.insertTerm(coef, 1);
            } else if (term == "-x") {
                poly.insertTerm(-1, 1);
            } else {
                poly.insertTerm(1, 1);
            }
        } else {
            // Term doesn't contain "x", indicating an exponent of 0
            if (sscanf(term.c_str(), "%d", &coef) == 1) {
                poly.insertTerm(coef, 0);
            }
        }
    }
}

int main() {
    std::string input1, input2, operation;
    std::cin >> input1;
    std::cin >> input2;
    std::cin >> operation;

    Polynomial poly1, poly2;

    // Parse and insert terms into the first and second polynomials
    parseAndInsertTerms(input1, poly1);
    parseAndInsertTerms(input2, poly2);

    if (poly1.head == nullptr && poly2.head == nullptr) {
        std::cout << "0" << std::endl;
        return 0;
    }

    if (operation == "+") {
        poly1.addOrSubtract(poly2, false);
    } else if (operation == "-") {
        poly1.addOrSubtract(poly2, true);
    }
    
    poly1.simplify();
    poly1.display();

    poly1.clear();
    poly2.clear();

    return 0;
}