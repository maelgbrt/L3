import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;



// <TypeNom> : correspond au type de l'etat
// <TypeNom> : correspond au type du paramètre de transition

public class Automate<TypeNom, TypeParam> {
    private ArrayList<Etat<TypeNom, TypeParam>> ensembleEtats; // Liste des Etats présent dans l'automate
    private Etat<TypeNom, TypeParam> etatInitial; // Indique Etat Initial


    // Constructeur
    public Automate(ArrayList<Etat<TypeNom, TypeParam>> ensembleEtats, Etat<TypeNom, TypeParam> etatInitial) {
        this.ensembleEtats = (ensembleEtats != null) ? ensembleEtats : new ArrayList<>();
        this.etatInitial = etatInitial;
    }



// Reconnait si le mot passé en paramètre correspond à l'automate courant
 public boolean reconnait(ArrayList<TypeParam> mot) {
        Set<Etat<TypeNom, TypeParam>> etatsCourants = new HashSet<>(); // Creer un set (pour eviter doublon) d'etat courant 
        etatsCourants.add(etatInitial); // Ajoute etat INitial dans la liste d'etat courant

        for (TypeParam symbole : mot) { // Pour chaque symbole present dans le mot
            Set<Etat<TypeNom, TypeParam>> suivants = new HashSet<>(); // On creer un set de Suivant
            for (Etat<TypeNom, TypeParam> etat : etatsCourants) { // Pour chaque etat dans etat courant
                suivants.addAll(etat.findTransitions(symbole)); // On ajoute la liste des etat correpondant avec le symbole de transition dans suivant
            }
            etatsCourants = suivants; // On passe dans etat courant les etats de suivant

            if (etatsCourants.isEmpty()) {
                return false;
            }
        }

        for (Etat<TypeNom, TypeParam> etat : etatsCourants) {
            if (etat.getEstEtatFinal()) { // verifie le(s) etat(s) final/finaux
                return true;
            }
        }
        return false;
    }

    public ArrayList<Etat<TypeNom, TypeParam>> getEnsembleEtats() { return ensembleEtats; }
    public Etat<TypeNom, TypeParam> getEtatInitial() { return etatInitial; }
}