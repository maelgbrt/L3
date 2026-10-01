import java.util.ArrayList;

public class Automate {
    ArrayList<Character> alphabet = new ArrayList<>();
    ArrayList<Etat> EnsembleEtats = new ArrayList<>();
    Etat etatInitial;
    

    public Automate(ArrayList<Character> alphabet,ArrayList<Etat> EnsembleEtats,Etat etatInitial) {
        this.alphabet = alphabet;
        this.EnsembleEtats = EnsembleEtats;
        this.etatInitial = etatInitial;
    }



// Question 1.2
    public boolean reconnait (ArrayList<Character> mot){
        
        boolean res = true;
        // au début on NE peut être que dans l'état initial (aipe)
        Etat etat_courant = etatInitial;

        // On parcours sur les charachters de mot
        for (int i =0; i<mot.size();i++) {
            Character caractere = mot.get(i);   // un objet Character
            char c = caractere.charValue();

            Etat etat_suivant = FindTransition (c, etat_courant); // trouve la transition correspondante en parcourant chaque transition de l'etat courant et peut renvoyer null
                if (etat_suivant){
                    etat_courant = etat_suivant;
                }else {
                    res = false;
                }
        }
        return res;
    }


    public ArrayList<Character> getAlphabet() {
        return alphabet;
    }
    public ArrayList<Etat> getEnsembleEtats() {
        return EnsembleEtats;
    }
    public Etat getEtatInitial() {
        return etatInitial;
    }



    public void setAlphabet(ArrayList<Character> alphabet) {
        this.alphabet = alphabet;
    }
    public void setEnsembleEtats(ArrayList<Etat> ensembleEtats) {
        EnsembleEtats = ensembleEtats;
    }
    public void setEtatInitial(Etat etatInitial) {
        this.etatInitial = etatInitial;
    }

}