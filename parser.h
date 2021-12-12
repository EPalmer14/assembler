//
//  parser.h
//  assembler
//
//  Created by Zeke Palmer on 4/13/21.
//

#ifndef parser_h
#define parser_h

#include <stdio.h>

#endif /* parser_h */

// removes the whitespace and comments from an input line
void removeSpacesAndComments(char *inputBuffer);

// Read the line to determine what type of command it is
char CommandType(char *line);

// returns a line from the input file without any spaces or comments;
// parses the line
int parseLine(char *inputBuffer);
    
void makeLabel(char *inputBuffer);
