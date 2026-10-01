import java.util.ArrayList;

public class App2 {
    public static void main(String[] args) {
            System.out.println("Hello, World!");

        Etat un = new  Etat(false,"un",null);
        Etat deux = new  Etat(false, "deux",null);
        Etat trois = new  Etat(true, "trois",null);
        
        Transition trans1b2 = new Transition(un,deux, "b");        
        Transition trans2a2= new Transition(deux,deux, "a");
        Transition trans2b3 = new Transition(deux,trois, "b");
        Transition trans3c2 = new Transition(trois,deux, "c");
        Transition trans3b3 = new Transition(trois,trois, "b");


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
        alphabet.add("a");
        alphabet.add("b");
        alphabet.add("c");

        ArrayList<Etat> ensembleEtats = new ArrayList<>();
        ensembleEtats.add(un);
        ensembleEtats.add(deux);
        ensembleEtats.add(trois);

    

        // ############ QUESTION 3

        Automate Question3 = new Automate(alphabet,ensembleEtats,un);

        ArrayList<String> mot1 = new ArrayList<>();
        mot1.add("b");
        mot1.add("b");
        mot1.add("b");

        System.out.println(Question3.reconnait(mot1));

        ArrayList<String> mot2 = new ArrayList<>();
        mot2.add("b");
        mot2.add("a");
        mot2.add("b");

        System.out.println(Question3.reconnait(mot2));

    //    ArrayList<Character> mot3 = new ArrayList<>();
    //     mot3.add("b");
    //     mot3.add("a");
    //     mot3.add("b");
    //     mot3.add("c");
    //     mot3.add("b");

    //     System.out.println(Question3.reconnait(mot3));


        ArrayList<String> mot4 = new ArrayList<>();
        mot2.add("a");
        mot2.add("a");
        mot2.add("b");

        System.out.println(Question3.reconnait(mot4));  // false
    // }
    
    }

}