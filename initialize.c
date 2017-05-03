//Alex Pospesel
//ID: 001146589
//NetID: ap212246
//Email: apospesel@albany.edu
//CSI 402
//Program 3
//Due 3/27/16

#include "headers.h"
#include "prototypes.h"

//return number of tables
int numTables(FILE *configfile){
	int numOfTables;
	
	//read number of tables
	fscanf(configfile, "%d", &numOfTables);
	
	return numOfTables;
}

//return table names
char ** tables(FILE *configfile, int numOfTables){
	
	char ** tableNames;

	//tableNames = malloc(numOfTables * sizeof(char *));
	tableNames = checkMalloc((numOfTables) * sizeof(char *));
	
	int i;
	
	
	for(i = 0; i < numOfTables; i++){
		
		//tableNames[i] = malloc(MAX_STR_SIZE * sizeof(char));
		tableNames[i] = checkMalloc((MAX_STR_SIZE) * sizeof(char));

		fscanf(configfile, "%s", tableNames[i]);
		
	}
	
	//return the table array
	return tableNames;
}

table ** tableConfig(char **tableNames, int numOfTables){
	
	//array of strings for .table and .data files
	char **tableConfigName;	//for .table
	char **tableDataName;	//for .data

	//make a table array
	table ** tableArray;

	//malloc tables
	tableArray = (struct table **)checkMalloc(sizeof(struct table*) * numOfTables);

	//malloc for size of arrays
	tableConfigName = checkMalloc((numOfTables) * sizeof(char *));
	tableDataName = checkMalloc((numOfTables) * sizeof(char *));

	//file pointers
	FILE *tableConfigPointer;
	FILE *tableDataPointer;	

	//for loop counters
	int i;
	int j;
	int h;

	//.data file length
	int dataFileLength;

	//.table/scheme data
	int numOfCols;
	int numOfRows;

	char colName[MAX_STR_SIZE];
	char colType[MAX_STR_SIZE];
	int colByteSize;



	//loop through tableNames and open and close files respectively
	for(i = 0; i < numOfTables; i++){

		//TESTING
		//printf("Table: %d\n", i);
		//fflush(stdout);
		
		//malloc tableArray[i]
		tableArray[i] = checkMalloc(sizeof(struct table*));

		//malloc the 2 arrays
		tableConfigName[i] = checkMalloc(sizeof(char) * (MAX_STR_SIZE));
		tableDataName[i] = checkMalloc(sizeof(char) * (MAX_STR_SIZE));

		/*
		//TESTING
		//malloc name of table
		tableArray[i]->tableName = checkMalloc(sizeof(char) * strlen(tableNames[i] + 1));

		//set name of table
		strcpy(tableArray[i]->tableName, tableNames[i]);
		//END TESTING
		*/

		//append .table and .data accordingly
		sprintf(tableConfigName[i], "%s.table", tableNames[i]);
		sprintf(tableDataName[i], "%s.data", tableNames[i]);

		//open .table file
		tableConfigPointer = checkOpen(tableConfigName[i], "r", "Could not open schema file.");
		
		//open .data file
		tableDataPointer = checkOpen(tableDataName[i], "r", "Could not open data file.");

		//read .table file for num of cols
		fscanf(tableConfigPointer, "%d", &numOfCols);

		//TESTING
		//printf("Number of cols: %d\n", numOfCols);

		//find length of .data file
		fseek(tableDataPointer, 0, SEEK_END);
		dataFileLength = ftell(tableDataPointer);
		fseek(tableDataPointer, 0, SEEK_SET);

		//total col size to determine row size
		int rowSize = 0;

		
		//read .table file for row sizes only
		for(j = 0; j < numOfCols; j++){

			//scan line of .table file
			fscanf(tableConfigPointer, "%s %s %d", colName, colType, &colByteSize);

			//total col size summed up
			rowSize += colByteSize;
		}

		//num of rows calculation
		numOfRows = dataFileLength/rowSize;

		//calcualte and save num of rows to table
		tableArray[i]->numRows = numOfRows;

		//assign data to table, num of columns
		tableArray[i]->numCols = numOfCols;

		//assign row size to table
		tableArray[i]->rowSize = rowSize;

		//malloc rows inside tableArray
		tableArray[i]->rowArray = checkMalloc(sizeof(struct row*) * (numOfRows));

		//fseek to beginning of .table and re-read data
		fseek(tableConfigPointer, 0, SEEK_SET);

		//read .table file for num of cols
		fscanf(tableConfigPointer, "%d", &numOfCols);

		//loop through .table again saving the data this time
		for(j = 0; j < tableArray[i]->numCols; j++){

			//scan line of .table file
			fscanf(tableConfigPointer, "%s %s %d", colName, colType, &colByteSize);

			//TESTING
			//checkPoint();

			//printf("Seg check 0\n");

			//malloc attribute struct per cell
			tableArray[i]->rowArray[j] = checkMalloc(sizeof(struct row));

			//printf("Seg check 1\n");
			
			//malloc attrArray by cols
			tableArray[i]->rowArray[j]->attrArray = checkMalloc(sizeof(struct attribute) * (tableArray[i]->numCols));

			//printf("Seg check 2\n");

			//TESTING
			//checkPoint();
			//set size of row in row struct and num of attributes
			tableArray[i]->rowArray[j]->size = rowSize;
			tableArray[i]->rowArray[j]->numAttributes = numOfCols;

			//loop over cols
			for(h = 0; h < tableArray[i]->numRows; h++){

				//TESTING
				
				//printf("Malloc'ing each row.\n");

				//printf("Segfault check 0\n");

				//malloc attribute struct
				tableArray[i]->rowArray[j]->attrArray[h] = checkMalloc(sizeof(struct attribute));

				//printf("Segfault check 1\n");

				//malloc to strings
				tableArray[i]->rowArray[j]->attrArray[h]->name = checkMalloc(sizeof(char) * (strlen(colName) + 1));

				//printf("Segfault check 2\n");

				tableArray[i]->rowArray[j]->attrArray[h]->type = checkMalloc(sizeof(char) * (strlen(colType) + 1));

				//printf("Segfault check 3\n");

				//TESTING
				//if()
				
				//TESTING
				//checkPoint();

				//set data from .table
				strcpy(tableArray[i]->rowArray[j]->attrArray[h]->name, colName);
				strcpy(tableArray[i]->rowArray[j]->attrArray[h]->type, colType);
				tableArray[i]->rowArray[j]->attrArray[h]->size = colByteSize;

				//TESTING
				//checkPoint();
				/*

				printf("NAME is: %s\n", colName);
				printf("TYPE is: %s\n", colType);
				printf("SIZE is: %d\n", colByteSize);
				printf("\n");
				*/

				//printf("Table: %d Col: %d Row: %d\n", i, j, h);
				/*
				printf("NAME is: %s\n", tableArray[i]->rowArray[j]->attrArray[h]->name);
				printf("TYPE is: %s\n", tableArray[i]->rowArray[j]->attrArray[h]->type);
				printf("SIZE is: %d\n", tableArray[i]->rowArray[j]->attrArray[h]->size);
				printf("\n");
				*/

				//read .data file
				/*
				if(strcmp("str", colType) == 0){
					//malloc memory for sting
					tableArray[i]->rowArray[j]->attrArray[h]->data.str = checkMalloc(sizeof(char) * colByteSize);

					//read string
					fread(tableArray[i]->rowArray[j]->attrArray[h]->data.str, colByteSize, 1, tableDataPointer);
				}else{
					//malloc memory for int
					//tableArray[i]->rowArray[j]->attrArray[h]->data.integer = checkMalloc(sizeof(int));
					//must be integer
					fread(&(tableArray[i]->rowArray[j]->attrArray[h]->data.integer), colByteSize, 1, tableDataPointer);
				}
				*/

				//TESTING
				//checkPoint();
				//testing
				/*
				printf("Table: %d Col: %d Col Name: %s \n", i, j, tableArray[i]->rowArray[j]->attrArray[h]->name);
				printf("Table: %d Col: %d Col Type: %s\n", i, j, tableArray[i]->rowArray[j]->attrArray[h]->type);
				printf("Table: %d Col: %d Col Size: %d\n", i, j, tableArray[i]->rowArray[j]->attrArray[h]->size);

				if(strcmp("str", colType) == 0){
					printf("Table: %d Col: %d Data: %s\n", i, j, tableArray[i]->rowArray[j]->attrArray[h]->data.str);
				}else{
					printf("Table: %d Col: %d Data: %d\n", i, j, &(tableArray[i]->rowArray[j]->attrArray[h]->data.integer));
				}
				*/
				

			}

		}
		
		//printf("Type is: %s\n", tableArray[0]->rowArray[0]->attrArray[0]->type);
		//fflush(stdout);

		//TESTING
		/*
		printf("Table %d Num rows: %d\n", i, tableArray[i]->numRows);
		printf("Table %d Num cols: %d\n", i, tableArray[i]->numCols);
		printf("Table %d Row size: %d\n", i, tableArray[i]->rowSize);
		printf("\n");
		*/

		//read .data
		//TESTING
		//printf("Table: %d\n", i);
		//printf("Table Name: %s\n", tableArray[i]->tableName);
		//loop rows
		for(h = 0; h < tableArray[i]->numRows; h++){

			//TESTING
			//printf("Row: %d\n", h);
			//fflush(stdout);

			//loop columns
			for(j = 0; j < tableArray[i]->numCols; j++){

				//TESTING
				/*
				printf("Do we get here.\n");
				fflush(stdout);
				printf("Name is: %s\n", tableArray[i]->rowArray[j]->attrArray[h]->name);
				printf("Type is: %s\n", tableArray[i]->rowArray[j]->attrArray[h]->type);
				printf("Size is: %d\n", tableArray[i]->rowArray[j]->attrArray[h]->size);
				printf("\n");
				*/
				
				
				//TESTING
				//printf("Col: %d\n", j);
				//printf("Type is: %s\n", tableArray[0]->rowArray[0]->attrArray[0]->type);
				//fflush(stdout);
				
				if(strcmp("str\0", tableArray[i]->rowArray[j]->attrArray[h]->type) == 0){
					//malloc memory for sting

					//TESTING
					//printf("Reading String: %d bytes\n", tableArray[i]->rowArray[j]->attrArray[h]->size);

					tableArray[i]->rowArray[j]->attrArray[h]->data.str = (char *)checkMalloc(sizeof(char) * (tableArray[i]->rowArray[j]->attrArray[h]->size));

					//read string
					fread(tableArray[i]->rowArray[j]->attrArray[h]->data.str, tableArray[i]->rowArray[j]->attrArray[h]->size, 1, tableDataPointer);
					
				}else if(strcmp("int\0", tableArray[i]->rowArray[j]->attrArray[h]->type) == 0){
					//malloc memory for int
					//tableArray[i]->rowArray[j]->attrArray[h]->data.integer = checkMalloc(sizeof(int));
					//must be integer
					//TESTING
					//printf("Reading Int: %d bytes\n", tableArray[i]->rowArray[j]->attrArray[h]->size);

					fread(&(tableArray[i]->rowArray[j]->attrArray[h]->data.integer), tableArray[i]->rowArray[j]->attrArray[h]->size, 1, tableDataPointer);
					//checkPoint();

				}else{
					die("Type Error.");
				}

				//TESTING
				/*
				if(strcmp("str", tableArray[i]->rowArray[j]->attrArray[h]->type) == 0){
					printf("%s\t", tableArray[i]->rowArray[j]->attrArray[h]->data.str);
				}else{
					printf("%d\t", tableArray[i]->rowArray[j]->attrArray[h]->data.integer);
				}
				*/
				
			}//end looping cols

			//printf("\n");

		}//end looping rows

		//printf("\n");


		//close file pointers
		fclose(tableConfigPointer);
		fclose(tableDataPointer);

		//TESTING
		//checkPoint();
		
	} // end looping table

	//read .data

	/*
	//nested 3 for loops to read data from .data
	//loop tables
	for(i = 0; i < numOfTables; i++){
		//TESTING
		printf("Table: %d\n", i);
		//loop rows
		for(h = 0; h < numOfRows; h++){

			//loop columns
			for(j = 0; j < numOfCols; j++){
				
				if(strcmp("str", tableArray[i]->rowArray[j]->attrArray[h]->type) == 0){
					//malloc memory for sting
					tableArray[i]->rowArray[j]->attrArray[h]->data.str = checkMalloc(sizeof(char) * colByteSize);

					//read string
					fread(tableArray[i]->rowArray[j]->attrArray[h]->data.str, tableArray[i]->rowArray[j]->attrArray[h]->size, 1, tableDataPointer);
				}else{
					//malloc memory for int
					//tableArray[i]->rowArray[j]->attrArray[h]->data.integer = checkMalloc(sizeof(int));
					//must be integer
					fread(&(tableArray[i]->rowArray[j]->attrArray[h]->data.integer), tableArray[i]->rowArray[j]->attrArray[h]->size, 1, tableDataPointer);
				}

				//TESTING
				if(strcmp("str", tableArray[i]->rowArray[j]->attrArray[h]->type) == 0){
					printf("Str: %s ", tableArray[i]->rowArray[j]->attrArray[h]->data.str);
				}else{
					printf("Int: %d ", &(tableArray[i]->rowArray[j]->attrArray[h]->data.integer));
				}
				
			}//end looping cols

			printf("\n");

		}//end looping rows

	}//end looping tables
	*/

	return tableArray;
	
}//end tableConfig function()