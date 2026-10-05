import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class Automate<TypeNom, TypeParam> {
    private ArrayList<Etat<TypeNom, TypeParam>> ensembleEtats;
    private Etat<TypeNom, TypeParam> etatInitial;

    public Automate(ArrayList<Etat<TypeNom, TypeParam>> ensembleEtats, Etat<TypeNom, TypeParam> etatInitial) {
        this.ensembleEtats = (ensembleEtats != null) ? ensembleEtats : new ArrayList<>();
        this.etatInitial = etatInitial;
    }



    
 public boolean reconnait(ArrayList<TypeParam> mot) {
        Set<Etat<TypeNom, TypeParam>> etatsCourants = new HashSet<>();
        etatsCourants.add(etatInitial);

        for (TypeParam symbole : mot) {
            Set<Etat<TypeNom, TypeParam>> suivants = new HashSet<>();
            for (Etat<TypeNom, TypeParam> etat : etatsCourants) {
                suivants.addAll(etat.findTransitions(symbole));
            }
            etatsCourants = suivants;

            if (etatsCourants.isEmpty()) {
                return false;
            }
        }

        for (Etat<TypeNom, TypeParam> etat : etatsCourants) {
            if (etat.getEstEtatFinal()) {
                return true;
            }
        }
        return false;
    }

    public ArrayList<Etat<TypeNom, TypeParam>> getEnsembleEtats() { return ensembleEtats; }
    public Etat<TypeNom, TypeParam> getEtatInitial() { return etatInitial; }
}