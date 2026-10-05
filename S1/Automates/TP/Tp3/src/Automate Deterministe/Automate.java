import java.util.ArrayList;

// Représente un automate fini déterministe
public class Automate {
    // Composants de l'automate
    ArrayList<String> alphabet = new ArrayList<>();       // Ensemble des symboles valides (l'alphabet)
    ArrayList<Etat> EnsembleEtats = new ArrayList<>();    // Ensemble de tous les états de l'automate
    Etat etatInitial;                                      // État de départ pour la lecture d'un mot
    
    // Constructeur : initialise l'automate avec son alphabet, ses états et son état initial
    public Automate(ArrayList<String> alphabet, ArrayList<Etat> EnsembleEtats, Etat etatInitial) {
        this.alphabet = alphabet;
        this.EnsembleEtats = EnsembleEtats;
        this.etatInitial = etatInitial;
    }

    // Vérifie si une séquence de symboles (un mot) est acceptée par l'automate
    public boolean reconnait(ArrayList<String> Tab_mot) {

        // On commence la lecture à l'état initial
        Etat etat_courant = etatInitial;
        
        // Parcourt chaque symbole du mot un par un
        for (int i = 0; i < Tab_mot.size(); i++) {
            String c = Tab_mot.get(i);

            // Recherche la transition sortante pour le symbole 'c'
            etat_courant = etat_courant.findTransition(c);
            
            // Si aucune transition n'existe pour ce symbole, le mot est rejeté
            if (etat_courant == null) {
                return false;
            }
        }
        
        // À la fin du mot, on vérifie si l'état d'arrivée est un état final (acceptant)
        return etat_courant.getEstEtatFinal();
    }

    // --- Getters et Setters ---

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