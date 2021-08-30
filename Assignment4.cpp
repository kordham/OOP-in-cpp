// PHYS 30762 Programming in C++
// Assignment 4 - Mohammad Kordzanganeh
// The School of Physics and Astronomy

// This program takes in complex numbers and extracts
// features such as modulus and argument. It also augments
// the main mathematical operators (+,-,*,/) to accommodate for them. 

// Class for complex numbers

#include<iostream>
#include<cmath>

class complex
{
  // Make function to overload operator<< and operator>> as friends
  friend std::ostream & operator<<(std::ostream &os, const complex &z);
  friend std::istream & operator>>(std::istream &is, complex &z);

private:
  double re,im;
public:
  // Constructors & destructor
  complex()
  {
      re=im=0;
  }
  complex(double real_part, double im_part)
  {
      re=real_part; im=im_part;
  }
  ~complex(){}

  // Return real component
  double get_real() const 
  {
      return re;
  }
  // Return imaginary component
  double get_imaginary() const 
  {
      return im;
  }
  // Return modulus
  double get_mod() const
  {
      return std::sqrt(re*re+im*im);
  }
  // Return argument
  double get_arg() const
  {
      return atan2(im,re);
  }
  // Return complex conjugate
  complex get_conj() const
  {
      return complex(re,-1.*im);
  }
  // Overload + operator for addition 
  complex operator+(const complex &z) const
  {
      return complex(re+z.get_real(),im+z.get_imaginary());
  }
  // Overload - operator for subtraction
  complex operator-(const complex &z) const
  {
      return complex(re-z.get_real(),im-z.get_imaginary());
  }
  // Overload * operator for multiplication, z1*z2
  complex operator*(const complex &z) const
  {
      double real_result{re*z.get_real()-im*z.get_imaginary()};
      double imaginary_result{re*z.get_imaginary()+im*z.get_real()};
      return complex(real_result,imaginary_result);
  }
  // Overload / operator for division, z1/z2
  complex operator/(const complex &z) const
  {
    if(z.get_real()==0. && z.get_imaginary() ==0.){
        std::cout<<"Error: Division by zero."<<std::endl;
        
    }
    else{
        complex numerator{complex(re*z.get_real()+im*z.get_imaginary()
            ,im*z.get_real()-re*z.get_imaginary())};
        double denominator{z.get_mod()};
        complex result(numerator.get_real()/denominator,numerator.get_imaginary()/denominator);
        return result;
    }
  }
  // Compounding operators (+= -= /= *=)
  // Overload + operator for addition 
  void operator+=(const complex &z)
  {
      re+=z.get_real();
      im+=z.get_imaginary();
  }
  // Overload -= operator for subtraction
  void operator-=(const complex &z) 
  {
      re-=z.get_real();
      im-=z.get_imaginary();
  }
  // Overload *= operator for multiplication, z1*z2
  void operator*=(const complex &z) 
  {
      double real_result{re*z.get_real()-im*z.get_imaginary()};
      double imaginary_result{re*z.get_imaginary()+im*z.get_real()};
      re = real_result;
      im = imaginary_result;
  }
  // Overload =/ operator for division
  void operator/=(const complex &z) 
  {
    if(z.get_real()==0. && z.get_imaginary() ==0.){
        std::cout<<"Error: Division by zero."<<std::endl;
        exit(EXIT_FAILURE);
    }
    else{
        //numerator*conjugate of the other number and denominator*its conjugate
        complex numerator{complex(re*z.get_real()+im*z.get_imaginary(),
            im*z.get_real()-re*z.get_imaginary())};
        double denominator{z.get_mod()};

        re = numerator.get_real()/denominator;
        im = numerator.get_imaginary()/denominator;
    }
  }

  // get the polar representation 
  void print_cplx_polar() const
  {
      std::cout<<this->get_mod()<<"*exp("<<this->get_arg()<<"i)";
      return;
  }
};

// Function to overload << operator for complex numbers
std::ostream & operator<<(std::ostream &os, const complex &z)
{
    os<<z.re;
    if(z.im>=0){
        os<<"+";
    }
    os<<z.im<<"i";
    return os;
}

// Function to overload >> operator for complex numbers
std::istream & operator>>(std::istream &is, complex &z)
{
    double im{},re{};

    is>>re;
    is>>im;
    //make sure there is a complex indicator at the end
    if(is.peek()=='i' || is.peek()=='j' || is.peek()=='I' || is.peek()=='J'){
        is.ignore();
        z.im = im;
        z.re = re;
        return is;
    }
    else{
        std::cout<<"Incorrect format for the complext number."<<std::endl;
        exit(EXIT_FAILURE);
    }
}

int main()
{  
  std::cout.precision(3);

  // Create two complex numbers
  complex a{3,4};
  complex b{1,-2};

  // Get real and imaginary components, modulus and argument
  std::cout<<"a = "<<a<<" = ";
  a.print_cplx_polar();
  std::cout<<std::endl;

  std::cout<<"b = "<<b<<" = ";
  b.print_cplx_polar();
  std::cout<<std::endl<<std::endl;
  // Get conjugates
  std::cout<<"conj(a) = "<<a.get_conj()<<std::endl;
  std::cout<<"conj(b) = "<<b.get_conj()<<std::endl;

  // Get sum, difference, product and quotient of a and b
  std::cout<<"a+b = "<<a+b<<
  std::endl<<"a-b = "<<a-b<<
  std::endl<<"a*b = "<<a*b<<
  std::endl<<"a/b = "<<a/b<<
  std::endl<<std::endl;

  complex z1;
  std::cout<<"input first complex number (z_1 = x_1+y_1i):"<<std::endl;
  std::cin>>z1;
  std::cout<<"you entered: "<<z1<<std::endl<<std::endl;

  complex z2;
  std::cout<<"input second complex number (z_2 = x_2+y_2i):"<<std::endl;
  std::cin>>z2;
  std::cout<<"you entered: "<<z2<<std::endl<<std::endl;  

  std::cout<<"z_1 + z_2 = "<<z1+z2<<
  std::endl<<std::endl;
  return 0;
}