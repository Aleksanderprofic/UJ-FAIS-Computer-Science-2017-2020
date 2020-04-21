#include <iostream>
#include <ctime>

int main(int argc, char* argv[]) {

	srand(time(NULL));

     if(argc != 2) {
		std::cerr << "Usage:\n\t" << argv[0] << " number \n\n";
		return 1;
	}


	int number = std::stoi(argv[1]);
	int half = rand()%number;

	int temp = -(number*5);
	int diff1 = temp/half;
	int diff2 = -temp/(number-half);
	int randomize = 0;
	
	for(int i = 1, j = half - 1; i < half; i++, j--) {
		randomize = rand()%diff1;
		std::cout << -randomize+(j*diff1) << std::endl;
	}

	for(int i = half, j = 0; i < number; i++, j++) {
		randomize = rand()%diff2;
		std::cout << randomize+(j*diff2) << std::endl;
	}

      std::cout << rand()%(2*temp)+temp << std::endl;

	return 0;
}