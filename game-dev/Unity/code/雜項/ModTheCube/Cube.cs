using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cube : MonoBehaviour
{
    public MeshRenderer Renderer;
    private float pi = 3.14159f;
    private float red = 1.0f;
    private float green = 0.0f;
    private float blue = 0.0f;
    private const float RedCyclesPerSecond = 0.5f;
    void Start()
    {
        transform.position = new Vector3(3, 4, 1);
        transform.localScale = Vector3.one * 1.5f;

        Material material = Renderer.material;
        material.color = new Color(0.5f, 1.0f, 0.3f, 0.4f);
    }
    
    void Update()
    {
        transform.Rotate(50.0f * Time.deltaTime, 10.0f * Time.deltaTime, 10.0f * Time.deltaTime);
        Material material = Renderer.material;


        red += RedCyclesPerSecond * Time.deltaTime;
        blue += RedCyclesPerSecond * Time.deltaTime;
        green += RedCyclesPerSecond * Time.deltaTime;
        if (red > 1.0f)
        {
            red = 0.0f;
        }
        if (blue > 1.0f)
        {
            blue = 0.0f;
        }
        if (green > 1.0f)
        {
            green = 0.0f;
        }
        material.color = new Color(red, blue, green);
    }
}
