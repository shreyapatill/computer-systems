#include "RealNumber.h"
#include "helper.h"

RealNumber::RealNumber()
{
    real_component = 0;
    number_type = 0;
    magnitude = 0;
    phase = 0;
}

RealNumber::RealNumber(double rval)
{
    real_component = rval;
    number_type = 0;
    magnitude = abs(rval);
    phase = calculate_phase(rval, 0);
}

RealNumber::RealNumber( const RealNumber& other )
{
    real_component = other.get_real_component();
    number_type = 0;
    magnitude = other.get_magnitude();
    phase = other.get_phase();
}

void RealNumber::set_real_component (double rval)
{
    real_component = rval;
    phase = calculate_phase(rval, 0);
    magnitude = abs(rval);
}

double RealNumber::get_real_component() const
{
    return real_component;
}

double RealNumber::get_magnitude() const{
    return magnitude;
}

double RealNumber::get_phase() const{
    return phase;
}

RealNumber RealNumber::operator + (const RealNumber& arg)
{
    double arg_component = arg.get_real_component();
    return RealNumber( real_component + arg_component );
}

RealNumber RealNumber::operator - (const RealNumber& arg)
{
    double arg_component = arg.get_real_component();
    return RealNumber( real_component - arg_component );
}

RealNumber RealNumber::operator * (const RealNumber& arg)
{
    double arg_component = arg.get_real_component();
    return RealNumber( real_component * arg_component );
}

RealNumber RealNumber::operator / (const RealNumber& arg)
{
    double arg_component = arg.get_real_component();
    return RealNumber( real_component / arg_component );
}

ComplexNumber RealNumber::operator + (const ImaginaryNumber& arg){
    double arg_imaginary = arg.get_imaginary_component();
    return ComplexNumber( real_component , arg_imaginary );
}

ComplexNumber RealNumber::operator - (const ImaginaryNumber& arg){
    double arg_imaginary = arg.get_imaginary_component();
    return ComplexNumber( real_component, -1 * arg_imaginary );
}

ImaginaryNumber RealNumber::operator * (const ImaginaryNumber& arg){
    double arg_imaginary = arg.get_imaginary_component();
    return ImaginaryNumber( arg_imaginary * real_component );
}

ImaginaryNumber RealNumber::operator / (const ImaginaryNumber& arg){
    double arg_imaginary = arg.get_imaginary_component();
    return ImaginaryNumber( -1 * real_component / arg_imaginary );
}

ComplexNumber RealNumber::operator + (const ComplexNumber& arg){
    double arg_real = arg.get_real_component();
    double arg_imaginary = arg.get_imaginary_component();
    return ComplexNumber( real_component + arg_real, arg_imaginary );
}

ComplexNumber RealNumber::operator - (const ComplexNumber& arg){
    double arg_real = arg.get_real_component();
    double arg_imaginary = arg.get_imaginary_component();
    return ComplexNumber( real_component - arg_real, arg_imaginary );
}

ComplexNumber RealNumber::operator * (const ComplexNumber& arg){
    double arg_real = arg.get_real_component();
    double arg_imaginary = arg.get_imaginary_component();
    return ComplexNumber( real_component * arg_real, real_component * arg_imaginary );
}

ComplexNumber RealNumber::operator / (const ComplexNumber& arg){
    double arg_real = arg.get_real_component();
    double arg_imaginary = arg.get_imaginary_component();
    double real = (real_component * arg_real) / (arg_real*arg_real + arg_imaginary*arg_imaginary);
    double imaginary = -1 * (real_component * arg_imaginary) / (arg_real*arg_real + arg_imaginary*arg_imaginary);
    return ComplexNumber( real , imaginary );
}

string RealNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << real_component;
    return my_output.str();
}