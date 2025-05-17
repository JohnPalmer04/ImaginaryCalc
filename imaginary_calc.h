#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <vector>
#include <stdexcept>

class ImaginaryNumber
{
public:
    // Constructors

    ImaginaryNumber(double r, double i);

    ImaginaryNumber();

    // Getters and setters

    double get_real() const;

    double get_imaginary() const;

    void set_real(int new_real);

    void set_imaginary(int new_imaginary);

    // Overloaded operators

    friend std::ostream &operator<<(std::ostream &os, const ImaginaryNumber &num);

    ImaginaryNumber operator+(const ImaginaryNumber &otherNum) const;

    ImaginaryNumber operator-(const ImaginaryNumber &otherNum) const;

    ImaginaryNumber operator-() const;

    ImaginaryNumber operator*(const ImaginaryNumber &otherNum) const;

    ImaginaryNumber operator/(const ImaginaryNumber &otherNum) const;

    bool operator==(const ImaginaryNumber &other) const;

    bool operator!=(const ImaginaryNumber &other) const;

    // Imaginary Number Operations

    // Gets the conjugate of a complex number (a+bi -> a-bi)
    ImaginaryNumber get_conjugate() const;

    // Gets the length of a complex number in the complex plane
    double magnitude() const;

    // Gets the angle between the complex number and positive real axis
    double argument() const;

    // Gets the magnitude of the imaginary number sqaured
    double abs_squared() const;

    // Returns the parts of the polar form of an imaginary number
    void to_polar(double &r, double &theta) const;

    // Uses De Moivre's Theorem to exponentiate a complex number
    ImaginaryNumber pow(int n) const;

private:
    // Member variables

    double real_part;

    double imaginary_part;
};

// Uses the magnitude and argument of an imaginary number to get the Cartesian form
static ImaginaryNumber from_polar(double r, double theta);

// Helper function for the main method to make an imaginary number from the input string
ImaginaryNumber parse_imaginary_number(std::string imaginaryNum);
