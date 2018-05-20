#pragma once
#include <IDVMath.h>
class Boid2D
{
private:
	std::vector<Boid2D> totalAgents;
	float fAgentNeighborRadius;
public:
	XVECTOR2 vPosition, vFront, vRight, vVelocity;
	float fMagnitude, fInnerRadio, fOuterRadio;
public:
	Boid2D();
	Boid2D(float x, float y, float iradio, float oradio, float mag);
	~Boid2D();
	void SetRight();
	XVECTOR2
		Flee(XVECTOR2 vObjective),
		Seek(XVECTOR2 vObjective),
		Avoid(XVECTOR2 vObjective, XVECTOR2 vObjectiveDirection, XVECTOR2 vObjectiveVelocity, float fTimeOffset),
		Pursue(XVECTOR2 vObjective, XVECTOR2 vObjectiveDirection, XVECTOR2 vObjectiveVelocity, float fTimeOffset),
		Arrive(XVECTOR2 vObjective),
		Leave(XVECTOR2 vObjective),
		Wander(XVECTOR2 vObjective, float fVisionAngle),
		Flock(),
		Cohesion(),
		Direction(),
		Distance(),
		ObstacleAvoidance();

};
Boid2D::Boid2D()
{

}
Boid2D::Boid2D(float x, float y,float iradio,float oradio,float mag)
{
	vPosition.x = x;
	vPosition.y = y;
	fMagnitude = mag;
	fInnerRadio = iradio;
	fOuterRadio = oradio;
	vRight.x = +vPosition.y;
	vRight.y = -vPosition.x;
}
Boid2D::~Boid2D()
{

}
void Boid2D::SetRight()
{
	vRight.x = +vPosition.y;
	vRight.y = -vPosition.x;
}
XVECTOR2 Boid2D::Seek(XVECTOR2 vObjective)
{
	XVECTOR2 vForce = vObjective - vPosition;
	vForce.Normalize();
	vForce *= fMagnitude;
	return vForce;

}
XVECTOR2 Boid2D::Flee(XVECTOR2 vObjective)
{
	XVECTOR2 vForce = vPosition - vObjective;
	vForce.Normalize();
	vForce *= fMagnitude;
	return vForce;
}
XVECTOR2 Boid2D::Avoid(XVECTOR2 vObjective, XVECTOR2 vObjectiveDirection, XVECTOR2 vObjectiveVelocity, float fTimeOffset)
{
	float fObjectiveAngle = XVEC2Angle(vObjective);
	XVECTOR2 vPredictPosition = vObjective + vObjectiveVelocity * fTimeOffset;
	while ((vPosition - vObjective).Length() <= vPredictPosition.Length())
	{
		fTimeOffset--;
		XVECTOR2 vPredictPosition = vObjective + vObjectiveVelocity * fTimeOffset;
	}
	return Leave(vPredictPosition);
}
XVECTOR2 Boid2D::Pursue(XVECTOR2 vObjective, XVECTOR2 vObjectiveDirection, XVECTOR2 vObjectiveVelocity, float fTimeOffset)
{
	float fObjectiveAngle = XVEC2Angle(vObjective);
	XVECTOR2 vPredictPosition = vObjective + vObjectiveVelocity * fTimeOffset;
	while ((vPosition - vObjective).Length() <= vPredictPosition.Length())
	{
		fTimeOffset--;
		XVECTOR2 vPredictPosition = vObjective + vObjectiveVelocity * fTimeOffset;
	}
	return Seek(vPredictPosition);
}
XVECTOR2 Boid2D::Arrive(XVECTOR2 vObjective)
{
	XVECTOR2 vForce = Seek(vObjective);
	float scale = 0.0f;
	float distance = (vObjective - vPosition).Length();
	scale = Minimum((distance / fInnerRadio), 1.0f);
	return vForce*scale;
}
XVECTOR2 Boid2D::Leave(XVECTOR2 vObjective)
{
	XVECTOR2 vForce = Flee(vObjective);
	float scale = 1.0f;
	if ((vPosition - vObjective).Length() >= fInnerRadio)
	{
		float distance = (vObjective - vPosition).Length() - fInnerRadio;
		distance = fOuterRadio - distance;
		scale = Minimum((distance / fOuterRadio), 1.0f);
		if (scale <= .001f)
			scale = 0;
	}
}
XVECTOR2 Boid2D::Wander(XVECTOR2 vObjective, float fVisionAngle)
{
	float fCircleOffset = 10;
	//The angle of difference between our front and world axis
	float fObjectAngle = XVEC2Angle(vPosition);
	//The center of our projected circle. Is in front of the object
	XVECTOR2 vCircleCenter = { (cos(fObjectAngle)*fCircleOffset) + vPosition.x,(sin(fObjectAngle)*fCircleOffset) + vPosition.y };
	float fRandomAngle = RandomRange(fObjectAngle - (fVisionAngle / 2.0f), fObjectAngle + (fVisionAngle / 2.0f), 1234.0f);
	XVECTOR2 vRandomObjective = { cos(fRandomAngle),sin(fRandomAngle) };
	return Seek(vRandomObjective);
}
XVECTOR2 Boid2D::Flock()
{
	XVECTOR2 vFlock = Cohesion() + Direction() + Distance();
	return vFlock;
}
XVECTOR2 Boid2D::Cohesion()
{
	XVECTOR2 vGeneralPosition,vToCenter;
	int iNeighborAgents = 0;
	for each(Boid2D agent in totalAgents)
	{
		if ((agent.vPosition - vPosition).Length() != 0 && (agent.vPosition - vPosition).Length() < fAgentNeighborRadius)
		{
			vGeneralPosition += agent.vPosition;
			++iNeighborAgents;
		}
	}
	if (iNeighborAgents != 0)
	{
		vGeneralPosition /= iNeighborAgents;
		vToCenter = { vGeneralPosition - vPosition };
		vToCenter.Normalize();
	}
	return vToCenter;
}
XVECTOR2 Boid2D::Direction()
{
	XVECTOR2 vGeneralDirection;
	int iNeighborAgents = 0;
	for each(Boid2D agent in totalAgents)
	{
		if ((agent.vPosition - vPosition).Length() != 0 && (agent.vPosition - vPosition).Length() < fAgentNeighborRadius)
		{
			vGeneralDirection += agent.vFront;
			++iNeighborAgents;
		}
	}
	if (iNeighborAgents != 0)
	{
		vGeneralDirection /= iNeighborAgents;
		vGeneralDirection.Normalize();
	}
	return vGeneralDirection;
}
XVECTOR2 Boid2D::Distance()
{
	int iNeighborAgents = 0;
	XVECTOR2 vGeneralAvoidance;
	for each(Boid2D agent in totalAgents)
	{
		if ((agent.vPosition - vPosition).Length() != 0 && (agent.vPosition - vPosition).Length() < fAgentNeighborRadius)
		{
			vGeneralAvoidance += (agent.vPosition - vPosition);
			++iNeighborAgents;
		}
	}
	if (iNeighborAgents != 0)
	{
		vGeneralAvoidance /= iNeighborAgents;
		vGeneralAvoidance *= -1;
		vGeneralAvoidance.Normalize();
	}
	return vGeneralAvoidance;
}
XVECTOR2 Boid2D::ObstacleAvoidance()
{
	//Define the boundaries of our BoxCollider
	float fLeftNear, fLeftFar, fRightNear, fRightFar;

	return XVECTOR2() = {};
}