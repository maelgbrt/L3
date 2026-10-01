
import java.util.ArrayList;

public class App {
    public static void main(String[] args) {
            System.out.println("Hello, World!");

        Etat GoLabyrinthe = new  Etat(false,"Parcours le labyrinthe",null);
        Etat FollowPC = new  Etat(false, "Poursuit Pac-Man",null);
        Etat FleePC = new  Etat(false, "Fuit Pac-Man",null);
        Etat returnBase = new  Etat(false, "Retourne à la base",null);
        
        Transition FindBase = new Transition(returnBase,GoLabyrinthe, "atteint la base");        
        Transition LosePC = new Transition(FollowPC,GoLabyrinthe, "a perdu Pac-Man");
        Transition SeePC = new Transition(GoLabyrinthe,FollowPC, "a vu Pac-Man");
        Transition EatbyPC = new Transition(FleePC,returnBase, "a été mangé par Pac-Man");
        Transition EatGomme = new Transition(FollowPC,FleePC, "Pac-Man mange une super pac-gomme");
        Transition EatGomme2 = new Transition(GoLabyrinthe,FleePC, "Pac-Man mange une super pac-gomme");
        Transition ExpirePacGomme = new Transition(FleePC,GoLabyrinthe, "Super pac-gomme expire");

        ArrayList<Transition> TransitionGoLabyrinthe = new  ArrayList<>();
        ArrayList<Transition> TransitionFollowPC = new  ArrayList<>();
        ArrayList<Transition> TransitionFleePC = new  ArrayList<>();
        ArrayList<Transition> TransitionReturnBase = new  ArrayList<>();

        TransitionGoLabyrinthe.add(SeePC);
        TransitionGoLabyrinthe.add(EatGomme2);
        TransitionFollowPC.add(LosePC);
        TransitionFollowPC.add(EatGomme);
        TransitionFleePC.add(ExpirePacGomme);
        TransitionFleePC.add(EatbyPC);
        TransitionReturnBase.add(FindBase);

        GoLabyrinthe.ensembleTransitions.addAll(TransitionGoLabyrinthe);
        FollowPC.ensembleTransitions.addAll(TransitionFollowPC);
        FleePC.ensembleTransitions.addAll(TransitionFleePC);
        returnBase.ensembleTransitions.addAll(TransitionReturnBase);

        ArrayList<String> alphabet = new ArrayList<>();
        alphabet.add("atteint la base");
        alphabet.add("Pac-Man mange une super pac-gomme");
        alphabet.add("a vu Pac-Man");
        alphabet.add("a perdu Pac-Man");
        alphabet.add("a été mangé par Pac-Man");
        alphabet.add("Super pac-gomme expire");

        ArrayList<Etat> ensembleEtats = new ArrayList<>();
        ensembleEtats.add(GoLabyrinthe);
        ensembleEtats.add(FollowPC);
        ensembleEtats.add(FleePC);
        ensembleEtats.add(returnBase);

    

        // ############ QUESTION 3

       



    // }
    
    }

}