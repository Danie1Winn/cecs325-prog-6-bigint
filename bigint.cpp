class BigInt {
private:
    vector<char> v; //<- notice this is a vector of char, not int
public:
    BigInt();
    BigInt(int);
    BigInt(string);
    
    BigInt operator+ (BigInt);
    BigInt operator- (BigInt);
    BigInt operator– (int);
    BigInt operator* (BigInt);
    
    BigInt operator/ (BigInt);
    BigInt operator% (BigInt);
    BigInt operator++(int);
    BigInt operator++( );
    BigInt operator[](int); // index function
    
    int size();
    void print();
    BigInt fibo( ); // Fibonacci of current number
    BigInt fact( ); // Factorial of current number
    BigInt collatz(bool);   // prints Collatz sequence – returns number of steps
                            // Accepts a bool: true means print the steps
    friend BigInt operator+ (int, BigInt);
    friend ostream& operator<<(ostream&, const BigInt&);
};