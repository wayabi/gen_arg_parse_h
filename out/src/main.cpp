#include "arg_parse.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv){
	arg_parse ap_;
	string parse_error = ap_.parse(argc, argv);
	if(parse_error.size() == 0){
		ap_.print(cout);
	}else{
		cout << parse_error << endl;
	}
	return 0;
}
