using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnManager : MonoBehaviour
{
    public GameObject[] obstaclePrefab;
    private Vector3 spawnPos = new Vector3(25,0,0);
    // Start is called before the first frame update
    private float startDelay = 2;
    private float repeatRate = 2.5f;

    private PlayerController playerController;
    void Start()
    {
        InvokeRepeating("SpawnObstacle",startDelay,repeatRate);
        playerController = GameObject.Find("Player").GetComponent<PlayerController>();
    }

    void SpawnObstacle()
    {
        int i = Random.Range(0,obstaclePrefab.Length);
        if (playerController.gameOver == false)
            Instantiate(obstaclePrefab[i],spawnPos,obstaclePrefab[i].transform.rotation);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
