import java.util.ArrayList;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class Etat <TypeNom , TypeParam> {
    private boolean estEtatFinal;
    private TypeNom nomEtat;
    private ArrayList<Transition<TypeParam>> ensembleTransitions;

    public Etat(boolean estEtatFinal,TypeNom nomEtat, ArrayList<Transition<TypeParam>> ensembleTransitions){
        this.estEtatFinal = estEtatFinal;
        this.nomEtat = nomEtat;
        this.ensembleTransitions = (ensembleTransitions != null) ? ensembleTransitions : new ArrayList<>();
    }


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
        return  estEtatFinal;
    }
  
    public ArrayList<Transition<TypeParam>> getEnsembleTransitions() {
        return ensembleTransitions;
    }

    public void setEstEtatFinal(boolean estEtatFinal) {
        this.estEtatFinal = estEtatFinal;
    }
    public void setNomEtat(TypeNom nomEtat) {
        this.nomEtat = nomEtat;
    }

}