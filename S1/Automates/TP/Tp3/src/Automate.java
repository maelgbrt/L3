import java.util.ArrayList;

public class Automate {
    ArrayList<String> alphabet = new ArrayList<>();
    ArrayList<Etat> EnsembleEtats = new ArrayList<>();
    Etat etatInitial;

    public Automate(ArrayList<String> alphabet, ArrayList<Etat> EnsembleEtats, Etat etatInitial) {
        this.alphabet = alphabet;
        this.EnsembleEtats = EnsembleEtats;
        this.etatInitial = etatInitial;
    }

    public boolean reconnait(ArrayList<String> Tab_mot) {

        Etat etat_courant = etatInitial;
        
        for (int i = 0; i < Tab_mot.size(); i++) {
            String c = Tab_mot.get(i);
            System.out.println(c);

            // etat_courant = etat_courant.findTransition(c);
            // if (etat_courant == null) {
            //     return false;
            // }
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







    public ArrayList<String> getAlphabet() {
        return alphabet;
    }

    public ArrayList<Etat> getEnsembleEtats() {
        return EnsembleEtats;
    }

    public Etat getEtatInitial() {
        return etatInitial;
    }

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