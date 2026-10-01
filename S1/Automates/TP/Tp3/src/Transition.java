public class Transition {
    Etat departEtat;
    Etat finEtat;
    String parametre;

    public Transition(Etat departEtat,Etat finEtat,String parametre){
        this.departEtat = departEtat;
        this.finEtat = finEtat;
        this.parametre = parametre;
    }
    
   


    public Etat getdepartEtat() {
        return departEtat;
    }
    public Etat getFinEtat() {
        return finEtat;
    }
    public String getParametre() {
        return parametre;
    }
    public void setdepartEtat(Etat departEtat) {
        this.departEtat = departEtat;
    }
    public void setFinEtat(Etat finEtat) {
        this.finEtat = finEtat;
    }public void setParametre(String parametre) {
        this.parametre = parametre;
    }
}