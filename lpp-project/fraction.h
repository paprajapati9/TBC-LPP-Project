#ifndef __fraction_H_INCLUDED__
#define __fraction_H_INCLUDED__

#include <bits/stdc++.h>

class fraction
{
  public:
    int numerator;
    int denominator;

    fraction(int numerator = 0, int denominator = 1){
        simplestForm(numerator, denominator);
        this->numerator = numerator;
        this->denominator = denominator;
    }

    // Function to reduce a fraction to its lowest form
    void simplestForm(int &numerator, int &denominator)
    {
        int d;
        d = std::__gcd(numerator, denominator);
      
        numerator = numerator / d;
        denominator = denominator / d;
    }

    friend std::ostream& operator<< (std::ostream &out, const fraction &frac);

    friend fraction operator + (fraction const &, fraction const &);

    friend fraction operator - (fraction const &, fraction const &);

    friend fraction operator * (fraction const &, fraction const &);

    friend fraction operator / (fraction const &, fraction const &);
};

std::ostream& operator<< (std::ostream &out, const fraction &frac)
{
    // Since operator<< is a friend of the fraction class, we can access fraction's members directly.
    if(frac.denominator > 1)
        out << frac.numerator << "/" << frac.denominator ; // actual output done here
    else 
        out << frac.numerator;

    return out; // return std::ostream so we can chain calls to operator<<
}

//Function to add two fractions
fraction operator + (fraction const &frac1, fraction const &frac2)
{
    int newNumerator = frac1.numerator * frac2.denominator + frac2.numerator * frac1.denominator;
    int newDenomenator = frac1.denominator * frac2.denominator;
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
    int newNumerator = frac1.numerator * frac2.numerator;
    int newDenomenator = frac1.denominator * frac2.denominator;
    return fraction(newNumerator, newDenomenator);
}

//Function to divide two fractions
fraction operator / (fraction const &frac1, fraction const &frac2)
{
    int newNumerator = frac1.numerator * frac2.denominator;
    int newDenomenator = frac1.denominator * frac2.numerator;
    return fraction(newNumerator, newDenomenator);
}

#endif