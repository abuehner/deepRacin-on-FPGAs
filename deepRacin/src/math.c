#include <cmath>

void computeExp(
    float* gInput,
    float* outputArr,
	int gx, int gy, int gz,
	int sizeX, int sizeY
    )
{
	int mult = gz*(sizeX*sizeY);
	int mult2 = gy * sizeX;
	int gid = mult +(mult2+ gx);
    outputArr[gid] = exp(gInput[gid]);
}

void mulScalar(
    float * gInput,
    float* outputArr,
    float scalar,
	int gx, int gy, int gz,
	int sizeX, int sizeY
    )
{
	int mult = gz*(sizeX*sizeY);
	int mult2 = gy * sizeX;
	int gid = mult +(mult2+ gx);
    outputArr[gid] = gInput[gid]*scalar;
}
