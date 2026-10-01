import java.lang.annotation.Retention;
import java.util.ArrayList;

import javax.print.DocFlavor.STRING;

public class Etat {
    boolean estEtatFinal;
    String nomEtat;
    ArrayList<Transition> ensembleTransitions;

    public Etat(boolean estEtatFinal,String nomEtat, ArrayList<Transition> ensembleTransitions){
        this.estEtatFinal = estEtatFinal;
        this.nomEtat = nomEtat;
        this.ensembleTransitions = (ensembleTransitions == null) ? new ArrayList<>() : ensembleTransitions;
    }






public Etat findTransition (String c){

    Etat etat_suivant = null;

    // System.out.println("Etat : " + nomEtat);
        for (var transition : ensembleTransitions) {
            // System.out.println("transition : " + transition.parametre);
            // System.out.println("fin de la transition : " + transition.finEtat.nomEtat);
            // System.out.println(transition.parametre + " = " + c + " / " + transition.departEtat.nomEtat);

            
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