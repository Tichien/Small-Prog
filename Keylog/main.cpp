#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string Traducteur(int keyPressed, bool *isMajPressed, bool *isShiftPressed, bool *isAltGrPressed);

int main()
{
    string ligne;
    string keyState;
    string const fichierEnL("input.txt");
    ifstream fluxFichier(fichierEnL.c_str());

    int keycode;
    bool isMajPressed = false;
    bool isShiftPressed = false;
    bool isAltGrPressed = false;

        if(fluxFichier)
        {
            while((getline(fluxFichier, ligne)) != NULL)
            {
                for(int i = 0 ; i < 2 ; i++)
                {fluxFichier >> keyState;}
                fluxFichier >> keycode;

                if(keyState == "press" && (keycode == 50 || keycode == 62))
                isShiftPressed = true;

                if(keyState == "release" && (keycode == 50 || keycode == 62))
                isShiftPressed = false;

                if(keyState == "press" && keycode == 66)
                isMajPressed = !isMajPressed;

                if(keyState == "press" && (keycode == 108))
                isShiftPressed = true;

                if(keyState == "release" && (keycode == 108))
                isShiftPressed = false;

                if(keyState == "press")
                cout << Traducteur(keycode, &isMajPressed, &isShiftPressed, &isAltGrPressed);
            }
        }

        else{cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;}

    return 0;
}

string Traducteur(int keyPressed, bool *isMajPressed, bool *isShiftPressed, bool *isAltGrPressed)
{
    string traduction = "";

    if(!(*isMajPressed) && !(*isShiftPressed))
    {
        string toucheClavMin[120] = {"", "","","","","","","","","Echap","&",   //10
                                     "é","\"","'","(","-","è","_","ç","à",")",   //20
                                     "=","Erase","Tab","a","z","e","r","t","y","u",   //30
                                     "i","o","p","^","$","Entrer\n","Control","q","s","d",   //40
                                     "f","g","h","j","k","l","m","ù","²","Shift",   //50
                                     "*","w","x","c","v","b","n",",",";",":",   //60
                                     "!","Shift","*","ModeSwitch"," ","Maj","f1","f2","f3","f4",   //70
                                     "f5","f6","f7","f8","f9","f10","NumLock","","7","8",   //80
                                     "9","-","4","5","6","+","1","2","3","0",   //90
                                     ".","","","<","f11","f12","Home","","Prior","",   //100
                                     "","","","End","Next","Insert","Delete","AltGr","Control","",   //110
                                     "","/","Erase","","Alt","","","",""};

        traduction = toucheClavMin[keyPressed];
    }

    else if((*isShiftPressed) || (*isMajPressed))
    {
        string toucheClavMaj[120] = {"", "","","","","","","","","Echap","1",   //10
                                     "2","3","4","5","6","7","8","9","0","°",   //20
                                     "+","Erase","Tab","A","Z","E","R","T","Y","U",   //30
                                     "I","O","P","¨","£","Entrer\n","Control_l","Q","S","D",   //40
                                     "F","G","H","J","K","L","M","%","²","Shift",   //50
                                     "µ","W","X","C","V","B","N","?",".","/",   //60
                                     "§","Shift","*","ModeSwitch"," ","Maj","f1","f2","f3","f4",   //70
                                     "f5","f6","f7","f8","f9","f10","NumLock","","7","8",   //80
                                     "9","-","4","5","6","+","1","2","3","0",   //90
                                     ".","",">","f11","f12","Home","","Prior","",   //100
                                     "","","","End","Next","Insert","Delete","AltGr","Control","",   //110
                                     "","/","Erase","","Alt","","","",""};

        traduction = toucheClavMaj[keyPressed];
    }


    if((*isAltGrPressed))
    {
        string toucheClavMin[120] = {"", "","","","","","","","","Echap","&",   //10
                                     "~","#","{","[","|","`","\"","^","@","]",   //20
                                     "}","Erase","Tab","a","z","e","r","t","y","u",   //30
                                     "i","o","p","^","$","Entrer\n","Control","q","s","d",   //40
                                     "f","g","h","j","k","l","m","ù","²","Shift",   //50
                                     "*","w","x","c","v","b","n",",",";",":",   //60
                                     "!","Shift","*","ModeSwitch"," ","Maj","f1","f2","f3","f4",   //70
                                     "f5","f6","f7","f8","f9","f10","NumLock","","7","8",   //80
                                     "9","-","4","5","6","+","1","2","3","0",   //90
                                     ".","","","<","f11","f12","Home","","Prior","",   //100
                                     "","","","End","Next","Insert","Delete","AltGr","Control","",   //110
                                     "","/","Erase","","Alt","","","",""};

        traduction = toucheClavMin[keyPressed];
    }

    return traduction != "" ? traduction : "Erreur:DonnéesManquantes";
}
