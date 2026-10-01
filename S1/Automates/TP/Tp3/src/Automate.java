import java.util.ArrayList;

public class Automate {
<<<<<<< HEAD
    ArrayList<String> alphabet = new ArrayList<>();
=======
    ArrayList<String> alphabet = new ArrayList<String>();
>>>>>>> c05ad57819557894491a54440b96d8a0f9270484
    ArrayList<Etat> EnsembleEtats = new ArrayList<>();
    Etat etatInitial;
    

<<<<<<< HEAD
    public Automate(ArrayList<String> alphabet, ArrayList<Etat> EnsembleEtats, Etat etatInitial) {
=======
    public Automate(ArrayList<String> alphabet,ArrayList<Etat> EnsembleEtats,Etat etatInitial) {
>>>>>>> c05ad57819557894491a54440b96d8a0f9270484
        this.alphabet = alphabet;
        this.EnsembleEtats = EnsembleEtats;
        this.etatInitial = etatInitial;
    }

<<<<<<< HEAD
    public boolean reconnait(ArrayList<String> Tab_mot) {

        Etat etat_courant = etatInitial;
        
        for (int i = 0; i < Tab_mot.size(); i++) {
            String c = Tab_mot.get(i);
            System.out.println(c);

            // etat_courant = etat_courant.findTransition(c);
            // if (etat_courant == null) {
            //     return false;
            // }
=======


// Question 1.2
    // public boolean reconnait1 (ArrayList<Character> mot){
    //     ArrayList<Etat> courants = new ArrayList<>();
    //     courants.add(etatInitial);   // au début on peut être que dans l'état initial

    //     // On parcours sur les charachters de mot
    //     for (int i =0; i<mot.size();i++) {
    //         Character caractere = mot.get(i);   // un objet Character
    //         char c = caractere.charValue();
    //         ArrayList<Etat> suivants = new ArrayList<>(); // Peut créer des prbl de

    //         for (int j = 0; j<courants.size(); j++){
    //             Etat e = courants.get(j);

    //             for (int x = 0; x < e.getEnsembleTransitions().size(); x++) {
    //                 Transition t = e.getEnsembleTransitions().get(x);
    //                 if (t.getParametre() == c) {
    //                     suivants.add(t.getArriveEtat());    // prbl si non deterministe (partie 2)
    //                 }
    //             }
    //         }

    //         courants = suivants;
    //         if (courants.isEmpty()) {
    //             return false;
    //         }

    //     }
    //     for (int i = 0; i < courants.size(); i++) {
    //         Etat e = courants.get(i);
    //         if (e.getEstEtatFinal()) {
    //             return true;
    //         }
    //     }
    //     return false;
    // }


    public boolean reconnait(ArrayList<String> mot) {

        // au début on NE peut être que dans l'état initial (aipe)
        Etat etat_courant = etatInitial;
        
        // On parcours sur les charachters de mot
        for (int i = 0; i < mot.size(); i++) {
            String c = mot.get(i);
            etat_courant = etat_courant.findTransition(c);
            if (etat_courant == null) {
                return false;
            }
>>>>>>> c05ad57819557894491a54440b96d8a0f9270484
        }
        return etat_courant.estEtatFinal;
    }

<<<<<<< HEAD

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






=======
    // public boolean reconnait_gen(ArrayList<Character> mot) {

    //     // au début on NE peut être que dans l'état initial (aipe)
    //     Etat etat_courant = etatInitial;
        
    //     // On parcours sur les charachters de mot
    //     for (int i = 0; i < mot.size(); i++) {
    //         char c = mot.get(i);
    //         etat_courant = etat_courant.findTransition(c);
    //         if (etat_courant == null) {
    //             return false;
    //         }
    //     }
    //     return etat_courant.estEtatFinal;
    // }
>>>>>>> c05ad57819557894491a54440b96d8a0f9270484

    public ArrayList<String> getAlphabet() {
        return alphabet;
    }
    public ArrayList<Etat> getEnsembleEtats() {
        return EnsembleEtats;
    }
    public Etat getEtatInitial() {
        return etatInitial;
    }

<<<<<<< HEAD
=======


>>>>>>> c05ad57819557894491a54440b96d8a0f9270484
    public void setAlphabet(ArrayList<String> alphabet) {
        this.alphabet = alphabet;
    }
    public void setEnsembleEtats(ArrayList<Etat> ensembleEtats) {
        EnsembleEtats = ensembleEtats;
    }
    public void setEtatInitial(Etat etatInitial) {
        this.etatInitial = etatInitial;
    }

}