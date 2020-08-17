#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <stdint.h>

#define N_FIELDS 				3
#define FIELD_LENGTH 			100

// command delimiters
#define COMMAND_DELIMITERS 		" \t\r\n"

// lookup table for command
// LOAD & VERIFY are from fpga_elf.h
static const char *pCodes[] 	= {"CLOSE", "READ", "WRITE","LOAD", "VERIFY",	"CONFIG", 	"RUN"	};
static const char n_fields[] 	= {1, 		2, 		3, 		2, 		2, 			3,  		2		};
static const bool field1_hex[] 	= {false, 	true, 	true, 	false, 	false, 		true, 		false	}; 
static const bool field2_hex[] 	= {false, 	false, 	true, 	false, 	false,	 	true, 		false 	};


typedef struct command{
	char 		table_index; 						// lookup table match index
	char 		n_fields; 							// number of fields extracted from parse
	char 		field[N_FIELDS][FIELD_LENGTH]; 		// parsed fields as strings
	uint32_t 	field1_number; 						// field0 converted to number
	uint32_t 	field2_number; 						// field1 converted to number
} command;


// lookup table for the command
// mneumonic, fields, hex, etc.
/*static const char* codes[] 		= {	"READ",	"WRITE",	"READB",	"LOAD",		"VERIFY",	"CONFIG", 	"RUN",		"TEST", 	"RUN_SAMPLER", 	"SAMPLE_ALL",
									"RUN_SCOPE_ALL" };
static const char n_fields[] 	= {	2, 		3, 			3, 			2, 			2, 			3, 			2, 			1, 			2, 				1,
									1 };
static const bool field1_hex[] 	= {	true, 	true, 		true, 		false, 		false, 		true, 		false, 		false, 		false, 			false,
									false };
static const bool field2_hex[] 	= {	false, 	true, 		true, 		false, 		false, 		true, 		false, 		false, 		false, 			false,
									false };*/



uint32_t 		parse_input(command *pCommand, char *pBuffer);
// description: 	- blocking
// 					- parse and error check the command
// return: 			0: success, 1: fail
// pCommand: 		command data structure to populate
// pBuffer: 		command string to parse

#endif