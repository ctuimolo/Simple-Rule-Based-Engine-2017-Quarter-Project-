/* ============================================ *
 *												*
 *  CMPS 109 - Quarter Project - PHASE #3       *
 *  Simple Rule-Base Inference (SRI) Engine     *
 *  3/10/2017                                   *
 *										     	*
 *	Chaiz Tuimoloau : ctuimolo@ucsc.edu         *
 *	Eisaku Imura    : eimura@ucsc.edu           *
 *                                              *
 * ============ Fact Class Source ============= */

#include "Fact.h"

 // ================================================== //
 //      Constructor if given individual parameters    //
 // ================================================== //
Fact::Fact(std::string title, std::vector<std::string> args) {
	title_fact = title;
	store_fact = args;
}

// ================================================== //
//      Constructor if given full string to parse     //
// ================================================== //
Fact::Fact(std::string source) {

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

	while (tmp != '(') {

		if (index >= source.size()) {
			std::cerr << "error : Fact::Fact() : INPUT ERROR" << std::endl;
			return;
		}

		curr_string.push_back(tmp);
		tmp = source[++index];
	}

	title_fact = curr_string;

	tmp = source[++index];
	curr_string.clear();

	while (tmp != ')') {

		if (index >= source.size()) {
			std::cerr << "error : Fact::Fact() : INPUT ERROR" << std::endl;
			return;
		}

		curr_string.push_back(tmp);
		tmp = source[++index];
		if (tmp == ',') {
			if(curr_string != "")
				store_fact.push_back(curr_string);
			tmp = source[++index];
			curr_string.clear();
		}
	}

	if (curr_string != "")
		store_fact.push_back(curr_string);
}

std::string Fact::get_title() {
	return title_fact;
}

std::vector<std::string> Fact::get_args() {

	return store_fact;
}

int Fact::get_argsize() {

	return store_fact.size();
}


Fact::~Fact() {

}

void Fact::print() {
	std::cout << "===== FACT =====" << std::endl;
	std::cout << "Fact title: " << title_fact << std::endl;
	std::cout << "Fact args: ";
	for (int i = 0; i < store_fact.size(); i++) 
		std::cout << store_fact[i] << " ";
	std::cout << std::endl;
	std::cout << "================" << std::endl;
}