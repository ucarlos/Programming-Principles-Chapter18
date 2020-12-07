/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 01/12/2020
 * 
 * Chapter18 Try This
 *     Please execute this.
 *
 *     We really mean it: do run this example and make sure you understand the
 *     result. If you do, you’ll understand most of what there is to know about
 *     construction and destruction of objects.
 *
 *     Addition: View the executable through bash or any shell. CLion's
 *     executable does not place the line breaks correctly.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <new>
#include <vector>
using namespace std;
struct X{
    int val;

    void out(const string &s, int nv){
		cerr << this << "-->" << s << ":" << val
			 << "("  << nv
			 << ")\n";
    }

    X(){out("X()", 0); val = 0;} // default constructor
    X(int v){ val = v; out("X(int)", v);}
    X(const X &x){ val = x.val; out("X(X&) ", x.val);} // Copy constructor
    X& operator=(const X &a){ // Copy Assignment
		out("X::operator=()", a.val);
		val = a.val;
		return *this;
    }

    ~X(){ out ("~X()", 0);} //Destructor

};


X glob(2);
X copy(X a){ return a; }
X copy2(X a){ X aa = a; return aa; }
X& ref_to(X &a) { return a; }
X* make(int i){X a(i); return new X(a);}
struct XX{X a; X b;};


int main(void){
    cerr << "Declaring variables loc and loc2..." << endl;
    X loc{4}; // Local Variable
    X loc2{loc}; // Copy construction
    cerr << endl << "Assigning X{5} to loc" <<  endl;
    loc = X{5};
    
    cerr << endl << "Assigning copy(loc) to loc2" <<  endl;
    loc2 = copy(loc); // Call by value and return
    
    cerr << endl << "Assigning copy2(loc) to loc2" << endl;
    loc2 = copy2(loc);
    
    cerr << endl << "Create loc3 with a value of 6 " << endl;
    X loc3 {6};

    // X &r = ref_to(loc);
    
    cerr << endl <<  "Create using make(7) and delete it..." << endl;
    delete make(7);
    
    cerr << endl << "Create using make(8) and delete it..." << endl;
    delete make(8);
    
    cerr << endl << "Now dealing with Vectors... " << endl;
    cerr << endl << "Creating vector v with four elements of type X " << endl; 
    vector<X> v(4); //default values
    
    
    cerr << endl << "Creating an object of type class XX" << endl;
    XX loc4;
    
    cerr << endl
		 << "Creating a pointer to X and assign it to a X object with value 9..."
		 << endl;
    X *p = new X{9}; // An X on the free store

    cerr << endl << "Now delete the pointer." << endl;
    delete p;
    
    cerr << endl
		 << "Creating a pointer pp of type X and assign it five objects of type X."
		 << endl;
    X *pp = new X[5]; // An array of Xs on the free store
    
    cerr << endl << "Now delete the pointer." << endl;    
    delete[] pp;
    
    cerr << endl <<  "Destroying the rest.." << endl;
    return 0;
}
