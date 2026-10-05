import java.util.ArrayList;

public class App {
    public static void main(String[] args) {
            System.out.println("Hello, World!");



            Etat un = new Etat<Integer,Character>(false,1,null);
            Etat deux = new Etat<Interger,Character>(false,2,null);
            Etat trois = new Etat<Integer, Character>(true,3,null);
            // Etat String = new Etat<String,Integer>(false,"Le point 1",null);
            // Etat Char = new Etat<String,Integer>(false,"Le point 1",null);



            // String.getEnsembleTransitions().add(new Transition<>(String, Char, Integer));

                    // Etat GoLabyrinthe = new  Etat(false,"Parcours le labyrinthe",null);
                    // Etat FollowPC = new  Etat(false, "Poursuit Pac-Man",null);
                    // Etat FleePC = new  Etat(false, "Fuit Pac-Man",null);
        

        Transition FindBase = new Transition<String>(returnBase, GoLabyrinthe, "atteint la base");
        //         Transition FindBase = new Transition(returnBase,GoLabyrinthe, "atteint la base");        

    }



//         Etat returnBase = new  Etat(false, "Retourne à la base",null);
        
//         Transition LosePC = new Transition(FollowPC,GoLabyrinthe, "a perdu Pac-Man");
//         Transition SeePC = new Transition(GoLabyrinthe,FollowPC, "a vu Pac-Man");
//         Transition EatbyPC = new Transition(FleePC,returnBase, "a été mangé par Pac-Man");
//         Transition EatGomme = new Transition(FollowPC,FleePC, "Pac-Man mange une super pac-gomme");
//         Transition EatGomme2 = new Transition(GoLabyrinthe,FleePC, "Pac-Man mange une super pac-gomme");
//         Transition ExpirePacGomme = new Transition(FleePC,GoLabyrinthe, "Super pac-gomme expire");

//         ArrayList<Transition> TransitionGoLabyrinthe = new  ArrayList<>();
//         ArrayList<Transition> TransitionFollowPC = new  ArrayList<>();
//         ArrayList<Transition> TransitionFleePC = new  ArrayList<>();
//         ArrayList<Transition> TransitionReturnBase = new  ArrayList<>();

//         TransitionGoLabyrinthe.add(SeePC);
//         TransitionGoLabyrinthe.add(EatGomme2);
//         TransitionFollowPC.add(LosePC);
//         TransitionFollowPC.add(EatGomme);
//         TransitionFleePC.add(ExpirePacGomme);
//         TransitionFleePC.add(EatbyPC);
//         TransitionReturnBase.add(FindBase);

//         GoLabyrinthe.ensembleTransitions.addAll(TransitionGoLabyrinthe);
//         FollowPC.ensembleTransitions.addAll(TransitionFollowPC);
//         FleePC.ensembleTransitions.addAll(TransitionFleePC);
//         returnBase.ensembleTransitions.addAll(TransitionReturnBase);


//         ArrayList<Etat> ensembleEtats = new ArrayList<>();
//         ensembleEtats.add(GoLabyrinthe);
//         ensembleEtats.add(FollowPC);
//         ensembleEtats.add(FleePC);
//         ensembleEtats.add(returnBase);


//         Automate AutomatePC = new Automate( ensembleEtats, GoLabyrinthe);


//         // ############ QUESTION 3
// // ############ QUESTION 3 : TESTS DE L'AUTOMATE PAC-MAN

//         System.out.println("\n--- SCÉNARIO 1 : Chasse puis perte de vue ---");
//         // Parcours -> Chasse -> Parcours
//         ArrayList<String> test1 = new ArrayList<>();
//         test1.add("a vu Pac-Man");
//         test1.add("a perdu Pac-Man");
//         System.out.println("Séquence valide : " + AutomatePC.reconnait(test1)); // Attendu : true

//         System.out.println("\n--- SCÉNARIO 2 : Pris au piège par une super pac-gomme ---");
//         // Parcours -> Chasse -> Super gomme -> Mangé -> Retour base -> Parcours
//         ArrayList<String> test2 = new ArrayList<>();
//         test2.add("a vu Pac-Man");
//         test2.add("Pac-Man mange une super pac-gomme");
//         test2.add("a été mangé par Pac-Man");
//         test2.add("atteint la base");
//         System.out.println("Cycle complet de capture : " + AutomatePC.reconnait(test2)); // Attendu : true

//         // System.out.println("\n--- SCÉNARIO 3 : Fuite réussie (expiration) ---");
//         // // Parcours -> Super gomme -> Fuite -> Expiration -> Parcours
//         // ArrayList<String> test3 = new ArrayList<>();
//         // test3.add("Pac-Man mange une super pac-gomme");
//         // test3.add("Super pac-gomme expire");
//         // System.out.println("Survie à la super gomme : " + AutomatePC.reconnait(test3)); // Attendu : true

//         // System.out.println("\n--- SCÉNARIO 4 : Transition impossible (doit échouer) ---");
//         // // Impossible d'être mangé directement depuis l'état initial (GoLabyrinthe)
//         // ArrayList<String> testInvalide = new ArrayList<>();
//         // testInvalide.add("a été mangé par Pac-Man");
//         // System.out.println("Action impossible : " + AutomatePC.reconnait(testInvalide)); // Attendu : false

//         // System.out.println("\n--- SCÉNARIO 5 : Mot inconnu hors alphabet ---");
//         // ArrayList<String> testHorsAlphabet = new ArrayList<>();
//         // testHorsAlphabet.add("Pac-Man saute un mur");
//         // System.out.println("Hors alphabet : " + AutomatePC.reconnait(testHorsAlphabet)); // Attendu : false
       



//     // }
    
//     }

}