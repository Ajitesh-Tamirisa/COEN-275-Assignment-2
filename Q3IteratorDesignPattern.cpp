#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book;
class Category;
class Iterator;

class Book {
private:
    string title;
public:
    Book(const string& title) : title(title) {}
    string getTitle() const { return title; }
};

class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual Book* next() = 0;
};

// Concrete Iterator for books
class BookIterator : public Iterator {
private:
    vector<Book*> books;
    size_t position;
public:
    BookIterator(vector<Book*>& books) : books(books), position(0) {}
    bool hasNext() override { return position < books.size(); }
    Book* next() override {
        if (!hasNext()) {
            throw out_of_range("No more books");
        }
        return books[position++];
    }
};

class Category {
private:
    string name;
    vector<Book*> books;
public:
    Category(const string& name) : name(name) {}
    void addBook(Book* book) { books.push_back(book); }
    Iterator* createIterator() { return new BookIterator(books); }
    string getName() const { return name; }
};

class Library {
private:
    vector<Category*> categories;
public:
    void addCategory(Category* category) { categories.push_back(category); }

    // Iterate over all books in the library
    void iterateAllBooks() {
        for (Category* category : categories) {
            Iterator* iterator = category->createIterator();
            while (iterator->hasNext()) {
                Book* book = iterator->next();
                cout << category->getName() << ": " << book->getTitle() << endl;
            }
            delete iterator;
        }
    }

    // Iterate over books in a specific category
    void iterateCategoryBooks(const string& categoryName) {
        for (Category* category : categories) {
            if (category->getName() == categoryName) {
                Iterator* iterator = category->createIterator();
                while (iterator->hasNext()) {
                    Book* book = iterator->next();
                    cout << category->getName() << ": " << book->getTitle() << endl;
                }
                delete iterator;
                return;
            }
        }
        cout << "Category not found: " << categoryName << endl;
    }
};

int main() {
    Library library;

    Category fiction("Fiction");
    fiction.addBook(new Book("Fiction Book 1"));
    fiction.addBook(new Book("Fiction Book 2"));
    fiction.addBook(new Book("Fiction Book 3"));

    Category nonFiction("Non-Fiction");
    nonFiction.addBook(new Book("Non Fiction Book 1"));
    nonFiction.addBook(new Book("Non Fiction Book 2"));
    nonFiction.addBook(new Book("Non Fiction Book 3"));
    nonFiction.addBook(new Book("Non Fiction Book 4"));
    nonFiction.addBook(new Book("Non Fiction Book 5"));

    Category science("Science");
    science.addBook(new Book("Science Book 1"));
    science.addBook(new Book("Science Book 2"));
    science.addBook(new Book("Science Book 3"));

    library.addCategory(&fiction);
    library.addCategory(&nonFiction);
    library.addCategory(&science);

    cout << "\n***********Iterating over all books***********" << endl;
    library.iterateAllBooks();

    cout << "\n***********Iterating over Fiction books***********" << endl;
    library.iterateCategoryBooks("Fiction");

    cout << "\n***********Iterating over Non-Fiction books***********" << endl;
    library.iterateCategoryBooks("Non-Fiction");

    cout << "\n***********Iterating over Science books***********" << endl;
    library.iterateCategoryBooks("Science");

    return 0;
}
