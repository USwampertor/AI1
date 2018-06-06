using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Controller : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		if(Input.GetKey(KeyCode.W))
        {
            transform.Translate(0.0f, 0.0f, .2f);
        }
        if (Input.GetKey(KeyCode.S))
        {
            transform.Translate(0.0f, 0.0f, -.2f);
        }
        if (Input.GetKey(KeyCode.A))
        {
            transform.Rotate(0, -10.0f, 0);
        }
        if (Input.GetKey(KeyCode.D))
        {
            transform.Rotate(0, 10.0f, 0);
        }
    }
}
