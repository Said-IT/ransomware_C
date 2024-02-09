#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void handleUpload(int clientSocket);
void handleEncryptionDecryption(int clientSocket);

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(struct sockaddr_in);

    // Création du socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    // Configuration de l'adresse du serveur
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12345); // Port arbitraire

    // Liaison du socket à l'adresse
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Erreur lors de la liaison du socket");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Mise en écoute du socket
    if (listen(serverSocket, 5) == -1) {
        perror("Erreur lors de la mise en écoute du socket");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    printf("Serveur en attente de connexions...\n");

    // Attente de connexions
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrSize);
    if (clientSocket == -1) {
        perror("Erreur lors de l'acceptation de la connexion");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    printf("Connexion établie avec le client.\n");

    // Menu du serveur
    int choice;
    do {
        printf("\nMenu du serveur:\n");
        printf("1. Upload\n");
        printf("2. Cryptage/Decryptage\n");
        printf("0. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                handleUpload(clientSocket);
                break;
            case 2:
                handleEncryptionDecryption(clientSocket);
                break;
            case 0:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide. Réessayez.\n");
        }
    } while (choice != 0);

    // Fermeture des sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}

void handleUpload(int clientSocket) {
    // Recevoir la liste des fichiers du client
    char buffer[1024];
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("Fichiers reçus du client:\n%s\n", buffer);

    // Demander au serveur de choisir un fichier pour l'upload
    char filename[256];
    printf("Choisissez un fichier pour l'upload: ");
    scanf("%s", filename);

    // Envoyer le nom du fichier au client
    send(clientSocket, filename, sizeof(filename), 0);

    // Ouverture du fichier en mode binaire
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    // Lecture du fichier par morceaux et envoi au client
    char fileBuffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(fileBuffer, 1, sizeof(fileBuffer), file)) > 0) {
        send(clientSocket, fileBuffer, bytesRead, 0);
    }

    // Fermeture du fichier
    fclose(file);

    printf("Upload du fichier %s terminé.\n", filename);
}

void handleEncryptionDecryption(int clientSocket) {
    // Recevoir la liste des fichiers du client (non affichée côté client)
    char buffer[1024];
    recv(clientSocket, buffer, sizeof(buffer), 0);

    // Demander au serveur de choisir un fichier pour le cryptage
    char filename[256];
    printf("Choisissez un fichier pour le cryptage: ");
    scanf("%s", filename);

    // Envoyer le nom du fichier au client
    send(clientSocket, filename, sizeof(filename), 0);

    // Recevoir le montant du client
    double amount;
    printf("Montant à payer pour le cryptage: ");
    scanf("%lf", &amount);

    // Envoyer le montant au serveur
    send(clientSocket, &amount, sizeof(amount), 0);

    // Recevoir la décision du serveur (payer ou non)
    char decision[10];
    recv(clientSocket, decision, sizeof(decision), 0);

    if (strcmp(decision, "payer") == 0) {
        //  Code pour le decryptage
        printf("Décryptage du fichier %s en cours...\n", filename);
    } else {
        // Répéter jusqu'à ce que le serveur accepte le paiement
        while (strcmp(decision, "payer") != 0) {
            printf("Montant insuffisant. Réessayez.\n");

            // Demander un nouveau montant
            printf("Montant à payer pour le cryptage: ");
            scanf("%lf", &amount);

            // Envoyer le nouveau montant au serveur
            send(clientSocket, &amount, sizeof(amount), 0);

            // Recevoir la décision mise à jour
            recv(clientSocket, decision, sizeof(decision), 0);
        }

        // Code pour le decryptage
        printf("Décryptage du fichier %s en cours...\n", filename);
    }
}

