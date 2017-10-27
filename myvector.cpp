#include "vector.h"
using namespace std;
int main() {
	std::cout << "Create CSEVector: " << std::endl;
	   ubcse::vector<int> array1;
	   array1.insert(0,5);
	   if (true) {
	      std::cout << "Create array2 in a temp scope: " << std::endl;

	      ubcse::vector<int> array2;

	   }

	   std::cout << "Create a vector that is a copy of array: " << std::endl;
	   // This calls the copy constructor.
	   ubcse::vector<int> array3;
array3 = array1;

	   array3.push_back(20);
	   array3.push_back(50);
	   array3.insert(0,100);

	   std::cout << "\nContents of array1:\n";
	   for(int i = 0; i < array1.size(); ++i) {
	      std::cout << array1[i] << " ";
	   }
	   std::cout << "\nContents of array3:\n";
	   for(int i = 0; i < array3.size(); ++i) {
	      std::cout << array3[i] << " ";
	   }

	   std::cout<< "check range constructor"<< std::endl;
	   ubcse::vector<int> array4(array3[1],array3[2]);

	   std::cout << "\nContents of array4:\n";
	   for(int i = 0; i < array4.size(); ++i) {
		  std::cout << array4[i] << " ";
	   }

	   std::cout<< "check fill constructor"<< std::endl;
	   ubcse::vector<int> array5(5,4);

	   std::cout << "\nContents of array5:\n";
	   array5.print();

	   ubcse::vector<int> array6(array5);
	   std::cout << "\nContents of array6:\n";
	   array6.print();

	   array6.insert(3,200);
	   std::cout << "\nContents of array6:\n";
	   array6.print();

	   std::cout << "\narray6 is empty:"<< array6.empty()<<std::endl;

	   ubcse::vector<int> array7(array3,1,3);
	   std::cout << "\nContents of array7:\n";
	   array7.print();

	   array6.concat(array7);

	   std::cout << "\nContents of array6:\n";
	   array6.print();

	   return 0;

	return 0;
}
