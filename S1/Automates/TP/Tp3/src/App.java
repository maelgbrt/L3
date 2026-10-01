import java.util.ArrayList;

public class App {
    public static void main(String[] args) {
            System.out.println("Hello, World!");

        Etat un = new  Etat(false,"parcouru",null);
        Etat deux = new  Etat(false, "poursuit",null);
        Etat trois = new  Etat(true, "mort",null);
        
        Transition trans1b2 = new Transition(un,deux, "mot1");        
        Transition trans2a2= new Transition(deux,deux, "mot2");
        Transition trans2b3 = new Transition(deux,trois, "mot2");
        Transition trans3c2 = new Transition(trois,deux, "mot2");
        Transition trans3b3 = new Transition(trois,trois, "mot1");


        ArrayList<Transition> Transition1 = new  ArrayList<>();
        ArrayList<Transition> Transition2 = new  ArrayList<>();
        ArrayList<Transition> Transition3 = new  ArrayList<>();

        Transition1.add(trans1b2);
        Transition2.add(trans2a2);
        Transition2.add(trans2b3);
        Transition3.add(trans3c2);
        Transition3.add(trans3b3);

        un.ensembleTransitions.addAll(Transition1);
        deux.ensembleTransitions.addAll(Transition2);
        trois.ensembleTransitions.addAll(Transition3);

        ArrayList<String> alphabet = new ArrayList<>();
        alphabet.add("mot1");
        alphabet.add("mot2");
        alphabet.add("mot3");
        alphabet.add("mot4");

        ArrayList<Etat> ensembleEtats = new ArrayList<>();
        ensembleEtats.add(un);
        ensembleEtats.add(deux);
        ensembleEtats.add(trois);

    

        // ############ QUESTION 3

        Automate Question3 = new Automate(alphabet,ensembleEtats,un);
        System.out.println(Question3.reconnait(alphabet));


    // }
    
    }

}