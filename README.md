# Library-Management-System

# 📚 Library Management System in C++

A simple yet powerful **Object-Oriented Library Management System** built in C++. This project demonstrates practical implementation of OOP concepts like **encapsulation**, **inheritance**, and **abstraction** along with features such as **book borrowing, returning, fine calculation**, and **transaction history tracking**.

---

## 🚀 Features

- Add new books and users
- Borrow and return books
- Fine calculation for late returns (₹10 per day after 14 days)
- Track each user’s borrowing history
- Availability status for each book
- Proper date handling using `<ctime>`

---

## 🧱 Object-Oriented Concepts Used

| Class       | Responsibility                                                  |
|-------------|------------------------------------------------------------------|
| `Book`      | Stores book details and availability status                     |
| `User`      | Handles user info, borrowing/returning logic, and history       |
| `Transaction` | Logs book borrow/return with date and fine computation        |
| `Library`   | Acts as a manager to connect books and users                    |

---

## 🛠️ Tech Stack

- **Language**: C++
- **Standard Library Used**: `<vector>`, `<string>`, `<map>`, `<ctime>`, `<iomanip>`

---
