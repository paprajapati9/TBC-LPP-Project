#ifndef __fraction_H_INCLUDED__
#define __fraction_H_INCLUDED__

#include <iostream>

/**
 * Fraction data type class
 */
class fraction
{
    public:
    double numerator;
    double denominator;

    //constructor
    fraction(double numerator = 0, double denominator = 1){
        simplestForm(numerator, denominator);
        this->numerator = numerator;
        this->denominator = denominator;
    }

    int gcd(int a, int b){
        if (b == 0)
            return a;
        return gcd(b, a % b);  
    }

    // Function to reduce a fraction to its lowest form
    void simplestForm(double &numerator, double &denominator)
    {
        double d, num = numerator, den = denominator;
        //in case of calculation gcd of negative numbers, it gives wrong answers
        //for negative numbers, so making it temperorily positive
        if(num < 0) num *= -1;
        if(den < 0) den *= -1;
        d = gcd((int)num, (int)den);
      
        numerator = numerator / d;
        denominator = denominator / d;
    }

    friend std::ostream& operator<< (std::ostream &out, const fraction &frac);

    friend fraction operator + (fraction const &, fraction const &);

    friend fraction operator - (fraction const &, fraction const &);

    friend fraction operator * (fraction const &, fraction const &);

    friend fraction operator / (fraction const &, fraction const &);

    friend bool operator < (fraction const &, fraction const &);

    friend bool operator > (fraction const &, fraction const &);

    friend bool operator == (fraction const &, fraction const &);
};

std::ostream& operator<< (std::ostream &out, const fraction &frac)
{
    // Since operator<< is a friend of the fraction class, we can access fraction's members directly.
    if(frac.numerator == -0) out << 0;
    else if(frac.denominator > 1)
        {
            out<<(std::to_string((int)frac.numerator) + "/" + std::to_string((int)frac.denominator));
        }
    else 
        out << frac.numerator;

    return out; // return std::ostream so we can chain calls to operator<<
}

//Function to add two fractions
fraction operator + (fraction const &frac1, fraction const &frac2)
{
    double newNumerator = frac1.numerator * frac2.denominator + frac2.numerator * frac1.denominator;
    double newDenomenator = frac1.denominator * frac2.denominator;
    return fraction(newNumerator, newDenomenator);
}

//Function to subtract two fractions
fraction operator - (fraction const &frac1, fraction const &frac2)
{
    int newNumerator = frac1.numerator * frac2.denominator - frac2.numerator * frac1.denominator;
    int newDenomenator = frac1.denominator * frac2.denominator;
    return fraction(newNumerator, newDenomenator);
}

//Function to multiply two fractions
fraction operator * (fraction const &frac1, fraction const &frac2)
{
    double newNumerator = frac1.numerator * frac2.numerator;
    double newDenomenator = frac1.denominator * frac2.denominator;
    return fraction(newNumerator, newDenomenator);
}

//Function to divide two fractions
fraction operator / (fraction const &frac1, fraction const &frac2)
{
    double newNumerator = frac1.numerator * frac2.denominator;
    double newDenomenator = frac1.denominator * frac2.numerator;
    return fraction(newNumerator, newDenomenator);
}

//Function to compare < in two fractions
bool operator < (fraction const &frac1, fraction const &frac2)
{
    double n1 = frac1.numerator / frac1.denominator;
    double n2 = frac2.numerator / frac2.denominator;
    if(n1 < n2) return 1;
    else return 0;
}

//Function to compare > in two fractions
bool operator > (fraction const &frac1, fraction const &frac2)
{
    double n1 = frac1.numerator / frac1.denominator;
    double n2 = frac2.numerator / frac2.denominator;
    if(n1 > n2) return 1;
    else return 0;
}

//Function to compare == in two fractions
bool operator == (fraction const &frac1, fraction const &frac2)
{
    fraction n1 = fraction(frac1.numerator, frac1.denominator);
    fraction n2 = fraction(frac2.numerator, frac2.denominator);
    if(n1.numerator == n2.numerator && n1.denominator == n2.denominator) return 1;
    else return 0;
}

//Function to compare != in two fractions
bool operator != (fraction const &frac1, fraction const &frac2)
{
    fraction n1 = fraction(frac1.numerator, frac1.denominator);
    fraction n2 = fraction(frac2.numerator, frac2.denominator);
    if(n1.numerator != n2.numerator || n1.denominator != n2.denominator) return 1;
    else return 0;
}

#endif