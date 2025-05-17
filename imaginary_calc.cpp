#include "imaginary_calc.h"

ImaginaryNumber::ImaginaryNumber(double r, double i) : real_part(r), imaginary_part(i) {}

ImaginaryNumber::ImaginaryNumber() : real_part(0.0), imaginary_part(1.0) {}

double ImaginaryNumber::get_real() const
{
    return real_part;
}

double ImaginaryNumber::get_imaginary() const
{
    return imaginary_part;
}

void ImaginaryNumber::set_real(int new_real)
{
    real_part = new_real;
}

void ImaginaryNumber::set_imaginary(int new_imaginary)
{
    imaginary_part = new_imaginary;
}

ImaginaryNumber ImaginaryNumber::operator+(const ImaginaryNumber &otherNum) const
{
    return ImaginaryNumber(real_part + otherNum.real_part, imaginary_part + otherNum.imaginary_part);
}

ImaginaryNumber ImaginaryNumber::operator*(const ImaginaryNumber &otherNum) const
{
    double new_real_part = (real_part * otherNum.real_part) - (imaginary_part * otherNum.imaginary_part);
    double new_imaginary_part = (real_part * otherNum.imaginary_part) + (imaginary_part * otherNum.real_part);
    return ImaginaryNumber(new_real_part, new_imaginary_part);
}

ImaginaryNumber ImaginaryNumber::operator-(const ImaginaryNumber &otherNum) const
{
    return ImaginaryNumber(real_part - otherNum.real_part, imaginary_part - otherNum.imaginary_part);
}

ImaginaryNumber ImaginaryNumber::get_conjugate() const
{
    return ImaginaryNumber(real_part, -imaginary_part);
}

ImaginaryNumber ImaginaryNumber::operator/(const ImaginaryNumber &otherNum) const
{
    ImaginaryNumber new_numerator = (*this) * otherNum.get_conjugate();
    ImaginaryNumber new_denominator = otherNum * otherNum.get_conjugate();
    double real_denom = new_denominator.real_part;
    return ImaginaryNumber(new_numerator.real_part / real_denom, new_numerator.imaginary_part / real_denom);
}

double ImaginaryNumber::magnitude() const
{
    double a = real_part;
    double b = imaginary_part;
    return std::sqrt(a * a + b * b);
}

double ImaginaryNumber::argument() const
{
    return std::atan2(imaginary_part, real_part);
}

double ImaginaryNumber::abs_squared() const
{
    return (real_part * real_part + imaginary_part * imaginary_part);
}

void ImaginaryNumber::to_polar(double &r, double &theta) const
{
    r = magnitude();
    theta = argument();
}

bool ImaginaryNumber::operator==(const ImaginaryNumber &other) const
{
    return real_part == other.real_part && imaginary_part == other.imaginary_part;
}

bool ImaginaryNumber::operator!=(const ImaginaryNumber &other) const
{
    return real_part != other.real_part || imaginary_part != other.imaginary_part;
}

ImaginaryNumber ImaginaryNumber::operator-() const
{
    return ImaginaryNumber(-real_part, -imaginary_part);
}

ImaginaryNumber ImaginaryNumber::pow(int n) const
{
    double r = magnitude();
    double theta = argument();
    double r_to_n = std::pow(r, n);
    double real = r_to_n * (std::cos(n * theta));
    double imag = r_to_n * (std::sin(n * theta));
    return ImaginaryNumber(real, imag);
}

static ImaginaryNumber from_polar(double r, double theta)
{
    return ImaginaryNumber(r * std::cos(theta), r * std::sin(theta));
}

std::ostream &operator<<(std::ostream &os, const ImaginaryNumber &num)
{
    os << num.real_part;
    if (num.imaginary_part < 0)
    {
        os << "-" << (-1 * num.imaginary_part) << "i";
    }
    else
    {
        os << "+" << num.imaginary_part << "i";
    }
    return os;
}

ImaginaryNumber parse_imaginary_number(std::string imaginaryNum)
{
    size_t plus_loc = imaginaryNum.find('+');
    size_t minus_loc = imaginaryNum.find('-', 1);
    size_t sign_loc;
    if (plus_loc != std::string::npos)
    {
        sign_loc = plus_loc;
    }
    else
    {
        sign_loc = minus_loc;
    }
    if (sign_loc == std::string::npos)
    {
        throw std::invalid_argument("Missing + or - for form of a+bi or a-bi");
    }
    std::string real = imaginaryNum.substr(0, sign_loc);
    std::string imag = imaginaryNum.substr(sign_loc, imaginaryNum.length() - sign_loc);
    if (imag.back() == 'i')
    {
        imag.pop_back();
    }
    double real_dbl = std::stod(real);
    double imag_dbl = std::stod(imag);
    return ImaginaryNumber(real_dbl, imag_dbl);
}

void print_help()
{
    std::cout << "This program is a calculator that can perform functions on complex numbers.\nFor any complex number in the form a+bi where a and b are real numbers:" << std::endl;

    std::cout << "a+bi + c+di     -> sum" << std::endl;
    std::cout << "a+bi - c+di     -> difference" << std::endl;
    std::cout << "a+bi * c+di     -> product" << std::endl;
    std::cout << "a+bi / c+di     -> quotient" << std::endl;
    std::cout << "a+bi == c+di    -> equality" << std::endl;
    std::cout << "a+bi != c+di    -> inequality" << std::endl;
    std::cout << "- a+bi          -> negation" << std::endl;
    std::cout << "conj a+bi       -> conjugate" << std::endl;
    std::cout << "mag a+bi        -> magnitude" << std::endl;
    std::cout << "arg a+bi        -> angle (argument)" << std::endl;
    std::cout << "abs_sqd a+bi    -> magnitude squared" << std::endl;
    std::cout << "to_plr a+bi     -> polar form" << std::endl;
    std::cout << "pow e a+bi      -> raise to integer power" << std::endl;
    std::cout << "frm_plr r theta -> Cartesian from polar (r, theta)" << std::endl;
    std::cout << "Use '<' in place of an imaginary number to use previous answer" << std::endl;
}

int main()
{
    bool running_flag = true;
    ImaginaryNumber num1;
    ImaginaryNumber num2;
    ImaginaryNumber ans;
    std::cout << "IMAGINARY NUMBER CALCULATOR\nEnter HELP for overview of options\nEnter QUIT to stop program" << std::endl;
    while (running_flag)
    {
        std::string user_input;
        std::vector<std::string> user_vector;
        std::getline(std::cin, user_input);
        std::stringstream ss(user_input);
        std::string item;
        char delimiter = ' ';

        while (getline(ss, item, delimiter))
        {
            if (!item.empty())
            {
                user_vector.push_back(item);
            }
        }

        size_t vector_size = user_vector.size();

        if (vector_size == 1)
        {
            if (user_vector[0] == "HELP")
            {
                print_help();
            }
            else if (user_vector[0] == "QUIT")
            {
                std::cout << "Program exited" << std::endl;
                running_flag = false;
            }
            else
            {
                std::cout << "Invalid argument, expected HELP or QUIT" << std::endl;
            }
        }
        else if (vector_size == 2)
        {
            if (user_vector[1] == "<")
            {
                num1 = ans;
            }
            else
            {
                try
                {
                    num1 = parse_imaginary_number(user_vector[1]);
                }
                catch (const std::invalid_argument e)
                {
                    std::cerr << "ERROR: " << e.what() << std::endl;
                    continue;
                }
            }
            std::string func = user_vector[0];
            if (func == "-")
            {
                ans = -num1;
                std::cout << ans << std::endl;
            }
            else if (func == "conj")
            {
                ans = num1.get_conjugate();
                std::cout << ans << std::endl;
            }
            else if (func == "mag")
            {
                std::cout << num1.magnitude() << std::endl;
            }
            else if (func == "arg")
            {
                std::cout << num1.argument() << std::endl;
            }
            else if (func == "abs_sqd")
            {
                std::cout << num1.abs_squared() << std::endl;
            }
            else if (func == "to_plr")
            {
                double r;
                double theta;
                num1.to_polar(r, theta);
                std::cout << r << "(cos(" << theta << ") + isin(" << theta << "))" << std::endl;
            }
            else
            {
                std::cout << "Improper function entered" << std::endl;
            }
        }
        else if (vector_size == 3)
        {
            std::string first_arg = user_vector[0];
            if (first_arg == "pow")
            {
                int exponent = stoi(user_vector[1]);
                if (user_vector[2] == "<")
                {
                    num1 = ans;
                }
                else
                {
                    num1 = parse_imaginary_number(user_vector[2]);
                }
                ans = num1.pow(exponent);
                std::cout << ans << std::endl;
            }
            else if (first_arg == "frm_plr")
            {
                double r = stod(user_vector[1]);
                double theta = stod(user_vector[2]);
                num1 = from_polar(r, theta);
                std::cout << num1 << std::endl;
            }
            else
            {
                if (user_vector[0] == "<")
                {
                    num1 = ans;
                }
                else
                {
                    try
                    {
                        num1 = parse_imaginary_number(user_vector[0]);
                    }
                    catch (const std::invalid_argument e)
                    {
                        std::cerr << "FIRST NUM ENTERED INCORRECTLY: " << e.what() << std::endl;
                        continue;
                    }
                }
                if (user_vector[2] == "<")
                {
                    num2 = ans;
                }
                else
                {
                    try
                    {
                        num2 = parse_imaginary_number(user_vector[2]);
                    }
                    catch (const std::invalid_argument e)
                    {
                        std::cerr << "SECOND NUM ENTERED INCORRECTLY: " << e.what() << std::endl;
                        continue;
                    }
                }
                std::string func = user_vector[1];
                if (func == "+")
                {
                    ans = num1 + num2;
                    std::cout << ans << std::endl;
                }
                else if (func == "-")
                {
                    ans = num1 - num2;
                    std::cout << ans << std::endl;
                }
                else if (func == "*")
                {
                    ans = num1 * num2;
                    std::cout << ans << std::endl;
                }
                else if (func == "/")
                {
                    ans = num1 / num2;
                    std::cout << ans << std::endl;
                }
                else if (func == "==")
                {
                    int truth_val = (num1 == num2);
                    std::string truth_string;
                    if (truth_val)
                    {
                        truth_string = "True";
                    }
                    else
                    {
                        truth_string = "False";
                    }
                    std::cout << truth_string << std::endl;
                }
                else if (func == "!=")
                {
                    int truth_val = (num1 != num2);
                    std::string truth_string;
                    if (truth_val)
                    {
                        truth_string = "True";
                    }
                    else
                    {
                        truth_string = "False";
                    }
                    std::cout << truth_string << std::endl;
                }
                else
                {
                    std::cout << "Argument entered incorrectly" << std::endl;
                }
            }
        }
        else
        {
            std::cout << "Invalid argument, expected 1, 2, or 3 arguments" << std::endl;
        }
    }
    return 0;
}