public class Transition {
    Etat departEtat;
    Etat finEtat;
    char parametre;

    public Transition(Etat finEtat,Etat departEtat,char parametre){
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
    public char getParametre() {
        return parametre;
    }
    public void setdepartEtat(Etat departEtat) {
        this.departEtat = departEtat;
    }
    public void setFinEtat(Etat finEtat) {
        this.finEtat = finEtat;
    }public void setParametre(char parametre) {
        this.parametre = parametre;
    }
}