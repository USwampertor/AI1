using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : Boid {
    float m_playerVelocity = .015f;
    float MAX_VELOCITY = 1.0f;
	// Use this for initialization
	void Start () {
        vLastForce = new Vector3();
    }
	
	// Update is called once per frame
	void Update () {
        Vector3 actualForce = vLastForce;
        if (Input.GetKey(KeyCode.W))
        {
            actualForce += transform.forward * m_playerVelocity;
        }
        if (Input.GetKey(KeyCode.S))
        {
            actualForce -= transform.forward * m_playerVelocity;
        }
        if (Input.GetKey(KeyCode.A))
        {
            actualForce -= transform.right * m_playerVelocity;
        }
        if (Input.GetKey(KeyCode.D))
        {
            actualForce += transform.right * m_playerVelocity;
        }
        if(actualForce.z >= MAX_VELOCITY)
        {
            actualForce.z = MAX_VELOCITY;
        }
        if (actualForce.z <= -MAX_VELOCITY)
        {
            actualForce.z = -MAX_VELOCITY;
        }
        actualForce *= 0.96521f;
        transform.Translate(actualForce);
        vLastForce = actualForce;
        transform.rotation = Quaternion.LookRotation((actualForce).normalized, transform.up);
    }
}
