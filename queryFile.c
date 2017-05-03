//Alex Pospesel
//ID: 001146589
//NetID: ap212246
//Email: apospesel@albany.edu
//CSI 402
//Program 3
//Due 3/27/16

#include "headers.h"
#include "prototypes.h"

void readQueryFile(FILE* queryfile, table** tableArray, char** tableNames, int numOfTables){
	//read query file's first command
	char command[MAX_STR_SIZE];
	
	//make sure it stops at EOF
	while(!feof(queryfile)){
		//read file line by line
		fscanf(queryfile, "%s", command);
		

		if(strcmp(command, "select") == 0){
			
			//call selectQuery function
			selectQuery(queryfile, tableArray, tableNames, numOfTables);

		}else if(strcmp(command, "numRows") == 0){
			
			//call numRows function
			numRowsQuery(queryfile, tableArray, tableNames, numOfTables);

		}else if(strcmp(command, "rowStat") == 0){
			
			//call rowStat function
			rowStatQuery(queryfile, tableArray, tableNames, numOfTables);


		}else if(strcmp(command, "numCols") == 0){
			
			//call numColsQuery function
			numColsQuery(queryfile, tableArray, tableNames, numOfTables);
			

		}else if(strcmp(command, "colStat") == 0){
			
			//call colStatQuery function
			colStatQuery(queryfile, tableArray, tableNames, numOfTables);

		}else if(strcmp(command, "project") == 0){
			
			//call projectQuery function
			projectQuery(queryfile, tableArray, tableNames, numOfTables);


		}else if(strcmp(command, "stop") == 0){
			//when encountouring stop in query
			//end nicely.
			stopQuery();
			
		}else{
			die("Problem reading query.\n");
		}
		
		//append '\n' char to end of query
		printf("\n");

	}//end scanf loop
	

}//end readQueryFile

void selectQuery(FILE* queryfile, table** tableArray, char** tableNames, int numOfTables){
	//TODO
	//variables
	char tableSel[MAX_STR_SIZE];
	char colSel[MAX_STR_SIZE];
	char cmpSel[MAX_STR_SIZE];
	char valSel[MAX_STR_SIZE];
	char* valSelNonQuote;
	int valSelInteger;
	int table;
	int col;
	int valSelCounter = 0;
	
	//loop counters
	int i;
	int j;
	int h;
	
	//scan line for query
	fscanf(queryfile, "%s %s %s %s", tableSel, colSel, cmpSel, valSel);
	
	//TESTING
	//printf("Scan complete\n");
	
	//get tableIndex integer
	table = tableIndex(tableSel, tableNames, numOfTables);
	
	//if table DNE
	if(table == -1){
		//print error is table DNE
		printf("Error:  Invalid table -- %s\n", tableSel);
		
		//return to query file
		return;
	}
	
	//get colIndex integer
	col = colIndex(colSel, table, tableArray);
	
	if(col == -1){
		//print error is table DNE
		printf("Error:  Invalid column -- %s\n", colSel);
		
		//return to query file
		return;
	}
	
	//remove quotes on valSel
	valSelNonQuote = removeQuotes(valSel);
	
	//check compare value
	if(strcmp(cmpSel, "==") == 0){
		
		//if valSel has a quote in it, must be string
		if(valSel[0] == '\"'){
			
			
			//now print all data with valSelNonQuote requirements
			for(i = 0; i < tableArray[table]->numRows; i++){

				//remove quotes on valSel
				valSelNonQuote = removeQuotes(valSel);
			
				//check if valSel is what we want
				if(strcmp(valSelNonQuote, tableArray[table]->rowArray[col]->attrArray[i]->data.str) == 0){
					
					
					//increment valSelCounter
					valSelCounter++;
					
					//print whole line if contains data we are looking for
					printLine(tableArray, i, table);
					
					
					//copy value back into valSelNonQuote for some weird behavior
					strcpy(valSelNonQuote, tableArray[table]->rowArray[col]->attrArray[i]->data.str);
					
				}
				
			}//end looping tables
				
		}else{
			//must be an int to compare to
			
			for(i = 0; i < tableArray[table]->numRows; i++){

				
				valSelInteger = atoi(valSel);
			
				//check if valSel is what we want
				if(valSelInteger == tableArray[table]->rowArray[col]->attrArray[i]->data.integer){
					
					//increment valSelCounter
					valSelCounter++;
					
					//print whole line if contains data we are looking for
					printLine(tableArray, i, table);
					
					//for undefined behavior, copy data back into valSelInteger
					valSelInteger = tableArray[table]->rowArray[col]->attrArray[i]->data.integer;
					
				}
				
			}//end looping tables
		}
		
	}else if(strcmp(cmpSel, "!=") == 0){
		//printf("!= detected\n");
		
		//if valSel has a quote in it, must be string
		if(valSel[0] == '\"'){
			
			
			//now print all data with valSelNonQuote requirements
			for(i = 0; i < tableArray[table]->numRows; i++){

				//remove quotes on valSel
				valSelNonQuote = removeQuotes(valSel);
			
				//check if valSel is what we want
				if(strcmp(valSelNonQuote, tableArray[table]->rowArray[col]->attrArray[i]->data.str) != 0){
					
					
					//increment valSelCounter
					valSelCounter++;
					
					//print whole line if contains data we are looking for
					printLine(tableArray, i, table);
					
					
					//copy value back into valSelNonQuote for some weird behavior
					//strcpy(valSelNonQuote, tableArray[table]->rowArray[col]->attrArray[i]->data.str);
					
				}
				
			}//end looping tables
				
		}else{
			//must be an int to compare to
			
			for(i = 0; i < tableArray[table]->numRows; i++){

				
				valSelInteger = atoi(valSel);
			
				//check if valSel is what we want
				if(valSelInteger != tableArray[table]->rowArray[col]->attrArray[i]->data.integer){
					
					//increment valSelCounter
					valSelCounter++;
					
					//print whole line if contains data we are looking for
					printLine(tableArray, i, table);
					
					//for undefined behavior, copy data back into valSelInteger
					//valSelInteger = tableArray[table]->rowArray[col]->attrArray[i]->data.integer;
					
				}
				
			}//end looping tables
		}
		
	}else if(strcmp(cmpSel, "<=") == 0){
		//printf("<= detected\n");
		
		//if valSel has a quote in it, must be string
		if(valSel[0] == '\"'){
			
			//cant have str in less than or greater than comparisons
			printf("Error:  Wrong type of value for attribute %s.\n", colSel);
			return;
		
		}else{
			//must be an int to compare to
			
			for(i = 0; i < tableArray[table]->numRows; i++){

				if(strcmp(tableArray[table]->rowArray[col]->attrArray[i]->type, "str") == 0){
					//str was enterd in a str field
					printf("Error:  Wrong type of value for attribute %s.\n", colSel);
					
					return;
				}
				
				valSelInteger = atoi(valSel);
				
				//TESTING
				//printf("valSelInteger is: %d\n", valSelInteger);
			
				//check if valSel is what we want
				if(valSelInteger >= tableArray[table]->rowArray[col]->attrArray[i]->data.integer){
					
					//increment valSelCounter
					valSelCounter++;
					
					//print whole line if contains data we are looking for
					printLine(tableArray, i, table);
					
					//for undefined behavior, copy data back into valSelInteger
					//valSelInteger = tableArray[table]->rowArray[col]->attrArray[i]->data.integer;
					
				}
				
			}//end looping tables
			
		}
		
	}else if(strcmp(cmpSel, ">=") == 0){
		//printf(">= detected\n");
		
		//if valSel has a quote in it, must be string
		if(valSel[0] == '\"'){
			
			//cant have str in less than or greater than comparisons
			printf("Error:  Wrong type of value for attribute %s.\n", colSel);
			return;
		
		}else{
			//must be an int to compare to
			
			for(i = 0; i < tableArray[table]->numRows; i++){

				if(strcmp(tableArray[table]->rowArray[col]->attrArray[i]->type, "str") == 0){
					//str was enterd in a str field
					printf("Error:  Wrong type of value for attribute %s.\n", colSel);
					
					return;
				}
				
				
				valSelInteger = atoi(valSel);
				
				//TESTING
				//printf("valSelInteger is: %d\n", valSelInteger);
			
				//check if valSel is what we want
				if(valSelInteger <= tableArray[table]->rowArray[col]->attrArray[i]->data.integer){
					
					//increment valSelCounter
					valSelCounter++;
					
					//print whole line if contains data we are looking for
					printLine(tableArray, i, table);
					
					//for undefined behavior, copy data back into valSelInteger
					valSelInteger = tableArray[table]->rowArray[col]->attrArray[i]->data.integer;
					
				}
				
			}//end looping tables
			
		}
		
	}else if(strcmp(cmpSel, ">") == 0){
		//printf("> detected\n");
		
		//if valSel has a quote in it, must be string
		if(valSel[0] == '\"'){
			
			//cant have str in less than or greater than comparisons
			printf("Error:  Wrong type of value for attribute %s.\n", colSel);
			return;
		
		}else{
			//must be an int to compare to
			
			for(i = 0; i < tableArray[table]->numRows; i++){

				if(strcmp(tableArray[table]->rowArray[col]->attrArray[i]->type, "str") == 0){
					//str was enterd in a str field
					printf("Error:  Wrong type of value for attribute %s.\n", colSel);
					
					return;
				}
				
				
				valSelInteger = atoi(valSel);
				
				//TESTING
				//printf("valSelInteger is: %d\n", valSelInteger);
			
				//check if valSel is what we want
				if(valSelInteger < tableArray[table]->rowArray[col]->attrArray[i]->data.integer){
					
					//increment valSelCounter
					valSelCounter++;
					
					//print whole line if contains data we are looking for
					printLine(tableArray, i, table);
					
					//for undefined behavior, copy data back into valSelInteger
					//valSelInteger = tableArray[table]->rowArray[col]->attrArray[i]->data.integer;
					
				}
				
			}//end looping tables
			
		}
		
	}else if(strcmp(cmpSel, "<") == 0){
		//printf("< detected\n");
		
		//if valSel has a quote in it, must be string
		if(valSel[0] == '\"'){
			
			//cant have str in less than or greater than comparisons
			printf("Error:  Wrong type of value for attribute %s.\n", colSel);
			return;
		
		}else{
			//must be an int to compare to
			
			for(i = 0; i < tableArray[table]->numRows; i++){

			
				if(strcmp(tableArray[table]->rowArray[col]->attrArray[i]->type, "str") == 0){
					//str was enterd in a str field
					printf("Error:  Wrong type of value for attribute %s.\n", colSel);
					
					return;
				}
				
				valSelInteger = atoi(valSel);
				
				//TESTING
				//printf("valSelInteger is: %d\n", valSelInteger);
			
				//check if valSel is what we want
				if(valSelInteger > tableArray[table]->rowArray[col]->attrArray[i]->data.integer){
					
					//increment valSelCounter
					valSelCounter++;
					
					//print whole line if contains data we are looking for
					printLine(tableArray, i, table);
					
					//for undefined behavior, copy data back into valSelInteger
					//valSelInteger = tableArray[table]->rowArray[col]->attrArray[i]->data.integer;
					
				}
				
			}//end looping tables
			
		}
		
	}else{
		//error
		printf("Compare value error.\n");
		return;
	}
	
	//if nothing present
	if(valSelCounter == 0){
		printf("No value satisfies the specified condition.\n");
	}
	
	//TESTING
	//printf("End select\n");
	
	
	//end of fucntion
	return;
	
}//end selectQuery function

void numRowsQuery(FILE* queryfile, table** tableArray, char** tableNames, int numOfTables){
	//number of rows per table specified
	char tableSel[MAX_STR_SIZE];
	int index;
	
	//scan query file for table name
	fscanf(queryfile, "%s", tableSel);
	
	//get index of table
	index = tableIndex(tableSel, tableNames, numOfTables);
	
	//check for '-1' if table exists
	if(index == -1){
		printf("Error:  Invalid table -- %s\n", tableSel);
	}else{
		//print number of rows to screen for table
		printf("%d\n", tableArray[index]->numRows);
	}
	
}//end numRowsQuery

void rowStatQuery(FILE* queryfile, table** tableArray, char** tableNames, int numOfTables){
	//number of rows per table specified
	char tableSel[MAX_STR_SIZE];
	int index;
	
	//scan query file for table name
	fscanf(queryfile, "%s", tableSel);
	
	//get index of table
	index = tableIndex(tableSel, tableNames, numOfTables);
	
	//check for '-1' if table exists
	if(index == -1){
		printf("Error:  Invalid table -- %s\n", tableSel);
		
		return;
	}
	
	//print size of rows to screen for table
	printf("%d\n", tableArray[index]->rowSize);
	
}

void numColsQuery(FILE* queryfile, table** tableArray, char** tableNames, int numOfTables){
	//number of cols per table specified
	char tableSel[MAX_STR_SIZE];
	int index;
	
	//scan query file for table name
	fscanf(queryfile, "%s", tableSel);
	
	//get index of table
	index = tableIndex(tableSel, tableNames, numOfTables);
	
	//check for '-1' if table exists
	if(index == -1){
		printf("Error:  Invalid tabkle -- %s\n", tableSel);
	}else{
		//print number of cols to screen for table
		printf("%d\n", tableArray[index]->numCols);
	}
}

void colStatQuery(FILE* queryfile, table** tableArray, char** tableNames, int numOfTables){
	//print col type and size
	char tableSel[MAX_STR_SIZE];
	char colSel[MAX_STR_SIZE];
	int table;
	int col;
	
	//scan query file for table name
	fscanf(queryfile, "%s", tableSel);
	
	table = tableIndex(tableSel, tableNames, numOfTables);
	
	//if table DNE
	if(table == -1){
		//print error is table DNE
		printf("Error:  Invalid table -- %s\n", tableSel);
		
		//read rest of data to move file pointer to correct location
		fscanf(queryfile, "%s", colSel);
		
		//return to query file
		return;
	}
	
	//read next word of query
	fscanf(queryfile, "%s", colSel);
	
	col = colIndex(colSel, table, tableArray);
	
	//if -1 then incorrect col was inputted
	if(col == -1){
		//print error of column DNE
		printf("Error: Invalid column -- %s\n", colSel);
		
		//return to query
		return;
	}
	
	//print correct data
	printf("Attribute type  :  %s\n", tableArray[table]->rowArray[col]->attrArray[0]->type);
	printf("Atrribute length:  %d\n", tableArray[table]->rowArray[col]->attrArray[0]->size);
	
}

void projectQuery(FILE* queryfile, table** tableArray, char** tableNames, int numOfTables){
	//variables
	char tableSel[MAX_STR_SIZE];
	char colSel[MAX_STR_SIZE];
	int table;
	int col;
	
	//scan line for query
	fscanf(queryfile, "%s %s", tableSel, colSel);
	
	//get tableIndex integer
	table = tableIndex(tableSel, tableNames, numOfTables);
	
	//if table DNE
	if(table == -1){
		//print error is table DNE
		printf("Error:  Invalid table -- %s\n", tableSel);
		
		//return to query file
		return;
	}
	
	//get colIndex integer
	col = colIndex(colSel, table, tableArray);
	
	if(col == -1){
		//print error is table DNE
		printf("Error:  Invalid column -- %s\n", colSel);
		
		//return to query file
		return;
	}
	
	//make array of strings
	char** colData = checkMalloc(sizeof(char) * (tableArray[table]->numCols));
	
	//save colData into array to check for duplicates
	int i;
	int j;
	int presentCounter;
	char* tempNumHolder = checkMalloc(sizeof(char) * MAX_STR_SIZE);
	
	for(i = 0; i < tableArray[table]->numRows; i++){
		
		//malloc indivigual if
		colData[i] = checkMalloc(sizeof(char) * MAX_STR_SIZE);
		
		//if its a str
		if(strcmp(tableArray[table]->rowArray[col]->attrArray[i]->type, "str") == 0){
			
			//reset presentCounter = 0
			presentCounter = 0;
			
			//check if already in array
			for(j = 0; j < i; j++){
				//if in array add 1 to counter
				if(strcmp(colData[j], tableArray[table]->rowArray[col]->attrArray[i]->data.str) == 0){
					presentCounter++;
				}
			}
			
			//copy data
			strcpy(colData[i], tableArray[table]->rowArray[col]->attrArray[i]->data.str);
			
		}else{
			
			//reset presentCounter = 0
			presentCounter = 0;
			
			//strcpy(tempNumHolder, tableArray[table]->rowArray[col]->attrArray[i]->data.integer);
			
			//convert and copy data into tempNumHolder
			sprintf(tempNumHolder, "%d", tableArray[table]->rowArray[col]->attrArray[i]->data.integer);
			
			
			//check if already in array
			for(j = 0; j < i; j++){
				
				//strcpy(tempNumHolder, tempNumHolder);
				//if in array add 1 to counter
				if(strcmp(colData[j], tempNumHolder) == 0){
					presentCounter++;
				}
			}
			
			//copy data into colData
			//printf("Fail here?\n");
			
			strcpy(colData[i], tempNumHolder);
			
		}
		
		
		//only print if not a duplicate
		if(presentCounter == 0){
			printf("%s\n", colData[i]);
		}
		
	}
	
}

void stopQuery(){
	//stop detected, end nicely
	exit(0);
}

int tableIndex(char* tableName,char** tableNames,int numOfTables){
	//return what index the table is at in tableArray**
	int i;
	for(i = 0; i < numOfTables; i++){
		//compare inputted string to tableNames
		if(strcmp(tableName, tableNames[i]) == 0){
			return i;
		}
	}
	
	//return -1 if not found
	return -1;
}

int colIndex(char* colName, int tableIndex, table** tableArray){
	//return col index
	int i;
	for(i = 0; i < tableArray[tableIndex]->numCols; i++){
		
		
		//compare col names to find a match
		if(strcmp(colName, tableArray[tableIndex]->rowArray[i]->attrArray[0]->name) == 0){
			//return col index
			return i;
		}
	}
	
	//return -1 if col DNE
	return -1;
}

char* removeQuotes(char* string){
	
	int stringLen = strlen(string);
	char tempString[MAX_STR_SIZE + 2];
	char* removedQuotes = checkMalloc(sizeof(char) * MAX_STR_SIZE);
	
	strcpy(tempString, string);
	
	removedQuotes = strtok(tempString, "\"");
	
	return removedQuotes;
	
}

void printLine(table** tableArray, int row, int tableNum){
	
	int j;
	
	for(j = 0; j < tableArray[tableNum]->numCols; j++){
	
		//determine if str or int needs to be printed
		if(strcmp(tableArray[tableNum]->rowArray[j]->attrArray[row]->type, "str") == 0){
			//TESTING
			//printf("Start of str print.\n");
			printf("%s\t", tableArray[tableNum]->rowArray[j]->attrArray[row]->data.str);
		}else{
			//TESTING
			//printf("Start of integer print.\n");
			
			printf("%d\t", tableArray[tableNum]->rowArray[j]->attrArray[row]->data.integer);
		}
		
	}
	
	//Add new line for formatting
	printf("\n");
}//end printLine function