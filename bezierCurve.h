#ifndef __bezierCurve_h_included__
#define __bezierCurve_h_included__

    int coefficient(int n, int i);
    float* makeBezierBasis (float coords[], int order);
    void makeBezierCurve (int order, float curve[], int segments, float xCoords[],
                          float yCoords[], float zCoords[]);

#endif

