/* ============================================ *
 *												*
 *  CMPS 109 - Quarter Project - PHASE #3       *
 *  Simple Rule-Base Inference (SRI) Engine     *
 *  3/10/2017                                   *
 *										     	*
 *	Chaiz Tuimoloau : ctuimolo@ucsc.edu         *
 *	Eisaku Imura    : eimura@ucsc.edu           *
 *                                              *
 * ============ Rule Class Source ============= */

#include "Rule.h"

 // ================================================== //
 //      Constructor if given full string to parse     //
 // ================================================== //
Rule::Rule(std::string source) {

	if (source == "") {
		std::cerr << "error : Rule::Rule() : INPUT ERROR" << std::endl;
		return;
	}

	// String buffer for pushing into title, args, etc...
	std::string curr_string;

	// String indexes for iterating
	char tmp = source[0];
	int index = 0;

	/*
	* The logic that follows can be traced from SRI.cpp's similar
	* methods of string parsing: i.e., getting querey args and title
	* from a string such as "RULE Father($X,$Y) :- AND Parent($X,$Y) Male($X)"
	*/

	std::vector<std::string> tmp_vector;
	std::vector<std::string> tmp_vector2;
	std::vector<std::string> tmp_vector3;

	while (tmp != '(') {

		if (index >= source.size()) {
			std::cerr << "error : Rule::Rule() : INPUT ERROR" << std::endl;
			return;
		}
		curr_string.push_back(tmp);
		tmp = source[++index];
	}

	first_title = curr_string;

	tmp = source[++index];
	curr_string.clear();

	tmp_vector = get_args(source, index);

	tmp = source[++index];

	if (tmp == ':') {
		tmp = source[++index];
		if (tmp == '-') 
			tmp = source[++index];
		else {
			std::cerr << "error : Rule::Rule() : INPUT ERROR" << std::endl;
			return;
		}
	}
	else {
		std::cerr << "error : Rule::Rule() : INPUT ERROR" << std::endl;
		return;
	}

	curr_string.push_back(tmp);
	tmp = source[++index];
	curr_string.push_back(tmp);

	if (curr_string != "OR") {
		tmp = source[++index];
		curr_string.push_back(tmp);
		if (curr_string != "AND") {
			std::cerr << "error : Rule::Rule() : INPUT ERROR" << std::endl;
			return;
		}
	}

	operation = curr_string;
	curr_string.clear();
	tmp = source[++index];

	while (tmp != '(') {

		if (index >= source.size()) {
			std::cerr << "error : Rule::Rule() : INPUT ERROR" << std::endl;
			return;
		}

		curr_string.push_back(tmp);
		tmp = source[++index];
	}

	second_title = curr_string;
	tmp = source[++index];
	curr_string.clear();

	tmp_vector2 = get_args(source, index);
	tmp = source[++index];

	while (tmp != '(') {

		if (index >= source.size()) {
			std::cerr << "error : Rule::Rule() : INPUT ERROR" << std::endl;
			return;
		}

		curr_string.push_back(tmp);
		tmp = source[++index];
	}

	third_title = curr_string;
	tmp = source[++index];
	curr_string.clear();

	tmp_vector3 = get_args(source, index);
	tmp = source[++index];

	first_args = tmp_vector;
	second_args = tmp_vector2;
	third_args = tmp_vector3;
	
	if (operation != "AND") {
		if(operation != "OR") {
			std::cerr << "error : Rule::Rule() : INPUT ERROR" << std::endl;
			return;
		}
	}

	if (get_title(1) == "" || get_title(2) == "" || get_title(3) == "") {
		std::cerr << "error : Rule::Rule() : INPUT ERROR" << std::endl;
		return;
	}

	if (get_argsize(1) == 0 || get_argsize(2) == 0 || get_argsize(3) == 0) {
		std::cerr << "error : Rule::Rule() : INPUT ERROR" << std::endl;
		return;
	}
}

// ========================= //
//      Lonely destructor    //
// ========================= //
Rule::~Rule() {

}

std::string Rule::get_operation() {
	return operation;
}

std::string Rule::get_title(int block) {

	switch (block) {
	case 1:
		return first_title;
		break;
	case 2:
		return second_title;
		break;
	case 3:
		return third_title;
		break;
	default:
		return "";
		break;
	}
}
// ================================================================== //
//      Grab args from a source string and return them as a vector    //
// ================================================================== //
std::vector<std::string> Rule::get_args(std::string& source, int& index) {

	std::vector<std::string> empty;
	std::vector<std::string> tmp_vector;
	std::string curr_string;

	char tmp = source[index];

	while (tmp != ')') {

		if (index >= source.size())
			return empty;

		curr_string.push_back(tmp);
		tmp = source[++index];
		if (tmp == ',') {
			if (curr_string != "")
				tmp_vector.push_back(curr_string);
			tmp = source[++index];
			curr_string.clear();
		}
	}

	if(curr_string != "")
		tmp_vector.push_back(curr_string);

	return tmp_vector;
}

// ========================================== //
//      GETTER: Get args from current Rule    //
// ========================================== //
std::vector<std::string> Rule::get_args(int block) {
	
	std::vector<std::string> empty;

	switch (block) {
	case 1:
		return first_args;
		break;
	case 2:
		return second_args;
		break;
	case 3:
		return third_args;
		break;
	default:
		return empty;
		break;
	}
}


int Rule::get_argsize(int block) {

	switch (block) {
	case 1:
		return first_args.size();
		break;
	case 2:
		return second_args.size();
		break;
	case 3:
		return third_args.size();
		break;
	default:
		return 0;
		break;
	}
}


void Rule::print() {
	std::cout << "===== RULE =====" << std::endl;

	std::cout << "Rule name: " << first_title << std::endl;;
	std::cout << "Rule args:";
	for (int i = 0; i < first_args.size(); i++) {
		std::cout << " " << first_args[i];
	}
	std::cout << std::endl;
	std::cout << "Operation: " << operation << std::endl;
	std::cout << "LH Fact name: " << second_title << std::endl;
	std::cout << "LH fact args:";
	for (int i = 0; i < second_args.size(); i++) {
		std::cout << " " << second_args[i];
	}
	std::cout << std::endl;
	std::cout << "RH fact name: " << third_title << std::endl;
	std::cout << "RH fact args:" ;
	for (int i = 0; i < third_args.size(); i++) {
		std::cout << " " <<  third_args[i];
	}
	std::cout << std::endl;
	std::cout << "================" << std::endl;
}