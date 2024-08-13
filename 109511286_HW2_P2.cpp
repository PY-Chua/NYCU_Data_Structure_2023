#include <iostream>
#include <list>
#include <string>

using namespace std;

class Card {
public:
    string value;
    Card* next;

    Card(const string& val) : value(val), next(nullptr) {}
};

class CardPile {
public:
    CardPile() : head(nullptr), tail(nullptr) {}

    void add(const string& value) {
        Card* newCard = new Card(value);
        if (head == nullptr) {
            head = tail = newCard;
        } else {
            newCard->next = head;
            head = newCard;
        }
    }

    void deleteCard(const string& value) {
        Card* current = head;
        Card* previous = nullptr;

        while (current != nullptr) {
            if (current->value == value) {
                if (current == head) {
                    head = current->next;
                } else if (current == tail) {
                    tail = previous;
                    tail->next = nullptr;
                } else {
                    previous->next = current->next;
                }
                delete current;
                return;
            }

            previous = current;
            current = current->next;
        }
    }

    void truncateFirst() {
        if (head != nullptr) {
            Card* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void truncateLast() {
        if (head != nullptr) {
            if (head == tail) {
                delete head;
                head = tail = nullptr;
            } else {
                Card* current = head;
                while (current->next != tail) {
                    current = current->next;
                }
                delete tail;
                tail = current;
                tail->next = nullptr;
            }
        }
    }

    void printCardPile() {
        Card* current = head;
        while (current != nullptr) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }

    ~CardPile() {
        while (head != nullptr) {
            Card* temp = head;
            head = head->next;
            delete temp;
        }
    }

private:
    Card* head;
    Card* tail;
};

int main() {
    int n;
    cin >> n;

    CardPile cardPile;

    while (n--) {
        string operation;
        cin >> operation;

        if (operation == "add") {
            string card;
            cin >> card;
            cardPile.add(card);
        } else if (operation == "delete") {
            string card;
            cin >> card;
            cardPile.deleteCard(card);
        } else if (operation == "truncateFirst") {
            cardPile.truncateFirst();
        } else if (operation == "truncateLast") {
            cardPile.truncateLast();
        }
    }

    cardPile.printCardPile();

    return 0;
}