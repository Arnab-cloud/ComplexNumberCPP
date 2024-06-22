#include<iostream>
#include<stdexcept>
#include<cmath>

// value of 'tau'
// to convert radian in degree divide with 'tau'
constexpr double pi = 3.14159265358979323846;
constexpr double tau = 2*pi;

// Different Display modes of the complex number
namespace Display
{
    enum Mode
    {
        TUPLE,
        RECT,
        ANGLE,
        POLAR,
        EXP,
        CART
    };
};


// Complex class
template<typename T>
class Complex
{
    private:
    T m_real; // holds the real part
    T m_img; // holds the imaginary part

    public:
    // default constructor
    explicit Complex(const T& real=0.0,const T& img=0.0): m_real{real}, m_img{img} {}

    Complex<T>& operator=(const Complex<T>&); // copy assignment operator
    Complex<T>& operator=(const T& x); // same but directly uses type T
    
    // Addition
    Complex<T> operator+(const Complex<T>& c) const;
    Complex<T> operator+(const T& x) const;
    
    // Subtraction
    Complex<T> operator-(const Complex& c) const;
    Complex<T> operator-(const T& x) const;

    // Multiplication
    Complex<T> operator*(const Complex& c) const;
    Complex<T> operator*(const T& x) const;

    // Division
    Complex<T> operator/(const Complex& c) const;
    Complex<T> operator/(const T& x) const;

    // Add and copy
    Complex<T>& operator+=(const Complex<T>& c);
    Complex<T>& operator+=(const T& x) ;
    
    // Subtract and copy
    Complex<T>& operator-=(const Complex& c);
    Complex<T>& operator-=(const T& x);

    // Multiply and copy
    Complex<T>& operator*=(const Complex& c);
    Complex<T>& operator*=(const T& x);

    // Divide and copy
    Complex<T>& operator/=(const Complex& c);
    Complex<T>& operator/=(const T& x);

    // Returns the conjugate of complex number 'c'
    Complex<T> conjugate(const Complex<T>& c) const;

    // calculates mod or absolute value 
    double mod() const;
    // calculates the phase
    double getPhase() const;

    // calculates a positive integer power of any complex number 
    static Complex<T> power(const Complex<T>& x, const int& n);
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Complex<U>& c);
    void display(const Display::Mode& mode = Display::TUPLE, bool isRed = true) const;
};

template<typename T>
Complex<T>& Complex<T>::operator=(const Complex<T>& c)
{
    m_real = c.m_real;
    m_img  = c.m_img;
    return *this;
}

template<typename T>
Complex<T>&  Complex<T>::operator=(const T& x)
{
    m_real = x;
    m_img = 0;
    return *this;
}

template<typename T>
    Complex<T>  Complex<T>::operator+(const Complex<T>& c) const { return Complex<T>(m_real + c.m_real, m_img + c.m_img); }
template<typename T>
    Complex<T> Complex<T>::operator+(const T& x) const{ return Complex<T>(m_real+x,m_img); }

template<typename T>
    Complex<T> Complex<T>::operator-(const Complex<T>& c) const { return Complex<T>(m_real - c.m_real, m_img - c.m_img); }
template<typename T>
    Complex<T> Complex<T>::operator-(const T& x) const { return Complex<T>(m_real-x,m_img); }

    // Multiplication
template<typename T>
    Complex<T> Complex<T>::operator*(const Complex<T>& c) const { return Complex<T>(m_real*c.m_real - m_img*c.m_img, m_real*c.m_img + m_img*c.m_real); }
template<typename T>
    Complex<T> Complex<T>::operator*(const T& x) const { return Complex<T>(m_real*x, m_img*x); }

    // Division
template<typename T>
Complex<T> Complex<T>::operator/(const Complex<T>& c) const
{
    Complex<T> result;
    if(c.m_real == 0 && c.m_img == 0)
        throw std::invalid_argument("Division by Zero not allowed");
    if(m_real == 0 && m_img == 0)
        return Complex<T>(0,0);
    T m_real1 = c.m_real;
    T m_img1 = c.m_img;
    T deNom = pow(m_real1, 2) + pow(m_img1, 2);
    return Complex<T>((m_real*m_real1 + m_img*m_img1)/deNom, (m_img*m_real1 - m_real*m_img1)/deNom);
}
template<typename T>
Complex<T> Complex<T>::operator/(const T& x) const
{
    if(x==0.0)
        throw std::invalid_argument("Division by Zero not allowed");
    return Complex<T>(m_real/x,m_img/x);
}

template<typename T>
    Complex<T>& Complex<T>::operator+=(const Complex<T>& c) { return *this = *this + c; }
template<typename T>
    Complex<T>& Complex<T>::operator+=(const T& c) { return *this = *this + c; }

template<typename T>
    Complex<T>& Complex<T>::operator-=(const Complex<T>& c) { return *this = *this - c; }
template<typename T>
    Complex<T>& Complex<T>::operator-=(const T& c) { return *this = *this - c; }

template<typename T>
    Complex<T>& Complex<T>::operator*=(const Complex<T>& c) { return *this = *this * c; }
template<typename T>
    Complex<T>& Complex<T>::operator*=(const T& c) { return *this = *this * c; }

template<typename T>
    Complex<T>& Complex<T>::operator/=(const Complex<T>& c) { return *this = *this / c; }    
template<typename T>
    Complex<T>& Complex<T>::operator/=(const T& c) { return *this = *this / c; }

template<typename T>
    Complex<T> Complex<T>::conjugate(const Complex<T>& c) const { return Complex<T>(m_real, -m_img); }
template<typename T>
    double Complex<T>::mod() const { return sqrt(pow(m_real, 2) + pow(m_img, 2)); }
template<typename T>
    double Complex<T>::getPhase() const { return atan2(m_img, m_real); }

template<typename T>
Complex<T> Complex<T>::power(const Complex<T>& x, const int& n)
{
    if(n==0) return Complex<T>(1,0);
    Complex<T> temp = power(x, n/2);
    if(n%2 == 0) return temp * temp;
    return x * temp * temp;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Complex<T>& c) 
{
    os << "Real: " << c.m_real << '\n' << "Img: "<< c.m_img << '\n'; 
    return os;
}

template<typename T>
void Complex<T>::display(const Display::Mode& mode, bool isRed) const
{
    switch(mode)
    {
        case Display::TUPLE:
            std::cout << "(" << m_real << "," << " " << m_img << ")";
            break;
        case Display::RECT:
            std::cout << m_real << " + " << m_img << " i";
        break;
        case Display::ANGLE:
            std::cout << this->mod() << " L ";
            if(isRed)
                std::cout << this->getPhase() << " rad";
            else
                std::cout << this->getPhase()/tau << " deg";  
            break;
        case Display::EXP:
            std::cout << this->mod() << " e^" << "i " << this->getPhase();
            break;
        case Display::CART:
            std::cout << "|z| = " << this->mod() << '\n' << "theta = arg(z) = " << this->getPhase() << " rad";
            break;
        default:
            std::cerr << "Use a valid Display Mode!" << '\n';
    }
    std::cout << '\n';
}

int main()
{
    // std::cout << max(3.0,5.0);
    Complex<double> c1(5, 2);
    Complex<double> c2(4, 5);
/*
    c1.display();
    c2.display();
    c1 += 5;
    c1.display();
    c1 -= 6;
    c1.display();
    c1 *= 7;
    c1.display();
    c1 /= 8;
    c1.display();
    
   c1.display(Display::ANGLE,false);
    Complex<double> c3 = c1 * c1;
    c3 *= c3;
    c3.display(Display::EXP);
    Complex<double>::power(c1,4).display(Display::ANGLE);
    */
    c1.display();
    c1 += 5.2;
    c1.display(Display::ANGLE, false);

    return 0;
}