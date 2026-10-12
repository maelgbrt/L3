// <TypeNom> : correspond au type de l'identifiant de l'état
// <TypeParam> : correspond au type du symbole ou étiquette de transition

public class Transition<TypeNom, TypeParam> {
    private Etat<TypeNom, TypeParam> departEtat; // L'état d'origine de la transition
    private Etat<TypeNom, TypeParam> finEtat;    // L'état de destination de la transition
    private TypeParam parametre;                 // Le symbole ou paramètre déclenchant la transition

    // Constructeur
    public Transition(Etat<TypeNom, TypeParam> departEtat, Etat<TypeNom, TypeParam> finEtat, TypeParam parametre) {
        this.departEtat = departEtat;
        this.finEtat = finEtat;
        this.parametre = parametre;
    }

    // Récupère l'état de départ
    public Etat<TypeNom, TypeParam> getdepartEtat() {
        return this.departEtat;
    }

    // Récupère l'état d'arrivée
    public Etat<TypeNom, TypeParam> getFinEtat() {
        return this.finEtat;
    }

    // Récupère le symbole associé à la transition
    public TypeParam getParametre() {
        return this.parametre;
    }

    // Modifie l'état de départ
    public void setdepartEtat(Etat<TypeNom, TypeParam> departEtat) {
        this.departEtat = departEtat;
    }

    // Modifie l'état d'arrivée
    public void setFinEtat(Etat<TypeNom, TypeParam> finEtat) {
        this.finEtat = finEtat;
    }

    // Modifie le symbole associé à la transition
    public void setParametre(TypeParam parametre) {
        this.parametre = parametre;
    }
}