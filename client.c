#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <arpa/inet.h>

void sendFileList(int serverSocket);
double enterAmount();

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Création du socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    // Configuration de l'adresse du serveur
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Adresse IP du serveur
    serverAddr.sin_port = htons(12345); // Port arbitraire

    // Connexion au serveur
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Erreur lors de la connexion au serveur");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    // Envoi de la liste des fichiers et saisie du montant
    sendFileList(clientSocket);
    double amount = enterAmount();
    send(clientSocket, &amount, sizeof(amount), 0);

    // Fermeture du socket
    close(clientSocket);

    return 0;
}

void sendFileList(int serverSocket) {
    DIR *dir;
    struct dirent *entry;

    // Ouvrir le répertoire courant
    dir = opendir(".");
    if (!dir) {
        perror("Erreur lors de l'ouverture du répertoire");
        return;
    }

    // Construire la liste des fichiers dans le répertoire
    char fileList[1024] = "";
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {  // Fichier régulier
            strcat(fileList, entry->d_name);
            strcat(fileList, "\n");
        }
    }
    closedir(dir);

    // Envoyer la liste des fichiers au serveur
    send(serverSocket, fileList, sizeof(fileList), 0);

    // Afficher la liste des fichiers côté client (facultatif)
    printf("Liste des fichiers envoyée au serveur:\n%s\n", fileList);
}

double enterAmount() {
    double amount;
    printf("Saisissez le montant à payer : ");
    scanf("%lf", &amount);
    return amount;
}

