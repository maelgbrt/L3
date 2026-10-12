import java.util.ArrayList;

public class App {
    public static void main(String[] args) {



        // ==========================================
        // PARTIE AUTOMATE DETERMINISTE : On a décidé de ne pas utiliser la généicité ici
        // car cela ne nous semblait pas pertinent. Nous supprimerons par la suite(la partie 2 : 
        // automate non deterministe) des paramètres et des listes qui ne sont au final pas utile (alphabet)
        // ==========================================


        // ==========================================
        // PARTIE 1 : Automate lettres (bbb, bab, babcb)
        // ==========================================

        // Création des 3 états (l'état "trois" est l'état acceptant)
        Etat un = new Etat(false, "un", null);
        Etat deux = new Etat(false, "deux", null);
        Etat trois = new Etat(true, "trois", null);
        
        // Définition des transitions entre les états
        Transition trans1b2 = new Transition(un, deux, "b");        
        Transition trans2a2 = new Transition(deux, deux, "a");
        Transition trans2b3 = new Transition(deux, trois, "b");
        Transition trans3c2 = new Transition(trois, deux, "c");
        Transition trans3b3 = new Transition(trois, trois, "b");

        // Regroupement des transitions par état
        ArrayList<Transition> Transition1 = new ArrayList<>();
        ArrayList<Transition> Transition2 = new ArrayList<>();
        ArrayList<Transition> Transition3 = new ArrayList<>();

        Transition1.add(trans1b2);
        Transition2.add(trans2a2);
        Transition2.add(trans2b3);
        Transition3.add(trans3c2);
        Transition3.add(trans3b3);

        // Association des listes de transitions à chaque état
        un.ensembleTransitions.addAll(Transition1);
        deux.ensembleTransitions.addAll(Transition2);
        trois.ensembleTransitions.addAll(Transition3);

        // Liste de tous les états de l'automate
        ArrayList<Etat> ensembleEtatsQ1 = new ArrayList<>();
        ensembleEtatsQ1.add(un);
        ensembleEtatsQ1.add(deux);
        ensembleEtatsQ1.add(trois);

        // Alphabet accepté : a, b, c
        ArrayList<String> alphabetQ1 = new ArrayList<>();
        alphabetQ1.add("a");
        alphabetQ1.add("b");
        alphabetQ1.add("c");

        // Instanciation de l'automate avec "un" comme état de départ
        Automate Question3 = new Automate(alphabetQ1, ensembleEtatsQ1, un);

        // Test 1 : mot "bbb" (parcours : un -> deux -> trois -> trois)
        ArrayList<String> test_bbb = new ArrayList<>();
        test_bbb.add("b");
        test_bbb.add("b");
        test_bbb.add("b");
        System.out.println("Le mot bbb est reconnu : " + Question3.reconnait(test_bbb));

        // Test 2 : mot "bab" (parcours : un -> deux -> deux -> trois)
        ArrayList<String> test_bab = new ArrayList<>();
        test_bab.add("b");
        test_bab.add("a");
        test_bab.add("b");
        System.out.println("Le mot bab est reconnu : " + Question3.reconnait(test_bab));

        // Test 3 : mot "babcb" (parcours : un -> deux -> deux -> trois -> deux -> trois)
        ArrayList<String> test_babcb = new ArrayList<>();
        test_babcb.add("b");
        test_babcb.add("a");
        test_babcb.add("b");
        test_babcb.add("c");
        test_babcb.add("b");
        System.out.println("Le mot babcb est reconnu : " + Question3.reconnait(test_babcb));

        // ==========================================
        // PARTIE 2 : Automate Pac-Man (comportement fantôme)
        // ==========================================

        System.out.println("\n---------------Pac Man--------------");

        // Création des 4 états du fantôme
        Etat GoLabyrinthe = new Etat(false, "Parcours le labyrinthe", null);
        Etat FollowPC = new Etat(false, "Poursuit Pac-Man", null);
        Etat FleePC = new Etat(false, "Fuit Pac-Man", null);
        Etat returnBase = new Etat(false, "Retourne à la base", null);
        
        // Définition des actions / transitions du fantôme
        Transition FindBase = new Transition(returnBase, GoLabyrinthe, "atteint la base");        
        Transition LosePC = new Transition(FollowPC, GoLabyrinthe, "a perdu Pac-Man");
        Transition SeePC = new Transition(GoLabyrinthe, FollowPC, "a vu Pac-Man");
        Transition EatbyPC = new Transition(FleePC, returnBase, "a été mangé par Pac-Man");
        Transition EatGomme = new Transition(FollowPC, FleePC, "Pac-Man mange une super pac-gomme");
        Transition EatGomme2 = new Transition(GoLabyrinthe, FleePC, "Pac-Man mange une super pac-gomme");
        Transition ExpirePacGomme = new Transition(FleePC, GoLabyrinthe, "Super pac-gomme expire");

        // Regroupement des transitions sortantes de chaque état
        ArrayList<Transition> TransitionGoLabyrinthe = new ArrayList<>();
        ArrayList<Transition> TransitionFollowPC = new ArrayList<>();
        ArrayList<Transition> TransitionFleePC = new ArrayList<>();
        ArrayList<Transition> TransitionReturnBase = new ArrayList<>();

        TransitionGoLabyrinthe.add(SeePC);
        TransitionGoLabyrinthe.add(EatGomme2);
        TransitionFollowPC.add(LosePC);
        TransitionFollowPC.add(EatGomme);
        TransitionFleePC.add(ExpirePacGomme);
        TransitionFleePC.add(EatbyPC);
        TransitionReturnBase.add(FindBase);

        // Association des transitions aux états correspondants
        GoLabyrinthe.ensembleTransitions.addAll(TransitionGoLabyrinthe);
        FollowPC.ensembleTransitions.addAll(TransitionFollowPC);
        FleePC.ensembleTransitions.addAll(TransitionFleePC);
        returnBase.ensembleTransitions.addAll(TransitionReturnBase);

        // Alphabet des événements possibles dans le jeu
        ArrayList<String> alphabet = new ArrayList<>();
        alphabet.add("atteint la base");
        alphabet.add("Pac-Man mange une super pac-gomme");
        alphabet.add("a vu Pac-Man");
        alphabet.add("a perdu Pac-Man");
        alphabet.add("a été mangé par Pac-Man");
        alphabet.add("Super pac-gomme expire");

        // Liste de tous les états du jeu
        ArrayList<Etat> ensembleEtats = new ArrayList<>();
        ensembleEtats.add(GoLabyrinthe);
        ensembleEtats.add(FollowPC);
        ensembleEtats.add(FleePC);
        ensembleEtats.add(returnBase);

        // Création de l'automate avec GoLabyrinthe comme état initial
        Automate AutomatePC = new Automate(alphabet, ensembleEtats, GoLabyrinthe);

        // ==========================================
        // TESTS DE L'AUTOMATE PAC-MAN
        // ==========================================

        // Scénario 1 : Le fantôme voit Pac-Man puis le perd
        System.out.println("\n--- SCÉNARIO 1 : Chasse puis perte de vue ---");
        ArrayList<String> test1 = new ArrayList<>();
        test1.add("a vu Pac-Man");
        test1.add("a perdu Pac-Man");
        System.out.println("Séquence valide : " + AutomatePC.reconnait(test1));

        // Scénario 2 : Super gomme mangée, fantôme dévoré, retour à la base
        System.out.println("\n--- SCÉNARIO 2 : Pris au piège par une super pac-gomme ---");
        ArrayList<String> test2 = new ArrayList<>();
        test2.add("a vu Pac-Man");
        test2.add("Pac-Man mange une super pac-gomme");
        test2.add("a été mangé par Pac-Man");
        test2.add("atteint la base");
        System.out.println("Cycle complet de capture : " + AutomatePC.reconnait(test2));

        // Scénario 3 : Le fantôme fuit jusqu'à la fin de l'effet de la super gomme
        System.out.println("\n--- SCÉNARIO 3 : Fuite réussie (expiration) ---");
        ArrayList<String> test3 = new ArrayList<>();
        test3.add("Pac-Man mange une super pac-gomme");
        test3.add("Super pac-gomme expire");
        System.out.println("Survie à la super gomme : " + AutomatePC.reconnait(test3));

        // Scénario 4 : Enchaînement impossible (doit renvoyer false)
        System.out.println("\n--- SCÉNARIO 4 : Transition impossible (doit échouer) ---");
        ArrayList<String> testInvalide = new ArrayList<>();
        testInvalide.add("a été mangé par Pac-Man");
        System.out.println("Action impossible : " + AutomatePC.reconnait(testInvalide));

        // Scénario 5 : Événement inexistant dans l'alphabet (doit renvoyer false)
        System.out.println("\n--- SCÉNARIO 5 : Mot inconnu hors alphabet ---");
        ArrayList<String> testHorsAlphabet = new ArrayList<>();
        testHorsAlphabet.add("Pac-Man saute un mur");
        System.out.println("Hors alphabet : " + AutomatePC.reconnait(testHorsAlphabet));
    }
}