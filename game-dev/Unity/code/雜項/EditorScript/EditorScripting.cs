using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class EditorScripting : EditorScripting
{
    string custString = "String Here";
    bool groupEnabled;
    bool optionalSettings = true;
    float jumpMod = 1.0f;
    float impactMod = 0.5f;

    [MenuItem("Window / Custom Controls")]

    public static void ShowWindow()
    {
        EditorWindow.GetWindow(typeof(EditorScripting));
    }

    private void OnGUI() {

    }

    
}