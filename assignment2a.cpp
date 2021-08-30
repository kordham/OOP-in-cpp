// PHYS 30762 Programming in C++
// Assignment 2-a
// Mohammad Kordzanganeh

// Program to compute mean, standard deviation and standard
// error of the a set of courses. Data is read from file


#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>
#include<sstream>

// Functions to compute mean and standard deviation
double get_mean(double *array_marks, int array_length)
{
    double mean{};
    for(int i{};i<array_length;i++) mean+=array_marks[i];
    mean = mean/array_length;
    return mean;
}
double get_std_dev(double *array_marks, int array_length)
{
    double mean = get_mean(array_marks,array_length);
    double std_dev{};

    for(int i{};i<array_length;i++){
        std_dev+=(array_marks[i]-mean)*(array_marks[i]-mean);
    }
    //denominator is N-1 -> check for division by zero by checking N>1
    if(array_length<2){
        std::cout<<"fewer than 2 data points - cannot find standard deviation, taking it to be zero"<<std::endl;
        return 0;
    }
    std_dev = std_dev/(array_length-1);
    std_dev = std::sqrt(std_dev);
    return std_dev;
}
double get_error(double *array_marks,int array_length)
{
    double std_dev = get_std_dev(array_marks,array_length);
    double error = std::sqrt(std_dev*std_dev/array_length);
    return error;
}
// Main function
int main()
{
    char data_file[100];
    // Ask user to enter number of courses
    // Or determine in another way
    int number_courses{};

    // Ask user to enter filename
    std::cout<<"Enter data filename: ";
    std::cin>>data_file;

    // Open file and check if successful
    std::fstream course_stream(data_file);
    if(!course_stream.good()){
        // Print error message and exit
        std::cerr <<"Error: file could not be opened"<<std::endl;
        return(1);
    }

    // Get number of lines in the file
    std::string line{};
    while(std::getline(course_stream, line)){
        if(!line.empty()){
            number_courses++;
        }
    }
    course_stream.close();

    //Dynamic memory allocation for an array of marks
    double *course_marks;
    course_marks = new double[number_courses];
    
    //need to open the file again and put in a fstream
    course_stream.open(data_file);
    int count{};
    while(std::getline(course_stream, line)){
        if(!line.empty()){
            std::stringstream line_ss(line);
            double mark{};
            //If the line does not have a double mark as its first argument, do not read in
            if (!(line_ss >> mark)){ 
                std::cout<<"File corrupted on line "<<count+1<<std::endl;
            } 
            else{
            course_marks[count]= mark;
            count++;
            }
        }
    }
    // Close file
    course_stream.close();

    // Print number of courses read in
    std::cout<<"number of courses read in: "<<number_courses<<std::endl;
    // Compute mean, standard deviation and  standard error of mean
    std::cout<<"mean: "<<get_mean(course_marks,number_courses)<<std::endl
    <<"stadard deviation: "<<get_std_dev(course_marks,number_courses)<<std::endl
    <<"standard error: " << get_error(course_marks,number_courses)<<std::endl;
    // Free memory
    delete[] course_marks;

    return 0;
}