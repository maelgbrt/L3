# Application Mobile (Wayntal)

### Choix pédagogiques
* Application native avec **Kotlin**
* Création des vues avec le framework **Jetpack Compose**
* Suivi sur sa propre machine ou celle de son binôme
* Tests directement sur son appareil Android
* Éviter le simple « copier-coller »

### Objectifs
* Savoir se situer dans l'écosystème mobile
* Démystifier le développement mobile (comprendre que ce n'est pas magique)
* Comprendre le fonctionnement d'un environnement de développement (IDE, SDK, émulateur)
* Être capable de concevoir une application mobile de bout en bout

---

## 1. Introduction au Développement Mobile

### Qu'est-ce qu'une application mobile ?
* **Application :** Logiciel applicatif ou programme conçu pour réaliser une tâche précise (navigateur web, éditeur de texte, jeu vidéo).
* **Mobile :** Appareil informatique portable et autonome (smartphone, tablette).

---

## 2. Typologie des Applications

| Type d'application | Technologies / Langages | Accès matériel | Distribution |
| :--- | :--- | :--- | :--- |
| **Native** | Kotlin / Java (Android)<br>Swift / Objective-C (iOS) | **Complet et direct** (caméra, capteurs, Bluetooth, appels, etc.) | Stores officiels (Google Play Store, App Store) |
| **Hybride** | HTML, CSS, JavaScript (via un conteneur *WebView*) | **Limité** (dépend des ponts/plugins natifs) | Stores officiels (Google Play Store, App Store) |
| **PWA** *(Progressive Web App)* | Technologies Web modernes (HTML5, Manifest, Service Workers) | **Très restreint** (limité aux API du navigateur) | Directement via le navigateur (sans store) |

> **Guidelines :** Chaque système d'exploitation impose ses propres règles d'interface utilisateur (*Material Design* pour Android, *Human Interface Guidelines* pour iOS).

---

## 3. UI Design vs UX Design

### UI Design (*User Interface*)
* S'intéresse à l'aspect visuel et esthétique de l'application (couleurs, typographies, icônes, animations).
* Améliore l'engagement de l'utilisateur à travers ses émotions.

### UX Design (*User Experience*)
* Décrit et structure l'ensemble des interactions de l'utilisateur.
* Optimise l'accessibilité, la simplicité et la fluidité des parcours.

---

## 4. Règles d'Ergonomie Mobile

### L'Affordance
* Informer visuellement l'utilisateur qu'une action est possible.
* *Exemple :* Une icône de menu accompagnée d'un libellé explicite sous l'icône, bouton surélevé avec ombre.

### La Lisibilité
* Limiter l'information à l'essentiel pour éviter la surcharge cognitive.
* Structurer la hiérarchie visuelle des textes.

### Design pour le pouce (*Thumb Zone*)
* Prise en compte de la tenue du smartphone à une main.
* Adaptation à la taille croissante des écrans.
* Placement des zones d'interaction clés dans la zone naturellement accessible par le pouce.

### Gestes tactiles standards
* **Tap :** Pression simple (sélection, validation).
* **Swipe :** Balayage horizontal ou vertical.
* **Pinch to zoom :** Pincement pour zoomer / dézoomer.
* **Long press :** Appui prolongé pour afficher des actions contextuelles.