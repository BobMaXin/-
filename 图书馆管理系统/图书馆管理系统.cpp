#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Book {
public:
    string title;
    string author;
    int borrowCount;

    Book(string title, string author) {
        this->title = title;
        this->author = author;
        this->borrowCount = 0;
    }
};

class Reader {
public:
    string name;
    vector<Book*> borrowedBooks;

    Reader(string name) {
        this->name = name;
    }

    void borrowBook(Book* book) {
        borrowedBooks.push_back(book);
    }

    void returnBook(Book* book) {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), book);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
        }
    }
};

class LibraryManagementSystem {
private:
    vector<Book*> books;
    vector<Reader*> readers;

public:
    void addBook(string title, string author) {
        books.push_back(new Book(title, author));
    }

    void addReader(string name) {
        readers.push_back(new Reader(name));
    }

    void borrowBook(string readerName, string bookTitle) {
        Reader* reader = nullptr;
        Book* book = nullptr;

        for (Reader* r : readers) {
            if (r->name == readerName) {
                reader = r;
                break;
            }
        }

        for (Book* b : books) {
            if (b->title == bookTitle) {
                book = b;
                break;
            }
        }

        if (reader && book) {
            reader->borrowBook(book);
            book->borrowCount++;
        }
        else {
            cout << "Failed to borrow book." << endl;
        }
    }

    void returnBook(string readerName, string bookTitle) {
        Reader* reader = nullptr;
        Book* book = nullptr;

        for (Reader* r : readers) {
            if (r->name == readerName) {
                reader = r;
                break;
            }
        }

        for (Book* b : books) {
            if (b->title == bookTitle) {
                book = b;
                break;
            }
        }

        if (reader && book) {
            reader->returnBook(book);
        }
        else {
            cout << "Failed to return book." << endl;
        }
    }

    void displayTopBooks(int n) {
        vector<Book*> sortedBooks = books;
        sort(sortedBooks.begin(), sortedBooks.end(), [](Book* a, Book* b) {
            return a->borrowCount > b->borrowCount;
            });

        cout << "Top " << n << " most borrowed books:" << endl;
        for (int i = 0; i < min((int)sortedBooks.size(), n); i++) {
            cout << sortedBooks[i]->title << " by " << sortedBooks[i]->author << " (borrowed " << sortedBooks[i]->borrowCount << " times)" << endl;
        }
    }

    void displayPersonalizedRecommendation(string readerName) {
        Reader* reader = nullptr;
        for (Reader* r : readers) {
            if (r->name == readerName) {
                reader = r;
                break;
            }
        }

        if (reader) {
            cout << "Personalized recommendation for " << reader->name << ":" << endl;
            for (Book* book : books) {
                if (find(reader->borrowedBooks.begin(), reader->borrowedBooks.end(), book) == reader->borrowedBooks.end()) {
                    cout << book->title << " by " << book->author << endl;
                }
            }
        }
        else {
            cout << "Reader not found." << endl;
        }
    }
};

int main() {
    LibraryManagementSystem lms;

    lms.addBook("The Great Gatsby", "F. Scott Fitzgerald");
    lms.addBook("To Kill a Mockingbird", "Harper Lee");
    lms.addBook("1984", "George Orwell");
    lms.addBook("Pride and Prejudice", "Jane Austen");

    lms.addReader("Alice");
    lms.addReader("Bob");
    lms.addReader("Charlie");

    lms.borrowBook("Alice", "The Great Gatsby");
    lms.borrowBook("Bob", "To Kill a Mockingbird");
    lms.borrowBook("Charlie", "1984");
    lms.borrowBook("Alice", "Pride and Prejudice");

    lms.returnBook("Alice", "The Great Gatsby");

    lms.displayTopBooks(3);
    lms.displayPersonalizedRecommendation("Alice");

    return 0;
}