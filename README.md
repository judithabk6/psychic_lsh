# psychic_lsh

*Phase 1: Création du graphe*
Le but est de créer un fichier graphe qui contient : 
- N M L<-- Nombre de noeuds, Nombre de connections, Nombre de Labels
- Sur les lignes 1+i à 1+N : k entiers, les labels du noeuds i
- Sur les lignes 1+N+j à 1+N+M : 2 entiers, un flottant, décrivant une arête entre deux noeuds.

On peut le faire en whatever. Ça peut dépendre du dataset. On s'en fout. Le but c'est d'avoir le fichier qui décrit le graphe, prêt à servir, le plus vite possible.

*Phase 2: Quantization*
Le code C++ est un serveur Thrift, qui répond à une requete _quantizeGraph(string graphFile, string method, vector<double?> params)_ en renvoyant la matrice du graphe quantized et les clusters qu'il a créé.

*Phase 3: Évaluation*
En Python, le client Thrift appelle la quantization comme il veut, et utilise les résultats pour calculer HFS, généraliser les résultats aux graphes complets et faire des jolis plots. On aimerait avoir : 
- Mean precision at 15% recall (comme dans https://cs.nyu.edu/~fergus/papers/fwt_ssl.pdf)
- Running time
- Precision / recall (pour un nombre fixe d'exemples labellisés)

À chaque fois, on veut comparer : Fergus, Nous, Charikar (http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.87.3954&rep=rep1&type=pdf)

On pourra éventuellement essayer plusieurs méthodes de LSH.