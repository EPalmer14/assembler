//
//  main.c
//  assembler
//
//  Created by Zeke Palmer and Siobhan Lounsbury on 4/8/21.
//
//  By Zeke Palmer and Siobhan Lounsbury
//  CS140
//  2021

#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "parser.h"
#include "code.h"
#define MAX_LINE_SIZE 200



int main(int argc, char** argv) {
    
    // Maps for different purposes; ST handles Labels; The others are the
    // pieces of a binary command
    map ST;
    map Comp = createMap(2000);
    map Dest = createMap(2000);
    map Jump = createMap(2000);
    
    // Initialize symbol table keys
    CompMap(Comp);
    DestMap(Dest);
    JumpMap(Jump);
    
    //if(argc != 3){
        //puts("Usage: ./assembler inputfile.asm outputfile.hack");
        //exit(1);
    //}
    
    // In and out files
    char* infileName = "/Users/zekepalmer/Desktop/assembler/assembler/Pong.asm";
    char* outfileName = "out.txt";
    
    // Open the input file and output file
    FILE* inFile = fopen(infileName, "r");
    FILE* outFile = fopen(outfileName, "w");
    
    // If the input file is NULL, throw an error
    if(inFile == NULL) {
            perror("Error opening input file:");
            exit(1);
        }
    
    // First pass; return the symbol table created with labels
    ST = FirstPass(inFile, outFile);
    
    // close the files
    fclose(outFile);
    fclose(inFile);
    
    // open the file that is the same input file but cleaned up with no spaces
    // or comments and create a new output file
    char *secondIn = "out.txt";
    char *finalOut = "outputfile.hack";
    
    // second input file is for reading, last output file is for writing
    FILE *in = fopen(secondIn, "r");
    FILE *out = fopen(finalOut, "w");
    
    // if NULL, then there was an error opening th file
    if(in == NULL){
        perror("Error opening input file:");
        exit(1);
    }
    
    // Second pass;
    SecondPass(in, out, ST, Comp, Dest, Jump);
    
    // close the files
    fclose(out);
    fclose(in);
    
}


