#include "ComplexNumber.h"
#include "helper.h"

ComplexNumber::ComplexNumber()
{
    real_component = 0;
    imaginary_component = 0;
    number_type = 2;
    magnitude = 0;
    phase = 0;
}

ComplexNumber::ComplexNumber(double rval_real_component, double rval_imaginary_component)
{
    real_component = rval_real_component;
    imaginary_component = rval_imaginary_component;
    number_type = 2;
    magnitude = sqrt( real_component*real_component + imaginary_component*imaginary_component );
    phase = calculate_phase(rval_real_component, rval_imaginary_component);
}

ComplexNumber::ComplexNumber( const ComplexNumber& other )
{
    real_component = other.get_real_component();
    imaginary_component = other.get_imaginary_component();
    number_type = 2;
    magnitude = other.get_magnitude();
    phase = other.get_phase();
}

void ComplexNumber::set_real_component (double rval)
{
    real_component = rval;
    phase = calculate_phase(real_component, imaginary_component);
    magnitude = sqrt( real_component*real_component + imaginary_component*imaginary_component );
}

double ComplexNumber::get_real_component() const
{
    return real_component;
}

void ComplexNumber::set_imaginary_component (double rval)
{
    imaginary_component = rval;
    phase = calculate_phase(real_component, imaginary_component);
    magnitude = sqrt( real_component*real_component + imaginary_component*imaginary_component );
}

double ComplexNumber::get_imaginary_component() const
{
    return imaginary_component;
}

double ComplexNumber::get_magnitude() const{
    return magnitude;
}

double ComplexNumber::get_phase() const{
    return phase;
}

ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
    double arg_real = arg.get_real_component();
    double arg_imaginary = arg.get_imaginary_component();
    return ComplexNumber( real_component + arg_real, imaginary_component + arg_imaginary );
}

ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
    double arg_real = arg.get_real_component();
    double arg_imaginary = arg.get_imaginary_component();
    return ComplexNumber( real_component - arg_real, imaginary_component - arg_imaginary );
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
    double arg_real = arg.get_real_component();
    double arg_imaginary = arg.get_imaginary_component();
    double real = real_component * arg_real + -1 * imaginary_component * arg_imaginary;
    double imaginary = real_component * arg_imaginary + imaginary_component * arg_real;
    return ComplexNumber( real, imaginary );
}

ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
    double arg_real = arg.get_real_component();
    double arg_imaginary = arg.get_imaginary_component();
    double real = ( real_component*arg_real + imaginary_component*arg_imaginary ) / ( arg_real*arg_real + arg_imaginary*arg_imaginary );
    double imaginary = ( imaginary_component*arg_real - real_component*arg_imaginary ) / ( arg_real*arg_real + arg_imaginary*arg_imaginary ) ;
    return ComplexNumber( real, imaginary );
}

ComplexNumber ComplexNumber::operator + (const RealNumber& arg)
{
    double arg_real = arg.get_real_component();
    return ComplexNumber( real_component + arg_real, imaginary_component );
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
    double arg_real = arg.get_real_component();
    return ComplexNumber( real_component - arg_real, imaginary_component );
}

ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
    double arg_real = arg.get_real_component();
    return ComplexNumber( real_component * arg_real, imaginary_component * arg_real);
}

ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
    double arg_real = arg.get_real_component();
    return ComplexNumber( real_component / arg_real, imaginary_component / arg_real);
}

ComplexNumber ComplexNumber::operator + (const ImaginaryNumber& arg){
    double arg_imaginary = arg.get_imaginary_component();
    return ComplexNumber( real_component, imaginary_component + arg_imaginary );
}

ComplexNumber ComplexNumber::operator - (const ImaginaryNumber& arg)
{
    double arg_imaginary = arg.get_imaginary_component();
    return ComplexNumber( real_component, imaginary_component - arg_imaginary );
}

ComplexNumber ComplexNumber::operator * (const ImaginaryNumber& arg)
{
    double arg_imaginary = arg.get_imaginary_component();	
    return ComplexNumber( -1 * imaginary_component * arg_imaginary, real_component * arg_imaginary );
}

ComplexNumber ComplexNumber::operator / (const ImaginaryNumber& arg)
{
    double arg_imaginary = arg.get_imaginary_component();	
    double real = ( imaginary_component * arg_imaginary ) / ( arg_imaginary * arg_imaginary );
    double imaginary = (-1 * real_component * arg_imaginary ) / ( arg_imaginary * arg_imaginary );
    return ComplexNumber( real, imaginary );
}

string ComplexNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    if (imaginary_component > 0)
        my_output << std::setprecision(3) << real_component << " + " << imaginary_component << 'i';
    else if (imaginary_component < 0)
        my_output << std::setprecision(3) << real_component << " - " << abs(imaginary_component) << 'i';
    else
        my_output << std::setprecision(3) << real_component;
    
    return my_output.str();
}