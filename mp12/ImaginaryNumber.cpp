#include "ImaginaryNumber.h"
#include "helper.h"

ImaginaryNumber::ImaginaryNumber()
{
    imaginary_component = 0;
    number_type = 1;
    magnitude = 0;
    phase = 0;
}

ImaginaryNumber::ImaginaryNumber(double rval)
{
    imaginary_component = rval;
    number_type = 1;
    magnitude = abs( imaginary_component );
    phase = calculate_phase(0, rval);
}

ImaginaryNumber::ImaginaryNumber( const ImaginaryNumber& other )
{
    imaginary_component = other.get_imaginary_component();
    number_type = 1;
    magnitude = other.get_magnitude();
    phase = other.get_phase();
}

void ImaginaryNumber::set_imaginary_component (double rval)
{
    imaginary_component = rval;
    phase = calculate_phase(0, rval);
    magnitude = abs( imaginary_component );
}

double ImaginaryNumber::get_imaginary_component() const
{
    return imaginary_component;
}

//Getter function for magnitude
double ImaginaryNumber::get_magnitude() const{
    return magnitude;
}

//Getter function for phase
double ImaginaryNumber::get_phase() const{
    return phase;
}

//Operator Overload
ImaginaryNumber ImaginaryNumber::operator + (const ImaginaryNumber& arg)
{
    double arg_imaginary = arg.get_imaginary_component();
    return ImaginaryNumber( arg_imaginary + imaginary_component );
}

ImaginaryNumber ImaginaryNumber::operator - (const ImaginaryNumber& arg)
{
    double arg_imaginary = arg.get_imaginary_component();
    return ImaginaryNumber( imaginary_component - arg_imaginary );
}

RealNumber ImaginaryNumber::operator * (const ImaginaryNumber& arg)
{
    double arg_imaginary = arg.get_imaginary_component();
    return RealNumber( -1 * imaginary_component * arg_imaginary );
}

RealNumber ImaginaryNumber::operator / (const ImaginaryNumber& arg)
{
    double arg_imaginary = arg.get_imaginary_component();
    return RealNumber( imaginary_component / arg_imaginary );
}

ComplexNumber ImaginaryNumber::operator + (const RealNumber& arg)
{
    double arg_real = arg.get_real_component();
    return ComplexNumber( arg_real, imaginary_component );
}

ComplexNumber ImaginaryNumber::operator - (const RealNumber& arg)
{
    double arg_real = arg.get_real_component();
    return ComplexNumber( -1 * arg_real, imaginary_component );
}

ImaginaryNumber ImaginaryNumber::operator * (const RealNumber& arg)
{
    double arg_real = arg.get_real_component();
    return ImaginaryNumber( arg_real * imaginary_component );
}

ImaginaryNumber ImaginaryNumber::operator / (const RealNumber& arg)
{
    double arg_real = arg.get_real_component();
    return ImaginaryNumber( imaginary_component / arg_real );
}

ComplexNumber ImaginaryNumber::operator + (const ComplexNumber& arg)
{
    double arg_real = arg.get_real_component();
    double arg_imaginary = arg.get_imaginary_component();
    return ComplexNumber( arg_real, imaginary_component + arg_imaginary );
}

ComplexNumber ImaginaryNumber::operator - (const ComplexNumber& arg)
{
    double arg_real = arg.get_real_component();
    double arg_imaginary = arg.get_imaginary_component();
    return ComplexNumber( -1 * arg_real, imaginary_component - arg_imaginary );
}

ComplexNumber ImaginaryNumber::operator * (const ComplexNumber& arg)
{
    double arg_real = arg.get_real_component();
    double arg_imaginary = arg.get_imaginary_component();	
    return ComplexNumber( -1 * imaginary_component * arg_imaginary, arg_real * imaginary_component );
}

ComplexNumber ImaginaryNumber::operator / (const ComplexNumber& arg)
{
    double arg_real = arg.get_real_component();
    double arg_imaginary = arg.get_imaginary_component();
    double real = ( imaginary_component*arg_imaginary ) / ( arg_real*arg_real + arg_imaginary*arg_imaginary );
    double imaginary = ( imaginary_component*arg_real ) / ( arg_real*arg_real + arg_imaginary*arg_imaginary ) ;
    return ComplexNumber( real, imaginary );
}

string ImaginaryNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << imaginary_component << 'i';
    return my_output.str();
}