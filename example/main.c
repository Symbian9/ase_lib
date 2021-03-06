#include <stdio.h>
#include "ase_loader.h"
#include "ase_writer.h"
int main(int argc, char **argv)
{
    ASE_FILE ase;
    ASE_ERRORTYPE error;
    uint16_t i, ii, a, numFiles = 1;
    const char *filenames[] = {"data/example.ase"};
    for(a=0;a<numFiles;a++){
        /*     --- Read ase file ---      */
        printf("Loading file %s\n", filenames[a]);
        error = ase_openAndReadAseFile(&ase, filenames[a]);
        printf("ASE file version %d.%d\n", ase.version[0],ase.version[1]);
        if(!error){
            for(i=0;i<ase.numGroups;i++){
                ASE_GROUP *group = ase.groups + i;
                printf("  Group \"%s\"\n", group->name);
                for(ii=0;ii<group->numColors;ii++){
                    ASE_COLOR *color = group->colors + ii;
                    uint16_t iii = 0;
                    char *typeName;
                    int16_t numVars = 0;
                    switch(color->type){
                        case ASE_COLORTYPE_RGB:  typeName = "RGB";  numVars = 3;  break;
                        case ASE_COLORTYPE_CMYK: typeName = "CMYK"; numVars = 4; break;
                        case ASE_COLORTYPE_LAB:  typeName = "LAB";  numVars = 3;  break;
                        case ASE_COLORTYPE_GRAY: typeName = "Gray"; numVars = 1; break;
                    }
                    printf("    Color [%s] \"%s\"\n      ",typeName,color->name);
                    while(iii < numVars){
                        printf("%f ", color->col[iii]);
                        iii++;
                    }
                    printf("\n");
                }
            }
            /*     --- Write ase file ---      */
            printf("Writing file %s\n", "data/out.ase");
            if(ase_openAndWriteAseFile(&ase,"data/out.ase")){
                printf("  Error occured: %s\n", ase_getErrorString(error));
            }
            /* --- Don't forget to free the data structure --- */
            ase_freeAseFile(&ase);
        }
        else{
            printf("  Error occured: %s\n", ase_getErrorString(error));
        }
    }
    return 0;
}
