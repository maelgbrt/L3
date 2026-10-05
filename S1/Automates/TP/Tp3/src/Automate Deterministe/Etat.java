import java.util.ArrayList;

// Représente un état au sein d'un automate
public class Etat {
    // Attributs décrivant l'état
    boolean estEtatFinal;                       // Indique si l'état est terminal/acceptant
    String nomEtat;                             // Nom ou identifiant de l'état (ex: "q0", "deux")
    ArrayList<Transition> ensembleTransitions;  // Liste des transitions sortant de cet état

    // Constructeur : initialise les champs et évite les erreurs NullPointerException
    public Etat(boolean estEtatFinal, String nomEtat, ArrayList<Transition> ensembleTransitions) {
        this.estEtatFinal = estEtatFinal;
        this.nomEtat = nomEtat;
        this.ensembleTransitions = (ensembleTransitions != null)
                                    ? ensembleTransitions
                                    : new ArrayList<>(); // Initialise une liste vide si null
    }

    // Cherche et renvoie l'état cible pour une lettre/symbole donné 'c'
    public Etat findTransition(String c) {
        Etat etat_suivant = null;

        // Parcours toutes les transitions sortantes
        for (var transition : ensembleTransitions) {
            // Si l'étiquette de la transition correspond au symbole lu
            if (transition.getParametre().equals(c)) {
                etat_suivant = transition.finEtat; // Récupère l'état d'arrivée
            }
        }
        return etat_suivant; // Renvoie l'état suivant ou null si aucune transition n'existe
    }   

    // --- Getters et Setters ---

    public String getNomEtat() {
        return nomEtat;
    }

    public boolean getEstEtatFinal() {
        return estEtatFinal;
    }
  
    public ArrayList<Transition> getEnsembleTransitions() {
        return ensembleTransitions;
    }

    public void setEstEtatFinal(boolean estEtatFinal) {
        this.estEtatFinal = estEtatFinal;
    }

    public void setNomEtat(String nomEtat) {
        this.nomEtat = nomEtat;
    }
}