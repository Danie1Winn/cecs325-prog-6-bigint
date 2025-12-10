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

    // Operators
    bool operator==(const BigInt&);     
    BigInt operator++(int);                // post-increment n++
    BigInt operator++();                   // pre-increment ++n
    BigInt operator+(BigInt);              // addition BigInt + BigInt

    // Friend functions
    friend BigInt operator+(int, BigInt);  // addition int + BigInt
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

// Operator implementations
bool BigInt::operator==(const BigInt& other) {
    if (v.size() != other.v.size()) {
        return false;
    }
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] != other.v[i]) {
            return false;
        }
    }
    return true;
}

// Pre-increment
BigInt BigInt::operator++() {
    int i = 0;
    v[i]++;
    
    while (v[i] > 9) {
        v[i] = 0;
        i++;

        if (i == v.size()) {
            v.push_back(0);
        }
        v[i]++;
    }
    return *this;
}

// Post-increment
BigInt BigInt::operator++(int) {
    BigInt temp = *this; // Saves current state
    ++(*this);          // Calls pre-increment
    return temp;        // Returns saved state
}

// BigInt + BigInt
BigInt BigInt::operator+(BigInt op2) {
    BigInt sum;
    sum.v.clear(); // Clear initial 0

    int carry = 0;
    size_t i = 0; // Counts index

    // Loops while digits are in either number or carry exists
    while (i < this->v.size() || i < op2.v.size() || carry > 0) {
        // grab digit from first num
        int num1 =  (i < this->v.size()) ? this->v[i] : 0;

        // grab digit from second num
        int num2 = (i < op2.v.size()) ? op2.v[i] : 0;

        // add
        int total = num1 + num2 + carry;

        // store ones place digit
        sum.v.push_back(total % 10);

        // update carry
        carry = total / 10;

        i++;
    }
    return sum;
}

// int + BigInt
BigInt operator+(int n, BigInt b) {
    return b + BigInt(n);
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
    BigInt n2(1234);
    BigInt maxInt(2147483647);

    cout << "n1 + n2 = " << n1 + n2 << endl;
    cout << "10 + n1 = " << 10 + n1 << endl;

    BigInt nine(99);
    cout << "99 + 1  = " << nine + BigInt(1) << endl;
    
    cout << "maxInt + maxInt = " << maxInt + maxInt << endl;

    return 0;
}