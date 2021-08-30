// PHYS 30762 Programming in C++
// Assignment 4
// Mohammad Kordzanganeh
//
// A program that demonstrates the usage of Object Oriented Programming
// in the context of a creating a class "galaxy" and adding sattelites to it
#include<iostream>
#include<string>
#include<vector>
#include<cmath>

class galaxy
{
private:
  std::string hubble_type{""};
  double redshift{0.0};
  double total_mass{0.0};
  double stellar_mass_fraction{0.0}; 
  std::vector<galaxy> satellites;

public:
  // Default Constructor
  galaxy()
  {
      std::cout<<"\t\033[1;32mGalaxy created\033[0m"<<std::endl;
  }
  // Parameterised Constructor
  galaxy(std::string hubble_type,double redshift,double total_mass, double stellar_mass_fraction):
      hubble_type{hubble_type},redshift{redshift}
      ,total_mass{total_mass},stellar_mass_fraction{stellar_mass_fraction}
  {
      std::cout<<"\t\033[1;32mGalaxy created\033[0m"<<std::endl;
  }
  // Destructor
  ~galaxy()
  {
      std::cout<<"\t\033[1;31mGalaxy destroyed\033[0m"<<std::endl;
  }
  // Return stellar mass (M_* = f_* x M_tot)
  double stellar_mass() 
  {
      return stellar_mass_fraction*total_mass;
  }
  // Change galaxy's Hubble type
  void change_type(std::string new_type) 
  {
      hubble_type=new_type;
      return;
  }
  // Prototype for function to print out an object's data
  void print_data();
  // Add satellite galaxy default
  void add_satellite(galaxy satellite)
  {
      satellites.push_back(satellite);
      std::cout<<"\t\033[1;94mSatellite galaxy added\033[0m"<<std::endl;
      return; 
    }
};
// Print out an object's data
void galaxy::print_data()
{
  //check if parameterised
  if(total_mass !=0){
        std::cout.precision(3);
        std::cout<<"Galaxy with the following attributes:"
        <<std::endl<<"\tType: "<<hubble_type<<" ,redshift: "<<redshift<<
        " ,total mass: "<<total_mass<<" Solar masses, stellar mass fraction: "<<
        stellar_mass_fraction<<std::endl;

        //print number
        std::cout<<"Number of satellites: "<<satellites.size()<<std::endl;

        //if satellites exist, print number and each of their attributes
        if(!satellites.empty()){
            //print attributes of each
            int count{0};
            for(auto satellite_it=satellites.begin();
            satellite_it<satellites.end();
            ++satellite_it){
                std::cout<<"\tSatellite #"<<++count<<std::endl;
                //recursively print data of the satellites
                satellite_it->print_data();
            }
        }
    }
    else{
        std::cout<<"Galaxy with unspecified attributes"<<std::endl;
    }

  return;
}
// End of class and associated member functions

// Main program
int main()
{
  std::vector<galaxy> galaxy_list;
  // Example using default constructor
  galaxy galaxy_1; 
  // Example using parameterised constructor
  galaxy galaxy_2{galaxy("Irr",2.0,1.00e10,0.01)};
  galaxy galaxy_3{galaxy("Sb",3.0,1.00e8,0.04)};

  // Get and print out stellar mass
  double galaxy_2_stellar_mass = galaxy_2.stellar_mass();

  std::cout<<"Stellar mass of galaxy 2 is "
  << galaxy_2_stellar_mass << " Solar masses"<<std::endl;
  // Change Hubble type from Irr to S0
  galaxy_2.change_type("S0");
  // Add satellite galaxy - default
  galaxy galaxy_2_satellite_1;
  galaxy_2.add_satellite(galaxy_2_satellite_1);
  // Add satellite galaxy - parameterised
  galaxy galaxy_2_satellite_2{galaxy("Irr",2.0,1.00e7,0.05)};  
  galaxy_2.add_satellite(galaxy_2_satellite_2);

  galaxy_list.push_back(galaxy_1);
  galaxy_list.push_back(galaxy_2);
  galaxy_list.push_back(galaxy_3);

  //using iterator to print out the total stellar mass of all galaxies in the list
  //as well as printing out the 
  double total_list_stellar_mass{0.0};
  for(auto galaxy_it=galaxy_list.begin();
            galaxy_it<galaxy_list.end();
            ++galaxy_it){
                total_list_stellar_mass+=galaxy_it->stellar_mass();
                galaxy_it->print_data();
            }
  std::cout<<"The total stellar mass of the galaxies is: "<<total_list_stellar_mass<<" Solar masses"<<std::endl;
  return 0;
}
