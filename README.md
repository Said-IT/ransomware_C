# ransomware_C



Description concise de votre projet.

## Fonctionnalités

- **Upload de Fichiers:** Le serveur permet aux clients d'envoyer des fichiers depuis leur répertoire local.
- **Cryptage/Décryptage:** Le serveur peut effectuer des opérations de cryptage/décryptage sur les fichiers reçus, en fonction d'un montant spécifié par le client.

## Prérequis

- **Environnement de Développement:** [Indiquez les détails de l'environnement de développement nécessaire, par exemple, compilateur C, bibliothèques, etc.]

## Comment Utiliser

1. **Compilation:**
   ```bash
   https://github.com/Said-IT/ransomware_C
Exécution du Serveur:

bash
Copy code
./server
Exécution du Client:

bash
Copy code
./client
Instructions pour l'Utilisateur:

Le client envoie la liste des fichiers du répertoire local au serveur.
Le serveur propose un menu pour effectuer l'upload ou des opérations de cryptage/décryptage.
Pour l'upload, le client choisit un fichier qui est ensuite transféré au serveur.
Pour le cryptage/décryptage, le client saisit le montant à payer, le serveur prend la décision de crypter ou non en fonction du montant.
## Fonctionnement
### Upload de Fichiers
Le client envoie la liste des fichiers dans son répertoire local au serveur.
Le serveur affiche la liste et demande au client de choisir un fichier pour l'upload.
Le client sélectionne un fichier.
Le serveur reçoit le fichier et effectue les opérations nécessaires.
### Cryptage/Décryptage
Le client envoie la liste des fichiers dans son répertoire local au serveur.
Le serveur affiche la liste et demande au client de choisir un fichier pour le cryptage.
Le client sélectionne un fichier.
Le client saisit un montant à payer.
Le serveur prend la décision de crypter ou non en fonction du montant.
Si le cryptage est accepté, le serveur effectue les opérations de cryptage/décryptage.
### Structure du Projet
server.c: Code source pour le serveur.
client.c: Code source pour le client.

## apreçu  :

![Image d'illustration](/image/server)


Auteur
Said A.M
