/* ============================================ *
 *												*
 *  CMPS 109 - Quarter Project - PHASE #3       *
 *  Simple Rule-Base Inference (SRI) Engine     *
 *  3/10/2017                                   *
 *										     	*
 *	Chaiz Tuimoloau : ctuimolo@ucsc.edu         *
 *	Eisaku Imura    : eimura@ucsc.edu           *
 *                                              *
 * ============ Rule Class Header ============= */

// ========================= //
//     include libraries     //
// ========================= //

#include "common.h"

class Rule {

private:

	// RULE TEMPLATE
	//=======================================================================//												
	//   RULE   Grandma($X,$Y) :-  AND    Mother($X,$Z)     Parent($Z,$Y)    //
	//              ^^^^           ^^^        ^^^^               ^^^^        //
	//           first(args)    operation   second(args)       third(args)   //
	//=======================================================================//	

	std::string first_title;  
	std::vector<std::string> first_args;

	std::string operation;

	std::string second_title;
	std::vector<std::string> second_args;

	std::string third_title;
	std::vector<std::string> third_args;


public:

	// ======================= //
	//    CON(DE)STRUCTORS     //
	// ======================= //
	Rule(std::string source);
	~Rule();

	// ========================= //
	//     PARAMETER GETTERS     //
	// ========================= //
	std::string get_operation();
	std::string get_title(int);
	std::vector<std::string> get_args(int);
	std::vector<std::string> get_args(std::string& source, int& index);
	int get_argsize(int);


	// Print to std::cout
	void print();

};