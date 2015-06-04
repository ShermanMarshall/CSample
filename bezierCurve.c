#include "bezierCurve.h"

int numArrayItems(int order, int segments) {
    return 3 * segments;
}

void makeBezierCurve (int order, float curve[], int segments, float xCoords[],	float yCoords[], float zCoords[]) {

	float* xBasis = makeBezierBasis(xCoords, order);
	float* yBasis = makeBezierBasis(yCoords, order);
	float* zBasis = makeBezierBasis(zCoords, order);

	int index = 0;

	curve[index++] = xCoords[0];
	curve[index++] = yCoords[0];
   	curve[index++] = zCoords[0];
    
    for (float x = 1; x < (segments - 1); x++, index+=3) {
        float t = 1; curve[index] = curve[index + 1] = curve[index + 2] = 0.0f;
        
        for (int y = 0; y <= order; y++) {
            for (int z = 0; z < y; z++)
                t *= x/segments;
            
            curve[index] += t * xBasis[y];
            curve[index + 1] += t * yBasis[y];
            curve[index + 2] += t * zBasis[y];
        }
        
    }
    
    curve[index++] = xCoords[order];
    curve[index++] = yCoords[order];
    curve[index] = zCoords[order];
}

float* makeBezierBasis (float coords[], int order) {
	int a = order; 
	
    	float* geometryBasis= malloc(sizeof(float)*(order+1)); //new float[order+1];
    
	float mat[a+1][a+1]; int n = a;

	for (int x = 0; x <= n; x++) {
                float coeff = coefficient(n, x); int order = n - x;

                for (int y = 0; y <= n; y++) {
                        if (y <= order) {
                                mat[y][x] = coeff * coefficient(order, y);

                                if ((order - y) % 2)
                                        mat[y][x] *= -1;
                        } else {
                                mat[y][x] = 0;
                        }
                }
        }
	
	for (int x = 0; x <= a; x++) {
		geometryBasis[x] = 0;

		for (int y = 0; y <= a; y++) {
			geometryBasis[x] += mat[y][x] * coords[y];
		}
	}
    
	return geometryBasis;
}

float coefficient (int n, int i) {
	int iterations; float num, denom;
	num = denom = 1; iterations = n - i;

	for (int x = n, y = 0; y < iterations; x--, y++) 
		num *= x;
	
	for (int x = iterations; x > 1; x--)
		denom *= x;
	
	return num/denom;
}

