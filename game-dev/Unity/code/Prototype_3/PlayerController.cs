using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    private Rigidbody playerRb;
    public float jumpForce;
    public float gravityModifier;
    public bool isOnGround = true;
    private int jumptime = 0;
    public bool gameOver = false;

    private Animator playerAnim;
    public ParticleSystem explosionParticle;
    public ParticleSystem dirtParticle;
    public AudioClip jumpSound;
    public AudioClip crashSound;
    public AudioSource playerAudio;
    private MoveLeft moveleftBackground;
    private GameObject[] moveleftObs;
    public bool doubleSpeed = false;

    // Start is called before the first frame update
    void Start()
    {
        playerRb = GetComponent<Rigidbody>();
        Physics.gravity *= gravityModifier;
        playerAnim = GetComponent<Animator>();
        playerAudio = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        moveleftBackground = GameObject.Find("Background").GetComponent<MoveLeft>();
        moveleftObs = GameObject.FindGameObjectsWithTag("Obstacle");
        if (Input.GetKeyDown(KeyCode.Space) && jumptime < 2 && !gameOver)
        {
            playerRb.AddForce(Vector3.up * jumpForce, ForceMode.Impulse);
            jumptime++;
            playerAnim.SetTrigger("Jump_trig");
            dirtParticle.Stop();
            // 在Animator中存在Jump_trig

            playerAudio.PlayOneShot(jumpSound,1.0f);
        }
        if (Input.GetButton("LShift") && !gameOver)
        {
            doubleSpeed = true;
            playerAnim.SetFloat("Speed_Multiplier",2.0f);
        }
        else if (doubleSpeed)
        {
            doubleSpeed = false;
            playerAnim.SetFloat("Speed_Multiplier",1.0f);
        }
    }
    private void OnCollisionEnter(Collision collision) {
        if (collision.gameObject.CompareTag("Ground"))
        {
            jumptime = 0;
            dirtParticle.Play();
        }
        else if (collision.gameObject.CompareTag("Obstacle"))
        {
            gameOver = true;
            Debug.Log("Game Over!");
            // Death Anim
            playerAnim.SetBool("Death_b",true);
            playerAnim.SetInteger("DeathType_int",1);
            explosionParticle.Play();
            dirtParticle.Stop();
            playerAudio.PlayOneShot(crashSound,1.0f);
        }
    }
}
