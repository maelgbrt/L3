import java.util.ArrayList;

public class Automate {
    ArrayList<Character> alphabet = new ArrayList<>();
    ArrayList<Etat> EnsembleEtats = new ArrayList<>();
    Etat etatInitial;

    public Automate(ArrayList<Character> alphabet, ArrayList<Etat> EnsembleEtats, Etat etatInitial) {
        this.alphabet = alphabet;
        this.EnsembleEtats = EnsembleEtats;
        this.etatInitial = etatInitial;
    }

    // // Question 1.2
    public boolean reconnait(ArrayList<String> Tab_mot) {

    //     // au début on NE peut être que dans l'état initial (aipe)
        Etat etat_courant = etatInitial;
        
    //     // On parcours sur les charachters de mot
        for (int i = 0; i < Tab_mot.size(); i++) {
            String c = Tab_mot.get(i);

            etat_courant = etat_courant.findTransition(c);
            if (etat_courant == null) {
                return false;
            }
        }
        return etat_courant.estEtatFinal;
    }


    // Au début on ne peut être que dans l'état initial
// Etat etat_courant = etatInitial;

// // On parcourt les caractères du mot
// for (int i = 0; i < mot.length(); i++) {
//     char c = mot.charAt(i); // Utilisation de charAt(i)
//     etat_courant = etat_courant.findTransition(c);
//     if (etat_courant == null) {
//         return false;
//     }
// }
// return etat_courant.estEtatFinal;






     // Question 1.2
    public T reconnait(ArrayList<Character> mot) {

        // au début on NE peut être que dans l'état initial (aipe)
        Etat etat_courant = etatInitial;
        
        // On parcours sur les charachters de mot
        for (int i = 0; i < mot.size(); i++) {
            char c = mot.get(i);

            etat_courant = etat_courant.findTransition(c);
            if (etat_courant == null) {
                return false;
            }
        }
        return etat_courant.estEtatFinal;
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