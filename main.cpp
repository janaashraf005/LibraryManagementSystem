#include <iostream>
using namespace std;

class Book{
public:
    int ID;
    string title;
    string author;
    bool availability = true;

    struct waitingNode {
        int userID;
        waitingNode *next;
        waitingNode(int id) {
            userID = id;
            next = NULL;
        }
    };

    waitingNode *head = NULL;

    void addToWaiting(int id) {
        waitingNode *newNode = new waitingNode(id);
        if (head == NULL) {
            head = newNode;
        } else {
            waitingNode *current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    int removeFromWaiting() {
        if (head == NULL) {
            return -1;
        } else {
            waitingNode *current = head;
            int userID = current->userID;
            head = head->next;
            delete current;
            return userID;
        }
    }
};

class user {
public:
    string name;
    int ID;
};

struct node {
    Book* bookNode;
    node* next;
    node(Book* b) {
        bookNode = b;
        next = NULL;
    }
};

struct userNode {
    user* userptr;
    userNode *next;
    userNode(user *u) {
        userptr = u;
        next = NULL;
    }
};

class library{
private:
    node* head = NULL;
    userNode *userhead = NULL;

public:
    void addBook(int id, string t, string aut) {
        Book* newBook = new Book{};
        newBook->ID = id;
        newBook->title = t;
        newBook->author = aut;

        node* newNode = new node(newBook);
        if (head == NULL) {
            head = newNode;
        } else {
            node* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
        cout<<endl;
    }

    void searchBookID(int id) {
        node* current = head;
        bool found = false;

        if (current == NULL) {
            cout << "Library is empty." << endl;
        } else {
            while (current != NULL) {
                if (current->bookNode->ID == id) {
                    cout << "Book title: " << current->bookNode->title << endl;
                    cout << "Book ID: " << current->bookNode->ID << endl;
                    cout << "Book availability: " << current->bookNode->availability << endl;
                    found = true;
                    break;
                }
                current = current->next;
            }
            if (!found) {
                cout << "Book with ID " << id << " not found." << endl;
            }
        }
        cout<<endl;
    }

    void searchBookTitle(string t) {
        node* current = head;
        bool found = false;

        if (current == NULL) {
            cout << "Library is empty." << endl;
        } else {
            while (current != NULL) {
                if (current->bookNode->title == t) {
                    cout << "Book title: " << current->bookNode->title << endl;
                    cout << "Book ID: " << current->bookNode->ID << endl;
                    cout << "Book availability: " << current->bookNode->availability << endl;
                    found = true;
                    break;
                }
                current = current->next;
            }
            if (!found) {
                cout << "Book with title " << t << " not found." << endl;
            }
        }
        cout<<endl;
    }
  void deleteBook(int bookID){
   node *current=head;
   node *prev = NULL;
   bool found=false;
   while(current!=NULL){
        if(current->bookNode->ID==bookID){
            if(prev==NULL){
                head=current->next;
                delete current;
                current=head;
                found=true;
                cout<<"Book has been deleted"<<endl;
            }
            else{
                prev->next=current->next;
                delete current;
                current=prev->next;
                found=true;
                cout<<"Book has been deleted"<<endl;
            }
        }
        else{
            prev=current;
            current=current->next;
        }
  }
  if(!found){
    cout << "Book with ID " << bookID << " not found." << endl;
  }
  cout<<endl;
  }

  void display(){
   node *current=head;
   if(head==NULL){
    cout<<"Library is empty"<<endl;
   }
   while(current!=NULL){
    cout <<"Book's title: " << current->bookNode->title << endl
         << "Book's ID: " << current->bookNode->ID << endl
         << "Book's author: "<<current->bookNode->author<<endl
         << "Book availability: " << current->bookNode->availability << endl;
         current=current->next;
         cout<<endl;
   }
   cout<<endl;
  }

  void registerUser(string n, int id){
   user *newUser = new user{};
   newUser->name=n;
   newUser->ID=id;

   userNode *newUserNode = new userNode(newUser);
   if (userhead == NULL) {
            userhead = newUserNode;
        }
        else {
            userNode* current = userhead;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newUserNode;
        }
        cout<<endl;
    }

 void displayUsers(){
  userNode *current=userhead;
  if(userhead==NULL){
    cout<<"No registered users"<<endl;
   }
   while(current!=NULL){
    cout <<"User's name: " << current->userptr->name<< endl
         << "User's ID: " << current->userptr->ID<< endl;
         current=current->next;
         cout<<endl;
   }
   cout<<endl;
 }
 void returnBook(int bookID) {
        node *current = head;
        bool found = false;

        while (current != NULL) {
            if (current->bookNode->ID == bookID) {
                found = true;

                if (current->bookNode->availability) {
                    cout << "Book was not borrowed." << endl;
                }
                else {
                    int nextUserID = current->bookNode->removeFromWaiting();
                    if (nextUserID == -1) {
                        current->bookNode->availability = true;
                        cout << "Book has been returned and is now available." << endl;
                    }
                    else {
                        cout << "Book has been assigned to the next user in the waiting list (User ID: " << nextUserID << ")." << endl;
                    }
                }
                break;
            }
            current = current->next;
        }

        if (!found) {
            cout << "Book with ID " << bookID << " not found." << endl;
        }

        cout << endl;
    }

 void borrowBook(int userID, int bookID){
     node *current=head;
     bool found=false;
     while(current!=NULL){
     if(current->bookNode->ID==bookID){
        found=true;
        if(current->bookNode->availability==true){
            current->bookNode->availability=false;
            cout<<"Book has been borrowed successfully"<<endl;
        }
        else{
            cout<<"Book is currently unavailable. User added to waiting list"<<endl;
            current->bookNode->addToWaiting(userID);
        }
        break;
     }
     else{
        current=current->next;
     }
     }
     if(!found){
       cout << "Book with ID " << bookID << " not found." <<endl;
     }
   cout<<endl;
 }

 void Sort(library lib) {
     int x;
     cout<<"Enter 1 to sort by title"<<endl
         <<"Enter 2 to sort by ID"<<endl
         <<"Enter 3 to sort by author"<<endl;
     cin>>x;
        switch (x) {
        case 1: {
          if (head == NULL) {
        cout << "Library is empty." << endl;
        return;
      }

     for (node *i = head; i != NULL; i = i->next) {
        for (node *j = i->next; j != NULL; j = j->next) {
            if (i->bookNode->title > j->bookNode->title) {
                Book *temp = i->bookNode;
                i->bookNode = j->bookNode;
                j->bookNode = temp;
            }
        }
    }

    lib.display();
    cout << endl;
        } break;
        case 2: {
          if (head == NULL || head->next == NULL) {
        cout << "Library is empty." << endl;
        return;
      }

     for (node *i = head; i != NULL; i = i->next) {
        for (node *j = i->next; j != NULL; j = j->next) {
            if (i->bookNode->ID > j->bookNode->ID) {
                Book *temp = i->bookNode;
                i->bookNode = j->bookNode;
                j->bookNode = temp;
            }
        }
    }

    lib.display();
    cout << endl;
        } break;
        case 3: {
            if (head == NULL || head->next == NULL) {
        cout << "Library is empty." << endl;
        return;
      }

     for (node *i = head; i != NULL; i = i->next) {
        for (node *j = i->next; j != NULL; j = j->next) {
            if (i->bookNode->author > j->bookNode->author) {
                Book *temp = i->bookNode;
                i->bookNode = j->bookNode;
                j->bookNode = temp;
            }
        }
    }

    lib.display();
    cout << endl;
        }
        break;
        default:
            cout << "Invalid choice" << endl;
        }

}



};

int main() {
    library lib;
    int x;

    while (true) {
        cout << "Enter 1 for adding a book" << endl
             << "Enter 2 for searching for a book by ID" << endl
             << "Enter 3 for searching for a book by title" << endl
             << "Enter 4 for deleting a book" << endl
             << "Enter 5 for displaying the available books" << endl
             << "Enter 6 for user registration" << endl
             << "Enter 7 for displaying registered users" << endl
             << "Enter 8 to borrow a book" << endl
             << "Enter 9 to return a book" << endl
             << "Enter 10 to sort books" << endl
             << "Enter 0 to exit" << endl;
        cin >> x;

        switch (x) {
        case 1: {
            int id;
            string t, aut;
            cout << "Enter the book's ID: ";
            cin >> id;
            cout << "Enter the book's title: ";
            cin >> t;
            cout << "Enter the book's author: ";
            cin >> aut;
            lib.addBook(id, t, aut);
        } break;
        case 2: {
            int id;
            cout << "Enter the book's ID: ";
            cin >> id;
            lib.searchBookID(id);
        } break;
        case 3: {
            string t;
            cout << "Enter the book's title: ";
            cin >> t;
            lib.searchBookTitle(t);
        } break;
        case 4: {
            int id;
            cout << "Enter the book's ID: ";
            cin >> id;
            lib.deleteBook(id);
        } break;
        case 5: {
            lib.display();
        } break;
        case 6: {
            int id;
            string n;
            cout << "Enter the user's name: ";
            cin >> n;
            cout << "Enter the user's ID: ";
            cin >> id;
            lib.registerUser(n,id);
        } break;
        case 7: {
            lib.displayUsers();
        } break;
        case 8: {
            int userID, bookID;
            cout << "Enter the user's ID: ";
            cin >> userID;
            cout << "Enter the book's ID you want to borrow: ";
            cin >> bookID;
            lib.borrowBook(userID, bookID);
        } break;
        case 9: {
            int bookID;
            cout << "Enter the book's ID to return: ";
            cin >> bookID;
            lib.returnBook(bookID);
        } break;
        case 10: {
          lib.Sort(lib);
        } break;
        case 0: {
            return 0;
        }
        default:
            cout << "Invalid choice" << endl;
        }
    }

    return 0;
}






