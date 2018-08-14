#pragma once
#include "Utilities.h"
#include "Connection.h"
class Triangle
{
public:
	XVECTOR2 m_va, m_vb, m_vc;
	Connection m_c1, m_c2, m_c3;
	Triangle();
	~Triangle();
};

