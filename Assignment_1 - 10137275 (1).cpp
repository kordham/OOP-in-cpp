// Assignment 1 - Bohr transition energy calculator
// Mohammad Kordzanganeh - 19 Feb 2021
// Program to calculate transition energy using simple Bohr formula

#include<iostream>
#include<iomanip>
#include<tuple> 
#include<string>


double get_energy_level(int quantum_number, int atomic_number)
{

  const double hydrogen_ionisation_energy{13.6};
  double level_energy{};

  //energy in eV
  level_energy = -hydrogen_ionisation_energy*atomic_number*atomic_number/(quantum_number*quantum_number);
  return level_energy;
}



int int_input_checker(std::string query)
{

  bool fail{true};
  int acquired_integer{};
    while(fail){

    std::cout<<"Please input the "<<query<<": "<<std::endl;
    std::cin>>acquired_integer;

    if(std::cin.fail() || acquired_integer==0){

      std::cin.clear();
      std::cin.ignore(256,'\n');
      std::cout<<"The input was incorrectly formatted, please input a non-zero integer"<<std::endl;
    }
    else{
      fail = false;
    }
  }
  return acquired_integer;
}

// a function to query the user for 2 quantum numbers for high/low energy levels,
// the atomic number, and whether they want the answer in joules or eV
std::tuple<int,int,int,char> get_input_variables()
{

  //declare & initialise variables 
  int lower_level{1},higher_level{};
  int atomic_number{1};
  char joules_or_ev{'e'};
  bool wrong_character{true};

  //query the User for the variables
  atomic_number = int_input_checker("atomic number");

  while(higher_level<lower_level){
    lower_level = int_input_checker("lower level quantum number");
    higher_level = int_input_checker("higher level quantum number");

    if(higher_level<lower_level){
      std::cout<<"The quantum number of the higher level must be larger than or equal to the lower quantum number, please try again"<<std::endl;
    }
  }
  std::cout<<"Please specify if you'd like to get the answer in Joules or eV.  You can respond with (j) or (e) respectively:"<<std::endl;
  while(wrong_character){
    std::cin>>joules_or_ev;
    if(std::tolower(joules_or_ev)=='j' || std::tolower(joules_or_ev)=='e' ) {
      joules_or_ev = std::tolower(joules_or_ev);
      wrong_character = false;
    }
    else{
      std::cin.clear();
      std::cin.ignore(256,'\n');
      std::cout<<"The input was incorrectly formatted.  Please input 'j' for Joules or 'e' for eV."<<std::endl;
    }
  }

  return {atomic_number,lower_level,higher_level,joules_or_ev};
}


double convert_to_joule(double energy)
{
  const double ev_to_joule{1.6022e-19};
  return ev_to_joule*energy;
}


int main()
{
  const int number_decimals{3};
  char user_engaged{'y'};
  double energy_difference{0.0};
  std::string unit{"J"};

  //ensure the user can repeat the process if they so wish
  while(user_engaged=='y'){
    
    //query the User for the inputs
    auto [atomic_number,lower_level,higher_level,joules_or_ev]=get_input_variables();

    energy_difference = get_energy_level(higher_level,atomic_number) - get_energy_level(lower_level,atomic_number);
    
    //assign a unit to be used
    if(joules_or_ev=='j'){
      energy_difference = convert_to_joule(energy_difference);
      unit = "J";
    }
    else{
      unit = "eV";
    }

    // show the final answer to the User
    std::cout.setf(std::ios::fixed,std::ios::floatfield);
    std::cout<<std::setprecision(number_decimals)<<"The energy_difference is "<<std::scientific<<energy_difference<<"\t"<<unit<<std::endl;
    
    //query the User to see if they want to repeat
    bool incorrect_repeat_character{true};
    while(incorrect_repeat_character){
      std::cout<<"Would you like to repeat the process? Please specify yes (y) or no (n):"<<std::endl;
      std::cin>>user_engaged;

      //check if the input is correct
        if(std::tolower(user_engaged)!='y' && std::tolower(user_engaged)!='n'){
          std::cin.clear();
          std::cin.ignore(256,'\n');
          std::cout<<"The input was incorrect"<<std::endl;
        }
        else if(std::tolower(user_engaged)=='y'){
          incorrect_repeat_character = false;
          }
        else{
          user_engaged = 'n';
          incorrect_repeat_character = false;
        } 
    }
  }
  return 0;
}