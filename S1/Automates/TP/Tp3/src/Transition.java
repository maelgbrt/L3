public class Transition <NomType,TypeParam> {
    private Etat<TypeNom,TypeParam> departEtat;
    private Etat<TypeNom,TypeParam> finEtat;
    private TypeParam parametre;

    public Transition(Etat<TypeNom,TypeParam> departEtat,Etat<TypeNom,TypeParam> finEtat,TypeParam parametre){
        this.departEtat = departEtat;
        this.finEtat = finEtat;
        this.parametre = parametre;
    }


    public Etat<TypeNom,TypeParam> getdepartEtat() {
        return this.departEtat;
    }
    public Etat<TypeNom,TypeParam> getFinEtat() {
        return this.finEtat;
    }
    public TypeParam getParametre() {
        return this.parametre;
    }
    public void setdepartEtat(Etat<TypeNom,TypeParam> departEtat) {
        this.departEtat = departEtat;
    }
    public void setFinEtat(Etat<TypeNom,TypeParam> finEtat) {
        this.finEtat = finEtat;
    }public void setParametre(TypeParam parametre) {
        this.parametre = parametre;
    }
}