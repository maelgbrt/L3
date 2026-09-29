import java.util.ArrayList;

public class Etat {
    boolean estEtatFinal;
    string nomEtat;
    ArrayList<Transition> ensembleTransitions;

    public Etat(boolean estEtatFinal,string nomEtat, ArrayList<Transition> ensembleTransitions){
        this.estEtatFinal = estEtatFinal;
        this.nomEtat = nomEtat;
        this.ensembleTransitions = ensembleTransitions;
    }

    public string getNomEtat() {
        return nomEtat;
    }
    public boolean getEstEtatFinal() {
        return  estEtatFinal;
    }
  
    public void setEstEtatFinal(boolean estEtatFinal) {
        this.estEtatFinal = estEtatFinal;
    }
    public void setNomEtat(string nomEtat) {
        this.nomEtat = nomEtat;
    }

}
