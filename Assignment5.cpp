// PHYS 30762 Programming in C++
// Assignment 5 - Mohammad Kordzanganeh
// The School of Physics and Astronomy

// This program takes in matrices and can generate their determinant using recursion
// matrix multiplication, addition and subtraction have also been added to the overall functionality

// Class for matrices

//Defining colour characters
#define RESET   "\033[0m"
#define GREEN   "\033[32m" 
#define BLUE    "\033[34m" 
#define RED     "\033[31m"


#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<limits>

class matrix
{
    friend double get_det(const matrix &input_matrix);
    friend std::ostream & operator<<(std::ostream &os, const matrix &z);
    friend std::istream & operator>>(std::istream &is, matrix &z);
private:
    int row,col;
    double *elements{nullptr};
public:
    // Constructors & destructor
    matrix(){}
    matrix(int input_row,int input_col)
    {
        row = input_row;
        col = input_col;
        elements = new double[row*col];
    }
    ~matrix()
    {
        //make sure not a null pointer
        if(elements!=nullptr){delete[] elements;}
    }

    //element setters
    void set_elements(double *input_elements)
    {
        for(int i{};i<row*col;i++){
            elements[i] = input_elements[i];
        }
    }
    //getter functions
    int get_row() const
    {
        return row;
    }
    int get_col() const
    {
        return col;
    }

    //functions to delete a col/row
    void del_row(int row_number)
    {
        //shift start from 1 to 0 (matrix to c++ array):
        row_number--;
        double *new_elements = new double[(row-1)*col];
        int current_row{},current_col{};
        for(int i{};i<row*col;i++){
            if(i%row==0 && i!=0){
                current_row++;current_col=0;
            }
            else if(i!=0) current_col++;
            if(current_row<row_number) new_elements[i] = elements[i];
            else if(current_row>row_number) new_elements[i-col] = elements[i];
        }
        delete[] elements;
        elements = new_elements;
        row--;
    }
    void del_col(int col_number)
    {   
        //shift start from 1 to 0 (matrix to c++ array):
        col_number--;
        double *new_elements = new double[row*(col-1)];
        int current_row{},current_col{};
        for(int j{};j<row*col;j++){
            if(j%col==0 && j!=0){
                current_row++;current_col=0;
            }
            else if(j!=0) current_col++;
            if(current_col<col_number) new_elements[j-current_row] = elements[j];
            else if(current_col>col_number) new_elements[j-current_row-1] = elements[j];

        }
        delete[] elements;
        elements = new_elements;
        col--;
    }
    //combined deletion of column and row
    void del_col_row(int row_number,int col_number){
        del_row(row_number);
        del_col(col_number);
    }
    matrix operator+(const matrix &m) const
    {
        matrix result_matrix{row,col};
        if(m.col==col && m.row==row){
            for(int i{};i<col*row;i++){
                result_matrix.elements[i] = elements[i] + m.elements[i];
            }
            return result_matrix;
        }
        else{
            std::cout<<"Dimension ERROR: Matrix addition requires same dimensions for both matrices."<<std::endl;
            throw("Dimension ERROR");
        } 
    }
    matrix fetch_row(int in_row) const
    {
        //shift start from 1 to 0 (matrix to c++ array):
        in_row--;
        matrix result_matrix{1,col};
        int count{};
        for(int i{};i<row*col;i++){
            //check if i in the confines of the row
            if(i>=in_row*col && i<(in_row+1)*col){
                result_matrix.elements[count]=elements[i];
                count++;
            }
        }
        return result_matrix;
    }
    matrix fetch_col(int in_col) const
    {
        //shift start from 1 to 0 (matrix to c++ array):
        in_col--;
        matrix result_matrix{row,1};
        int count{};
        for(int i{};i<row*col;i++){
            //check if i in the desired column
            if(i%col==in_col){
                result_matrix.elements[count]=elements[i];
                count++;
            }
        }
        return result_matrix;
    }
    matrix operator-(const matrix &m) const
    {
    if(m.col==col && m.row==row){
        matrix result_matrix{row,col};
        for(int i{};i<col*row;i++){
            //element-wise subtraction
            result_matrix.elements[i] = elements[i] - m.elements[i];
        }
        return result_matrix;
    }
    else{
        throw("Dimension ERROR: Matrix subtraction requires same dimensions for both matrices");
    }  
    }
    //Matrix multiplication
    matrix operator*(const matrix &m) const
    {
    if(m.row==col){
        matrix result_matrix{row,m.col};
        for(int j{};j<row*m.col;j++){
            for(int i{};i<col;i++){
                result_matrix.elements[j]+= fetch_row(j/row+1).elements[i]*m.fetch_col(j%m.col+1).elements[i];
            }
        }
        return result_matrix;
    }
    else{
        throw("Dimension ERROR: In matrix multiplication, the number of columns of the first matrix must equal number of rows of the second one");
    }
  }

  //copy and move constructors and assignment operators placeholder
  matrix(const matrix&); //copy
  matrix(matrix&&); //move
  matrix& operator=(const matrix&); //copy assignment
  matrix& operator=(matrix&&); //move assignment

};

// Constructor and Assignment Operator for deep copy for Move
matrix::matrix(matrix &&m)
{  
  std::swap(col,m.col);std::swap(row,m.row);
  std::swap(elements,m.elements);
}
matrix & matrix::operator=(matrix &&m)
{
  col=m.col;
  row=m.row;
  if(elements!=nullptr){
      delete[] elements;
  }
  elements=m.elements;
  m.elements = nullptr;
  return *this;
}
// Constructor and Assignment Operator for Deep Copy
matrix::matrix(const matrix &m)
{
  // Copy size and declare new array
  elements=nullptr; row=m.row;col=m.col;
  if(row>0 && col>0){
        elements = new double[row*col];
        for(int i{};i<row*col;i++){
            elements[i] = m.elements[i];
        }
    }
}
matrix & matrix::operator=(const matrix &m)
{
  //tackling self-assignment
  if(&m == this) return *this;
  delete[] elements; 
  // Now copy size and declare new array
  row = m.row;col = m.col;
  if(row>0 && col>0)
    {
        elements = new double[row*col];
        for(int i{};i<row*col;i++){
            elements[i] = m.elements[i];
        }
    }
  return *this;
}
// >> and << operators overloaded
std::ostream & operator<<(std::ostream &os, const matrix &m)
{
    if(m.row!=0 && m.col !=0){
        for(int i{};i<m.row*m.col;i++)
        {
            if(i%m.col==0 && i!=0){os<<std::endl;}
            os<<m.elements[i]<<" ";
            
        }
    }
    else std::cout<<RED<<"Matrix of zero dimensions"<<RESET;
    os<<std::endl<<std::endl;
    return os;
}
std::istream & operator>>(std::istream &is, matrix &m)
{
    std::cout<<"Enter number of rows:"<<std::endl;
    is>>m.row;
    std::cout<<"Enter number of columns:"<<std::endl;
    is>>m.col;
    m.elements = new double[m.col*m.row];
    for(int i{};i<m.row;i++){
        std::cout<<"Enter row "<<i+1<<" of elements, space delimited:"<<std::endl;
        for(int j{};j<m.col;j++){
            is>>m.elements[i*m.col+j];
        }
        //remove the excess input elements
        is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return is;
}

//Determinant function
double get_det(const matrix &input_matrix)
{
    if(input_matrix.row==input_matrix.col){
        int sign{1};
        double det{};
        for(int i{1};i<=input_matrix.row;i++){
            if(input_matrix.row!=1){
            matrix cp_mat = input_matrix;
            //find the matrix of minors (used the top row for simplicity in this case)
            cp_mat.del_row(1);
            cp_mat.del_col(i);
            //use of recursion to get the 
            det += sign*input_matrix.elements[i-1]*get_det(cp_mat);
            sign*=-1;
            }
            else {
                det = input_matrix.elements[0];
            }
        }
        return det;
    }
    else{
        throw("Error, not a square matrix so cannot calculate determinant.");
    }
}

int main()
{  
  std::cout.precision(3);
  matrix a;
  std::cout<<"Enter your matrix, 'a':"<<std::endl;
  std::cin>>a;
  std::cout<<BLUE<<"You have entered: "<<std::endl<<GREEN<<a<<RESET;
  try{
    std::cout<<BLUE<<"Determinant = "<<GREEN<<get_det(a)<<RESET<<std::endl<<std::endl;
  }
  catch(const char* msg){
      std::cerr<<RED<<msg<<RESET<<std::endl;
  }
  matrix b;
  //copy a into b
  b=a;
  //Create an array of ones
  double *array_of_ones;
  array_of_ones = new double[a.get_row()*a.get_col()];
  for(int i{};i<a.get_row()*a.get_col();i++){
      array_of_ones[i]=1;
  }
  a.set_elements(array_of_ones);
  delete[] array_of_ones;

  std::cout<<"Copying Matrix a into b, then changing 'a' to a matrix of all ones:"<<std::endl;
  std::cout<<"Matrix a = "<<std::endl<<a;
  std::cout<<"Matrix b = "<<std::endl<<b;
  std::cout<<"The value of b has remained unchanged so the copy"<<GREEN<<" works!"<<RESET<<std::endl<<std::endl;

  //You can uncomment the following as appropriate to check functionality
  try{
    //std::cout<<BLUE<<"Matrix a+b = "<<GREEN<<std::endl<<a+b<<RESET;
    //std::cout<<BLUE<<"Matrix a-b = "<<GREEN<<std::endl<<a-b<<RESET;
    std::cout<<BLUE<<"Matrix a*b = "<<GREEN<<std::endl<<a*b<<RESET;
  } catch(const char* msg){
      std::cerr<<RED<<msg<<std::endl<<RESET;
  }
  std::string row_or_col{""};
  std::cout<<"Would you like to fetch a column(col) or a row(row)?"<<std::endl;
  std::cin>>row_or_col;
  if(row_or_col=="col"){
      int col_num{};
      std::cout<<"You have chosen to enter a column.\nWhich column would you like to fetch?"<<std::endl;
      std::cin>>col_num;
      //Changing the input number from 1+ convention to 0+ convention
      if(col_num<=b.get_col() && col_num>0) std::cout<<BLUE<<"Matrix b, column "<<col_num<<":"<<std::endl<<GREEN<<b.fetch_col(col_num)<<RESET<<std::endl;
      else std::cout<<RED<<"The dimension is out of bounds"<<RESET<<std::endl;
  }
  else if(row_or_col=="row"){
      int row_num{};
      std::cout<<"You have chosen to enter a row.\nWhich row would you like to fetch?"<<std::endl;
      std::cin>>row_num;
      //Changing the input number from 1+ convention to 0+ convention
      if(row_num<=b.get_row() && row_num>0)std::cout<<BLUE<<"Mat b, row "<<row_num<<":"<<std::endl<<GREEN<<b.fetch_row(row_num)<<RESET<<std::endl;
      else std::cout<<RED<<"The dimension is out of bounds"<<RESET<<std::endl;
  }    
  else{
      std::cout<<RED<<"Incorrect choice"<<RESET;
      exit(EXIT_FAILURE);
  }

  //demonstrating row and column deletion functionality
  b.del_col_row(1,1);
  std::cout<<"Matrix b after removing the first column and row:"<<std::endl<<"matrix b="<<std::endl<<GREEN<<b<<RESET<<std::endl;
  //demonstrating move
  std::cout<<"Demonstrating the Move functionality by moving matrix a to c:"<<std::endl;
  matrix c = std::move(a);
  std::cout<<"Matrix a:"<<std::endl<<a;
  std::cout<<"Matrix c:"<<std::endl<<c;
  std::cout<<"Matrix c is identical to what matrix a was previously, and a is null so it"<<GREEN<<" works!"<<std::endl;
  return 0;
}