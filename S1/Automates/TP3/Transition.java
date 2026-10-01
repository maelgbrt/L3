public class Transition {
    Etat arriveEtat;
    Etat finEtat;
    char parametre;

    public Transition(Etat finEtat,Etat arriveEtat,char parametre){
        this.arriveEtat = arriveEtat;
        this.finEtat = finEtat;
        this.parametre = parametre;
    }

   


    public Etat getArriveEtat() {
        return arriveEtat;
    }
    public Etat getFinEtat() {
        return finEtat;
    }
    public char getParametre() {
        return parametre;
    }
    public void setArriveEtat(Etat arriveEtat) {
        this.arriveEtat = arriveEtat;
    }
    public void setFinEtat(Etat finEtat) {
        this.finEtat = finEtat;
    }public void setParametre(char parametre) {
        this.parametre = parametre;
    }
}