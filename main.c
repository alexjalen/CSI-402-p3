//Alex Pospesel
//ID: 001146589
//NetID: ap212246
//Email: apospesel@albany.edu
//CSI 402
//Program 3
//Due 3/27/16

#include "headers.h"
#include "prototypes.h"

int main (int argc, char *argv[]){
	
	//variables
	FILE *configfile;
	FILE *queryfile;
	
	//tests for correct number of arguments
	if(argc != 3){
		die("Incorrect number of arguments.");
	}
	
	//check and open config file for validity
	configfile = checkOpen(argv[1], "r", "Could not open config file.");

	//check and open query file
	queryfile = checkOpen(argv[2], "r", "Could not open query file.");

	//store table names
	int numOfTables = numTables(configfile);
	
	//stores table names
	char ** tableNames = tables(configfile, numOfTables);
	
	//close config file, done with it
	fclose(configfile);
	
	//declare variables for struct table into an array of structs
	//then read tables and save into tables array.
	//read table schema file
	table ** tables = tableConfig(tableNames, numOfTables);
	
	//query
	readQueryFile(queryfile, tables, tableNames, numOfTables);
	
	
	
	
	//close query file
	fclose(queryfile);

	return 0;
	
}//end main