#include <iostream>
#include <string>
using namespace std;

const int MAX_BOOKS = 50;
const int MAX_MEMBERS = 50;
const int MAX_ISSUES = 100;

struct Book {
    int id;
    string title;
    int copies;
};

struct Member {
    int id;
    string name;
    int booksIssued;
};

struct Issue {
    int bookId;
    int memberId;
};

void addBook(Book books[], int& bookCount) {
    if (bookCount >= MAX_BOOKS) {
        cout << "Library is full, cannot add more books.\n";
        return;
    }
    cout << "Enter Book ID: ";
    cin >> books[bookCount].id;
    cout << "Enter Book Title: ";
    cin.ignore();
    getline(cin, books[bookCount].title);
    cout << "Enter number of copies: ";
    cin >> books[bookCount].copies;
    bookCount++;
    cout << "Book added successfully.\n";
}

void addMember(Member members[], int& memberCount) {
    if (memberCount >= MAX_MEMBERS) {
        cout << "Library membership is full, cannot add more members.\n";
        return;
    }
    cout << "Enter Member ID: ";
    cin >> members[memberCount].id;
    cout << "Enter Member Name: ";
    cin.ignore();
    getline(cin, members[memberCount].name);
    members[memberCount].booksIssued = 0;
    memberCount++;
    cout << "Member added successfully.\n";
}

void issueBook(Book books[], int bookCount, Member members[], int memberCount, Issue issues[], int& issueCount) {
    if (issueCount >= MAX_ISSUES) {
        cout << "Issue log is full, cannot issue more books.\n";
        return;
    }

    int bookId, memberId;

    cout << "Enter Book ID to issue: ";
    cin >> bookId;
    cout << "Enter Member ID: ";
    cin >> memberId;

    int bookIndex = -1;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == bookId) {
            bookIndex = i;
            break;
        }
    }

    if (bookIndex == -1) {
        cout << "Book not available.\n";
        return;
    }
    else if (books[bookIndex].copies <= 0) {
        cout << "No copies of the book are available.\n";
        return;
    }

    int memberIndex = -1;
    for (int i = 0; i < memberCount; i++) {
        if (members[i].id == memberId) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
        cout << "Member not found.\n";
        return;
    }
    else if (members[memberIndex].booksIssued >= 5) {
        cout << "Member has already issued the maximum number of books.\n";
        return;
    }

    books[bookIndex].copies--;
    members[memberIndex].booksIssued++;

    issues[issueCount].bookId = bookId;
    issues[issueCount].memberId = memberId;

    issueCount++;
    cout << "Book issued su ccessfully.\n";
}

void returnBook(Book books[], int bookCount, Member members[], int memberCount, Issue issues[], int& issueCount) {
    int bookId, memberId;

    cout << "Enter Book ID to return: ";
    cin >> bookId;
    cout << "Enter Member ID: ";
    cin >> memberId;

    for (int i = 0; i < issueCount; i++) {
        if (issues[i].bookId == bookId && issues[i].memberId == memberId) {
            for (int j = 0; j < bookCount; j++) {
                if (books[j].id == bookId) {
                    books[j].copies++;
                    break;
                }
            }

            for (int k = 0; k < memberCount; k++) {
                if (members[k].id == memberId) {
                    members[k].booksIssued--;
                    break;
                }
            }
            //array deletion
            for (int l = i; l < issueCount - 1; l++) {
                issues[l] = issues[l + 1];
            }
            issueCount--;

            cout << "Book returned successfully.\n";
            return;
        }
    }
    cout << "No matching issue found.\n";
}

void displayBooks(const Book books[], int bookCount) {
    cout << "Books in library:\n";
    for (int i = 0; i < bookCount; i++) {
        cout << "Book ID: " << books[i].id << ", Title: " << books[i].title << ", Copies: " << books[i].copies << "\n";
    }
}

void displayMembers(const Member members[], int memberCount) {
    cout << "Library Members:\n";
    for (int i = 0; i < memberCount; i++) {
        cout << "Member ID: " << members[i].id << ", Name: " << members[i].name << ", Books Issued: " << members[i].booksIssued << "\n";
    }
}

void displayIssues(const Issue issues[], int issueCount) {
    cout << "Issued Books:\n";
    for (int i = 0; i < issueCount; i++) {
        cout << "Book ID: " << issues[i].bookId << ", Member ID: " << issues[i].memberId << "\n";
    }
}

int main() {
    Book books[MAX_BOOKS];
    int bookCount = 0;

    Member members[MAX_MEMBERS];
    int memberCount = 0;

    Issue issues[MAX_ISSUES];
    int issueCount = 0;

    int choice;
    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Add Member\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Display Books\n";
        cout << "6. Display Members\n";
        cout << "7. Display Issues\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addBook(books, bookCount);
            break;
        case 2:
            addMember(members, memberCount);
            break;
        case 3:
            issueBook(books, bookCount, members, memberCount, issues, issueCount);
            break;
        case 4:
            returnBook(books, bookCount, members, memberCount, issues, issueCount);
            break;
        case 5:
            displayBooks(books, bookCount);
            break;
        case 6:
            displayMembers(members, memberCount);
            break;
        case 7:
            displayIssues(issues, issueCount);
            break;
        case 8:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please ";

        }
    }

}