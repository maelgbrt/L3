public class Transition<T> {
    Etat departEtat;
    Etat finEtat;
    T parametre;

    public Transition(Etat departEtat,Etat finEtat,T parametre){
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
    public T getParametre() {
        return parametre;
    }
    public void setdepartEtat(Etat departEtat) {
        this.departEtat = departEtat;
    }
    public void setFinEtat(Etat finEtat) {
        this.finEtat = finEtat;
    }public void setParametre(T parametre) {
        this.parametre = parametre;
    }
}