// Représente une transition orientée entre deux états dans un automate
public class Transition {
    // Attributs de la transition
    Etat departEtat;    // État source (d'où part la transition)
    Etat finEtat;       // État cible (où arrive la transition)
    String parametre;   // Symbole ou étiquette déclenchant la transition (ex: "a", "b")

    // Constructeur : initialise la transition avec sa source, sa destination et son symbole
    public Transition(Etat departEtat, Etat finEtat, String parametre) {
        this.departEtat = departEtat;
        this.finEtat = finEtat;
        this.parametre = parametre;
    }

    // --- Getters et Setters ---

    // Renvoie l'état de départ
    public Etat getdepartEtat() {
        return departEtat;
    }

    // Renvoie l'état d'arrivée
    public Etat getFinEtat() {
        return finEtat;
    }

    // Renvoie l'étiquette / symbole de la transition
    public String getParametre() {
        return parametre;
    }

    // Modifie l'état de départ
    public void setdepartEtat(Etat departEtat) {
        this.departEtat = departEtat;
    }

    // Modifie l'état d'arrivée
    public void setFinEtat(Etat finEtat) {
        this.finEtat = finEtat;
    }

    // Modifie l'étiquette / symbole
    public void setParametre(String parametre) {
        this.parametre = parametre;
    }
}