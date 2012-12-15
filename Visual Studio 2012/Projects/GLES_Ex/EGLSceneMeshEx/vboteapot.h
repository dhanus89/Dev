#ifndef VBOTEAPOT_H
#define VBOTEAPOT_H
#include "drawable.h"
#include "DXMatrix.h"
#include "DXVector.h"

class VBOTeapot : public Drawable
{
private:
    unsigned int vaoHandle;
    unsigned int faces;

    void generatePatches(float * v, float * n, float *tc, unsigned int* el, int grid);
    void buildPatchReflect(int patchNum,
                           float *B, float *dB,
                           float *v, float *n, float *, unsigned int *el,
                           int &index, int &elIndex, int &, int grid,
                           bool reflectX, bool reflectY);
    void buildPatch(DXVector3 patch[][4],
                    float *B, float *dB,
                    float *v, float *n,float *, unsigned int *el,
                    int &index, int &elIndex, int &, int grid, DXMatrix33 reflect, bool invertNormal);
    void getPatch( int patchNum, DXVector3 patch[][4], bool reverseV );

    void computeBasisFunctions( float * B, float * dB, int grid );
    DXVector3 evaluate( int gridU, int gridV, float *B, DXVector3 patch[][4] );
    DXVector3 evaluateNormal( int gridU, int gridV, float *B, float *dB, DXVector3 patch[][4] );
    void moveLid(int,float *,DXMatrix44);

public:
    VBOTeapot(int grid, DXMatrix44 lidTransform);

    void render() const;
};

#endif // VBOTEAPOT_H
