//
//  code.h
//  assembler
//
//  Created by Zeke Palmer on 4/15/21.
//

#ifndef code_h
#define code_h

#include <stdio.h>
#include "map.h"
#endif /* code_h */

void CompMap(map Comp);
void DestMap(map Dest);
void JumpMap(map Jump);

map FirstPass(FILE *inFile, FILE *outFile);

void SecondPass(FILE *in, FILE *out, map Map, map Comp, map Dest, map Jump);

