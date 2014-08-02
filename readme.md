## ASE_Loader

A simple MIT-licensed C99-library for reading Adobe Swatch Exchange (.ASE) files.
The library consists of a single header file.

----------------

## Usage

```
//Read ASE-file from filename
ASE_FILE file = openAndReadAseFile("file.ase");

//Read ASE-file from file stream
FILE *f = fopen("file.ase","r");
ASE_FILE file = readAseFile(f);
fclose(f);

//Parse ASE-file
for(int i=0;i<file.numGroups;i++){
    GROUP *group = file.groups + i;
    // Name: group->name (wchar_t *)
    for(int ii=0;ii<group->numColors;ii++){
        COLOR *color = group->colors + ii;
        // Name: color->name (wchar_t *)
        // Color type: color->type (enum, one of COLORTYPE_RGB, COLORTYPE_CMYK,
        //        COLORTYPE_LAB or COLORTYPE_GRAY)
        // Color values: color->col (float[4], unused channels are -1.f)
    }
}
```
