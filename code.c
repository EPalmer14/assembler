//
//  code.c
//  assembler
//
//  Created by Zeke Palmer and Siobhan Lounsbury on 4/15/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"
#include "parser.h"
#include "map.h"
#define MAX_LINE_SIZE 200

void Predefined(map ST){
    // Insert predefined labels
    insertKey(ST, "SP\n", "0");
    insertKey(ST, "R0\n", "0");
    insertKey(ST, "R1\n", "1");
    insertKey(ST, "R2\n", "2");
    insertKey(ST, "R3\n", "3");
    insertKey(ST, "R4\n", "4");
    insertKey(ST, "R5\n", "5");
    insertKey(ST, "R6\n", "6");
    insertKey(ST, "R7\n", "7");
    insertKey(ST, "R8\n", "8");
    insertKey(ST, "R9\n", "9");
    insertKey(ST, "R10\n", "10");
    insertKey(ST, "R11\n", "11");
    insertKey(ST, "R12\n", "12");
    insertKey(ST, "R13\n", "13");
    insertKey(ST, "R14\n", "14");
    insertKey(ST, "R15\n", "15");
    insertKey(ST, "SCREEN\n", "16384");
    insertKey(ST, "KBD\n", "24576");
    
}
void CompMap(map Comp){
    // Insert possible keys for Comp
    insertKey(Comp, "0\n", "0101010");
    insertKey(Comp, "1\n", "0111111");
    insertKey(Comp, "-1\n", "0111010");
    insertKey(Comp, "D\n", "0001100");
    insertKey(Comp, "A\n", "0110000");
    insertKey(Comp, "M\n", "1110000");
    insertKey(Comp, "!D\n", "0001101");
    insertKey(Comp, "!A\n", "0110001");
    insertKey(Comp, "!M\n", "1110001");
    insertKey(Comp, "-D\n", "0001111");
    insertKey(Comp, "-A\n", "0110011");
    insertKey(Comp, "-M\n", "1110011");
    insertKey(Comp, "D+1\n", "0011111");
    insertKey(Comp, "A+1\n", "0110111");
    insertKey(Comp, "M+1\n", "1110111");
    insertKey(Comp, "D-1\n", "0001110");
    insertKey(Comp, "A-1\n", "0110010");
    insertKey(Comp, "M-1\n", "1110010");
    insertKey(Comp, "D+A\n", "0000010");
    insertKey(Comp, "D+M\n", "1000010");
    insertKey(Comp, "D-A\n", "0010011");
    insertKey(Comp, "D-M\n", "1010011");
    insertKey(Comp, "A-D\n", "0000111");
    insertKey(Comp, "M-D\n", "1000111");
    insertKey(Comp, "D&A\n", "0000000");
    insertKey(Comp, "D&M\n", "1000000");
    insertKey(Comp, "D|A\n", "0010101");
    insertKey(Comp, "D|M\n", "1010101");
    
}

void DestMap(map Dest){
    // Insert possible keys for Dest
    insertKey(Dest, "", "000");
    insertKey(Dest, "M", "001");
    insertKey(Dest, "D", "010");
    insertKey(Dest, "MD", "011");
    insertKey(Dest, "A", "100");
    insertKey(Dest, "AM", "101");
    insertKey(Dest, "AD", "110");
    insertKey(Dest, "AMD", "111");
}

void JumpMap(map Jump){
    // Insert possible keys for Jump
    insertKey(Jump, "", "000");
    insertKey(Jump, "JGT\n", "001");
    insertKey(Jump, "JEQ\n", "010");
    insertKey(Jump, "JGE\n", "011");
    insertKey(Jump, "JLT\n", "100");
    insertKey(Jump, "JNE\n", "101");
    insertKey(Jump, "JLE\n", "110");
    insertKey(Jump, "JMP\n", "111");
}

void DecimalToBinary(int input, char *inputBuffer){
    // 16 bit binary number representation
    int binary[16] = {0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0};
    
    // makes each bit in the string either a 1 or 0 depending on the input
    int i = 0;
    while(input > 0){
        binary[i] = input % 2;
        input = input / 2;
        i++;
    }
    
    // creates a 16 "bit" string to copy values into
    char bin[16] = {'\0'};
    char a[2];
    
    // copies each value from the int array binary into the string bin
    // by using a as a middle-man int to char converter
    int j = 0;
    while(j < 16){
        sprintf(a, "%d", binary[j]);
        bin[j] = a[0];
        j++;
    }
    
    // copies bin back to input buffer and add a null character at the end
    int k = 0;
    while(k < 16){
        inputBuffer[k] = bin[k];
        k++;
    }
    inputBuffer[k] = '\0';
}

// Reverses a string to read properly as a binary number
void reverseString(char *inputBuffer){
    // create a string to copy into
    char str[MAX_LINE_SIZE];
    // begin and end indezes and a count
    int begin, end, count = 0;
    // Find the end of string
    while(inputBuffer[count] != '\0'){
        count++;
    }
    // Set end to the last index of string
    end = count - 1;
    for(begin = 0; begin < count; begin++){
        str[begin] = inputBuffer[end];
        end--;
    }
    // copy the reversed string back into the input buffer
    int i = 0;
    while(inputBuffer[i] != '\0'){
        inputBuffer[i] = str[i];
        i++;
    }
}

// Translate an A command
char translate_A(char *inputBuffer, map Map){
    
    int val;
    char *value;
    // The label character array
    char label[MAX_LINE_SIZE + 1];
    // copy inputBuffer into label
    strcpy(label, inputBuffer);
    // Makes the label easier to check
    makeLabel(label);
    // Gets the value (memory address) of the command
    value = lookupKey(Map, label);
    // converts it to an integer
    val = atoi(value);
    // converts the value to a string binary representation and returns it
    DecimalToBinary(val, inputBuffer);
    return *inputBuffer;
}

// Similar to translate_A but returns the binary representation of the line
// number called after a Label appears
char translate_L(char *inputBuffer, map Map){
    
    int val;
    char *value;
    // The label character array
    char label[MAX_LINE_SIZE + 1];
    // copy inputBuffer into label
    strcpy(label, inputBuffer);
    // Makes the label easier to check
    makeLabel(label);
    // Gets the value (line number) of the label call
    value = lookupKey(Map, label);
    // converts it to an integer
    val = atoi(value);
    // converts the value to a string binary representation and returns it
    DecimalToBinary(val, inputBuffer);
    return *inputBuffer;
    
}


// Translate a C command
void translate_C(char *inputBuffer, map Comp, map Dest, map Jump){
    // The beginning of a string that represents our binary number
    // C commands start with 111 so we can put those in now
    char c[17] = {'1', '1', '1', '\0'};
    
    // Buffer copies the inputBuffer without '=' or ';' signs
    char buffer[5];
    // buffer copies over to a different string; either comp, dest, or jump
    char comp[5];
    char dest[5];
    char jump[5];
    
    // a saves whatever sign is in the inputBuffer; either '=' or ';'
    char a[2];
    
    // Pointers to strings which will hold the return value of the symbol
    // tables when they return their respective binary representation
    char *b;
    char *d;
    char *j;
    // count for inputBuffer, index for the other character arrays, and
    // bufferCount since buffer needs to be reset in the middle of the
    // inputBuffers command
    int index = 0;
    int count = 0;
    int bufferCount = 0;
    
    // Loops and saves characters in the buffer as long as they are not
    // '=' or ';'
    while(inputBuffer[count] != '\0'){
        if(inputBuffer[count] != '=' && inputBuffer[count] != ';'){
            buffer[bufferCount] = inputBuffer[count];
        }
        // If the character that is read is a '=' or ';' then split the
        // command because one part is the dest, jump, or comp depending
        // on the kind of command
        if(inputBuffer[count] == '=' || inputBuffer[count] == ';'){
            // save the type of sign in a[0]
            a[0] = inputBuffer[count];
            // if sign is a '=' then first part is dest
            if(inputBuffer[count] == '='){
                while(buffer[index] != '\0'){
                    dest[index] = buffer[index];
                    index++;
                }
                buffer[0] = '\0';
                bufferCount = -1;
            }
            // if sign is a ';' then first part is comp
            else{
                while(buffer[index] != '\0'){
                    comp[index] = buffer[index];
                    index++;
                }
                comp[index] = '\n';
                comp[index + 1] = '\0';
                buffer[0] = '\0';
                // bufferCount to -1 because it will increment again by the
                // time the loop repeats so it will be back to 0
                bufferCount = -1;
            }
        }
        // increment counts
        count++;
        bufferCount++;
    }
    // set index back to 0
    index = 0;
    
    // if an '=' sign was used, then second part is comp
    if(a[0] == '='){
        while(buffer[index] != '\0'){
            comp[index] = buffer[index];
            index++;
        }
        // make sure after the comp is null
        comp[index] = '\0';
    }
    // if a ';' sign was used, then second part is jump
    else{
        while(buffer[index] != '\0'){
            jump[index] = buffer[index];
            index++;
        }
        // make sure after the jump instruction is null
        jump[index] = '\0';
    }
    
    // if jump command wasn't used, make it null so it translates to 000
    if(a[0] == '='){
        jump[0] = '\0';
    }
    // same with dest
    else{
        dest[0] = '\0';
    }
    
    // get the values of the keys and concatenate them with our string c
    b = lookupKey(Comp, comp);
    strcat(c, b);
    d = lookupKey(Dest, dest);
    strcat(c, d);
    j = lookupKey(Jump, jump);
    strcat(c, j);
    
    // copy c back to the inputBuffer; now a command written in binary
    strcpy(inputBuffer, c);
}

map FirstPass(FILE *inFile, FILE *outFile){
    
    // Creates a map for the labels
    map newMap;
    newMap = createMap(2000);
    
    // Insert predefined symbols into the Map
    Predefined(newMap);
    
    // String array for each line
    char inputBuffer[MAX_LINE_SIZE + 1];
    
    // counts the lines of the file
    int count = 0;
    
    // Gets the first line of the input file
    fgets(inputBuffer, MAX_LINE_SIZE, inFile);
    char linenum[100];
    
    // Main while loop which goes through each line of an input file and
    // removes its whitespace and comments and then translates it into
    // a specific command
    while(!feof(inFile)){
        // Cleans the line
        int printLine = parseLine(inputBuffer);
        // Gets the command type
        char cmd = CommandType(inputBuffer);
        // The label character array
        char label[MAX_LINE_SIZE + 1];
        // If the line is empty do not put it in output file
        if(printLine){
            // Ignore A and C commands in first pass
            if(cmd == 'L'){
                // copy inputBuffer into label
                strcpy(label, inputBuffer);
                // Makes the label easier to check for second pass
                makeLabel(label);
                // Make the count a string
                sprintf(linenum, "%d", count);
                // Add a newline character after the label
                strcat(label, "\n");
                // Put the label and the line number of the next line in table
                insertKey(newMap, label, linenum);
                // Decrease count since we don't count the label itself
                count--;
            }
            // Puts the cleaned up line in the output file
            fputs(inputBuffer, outFile);
            fputs("\n", outFile);
            // Increase the count to count new line
            count++;
        }
        // Get the next line
        fgets(inputBuffer, MAX_LINE_SIZE, inFile);
    }
    
    // Return the map of labels
    return newMap;
}

// Start address and the character array that we convert the address into
int address = 16;
char M[200];

void SecondPass(FILE *in, FILE *out, map Map, map Comp, map Dest, map Jump){
    
    // String array for each line
    char inputBuffer[MAX_LINE_SIZE + 1];
    
    // Gets the first line of the input file
    fgets(inputBuffer, MAX_LINE_SIZE, in);
    
    // While there are still lines in the file
    while(!feof(in)){
        // Command type
        char cmd = CommandType(inputBuffer);
        // The label character array
        char label[MAX_LINE_SIZE + 1];
        // Ignore Labels in second pass
        if(cmd == 'A' || cmd == 'C'){
            // If A command
            if(cmd == 'A'){
                // copy inputBuffer into label
                strcpy(label, inputBuffer);
                // format label to the same as in the symbol table to make
                // checking the symbol table for that key easier
                makeLabel(label);
                // Check to see if A command is already in symbol table
                if(containsKey(Map, label) == -1){
                    // Make address a string
                    sprintf(M, "%d", address);
                    // Add A command to symbol table in next available address
                    // Starting with 16
                    insertKey(Map, label, M);
                    address++;
                    // translate the A command and reverse it
                    translate_A(inputBuffer, Map);
                    reverseString(inputBuffer);
                    // write the binary command into the out file
                    fputs(inputBuffer, out);
                    fputs("\n", out);
                    }
                }else{
                    // writes the line number referencing the label in binary
                    // and then reverses it so it reads correctly
                    translate_L(inputBuffer, Map);
                    reverseString(inputBuffer);
                    // write the binary command into the out file
                    fputs(inputBuffer, out);
                    fputs("\n", out);
                }
            }
            else{
                // if not an A command, translate it as a C command
                translate_C(inputBuffer, Comp, Dest, Jump);
                fputs(inputBuffer, out);
                fputs("\n", out);
            }
        }
        // Gets the next line
        fgets(inputBuffer, MAX_LINE_SIZE, in);
    }
}
