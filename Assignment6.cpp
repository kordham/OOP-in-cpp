// PHYS 30762 Programming in C++
// Assignment 6 - Mohammad Kordzanganeh
// The School of Physics and Astronomy

/***
This program demonstrates a hierarchical structure to shapes
It includes an abstract base class with a virtual destroyer, 
pure virtual functions and derived classes to show 2- and 3D shapes.
It also calculates their volumes and areas where applicable.
***/

#define PI      3.141529
#define RESET   "\033[0m"
#define GREEN   "\033[32m" 
#define BLUE    "\033[34m" 
#define RED     "\033[31m"

#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<limits>

//Abstract base class
class shape 
{
protected:
    std::string type;
public: 
    //virtual destroyer function - if any of the derived classes used dynamic memory allocation 
    //they could have their unique destroyers - demonstrated in the square class
    virtual ~shape(){std::cout<<RED<<type<<" destroyed"<<RESET<<std::endl;}
    virtual int get_num_dims()  const=0; //pure virtual function for number of dimensions
    virtual double get_area()   const=0; // for area
    virtual double get_volume() const=0; // for volume
    virtual double get_perimeter() const=0; // for perimeter

    std::string get_type() const
    {
        return type;
    }
};

// 2D and 3D shapes are derived classes from the shape base class
class shape_2d : public shape 
{
public:
    int get_num_dims() const
    {
        return 2;
    }
    //volume =0 for 2D shapes
    double get_volume() const
    {
        return 0;
    }
};

class shape_3d : public shape 
{
public:
    //output number of dimensions
    int get_num_dims()  const
    {
        return 3;
    }
    //perimeter makes no sense for 3D shapes
    double get_perimeter() const
    {
        return 0;
    }
};
//2D shapes - general
class rectangle : public shape_2d
{
protected:
    double length,width;
public:
    //default and parameterised constructors
    rectangle(): length{},width{} 
    {
        type = "Rectangle";
    }
    rectangle(double l,double w):length{l},width{w} 
    {
        type = "Rectangle";
    }
    
    double get_area() const{
        return length*width;
    }
    double get_perimeter() const{
        return 2.*(length+width);
    }
};
class ellipse : public shape_2d
{
protected:
    double semi_major,semi_minor;
public:
    //default and parameterised constructors
    ellipse(): semi_major{},semi_minor{} 
    {
        type = "Ellipse";
    }
    ellipse(double a,double b): semi_major{a},semi_minor{b} 
    {
        type = "Ellipse";
    }
    double get_area() const
    {
        return PI*semi_major*semi_minor;
    }
    //Perimeter of an ellipse https://www.mathsisfun.com/geometry/ellipse-perimeter.html
    double get_perimeter() const
    {
        return 2.*PI*sqrt((semi_major*semi_major+semi_minor*semi_minor)/2.);
    }
};

//2D shapes, 2nd layer inheritance
class square : public rectangle
{
public:
    square(double side): rectangle{side,side} 
    {
        type = "Square";
    }
    //Explicit use of destroyer here - this will be mentioned in addition to the shape destroyer
    ~square(){std::cout<<BLUE<<"Square destroyed - explicit destroyer in the square class - the shape destroyer is the line below"<<RESET<<std::endl;}
};
class circle : public ellipse
{
public:
    circle(double radius): ellipse{radius,radius} 
    {
        type = "Circle";
    }
};

//3D shapes - general
class cuboid : public shape_3d
{
protected:
    double length,width,height;
public:
    //default and parameterised constructors
    cuboid(): length{},width{},height{} 
    {
        type = "Cuboid";
    }
    cuboid(double l,double w,double h): length{l},width{w},height{h} 
    {
        type = "Cuboid";
    }
    //overriding the virtual functions
    double get_area() const
    {
        return 2.*(width*length+width*height+height*length);
    }
    double get_volume() const
    {
        return width*height*length;
    }
};
class ellipsoid : public shape_3d
{
protected:
    double semi_major,semi_middle,semi_minor;
public:
    //default and parameterised constructors
    ellipsoid(): semi_major{},semi_middle{},semi_minor{} 
    {
        type = "Ellipsoid";
    }
    ellipsoid(double a,double b,double c): semi_major{a},semi_middle{b},semi_minor{c} 
    {
        type = "Ellipsoid";
    }
    virtual double get_area() const
    {
        //approximate ellipsoid surface area https://en.wikipedia.org/wiki/Ellipsoid
        //Don't need to re-define for a sphere as it works for any value of p
        double p{1.6075};
        return 4.*PI*pow(
            (pow(semi_major,p)*pow(semi_minor,p)+
            pow(semi_middle,p)*pow(semi_minor,p)+
            pow(semi_middle,p)*pow(semi_major,p))/3.
            ,1./p
        );
    }
    double get_volume() const
    {
        return 4./3.*PI*semi_major*semi_middle*semi_minor;
    }
};

//3D shapes 2nd layer inheritance
class cube : public cuboid
{
public:
    cube(double side): cuboid{side,side,side} 
    {
        type = "Cube";
    }

};
class sphere : public ellipsoid
{
public:
    sphere(double radius): ellipsoid{radius,radius,radius} 
    {
        type = "Sphere";
    }
};
//Prism class
class prism : public shape_3d
{
private:
    double depth;
    double base_area;
    double base_perimeter;
public:
    prism(): shape_3d(),depth{},base_area{}
    {
        type = "Prism";
    }
    prism(shape_2d* input_base,double d):shape_3d{},base_area{input_base->get_area()},base_perimeter{input_base->get_perimeter()},depth{d} 
    {
        type = "Prism";
    }
    double get_volume() const
    {
        return base_area*depth;
    }
    double get_area() const
    {
        return base_perimeter*depth + 2.*base_area;
    }
};

int main()
{  
    std::cout.precision(4);
    shape *shapes_array[9];
    shape_2d *prism_base = new rectangle{1.,2.};

    shapes_array[0] = new rectangle{1.,2.};
    shapes_array[1] = new ellipse{2.,3.};
    shapes_array[2] = new square{6.};
    shapes_array[3] = new circle{3.};
    shapes_array[4] = new cuboid{1.,2.,3.};
    shapes_array[5] = new ellipsoid{1.,2.,3.};
    shapes_array[6] = new cube{3.};
    shapes_array[7] = new sphere{4.};
    shapes_array[8] = new prism{prism_base,2.};

    //print out the shapes and their respective volumes, areas, and perimeters
    for(int i{};i<9;i++){
        std::cout<<GREEN<<shapes_array[i]->get_type()<<RESET<< " is a "<<shapes_array[i]->get_num_dims()
            <<"D shape with:"<<BLUE<<"\t Volume= "<<RESET<<shapes_array[i]->get_volume()<<BLUE<<"\tArea = "
            <<RESET<<shapes_array[i]->get_area()<<BLUE<<"\tPerimeter= "<<RESET<<shapes_array[i]->get_perimeter()<<std::endl;
    }
    //free up the memory
    for (int i{};i<9;i++){
        delete shapes_array[i];shapes_array[i]=0;
    }
    delete prism_base;
    return 0;
}