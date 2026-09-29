import java.util.ArrayList;

public class App {
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");

        Etat un = new  Etat(false,"un",null);
        Etat deux = new  Etat(false, "deux",null);
        Etat trois = new  Etat(true, "trois",null);
        
        Transition trans1b2 = new Transition(un,deux, 'b');        
        Transition trans2a2= new Transition(deux,deux, 'a');
        Transition trans2b3 = new Transition(deux,trois, 'b');
        Transition trans3c2 = new Transition(trois,deux, 'c');
        Transition trans3b3 = new Transition(trois,trois, 'b');


        ArrayList<Transition> Transition1 = new  ArrayList<>();
        ArrayList<Transition> Transition2 = new  ArrayList<>();
        ArrayList<Transition> Transition3 = new  ArrayList<>();

        Transition1.add(trans1b2);
        Transition2.add(trans2a2);
        Transition2.add(trans2b3);
        Transition3.add(trans3c2);
        Transition3.add(trans3b3);



        un.ensembleTransitions.add(Transition1);
        deux.ensembleTransitions.add(Transition2);
        trois.ensembleTransitions.add(Transition3);



        ArrayList<Character> alphabet = new ArrayList<>();
        alphabet.add('a');
        alphabet.add('b');
        alphabet.add('c');

        ArrayList<Etat> ensembleEtats = new ArrayList<>();
        ensembleEtats.add(un);
        ensembleEtats.add(deux);
        ensembleEtats.add(trois);

        Automate Question3 = new Automate(alphabet,ensembleEtats,un);



        // boolean reponse = Question3.reconnait(alphabet);
    }
}
