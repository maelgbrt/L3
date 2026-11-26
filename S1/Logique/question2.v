(****
 ** INFO501 : logique et informatique
 ** TP2
 ** Mario Super, groupe 3
 ****)


(* pour avoir le raisonnement par l'absurde
   (à n'utiliser que lorsque c'est vraiment nécessaire) *)
Require Import Classical_Prop.


Section question2.
  Variable P Q : Prop.

  Theorem et_1 : (P /\ Q) -> P.
  Proof.
  intro patate.
  destruct patate.
  assumption .
  Qed. 


  Theorem et_2 : (P /\ Q) -> Q.
  Proof.
  intro etape1.
  destruct etape1.
  assumption.
  Qed .

End question2.

Section question3.
  Variable P Q R : Prop.

  Theorem et_com : P /\ Q   ->   Q /\ P.
  Proof.
  intro clementine.
  destruct clementine.
  split .
  assumption .
  assumption .
  Qed . 


  Theorem ou_com : P \/ Q   <->   Q \/ P.
  Proof. 
  split .
  - intro cristinaCordula.
  destruct cristinaCordula.
  + right.
  assumption .
  + left.
  assumption.
  - intro phase2.
  destruct phase2.
  + right.
  assumption .
  + left .
  assumption .
  Qed .




  Theorem contraposition : (P -> Q)  ->  (~Q -> ~P).
  Proof.
  intro h1.
  intro h2.
  intro h3.
  apply h2.
  apply h1.
  assumption .
  Qed.


  Theorem distribution : (P \/ (Q /\ R))  ->  (P \/ Q) /\ (P \/ R).
  Proof.
  Admitted. 

End question3.


Section question4.
  (* première loi de de Morgan :  ¬(P ∨ Q) ⇔ ¬P ∧ ¬Q *)
  (* ... *)

End question4.

Section question5.
  (* BONUS *)
  (* deuxième loi de de Morgan :  P ∨ Q ⇔ ¬(¬P ∧ ¬Q) *)
  (* ... *)

  (* BONUS *)
  (* tiers exclu  ¬P ∨ P *)
  (* ... *)

  Qed.
End question5.


Section question6.
  Variable X : Set.
  Variable P Q : X -> Prop.

  Theorem pourtout_et : (forall x:X, (P x /\ Q x)) <-> (forall x : X, P x) /\ (forall x : X, Q x).
  Proof.
  Admitted. 


  Theorem existe_ou : (exists x:X, (P x \/ Q x)) <-> (exists x:X, P x) \/ (exists x:X, Q x).
  Proof.
  Admitted. 

End question6.


Section question7.
  (* troisième loi de de Morgan :  ¬(∃ x:X, P(x)) ⇔ ∀ x:X, ¬ P(x) *)
  (* ... *)

End question7.


Section question8.
  (* BONUS *)
  (* quatrième loi de de Morgan :  (∃ x:X, P(x)) ⇔ ¬(∀ x:X, ¬P(x)) *)
  (* ... *)

End question8.