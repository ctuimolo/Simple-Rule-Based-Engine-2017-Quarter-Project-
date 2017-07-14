/* ============================================ *
 *												*
 *  CMPS 109 - Quarter Project - PHASE #3       *
 *  Simple Rule-Base Inference (SRI) Engine     *
 *  3/10/2017                                   *
 *										     	*
 *	Chaiz Tuimoloau : ctuimolo@ucsc.edu         *
 *	Eisaku Imura    : eimura@ucsc.edu           *
 *                                              *
 * ============ SRI Class Source ============== */

#include "SRI.h"

// ============================================ //
//     Parse source string for function call    //
//     FACT, DUMP, RULE, INFERENCE, etc...      //
// ============================================ //
std::string SRI::get_function_call(std::string& input, std::string::iterator& curr_index) {

	std::string function_call;
	std::string empty;
	char tmp = input[0];

	int index_start;
	int arg_length = 0;

	while (tmp == ' ') {
		if (curr_index == input.end()) break;
		else curr_index++;
		tmp = input[std::distance(input.begin(), curr_index)];
	}

	index_start = std::distance(input.begin(), curr_index);

	while (tmp != ' ') {
		if (curr_index == input.end()) break;
		else curr_index++;
		arg_length++;
		tmp = input[std::distance(input.begin(), curr_index)];
	}

	while (tmp == ' ') {
		if (curr_index == input.end()) break;
		else curr_index++;
		tmp = input[std::distance(input.begin(), curr_index)];
	}

	function_call = input.substr(index_start, arg_length);
	return function_call;
}

// ====================================================== //
//     Clean unecessary empty spaces from source string   //
// ====================================================== //
std::string SRI::remove_space(std::string& source, std::string::iterator& start_index) {

	std::string return_string;
	char tmp = source[std::distance(source.begin(), start_index)];

	for (std::string::iterator i = start_index; i != source.end(); i++) {

		tmp = source[std::distance(source.begin(), i)];
		if (tmp != ' ') return_string.push_back(tmp);
	}

	return return_string;
}

// ===================================================== //
//     Check KB for if NEW_FACT's values already exist   //
// ===================================================== //
bool SRI::fact_exists(std::string title, std::vector<std::string> args) {

	for (int i = 0; i < KB.size(); i++) {
		if (KB[i]->get_title() == title) {
			int count = 0;
			for (int j = 0; j < KB[i]->get_args().size() && j < args.size(); j++) 
				if (KB[i]->get_args()[j] == args[j]) 
					count++;

			if (count == KB[i]->get_argsize()) 
				return true;
		}
	}
	return false;
}

// ===================================================== //
//     Check RB for if NEW_RULE's values already exist   //
// ===================================================== //
bool SRI::rule_exists(std::string title1, std::vector<std::string> args1, std::string title2, std::vector<std::string> args2, std::string title3, std::vector<std::string> args3) {

	for (int i = 0; i < RB.size(); i++) {
		if (RB[i]->get_title(1) == title1 && RB[i]->get_title(2) == title2 && RB[i]->get_title(3) == title3) {
			int count1 = 0;
			int count2 = 0;
			int count3 = 0;
			for (int j = 0; j < RB[i]->get_args(1).size() && j < args1.size(); j++) 
				if (RB[i]->get_args(1)[j] == args1[j]) 
					count1++;

			for (int j = 0; j < RB[i]->get_args(2).size() && j < args2.size(); j++)
				if (RB[i]->get_args(1)[j] == args2[j]) 
					count2++;

			for (int j = 0; j < RB[i]->get_args(3).size() && j < args3.size(); j++)
				if (RB[i]->get_args(1)[j] == args3[j]) 
					count3++;

			if (count1 == RB[i]->get_args(1).size() && count2 == RB[i]->get_args(2).size() && count3 == RB[i]->get_args(3).size())
				return true;
		}
	}
	return false;
}

// =========================================== //
//     Get parse input from an input string    //
// =========================================== //
void SRI::get_input(std::string load_input) {

	// char* buffer for input
	std::string input;
	
	// check for '#' comment
	if (!load_input.empty()) {
		int index = 0;
		char tmp = load_input[0];
		while (tmp != '#' && index < load_input.size()) {
			input.push_back(tmp);
			tmp = load_input[++index];
		}
	}

	// String iterator for whole source input
	std::string::iterator curr_index = input.begin();

	// Parse function call 
	std::string function_call = get_function_call(input, curr_index);

	
	// ==================================== //
	//     Switch case for Fnction Names    //
	// ==================================== //
	if (function_call == "LOAD") {
		LOAD(remove_space(input, curr_index));
	}

	else if (function_call == "DUMP") {
		DUMP(remove_space(input, curr_index));
	}
	
	else if (function_call == "FACT") {

		// Try initialize new fact
		Fact* tmp_fact = new Fact (remove_space(input, curr_index));

		// Ignore fact if FACT invalid
		if (tmp_fact->get_argsize() == 0 || tmp_fact->get_title().empty())
			delete tmp_fact;
		else
			// Check if fact already exists in KB
			if ( fact_exists(tmp_fact->get_title(), tmp_fact->get_args()) == false )
				KB.push_back(tmp_fact);
			else
				delete tmp_fact;
	}

	else if (function_call == "RULE") {

		// Try initialize new rule
		Rule* tmp_rule = new Rule (remove_space(input, curr_index));

		// Ignore rule if RULE invalid
		if (tmp_rule->get_argsize(1) == 0 || tmp_rule->get_argsize(2) == 0 || tmp_rule->get_argsize(3) == 0)
			delete tmp_rule;
		else if (tmp_rule->get_title(1).empty() || tmp_rule->get_title(2).empty() || tmp_rule->get_title(3).empty())
			delete tmp_rule;
		else
			// Check if rule already exists in RB
			if (rule_exists(tmp_rule->get_title(1), tmp_rule->get_args(1), tmp_rule->get_title(2), tmp_rule->get_args(2), tmp_rule->get_title(3), tmp_rule->get_args(3)) == false)
				RB.push_back(tmp_rule);
			else
				delete tmp_rule;
	}

	else if (function_call == "INFERENCE") {
		INFERENCE(remove_space(input, curr_index));
	}

	else if (function_call == "DROP") {
		DROP(remove_space(input, curr_index));
	}
	else if (function_call == "EXIT") {
		EXIT();
	}
	else if (function_call.empty()) {

	}
	else {
		std::cerr << "error: SRI::get_input(): INVALID INPUT" << std::endl;
	}
}

// ================================== //
//       INFERENCE function logic     //
// ================================== //
void SRI::INFERENCE(std::string source) {

	// INFERENCE QUEREY TEMPLATE
	//===========================================================//												
	//   INFERENCE     Grandma      ($X,$Y)           GF         //
	//                    ^^^         ^^^             ^          //
	//               query_title    query_args     return_title  //
	//===========================================================//	

	// Refresh SRIs queries

	std::vector<std::string>().swap(query_args);
	query_title = "";

	std::vector< std::vector<std::string> >().swap(return_args);
	return_title = "";

	// char and index initialization
	char tmp = source[0];
	int index = 0;

	// Grab query title
	while (tmp != '(') {
		query_title.push_back(tmp);
		tmp = source[++index];
		if (index >= source.size()) {
			std::cerr << "error : SRI::INFERENCE() : INPUT ERROR" << std::endl;
			return;
		}
	}

	// String buffer for pushing into title, args, etc...
	std::string curr_string;

	tmp = source[++index];
	if (index >= source.size()) {
		std::cerr << "error : SRI::INFERENCE() : INPUT ERROR" << std::endl;
		return;
	}

	while (tmp != ')') {
		curr_string.push_back(tmp);
		tmp = source[++index];
		if (tmp == ',') {
			query_args.push_back(curr_string);
			tmp = source[++index];
			curr_string.clear();
		}
		if (index >= source.size()) {
			std::cerr << "error : SRI::INFERENCE() : INPUT ERROR" << std::endl;
			return;
		}
	}

	query_args.push_back(curr_string);

	tmp = source[++index];
	while (index < source.size()) {
		return_title.push_back(tmp);
		tmp = source[++index];
	}
	
	bool add_facts = false;
	if (!return_title.empty())
		add_facts = true;

	std::vector<Rule*> matching_rules;

	for (int i = 0; i < RB.size(); i++) {
		if (query_title == RB[i]->get_title(1) && query_args.size() == RB[i]->get_argsize(1)) {
			matching_rules.push_back(RB[i]);
		}
	}

	for (int i = 0; i < matching_rules.size(); i++) {

		std::string operation = matching_rules[i]->get_operation();

		if (operation == "AND")
			return_args = do_AND(matching_rules[i], query_title, query_args, add_facts);
		else if (operation == "OR")
			return_args = do_OR(matching_rules[i], query_title, query_args, add_facts);
		else
			std::cerr << "Inference: Operation error" << std::endl;
	}

	if (add_facts) {
		for (int i = 0; i < return_args.size(); i++) {
			Fact* tmp_fact = new Fact(return_title, return_args[i]);
			if (fact_exists(tmp_fact->get_title(), tmp_fact->get_args()) == false)
				KB.push_back(tmp_fact);
			else
				delete tmp_fact;
		}
	}
}

// ============================================== //
//       AND collision/column matching logic      //
// ============================================== //
std::vector< std::vector<std::string> > SRI::do_AND(Rule* source_rule, std::string query_title, std::vector<std::string> query_args, bool add_facts) {

	std::vector< std::vector<std::string> > solution_vector;
	std::vector< std::vector<std::string> > solution_vector_fixed;

	std::string operation = source_rule->get_operation();

	std::string rule_title = source_rule->get_title(1);
	std::vector<std::string> rule_args = source_rule->get_args(1);

	std::string first_fact = source_rule->get_title(2);
	std::vector<std::string> first_fact_args = source_rule->get_args(2);

	std::string second_fact = source_rule->get_title(3);
	std::vector<std::string> second_fact_args = source_rule->get_args(3);


	// Lefthand fact (first_fact) match with all facts in KB
	std::vector<Fact*> matching_left_facts;
	std::cout << "SRI::do_AND() : std::thread andthread1 started..." << std::endl;
    std::thread andthread1 (push_matching_facts, KB, &matching_left_facts, first_fact, first_fact_args);

	// Righthand fact (second_fact) match with all facts in KB
	std::vector<Fact*> matching_right_facts;
	std::cout << "SRI::do_AND() : std::thread andthread2 started..." << std::endl;
	std::thread andthread2 (push_matching_facts, KB, &matching_right_facts, second_fact, second_fact_args);

    //Multithread
    andthread1.join();
	std::cout << "SRI::do_AND() : std::thread andthread1 completed" << std::endl;
    andthread2.join();
	std::cout << "SRI::do_AND() : std::thread andthread2 completed" << std::endl;
        
	// Populate local rule variables names
	std::vector<std::string> var_names;

    std::thread andthread3 (populate, &var_names, first_fact_args);
	std::cout << "SRI::do_AND() : std::thread andthread3 started..." << std::endl;

    std::thread andthread4 (populate, &var_names, second_fact_args);
	std::cout << "SRI::do_AND() : std::thread andthread4 started..." << std::endl;


    //Multithread
    andthread3.join();
	std::cout << "SRI::do_AND() : std::thread andthread3 completed" << std::endl;

    andthread4.join();
	std::cout << "SRI::do_AND() : std::thread andthread4 completed" << std::endl;

	// Reflect var names into var values vector (size = 2)
	std::vector< std::vector<std::string> > var_values(var_names.size());
	

	for (int i = 0; i < var_values.size(); i++) {
		var_values[i].push_back("");
		var_values[i].push_back("");
	}

	// start with a matching lefthand fact (LH[i])
	for (int i = 0; i < matching_left_facts.size(); i++) {
		// traverse all matching righthand fact (RH[j]
		for (int j = 0; j < matching_right_facts.size(); j++) {

			for (int index_t = 0; index_t < first_fact_args.size(); index_t++) {
				int index = 0;
				while (first_fact_args[index_t] != var_names[index])
					index++;
				var_values[index][0] = matching_left_facts[i]->get_args()[index_t];
			}

		   for (int index_t = 0; index_t < second_fact_args.size(); index_t++) {
				int index = 0;
				while (second_fact_args[index_t] != var_names[index])
					index++;
				var_values[index][1] = matching_right_facts[j]->get_args()[index_t];
			}

			std::vector<std::string> solution_args;
                        solution_args.resize(var_names.size());

			for (int k = 0; k < var_values.size(); k++) {
                             
				if (!var_values[k][0].empty() && var_values[k][0].size() != 0) {
					if (var_values[k][1] == var_values[k][0] || var_values[k][1].empty()) {
						// this column true
					
						solution_args[k] = var_values[k][0];
					}
				} else
					// this column true
					
					solution_args[k] = var_values[k][1];
			}

			bool push_this = false;

			for (int k = 0; k < solution_args.size(); k++) {
				if (solution_args[k].empty()) break;
				else if (k == solution_args.size() - 1)
					push_this = true;
			}

			if (push_this) 
				solution_vector.push_back(solution_args);

			for (int k = 0; k < var_values.size(); k++){
				std::vector<std::string>().swap(var_values[k]);
                                var_values[k].push_back("");
                                var_values[k].push_back("");
                        }
		}
	}

	solution_vector_fixed.resize(solution_vector.size());
	solution_vector_fixed.shrink_to_fit();

	for (int i = 0; i < solution_vector.size(); i++) {
		for (int index_t = 0; index_t < rule_args.size(); index_t++) {
			int index = 0;
			while (rule_args[index_t] != var_names[index])
				index++;
			solution_vector_fixed[i].push_back(solution_vector[i][index]);
		}
	}

	if (!add_facts) {
		for (int i = 0; i < solution_vector_fixed.size(); i++) {
			for (int j = 0; j < solution_vector_fixed[i].size(); j++)
				std::cout << query_args[j] << ":" << solution_vector_fixed[i][j] << " ";
			std::cout << std::endl;
		}
	}
	else return solution_vector_fixed;
}

//Multithread function used in AND
void SRI::populate(std::vector<std::string>* var_names, std::vector<std::string> fact_args){
   for(int H_argi = 0; H_argi < fact_args.size(); H_argi++){
      if(std::find((*var_names).begin(), (*var_names).end(), fact_args[H_argi]) == (*var_names).end())
         (*var_names).push_back(fact_args[H_argi]);
   }
}

//Multithread function used in both AND and OR
void SRI::push_matching_facts(std::vector<Fact*> KB, std::vector<Fact*>* matching_facts, std::string fact_name, std::vector<std::string> fact_args) {
	for (int i = 0; i < KB.size(); i++)
		if (fact_name == KB[i]->get_title() && fact_args.size() == KB[i]->get_argsize())
			(*matching_facts).push_back(KB[i]);
}


// ==================================== //
//       OR Branching  Factslogic       //
// ==================================== //
std::vector< std::vector<std::string> > SRI::do_OR(Rule* source_rule, std::string query_title, std::vector<std::string> query_args, bool add_facts) {

	std::vector< std::vector<std::string> > solution_vector;
	std::vector< std::vector<std::string> > solution_vector_fixed;

	std::string operation = source_rule->get_operation();

	std::string rule_title = source_rule->get_title(1);
	std::vector<std::string> rule_args = source_rule->get_args(1);

	std::string first_fact = source_rule->get_title(2);
	std::vector<std::string> first_fact_args = source_rule->get_args(2);

	std::string second_fact = source_rule->get_title(3);
	std::vector<std::string> second_fact_args = source_rule->get_args(3);

	// Populate local rule variables names
	std::vector<std::string> var_names;

	// Lefthand fact (first_fact) match with all facts in KB
	std::vector<Fact*> matching_left_facts; 
	std::cout << "SRI::do_OR() : std::thread orthread1 started..." << std::endl;
	std::thread orthread1 (push_matching_facts, KB, &matching_left_facts, first_fact, first_fact_args);

	// Righthand fact (second_fact) match with all facts in KB
	std::vector<Fact*> matching_right_facts;
	std::cout << "SRI::do_OR() : std::thread orthread1 started..." << std::endl;
    std::thread orthread2 (push_matching_facts, KB, &matching_right_facts, second_fact, second_fact_args);

    orthread1.join();
	std::cout << "SRI::do_OR() : std::thread orthread1 completed" << std::endl;

    orthread2.join();
	std::cout << "SRI::do_OR() : std::thread orthread2 completed" << std::endl;

	for (int LH_argi = 0; LH_argi < first_fact_args.size(); LH_argi++)
		if (std::find(var_names.begin(), var_names.end(), first_fact_args[LH_argi]) == var_names.end())
			var_names.push_back(first_fact_args[LH_argi]);

	for (int i = 0; i < matching_left_facts.size(); i++)
		solution_vector.push_back(matching_left_facts[i]->get_args());

	for (int RH_argi = 0; RH_argi < second_fact_args.size(); RH_argi++)
		if (std::find(var_names.begin(), var_names.end(), second_fact_args[RH_argi]) == var_names.end())
			var_names.push_back(second_fact_args[RH_argi]);

	for (int i = 0; i < matching_right_facts.size(); i++)
		solution_vector.push_back(matching_right_facts[i]->get_args());

	solution_vector_fixed.resize(solution_vector.size());
	solution_vector_fixed.shrink_to_fit();

	for (int i = 0; i < solution_vector.size(); i++) {
		for (int index_t = 0; index_t < rule_args.size(); index_t++) {
			int index = 0;
			while (rule_args[index_t] != var_names[index])
				index++;
			solution_vector_fixed[i].push_back(solution_vector[i][index]);
		}
	}

	if (!add_facts) {
		for (int i = 0; i < solution_vector_fixed.size(); i++) {
			for (int j = 0; j < solution_vector_fixed[i].size(); j++)
				std::cout << query_args[j] << ":" << solution_vector_fixed[i][j] << " ";
			std::cout << std::endl;
		}
	}
	else return solution_vector_fixed;
}

// ========================================================== //
//       To load a file and parse lines into Source Input     //
// ========================================================== //
void SRI::LOAD(std::string source) {

	std::string input;

	std::ifstream file;
	file.open(source.c_str());
	if (!file.is_open()) {
		std::cerr << "error : SRI:LOAD() : CANNOT OPEN FILE: " << source << std::endl;
		return;
	}
	while (!file.eof()) {
		getline(file, input);
		get_input(input);
	}
	file.close();
}

// ========================================================== //
//       Dump all RULES and FACTS from RB and KB to a file    //
// ========================================================== //
void SRI::DUMP(std::string source) {

	std::string tmp;
	std::ofstream file;

	file.open(source.c_str());
	
	for (int i = 0; i < KB.size(); i++) {
		file << "FACT " << KB[i]->get_title() << "(";
		for (int j = 0; j < KB[i]->get_argsize(); j++) {
			if (j != 0) {
				file << ",";
			}
			file << KB[i]->get_args()[j];
		}
		file << ")" << std::endl;
	}



	for (int i = 0; i < RB.size(); i++) {
		file << "RULE " << RB[i]->get_title(1) << "(";
		for (int j = 0; j < RB[i]->get_argsize(1); j++) {
			if (j != 0) {
				file << ",";
			}
			file << RB[i]->get_args(1)[j];
		}
		file << "):- " << RB[i]->get_operation() << " " << RB[i]->get_title(2) << "(";
		for (int j = 0; j < RB[i]->get_argsize(2); j++) {
			if (j != 0) {
				file << ",";
			}
			file << RB[i]->get_args(2)[j];
		}
		file << ")" << RB[i]->get_title(3) << "(";
		for (int j = 0; j < RB[i]->get_argsize(3); j++) {
			if (j != 0) {
				file << ",";
			}
			file << RB[i]->get_args(3)[j];
		}
		file << ")" << std::endl;
	}

	file.close();
}

// ============================================ //
//       To remove a FACT or RULE of a name     //
// ============================================ //
void SRI::DROP(std::string source) {

	for (int i = KB.size() - 1; i >= 0; i--) 
		if (KB[i]->get_title() == source) {
			delete KB[i];
			KB.erase(KB.begin() + i);
		}

	for (int i = RB.size() - 1; i >= 0; i--) 
		if (RB[i]->get_title(1) == source) {
			delete RB[i];
			RB.erase(RB.begin() + i);
		}
}


void SRI::START() {
	running = true;
}

void SRI::EXIT() {
	running = false;
	for (int i = KB.size() - 1; i >= 0; i--) {
		delete KB[i];
		KB.erase(KB.begin() + i);
	}

	for (int i = RB.size() - 1; i >= 0; i--) {
		delete RB[i];
		RB.erase(RB.begin() + i);
	}
}

bool SRI::is_running() {
	return running;
}


SRI::~SRI() {

	for (int i = KB.size() - 1; i >= 0; i--) {
			delete KB[i];
			KB.erase(KB.begin() + i);
	}

	for (int i = RB.size() - 1; i >= 0; i--) {
			delete RB[i];
			RB.erase(RB.begin() + i);
	}
}
