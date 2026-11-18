Question 1 : Affichez tout les types de publication.
`db.dblp.distinct("type")`
Réponse:
```
[
  'article',
  'book',
  'incollection',
  'inproceedings',
  'phdthesis',
  'proceedings',
  'www'
]
```

Question 2 : Afficher le titre de tout les articles depuis 2002

`db.dblp.find( { mdate: { $gt: "2002-01-01" } } )`
Réponse:
```
[
  {
    _id: ObjectId('595c2c8da7986c08721a8123'),
    mdate: '2012-06-09',
    author: [ 'Johanne Higgins' ],
    _key: 'homepages::78::11500',
    title: 'Home Page',
    type: 'www'
  },
  {
    _id: ObjectId('595c2c48a7986c0872f8ba53'),
    mdate: '2017-05-25',
    author: [ 'Gabriele Moser', 'Michaela De Martino', 'Sebastiano B. Serpico' ],
    ee: 'https://doi.org/10.1109/IGARSS.2013.6723567',
    booktitle: 'IGARSS',
    title: 'A multiscale contextual approach to change detection in multisensor VHR remote sensing images.',
    pages: '3435-3438',
    url: 'db/conf/igarss/igarss2013.html#MoserMS13',
    year: '2013',
    type: 'inproceedings',
    _key: 'conf::igarss::MoserMS13',
    crossref: [ 'conf::igarss::2013' ]
  },
  {
    _id: ObjectId('595c2bfda7986c0872d9750e'),
    ee: 'http://doi.acm.org/10.1145/2696863',
    number: '1',
    year: '2015',
    mdate: '2015-01-27',
    author: [ 'Ron Wakkary', 'Erik Stolterman' ],
    type: 'article',
    journal: 'Interactions',
    volume: '22',
    pages: '5',
    url: 'db/journals/interactions/interactions22.html#WakkaryS15',
    title: 'WELCOME: HCI is everywhere.',
    _key: 'journals::interactions::WakkaryS15'
  },
  {
    _id: ObjectId('595c2c9ca7986c087226d3e9'),
    mdate: '2015-07-30',
    author: [ 'Yezhang Tu' ],
    _key: 'homepages::166::0268',
    title: 'Home Page',
    type: 'www'
  },
  {
    _id: ObjectId('595c2c6fa7986c0872096044'),
    mdate: '2017-05-23',
    author: [ 'Martin Gaitzsch' ],
    ee: 'https://doi.org/10.1007/978-3-540-69962-0_23',
    booktitle: 'KiVS',
    title: 'Benutzerorientierte Leistungs- und Verfgbarkeitsbewertung von Internetdiensten am Beispiel des Portals hamburg.de.',
    pages: '267-274',
    url: 'db/conf/kivs/kivs2007.html#Gaitzsch07',
    year: '2007',
    type: 'inproceedings',
    _key: 'conf::kivs::Gaitzsch07',
    crossref: [ 'conf::kivs::2007' ]
  },
  {
    _id: ObjectId('595c2c87a7986c087215a2ea'),
    mdate: '2010-11-03',
    author: [ 'M. V. Migueles' ],
    _key: 'homepages::05::8658',
    title: 'Home Page',
    type: 'www'
  },
  {
    _id: ObjectId('595c2c81a7986c0872107abb'),
    mdate: '2010-12-01',
    author: [ 'Zahra S. Razaee' ],
    _key: 'homepages::14::8773',
    title: 'Home Page',
    type: 'www'
  },
  {
    _id: ObjectId('595c2c59a7986c0872002043'),
    mdate: '2017-05-24',
    author: [ 'Injoon Hong', 'Seongwook Park', 'Junyoung Park', 'Hoi-Jun Yoo' ],
    ee: 'https://doi.org/10.1109/ASSCC.2015.7387453',
    booktitle: 'A-SSCC',
    title: 'A 1.9nJ/pixel embedded deep neural network processor for high speed visual attention in a mobile vision recognition SoC.',
    pages: '1-4',
    url: 'db/conf/asscc/asscc2015.html#HongPPY15',
    year: '2015',
    type: 'inproceedings',
    _key: 'conf::asscc::HongPPY15',
    crossref: [ 'conf::asscc::2015' ]
  },
  {
    _id: ObjectId('595c2c87a7986c0872157a3b'),
    mdate: '2014-01-11',
    author: [ 'Vincent Faucher' ],
    _key: 'homepages::139::3982',
    title: 'Home Page',
    type: 'www'
  },
  {
    _id: ObjectId('595c2c2aa7986c0872ecfff8'),
    ee: 'https://doi.org/10.1080/01449290500222009',
    number: '3',
    year: '2006',
    mdate: '2017-05-20',
    author: [ 'Pei-Luen Patrick Rau', 'Jenwen Chen', 'Duye Chen' ],
    type: 'article',
    journal: 'Behaviour & IT',
    volume: '25',
    pages: '253-261',
    url: 'db/journals/behaviourIT/behaviourIT25.html#RauCC06',
    title: 'A study of presentations of mobile web banners for location-based information and entertainment information websites.',
    _key: 'journals::behaviourIT::RauCC06'
  },
  {
    _id: ObjectId('595c2c76a7986c08720c6206'),
    mdate: '2017-05-24',
    author: [ 'Koichi Kurumatani', 'Azuma Ohuchi' ],
    ee: 'https://doi.org/10.1007/3-540-45548-5_23',
    booktitle: 'JSAI Workshops',
    title: 'World Trade League as a Standard Problem for Multi-agent Economics - Concept and Background.',
    pages: '208-217',
    url: 'db/conf/jsai/jsai2001.html#KurumataniO01',
    year: '2001',
    type: 'inproceedings',
    _key: 'conf::jsai::KurumataniO01',
    crossref: [ 'conf::jsai::2001' ]
  },
  {
    _id: ObjectId('595c2c69a7986c087206c863'),
    mdate: '2015-01-03',
    author: [ 'Steven J. Castellucci', 'Robert J. Teather', 'Andriy Pavlovych' ],
    ee: 'http://doi.acm.org/10.1145/2491367.2491373',
    booktitle: 'SUI',
    title: 'Novel metrics for 3D remote pointing.',
    pages: '17-20',
    url: 'db/conf/sui/sui2013.html#CastellucciTP13',
    year: '2013',
    type: 'inproceedings',
    _key: 'conf::sui::CastellucciTP13',
    crossref: [ 'conf::sui::2013' ]
  },
  {
    _id: ObjectId('595c2bf7a7986c0872d6c302'),
    ee: [
      'https://doi.org/10.1109/69.846289',
      'http://doi.ieeecomputersociety.org/10.1109/69.846289'
    ],
    number: '3',
    year: '2000',
    mdate: '2017-05-20',
    author: [ 'Eui-Hong Han', 'George Karypis', 'Vipin Kumar' ],
    type: 'article',
    journal: 'IEEE Trans. Knowl. Data Eng.',
    volume: '12',
    pages: '377-352',
    url: 'db/journals/tkde/tkde12.html#HanKK00',
    title: 'Scalable Parallel Data Mining for Association Rules.',
    _key: 'journals::tkde::HanKK00'
  },
  {
    _id: ObjectId('595c2c6ca7986c0872080887'),
    mdate: '2017-05-24',
    author: [ 'Scott Pakin' ],
    ee: 'https://doi.org/10.1109/HPEC.2016.7761637',
    booktitle: 'HPEC',
    title: 'A quantum macro assembler.',
    pages: '1-8',
    url: 'db/conf/hpec/hpec2016.html#Pakin16',
    year: '2016',
    type: 'inproceedings',
    _key: 'conf::hpec::Pakin16',
    crossref: [ 'conf::hpec::2016' ]
  },
  {
    _id: ObjectId('595c2c03a7986c0872dbe06e'),
    ee: 'http://dx.doi.org/10.1016/S0377-2217(01)00170-9',
    number: '3',
    year: '2002',
    mdate: '2010-10-26',
    author: [ 'Steffen Jrgensen', 'Peter M. Kort' ],
    type: 'article',
    journal: 'European Journal of Operational Research',
    volume: '138',
    pages: '578-600',
    url: 'db/journals/eor/eor138.html#JorgensenK02',
    title: 'Optimal pricing and inventory policies: Centralized and decentralized decision making.',
    _key: 'journals::eor::JorgensenK02'
  },
  {
    _id: ObjectId('595c2c22a7986c0872e93c1c'),
    volume: '174',
    mdate: '2017-05-20',
    author: [ 'Xin Gao', 'Jian Hou' ],
    ee: 'https://doi.org/10.1016/j.neucom.2015.10.018',
    title: 'An improved SVM integrated GS-PCA fault diagnosis approach of Tennessee Eastman process.',
    pages: '906-911',
    url: 'db/journals/ijon/ijon174.html#GaoH16',
    journal: 'Neurocomputing',
    year: '2016',
    type: 'article',
    _key: 'journals::ijon::GaoH16'
  },
  {
    _id: ObjectId('595c2c74a7986c08720bc81e'),
    mdate: '2017-05-19',
    author: [ 'Markus Kallinger', 'Alfred Mertins' ],
    ee: 'https://doi.org/10.1109/ICASSP.2006.1661222',
    booktitle: 'ICASSP (5)',
    title: 'Multi-Channel Room Impulse Response Shaping - A Study.',
    pages: '101-104',
    url: 'db/conf/icassp/icassp2006-5.html#KallingerM06',
    year: '2006',
    type: 'inproceedings',
    _key: 'conf::icassp::KallingerM06',
    crossref: [ 'conf::icassp::2006' ]
  },
  {
    _id: ObjectId('595c2c21a7986c0872e8eaba'),
    ee: 'http://dx.doi.org/10.1021/ci960027v',
    number: '5',
    year: '1996',
    mdate: '2003-05-13',
    author: [ 'Harry P. Schultz', 'Emily B. Schultz', 'Tor P. Schultz' ],
    type: 'article',
    journal: 'Journal of Chemical Information and Computer Sciences',
    volume: '36',
    pages: '996-1000',
    url: 'db/journals/jcisd/jcisd36.html#SchultzSS96',
    title: 'Topological Organic Chemistry. 10. Graph Theory and Topological Indices of Conformational Isomers.',
    _key: 'journals::jcisd::SchultzSS96'
  },
  {
    _id: ObjectId('595c2ca0a7986c08722958ba'),
    mdate: '2014-04-07',
    author: [ 'Kazutaka Kouda' ],
    _key: 'homepages::144::0573',
    title: 'Home Page',
    type: 'www'
  },
  {
    _id: ObjectId('595c2c90a7986c08721d265c'),
    mdate: '2015-07-05',
    author: [ 'Yves-Laurent Kom Samo' ],
    _key: 'homepages::164::7320',
    title: 'Home Page',
    type: 'www'
  }
]

```

Question 3 : Trouver le nombre d'auteur
```
db> db.dblp.distinct("author").length
```
Réponse : 
`10815`

Question 4 : Trouvez toutes les publications de Jing Liu
`db> db.dblp.find({author:"Jing Liu"})`

Question 5 : Triez les résultats précédents par date de publication

`db.dblp.find({author:"Jing Liu"}).sort("mdate")`

Réponse : 
```
[
  {
    _id: ObjectId('595c2c56a7986c0872febc3d'),
    mdate: '2013-12-16',
    author: [ 'Haoqing Yinhe', 'Jing Liu' ],
    _key: 'conf::gi::YinheL13',
    booktitle: 'GI-Jahrestagung',
    title: 'Exploring Challenges in Embedding Metadata of Licences and Attribution in Digital Work.',
    pages: '3108-3130',
    url: 'db/conf/gi/gi2013.html#YinheL13',
    year: '2013',
    type: 'inproceedings',
    crossref: [ 'conf::gi::2013' ]
  },
  {
    _id: ObjectId('595c2c54a7986c0872fde5a1'),
    mdate: '2017-05-17',
    author: [ 'Ming Li', 'Jing Liu', 'Qiang Shen', 'Bin Yuan' ],
    ee: 'https://doi.org/10.1007/978-3-319-07782-6_53',
    booktitle: 'WASA',
    title: 'QS-PS: A New Approach for Emergency Packet Delivery in WBAN.',
    pages: '589-600',
    url: 'db/conf/wasa/wasa2014.html#LiLSY14',
    year: '2014',
    type: 'inproceedings',
    _key: 'conf::wasa::LiLSY14',
    crossref: [ 'conf::wasa::2014' ]
  },
  {
    _id: ObjectId('595c2c65a7986c087205033b'),
    mdate: '2017-05-26',
    author: [ 'Jing Liu', 'Xinming Ye', 'Jun Li 0002' ],
    ee: [
      'https://doi.org/10.1109/SNPD.2010.16',
      'http://doi.ieeecomputersociety.org/10.1109/SNPD.2010.16'
    ],
    booktitle: 'SNPD',
    title: 'CP-Nets Based Methodology for Integrating Functional Verification and Performance Analysis of Network Protocol.',
    pages: '41-46',
    url: 'db/conf/snpd/snpd2010.html#LiuYL10',
    year: '2010',
    type: 'inproceedings',
    _key: 'conf::snpd::LiuYL10',
    crossref: [ 'conf::snpd::2010' ]
  }
]
```

Question 6 : Affichez le titre des 5 articles les plus anciens.
`db> db.dblp.find({},{title: 1,"mdate": 1}).sort({"mdate":1}).limit(5)`

Réponse
```
[
  {
    _id: ObjectId('595c2c4fa7986c0872fbf5e3'),
    mdate: '2002-01-03',
    title: 'Diagnosing Crosstalk Faults in a Class of Dilated Blocking Optical Multistage Interconnection Networks.'
  },
  {
    _id: ObjectId('595c2c36a7986c0872f1f3b4'),
    mdate: '2002-01-03',
    title: 'Dimensioning the Continuous State Leaky Bucket for Geometric Arrivals.'
  },
  {
    _id: ObjectId('595c2c1da7986c0872e6d38b'),
    mdate: '2002-01-03',
    title: 'Bottom-Up Computation of Recursive Programs.'
  },
  {
    _id: ObjectId('595c2c76a7986c08720c63d8'),
    mdate: '2002-01-03',
    title: 'Complex Methods and Class Allocation in Distributed Object-Oriented Database Systems.'
  },
  {
    _id: ObjectId('595c2c57a7986c0872ff770c'),
    mdate: '2002-01-03',
    title: 'Channel Coding Techniques for Adaptive Multi Rate Speech Transmission.'
  }
]
```

Question 7 : Répondez à la question précédente en utilisant cette fois une variable temporaire Js et
la fonction sort() native des tableaux Js.
`db.dblp.find({},{title: 1,"mdate": 1}).sort({"mdate":1}).limit(5).toArray()`

Réponse: Même réponse que précédent

## Map/Reduce

Question 1 : Trouvez le nombre de publication pour chaque type trié par nombre de publication.

```
db.dblp.mapReduce(
    function () {emit(this.type,1)},
    function (key,values) {return Array.sum(values)},
    {out : "publi_par_type"}
)

db.publi_par_type.find().sort({value:-1})
```

Réponse : 
```
[
  { _id: 'inproceedings', value: 1738 },
  { _id: 'www', value: 1680 },
  { _id: 'article', value: 1460 },
  { _id: 'phdthesis', value: 53 },
  { _id: 'incollection', value: 28 },
  { _id: 'proceedings', value: 23 },
  { _id: 'book', value: 18 }
]
```

Question 2 : Trouvez le nombre de publication par auteur. Attention certaine publication n'ont pas d'auteur !

```
db.dblp.mapReduce(
    function() {
        if (this.author) {
                this.author.forEach(function(aut) {
                    emit(aut, 1);
                });
            } 
        },
    function(key, values) {
        return Array.sum(values);
    },
    { out: "publi_par_auteur" }
);

db.publi_par_auteur.find().sort({ value: -1 });
```

Réponse : 
```
[
  { _id: 'Li Zhang', value: 4 },
  { _id: 'Andrea J. Goldsmith', value: 3 },
  { _id: 'Xin Huang', value: 3 },
  { _id: 'David Lorge Parnas', value: 3 },
  { _id: 'Jerry L. Prince', value: 3 },
  { _id: 'Michael I. Jordan', value: 3 },
  { _id: 'Qing Li', value: 3 },
  { _id: 'Peer-Timo Bremer', value: 3 },
  { _id: 'Jing Liu', value: 3 },
  { _id: 'Ye Wang', value: 3 },
  { _id: 'Peng Zhao', value: 3 },
  { _id: 'Dacheng Tao', value: 3 },
  { _id: 'Yan Xu', value: 2 },
  { _id: 'Muhammad Sarfraz', value: 2 },
  { _id: 'Leonard Barolli', value: 2 },
  { _id: 'Weiwei Wu', value: 2 },
  { _id: 'Minh Nhut Nguyen', value: 2 },
  { _id: 'Javier Vazquez-Corral', value: 2 },
  { _id: 'Antoine Girard', value: 2 },
  { _id: 'Jian Hou', value: 2 }
]
```


Question 3 : Trouvez toutes les publications sans auteur.

```
db.dblp.mapReduce(
    function() {
        if (!this.author) {
            emit(this, 1);
        }
    },
    function(key, values) {
        return Array.sum(values); // On additionne les occurrences
    },
    { out: "publi_sans_auteur" }
);
db.publi_sans_auteur.find();
```

Réponse : 

```
...
  {
    _id: {
      _id: ObjectId('595c2c33a7986c0872f0b5ca'),
      publisher: 'IASTED::ACTA:20Press',
      mdate: '2006-03-30',
      _key: 'conf::cgim::2005',
      booktitle: 'Computer Graphics and Imaging',
      title: 'Proceedings of the Eighth IASTED International Conference on Computer Graphics and Imaging, CGIM 2005, Honolulu, Hawaii, USA, August 15-17, 2005',
      url: 'db/conf/cgim/cgim2005.html',
      editor: [ 'M. H. Hamza' ],
      year: '2005',
      isbn: '0-88986-514-0',
      type: 'proceedings'
    },
    value: 1
  },
  {
    _id: {
      _id: ObjectId('595c2c5aa7986c087200a0f5'),
      mdate: '2008-06-04',
      ee: 'http://ceur-ws.org/Vol-221/preface.pdf',
      booktitle: 'CACOA',
      title: 'Preface.',
      url: 'db/conf/ewcbr/cacoa2006.html#X06',
      year: '2006',
      type: 'inproceedings',
      _key: 'conf::ewcbr::X06',
      crossref: [ 'conf::ewcbr::2006cacoa' ]
    },
    value: 1
  },
  {
    _id: {
      _id: ObjectId('595c2c3da7986c0872f43985'),
      publisher: 'IEEE:20Computer:20Society',
      mdate: '2016-05-13',
      ee: [
        'http://ieeexplore.ieee.org/xpl/mostRecentIssue.jsp?punumber=11039',
        'https://www.computer.org/csdl/proceedings/ccc/2006/2596/00/index.html'
      ],
      booktitle: 'IEEE Conference on Computational Complexity',
      title: '21st Annual IEEE Conference on Computational Complexity (CCC 2006), 16-20 July 2006, Prague, Czech Republic',
      url: 'db/conf/coco/coco2006.html',
      year: '2006',
      isbn: '0-7695-2596-2',
      type: 'proceedings',
      _key: 'conf::coco::2006'
    },
    value: 1
  },
  {
    _id: {
      _id: ObjectId('595c2c36a7986c0872f21683'),
      publisher: 'IEEE',
      mdate: '2014-03-06',
      ee: 'http://ieeexplore.ieee.org/xpl/mostRecentIssue.jsp?punumber=5720574',
      booktitle: 'IDT',
      title: '5th International Design and Test Workshop, IDT 2010, Abu Dhabi, UAE, 14-15 December 2010',
      url: 'db/conf/idt/idt2010.html',
      editor: [ 'Yervant Zorian', 'Imtinan Elahi', 'Andr Ivanov', 'Ashraf Salem' ],
      year: '2010',
      isbn: '978-1-61284-291-2',
      type: 'proceedings',
      _key: 'conf::idt::2010'
    },
    value: 1
  },
  {
    _id: {
      _id: ObjectId('595c2c4fa7986c0872fb9617'),
      volume: '976',
      publisher: 'Springer',
      mdate: '2017-05-20',
      ee: 'https://doi.org/10.1007/3-540-60299-2',
      series: [ 'Lecture Notes in Computer Science' ],
      booktitle: 'CP',
      title: "Principles and Practice of Constraint Programming - CP'95, First International Conference, CP'95, Cassis, France, September 19-22, 1995, Proceedings",
      url: 'db/conf/cp/cp95.html',
      editor: [ 'Ugo Montanari', 'Francesca Rossi' ],
      year: '1995',
      isbn: '3-540-60299-2',
      type: 'proceedings',
      _key: 'conf::cp::1995'
    },
    value: 1
  },
  {
    _id: {
      _id: ObjectId('595c2c69a7986c087206a955'),
      volume: '5216',
      publisher: 'Springer',
      mdate: '2008-10-20',
      _key: 'conf::ices::2008',
      series: [ 'Lecture Notes in Computer Science' ],
      booktitle: 'ICES',
      title: 'Evolvable Systems: From Biology to Hardware, 8th International Conference, ICES 2008, Prague, Czech Republic, September 21-24, 2008. Proceedings',
      url: 'db/conf/ices/ices2008.html',
      editor: [ 'Gregory Hornby', 'Luks Sekanina', 'Pauline C. Haddow' ],
      year: '2008',
      isbn: '978-3-540-85856-0',
      type: 'proceedings'
    },
    value: 1
  },
  {
    _id: {
      _id: ObjectId('595c2c2ca7986c0872edd7eb'),
      ee: 'https://doi.org/10.1007/s00287-010-0494-7',
      number: '6',
      year: '2010',
      mdate: '2017-05-17',
      type: 'article',
      journal: 'Informatik Spektrum',
      volume: '33',
      pages: '550',
      url: 'db/journals/insk/insk33.html#XX10',
      title: 'Mitteilungen der Gesellschaft fr Informatik 206. Folge.',
      _key: 'journals::insk::XX10'
    },
    value: 1
  },
  {
    _id: {
      _id: ObjectId('595c2c6ca7986c0872082853'),
      mdate: '2013-12-02',
      _key: 'conf::lpe::2002',
      booktitle: 'LPE',
      title: 'Proceedings of the 12th International Workshop on Logic Programming Environments, WLPE 2002, Copenhagen, Denmark, July 31, 2002',
      url: 'db/conf/lpe/wlpe2002.html',
      editor: [ 'Alexandre Tessier' ],
      year: '2002',
      type: 'proceedings'
    },
    value: 1
  },
  {
    _id: {
      _id: ObjectId('595c2c73a7986c08720b32f6'),
      publisher: 'ACM',
      mdate: '2016-01-18',
      ee: 'http://doi.acm.org/10.1145/2785989',
      booktitle: 'HotMiddlebox@SIGCOMM',
      title: 'Proceedings of the 2015 ACM SIGCOMM Workshop on Hot Topics in Middleboxes and Network Function Virtualization, HotMiddlebox@SIGCOMM 2015, London, United Kingdom, August 21, 2015',
      url: 'db/conf/sigcomm/hotmiddlebox2015.html',
      editor: [ 'Theophilus Benson', 'Costin Raiciu' ],
      year: '2015',
      isbn: '978-1-4503-3540-9',
      type: 'proceedings',
      _key: 'conf::sigcomm::2015hotmiddlebox'
    },
    value: 1
  },
  {
    _id: {
      _id: ObjectId('595c2c3fa7986c0872f4d4ae'),
      publisher: 'IEEE',
      mdate: '2016-01-20',
      ee: 'http://ieeexplore.ieee.org/xpl/mostRecentIssue.jsp?punumber=6064644',
      booktitle: 'IAS Annual Meeting',
      title: '2011 IEEE Industry Applications Society Annual Meeting, Orlando, FL, USA, October 9-13, 2011',
      url: 'db/conf/iasam/iasam2011.html',
      year: '2011',
      isbn: '978-1-4244-9498-9',
      type: 'proceedings',
      _key: 'conf::iasam::2011'
    },
    value: 1
  },
  {
    _id: {
      _id: ObjectId('595c2c31a7986c0872efe36b'),
      publisher: 'Springer',
      mdate: '2011-11-25',
      _key: 'reference::algo::2008',
      title: 'Encyclopedia of Algorithms',
      url: 'db/reference/algo/algo2008.html',
      editor: [ 'Ming-Yang Kao' ],
      year: '2008',
      isbn: '978-0-387-30162-4',
      type: 'book'
    },
    value: 1
  },
  {
    _id: {
      _id: ObjectId('595c2c31a7986c0872f019af'),
      mdate: '2017-05-16',
      ee: 'https://doi.org/10.1007/978-0-387-39940-9_3420',
      booktitle: 'Encyclopedia of Database Systems',
      publtype: 'encyclopedia entry',
      pages: '2339',
      url: 'db/reference/db/r.html#X09xut',
      title: 'RDF.',
      year: '2009',
      type: 'incollection',
      _key: 'reference::db::X09xut',
      crossref: [ 'reference::db::2009' ]
    },
    value: 1
  }
]
```

Question 4 

```
db.dblp.mapReduce(
    function() {
        if (!this.author) {
            emit(this.type, 1);
        }
    },
    function(key, values) {
        return Array.sum(values); // On additionne les occurrences
    },
    { out: "publi_type_auteur" }
);
db.publi_type_auteur.find();
```

Réponse : 
```
[
  { _id: 'article', value: 5 },
  { _id: 'proceedings', value: 23 },
  { _id: 'incollection', value: 8 },
  { _id: 'inproceedings', value: 1 },
  { _id: 'book', value: 2 }
]
```

Question 5 

Fait lors de la question 2

## Modification du Shema




