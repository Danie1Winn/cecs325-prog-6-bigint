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
    BigInt operator++(int);               // post-increment n++
    BigInt operator++();                  // pre-increment ++n
    BigInt operator+(BigInt);             // addition BigInt + BigInt
    BigInt operator-(BigInt);             // subtraction BigInt - BigInt
    BigInt operator-(int);                // subtraction BigInt - int
    BigInt operator*(BigInt);             // multiplication BigInt * BigInt
    BigInt operator/(BigInt);             // division BigInt / BigInt
    BigInt operator%(BigInt);             // modulus BigInt % BigInt

    bool operator>(const BigInt&);
    bool operator<(const BigInt&);
    bool operator>=(const BigInt&);
    bool operator<=(const BigInt&);

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

// BigInt - BigInt
BigInt BigInt::operator-(BigInt other) {
    // Assume *this >= other, otherwise return 0
    BigInt result = *this;

    for (size_t i = 0; i < other.v.size(); i++) {
        result.v[i] -= other.v[i]; // subtract

        // borrow
        if (result.v[i] < 0) {
            result.v[i] += 10;  // add 10
            result.v[i + 1]--;  // borrow from next digit

            // handles if next digit goes negative
            int k = i + 1;
            while (result.v[k] < 0) {
                result.v[k] += 10;
                result.v[k + 1]--;
                k++;
            }
        }
    }
    // cleanup leading zeros
    while (result.v.size() > 1 && result.v.back() == 0) {
        result.v.pop_back();
    }
    return result;
}

// BigInt - int
BigInt BigInt::operator-(int n) {
    return *this - BigInt(n);
}

// BigInt * BigInt
BigInt BigInt::operator*(BigInt op2) {
    BigInt product;
    product.v.clear();

    product.v.resize(this->v.size() + op2.v.size(), 0); // initialize with zeros

    for (size_t i = 0; i < this->v.size(); i++) {
        int carry = 0;
        for (size_t j = 0; j < op2.v.size() || carry > 0; j++) {  
            // current product + existing value + carry
            int s2_digit = (j < op2.v.size()) ? op2.v[j] : 0;

            long long current = product.v[i + j] + (this->v[i] * s2_digit) + carry;

            product.v[i + j] = current % 10; // store ones place
            carry = current / 10;            // update carry
        }
    }
    // cleanup leading zeros
    while (product.v.size() > 1 && product.v.back() == 0) {
        product.v.pop_back();
    }
    return product;
}

// BigInt / BigInt
BigInt BigInt::operator/(BigInt divisor) {
    if (divisor.v.size() == 1 && divisor.v[0] == 0) {
        cout << "Cannot divide by zero." << endl;
        return BigInt(0);
    }
    if (*this < divisor) {
        return BigInt(0);
    }

    BigInt quotient;
    quotient.v.clear();     // clears 0

    BigInt remainder(0);

    // iterate from end of the vector to 0
    for (int i = this->v.size() - 1; i >= 0; i--) {
        // multiply remainder by 10
        if (remainder.v.size() == 1 && remainder.v[0] == 0) {
        } else {
            BigInt ten(10);
            remainder = remainder * ten;
        }

        // add current
        BigInt currentDigit(this->v[i]);
        remainder = remainder + currentDigit;

        int count = 0;
        while (remainder >= divisor) {
            remainder = remainder - divisor;
            count++;
        }
        // push count to quotient
        quotient.v.push_back(count);
    }

    // 
    int left = 0;
    int right = quotient.v.size() - 1;
    while (left < right) {
        char temp = quotient.v[left];
        quotient.v[left] = quotient.v[right];
        quotient.v[right] = temp;
        left++;
        right--;
    }

    // cleanup leading zeros
    while (quotient.v.size() > 1 && quotient.v.back() == 0) {
        quotient.v.pop_back();
    }
    return quotient;    
}

// BigInt % BigInt
BigInt BigInt::operator%(BigInt divisor) {
    if (divisor.v.size() == 1 && divisor.v[0] == 0) {
        cout << "Cannot divide by zero." << endl;
        return BigInt(0);
    }
    if (*this < divisor) {
        return *this;
    }

    BigInt remainder(0);

    // iterate from end of the vector to 0
    for (int i = this->v.size() -1; i >= 0; i--) {
        if (!(remainder.v.size() == 1 && remainder.v[0] == 0)) {
            BigInt ten(10);
            remainder = remainder * ten;
        }

        BigInt currentDigit(this->v[i]);
        remainder = remainder + currentDigit;

        while (remainder >= divisor) {
            remainder = remainder - divisor;
        }
    }
    return remainder;
}

// BigInt > BigInt
bool BigInt::operator>(const BigInt& other) {
    if (v.size() > other.v.size()) return true;
    if (v.size() < other.v.size()) return false;

    // if same size compares digit by digit
     for (int i = v.size() - 1; i >= 0; i--) {
        if (v[i] > other.v[i]) return true;
        if (v[i] < other.v[i]) return false;
     }
     return false; // if equal
}

// BigInt < BigInt
bool BigInt::operator<(const BigInt& other) {
    if (v.size() < other.v.size()) return true;
    if (v.size() > other.v.size()) return false;

    // if same size compares digit by digit
     for (int i = v.size() - 1; i >= 0; i--) {
        if (v[i] < other.v[i]) return true;
        if (v[i] > other.v[i]) return false;
     }
     return false; // if equal
}

// BigInt >= BigInt
bool BigInt::operator>=(const BigInt& other) {
    return !(*this < other); // not less than
}

// BigInt <= BigInt
bool BigInt::operator<=(const BigInt& other) {
    return !(*this > other); // not greater than
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
    cout << n2 << " / " << n1 << " = " << n2 / n1 << " rem " << n2 % n1 << endl;

    BigInt n3("100000");
    BigInt n4("2");
    cout << n3 << " / " << n4 << " = " << n3 / n4 << endl;

    return 0;
}