import java.util.ArrayList;

public class Etat {
    boolean estEtatFinal;
    String nomEtat;
    ArrayList<Transition> ensembleTransitions;

    public Etat(boolean estEtatFinal,String nomEtat, ArrayList<Transition> ensembleTransitions){
        this.estEtatFinal = estEtatFinal;
        this.nomEtat = nomEtat;
        this.ensembleTransitions = (ensembleTransitions != null)
                                    ? ensembleTransitions
                                    :new ArrayList<>(); // pour pas avoir de null pointer exception
    }

    public Etat findTransition (String c){

    Etat etat_suivant = null;

    System.out.println("Etat : " + nomEtat);
        for (var transition : ensembleTransitions) {
            //System.out.println("transition : " + transition.parametre);
                        //System.out.println(transition.parametre + " = " + c);
           if (transition.parametre.equals(c) ) {
            
                etat_suivant = transition.finEtat;
           } 
        }
        return etat_suivant;
    }   

    public String getNomEtat() {
        return nomEtat;
    }
    public boolean getEstEtatFinal() {
        return  estEtatFinal;
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