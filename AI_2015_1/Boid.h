#pragma once
#include <IDVMath.h>
#include "GameObject.h"
class Boid2D : GameObject
{
private:
	std::vector<Boid2D> totalAgents;
	std::vector<GameObject> totalObstacles;
	float fAgentNeighborRadius;
	int ID;
public:
	XVECTOR2 
		vFront, vRight, vVelocity, vWander;
	float
		fMagnitude, 
		fInnerRadio, fOuterRadio, fRadio, 
		fPushForce, 
		avoidTime = 5.0f, pursueTime = 5.0f, wanderTime = 0.0f;
public:
	Boid2D(std::string t);
	Boid2D(std::string t, float x, float y, float iradio, float oradio, float mag);
	~Boid2D();
	void SetRight();
	void SetID(int id);
	void Update();
	void GetBox(std::vector<XVECTOR2> b, std::vector<XVECTOR2> c);
	XVECTOR2
		Flee(XVECTOR2 vObjective),
		Seek(XVECTOR2 vObjective),
		Avoid(XVECTOR2 vObjective, XVECTOR2 vObjectiveDirection, XVECTOR2 vObjectiveVelocity),
		Pursue(XVECTOR2 vObjective, XVECTOR2 vObjectiveDirection, XVECTOR2 vObjectiveVelocity),
		Arrive(XVECTOR2 vObjective),
		Leave(XVECTOR2 vObjective),
		Wander(XVECTOR2 vObjective, float fVisionAngle),
		Flock(),
		Cohesion(),
		Direction(),
		Distance(),
		ObstacleAvoidance(),
		SurroundEnemies(XVECTOR2 objPos, float radius),
		CheckBoundaries(XVECTOR2 side, XVECTOR2 vecToObstacle, XVECTOR2 obsPosition, XVECTOR2 corner, float dotfactor, float boundary);
};

Boid2D::Boid2D(std::string t)
{
	//the agent should be added to the total agents vector in the scene
	m_tag = t;
}

Boid2D::Boid2D(std::string t, float x, float y,float iradio,float oradio,float mag)
{
	m_tag = t;
	m_position2d.x = x;
	m_position2d.y = y;
	fMagnitude = mag;
	fInnerRadio = iradio;
	fOuterRadio = oradio;
	vRight.x = +m_position2d.y;
	vRight.y = -m_position2d.x;
	fPushForce = 100;
}

Boid2D::~Boid2D()
{
	totalObstacles.clear();
	totalAgents.clear();

}
void Boid2D::SetRight()
{
	vRight.x = +m_position2d.y;
	vRight.y = -m_position2d.x;
	vRight.Normalize();
}
void Boid2D::Update()
{
	vVelocity;
}
XVECTOR2 Boid2D::Seek(XVECTOR2 vObjective)
{
	XVECTOR2 vForce = vObjective - m_position2d;
	vForce.Normalize();
	vForce *= fMagnitude;
	return vForce;

}

XVECTOR2 Boid2D::Flee(XVECTOR2 vObjective)
{
	XVECTOR2 vForce = m_position2d - vObjective;
	vForce.Normalize();
	vForce *= fMagnitude;
	return vForce;
}

XVECTOR2 Boid2D::Avoid(XVECTOR2 vObjective, XVECTOR2 vObjectiveDirection, XVECTOR2 vObjectiveVelocity)
{
	XVECTOR2 vPredictPosition = vObjective + vObjectiveVelocity * avoidTime;
	if ((m_position2d - vObjective).Length() <= vPredictPosition.Length())
	{
		avoidTime = (m_position2d - vObjective).Length();
		vPredictPosition = vObjective + vObjectiveVelocity * avoidTime;
	}
	else avoidTime = 5.0f;
	return Leave(vPredictPosition);
}

XVECTOR2 Boid2D::Pursue(XVECTOR2 vObjective, XVECTOR2 vObjectiveDirection, XVECTOR2 vObjectiveVelocity)
{
	XVECTOR2 vPredictPosition = vObjective + (vObjectiveVelocity * pursueTime);
	if ((m_position2d - vObjective).Length() <= vPredictPosition.Length())
	{
		pursueTime = (m_position2d - vObjective).Length();
		vPredictPosition = vObjective + (vObjectiveVelocity * pursueTime);
	}
	else pursueTime = 5.0f;
	return Seek(vPredictPosition);
}

XVECTOR2 Boid2D::Arrive(XVECTOR2 vObjective)
{
	XVECTOR2 vForce = Seek(vObjective);
	float scale = 0.0f;
	float distance = (vObjective - m_position2d).Length();
	scale = Minimum((distance / fInnerRadio), 1.0f);
	return vForce*scale;
}

XVECTOR2 Boid2D::Leave(XVECTOR2 vObjective)
{
	XVECTOR2 vForce = Flee(vObjective);
	float scale = 1.0f;
	if ((m_position2d - vObjective).Length() >= fInnerRadio)
	{
		float distance = (vObjective - m_position2d).Length() - fInnerRadio;
		distance = fOuterRadio - distance;
		scale = Minimum((distance / fOuterRadio), 1.0f);
		if (scale <= .001f)
			scale = 0;
	}
	return vForce * scale;
}

XVECTOR2 Boid2D::Wander(XVECTOR2 vObjective, float fVisionAngle)
{
	float fCircleOffset = 10.0f;
	fVisionAngle = 0.5f;
	//The angle of difference between our front and world axis
	float fWorldAngle = XVEC2Angle(m_position2d);
	//The center of our projected circle. Is in front of the object
	XVECTOR2 vCircleCenter =
	{ cos(fWorldAngle)*fCircleOffset, sin(fWorldAngle)*fCircleOffset };
	vCircleCenter += m_position2d;
	//Create a random angle between the world angle += vision
	float fRandomAngle = RandomRange(fWorldAngle - fVisionAngle, fWorldAngle + fVisionAngle, 1234.0f);
	//Creates the final point taking the circle center in front of us
	XVECTOR2 vRandomObjective =
	{ cos(fRandomAngle)*2.0f, sin(fRandomAngle)*2.0f };
	vRandomObjective += vCircleCenter;
	return Seek(vRandomObjective);
}

XVECTOR2 Boid2D::Flock()
{
	return  (Cohesion() + Direction() + Distance()).normalized()*fMagnitude;
}

XVECTOR2 Boid2D::Cohesion()
{
	GetList(totalAgents);
	XVECTOR2 vGeneralPosition = { 0,0 }, vToCenter = { 0,0 };
	int iNeighborAgents = 0;
	for each(Boid2D agent in totalAgents)
	{
		if ((agent.m_position2d - m_position2d).Length() != 0 && 
			(agent.m_position2d - m_position2d).Length() < fAgentNeighborRadius)
		{
			vGeneralPosition += agent.m_position2d;
			++iNeighborAgents;
		}
	}
	if (iNeighborAgents != 0)
	{
		vGeneralPosition /= iNeighborAgents;
		vToCenter = { vGeneralPosition - m_position2d };
		vToCenter.Normalize();
	}
	return vToCenter;
}

XVECTOR2 Boid2D::Direction()
{
	GetList(totalAgents);
	XVECTOR2 vGeneralDirection = { 0,0 };
	int iNeighborAgents = 0;
	for each(Boid2D agent in totalAgents)
	{
		if ((agent.m_position2d - m_position2d).Length() != 0 && (agent.m_position2d - m_position2d).Length() < fAgentNeighborRadius)
		{
			vGeneralDirection += agent.vFront;
			++iNeighborAgents;
		}
	}
	if (iNeighborAgents != 0)
	{
		vGeneralDirection /= iNeighborAgents;
		vGeneralDirection.Normalize();
		vGeneralDirection *= fMagnitude;
	}
	return vGeneralDirection;
}

XVECTOR2 Boid2D::Distance()
{
	GetList(totalAgents);
	int iNeighborAgents = 0;
	XVECTOR2 vGeneralAvoidance = { 0,0 };
	for each(Boid2D agent in totalAgents)
	{
		if ((agent.m_position2d - m_position2d).Length() != 0 && 
			(agent.m_position2d - m_position2d).Length() < fAgentNeighborRadius)
		{
			vGeneralAvoidance += (agent.m_position2d - m_position2d);
			++iNeighborAgents;
		}
	}
	if (iNeighborAgents != 0)
	{
		vGeneralAvoidance /= iNeighborAgents;
		vGeneralAvoidance *= -1;
		vGeneralAvoidance.Normalize();
		vGeneralAvoidance *= fMagnitude*2.0f;
	}
	return vGeneralAvoidance;
}
void Boid2D::GetBox(std::vector<XVECTOR2> b, std::vector<XVECTOR2> c)
{
	float fFrontOffset = 5.0f, fBackOffset = boundary;
	//Boundaries of our BoxCollider
	XVECTOR2 fLeftNear, fLeftFar, fRightNear, fRightFar;
	fLeftFar = m_position2d + vFront*fFrontOffset - vRight;
	fRightFar = m_position2d + vFront*fFrontOffset + vRight;
	fLeftNear = m_position2d - vFront*fBackOffset - vRight;
	fRightNear = m_position2d - vFront*fBackOffset + vRight;
	//Define the VectorBox
	XVECTOR2 vA, vB, vC, vD;
	vA = fRightFar - fLeftFar;
	vB = fLeftFar - fLeftNear;
	vC = fLeftNear - fRightNear;
	vD = fRightNear - fRightFar;
	b.push_back(vA); b.push_back(vB); b.push_back(vC); b.push_back(vD);
	c.push_back(fLeftFar); c.push_back(fLeftNear); c.push_back(fRightNear); c.push_back(fRightFar);
	//Make a dot product to see if an object is inside the boundaries
}
XVECTOR2 Boid2D::ObstacleAvoidance()
{
	GetList(totalObstacles);
	std::vector<XVECTOR2> Box;
	std::vector<XVECTOR2> Corners;
	GetBox(Box, Corners);
	
	XVECTOR2 vBackForce;
	//Define the positions
	
	for each(GameObject obstacle in totalObstacles)
	{
		if ((m_position2d - obstacle.m_position2d).Length() <= 10)
		{
			//XVECTOR2 A, B, C, D;
			//float fa, fb, fc, fd;
			float obs_bounds= obstacle.boundary;
			for (int i = 0; i < 4; ++i)
			{
				XVECTOR2 shoot = obstacle.m_position2d - Corners[i];
				float dot = XVEC2Dot(shoot, Box[i]) / (Box[i].Length()  * Box[i].Length());
				vBackForce += CheckBoundaries(Box[i], shoot, obstacle.m_position2d, Box[i], dot, obs_bounds);
			}
			//A = obstacle.m_position2d - fLeftFar;
			//B = obstacle.m_position2d - fLeftNear;
			//C = obstacle.m_position2d - fRightNear;
			//D = obstacle.m_position2d - fRightFar;
			//fa = XVEC2Dot(A, vA) / (vA.Length()  * vA.Length());
			//fb = XVEC2Dot(B, vB) / (vB.Length()  * vB.Length());
			//fc = XVEC2Dot(C, vC) / (vC.Length()  * vC.Length());
			//fd = XVEC2Dot(D, vD) / (vD.Length()  * vD.Length());
			//vBackForce += CheckBoundaries(vA, A, obstacle.m_position2d, fLeftFar, fa, obs_bounds);
			//vBackForce += CheckBoundaries(vB, B, obstacle.m_position2d, fLeftNear, fb, obs_bounds);
			//vBackForce += CheckBoundaries(vC, C, obstacle.m_position2d, fRightNear, fc, obs_bounds);
			//vBackForce += CheckBoundaries(vD, D, obstacle.m_position2d, fRightFar, fd, obs_bounds);
		}
		
	}
	return vBackForce;

}
void Boid2D::SetID(int id)
{
	ID = id;
}
XVECTOR2 Boid2D::CheckBoundaries(XVECTOR2 side, XVECTOR2 vecToObstacle, XVECTOR2 obsPosition, XVECTOR2 corner, float dotfactor, float boundary)
{
	XVECTOR2 result = { 0,0 };
	if (dotfactor > 0 && dotfactor < 1)
	{
		XVECTOR2 reason = side * dotfactor;
		XVECTOR2 backforce = reason - vecToObstacle;
		//Now we check via heuristics if we are accepting the object is inside our vector box
		if (backforce.Length() <= (boundary) / 2)
		{
			//Object is in fact inside our box
			backforce.Normalize();
			//That 4 is just heuristics that worked in unity, might be different in OpenGL
			result = backforce * fMagnitude * 4;
		}
	}
	return result;
}
XVECTOR2 Boid2D::SurroundEnemies(XVECTOR2 objPos, float radius)
{
	XVECTOR2 vForce = {0,0};
	GetList(totalAgents);
	XVECTOR2 vV = m_position2d - objPos;
	XVECTOR2 vW = vV.normalized() * 10.0f;
	XVECTOR2 vPoint = vW - vV + m_position2d;
	vForce += Arrive(vPoint);

	for each(Boid2D agent in totalAgents)
	{
		XVECTOR2 difference = (agent.m_position2d - m_position2d);
		if (difference.Length() != 0 &&
			difference.Length() <= 3.0f)
		{
			XVECTOR2 frontPoint = m_position2d + (vFront * 3.0f);
			XVECTOR2 front = frontPoint - m_position2d;

			if ((XVEC2Dot(difference, front) / (front.Length()*front.Length())) > .25f &&
				(XVEC2Dot(difference, front) / (front.Length()*front.Length())) < 2.0f)
			{
				vForce += /*Quaternion.AngleAxis(innervalue*90.0f, transform.up) **/ Leave(vPoint) * 2;
			}
		}
	}
	if ((vPoint - m_position2d).Length() <= .5f) return XVECTOR2{0,0};
	return vForce;
}