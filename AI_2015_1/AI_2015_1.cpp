/*///////////////////////////
|	Steering Behaviors		|
|	UAD 6th QUAD			|
|	For educational purposes|
///////////////////////////*/
#include "stdafx.h"
#include <IDVMath.h>
int main()
{
    return 0;
}
XVECTOR3 Wander()
{
	//Wander Makes the object Follow a random point created in a radius in front of it
}
XVECTOR3 Pursuit()
{

}
XVECTOR3 Evade()
{

}
XVECTOR3 Arrive(XVECTOR3 vPosition, XVECTOR3 vObjective, float fMagnitude, float innerradio, float outerradio)
{
	XVECTOR3 vForce = Seek(vPosition, vObjective, fMagnitude);
	float scale = 0.0f;
	float distance = (vObjective - vPosition).Length();
	scale = Minimum((distance / innerradio), 1.0f);
	return vForce*scale; 
}
XVECTOR3 Seek(XVECTOR3 vPosition, XVECTOR3 vObjective, float fMagnitude)
{
	XVECTOR3 vForce = vObjective - vPosition;
	vForce.Normalize();
	vForce *= fMagnitude;
	return vForce;
}
XVECTOR3 Leave(XVECTOR3 vPosition, XVECTOR3 vObjective, float fMagnitude, float innerradio, float outerradio)
{
	XVECTOR3 vForce = Flee(vPosition, vObjective, fMagnitude);
	float scale = 1.0f;
	if ((vPosition-vObjective).Length()>=innerradio)
	{
		float distance = (vObjective - vPosition).Length() - innerradio;
		distance = outerradio - distance;
		scale = Minimum((distance / outerradio), 1.0f);
		if (scale <= .001f)
			scale = 0;
	}
}

XVECTOR3 Flee(XVECTOR3 vPosition, XVECTOR3 vObjective, float fMagnitude)
{
	XVECTOR3 vForce = vPosition - vObjective;
	vForce.Normalize();
	vForce *= fMagnitude;
	return vForce;
}
void Turn()
{

}
