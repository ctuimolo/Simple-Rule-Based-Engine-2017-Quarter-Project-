/* ============================================ *
 *												*
 *  CMPS 109 - Quarter Project - PHASE #3       *
 *  Simple Rule-Base Inference (SRI) Engine     *
 *  3/10/2017                                   *
 *										     	*
 *	Chaiz Tuimoloau : ctuimolo@ucsc.edu         *
 *	Eisaku Imura    : eimura@ucsc.edu           *
 *                                              *
 * ============ Fact Class Header ============= */

// ========================= //
//     include libraries     //
// ========================= //

#include "common.h"

class Fact {

private:

	// FACT TEMPLATE
	//==============================//												
	//   FACT   Grandma($X,$Y)      //
	//              ^^^^            //
	//         title(store_fact)    //
	//==============================//	

	std::string title_fact;
	std::vector<std::string> store_fact;

public:

	// ======================= //
	//    CON(DE)STRUCTORS     //
	// ======================= //
	Fact(std::string title, std::vector<std::string> args);
	Fact(std::string source);
	~Fact();

	// ========================= //
	//     PARAMETER GETTERS     //
	// ========================= //
	std::string get_title();
	std::vector<std::string> get_args();
	int get_argsize();

	// Print to std::cout
	void print();

};
