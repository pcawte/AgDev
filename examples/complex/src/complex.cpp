/*
 * Title:			C++ complex number example
 * Author:			Paul Cawte
 * Created:			30/06/2022
 *
 * Modinfo:
 */
 
#include <stdio.h>

class complex {
    double re, im;
public:
    complex( double r, double i ) { re=r; im=i; }
    complex( double r ) { re=r; im=0.0; }
    double real() { return re; }
    double imag() { return im; }
 
    friend complex operator+(complex, complex);
    friend complex operator-(complex, complex);     // subtraction
    friend complex operator-(complex);              // negation
    friend complex operator*(complex, complex);
    friend complex operator/(complex, complex); 
};

int main()
{
    printf( "Complex Number C++Test Program\r\n\r\n" );

    complex a = 2.3;
    complex b = 1/a;
    complex c = a + (b*complex(1, 2.3));

    printf( "Result = (%f, %fi)\r\n", c.real(), c.imag() );

    return 0;
}


complex operator+( complex z1, complex z2 )
{
    return complex( z1.re + z2.re, z1.im + z2.im );
}

complex operator-( complex z1, complex z2 )
{
    return complex( z1.re - z2.re, z1.im - z2.im );
}

complex operator-( complex z )
{
    return complex( -z.re, -z.im );
}

complex operator*( complex z1, complex z2 )
{
    return complex( z1.re*z2.re - z1.im*z2.im, z1.re*z2.im + z1.im*z2.re );
}

complex operator/( complex z1, complex z2 )
{
    double divisor = z2.re*z2.re + z2.im*z2.im;
    return complex( ( z1.re*z2.re + z1.im*z2.im ) / divisor,
                        ( z1.im*z2.re - z1.re*z2.im ) / divisor );
}

