/* ============================================ *
 *												*
 *  CMPS 109 - Quarter Project - PHASE #3       *
 *  Simple Rule-Base Inference (SRI) Engine     *
 *  3/10/2017                                   *
 *										     	*
 *	Chaiz Tuimoloau : ctuimolo@ucsc.edu         *
 *	Eisaku Imura    : eimura@ucsc.edu           *
 *                                              *
 * ============== MAIN PROGRAM ================ */

// ========================= //
//     include libraries     //
// ========================= //

//#include "includes.h"
#include "common.h"
#include "SRI.h"

// ========================= //
//     main program loop     //
// ========================= //

int main(int argc, char* argv[]) {

	// Initialize our SRI engine
	SRI* engine = new SRI();

	// <string>input serves as char* buffer for SRI interaction
	std::string input;

	// For each <ifstream>file from commandline args
	for (int i = 1; i < argc; i++) {

		std::ifstream file;
		file.open(argv[i]);
		if (!file.is_open()) {
			std::cerr << "error : main() : CANNOT OPEN FILE: " << argv[i] << std::endl;
			continue;
		}
		while (!file.eof()) {
			// Pass file input >> char* buffer >> SRI engine input
			getline(file, input);
			engine->get_input(input);
		}
		file.close();
	}

	// Engage engine command line loop mode
	engine->START();

	// Program input loop
	while (engine->is_running()) {
		// Pass user input >> char* buffer >> SRI engine input
		getline(std::cin, input);
		engine->get_input(input);
	}

	// Free memory
	delete engine;
}