using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

// To save and load the user’s last chosen color, you’ll need three things in the MainManager class:
// A SaveData class that stores the color.
// A Save method that transforms that class into JSON format and writes it to a file.
// A Load method that transforms the data from the JSON file back into the SaveData class.
// Let’s start with the SaveData class:


public class MainManager : MonoBehaviour
{
    public static MainManager Instance;

    public Color TeamColor; // new variable declared

    [System.Serializable]
    class SaveData
    {
        public Color TeamColor;
    }

    public void SaveColor()
    {
        SaveData data = new SaveData();
        data.TeamColor = TeamColor;

        string json = JsonUtility.ToJson(data);
    
        File.WriteAllText(Application.persistentDataPath + "/savefile.json", json);
    }

    public void LoadColor()
    {
        string path = Application.persistentDataPath + "/savefile.json";
        if (File.Exists(path))
        {
            string json = File.ReadAllText(path);
            SaveData data = JsonUtility.FromJson<SaveData>(json);

            TeamColor = data.TeamColor;
        }
    }

    private void Awake()
    {
        // start of new code
        if (Instance != null)
        {
            Destroy(gameObject);
            return;
        }
        // end of new code
        
        Instance = this;
        DontDestroyOnLoad(gameObject);
    }
}
