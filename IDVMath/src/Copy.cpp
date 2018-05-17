#include <IDVMath.h>
#include <iostream>

void PrintMatrix(const XMATRIX44& Matrix)
{
	std::cout << "( " << Matrix.m11 << ", " << Matrix.m12 << ", " << Matrix.m13 << ", " << Matrix.m14 << ")" << std::endl;
	std::cout << "( " << Matrix.m21 << ", " << Matrix.m22 << ", " << Matrix.m23 << ", " << Matrix.m24 << ")" << std::endl;
	std::cout << "( " << Matrix.m31 << ", " << Matrix.m32 << ", " << Matrix.m33 << ", " << Matrix.m34 << ")" << std::endl;
	std::cout << "( " << Matrix.m41 << ", " << Matrix.m42 << ", " << Matrix.m43 << ", " << Matrix.m44 << ")" << std::endl;
}
void PrintVector3(const XVECTOR3&Vec3)
{
	std::cout << "( " << Vec3.x << " )" << std::endl;
	std::cout << "( " << Vec3.y << " )" << std::endl;
	std::cout << "( " << Vec3.z << " )" << std::endl;
}
void PrintVector2(const XVECTOR2&Vec2)
{
	std::cout << "( " << Vec2.x << " )" << std::endl;
	std::cout << "( " << Vec2.y << " )" << std::endl;
}
void XMatMultiply(XMATRIX44 & result, const XMATRIX44 & A, const XMATRIX44 & B)
{
	memset(&result.m[0], 0, sizeof(result));
	result.m11 = (A.m11*B.m11 + A.m12*B.m21 + A.m13*B.m31 + A.m14*B.m41);
	result.m12 = (A.m11*B.m12 + A.m12*B.m22 + A.m13*B.m32 + A.m14*B.m42);
	result.m13 = (A.m11*B.m13 + A.m12*B.m23 + A.m13*B.m33 + A.m14*B.m43);
	result.m14 = (A.m11*B.m14 + A.m12*B.m24 + A.m13*B.m34 + A.m14*B.m44);

	result.m21 = (A.m21*B.m11 + A.m22*B.m21 + A.m23*B.m31 + A.m24*B.m41);
	result.m22 = (A.m21*B.m12 + A.m22*B.m22 + A.m23*B.m32 + A.m24*B.m42);
	result.m23 = (A.m21*B.m13 + A.m22*B.m23 + A.m23*B.m33 + A.m24*B.m43);
	result.m24 = (A.m21*B.m14 + A.m22*B.m24 + A.m23*B.m34 + A.m24*B.m44);

	result.m31 = (A.m31*B.m11 + A.m32*B.m21 + A.m33*B.m31 + A.m34*B.m41);
	result.m32 = (A.m31*B.m12 + A.m32*B.m22 + A.m33*B.m32 + A.m34*B.m42);
	result.m33 = (A.m31*B.m13 + A.m32*B.m23 + A.m33*B.m33 + A.m34*B.m43);
	result.m34 = (A.m31*B.m14 + A.m32*B.m24 + A.m33*B.m34 + A.m34*B.m44);

	result.m41 = (A.m41*B.m11 + A.m42*B.m21 + A.m43*B.m31 + A.m44*B.m41);
	result.m42 = (A.m41*B.m12 + A.m42*B.m22 + A.m43*B.m32 + A.m44*B.m42);
	result.m43 = (A.m41*B.m13 + A.m42*B.m23 + A.m43*B.m33 + A.m44*B.m43);
	result.m44 = (A.m41*B.m14 + A.m42*B.m24 + A.m43*B.m34 + A.m44*B.m44);
	
}

void XMatTranslation(XMATRIX44 & ToTranslate, const float & dX, const float & dY, const float & dZ)
{
	ToTranslate.m41 += dX;
	ToTranslate.m42 += dY;
	ToTranslate.m43 += dZ;
	
}

void XMatTranslation(XMATRIX44 & ToTranslate, XVECTOR3&Differential)
{
	//ToTranslate.m11 += Differential.x; ToTranslate.m12 += Differential.x; ToTranslate.m13 += Differential.x; ToTranslate.m14 += Differential.x;
	//ToTranslate.m21 += Differential.y; ToTranslate.m22 += Differential.y; ToTranslate.m23 += Differential.y; ToTranslate.m24 += Differential.y;
	//ToTranslate.m31 += Differential.z; ToTranslate.m32 += Differential.z; ToTranslate.m33 += Differential.z; ToTranslate.m34 += Differential.z;
	ToTranslate.m41 += Differential.x;
	ToTranslate.m42 += Differential.y;
	ToTranslate.m43 += Differential.z;
}

void XMatScaling(XMATRIX44 & ToScale, const float & kX, const float &kY, const float &kZ)
{
	ToScale.m11 *= kX; ToScale.m12 *= kX; ToScale.m13 *= kX; ToScale.m14 *= kX;
	ToScale.m21 *= kY; ToScale.m22 *= kY; ToScale.m23 *= kY; ToScale.m24 *= kY;
	ToScale.m31 *= kZ; ToScale.m32 *= kZ; ToScale.m33 *= kZ; ToScale.m34 *= kZ;

}

void XMatRotationXLH(XMATRIX44 & RotateXLH, const float & thetta)
{
	XMATRIX44 Temp = RotateXLH;
	Temp.m21 = (RotateXLH.m21*cos(thetta)) + (RotateXLH.m31*sin(thetta)); Temp.m22 = (RotateXLH.m22*cos(thetta)) + (RotateXLH.m32*sin(thetta)); 
	Temp.m23 = (RotateXLH.m23*cos(thetta)) + (RotateXLH.m33*sin(thetta)); Temp.m24 = (RotateXLH.m24*cos(thetta)) + (RotateXLH.m34*sin(thetta));
	
	Temp.m31 = (-RotateXLH.m21*sin(thetta)) + (RotateXLH.m31*cos(thetta)); Temp.m32 = (-RotateXLH.m22*sin(thetta)) + (RotateXLH.m32*cos(thetta));
	Temp.m33 = (-RotateXLH.m23*sin(thetta)) + (RotateXLH.m33*cos(thetta)); Temp.m34 = (-RotateXLH.m24*sin(thetta)) + (RotateXLH.m34*cos(thetta));
	
	RotateXLH=Temp;
}

void XMatRotationXRH(XMATRIX44 & RotateXRH, const float & thetta)
{
	XMATRIX44 Temp = RotateXRH;
	Temp.m21 = (RotateXRH.m21*cos(thetta)) - (RotateXRH.m31*sin(thetta)); Temp.m22 = (RotateXRH.m22*cos(thetta)) - (RotateXRH.m32*sin(thetta));
	Temp.m23 = (RotateXRH.m23*cos(thetta)) - (RotateXRH.m33*sin(thetta)); Temp.m24 = (RotateXRH.m24*cos(thetta)) - (RotateXRH.m34*sin(thetta));

	Temp.m31 = (RotateXRH.m21*sin(thetta)) + (RotateXRH.m31*cos(thetta)); Temp.m32 = (RotateXRH.m22*sin(thetta)) + (RotateXRH.m32*cos(thetta));
	Temp.m33 = (RotateXRH.m23*sin(thetta)) + (RotateXRH.m33*cos(thetta)); Temp.m34 = (RotateXRH.m24*sin(thetta)) + (RotateXRH.m34*cos(thetta));

	RotateXRH = Temp;
}

void XMatRotationYLH(XMATRIX44 & RotateYLH, const float & thetta)
{
	XMATRIX44 Temp = RotateYLH;
	Temp = RotateYLH;
	Temp.m11 = (RotateYLH.m11*cos(thetta)) - (RotateYLH.m31*sin(thetta)); Temp.m12 = (RotateYLH.m12*cos(thetta)) - (RotateYLH.m32*sin(thetta));
	Temp.m13 = (RotateYLH.m13*cos(thetta)) - (RotateYLH.m33*sin(thetta)); Temp.m14 = (RotateYLH.m14*cos(thetta)) - (RotateYLH.m34*sin(thetta));
					  																							  
	Temp.m31 = (RotateYLH.m11*sin(thetta)) + (RotateYLH.m31*cos(thetta)); Temp.m32 = (RotateYLH.m12*sin(thetta)) + (RotateYLH.m32*cos(thetta));
	Temp.m33 = (RotateYLH.m13*sin(thetta)) + (RotateYLH.m33*cos(thetta)); Temp.m34 = (RotateYLH.m14*sin(thetta)) + (RotateYLH.m34*cos(thetta));

	RotateYLH = Temp;
}

void XMatRotationYRH(XMATRIX44 & RotateYRH, const float & thetta)
{
	XMATRIX44 Temp = RotateYRH;
	Temp = RotateYRH;
	Temp.m11 = (RotateYRH.m11*cos(thetta)) + (RotateYRH.m31*sin(thetta)); Temp.m12 = (RotateYRH.m12*cos(thetta)) + (RotateYRH.m32*sin(thetta));
	Temp.m13 = (RotateYRH.m13*cos(thetta)) + (RotateYRH.m33*sin(thetta)); Temp.m14 = (RotateYRH.m14*cos(thetta)) + (RotateYRH.m34*sin(thetta));

	Temp.m31 = (-RotateYRH.m11*sin(thetta)) + (RotateYRH.m31*cos(thetta)); Temp.m32 = (-RotateYRH.m12*sin(thetta)) + (RotateYRH.m32*cos(thetta));
	Temp.m33 = (-RotateYRH.m13*sin(thetta)) + (RotateYRH.m33*cos(thetta)); Temp.m34 = (-RotateYRH.m14*sin(thetta)) + (RotateYRH.m34*cos(thetta));

	RotateYRH = Temp;
}

void XMatRotationZLH(XMATRIX44 &RotateZLH, const float & thetta)
{
	XMATRIX44 Temp = RotateZLH;
	Temp = RotateZLH;
	Temp.m11 = (RotateZLH.m11*cos(thetta)) + (RotateZLH.m21*sin(thetta)); Temp.m12 = (RotateZLH.m12*cos(thetta)) + (RotateZLH.m22*sin(thetta));
	Temp.m13 = (RotateZLH.m13*cos(thetta)) + (RotateZLH.m23*sin(thetta)); Temp.m14 = (RotateZLH.m14*cos(thetta)) + (RotateZLH.m24*sin(thetta));

	Temp.m21 = (RotateZLH.m11*sin(-thetta)) + (RotateZLH.m21*cos(thetta)); Temp.m22 = (RotateZLH.m12*sin(-thetta)) + (RotateZLH.m22*cos(thetta));
	Temp.m23 = (RotateZLH.m13*sin(-thetta)) + (RotateZLH.m23*cos(thetta)); Temp.m24 = (RotateZLH.m14*sin(-thetta)) + (RotateZLH.m24*cos(thetta));

	RotateZLH = Temp;
}

void XMatRotationZRH(XMATRIX44 & RotateZRH, const float & thetta)
{
	XMATRIX44 Temp = RotateZRH;
	Temp = RotateZRH;
	Temp.m11 = (RotateZRH.m11*cos(thetta)) - (RotateZRH.m21*sin(thetta)); Temp.m12 = (RotateZRH.m12*cos(thetta)) - (RotateZRH.m22*sin(thetta));
	Temp.m13 = (RotateZRH.m13*cos(thetta)) - (RotateZRH.m23*sin(thetta)); Temp.m14 = (RotateZRH.m14*cos(thetta)) - (RotateZRH.m24*sin(thetta));
					   								 										 							   
	Temp.m21 = (RotateZRH.m11*sin(thetta)) + (RotateZRH.m21*cos(thetta)); Temp.m22 = (RotateZRH.m12*sin(thetta)) + (RotateZRH.m22*cos(thetta));
	Temp.m23 = (RotateZRH.m13*sin(thetta)) + (RotateZRH.m23*cos(thetta)); Temp.m24 = (RotateZRH.m14*sin(thetta)) + (RotateZRH.m24*cos(thetta));

	RotateZRH = Temp;
}

void XMatTranspose(XMATRIX44 &Transposed, XMATRIX44 ToTranspose )
{
	Transposed = ToTranspose;
	Transposed.m12 = ToTranspose.m21; Transposed.m13 = ToTranspose.m31; Transposed.m14 = ToTranspose.m41;
	Transposed.m21 = ToTranspose.m12; Transposed.m23 = ToTranspose.m32; Transposed.m24 = ToTranspose.m42;
	Transposed.m31 = ToTranspose.m13; Transposed.m32 = ToTranspose.m23; Transposed.m34 = ToTranspose.m43;
	Transposed.m41 = ToTranspose.m14; Transposed.m42 = ToTranspose.m24; Transposed.m43 = ToTranspose.m34;

}

void XMatIdentity(XMATRIX44 & matrix)
{
	memset(&matrix.m[0], 0, sizeof(matrix.m));
	matrix.m11 = 1; matrix.m22 = 1; matrix.m33 = 1; matrix.m44 = 1;

}

void XMatViewLookAtLH(XMATRIX44 &mpout, const XVECTOR3 &camPos, const XVECTOR3 &lookAt, const XVECTOR3 &upAxis) {
	XVECTOR3 zaxe = lookAt - camPos;
	zaxe.Normalize();

	XVECTOR3 xaxe;
	XVecCross(xaxe, upAxis, zaxe);
	xaxe.Normalize();

	XVECTOR3 yaxe;
	XVecCross(yaxe, zaxe, xaxe);

	mpout.m[0][0] = xaxe.x;
	mpout.m[0][1] = yaxe.x;
	mpout.m[0][2] = zaxe.x;
	XVecDot(mpout.m[3][0], xaxe, camPos);
	mpout.m[3][0] = -mpout.m[3][0];

	mpout.m[1][0] = xaxe.y;
	mpout.m[1][1] = yaxe.y;
	mpout.m[1][2] = zaxe.y;
	XVecDot(mpout.m[3][1], yaxe, camPos);
	mpout.m[3][1] = -mpout.m[3][1];

	mpout.m[2][0] = xaxe.z;
	mpout.m[2][1] = yaxe.z;
	mpout.m[2][2] = zaxe.z;
	XVecDot(mpout.m[3][2], zaxe, camPos);
	mpout.m[3][2] = -mpout.m[3][2];

	mpout.m[0][3] = 0.0f;
	mpout.m[1][3] = 0.0f;
	mpout.m[2][3] = 0.0f;
	mpout.m[3][3] = 1.0f;
}

void XMatViewLookAtRH(XMATRIX44 &mpout, const XVECTOR3 &camPos, const XVECTOR3 &lookAt, const XVECTOR3 &upAxis) {
	XVECTOR3 zaxe = camPos - lookAt;
	zaxe.Normalize();

	XVECTOR3 xaxe;
	XVecCross(xaxe, upAxis, zaxe);
	xaxe.Normalize();

	XVECTOR3 yaxe;
	XVecCross(yaxe, zaxe, xaxe);

	mpout.m[0][0] = xaxe.x;
	mpout.m[0][1] = yaxe.x;
	mpout.m[0][2] = zaxe.x;
	XVecDot(mpout.m[3][0], xaxe, camPos);
	mpout.m[3][0] = -mpout.m[3][0];

	mpout.m[1][0] = xaxe.y;
	mpout.m[1][1] = yaxe.y;
	mpout.m[1][2] = zaxe.y;
	XVecDot(mpout.m[3][1], yaxe, camPos);
	mpout.m[3][1] = -mpout.m[3][1];

	mpout.m[2][0] = xaxe.z;
	mpout.m[2][1] = yaxe.z;
	mpout.m[2][2] = zaxe.z;
	XVecDot(mpout.m[3][2], zaxe, camPos);
	mpout.m[3][2] = -mpout.m[3][2];

	mpout.m[0][3] = 0.0f;
	mpout.m[1][3] = 0.0f;
	mpout.m[2][3] = 0.0f;
	mpout.m[3][3] = 1.0f;
}

void XMatPerspectiveLH(XMATRIX44 &mpout, const float &FOV, const float &Aspect, const float &NearPlane, const float &FarPlane) {
	float x, y;
	float ang = FOV / 2.0f;

	y = cos(ang) / sin(ang);
	x = y / Aspect;

	mpout.m[0][0] = x;
	mpout.m[1][1] = y;
	mpout.m[2][2] = FarPlane / (FarPlane - NearPlane);
	mpout.m[2][3] = 1.0;
	mpout.m[3][2] = -(NearPlane*FarPlane) / (FarPlane - NearPlane);
	//mpout.m[3][3] = 0.0f;

}

void XMatPerspectiveRH(XMATRIX44 &mpout, const float &FOV, const float &Aspect, const float &NearPlane, const float &FarPlane)
{
	float x, y;
	float ang = FOV / 2.0f;

	y = cos(ang) / sin(ang);
	x = y / Aspect;

	mpout.m[0][0] = x;
	mpout.m[1][1] = y;
	mpout.m[2][2] = FarPlane / (NearPlane - FarPlane);
	mpout.m[2][3] = -1.0;
	mpout.m[3][2] = (NearPlane*FarPlane) / (NearPlane - FarPlane);
	mpout.m[3][3] = 0.0f;
}

void XMatOrthoLH(XMATRIX44 &m, const float &w, const float &h, const float &zn, const float &zf) {
	m.m[0][0] = 2.0f / w;
	m.m[1][1] = 2.0f / h;
	m.m[2][2] = 1.0f / (zf - zn);
	m.m[3][2] = -zn / (zf - zn);
	m.m[3][3] = 1.0f;
}

void XMatOrthoRH(XMATRIX44 &m, const float &w, const float &h, const float &zn, const float &zf) {
	m.m[0][0] = 2.0f / w;
	m.m[1][1] = 2.0f / h;
	m.m[2][2] = 1.0f / (zn - zf);
	m.m[3][2] = zn / (zn - zf);
	m.m[3][3] = 1.0f;
}

void XMatRotationAxisLH(XMATRIX44 & MatrixLH, const XVECTOR3 & RAxisLH, const float & thetta)
{
	XMATRIX44 Temp = MatrixLH;
	XVECTOR3 Normal;
	float costhetta = cos(thetta);
	float sinthetta = sin(thetta);
	float oneminusc = (1 - costhetta);
	XVec3Normalize(Normal, RAxisLH);
	Temp.m11 = (
		(MatrixLH.m11*((Normal.x*Normal.x*oneminusc) + costhetta)) + 
		(MatrixLH.m21*((Normal.x*Normal.y*oneminusc) + (sinthetta*Normal.z))) + 
		(MatrixLH.m31*((Normal.x*Normal.z*oneminusc) - (sinthetta*Normal.y)))
		);
	Temp.m12= (
		(MatrixLH.m12*((Normal.x*Normal.x*oneminusc) + costhetta)) +
		(MatrixLH.m22*((Normal.x*Normal.y*oneminusc) + (sinthetta*Normal.z))) +
		(MatrixLH.m32*((Normal.x*Normal.z*oneminusc) - (sinthetta*Normal.y)))
		);
	Temp.m13 = (
		(MatrixLH.m13*((Normal.x*Normal.x*oneminusc) + costhetta)) +
		(MatrixLH.m23*((Normal.x*Normal.y*oneminusc) + (sinthetta*Normal.z))) +
		(MatrixLH.m33*((Normal.x*Normal.z*oneminusc) - (sinthetta*Normal.y)))
		);
	Temp.m14 = (
		(MatrixLH.m14*((Normal.x*Normal.x*oneminusc) + costhetta)) +
		(MatrixLH.m24*((Normal.x*Normal.y*oneminusc) + (sinthetta*Normal.z))) +
		(MatrixLH.m34*((Normal.x*Normal.z*oneminusc) - (sinthetta*Normal.y)))
		);

	Temp.m21 = (
		(MatrixLH.m11*((Normal.y*Normal.x*oneminusc) - (sinthetta*Normal.z))) +
		(MatrixLH.m21*((Normal.y*Normal.y*oneminusc) + costhetta)) +
		(MatrixLH.m31*((Normal.y*Normal.z*oneminusc) + (sinthetta*Normal.x)))
		);
	Temp.m22 = (
		(MatrixLH.m12*((Normal.y*Normal.x*oneminusc) - (sinthetta*Normal.z))) +
		(MatrixLH.m22*((Normal.y*Normal.y*oneminusc) + costhetta)) +
		(MatrixLH.m33*((Normal.y*Normal.z*oneminusc) + (sinthetta*Normal.x)))
		);
	Temp.m23 = (
		(MatrixLH.m13*((Normal.y*Normal.x*oneminusc) - (sinthetta*Normal.z))) +
		(MatrixLH.m23*((Normal.y*Normal.y*oneminusc) + costhetta)) +
		(MatrixLH.m33*((Normal.y*Normal.z*oneminusc) + (sinthetta*Normal.x)))
		);
	Temp.m24 = (
		(MatrixLH.m14*((Normal.y*Normal.x*oneminusc) - (sinthetta*Normal.z))) +
		(MatrixLH.m24*((Normal.y*Normal.y*oneminusc) + costhetta)) +
		(MatrixLH.m34*((Normal.y*Normal.z*oneminusc) + (sinthetta*Normal.x)))
		);
	Temp.m31 = (
		(MatrixLH.m11*((Normal.z*Normal.x*oneminusc) + (sinthetta*Normal.y))) +
		(MatrixLH.m21*((Normal.z*Normal.y*oneminusc) - (sinthetta*Normal.x))) +
		(MatrixLH.m31*((Normal.z*Normal.z*oneminusc) + costhetta))
		);
	Temp.m32 = (
		(MatrixLH.m12*((Normal.z*Normal.x*oneminusc) + (sinthetta*Normal.y))) +
		(MatrixLH.m22*((Normal.z*Normal.y*oneminusc) - (sinthetta*Normal.x))) +
		(MatrixLH.m32*((Normal.z*Normal.z*oneminusc) + costhetta))
		);
	Temp.m33 = (
		(MatrixLH.m13*((Normal.z*Normal.x*oneminusc) + (sinthetta*Normal.y))) +
		(MatrixLH.m23*((Normal.z*Normal.y*oneminusc) - (sinthetta*Normal.x))) +
		(MatrixLH.m33*((Normal.z*Normal.z*oneminusc) + costhetta))
		);
	Temp.m34 = (
		(MatrixLH.m14*((Normal.z*Normal.x*oneminusc) + (sinthetta*Normal.y))) +
		(MatrixLH.m24*((Normal.z*Normal.y*oneminusc) - (sinthetta*Normal.x))) +
		(MatrixLH.m34*((Normal.z*Normal.z*oneminusc) + costhetta))
		);
	MatrixLH = Temp;
}

void XMatRotationAxisRH(XMATRIX44 & MatrixRH, const XVECTOR3 & RAxisRH, const float & thetta)
{
	XMATRIX44 Temp = MatrixRH;
	XVECTOR3 Normal;
	float costhetta = cos(thetta);
	float sinthetta = sin(thetta);
	float oneminusc = (1 - costhetta);
	XVec3Normalize(Normal, RAxisRH);
	Temp.m11 = (
		(MatrixRH.m11*((Normal.x*Normal.x*oneminusc) + costhetta)) +
		(MatrixRH.m21*((Normal.x*Normal.y*oneminusc) - (sinthetta*Normal.z))) +
		(MatrixRH.m31*((Normal.x*Normal.z*oneminusc) + (sinthetta*Normal.y)))
		);
	Temp.m12 = (
		(MatrixRH.m12*((Normal.x*Normal.x*oneminusc) + costhetta)) +
		(MatrixRH.m22*((Normal.x*Normal.y*oneminusc) - (sinthetta*Normal.z))) +
		(MatrixRH.m32*((Normal.x*Normal.z*oneminusc) + (sinthetta*Normal.y)))
		);
	Temp.m13 = (
		(MatrixRH.m13*((Normal.x*Normal.x*oneminusc) + costhetta)) +
		(MatrixRH.m23*((Normal.x*Normal.y*oneminusc) - (sinthetta*Normal.z))) +
		(MatrixRH.m33*((Normal.x*Normal.z*oneminusc) + (sinthetta*Normal.y)))
		);
	Temp.m14 = (
		(MatrixRH.m14*((Normal.x*Normal.x*oneminusc) + costhetta)) +
		(MatrixRH.m24*((Normal.x*Normal.y*oneminusc) - (sinthetta*Normal.z))) +
		(MatrixRH.m34*((Normal.x*Normal.z*oneminusc) + (sinthetta*Normal.y)))
		);

	Temp.m21 = (
		(MatrixRH.m11*((Normal.y*Normal.x*oneminusc) + (sinthetta*Normal.z))) +
		(MatrixRH.m21*((Normal.y*Normal.y*oneminusc) + costhetta)) +
		(MatrixRH.m31*((Normal.y*Normal.z*oneminusc) - (sinthetta*Normal.x)))
		);
	Temp.m22 = (
		(MatrixRH.m12*((Normal.y*Normal.x*oneminusc) + (sinthetta*Normal.z))) +
		(MatrixRH.m22*((Normal.y*Normal.y*oneminusc) + costhetta)) +
		(MatrixRH.m33*((Normal.y*Normal.z*oneminusc) - (sinthetta*Normal.x)))
		);
	Temp.m23 = (
		(MatrixRH.m13*((Normal.y*Normal.x*oneminusc) + (sinthetta*Normal.z))) +
		(MatrixRH.m23*((Normal.y*Normal.y*oneminusc) + costhetta)) +
		(MatrixRH.m33*((Normal.y*Normal.z*oneminusc) - (sinthetta*Normal.x)))
		);
	Temp.m24 = (
		(MatrixRH.m14*((Normal.y*Normal.x*oneminusc) + (sinthetta*Normal.z))) +
		(MatrixRH.m24*((Normal.y*Normal.y*oneminusc) + costhetta)) +
		(MatrixRH.m34*((Normal.y*Normal.z*oneminusc) - (sinthetta*Normal.x)))
		);
	Temp.m31 = (
		(MatrixRH.m11*((Normal.z*Normal.x*oneminusc) - (sinthetta*Normal.y))) +
		(MatrixRH.m21*((Normal.z*Normal.y*oneminusc) + (sinthetta*Normal.x))) +
		(MatrixRH.m31*((Normal.z*Normal.z*oneminusc) + costhetta))
		);
	Temp.m32 = (
		(MatrixRH.m12*((Normal.z*Normal.x*oneminusc) - (sinthetta*Normal.y))) +
		(MatrixRH.m22*((Normal.z*Normal.y*oneminusc) + (sinthetta*Normal.x))) +
		(MatrixRH.m32*((Normal.z*Normal.z*oneminusc) + costhetta))
		);
	Temp.m33 = (
		(MatrixRH.m13*((Normal.z*Normal.x*oneminusc) - (sinthetta*Normal.y))) +
		(MatrixRH.m23*((Normal.z*Normal.y*oneminusc) + (sinthetta*Normal.x))) +
		(MatrixRH.m33*((Normal.z*Normal.z*oneminusc) + costhetta))
		);
	Temp.m34 = (
		(MatrixRH.m14*((Normal.z*Normal.x*oneminusc) - (sinthetta*Normal.y))) +
		(MatrixRH.m24*((Normal.z*Normal.y*oneminusc) + (sinthetta*Normal.x))) +
		(MatrixRH.m34*((Normal.z*Normal.z*oneminusc) + costhetta))
		);
	MatrixRH = Temp;
}

void XVecTransformLH(XVECTOR3 & Transformed, const XVECTOR3 & SrcVector, const XMATRIX44 & SrcMatrix)
{
	Transformed.x = (SrcMatrix.m11 * SrcVector.x) + (SrcMatrix.m12 * SrcVector.y) + (SrcMatrix.m13 * SrcVector.z) + (SrcMatrix.m14 * SrcVector.w);
	Transformed.y = (SrcMatrix.m21 * SrcVector.x) + (SrcMatrix.m22 * SrcVector.y) + (SrcMatrix.m23 * SrcVector.z) + (SrcMatrix.m24 * SrcVector.w);
	Transformed.z = (SrcMatrix.m31 * SrcVector.x) + (SrcMatrix.m32 * SrcVector.y) + (SrcMatrix.m33 * SrcVector.z) + (SrcMatrix.m34 * SrcVector.w);
	Transformed.w = (SrcMatrix.m41 * SrcVector.x) + (SrcMatrix.m42 * SrcVector.y) + (SrcMatrix.m43 * SrcVector.z) + (SrcMatrix.m44 * SrcVector.w);

}
void XVecTransformNormalLH(XVECTOR3 & Normal, const XVECTOR3 & SrcVector, const XMATRIX44 &SrcMatrix)
{
	Normal.x = (SrcMatrix.m11 * SrcVector.x) + (SrcMatrix.m12 * SrcVector.y) + (SrcMatrix.m13 * SrcVector.z);
	Normal.y = (SrcMatrix.m21 * SrcVector.x) + (SrcMatrix.m22 * SrcVector.y) + (SrcMatrix.m23 * SrcVector.z);
	Normal.z = (SrcMatrix.m31 * SrcVector.x) + (SrcMatrix.m32 * SrcVector.y) + (SrcMatrix.m33 * SrcVector.z);
}
void XVecTransformRH(XVECTOR3 &Transformed, const XVECTOR3 &SrcVector, const XMATRIX44 &SrcMatrix)
{
	
	Transformed.x = (SrcMatrix.m11 * SrcVector.x) + (SrcMatrix.m12 * SrcVector.y) + (SrcMatrix.m13 * SrcVector.z) + (SrcMatrix.m14 * SrcVector.w);
	Transformed.y = (SrcMatrix.m21 * SrcVector.x) + (SrcMatrix.m22 * SrcVector.y) + (SrcMatrix.m23 * SrcVector.z) + (SrcMatrix.m24 * SrcVector.w);
	Transformed.z = -((SrcMatrix.m31 * SrcVector.x) + (SrcMatrix.m32 * SrcVector.y) + (SrcMatrix.m33 * SrcVector.z) + (SrcMatrix.m34 * SrcVector.w));
	Transformed.w = (SrcMatrix.m41 * SrcVector.x) + (SrcMatrix.m42 * SrcVector.y) + (SrcMatrix.m43 * SrcVector.z) + (SrcMatrix.m44 * SrcVector.w);
}
void XVecTransformNormalRH(XVECTOR3 &Normal, const XVECTOR3 &SrcVector, const XMATRIX44 &SrcMatrix)
{
	
	Normal.x = (SrcMatrix.m11 * SrcVector.x) + (SrcMatrix.m12 * SrcVector.y) + (SrcMatrix.m13 * SrcVector.z);
	Normal.y = (SrcMatrix.m21 * SrcVector.x) + (SrcMatrix.m22 * SrcVector.y) + (SrcMatrix.m23 * SrcVector.z);
	Normal.z = -((SrcMatrix.m31 * SrcVector.x) + (SrcMatrix.m32 * SrcVector.y) + (SrcMatrix.m33 * SrcVector.z));
}

void XVecDot(float & Dot, const XVECTOR3 & FirstV, const XVECTOR3 & SecondV)
{
	Dot = (FirstV.x * SecondV.x) + (FirstV.y * SecondV.y) + (FirstV.z * SecondV.z);
}
void XVecLength(float & Lenght, const XVECTOR3 &v)
{
	Lenght = sqrt((v.x* v.x)+ (v.y*v.y) + (v.z*v.z));
}
void XVecCross(XVECTOR3 & Cross, const XVECTOR3 &FirstV, const XVECTOR3 &SecondV)
{
	Cross.x = ((FirstV.y*SecondV.z) - (FirstV.z*SecondV.y)); 
	Cross.y = ((FirstV.z*SecondV.x) - (FirstV.x*SecondV.z));
	Cross.z = ((FirstV.x*SecondV.y) - (FirstV.y*SecondV.x));
}

void XVec3Normalize(XVECTOR3 & Normalized, const XVECTOR3 & ToNormalize)
{
	Normalized = ToNormalize;
	float v = sqrt((ToNormalize.x*ToNormalize.x) + (ToNormalize.y*ToNormalize.y) + (ToNormalize.z*ToNormalize.z));
	Normalized.x /= v; Normalized.y /= v; Normalized.z /= v;
}

////////////////////////////VECTOR2
XVECTOR2::operator float* ()
{
	return &x;
}
XVECTOR2::operator const float* () const
{
	return &x;
}

XVECTOR2& XVECTOR2:: operator+=(const XVECTOR2& other)
{
	this->x = this->x + other.x; this->y = this->y + other.y; return *this;
}
XVECTOR2& XVECTOR2::operator -= (const XVECTOR2& other)
{
	this->x = this->x - other.x; this->y = this->y - other.y; return *this;
}
XVECTOR2& XVECTOR2::operator *= (float times)
{
	this->x = this->x * times; this->y = this->y * times; return *this;
}
XVECTOR2& XVECTOR2::operator /= (float times)
{
	this->x = this->x / times; this->y = this->y / times; return *this;
}

XVECTOR2 XVECTOR2::operator + () const
{
	return *this;
}
XVECTOR2 XVECTOR2::operator - () const
{
	return XVECTOR2(-x, -y);
}

XVECTOR2 XVECTOR2::operator + (const XVECTOR2& other) const
{
	return XVECTOR2(x + other.x, y + other.y);
}
XVECTOR2 XVECTOR2::operator - (const XVECTOR2& other) const
{
	return XVECTOR2(x - other.x, y - other.y);
}
XVECTOR2 XVECTOR2::operator * (float times) const
{
	return XVECTOR2(x * times, y * times);
}
XVECTOR2 XVECTOR2::operator / (float times) const
{
	return XVECTOR2(x/times,y/times);
}

bool XVECTOR2::operator == (const XVECTOR2& other) const
{
	if (this->x==other.x&&this->y==other.y) return true;
	return false;
}
bool XVECTOR2::operator != (const XVECTOR2& other) const
{
	if (this->x != other.x&&this->y != other.y) return true;
	return false;
}
void XVECTOR2::Normalize()
{
	
	float v = sqrt((this->x * this->x)+ (this->y * this->y)); this->x = this->x / v; this->y = this->y / v;
}
float XVECTOR2::Length()
{
	return sqrt((this->x * this->x) + (this->y * this->y));
}
//////////////////VECTOR3
XVECTOR3::operator float* ()
{
	return &x;
}
XVECTOR3::operator const float* () const
{
	return &x;
}


XVECTOR3& XVECTOR3::operator += (const XVECTOR3& other)
{
	x = x + other.x; y = y + other.y; z = z + other.z; return *this;
}
XVECTOR3& XVECTOR3::operator -= (const XVECTOR3& other)
{
	x = x - other.x; y = y - other.y; z = z - other.z; return *this;

}
XVECTOR3& XVECTOR3::operator *= (float times)
{
	this->x = this->x * times; this->y = this->y * times; this->z = this->z * times; return *this;
}
XVECTOR3& XVECTOR3::operator /= (float times)
{
	this->x = this->x / times; this->y = this->y / times; this->z = this->z / times; return *this;

}

XVECTOR3 XVECTOR3::operator + () const
{
	return *this;
}
XVECTOR3 XVECTOR3::operator - () const
{
	return XVECTOR3(-x,-y,-z);
}

XVECTOR3 XVECTOR3::operator + (const XVECTOR3& other) const
{
	return XVECTOR3(x + other.x, y + other.y, z + other.z);
}

XVECTOR3 XVECTOR3::operator - (const XVECTOR3& other) const
{
	return XVECTOR3(x - other.x, y - other.y, z - other.z);
}
XVECTOR3 XVECTOR3::operator * (float times) const
{
	return XVECTOR3(x * times, y * times, z * times);
}
XVECTOR3 XVECTOR3::operator / (float times) const
{
	return XVECTOR3(x / times, y / times, z / times);
}

XVECTOR3 XVECTOR3::operator * (const XVECTOR3& other)
{
	this->x = this->x*other.x; this->y = this->y*other.y; this->z = this->z*other.z; return *this;
}


XVECTOR3 operator*(float times, const struct XVECTOR3 & other)
{
	return XVECTOR3(times*other.x,times*other.y,times*other.z);
}

bool XVECTOR3::operator == (const XVECTOR3& other) const
{
	if (this->x == other.x&&this->y == other.y&&this->z==other.z) return true;
	return false;
}
bool XVECTOR3::operator != (const XVECTOR3& other) const
{
	if (this->x != other.x&&this->y != other.y&&this->z != other.z) return true;
	return false;
}
void XVECTOR3::Normalize()
{
	float v = sqrt((this->x * this->x) + (this->y * this->y) + (this->z*this->z)); this->x = this->x / v; this->y = this->y / v; this->z = this->z / v;
}
float XVECTOR3::Length()
{
	return sqrt((this->x * this->x) + (this->y * this->y) + (this->z*this->z));
}

////////////MATRIX44

XMATRIX44_64::XMATRIX44_64()
{
	m11 = (double)0; m12 = (double)0; m13 = (double)0; m14 = (double)0;
	m21 = (double)0; m22 = (double)0; m23 = (double)0; m24 = (double)0;
	m31 = (double)0; m32 = (double)0; m33 = (double)0; m34 = (double)0;
	m41 = (double)0; m42 = (double)0; m43 = (double)0; m44 = (double)0;
}
XMATRIX44_64::XMATRIX44_64(XMATRIX44* i)
{
	m11 = (double)i->m11; m12 = (double)i->m12; m13 = (double)i->m13; m14 = (double)i->m14;
	m21 = (double)i->m21; m22 = (double)i->m22; m23 = (double)i->m23; m24 = (double)i->m24;
	m31 = (double)i->m31; m32 = (double)i->m32; m33 = (double)i->m33; m34 = (double)i->m34;
	m41 = (double)i->m41; m42 = (double)i->m42; m43 = (double)i->m43; m44 = (double)i->m44;


}

void XMATRIX44::Inverse(XMATRIX44 *o)
{
#if DOUBLE_FOR_INVERSE
	XMATRIX44_64 tmp64 = XMATRIX44_64(this);
	double det =
#else
	XMATRIX44 tmp64 = *this;
	float det =
#endif
		tmp64.m11*tmp64.m22*tmp64.m33*tmp64.m44 + tmp64.m11*tmp64.m23*tmp64.m34*tmp64.m42 + tmp64.m11*tmp64.m24*tmp64.m32*tmp64.m43
		+ tmp64.m12*tmp64.m21*tmp64.m34*tmp64.m43 + tmp64.m12*tmp64.m23*tmp64.m31*tmp64.m44 + tmp64.m12*tmp64.m24*tmp64.m33*tmp64.m41
		+ tmp64.m13*tmp64.m21*tmp64.m32*tmp64.m44 + tmp64.m13*tmp64.m22*tmp64.m34*tmp64.m41 + tmp64.m13*tmp64.m24*tmp64.m31*tmp64.m42
		+ tmp64.m14*tmp64.m21*tmp64.m33*tmp64.m42 + tmp64.m14*tmp64.m22*tmp64.m31*tmp64.m43 + tmp64.m14*tmp64.m23*tmp64.m32*tmp64.m41
		- tmp64.m11*tmp64.m22*tmp64.m34*tmp64.m43 - tmp64.m11*tmp64.m23*tmp64.m32*tmp64.m44 - tmp64.m11*tmp64.m24*tmp64.m33*tmp64.m42
		- tmp64.m12*tmp64.m21*tmp64.m33*tmp64.m44 - tmp64.m12*tmp64.m23*tmp64.m34*tmp64.m41 - tmp64.m12*tmp64.m24*tmp64.m31*tmp64.m43
		- tmp64.m13*tmp64.m21*tmp64.m34*tmp64.m42 - tmp64.m13*tmp64.m22*tmp64.m31*tmp64.m44 - tmp64.m13*tmp64.m24*tmp64.m32*tmp64.m41
		- tmp64.m14*tmp64.m21*tmp64.m32*tmp64.m43 - tmp64.m14*tmp64.m22*tmp64.m33*tmp64.m41 - tmp64.m14*tmp64.m23*tmp64.m31*tmp64.m42;
#if DOUBLE_FOR_INVERSE
	if (det == 0.0) {
#else
	if (det == 0.0f) {
#endif
		printf("\n\nThe Universe stopped, no det for Matrix, all ends here.\n\n");
		exit(666);
	}
#if DOUBLE_FOR_INVERSE
	det = 1.0 / det;
	XMATRIX44_64 out;
#else
	det = 1.0f / det;
	XMATRIX44 out;
#endif

	out.m11 = tmp64.m22*tmp64.m33*tmp64.m44 + tmp64.m23*tmp64.m34*tmp64.m42 + tmp64.m24*tmp64.m32*tmp64.m43 - tmp64.m22*tmp64.m34*tmp64.m43 - tmp64.m23*tmp64.m32*tmp64.m44 - tmp64.m24*tmp64.m33*tmp64.m42;
	out.m12 = tmp64.m12*tmp64.m34*tmp64.m43 + tmp64.m13*tmp64.m32*tmp64.m44 + tmp64.m14*tmp64.m33*tmp64.m42 - tmp64.m12*tmp64.m33*tmp64.m44 - tmp64.m13*tmp64.m34*tmp64.m42 - tmp64.m14*tmp64.m32*tmp64.m43;
	out.m13 = tmp64.m12*tmp64.m23*tmp64.m44 + tmp64.m13*tmp64.m24*tmp64.m42 + tmp64.m14*tmp64.m22*tmp64.m43 - tmp64.m12*tmp64.m24*tmp64.m43 - tmp64.m13*tmp64.m22*tmp64.m44 - tmp64.m14*tmp64.m23*tmp64.m42;
	out.m14 = tmp64.m12*tmp64.m24*tmp64.m33 + tmp64.m13*tmp64.m22*tmp64.m34 + tmp64.m14*tmp64.m23*tmp64.m32 - tmp64.m12*tmp64.m23*tmp64.m34 - tmp64.m13*tmp64.m24*tmp64.m32 - tmp64.m14*tmp64.m22*tmp64.m33;
	out.m21 = tmp64.m21*tmp64.m34*tmp64.m43 + tmp64.m23*tmp64.m31*tmp64.m44 + tmp64.m24*tmp64.m33*tmp64.m41 - tmp64.m21*tmp64.m33*tmp64.m44 - tmp64.m23*tmp64.m34*tmp64.m41 - tmp64.m24*tmp64.m31*tmp64.m43;
	out.m22 = tmp64.m11*tmp64.m33*tmp64.m44 + tmp64.m13*tmp64.m34*tmp64.m41 + tmp64.m14*tmp64.m31*tmp64.m43 - tmp64.m11*tmp64.m34*tmp64.m43 - tmp64.m13*tmp64.m31*tmp64.m44 - tmp64.m14*tmp64.m33*tmp64.m41;
	out.m23 = tmp64.m11*tmp64.m24*tmp64.m43 + tmp64.m13*tmp64.m21*tmp64.m44 + tmp64.m14*tmp64.m23*tmp64.m41 - tmp64.m11*tmp64.m23*tmp64.m44 - tmp64.m13*tmp64.m24*tmp64.m41 - tmp64.m14*tmp64.m21*tmp64.m43;
	out.m24 = tmp64.m11*tmp64.m23*tmp64.m34 + tmp64.m13*tmp64.m24*tmp64.m31 + tmp64.m14*tmp64.m21*tmp64.m33 - tmp64.m11*tmp64.m24*tmp64.m33 - tmp64.m13*tmp64.m21*tmp64.m34 - tmp64.m14*tmp64.m23*tmp64.m31;
	out.m31 = tmp64.m21*tmp64.m32*tmp64.m44 + tmp64.m22*tmp64.m34*tmp64.m41 + tmp64.m24*tmp64.m31*tmp64.m42 - tmp64.m21*tmp64.m34*tmp64.m42 - tmp64.m22*tmp64.m31*tmp64.m44 - tmp64.m24*tmp64.m32*tmp64.m41;
	out.m32 = tmp64.m11*tmp64.m34*tmp64.m42 + tmp64.m12*tmp64.m31*tmp64.m44 + tmp64.m14*tmp64.m32*tmp64.m41 - tmp64.m11*tmp64.m32*tmp64.m44 - tmp64.m12*tmp64.m34*tmp64.m41 - tmp64.m14*tmp64.m31*tmp64.m42;
	out.m33 = tmp64.m11*tmp64.m22*tmp64.m44 + tmp64.m12*tmp64.m24*tmp64.m41 + tmp64.m14*tmp64.m21*tmp64.m42 - tmp64.m11*tmp64.m24*tmp64.m42 - tmp64.m12*tmp64.m21*tmp64.m44 - tmp64.m14*tmp64.m22*tmp64.m41;
	out.m34 = tmp64.m11*tmp64.m24*tmp64.m32 + tmp64.m12*tmp64.m21*tmp64.m34 + tmp64.m14*tmp64.m22*tmp64.m31 - tmp64.m11*tmp64.m22*tmp64.m34 - tmp64.m12*tmp64.m24*tmp64.m31 - tmp64.m14*tmp64.m21*tmp64.m32;
	out.m41 = tmp64.m21*tmp64.m33*tmp64.m42 + tmp64.m22*tmp64.m31*tmp64.m43 + tmp64.m23*tmp64.m32*tmp64.m41 - tmp64.m21*tmp64.m32*tmp64.m43 - tmp64.m22*tmp64.m33*tmp64.m41 - tmp64.m23*tmp64.m31*tmp64.m42;
	out.m42 = tmp64.m11*tmp64.m32*tmp64.m43 + tmp64.m12*tmp64.m33*tmp64.m41 + tmp64.m13*tmp64.m31*tmp64.m42 - tmp64.m11*tmp64.m33*tmp64.m42 - tmp64.m12*tmp64.m31*tmp64.m43 - tmp64.m13*tmp64.m32*tmp64.m41;
	out.m43 = tmp64.m11*tmp64.m23*tmp64.m42 + tmp64.m12*tmp64.m21*tmp64.m43 + tmp64.m13*tmp64.m22*tmp64.m41 - tmp64.m11*tmp64.m22*tmp64.m43 - tmp64.m12*tmp64.m23*tmp64.m41 - tmp64.m13*tmp64.m21*tmp64.m42;
	out.m44 = tmp64.m11*tmp64.m22*tmp64.m33 + tmp64.m12*tmp64.m23*tmp64.m31 + tmp64.m13*tmp64.m21*tmp64.m32 - tmp64.m11*tmp64.m23*tmp64.m32 - tmp64.m12*tmp64.m21*tmp64.m33 - tmp64.m13*tmp64.m22*tmp64.m31;

	for (int i = 0; i < 16; i++) {
#if DOUBLE_FOR_INVERSE
		double val = det*out.mat[i];
		(*o).mat[i] = static_cast<float>(val);
#else
		(*o).mat[i] = det*out.mat[i];
#endif
	}
}
XMATRIX44& XMATRIX44::operator *= (const XMATRIX44& other)
{
	XMATRIX44 alfa;
	alfa.m11 = (m11*other.m11 + m12*other.m21 + m13*other.m31 + m14*other.m41);
	alfa.m12 = (m11*other.m12 + m12*other.m22 + m13*other.m32 + m14*other.m42);
	alfa.m13 = (m11*other.m13 + m12*other.m23 + m13*other.m33 + m14*other.m43);
	alfa.m14 = (m11*other.m14 + m12*other.m24 + m13*other.m34 + m14*other.m44);

	alfa.m21 = (m21*other.m11 + m22*other.m21 + m23*other.m31 + m24*other.m41);
	alfa.m22 = (m21*other.m12 + m22*other.m22 + m23*other.m32 + m24*other.m42);
	alfa.m23 = (m21*other.m13 + m22*other.m23 + m23*other.m33 + m24*other.m43);
	alfa.m24 = (m21*other.m14 + m22*other.m24 + m23*other.m34 + m24*other.m44);

	alfa.m31 = (m31*other.m11 + m32*other.m21 + m33*other.m31 + m34*other.m41);
	alfa.m32 = (m31*other.m12 + m32*other.m22 + m33*other.m32 + m34*other.m42);
	alfa.m33 = (m31*other.m13 + m32*other.m23 + m33*other.m33 + m34*other.m43);
	alfa.m34 = (m31*other.m14 + m32*other.m24 + m33*other.m34 + m34*other.m44);

	alfa.m41 = (m41*other.m11 + m42*other.m21 + m43*other.m31 + m44*other.m41);
	alfa.m42 = (m41*other.m12 + m42*other.m22 + m43*other.m32 + m44*other.m42);
	alfa.m43 = (m41*other.m13 + m42*other.m23 + m43*other.m33 + m44*other.m43);
	alfa.m44 = (m41*other.m14 + m42*other.m24 + m43*other.m34 + m44*other.m44);
	*this = alfa;
	return *this;

}
XMATRIX44& XMATRIX44::operator += (const XMATRIX44& other)
{
	m11 = m11 + other.m11; m12 = m12 + other.m12; m13 = m13 + other.m13; m14 = m14 + other.m14;
	m21 = m21 + other.m21; m22 = m22 + other.m22; m23 = m23 + other.m23; m24 = m24 + other.m24;
	m31 = m31 + other.m31; m32 = m32 + other.m32; m33 = m33 + other.m33; m34 = m34 + other.m34;
	m41 = m41 + other.m41; m42 = m42 + other.m42; m43 = m43 + other.m43; m44 = m44 + other.m44;
	return *this;
}
XMATRIX44& XMATRIX44::operator -= (const XMATRIX44& other)
{
	m11 = m11 - other.m11; m12 = m12 - other.m12; m13 = m13 - other.m13; m14 = m14 - other.m14;
	m21 = m21 - other.m21; m22 = m22 - other.m22; m23 = m23 - other.m23; m24 = m24 - other.m24;
	m31 = m31 - other.m31; m32 = m32 - other.m32; m33 = m33 - other.m33; m34 = m34 - other.m34;
	m41 = m41 - other.m41; m42 = m42 - other.m42; m43 = m43 - other.m43; m44 = m44 - other.m44;
	return *this;
}
XMATRIX44& XMATRIX44::operator *= (float times)
{
	m11 = m11 * times; m12 = m12 * times; m13 = m13 * times; m14 = m14 * times;
	m21 = m21 * times; m22 = m22 * times; m23 = m23 * times; m24 = m24 * times;
	m31 = m31 * times; m32 = m32 * times; m33 = m33 * times; m34 = m34 * times;
	m41 = m41 * times; m42 = m42 * times; m43 = m43 * times; m44 = m44 * times;
	return *this;
}
XMATRIX44& XMATRIX44::operator /= (float times)
{
	m11 = m11 / times; m12 = m12 / times; m13 = m13 / times; m14 = m14 / times;
	m21 = m21 / times; m22 = m22 / times; m23 = m23 / times; m24 = m24 / times;
	m31 = m31 / times; m32 = m32 / times; m33 = m33 / times; m34 = m34 / times;
	m41 = m41 / times; m42 = m42 / times; m43 = m43 / times; m44 = m44 / times;
	return *this;
}

XMATRIX44 XMATRIX44::operator + () const
{
	return *this;
}
XMATRIX44 XMATRIX44::operator - () const
{
	return XMATRIX44(
		-m11, -m12, -m13, -m14, 
		-m21, -m22, -m23, -m24, 
		-m31, -m32, -m33, -m34, 
		-m41, -m42, -m43, -m44);
}

XMATRIX44::operator float*()
{
	return  &m11;
}
XMATRIX44::operator const float* () const
{
	return  &m11;
}

XMATRIX44 XMATRIX44::operator * (const XMATRIX44& other) const
{
	XMATRIX44 alfa;
	alfa.m11 = (m11*other.m11 + m12*other.m21 + m13*other.m31 + m14*other.m41);
	alfa.m12 = (m11*other.m12 + m12*other.m22 + m13*other.m32 + m14*other.m42);
	alfa.m13 = (m11*other.m13 + m12*other.m23 + m13*other.m33 + m14*other.m43);
	alfa.m14 = (m11*other.m14 + m12*other.m24 + m13*other.m34 + m14*other.m44);

	alfa.m21 = (m21*other.m11 + m22*other.m21 + m23*other.m31 + m24*other.m41);
	alfa.m22 = (m21*other.m12 + m22*other.m22 + m23*other.m32 + m24*other.m42);
	alfa.m23 = (m21*other.m13 + m22*other.m23 + m23*other.m33 + m24*other.m43);
	alfa.m24 = (m21*other.m14 + m22*other.m24 + m23*other.m34 + m24*other.m44);

	alfa.m31 = (m31*other.m11 + m32*other.m21 + m33*other.m31 + m34*other.m41);
	alfa.m32 = (m31*other.m12 + m32*other.m22 + m33*other.m32 + m34*other.m42);
	alfa.m33 = (m31*other.m13 + m32*other.m23 + m33*other.m33 + m34*other.m43);
	alfa.m34 = (m31*other.m14 + m32*other.m24 + m33*other.m34 + m34*other.m44);

	alfa.m41 = (m41*other.m11 + m42*other.m21 + m43*other.m31 + m44*other.m41);
	alfa.m42 = (m41*other.m12 + m42*other.m22 + m43*other.m32 + m44*other.m42);
	alfa.m43 = (m41*other.m13 + m42*other.m23 + m43*other.m33 + m44*other.m43);
	alfa.m44 = (m41*other.m14 + m42*other.m24 + m43*other.m34 + m44*other.m44);
	return alfa;
}
XMATRIX44 XMATRIX44::operator + (const XMATRIX44& other) const
{
	return XMATRIX44(
		m11+other.m11, m12 + other.m12,m13 + other.m13,m14 + other.m14,
		m21+other.m21, m22 + other.m22,m23 + other.m23,m24 + other.m24,
		m31+other.m31, m32 + other.m32,m33 + other.m33,m34 + other.m34,
		m41+other.m41, m42 + other.m42,m43 + other.m43,m44 + other.m44);
}
XMATRIX44 XMATRIX44::operator - (const XMATRIX44& other) const
{
	return XMATRIX44(
		m11- other.m11, m12- other.m12, m13- other.m13, m14- other.m14,
		m21 -other.m21, m22 -other.m22, m23 -other.m23, m24 -other.m24,
		m31 -other.m31, m32 -other.m32, m33 -other.m33, m34 -other.m34,
		m41 -other.m41, m42 -other.m42, m43 -other.m43, m44 -other.m44);
}
XMATRIX44 XMATRIX44::operator * (float times) const
{
	return XMATRIX44(
		m11* times, m12 * times, m13* times, m14* times,
		m21 * times, m22 * times, m23* times, m24* times,
		m31 * times, m32 * times, m33* times, m34* times,
		m41 * times, m42 * times, m43* times, m44* times);
}
XMATRIX44 XMATRIX44::operator / (float times) const
{
	return XMATRIX44(
		m11/ times, m12 / times, m13/ times, m14/ times,
		m21 / times, m22 / times, m23/ times, m24/ times,
		m31 / times, m32 / times, m33/ times, m34/ times,
		m41 / times, m42 / times, m43/ times, m44/ times);
}

XMATRIX44 operator * (float times, const XMATRIX44& other)
{
	return XMATRIX44(
		other.m11 * times, other.m12 * times, other.m13 * times, other.m14 * times,
		other.m21 * times, other.m22 * times, other.m23 * times, other.m24 * times,
		other.m31 * times, other.m32 * times, other.m33 * times, other.m34 * times,
		other.m41 * times, other.m42 * times, other.m43 * times, other.m44 * times
	);
}

bool XMATRIX44::operator == (const XMATRIX44& other) const
{
	if (
	m11 == other.m11 && m12 == other.m12 && m13 == other.m13 && m14 == other.m14 &&
	m21 == other.m21 && m22 == other.m22 && m23 == other.m23 && m24 == other.m24 &&
	m31 == other.m31 && m32 == other.m32 && m33 == other.m33 && m34 == other.m34 &&
	m41 == other.m41 && m42 == other.m42 && m43 == other.m43 && m44 == other.m44
	)return true;
	return false;
}
bool XMATRIX44::operator != (const XMATRIX44& other) const
{
	if (
		m11 != other.m11 && m12 != other.m12 && m13 != other.m13 && m14 != other.m14 &&
		m21 != other.m21 && m22 != other.m22 && m23 != other.m23 && m24 != other.m24 &&
		m31 != other.m31 && m32 != other.m32 && m33 != other.m33 && m34 != other.m34 &&
		m41 != other.m41 && m42 != other.m42 && m43 != other.m43 && m44 != other.m44
		)return true;
	return false;
}

