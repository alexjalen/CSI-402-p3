//Alex Pospesel
//ID: 001146589
//NetID: ap212246
//Email: apospesel@albany.edu
//CSI 402
//Program 3
//Due 3/27316

//error.c file
void die(char * message);
void debug(char * message);
void checkPoint();
FILE * checkOpen(char * name, char * mode, char * failMessage);
void * checkMalloc(size_t s);

//initialize.c file
int numTables(FILE *configfile);
char ** tables(FILE *configfile, int numOfTables);
table ** tableConfig(char **tableNames, int numOfTables);

//queryFile.c file
void readQueryFile(FILE* queryfile, table ** tableArray, char ** tableNames, int numOfTables);
void selectQuery(FILE* queryfile, table** tableArray, char** tableNames, int numOfTables);
void numRowsQuery(FILE* queryfile, table** tableArray, char** tableNames, int numOfTables);
void rowStatQuery(FILE* queryfile, table** tableArray, char** tableNames, int numOfTables);
void numColsQuery(FILE* queryfile, table** tableArray, char** tableNames, int numOfTables);
void colStatQuery(FILE* queryfile, table** tableArray, char** tableNames, int numOfTables);
void projectQuery(FILE* queryfile, table** tableArray, char** tableNames, int numOfTables);
void stopQuery();
int tableIndex(char* tableName,char** tableNames,int numOfTables);
int colIndex(char* colName, int tableIndex, table** tableArray);
char* removeQuotes(char* string);
void printLine(table** tableArray, int row, int tableNum);
