import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

// <TypeNom> : correspond au type de l'etat
// <TypeNom> : correspond au type du paramètre de transition


public class Etat<TypeNom, TypeParam> {
    private boolean estEtatFinal; // Indique si cet état est un état d'acceptation (final). 
    private TypeNom nomEtat; // Indique le nom de l'état 
    private ArrayList<Transition<TypeNom, TypeParam>> ensembleTransitions; // La liste des transitions qu'il sont liées a cette automate


    //  Constructeur
    public Etat(boolean estEtatFinal, TypeNom nomEtat, ArrayList<Transition<TypeNom, TypeParam>> ensembleTransitions) {
        this.estEtatFinal = estEtatFinal;
        this.nomEtat = nomEtat;
        this.ensembleTransitions = (ensembleTransitions != null) ? ensembleTransitions : new ArrayList<>();
    }


    // Fonction qui prends en paramètre un Paramètre de transition etrenvoie la liste des transitions liée a ce paramètre depuis l'état courant
    public Set<Etat<TypeNom, TypeParam>> findTransitions(TypeParam c) {
        Set<Etat<TypeNom, TypeParam>> reponse = new HashSet<>();
        for (Transition<TypeNom, TypeParam> transition : ensembleTransitions) {
            if (transition.getParametre().equals(c)) {
                reponse.add(transition.getFinEtat());
            }
        }
        return reponse;
    }


    
    public TypeNom getNomEtat() {
        return nomEtat;
    }

    public boolean getEstEtatFinal() {
        return estEtatFinal;
    }

    public ArrayList<Transition<TypeNom, TypeParam>> getEnsembleTransitions() {
        return ensembleTransitions;
    }

    public void setEstEtatFinal(boolean estEtatFinal) {
        this.estEtatFinal = estEtatFinal;
    }

    public void setNomEtat(TypeNom nomEtat) {
        this.nomEtat = nomEtat;
    }
}