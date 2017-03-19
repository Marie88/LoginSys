//FATU MARIA 1211B
#include <iostream>
#include <cstring>
#include<cstdlib>
using namespace std;
struct Entry {
    char name[100];
    char nr[30];
    Entry(){}
    Entry(char name[],char nr[]) {
    	strcpy(this->name,name);
        strcpy(this->nr,nr);
    }


    int compare(Entry &other) { //function for comparing two entries, not case sensitive,returns 1 if they need to be ordered
        return strcasecmp(name, other.name)>0;
    }



    void display()
    { cout<<"Name: "<<name<<", "<<"Phone number: "<<nr<<endl;

    }

};

template<typename T> struct list_elem {
    T info;
    list_elem<T> *next, *prev;
};
template <typename T> class LinkedList {
public:
    list_elem<Entry> *pfirst, *plast;
    LinkedList() {
       pfirst = plast = NULL;
    }
    ~LinkedList(){

    }

    void addLast(T x) {
        list_elem<T> *paux;
        paux = new list_elem<T>;
        paux->info = x;

        paux->prev = plast;

        paux->next = NULL;
        if (plast != NULL) plast->next = paux;
        plast = paux;
        if (pfirst == NULL) pfirst = plast;
    }


     void removeLast() {
        list_elem<T> *paux;
        if (plast != NULL) {
            paux = plast->prev;
            if (pfirst == plast) pfirst = NULL;
            delete plast;
            plast = paux;
            if (plast != NULL) plast->next = NULL;
        }
        else cerr << "The list is empty" << endl;
    }

     list_elem<T>* findFirstOccurrence(T x) {
        list_elem<T> *paux;
        paux = pfirst;
        while (paux != NULL) {
            if (stricmp(paux->info.name,x.name)==0&&strcmp(paux->info.nr,x.nr)==0)
                return paux;
            paux = paux->next;
        }
        return NULL;
    }

    void removeFirstOccurrence(T x) {
        list_elem<T> *px;
        px = findFirstOccurrence(x);
        if (px != NULL) {
            if (px->prev != NULL)
                px->prev->next = px->next;
            if (px->next != NULL)
                px->next->prev = px->prev;
            if (px->prev == NULL)
                pfirst = px->next;
            if (px->next == plast)
                plast = px->prev;
            delete px;
        }
    }



    bool isEmpty() {
        return pfirst == plast;
    }


 	void printList() {
		for(list_elem<T> *p = pfirst; p; p = p->next)
        	p->info.display();
  	}

};

class Phonebook{
	LinkedList <Entry> book;
public:
	void print() { book.printList(); }

    void addPers(Entry e){ //adds persons at the end of our list
        book.addLast(e);
    }

    void removePers(Entry e) {
        book.removeFirstOccurrence(e);
    }

    void sortPhonebook() { //uses the principle of Bubble Sort with the aid of the pointers in the LL
		bool changed;
		do {
			changed = false;
			list_elem<Entry> *p = book.pfirst; //
	        while(p && p->next) {//while whe still have elements to compare (we are not at the end of our list)
	        	if(p->info.compare(p->next->info)) { //compares the infpormation of type Entry from two neighbour elements of the list uses compare function from Entry
	        		Entry aux = p->info;
	          		p->info = p->next->info;
	          		p->next->info = aux;
	          		changed = true;
	         	}
				p = p->next;
	        }
        } while(changed);
    }




    Entry getByName(char a[100]) { //retrieves an entry by introducing the name
        list_elem<Entry> *paux;
        paux = book.pfirst;
        while (paux != NULL) {
            if (stricmp(paux->info.name,a)==0)
                return paux->info;
            paux = paux->next;
        }
        cout<<"There is no such name in the adressbook.";
    }

     Entry getNo(char a[30]) { //retrieves an entry by introducing the name
        list_elem<Entry> *paux;
        paux = book.pfirst;
        while (paux != NULL) {
            if (stricmp(paux->info.nr,a)==0)
                return paux->info;
            paux = paux->next;
        }
        cout<<"There is no such name in the adressbook";
    }










};


int main()

{


    cout<<"Introduce the number of people you want to have in the adressbook: ";
    char ns[20],na[100],nr[30];
    cin.getline(ns,20);
    int n=atoi(ns);
   // cin>>n;cout<<endl;
     Entry p1,rem;
     Phonebook ph;


	// Move to the second line.
	//cin >> ws

    for(int i = 1; i <= n; i++) {
    	cout<<"Enter the name of your "<<i <<" entry:"<<endl;
    	cout.flush();
      	cin.getline(p1.name, 100);


      	cout<<"Enter the phoneno of your "<<i <<" entry:"<<endl;

      	cin.getline(p1.nr, 30);
      	cout<<endl;

      	ph.addPers(p1);
    }

    cout<<"Our adressbook without any remove looks like:"<<endl;

    ph.print();
    ph.sortPhonebook();

    cout<<"Our sorted adressbook looks like:"<<endl;
    ph.print();

    cout<<"Choose entry to be deleted:"<<endl;
    cout<<"Name: "; cin.getline(rem.name, 100);
    cout<<endl;
    cout<<"Introduce the name you would like to search: "<<endl;


    cout<<"Number: "; cin.getline(rem.nr, 30);
    ph.removePers(rem);
    cout<<endl;
    cout<<"Our adressbook with a removed entry looks like:"<<endl;
    ph.print();

    cin.getline(na,100);
    ph.getByName(na).display();
    cout<<endl;
    cout<<"Introduce the number you would like to search: "<<endl;
    cin.getline(nr,30);
    ph.getNo(nr).display();



    return 0;
}

