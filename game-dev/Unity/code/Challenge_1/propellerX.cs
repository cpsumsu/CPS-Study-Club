using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class propellerX : MonoBehaviour
{
    public float speed = 30;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 r = new Vector3(0,0, 1);
        transform.Rotate(r, speed * Time.deltaTime);
    }
}
