import java.util.ArrayList;

public class Automate {
    ArrayList<Character> alphabet = new ArrayList<>();
    ArrayList<Etat> EnsembleEtats = new ArrayList<>();
    etat etatInitial;
    

    public Automate(ArrayList<Character> alphabet,ArrayList<Etat> EnsembleEtats,ArrayList<Etat> etatInitial) {
        this.alphabet = alphabet;
        this.EnsembleEtats = EnsembleEtats;
        this.etatInitial = etatInitial;
    }



//babaa
    public reconnait (ArrayList<Character> mot){
        // charactere b 

        

        //boucle sur Ensemble Etat
    }


    public ArrayList<Character> getAlphabet() {
        return alphabet;
    }
    public ArrayList<Etat> getEnsembleEtats() {
        return EnsembleEtats;
    }
    public etat getEtatInitial() {
        return etatInitial;
    }



    public void setAlphabet(ArrayList<Character> alphabet) {
        this.alphabet = alphabet;
    }
    public void setEnsembleEtats(ArrayList<Etat> ensembleEtats) {
        EnsembleEtats = ensembleEtats;
    }
    public void setEtatInitial(etat etatInitial) {
        this.etatInitial = etatInitial;
    }

}
