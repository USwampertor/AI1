#pragma once
#include "GameObject.h"
class Boid2D : public GameObject
{
private:
	std::vector<Boid2D*> totalAgents;
	std::vector<GameObject*> totalObstacles;
	float fAgentNeighborRadius;
	int ID;
public:
	XVECTOR2 
		vFront, vRight, vVelocity, vWander, m_EnemyPosition;
	float
		fMagnitude, 
		fInnerRadio, fOuterRadio, fRadio, 
		fPushForce, 
		avoidTime = 5.0f, pursueTime = 5.0f, wanderTime = 0.0f;
public:
	sf::CircleShape m_body;
	Boid2D();
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
		Wander(float fVisionAngle),
		Flock(),
		Cohesion(),
		Direction(),
		Distance(),
		ObstacleAvoidance(),
		SurroundEnemies(XVECTOR2 objPos, float radius),
		CheckBoundaries(XVECTOR2 side, XVECTOR2 vecToObstacle, XVECTOR2 obsPosition, XVECTOR2 corner, float dotfactor, float boundary);
	void GetList()
	{

	}

};
