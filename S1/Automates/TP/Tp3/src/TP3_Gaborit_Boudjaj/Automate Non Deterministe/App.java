import java.util.ArrayList;
import java.util.List;

public class App {
    public static void main(String[] args) {
        System.out.println("Hello, World!");


         // ==========================================
        // PARTIE AUTOMATE NON DETERMINISTE : Utilisation de la généricité pour apprendre et la travailler
        // Découverte du lisst of qui simplifie beaucoup la déclaration des listes
        // ==========================================

        Etat<Integer, Character> un = new Etat<>(false, 1, null);
        Etat<Integer, Character> deux = new Etat<>(false, 2, null);
        Etat<Integer, Character> trois = new Etat<>(true, 3, null);

        Transition<Integer, Character> transition1b2 = new Transition<>(un, deux, 'b');
        Transition<Integer, Character> transition2a2 = new Transition<>(deux, deux, 'a');
        Transition<Integer, Character> transition2a3 = new Transition<>(deux, trois, 'a');
        Transition<Integer, Character> transition3b2 = new Transition<>(trois, deux, 'b');
        Transition<Integer, Character> transition3b3 = new Transition<>(trois, trois, 'b');

        un.getEnsembleTransitions().add(transition1b2);

        deux.getEnsembleTransitions().add(transition2a2);
        deux.getEnsembleTransitions().add(transition2a3);

        trois.getEnsembleTransitions().add(transition3b2);
        trois.getEnsembleTransitions().add(transition3b3);

        ArrayList<Etat<Integer, Character>> etats = new ArrayList<>(List.of(un, deux, trois));
        Automate<Integer, Character> automate = new Automate<>(etats, un);

        // Question 2.2.1

        System.out.println("Question 2.2.1 : ");
        ArrayList<Character> mot1 = new ArrayList<>(List.of('b', 'a'));
        System.out.println("Le mot ba est reconnu : " + automate.reconnait(mot1));

        ArrayList<Character> mot2 = new ArrayList<>(List.of('b', 'a', 'b', 'b', 'a'));
        System.out.println("Le mot babba est reconnu : " + automate.reconnait(mot2));
    }

}