//Alex Pospesel
//ID: 001146589
//NetID: ap212246
//Email: apospesel@albany.edu
//CSI 402
//Program 3
//Due 3/27/16
//Extended to 4/3/16

//include
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//definitions
#define MAX_STR_SIZE 16

//structs
union data{
	char* str;
	int integer;
};

typedef struct attribute{
	char* name;
	char* type;
	int size;
	union data data;
}attribute;

typedef struct row{
	int size;
	int numAttributes;
	attribute** attrArray;
}row;

typedef struct table{
	//char* tableName;
	int numRows;
	int numCols;
	int rowSize;
	row** rowArray;
}table;