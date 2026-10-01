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
        ArrayList<Etat> courants = new ArrayList<>();
        courants.add(etatInitial);   // au début on peut être que dans l'état initial

        // On parcours sur les charachters de mot
        for (int i =0; i<mot.size();i++) {
            Character caractere = mot.get(i);   // un objet Character
            char c = caractere.charValue();
            ArrayList<Etat> suivants = new ArrayList<>();

            for (int j = 0; j<courants.size(); j++){
                Etat e = courants.get(j);

                for (int x = 0; x < e.getEnsembleTransitions().size(); x++) {
                    Transition t = e.getEnsembleTransitions().get(x);
                    if (t.getParametre() == c) {
                        suivants.add(t.getArriveEtat());    // prbl si non deterministe (partie 2)
                    }
                }
                

            }

            courants = suivants;
            if (courants.isEmpty()) {
                return false;
            }

        }
        for (int i = 0; i < courants.size(); i++) {
            Etat e = courants.get(i);
            if (e.getEstEtatFinal()) {
                return true;
            }
        }
        return false;
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