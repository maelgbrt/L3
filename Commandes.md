
Question 1
`db.orders.find({},{commande_id : 1,client: 1})`

Question 2
`db.orders.find({},{commande_id : 1,client: 1,"produits.id_produit" : 1}) `

Question 3
`db.orders.find({},{commande_id : 1,client: 1,"produits.id_produit" : 1})`

Question 4
`db.orders.find({"produits.marque":'Samsung'}, { commande_id: 1, client: 1, "produits.id_produit": 1, "produits.nom": 1, "produits.marque": 1 } )`

Question 5 
`db.orders.find({"produits.marque":'Samsung'}, {} )`

Question 6
`td3> db.orders.find({"produits.marque":'Corsair'}, {"produits.attributs": 1,"produits.nom" : 1} )`

db.tuto.mapReduce(
   mapFunction1,
   reduceFunction1,
   { out: "map_reduce_example" }
)

