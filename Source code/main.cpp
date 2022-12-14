#include <bits/stdc++.h> // includes almost all std libraries
#include <string>
#include <iostream>
using namespace std;
//for sorting
string tolowerString(string s){
    for(int i=0;i<s.size();i++){
        s[i] = tolower(s[i]);
    }
    return s;
}

class Book {
    public:
        string AuthorNames;
        string BookTitle;
        string YearPublished;
        vector<string> ISBN;
        string Publisher;
        string LLC;
        int InStock;

    Book(string a, string b, string c, vector<string> d, string e, string f, int g){
        AuthorNames = a;
        BookTitle = b;
        YearPublished = c;
        for(int i=0;i<d.size();i++)ISBN.push_back(d[i]);
        Publisher = e;
        LLC = f;
        InStock = g;
    }
    void issue(){
        if(InStock > 0){
            InStock--;
            cout<<"Book issued successfully!\n";
        }
        else {
            cout<<"Book is not available.\n";
        }
    }
    void Return(){
        InStock++;
        cout<<"Book returned successfully!\n";
    }
    void print(){
        int i;
        cout<<"\nAuthor(s): ";
        cout<<AuthorNames;
        cout<<"\nTitle: ";
        cout<<BookTitle;
        cout<<"\nYear: ";
        cout<<YearPublished;
        cout<<"\nISBN: ";
        for(i=0;i<ISBN.size();i++){
            cout<<ISBN[i]<<" ";
        }
        cout<<"\nPublisher: ";
        cout<<Publisher;
        cout<<"\nLLC: ";
        cout<<LLC;
        cout<<"\nInStock: ";
        cout<<InStock<<endl;
    }
};

class Library {
    public:
        vector<Book> books;
    void add(Book b){
        books.push_back(b);
    }
    void remove(string isbn){
        int pos = -1;
        for(int i=0;i<books.size();i++){
            Book temp = books[i];
            for(int j=0;j<temp.ISBN.size();j++){
                if(temp.ISBN[j]==isbn){
                    temp.print();
                    pos = i;
                }
            }
        }
        if(pos == -1){
            cout<<"No results!"<<endl;
        }
        else {
            cout<<"Do you want to delete this book? (Y|N):";
            char ans;
            cin>>ans;
            if(ans == 'Y' || ans == 'y'){
                books.erase(books.begin()+pos);
                cout<<"Book with ISBN ("<<isbn<<") deleted successfully!\n";
            }
        }
    }
    vector<Book> search(Book b){
        vector<pair<int, Book>> foundBooks;
        vector<Book> result;
        for(int i=0;i<books.size();i++){
            //s1.find(s2)!= std::string::npos
            //это значит что строка с2 есть в строке с1.

            Book target = books[i];
            int similar=0;

            string s1 = target.AuthorNames;
            s1 = tolowerString(s1);
            string s2 = b.AuthorNames;
            s2 = tolowerString(s2);
            if(s1.find(s2)!= std::string::npos && s2.size()>1)similar++;


            s1 = target.BookTitle;
            s1 = tolowerString(s1);
            s2 = b.BookTitle;
            s2 = tolowerString(s2);
            if(s1.find(s2)!= std::string::npos && s2.size()>1)similar++;

            s1 = b.YearPublished;
            s2 = target.YearPublished;
            if(s1==s2)similar++;

            s1 = b.LLC;
            s2 = target.LLC;
            if(s1==s2 && s1.size()>1)similar++;

            for(int j=0;j<b.ISBN.size();j++){
                string s1 = b.ISBN[j];
                s1 = tolowerString(s1);
                for(int k=0;k<target.ISBN.size();k++){
                    string s2 = target.ISBN[k];
                    s2 = tolowerString(s2);
                    if(s1 == s2)similar++;
                }
            }

            s1 = b.Publisher;
            s1 = tolowerString(s1);
            s2 = target.Publisher;
            s2 = tolowerString(s2);
            if(s2.find(s1)!= std::string::npos && s1.size()>1)similar++;

            if(similar > 0){
                pair<int,Book> p = make_pair(similar, target);
                foundBooks.push_back(p);
            }
        }
        if(foundBooks.size()==0)return result;
        for(int i=0;i<foundBooks.size()-1;i++){
            for(int j=i+1;j<foundBooks.size();j++){
                if(foundBooks[i].first < foundBooks[j].first){
                    swap(foundBooks[i], foundBooks[j]);
                }
            }
        }
        for(int i=0;i<foundBooks.size();i++){
            result.push_back(foundBooks[i].second);
        }
        return result;
    }
    void sortByAuthor(){
        for(int i=0;i<books.size()-1;i++){
            for(int j=i+1;j<books.size();j++){
                if(books[i].AuthorNames > books[j].AuthorNames){
                    swap(books[i],books[j]);
                }
            }
        }
    }
    void sortByTitle(){
        for(int i=0;i<books.size()-1;i++){
            for(int j=i+1;j<books.size();j++){
                if(books[i].BookTitle > books[j].BookTitle){
                    swap(books[i], books[j]);
                }
            }
        }
    }
    void sortByYear(){
        for(int i=0;i<books.size()-1;i++){
            for(int j=i+1;j<books.size();j++){
                if(books[i].YearPublished > books[j].YearPublished){
                    swap(books[i], books[j]);
                }
            }
        }
    }
    void sortByISBN(){
        for(int i=0;i<books.size()-1;i++){
            for(int j=i+1;j<books.size();j++){
                if(books[i].ISBN.size() > books[j].ISBN.size()){
                    swap(books[i], books[j]);
                }
                else if(books[i].ISBN.size() == books[j].ISBN.size()) {
                    for(int k=0;k<books[i].AuthorNames.size();k++){
                        if(books[i].ISBN[k] < books[j].ISBN[k])break;
                        if(books[i].ISBN[k] > books[j].ISBN[k]){
                            swap(books[i],books[j]);
                            break;
                        }
                    }
                }
            }
        }
    }
    void sortByPublisher(){
        for(int i=0;i<books.size()-1;i++){
            for(int j=i+1;j<books.size();j++){
                if(books[i].Publisher > books[j].Publisher){
                    swap(books[i], books[j]);
                }
            }
        }
    }
    void sortByLLC(){
        for(int i=0;i<books.size()-1;i++){
            for(int j=i+1;j<books.size();j++){
                if(books[i].LLC > books[j].LLC){
                    swap(books[i], books[j]);
                }
            }
        }
    }
    void issue(string isbn){
        bool found = false;
        for(int i=0;i<books.size();i++){
            if(found)break;
            Book target = books[i];
            for(int j=0;j<target.ISBN.size();j++){
                string s2 = target.ISBN[j];
                if(isbn == s2){
                    found = true;
                    cout<<"Found:";
                    target.print();
                    cout<<"Do you want to issue this book? (Y|N)";
                    char ans;
                    cin>>ans;
                    if(ans == 'Y' || ans == 'y'){
                        books[i].issue();
                        break;
                    }
                }
            }
        }
        if(!found)cout<<"No results!\n";
    }
    void Return(string isbn){
        bool found = false;
        for(int i=0;i<books.size();i++){
            if(found)break;
            Book target = books[i];
            for(int j=0;j<target.ISBN.size();j++){
                string s2 = target.ISBN[j];
                if(isbn == s2){
                    found = true;
                    cout<<"Found:";
                    target.print();
                    cout<<"Do you want to return this book? (Y|N)";
                    char ans;
                    cin>>ans;
                    if(ans == 'Y' || ans == 'y'){
                        books[i].Return();
                        break;
                    }
                }
            }
        }
        if(!found)cout<<"No results!\n";
    }
    void printAll(){
        cin.ignore();
        for(int i=0;i<books.size();i++){
            books[i].print();

            cout<<"Press Enter to continue...";
            char any = getchar();
        }
    }
};

Library mainLibrary;


void parse_document(string filepath){
    fstream file(filepath);
    string s;
    getline(file,s);
    while(getline(file,s)){
        string tempName;
        string tempTitle="";
        string tempYear="";
        vector<string> tempISBN;
        string tempPublisher="";
        string tempLLC="";
        int tempInstock=0;
        bool q=false;
        string s1="";
        int order=-1;
        for(int i=0;i<s.size();i++){
            if(s[i]=='"'){
                if(q){
                    if(order == 1)tempName = s1;
                    if(order == 2)tempTitle = s1;
                    if(order == 3){
                        if(s1.size()>4){
                            s1 = s1.erase(0,1);
                        }
                        tempYear = s1;
                    }

                    if(order == 4){
                        string isbn="";
                        for(int j=0;j<s1.size();j++){
                            if(s1[j]==','){
                                tempISBN.push_back(isbn);
                                isbn="";
                                j++;
                            }
                            else {
                                isbn += s1[j];
                            }
                            if(j+1==s1.size()){
                                tempISBN.push_back(isbn);
                                isbn="";
                            }
                        }
                    }
                    if(order == 5)tempPublisher = s1;
                    if(order == 6)tempLLC = s1;

                    s1="";
                    q = false;
                }
                else {
                    q = true;
                    order ++;
                }
            }
            else {
                if(q || order == 6)s1 += s[i];//Потому что инсток не в кавычках и поэтому он не читает его. Тут ордер равен шести чтобы брать последние элементы в строке.
            }
        }
        //удалил первый элемент с строки потому что это запятая.
        s1.erase(0,1);
        //здесь уже идет конвертация строки в число
        for(int i=0;i<s1.size();i++){
            tempInstock *= 10;
            tempInstock += s1[i]-'0';
        }
        Book temp(tempName, tempTitle, tempYear, tempISBN, tempPublisher, tempLLC, tempInstock);
        mainLibrary.add(temp);
    }
}

int main(){
    parse_document("lmsdb.csv");
    cout<<"Welcome!\n";
    while(1){
        cout<<"\n\nChoose an option:\n";
        cout<<"(1) Add/delete/modify books\n";
        cout<<"(2) Search for a book\n";
        cout<<"(3) Sort books\n";
        cout<<"(4) Issue a book\n";
        cout<<"(5) Return a book\n";
        cout<<"(6) Exit\n";
        cout<<"(7) To print all books in library\n";
        char temp;
        cin>>temp;
        if(temp == '1'){
            cout<<"(1) to add a book\n";
            cout<<"(2) to delete a book\n";
            cout<<"(3) to modify a book\n";
            char option;
            cin>>option;
            if(option == '1'){
                string tempName;
                string tempTitle="";
                string tempYear="";
                vector<string> tempISBN;
                string tempPublisher="";
                string tempLLC="";
                int tempInstock=0;
                //author names
                cout<<"Author's name :\n";
                string name;
                cin>>name;
                tempName = name;
                //title of the book
                cin.ignore();
                cout<<"Title of the book: \n";
                string title;
                while(1){
                    char c = getchar();
                    if(c==10)break;
                    title += c;
                }
                tempTitle = title;
                //year of publish
                string YearPublished;
                cout<<"Year of publishing:\n";
                cin>>YearPublished;
                tempYear = YearPublished;
                //ISBN numbers
                cout<<"How many ISBN has this book?\n";
                int numberOfISBN;
                cin>>numberOfISBN;
                for(int i=0;i<numberOfISBN;i++){
                    cout<<"ISBN # "<<i+1<<" :";
                    string isbn;
                    cin>>isbn;
                    tempISBN.push_back(isbn);
                    cout<<endl;
                }
                //publisher
                cin.ignore();
                cout<<"Publisher: \n";
                string publisher;
                while(1){
                    char c = getchar();
                    if(c==10)break;
                    publisher += c;
                }
                tempPublisher = publisher;
                //LLC number
                string LLC;
                cout<<"LLC:\n";
                cin>>LLC;
                tempLLC = LLC;
                //in stock amount
                int InStock;
                cout<<"How many in stock?\n";
                cin>>InStock;
                tempInstock = InStock;

                //confirmation of adding
                Book New(tempName, tempTitle, tempYear, tempISBN, tempPublisher, tempLLC, tempInstock);
                cout<<"Book to be added:\n";
                New.print();
                cout<<"Add this book? (Y|N)";
                char ans;
                cin>>ans;
                if(ans == 'Y'||ans == 'y')mainLibrary.add(New);
                else cout<<"discard operation.";

                cin.ignore();
                cout<<"Press Enter to continue...";
                char any = getchar();
            }
            if(option == '2'){
                cout<<"Enter ISBN of the book to delete: ";
                string isbn;
                cin>>isbn;
                mainLibrary.remove(isbn);
                cin.ignore();
                cout<<"Press Enter to continue...";
                char any = getchar();
            }
            if(option == '3'){
                cout<<"Enter ISBN of the book to modify: ";
                string isbn;
                cin>>isbn;
                int pos = -1;
                for(int i=0;i<mainLibrary.books.size();i++){
                    Book temp = mainLibrary.books[i];
                    for(int j=0;j<temp.ISBN.size();j++){
                        if(temp.ISBN[j]==isbn){
                            temp.print();
                            pos = i;
                        }
                    }
                }
                if(pos == -1){
                    cout<<"No results!"<<endl;
                }
                else {
                    cout<<"Do you want to modify this book? (Y|N):";
                    char ans;
                    cin>>ans;
                    if(ans == 'Y' || ans == 'y'){
                        while(1){
                            cout<<"Modify: \n";
                            cout<<"(1) Author name(s)\n";
                            cout<<"(2) Title\n";
                            cout<<"(3) Year of publish\n";
                            cout<<"(4) ISBN\n";
                            cout<<"(5) Publisher\n";
                            cout<<"(6) LLC\n";
                            cout<<"(7) In stock\n";
                            int choice;
                            cin>>choice;
                            if(choice==1){
                                mainLibrary.books[pos].AuthorNames = "";
                                cout<<"Author's name: \n";
                                string name;
                                cin>>name;
                                mainLibrary.books[pos].AuthorNames = name;
                            }
                            if(choice==2){
                                cout<<"Title of the book: \n";
                                string title;
                                cin.ignore();
                                while(1){
                                    char c = getchar();
                                    if(c==10)break;
                                    title += c;
                                }
                                mainLibrary.books[pos].BookTitle = title;
                            }
                            if(choice==3){
                                cout<<"Year of publishing:\n";
                                string YearPublished;
                                cin>>YearPublished;
                                mainLibrary.books[pos].YearPublished = YearPublished;
                            }
                            if(choice==4){
                                mainLibrary.books[pos].ISBN.clear();
                                cout<<"How many ISBN has this book?\n";
                                int numberOfISBN;
                                cin>>numberOfISBN;
                                for(int i=0;i<numberOfISBN;i++){
                                    cout<<"ISBN # "<<i+1<<" :";
                                    string isbn;
                                    cin>>isbn;
                                    mainLibrary.books[pos].ISBN.push_back(isbn);
                                }
                            }
                            if(choice==5){
                                cin.ignore();
                                cout<<"Publisher: \n";
                                string publisher;
                                while(1){
                                    char c = getchar();
                                    if(c==10)break;
                                    publisher += c;
                                }
                               mainLibrary.books[pos].Publisher = publisher;
                            }
                            if(choice==6){
                                cout<<"LLC:\n";
                                string LLC;
                                cin>>LLC;
                                mainLibrary.books[pos].LLC = LLC;
                            }
                            if(choice==7){
                                cout<<"How many in stock?\n";
                                int InStock;
                                cin>>InStock;
                                mainLibrary.books[pos].InStock = InStock;
                            }
                            cout<<"Do you want to continue modifying? (Y|N)";
                            char ans1;
                            cin>>ans1;
                            if(ans1 !='Y' && ans1 != 'y')break;
                        }
                        cout<<"Modified version:\n";
                        mainLibrary.books[pos].print();
                    }
                }
                cin.ignore();
                cout<<"Press Enter to continue...";
                char any = getchar();
            }
        }
        if(temp == '2'){
            string tempName;
            string tempTitle="";
            string tempYear="";
            vector<string> tempISBN;
            string tempPublisher="";
            string tempLLC="";
            int tempInstock=0;
            while(1){
                cout<<"Search by (select 1 attribute)\n";
                cout<<"(1) By author name(s)\n";
                cout<<"(2) By book title\n";
                cout<<"(3) By year published\n";
                cout<<"(4) By ISBN number\n";
                cout<<"(5) By publisher\n";
                cout<<"(6) By LLC number\n";
                char ans;
                cin>>ans;
                if(ans=='1'){
                    cout<<"Author's name :\n";
                    string name;
                    cin>>name;
                    tempName = name;
                }
                else if(ans=='2'){
                    cin.ignore();
                    cout<<"Title of the book: \n";
                    string title="";
                    while(1){
                        char c = getchar();
                        if(c==10)break;
                        title += c;
                    }

                    tempTitle = title;
                }
                else if(ans=='3'){
                    string YearPublished;
                    cout<<"Year of publishing:\n";
                    cin>>YearPublished;
                    tempYear = YearPublished;
                }
                else if(ans=='4'){
                    cout<<"ISBN: \n";
                    string isbn;
                    cin>>isbn;
                    tempISBN.push_back(isbn);
                }
                else if(ans=='5'){
                    cin.ignore();
                    cout<<"Publisher: \n";
                    string publisher;
                    while(1){
                        char c = getchar();
                        if(c==10)break;
                        publisher += c;
                    }
                    tempPublisher = publisher;
                }
                else if(ans=='6'){
                    string LLC;
                    cout<<"LLC:\n";
                    cin>>LLC;
                    tempLLC = LLC;
                }
                //else continue;
                char searchAns;
                cout<<"Would you like to add another attribute? (Y|N)";
                cin>>searchAns;
                if(searchAns != 'Y' && searchAns != 'y')break;
            }
            Book New(tempName, tempTitle, tempYear, tempISBN, tempPublisher, tempLLC, tempInstock);
            vector<Book> foundBooks = mainLibrary.search(New);

            cout<<"\nSearch results:";
            cin.ignore();
            for(int i=0;i<foundBooks.size();i++){
                cout<<"\nResult #"<<i+1;
                foundBooks[i].print();
                cout<<"Press Enter to continue...";
                char any = getchar();
            }
        }
        if(temp == '3'){
            cout<<"Sort by (select 1 attribute)\n";
            cout<<"(1) By author name(s)\n";
            cout<<"(2) By book title\n";
            cout<<"(3) By year published\n";
            cout<<"(4) By ISBN number\n";
            cout<<"(5) By publisher\n";
            cout<<"(6) By LLC number\n";
            char ans;
            cin>>ans;
            if(ans=='1'){
                mainLibrary.sortByAuthor();
                cout<<"Books after sorting by author name(s):\n";
                mainLibrary.printAll();
            }
            if(ans=='2'){
                mainLibrary.sortByTitle();
                cout<<"Books after sorting by book's title:\n";
                mainLibrary.printAll();
            }
            if(ans=='3'){
                mainLibrary.sortByYear();
                cout<<"Books after sorting by year of publish:\n";
                mainLibrary.printAll();
            }
            if(ans=='4'){
                mainLibrary.sortByISBN();
                cout<<"Books after sorting by ISBN number:\n";
                mainLibrary.printAll();
            }
            if(ans=='5'){
                mainLibrary.sortByPublisher();
                cout<<"Books after sorting by publisher:\n";
                mainLibrary.printAll();
            }
            if(ans=='6'){
                mainLibrary.sortByLLC();
                cout<<"Books after sorting by LLC number:\n";
                mainLibrary.printAll();
            }
        }
        if(temp == '4'){
            cout<<"Enter ISBN of the book to issue: ";
            string isbn;
            cin>>isbn;
            mainLibrary.issue(isbn);

            cin.ignore();
            cout<<"Press Enter to continue...";
            char any = getchar();
        }
        if(temp == '5'){
            cout<<"Enter ISBN of the book to return: ";
            string isbn;
            cin>>isbn;
            mainLibrary.Return(isbn);

            cin.ignore();
            cout<<"Press Enter to continue...";
            char any = getchar();
        }
        if(temp == '6'){
            cout<<"exit\n";
            break;
        }
        if(temp == '7'){
            mainLibrary.printAll();
        }
    }
}
