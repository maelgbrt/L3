public class Transition {
    Etat departEtat;
    Etat finEtat;
    String parametre;

<<<<<<< HEAD
    public Transition(Etat departEtat,Etat finEtat,String parametre){
=======
    public Transition(Etat departEtat,Etat  finEtat,String parametre){
>>>>>>> c05ad57819557894491a54440b96d8a0f9270484
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