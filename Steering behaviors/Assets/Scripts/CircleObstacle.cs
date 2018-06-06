using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CircleObstacle : gameObject {

    public float radio;
	// Use this for initialization
	void Start (){
        vMyPosition = transform.position;
        radio = GetComponent<Renderer>().bounds.extents.magnitude;

    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
