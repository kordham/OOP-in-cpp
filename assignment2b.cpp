// PHYS 30762 Programming in C++
// Assignment 2-b
// Mohammad Kordzanganeh

// Program to compute mean, standard deviation and standard
// error of the a set of courses. Data is read from file.
// This program also can sort the given data w.r.t the course number
// or the course title. Additionally, it is possible to filter the list
// to only look at a course year's modules and/or mark statistics. 

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>
#include<sstream>
#include<vector>
#include<tuple>
#include<algorithm>

// Functions to compute mean, standard deviation and standard error
double get_mean(std::vector<double> vector_marks)
{
    double mean{};
    int vector_length = vector_marks.size();

    for(int i{};i<vector_length;i++) mean+=vector_marks[i];

    mean = mean/vector_length;
    return mean;
}
double get_std_dev(std::vector<double> vector_marks)
{
    double mean = get_mean(vector_marks);
    double std_dev{};

    int vector_length = vector_marks.size();

    for(int i{};i<vector_length;i++){
        std_dev+=(vector_marks[i]-mean)*(vector_marks[i]-mean);
    }
    //denominator is N-1 -> check for division by zero by checking N>1
    if(vector_length<2){
        std::cout<<"Fewer than 2 data points - cannot find standard deviation, taking it to be zero"<<std::endl;
        return 0;
    }

    std_dev = std_dev/(vector_length-1);
    std_dev = std::sqrt(std_dev);
    return std_dev;
}
double get_error(std::vector<double> vector_marks)
{
    double std_dev = get_std_dev(vector_marks);
    int vector_length = vector_marks.size();

    double error = std::sqrt(std_dev*std_dev/vector_length);
    return error;
}

 //takes a line and splits it into a tuple of <mark,course code,course title> 
std::tuple<double,int,std::string> string_splitter(std::string course_info)
{
    std::stringstream course_info_stream(course_info);

    double mark{};
    int course_no{};
    std::string title{};

    course_info_stream>>mark>>course_no;
    std::getline(course_info_stream,title);

    return {mark,course_no,title};
}
// displays the course information, and if print_stat=true gives the statistics for the info passed in
void print_output(std::vector<std::string> all_course_info,bool print_stats)
{
    std::vector<double> marks;
    std::cout<<std::endl<<" COURSE LIST " << std::endl;
    for(std::vector<std::string>::iterator vector_iterator{all_course_info.begin()};
      vector_iterator<all_course_info.end();
      ++vector_iterator){
          auto [mark,course_no,title] = string_splitter(*vector_iterator);
          std::cout<<"PHYS "<<course_no<<title<<std::endl;
          marks.push_back(mark);
      }
    if(print_stats){

        std::cout<<"mean mark: "<<get_mean(marks)<<std::endl<<
        "standard deviation: "<<get_std_dev(marks)<<std::endl<<
        "error on the mean: "<< get_error(marks)<<std::endl;
    }
}
//Takes in an integer and returns its first digit (from the left)
int get_year(int course_no)
{
    int digit = course_no;
    int remain{};
    do 
    {
        remain = digit%10;
        digit = digit/10;
    }
    while(digit>0);

    return remain;
}
//declare this function to filter the course info vectors
std::vector<std::string> filter_by_year(std::vector<std::string> all_course_info, int year)
{
    std::vector<std::string> year_course_info;
    for(std::vector<std::string>::iterator vector_iterator{all_course_info.begin()};
      vector_iterator<all_course_info.end();
      ++vector_iterator){
          //unwrap the tuple using auto
          auto [mark,course_no,title] = string_splitter(*vector_iterator);
          if(get_year(course_no)==year){
              year_course_info.push_back(*vector_iterator);
          }
      }

    return year_course_info;

}

// Sorting functions
bool sort_by_course_no(std::string course_info_1,std::string course_info_2)
{
    auto [mark_1,course_no_1,title_1] = string_splitter(course_info_1);
    auto [mark_2,course_no_2,title_2] = string_splitter(course_info_2);

    
    return course_no_2>course_no_1;
}

bool sort_by_title(std::string course_info_1,std::string course_info_2)
{
    auto [mark_1,course_no_1,title_1] = string_splitter(course_info_1);
    auto [mark_2,course_no_2,title_2] = string_splitter(course_info_2);
    
    return title_2>title_1;
}

    // Main function
int main(){

    char data_file[100];
    // Empty vector
    std::vector<std::string> all_course_info;

    // Ask user to enter filename
    std::cout<<"Enter data filename: ";
    std::cin>>data_file;

    // Open file and check if successful
    std::fstream course_stream(data_file);
    if(!course_stream.good()) 
    {
    // Print error message and exit
    std::cerr <<"Error: file could not be opened"<<std::endl;
    return(1);
    }
     
    //Populate the vectors from the files
    std::string line{};
    while(std::getline(course_stream, line)){
        if(!line.empty()){
            std::stringstream course_info_stream(line);
            //store all the non-empty, correctly-formatted information in the file here: 
            all_course_info.push_back(line);
            double mark{};
            int course_code{};
            std::string course_title;

            std::stringstream showcase_course_info_stream;

            if (!(course_info_stream >> mark >> course_code)){ 
                 std::cout<<"Irregularities found and ignored: "<<std::endl<<line<<std::endl;
            } 
            else{
                //This step, although not serving a direct purpose in the program, shows 
                //both the course number and course title in a stringstream
                std::getline(course_info_stream,course_title);
                showcase_course_info_stream <<"PHYS " << course_code<< course_title;
            }
        }
    }

    course_stream.close();

    // Print number of courses read in
    std::cout<<"number of courses read in: "<<all_course_info.size()<<std::endl;

    //print the courses and the mark statistics in each year
    const int number_of_years = 4;
    std::vector<double> year_marks;
    for(int year{1};year<=number_of_years;year++){
        std::cout<<std::endl<<"Courses In Year =  "<< year<<std::endl;
        print_output(filter_by_year(all_course_info,year),true);
    }

    //sort by title and print statistics
    std::cout<<std::endl<<"Course list sorted by course title:"<<std::endl;
    std::sort(all_course_info.begin(),all_course_info.end(),sort_by_title);
    print_output(all_course_info,true);

    //sort by course number and don't print statistics as will be the same as above
    std::cout<<std::endl<<"Course list sorted by course number:"<<std::endl;
    std::sort(all_course_info.begin(),all_course_info.end(),sort_by_course_no);
    print_output(all_course_info,false);   

    return 0;
}