#!/usr/bin/env python3

import sys

#
# NOTE: ce fichier utilise des annotations de type pour les fonctions et leurs
# paramètres. Vous pouvez vérifier que les annotations sont cohérentes avec le
# code en utilisant l'outil mypy.
#
from typing import Tuple, List, Optional, Iterator, Dict, TextIO

verbose: int = 0


###
# version naïve
def solve(F: List[List[int]], sol: List[int], bcp: bool = False) -> Optional[List[int]]:
    """recherche, récursivement, une solution pour un problème SAT
      ``F`` contient la formule considérée, en FNC (liste de listes de nombres)
      ``sol`` contient la solution partielle courante (liste de littéraux).
      L'argument bcp (que vous pouvez ignorer pendant toute la première partie
      du TP) permet d'activer l'optimisation de propagation des clauses
      unitaires.
      La fonction renvoie
        - soit None si la formule n'est pas satisfiable,
        - soit une solution (liste de littéraux) satisfaisant la formule.
    """

    # si F est vide, il n'y a aucune clause et la formule est satisfaite avec
    # la solution courante
    if not F:
        return sol

    # si F contient la clause vide, cette clause s'évalue à FAUX et la formule
    # n'est donc pas satisfaite avec la solution courante
    if [] in F:
        return None

    # on prend le premier littéral de la première clause
    lit = F[0][0]
    # on essaie les 2 valeurs possibles pour ce littéral
    return(solve(simplify_formula(F, lit), sol+[lit], bcp=bcp) or
           solve(simplify_formula(F, -lit), sol+[-lit], bcp=bcp))
    # REMARQUE : on utilise ici le fait que les listes non vides de Python
    # sont considérées comme VRAIES alors que la liste vide (ainsi que None)
    # est FAUSSE. On utilise aussi le fait que si le membre gauche d'un "or"
    # s'évalue à VRAI, Python ne calcule pas le membre droit...



def simplify_formula(F: List[List[int]], lit: int) -> List[List[int]]:
    """renvoie la formule ``F`` simplifiée lorsqu'on suppose que le littéral
       ``lit`` est vrai :
      - supprime les clauses qui contiennent ``lit`` (elle sont vraies)
      - supprime les littéraux ``-lit`` dans les autres clauses (ce littéral
        est faux)
    """
    simplified_F: List[List[int]] = []

    for cl in F:

        if lit in cl or -lit in cl: 
                #supprime la clause entière sinon
            if -lit in cl :
                nv_clause: List[int] = []
                for i in cl :
                    if i != -lit:
                        nv_clause.append(i)
                simplified_F.append(nv_clause)
        else :
            simplified_F.append(cl)

    return simplified_F


###
# fonction de tests
def main_test(F: List[List[int]], args: List[str]) -> int:
    """fonction appelée avec l'option `-T` de la ligne de commandes
      - la formule `F` est lue dans le fichier donné comme premier argument
        de la ligne de commandes
      - `args` est un tableau de chaines contenant les arguments suivants de
         la ligne de commandes"""
    lit = int(args[0])
    print(f"simplification avec {lit}")
    print("avant :", F)
    Fs = simplify_formula(F, lit)
    print("après :", Fs)
    return 0


###
# optimisation pour avoir un algo de style "DPLL
def BCP(F: List[List[int]]) -> Tuple[List[List[int]], List[int]]:
    """simplifie la formule avec la propagation des clauses unitaires
    La fonction renvoie une paire contenant la formule simplifiée et la liste
    des littéraux simplifiés.
    """
    sol: List[int] = []
    ...    # TODO
    return F, sol


##############################################################################
##############################################################################
# ************************************************************************** #
# * normalement, vous n'avez pas besoin de modifier la suite du fichier... * #
# ************************************************************************** #
##############################################################################
##############################################################################


#########################
# fonctions utilitaires
def message(*args, **kwargs) -> None:       # type: ignore
    print(*args, **kwargs, file=sys.stderr)


def parse_DIMACS(filename: str = "") -> List[List[int]]:
    """lit un fichier DIMACS dans un fichier (ou l'entrée standard) et renvoie
    une liste de listes de nombres
    Chaque nombre représente un littéral,
    chaque liste représente une clause,
    la liste externe représente la formule.

    Remarque : la ligne 'p cnf <nb_var> <nb_clauses>' est ignorée.
    """
    if filename and filename != "-":
        input_file: Iterator[str] = open(filename)
    else:
        input_file = sys.stdin

    F = []          # la formule finale
    for line in input_file:
        line = line.strip()
        if line.startswith("c"):    # commentaire
            continue
        if line.startswith("p"):    # paramètres du problème, ignorés
            continue
        if not line:
            continue
        cl = list(map(int, line.split()))
        last = cl.pop()
        assert last == 0
        assert 0 not in cl
        F.append(cl)
    return F


def save_DIMACS(F: List[List[int]], filename: str = "", header: str = "") -> int:
    """écrit la formule au format DIMACS (dans un fichier ou sur la sortie
    standard)"""
    if filename and filename != "-":
        output_file: TextIO = open(filename, mode="w")
    else:
        output_file = sys.stdout

    if header:
        for lit in header.split("\n"):
            output_file.write(f"c {lit}\n")

    if TRANSLATION:
        output_file.write("c translation table for variable names: \n")
        for i in range(1, len(TRANSLATION)):
            output_file.write(f"c     {TRANSLATION[i]} -> {i}\n")

    nb_var, nb_clauses, _ = parameters(F)
    output_file.write(f"p cnf {nb_var} {nb_clauses}\n")

    for cl in F:
        for lt in cl:
            output_file.write(f"{lt} ")
        output_file.write("0\n")

    return 0


def parse_SAT(filename: str = "") -> Tuple[List[List[int]], Dict[str,int], List[str]]:
    """lit un fichier au format 'sat' dans un fichier (ou l'entrée standard)
    et renvoie une liste de listes de nombres représentant la formule, ainsi
    que :
      - un dictionnaire qui donne, pour chaque variable textuelle, son numéro
      - une liste qui donne, pour chaque indice de variable, son texte
    """
    import re

    if filename and filename != "-":
        input_file: Iterator[str] = open(filename)
    else:
        input_file = sys.stdin

    index = {"": 0}     # dictionnary: for each textual variable, gives its index
    text = [""]         # list: for each index, give the corresponding textual variable

    F = []          # la formule finale
    i = 0
    for line in input_file:
        i += 1
        # if (i % 1000000 == 0):
        #     message(f" {i} clauses read")
        # elif (i % 10000 == 0):
        #     message(".", flush=True, end="")

        line = line.strip()
        if line.startswith("#"):    # commentaire
            continue
        if not line:                # ligne vide
            continue
        variables = line.split()
        cl = []
        for v in variables:
            sign = 1
            if v.startswith("-"):
                sign = -1
                v = v[1:]
            if not re.fullmatch(r"[A-Za-z0-9_@]+", v):
                message(f"*** invalid variable name: '{v}' on line {i}")
                sys.exit(3)

            x = index.get(v)
            if x is None:
                x = len(index)
                index[v] = x
                text.append(v)
            cl.append(sign * x)
        F.append(cl)
    return F, index, text


def print_lit(lit: int) -> None:
    """affiche un littéral"""
    if TRANSLATION is None:
        print(lit, end="")
    else:
        x = abs(lit)
        s = "" if lit > 0 else "-"
        v = TRANSLATION[x]
        print(f"{s}{v}", end="")


def print_clause(cl: List[int]) -> None:
    """affiche une clause (liste)"""
    print("[", end="")
    sep = ''
    for lit in cl:
        print(sep, end="")
        sep = ", "
        print_lit(lit)
    print("]", end="")


def print_CNF(F: List[List[int]]) -> None:
    """affiche une formule FNC (liste de listes)"""
    print("[ ", end="")
    sep = ''
    for cl in F:
        print(sep, end="")
        sep = ", "
        print_clause(cl)
    print(" ]", end="")


def print_sol(sol: List[int]) -> None:
    """affiche une solution"""
    if TRANSLATION is None:
        sol = sorted(sol, key=abs)  # on trie les littéraux par ordre croissant
        for i in range(len(sol)):
            print(sol[i], end=" ")
        print(0)
    else:
        for i in range(len(sol)):
            lit = sol[i]
            if lit < 0 and EXCLUDE_NEGATIVE_LIT:
                continue
            x = abs(lit)
            s = "" if lit > 0 else "-"
            v = TRANSLATION[x]
            if not v.startswith("_"):   # do not show literals starting with _
                print(f"{s}{v}", end=" ")
        print()


def parameters(F: List[List[int]]) -> Tuple[int, int, int]:
    """renvoie le nombre de variables, le nombre de clauses et le nombre de
    littéraux d'une formule en FNC"""
    nb_clauses = len(F)
    last_var = 0
    nb_lit = 0
    for cl in F:
        last_var = max(last_var, max(map(abs, cl)))
        nb_lit += len(cl)

    return last_var, nb_clauses, nb_lit


def randomize_formula(F: List[List[int]]) -> None:
    """mélange les clauses d'une formule et les littéraux de chaque clause"""
    from random import shuffle
    shuffle(F)
    for cl in F:
        shuffle(cl)


def check_sol(F: List[List[int]], sol: List[int]) -> bool:
    S = {}
    for lit in sol:
        S[lit] = True
        S[-lit] = False
    return all((any((S.get(lit, False) for lit in cl)) for cl in F))


###
# les fonctions principales
def main(F: List[List[int]], bcp: bool = False) -> None:
    """fonction principale pour la résolution naïve"""

    if verbose > 1:
        print_CNF(F)
        print()

    solution = solve(F, [], bcp)
    if solution is not None:
        print("SATISFIABLE")
        print_sol(solution)
        assert check_sol(F, solution)
        sys.exit(0)
    else:
        print("UNSATISFIABLE")
        sys.exit(1)


def main_all(F: List[List[int]], bcp: bool = False) -> None:
    """fonction principale pour le calcul naïf de toutes les solutions"""
    n = 0
    while True:
        S = solve(F, [], bcp)
        if S is None:
            break
        n += 1
        print_sol(S)
        assert check_sol(F, S)
        F.append([-lit for lit in S])

    if n == 0:
        print("UNSATISFIABLE")
        sys.exit(1)
    else:
        print(f"SATISFIABLE: {n} solution(s) found")
        sys.exit(0)


###


def help(exe: str) -> None:
    print(f"utilisation {exe} [options] [FICHIER_ENTREE [FICHIER_SORTIE]] ")
    print("""
Si FICHIER_ENTREE n'est pas donné, la formule sera lue sur l'entrée standard.
Si FICHIER_SORTIE n'est pas donné, le résultat sera affiché sur la sortie standard.

Si le format d'entrée n'est pas précisé, la formule est lue :
  - au format 'SAT' si le fichier a l'extension '.sat'
  - au format 'DIMACS' si le fichier a l'extension '.cnf'
Dans les autres cas, (par exemple, lorsque la formule est lue sur l'entrée
standard), le format 'SAT' est utilisé.

options disponibles :
  -N  /  --naive                    utilise la variante récursive naive de l'algorithme
  -D  /  --DPLL                     utilise la variante récursive de l'algorithme DPLL
  -A  /  --all                      utilise la variante qui affiche toutes les solutions
  -X  /  --exclude-negative-lit     n'affiche pas les littéraux négatifs dans les solutions
  -r  /  --randomize                mélange la formule avant de lancer l'algorithme
  -T  /  --test                     lance la fonction de tests, sans recherche de solution
  -v  /  --verbose                  affiche quelques informations supplémentaires sur la formule
  -C  /  --convert                  convertit la formule au format DIMACS, sans recherche de solution
  -s  /  --sat                      force le format 'sat' pour lire la formule
  -d  /  --dimacs                   force le format 'DIMACS' pour lire la formule
  -P  /  --profile                  lance simplesat en mode "profiling"
""")


if __name__ == "__main__":
    from getopt import gnu_getopt, GetoptError
    from sys import argv, exit
    import sys

    short_options = "NADCTsdrvhXP"
    long_options = ["naive", "all", "DPLL", "convert", "test", "sat", "dimacs",
                    "randomize", "verbose", "help", "exclude-negative-lit", "profile"]

    try:
        opts, args = gnu_getopt(argv[1:], short_options, long_options)
    except GetoptError as err:
        message(err)
        help(argv[0])
        sys.exit(2)

    bcp = False
    all_solutions = False
    randomize = False
    test = False
    convert_formula = False
    verbose = 0
    profiling = False
    input_filename = "-"        # stdin
    file_format = None
    TRANSLATION = None
    EXCLUDE_NEGATIVE_LIT = False
    output_filename = "-"       # stdout

    for o, a in opts:
        if o in ["-h", "--help"]:
            help(argv[0])
            sys.exit(0)
        elif o in ["-N", "--naive"]:
            bcp = False
        elif o in ["-A", "--all"]:
            all_solutions = True
        elif o in ["-D", "--DPLL"]:
            bcp = True
        elif o in ["-C", "--convert"]:
            convert_formula = True
            test = False
        elif o in ["-T", "--test"]:
            test = True
            convert_formula = False
        elif o in ["-r", "--randomize"]:
            randomize = True
        elif o in ["-v", "--verbose"]:
            verbose += 1
        elif o in ["-s", "--sat"]:
            file_format = "SAT"
        elif o in ["-d", "--dimacs"]:
            file_format = "DIMACS"
        elif o in ["-X", "--exclude-negative-lit"]:
            EXCLUDE_NEGATIVE_LIT = True
        elif o in ["-P", "--profile"]:
            profiling = True
        else:
            message("You shouldn't see this!")
            sys.exit(3)

    if len(args) == 0 and sys.stdin.isatty():
        message(">>> no filename: read SAT formula from stdin and write result on stdout")
        message(f">>> use  {argv[0]} --help  for help")

    if len(args) > 2 and not test:
        message("too many arguments")
        sys.exit(1)

    if len(args) >= 1:
        input_filename = args.pop(0)
    if len(args) >= 1 and not test:
        output_filename = args[0]

    if file_format is None:
        if not input_filename:
            file_format = "SAT"
        else:
            if input_filename.lower().endswith(".sat"):
                file_format = "SAT"
            elif input_filename.lower().endswith(".cnf") or input_filename.lower().endswith(".dimacs"):
                file_format = "DIMACS"
            else:
                file_format = "SAT"

    # ???
    # if output_filename and output_filename != "-":
    #     sys.stdout = open(output_filename, mode="w")

    if verbose > 1:
        message(f">>> formula is read from {input_filename if input_filename else 'stdin'}, in {file_format} format")
        if not test:
            if not bcp:
                message(">>> the naive algorithm will be used")
            else:
                message(">>> the DPLL algorithm will be used")
            if all_solutions:
                message(">>> all solutions will be computed")
            message(f">>> the result will be output to {output_filename if output_filename else 'stdout'}")

    if file_format == "DIMACS":
        F = parse_DIMACS(input_filename)
    elif file_format == "SAT":
        F, _, TRANSLATION = parse_SAT(input_filename)

    if verbose > 0:
        nb_var, nb_clauses, nb_lit = parameters(F)
        message(f">>> the formula contains {nb_var} variables and {nb_clauses} clauses, "
                f"for a total of {nb_lit} literals")

    if randomize:
        if verbose > 1:
            message(">>> randomizing the formula...")
        randomize_formula(F)

    if test:
        sys.exit(main_test(F, args))
    if convert_formula:
        sys.exit(save_DIMACS(F))

    if all_solutions:
        if profiling:
            import cProfile
            cProfile.runctx("main_all(F, bcp)", {}, locals(), sort="tottime")
        else:
            main_all(F, bcp)
    else:
        if profiling:
            import cProfile
            cProfile.runctx("main(F, bcp)", {}, locals(), sort="tottime")
        else:
            main(F, bcp)