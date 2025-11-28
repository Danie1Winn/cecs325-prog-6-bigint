// Name: Daniel Winn
// Class (CECS 325-02)
// Project Name (Prog 6 – Big Integer)
// Due Date 12/09/2025
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include <vector>
#include <string> 

// No namespace std allowed
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ostream;

class BigInt {
private:
    vector<char> v; //<- notice this is a vector of char, not int

public:
    BigInt();
    BigInt(int);
    BigInt(string);

    // Member functions
    int size() const;
    void print(); // Print digits

    // Friend functions
    friend ostream& operator<<(ostream&, const BigInt&);
};

// Constructors
// Default (initialize 0)
BigInt::BigInt() {
    v.push_back(0);
}

// Int constructor, int into digits
BigInt::BigInt(int n) {
    if (n == 0) {
        v.push_back(0);
    } else {
        while (n > 0) {
            v.push_back(n % 10); // Stores the last digit
            n /= 10; // Removes the last digit
        }
    }
}

// String constructor, string into digits
BigInt::BigInt(string s) {
    int len = (int)s.length();
    for (int i = len - 1; i >= 0; i--) {
        v.push_back(s[i] - '0');
    }
}

// Helpers

// Return number of digits
int BigInt::size() const {
    return v.size();
}

// Print digits (debugging)
void BigInt::print() {
    for (int i = v.size() - 1; i >= 0; --i) {
        cout << (int)v[i];
    }
}

// Friend implementations

// ostream operator
ostream& operator<<(ostream& out, const BigInt& b) {
    // Assignment requirement: If size > 12, print in scientific notation

    if (b.v.size() > 12) {
        for (int i = b.v.size() - 1; i >= 0; i--) {
            out << (int)b.v[i];
        }
    } else {
        // Print normally
        for (int i = b.v.size() - 1; i >= 0; i--) {
            out << (int)b.v[i];
        }
    }
    return out;
}

// Testing
int main() {
    BigInt n1(25);
    BigInt s1("25");
    BigInt n2(1234);
    BigInt s2("1234");
    BigInt empty;

    cout << "n1(int): " << n1 << endl;
    cout << "s1(str): " << s1 << endl;
    cout << "n2(int): " << n2 << endl;
    cout << "s2(str): " << s2 << endl;
    cout << "empty(): " << empty << endl;

    cout << "Print method: ";
    n2.print();
    cout << endl;

    return 0;
}