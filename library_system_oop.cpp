// Library Management System with Full OOP Features
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <iomanip>

using namespace std;

// Utility to get current date as string
tm getCurrentDate() {
    time_t now = time(0);
    return *localtime(&now);
}

string formatDate(tm date) {
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &date);
    return string(buffer);
}

int daysBetween(tm start, tm end) {
    time_t x = mktime(&start);
    time_t y = mktime(&end);
    return difftime(y, x) / (60 * 60 * 24);
}

class Book {
protected:
    string title, author;
    int id;
    bool available;

public:
    Book(int id, string title, string author)
        : id(id), title(title), author(author), available(true) {}

    virtual void display() {
        cout << "Book ID: " << id << ", Title: " << title << ", Author: " << author << ", Available: " << (available ? "Yes" : "No") << endl;
    }

    bool isAvailable() const { return available; }
    void setAvailable(bool status) { available = status; }
    int getId() const { return id; }
    string getTitle() const { return title; }
};

class Transaction {
    int bookId;
    string bookTitle;
    tm issueDate;
    tm returnDate;
    int fine;

public:
    Transaction(int id, string title, tm issue)
        : bookId(id), bookTitle(title), issueDate(issue), fine(0) {
        returnDate = {0};
    }

    void closeTransaction(tm returnD) {
        returnDate = returnD;
        int daysLate = daysBetween(issueDate, returnDate) - 14;
        fine = (daysLate > 0) ? daysLate * 10 : 0;
    }

    void display() {
        cout << "Book: " << bookTitle
             << ", Issued: " << formatDate(issueDate)
             << ", Returned: " << formatDate(returnDate)
             << ", Fine: Rs. " << fine << endl;
    }
};

class User {
    string name;
    int userId;
    vector<Transaction> history;
    map<int, tm> borrowedBooks; // BookID -> IssueDate

public:
    User(int id, string name) : userId(id), name(name) {}

    void borrowBook(Book &book) {
        if (!book.isAvailable()) {
            cout << "Book not available!\n";
            return;
        }
        book.setAvailable(false);
        tm today = getCurrentDate();
        borrowedBooks[book.getId()] = today;
        cout << "Book borrowed: " << book.getTitle() << " on " << formatDate(today) << endl;
    }

    void returnBook(Book &book) {
        if (borrowedBooks.find(book.getId()) == borrowedBooks.end()) {
            cout << "No such book borrowed!\n";
            return;
        }
        book.setAvailable(true);
        tm issue = borrowedBooks[book.getId()];
        tm today = getCurrentDate();

        Transaction txn(book.getId(), book.getTitle(), issue);
        txn.closeTransaction(today);
        history.push_back(txn);
        borrowedBooks.erase(book.getId());

        cout << "Book returned: " << book.getTitle() << " on " << formatDate(today) << endl;
        txn.display();
    }

    void viewHistory() {
        cout << "Borrowing history for " << name << ":\n";
        for (auto &txn : history) {
            txn.display();
        }
    }
};

class Library {
    vector<Book> books;
    vector<User> users;

public:
    void addBook(int id, string title, string author) {
        books.emplace_back(id, title, author);
    }

    void addUser(int id, string name) {
        users.emplace_back(id, name);
    }

    Book* findBook(int id) {
        for (auto &b : books)
            if (b.getId() == id)
                return &b;
        return nullptr;
    }

    User* findUser(int id) {
        for (auto &u : users)
            if (u.userId == id)
                return &u;
        return nullptr;
    }

    void borrowBook(int userId, int bookId) {
        Book *b = findBook(bookId);
        User *u = findUser(userId);
        if (b && u)
            u->borrowBook(*b);
        else
            cout << "Invalid User or Book ID.\n";
    }

    void returnBook(int userId, int bookId) {
        Book *b = findBook(bookId);
        User *u = findUser(userId);
        if (b && u)
            u->returnBook(*b);
        else
            cout << "Invalid User or Book ID.\n";
    }

    void showUserHistory(int userId) {
        User *u = findUser(userId);
        if (u)
            u->viewHistory();
        else
            cout << "User not found!\n";
    }
};

int main() {
    Library lib;
    lib.addBook(1, "1984", "Orwell");
    lib.addBook(2, "Clean Code", "Robert Martin");
    lib.addUser(101, "Alice");

    lib.borrowBook(101, 1);
    // Simulate wait here in real app
    lib.returnBook(101, 1);
    lib.showUserHistory(101);

    return 0;
}
