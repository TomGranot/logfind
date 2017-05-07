#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glob.h>
#include <libgen.h>

// Make sure the user presented some arguments to the function
int check_args(int argc, char *argv[])
{
	const char *underscore_o = "-o";

	if (argc == 1) {
		return 1; // There's only one argument (the program's name),
			  // throw error
	} else if (strcmp(argv[1], underscore_o) == 0 && argc == 2) {
		return 2; // There's only an "-o" without a following
		          // argument, throw error
	} else if (strcmp(argv[1], underscore_o) == 0 && argc > 2) {
		return 3; // There's an "-o" and some other arguments after it,
		          // this is logical OR and should be treated as such
	} else {
		return 0; // In all other cases, treat this as logcial AND and 
		          // carry on
	}
}

// Get the list of all files inside the log folder, and send
// It to the main function using a glob_t struct
glob_t get_log_list(void)
{
	glob_t globstruct;
	int rc;	
	// if you haven't placed .logfind in your root this will not work!
	rc = glob("~/.logfind/*", GLOB_TILDE, NULL, &globstruct);
	
	// if you got a non-zero then there's an error.
	if (rc != 0)
	{
		printf("There was an error with the glob function.");
		exit(0);
	}
	
	return globstruct;
}

// Find a string inside a file, with the path and the string
// to find provided by the user
int find_in_file(char *path_to_file,char *string_to_find)
{
	// get the file's size by finding the end and counting steps
	// from the beginning
	FILE *logfile = fopen(path_to_file, "r");
	fseek(logfile, 0L, SEEK_END);
	long filesize = ftell(logfile);
	rewind(logfile);
	
	// set some vars
	char str[100];
	int find_counter = 0;
	
	// go through the file one line at at time, and look for 
	// the string a
	while(fgets(str,filesize,logfile)) 
	{
		if(strstr(str, string_to_find))
		{
			find_counter++;
		}
	}
	
	// if you found something, return 0
	if(find_counter > 0)
	{
		return 0;
	// if the string wasn't found in the file, return 1
	} else {
		return 1;
	}
	
}

int main(int argc, char *argv[])
{
	// declaring logical OR as false to begin with (i.e. 1):
	// do an AND on all args
	int logical_or = 1;
	int rc = check_args(argc, argv);
	switch (rc) {
		case 1:
			printf("You need to insert at least one variable.\n");
			exit(0);

		case 2:
			printf("You need to insert something after the \"-o\" flag.\n");
			exit(0);
		
		case 3:
			logical_or = 0; // Use logical OR
	}	
	
	glob_t paths;
	int idx_files;
	paths = get_log_list();

	// loop through all the files in the log folder
	for(idx_files = 0; idx_files < paths.gl_pathc; idx_files++)
	{
		int idx;
		int arg_found_count = 0;
		// and then loop through all the arguments
		for (idx = 1; idx < argc; idx++)
		{
			// if you found even 1 occurence of the word, increment counter
			int rv = find_in_file(paths.gl_pathv[idx_files], argv[idx]);
			if (rv == 0)
			{
				arg_found_count++;
			}
		}
		
		// If the -o flag is missing: only print file name if the file
		// contains ALL the words, then print the file name
		if(logical_or == 1)
		{
			// if the counter is the same as the argument count (minus
			// the program's name) then print the file name. AKA - logical AND.
			if (arg_found_count == argc - 1)
			{
				// prtinf just the filename, without the whole path
				printf("%s\n", basename(paths.gl_pathv[idx_files]));
			}
			
		// The case for when the -o flag is present: if the files conatin AT LEAST one of the words,
		//then print the file name			
		} else {	
			// if the counter is greater than 0 then print the file name. 
			// AKA - logical OR.
			if (arg_found_count > 0)
			{
				// prtinf just the filename, without the whole path
				printf("%s\n", basename(paths.gl_pathv[idx_files]));
			}
		}
	}
	
	return 0;
}
