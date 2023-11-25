// Created by AJ DiLeo
// For use in CS211 Fall 2023 ONLY

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS_SIZE 100

typedef struct programmingLanguage {
	int id;
	char* language;
	int year;
	char* creator;
	char* paradigm;
	double popularityIndex;

	int isDeleted; // internal field, not accessible to user
} language_t;

// step 1: create structs for the other two tables: operatingSystems
// and databases
// include internal field

typedef struct operatingSystems {
	int id;
	char* name;
	int year;
	char* type;
	char* developer;

	int isDeleted;

} operating_t; 

typedef struct databases {
	int id;
	char* name;
	int year;
	char* type;
	char* developer;

	int isDeleted;
} databases_t; 

// step 2: create typedef struct for storing metadata

typedef struct storingMetadata {
	int count;
	int nextIndex;
	int maxCount;
} store_t;

// step 3: declare the two other arrays of structs
// programmingLanguages has been defined for you already
// TODO: add operatingSystems and databases
language_t* programmingLanguages;
operating_t* operatingSystem;
databases_t* database;




// step 4: declare 3 metadata structs, one for each table
store_t programmingLanguagesMetadata;
store_t operatingSystemMetadata;
store_t databaseMetadata;


// step 5: jump to L167


// This function takes the user's input and splits it by spaces
// into an array of strings, ignoring spaces that are wrapped in quotes
// There is no need to modify this code.
// You do not need to understand this code
// but you are welcome to research its application
void splitInput(char* input, char** args, int* arg_count) {
    *arg_count = 0;
    int in_quotes = 0; // Flag to track whether we are inside quotes
    char* token_start = input;

    for (char* ptr = input; *ptr != '\0'; ptr++) {
        if (*ptr == '"') {
            in_quotes = !in_quotes; // Toggle the in_quotes flag when a quote is encountered
        }

        if ((*ptr == ' ' || *ptr == '\n') && !in_quotes) {
            // If not inside quotes and a space or newline is found, consider it as a separator
            *ptr = '\0'; // Replace space or newline with null terminator
            args[(*arg_count)++] = token_start;
            token_start = ptr + 1; // Start of the next token
        }
    }

    // Add the last token (if any) after the loop
    if (*token_start != '\0') {
        // Remove leading and trailing double quotes if they exist
        if (token_start[0] == '"' && token_start[strlen(token_start) - 1] == '"') {
            token_start[strlen(token_start) - 1] = '\0'; // Remove trailing quote
            args[(*arg_count)++] = token_start + 1; // Remove leading quote
        } else {
            args[(*arg_count)++] = token_start;
        }
    }
    args[*arg_count] = NULL;
}

// step 7: implement setup function
// this function is responsible for dynamically allocating the
// particular table. Use the tables declared on L27.
void setup(char* table, int numRows) {

	
	
	
	if(strcmp(table, "programmingLanguages") == 0) {
		programmingLanguages = (language_t*)malloc(numRows * sizeof(language_t));
		programmingLanguagesMetadata.maxCount = numRows; 
		programmingLanguagesMetadata.count = 0;
	} else if(strcmp(table, "operatingSystems") == 0) {
		operatingSystem = (operating_t*)malloc(numRows * sizeof(operating_t));
		operatingSystemMetadata.maxCount = numRows;
		operatingSystemMetadata.count = 0;
	} else if(strcmp(table, "databases") == 0) {
		database = (databases_t*)malloc(numRows * sizeof(databases_t));
		databaseMetadata.maxCount = numRows;
		databaseMetadata.count = 0;
	}

	

	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("setup complete\n");
}

// step 8: implement insert function
// this function is responsible for updating the corresponding
// fields of the struct located at the next available index
// make sure to use and update your metadata.

// autograder print for insufficient capacity:
// fprintf(stderr, "cannot insert due to insufficient capacity.\n");
void insert(char** args) {

	language_t programmingLanguagesTemp;
	operating_t operatingSystemTemp;	
	databases_t databaseTemp;


	if(strcmp(args[1], "programmingLanguages") == 0) {
		
		if(programmingLanguagesMetadata.maxCount == programmingLanguagesMetadata.count) {
			fprintf(stderr, "cannot insert due to insufficient capacity.\n");
		} else {
			programmingLanguages[programmingLanguagesMetadata.nextIndex].id = atoi(args[2]);
			programmingLanguages[programmingLanguagesMetadata.nextIndex].language = strdup(args[3]);
			programmingLanguages[programmingLanguagesMetadata.nextIndex].year = atoi(args[4]);
			programmingLanguages[programmingLanguagesMetadata.nextIndex].creator = strdup(args[5]);
			programmingLanguages[programmingLanguagesMetadata.nextIndex].paradigm = strdup(args[6]);
			programmingLanguages[programmingLanguagesMetadata.nextIndex].popularityIndex = atof(args[7]);
			programmingLanguages[programmingLanguagesMetadata.nextIndex].isDeleted = 0;
			

			programmingLanguagesMetadata.count = programmingLanguagesMetadata.count + 1;
			programmingLanguagesMetadata.nextIndex = programmingLanguagesMetadata.nextIndex + 1;
			printf("insert complete\n");
			
			
		}	
		

	} else if(strcmp(args[1], "operatingSystems") == 0) {

		if(operatingSystemMetadata.maxCount == operatingSystemMetadata.count) {
			fprintf(stderr, "cannot insert due to insufficient capacity.\n");
		} else {
			operatingSystem[operatingSystemMetadata.nextIndex].id = atoi(args[2]);
			operatingSystem[operatingSystemMetadata.nextIndex].name = strdup(args[3]);
			operatingSystem[operatingSystemMetadata.nextIndex].year = atoi(args[4]);
			operatingSystem[operatingSystemMetadata.nextIndex].developer = strdup(args[5]);
			operatingSystem[operatingSystemMetadata.nextIndex].type = strdup(args[6]);
			operatingSystem[operatingSystemMetadata.nextIndex].isDeleted = 0;
		
			
			operatingSystemMetadata.count = operatingSystemMetadata.count + 1;
			operatingSystemMetadata.nextIndex = operatingSystemMetadata.nextIndex + 1;
			printf("insert complete\n");
		}
		

	} else if(strcmp(args[1], "databases") == 0) {

		if(databaseMetadata.maxCount == databaseMetadata.count) {
			fprintf(stderr, "cannot insert due to insufficient capacity.\n");
		} else {
			database[databaseMetadata.nextIndex].id = atoi(args[2]);
			database[databaseMetadata.nextIndex].name = strdup(args[3]);
			database[databaseMetadata.nextIndex].year = atoi(args[4]);
			database[databaseMetadata.nextIndex].type = strdup(args[5]);
			database[databaseMetadata.nextIndex].developer = strdup(args[6]);
			database[databaseMetadata.nextIndex].isDeleted = 0;
			
			
			databaseMetadata.count = databaseMetadata.count + 1;
			databaseMetadata.nextIndex = databaseMetadata.nextIndex + 1;
			printf("insert complete\n");
		}
		

	}


	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	
}

// step 9: implement soft delete function
// this function is responsible for marking a record as deleted
// you should be updating an internal field flag so that get will
// not display this record. 
// You should not be attempting to free/overwrite this record - it remains alloc
// with a updated field
// make use of your metadata
void delete(char* table, int id) {

	if(strcmp(table, "programmingLanguages") == 0) {
		for(int i = 0; i < programmingLanguagesMetadata.count; i++)
		{
			if(id == programmingLanguages[i].id)
			{
				programmingLanguages[i].isDeleted = 1;
			}
				
		}
	} else if(strcmp(table, "operatingSystems") == 0) {
		for(int i = 0; i < operatingSystemMetadata.count; i++)
		{
			if(id == operatingSystem[i].id)
			{
				operatingSystem[i].isDeleted = 1;
			}
				
		}
		
	} else if(strcmp(table, "databases") == 0) {
		for(int i = 0; i < databaseMetadata.count; i++)
		{
			if(id == database[i].id)
			{
				database[i].isDeleted = 1;
			}
				
		}
		
	}


	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("delete complete\n");
}

// step 10: implement modify function
// this function is responsible for overwriting all of the contents of all
// records that match an ID.
// make use of your metadata
// !!!NOTE: The structs store pointers. Make sure to free any allocated
// memory before overwriting it!!!
void modify(char** args) {

	if(strcmp(args[1], "programmingLanguages") == 0) {
		for(int i = 0; i < programmingLanguagesMetadata.count; i++)
		{
			if(atoi(args[2]) == programmingLanguages[i].id) {

				free(programmingLanguages[i].language);
				free(programmingLanguages[i].creator);
				free(programmingLanguages[i].paradigm);

				programmingLanguages[i].id = atoi(args[3]);
				programmingLanguages[i].language = strdup(args[4]);
				programmingLanguages[i].year = atoi(args[5]);
				programmingLanguages[i].creator = strdup(args[6]);
				programmingLanguages[i].paradigm = strdup(args[7]);
				programmingLanguages[i].popularityIndex = atof(args[8]);
			}
				
		}
	} else if(strcmp(args[1], "operatingSystems") == 0) {
		for(int i = 0; i < operatingSystemMetadata.count; i++)
		{
			if(atoi(args[2]) == operatingSystem[i].id) {

				free(operatingSystem[i].name);
				free(operatingSystem[i].developer);
				free(operatingSystem[i].type);

				operatingSystem[i].id = atoi(args[3]);
				operatingSystem[i].name = strdup(args[4]);
				operatingSystem[i].year = atoi(args[5]);
				operatingSystem[i].developer = strdup(args[6]);
				operatingSystem[i].type = strdup(args[7]);	
				
			
			}
				
		}
		
	} else if(strcmp(args[1], "databases") == 0) {
		for(int i = 0; i < databaseMetadata.count; i++)
		{

			if(atoi(args[2]) == database[i].id) {

				free(database[i].name);
				free(database[i].type);
				free(database[i].developer);

				database[i].id = atoi(args[3]);
				database[i].name = strdup(args[4]);
				database[i].year = atoi(args[5]);
				database[i].type = strdup(args[6]);
				database[i].developer = strdup(args[7]);
			}
				
		}
		
	}

	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("modify complete\n");
}

// step 11: implement get function
// this function is responsible for fetching all non-deleted records
// make use of your metadata
// Make sure to follow guidelines for format in writeup
// see examples as well
// Use %lf for formatting double data type
void get(char* table) {
	if(strcmp(table, "programmingLanguages") == 0) {

		printf("id,language,year,creator,paradigm,popularityIndex\n");
		for(int i = 0; i < programmingLanguagesMetadata.count; i++)
		{
			if(programmingLanguages[i].isDeleted == 0) {
				printf("%d,%s,%d,%s,%s,%lf\n", programmingLanguages[i].id, programmingLanguages[i].language, programmingLanguages[i].year, programmingLanguages[i].creator, programmingLanguages[i].paradigm, programmingLanguages[i].popularityIndex);
			}
				
		}
	} else if(strcmp(table, "operatingSystems") == 0) {

		printf("id,name,year,developer,kernelType\n");
		for(int i = 0; i < operatingSystemMetadata.count; i++)
		{
			if(operatingSystem[i].isDeleted == 0) {
				printf("%d,%s,%d,%s,%s\n", operatingSystem[i].id, operatingSystem[i].name, operatingSystem[i].year, operatingSystem[i].developer, operatingSystem[i].type);
			}
				
				
		}
		
	} else if(strcmp(table, "databases") == 0) {

		printf("id,name,year,type,developer\n");
		for(int i = 0; i < databaseMetadata.count; i++)
		{
			if(database[i].isDeleted == 0) {
				printf("%d,%s,%d,%s,%s\n", database[i].id, database[i].name, database[i].year, database[i].type, database[i].developer);
			}
				
				
		}
		
	}
}

// step 12: implement exit function
// this function should free all allocated memory
// Make sure to avoid memory leaks by freeing any allocated memory
// inside a struct (char*) before freeing the struct pointer
void exitProgram() {

	for(int i = 0; i < programmingLanguagesMetadata.count; i++)
	{
		free(programmingLanguages[i].language);
		free(programmingLanguages[i].creator);
		free(programmingLanguages[i].paradigm);	
	}

	for(int i = 0; i < operatingSystemMetadata.count; i++)
	{
		free(operatingSystem[i].name);
		free(operatingSystem[i].developer);
		free(operatingSystem[i].type);	
	}

	for(int i = 0; i < databaseMetadata.count; i++)
	{
		free(database[i].name);
		free(database[i].type);
		free(database[i].developer);
	}
	
	
	free(programmingLanguages);
	free(operatingSystem);
	free(database);
}

// this code is responsible for parsing the user's
// input, and determining based on the command
// which function to send it to.
// You do not have to modify this code, but you should
// understand it.
void execute_cmd(char** args, int arg_count) {
	char* cmd = args[0];
	if (strcmp(cmd, "setup") == 0) {
		setup(args[1], atoi(args[2]));
	} else if (strcmp(cmd, "insert") == 0) {
		insert(args);
	} else if (strcmp(cmd, "delete") == 0) {
		delete(args[1], atoi(args[2]));
	} else if (strcmp(cmd, "modify") == 0) {
		modify(args);
	} else if (strcmp(cmd, "get") == 0) {
		get(args[1]);
	} else if (strcmp(cmd, "exit") == 0) {
		exitProgram();
	} else {
		printf("\n");
	}
}

// step 6: initialize the default metadata values here
// jump to L76
void initializeMetadata() {
	programmingLanguagesMetadata.count = 0;
	operatingSystemMetadata.count = 0;
	databaseMetadata.count = 0;

	programmingLanguagesMetadata.maxCount = 0;
	operatingSystemMetadata.maxCount = 0;
	databaseMetadata.maxCount = 0;

	programmingLanguagesMetadata.nextIndex = 0;
	operatingSystemMetadata.nextIndex = 0;
	databaseMetadata.nextIndex = 0;



}

// this code creates the interactive shell
// you do not need to modify this
// You do not need to understand this code
// but you are welcome to research its application
void cmd_loop() {
	char input[MAX_INPUT_SIZE];
    ssize_t bytes_read;
	printf("Usage: \n");
	printf("setup {table} {numRows}\n");
	printf("insert {table} {data}\n");
	printf("delete {table} {id}\n");
	printf("modify {table} {id} {data}\n");
	printf("get {table}\n\n");
	initializeMetadata();
    while (1) {
        printf("CS211> ");
		fflush(stdout);
        
        // Read user input using the read() system call
        bytes_read = read(STDIN_FILENO, input, sizeof(input));
        
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        
        if (bytes_read == 0) {
			printf("\n");
            break;
        }
        
        // Null-terminate the input
        input[bytes_read] = '\0';

		char** args = (char**)malloc(MAX_ARGS_SIZE * sizeof(char*));
		int arg_count;

		splitInput(input, args, &arg_count);
        
        // Execute the user's command
        execute_cmd(args, arg_count);
		free(args);
    }
}


int main() {
	cmd_loop();
}