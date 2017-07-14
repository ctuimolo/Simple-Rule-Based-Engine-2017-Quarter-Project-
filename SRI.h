/* ============================================ *
 *												*
 *  CMPS 109 - Quarter Project - PHASE #3       *
 *  Simple Rule-Base Inference (SRI) Engine     *
 *  3/10/2017                                   *
 *										     	*
 *	Chaiz Tuimoloau : ctuimolo@ucsc.edu         *
 *	Eisaku Imura    : eimura@ucsc.edu           *
 *                                              *
 * ============ SRI Class Header ============== */

// ========================= //
//     include libraries     //
// ========================= //

#include "common.h"
#include "Rule.h"
#include "Fact.h"

class SRI {

private:

	// For loop mode
	bool running;

	// ============================= //
	//      Knowledge Base (KB)      //
	//      Rule Base      (RB)      //
	// ============================= //
	std::vector<Rule*> RB;
	std::vector<Fact*> KB;

	// For INFERENCE logic
	std::string query_title;
	std::vector<std::string> query_args;

	std::string return_title;
	std::vector< std::vector<std::string> > return_args;

	std::vector< std::vector<std::string> > do_AND(Rule*, std::string, std::vector<std::string>, bool);
	std::vector< std::vector<std::string> > do_OR(Rule*, std::string, std::vector<std::string>, bool);

	// For FACT and RULE parameter parsing from std::strings
	std::string get_function_call(std::string&, std::string::iterator&);
	std::string remove_space(std::string&, std::string::iterator&);

	bool rule_exists(std::string, std::vector<std::string>,
				     std::string, std::vector<std::string>,
					 std::string, std::vector<std::string>);

	bool fact_exists(std::string, std::vector<std::string>);

	static void push_matching_facts(std::vector<Fact*> KB, std::vector<Fact*>* matching_facts, std::string fact_name, std::vector<std::string> fact_args);

        static void populate(std::vector<std::string>* var_names, std::vector<std::string> fact_args);


public:

	// ======================= //
	//    CON(DE)STRUCTORS     //
	// ======================= //
	SRI() : running(false) {};
	~SRI();

	// ======================== //
	//     ENGAGE LOOP MODE     //
	// ======================== //
	void START();
	bool is_running();

	// ================================== //
	//    PASS STRING TO ENGINE PARSER    //
	// ================================== //
	void get_input(std::string);

	// ====================== //
	//    ENGINE FUNCTIONS    //
	// ====================== //
	void LOAD(std::string);
	void DUMP(std::string);
	void DROP(std::string);
	void INFERENCE(std::string);
	void EXIT();

};

  //void push_matching_facts(std::vector<Fact*>* know, std::vector<Fact*>* matching_facts, std::string* fact_name, std::vector<std::string>* fact_args);

