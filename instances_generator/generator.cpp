#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <random>    // mtrand

int main(int argc, char* const* argv) {
  int nodes, edges, p, lower, upper;
  int origin, destination, weight;

  char *old_instance_name = argv[1];  // old instance name
  int instance_type = atoi(argv[2]);  // instance type
  float b = atof(argv[3]);            // parameter for the generator
  int s = atoi(argv[4]);              // seed for the PRNG
  std::mt19937 gen(s);                // PRNG

  /* Open the classic instance */
  std::ifstream old_instance(old_instance_name);

  /* Read the number of lines and columns, printing it on the screen */
  old_instance >> nodes >> edges >> p;
  std::cout << nodes << " " << edges << std::endl;

  /* Generate the coefficient's intervals and print on the screen */
  for (int i = 0; i < edges; i++) {
      old_instance >> origin >> destination >> weight;
      std::cout << origin-1 << " " << destination-1 << " ";
      /* Beasley instances */
      if (instance_type == 1) {
        std::uniform_int_distribution<> uniformLower((1-b)*weight, (1+b)*weight);
        lower = uniformLower(gen);
        std::uniform_int_distribution<> uniformUpper(lower, 1+(1+b)*weight);
        upper = uniformUpper(gen);
        std::cout << lower << " " << upper << std::endl;
      /* Montemanni instances */
      } else if (instance_type == 2) {
        std::uniform_int_distribution<> uniformUpper(0, static_cast<int>(b));
        upper = uniformUpper(gen);
        std::uniform_int_distribution<> uniformLower(0, upper);
        lower = uniformLower(gen);
        std::cout << lower << " " << upper << std::endl;
      /* Kasperski-Zielinski instances */
      } else if (instance_type == 3) {
        std::uniform_int_distribution<> uniformLower(0, static_cast<int>(b));
        lower = uniformLower(gen);
        std::uniform_int_distribution<> uniformUpper(lower, lower + static_cast<int>(b));
        upper = uniformUpper(gen);
        std::cout << lower << " " << upper << std::endl;
      } else {
        std::cout << "Error: Instance type not defined. Please enter " << std::endl;
        std::cout << "1: Beasley instances" << std::endl;
        std::cout << "2: Montemanni instances" << std::endl;
        std::cout << "3: Kasperski-Zielinski instances" << std::endl;
        exit(0);
      }
  }
}
