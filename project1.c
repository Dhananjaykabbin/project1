#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_FRIENDS 100

// Structure to represent a friend (node) in the adjacency list
typedef struct Friend {
    char name[MAX_NAME_LENGTH];
    struct Friend *next;
} Friend;

// Structure to represent a graph node (head of the adjacency list)
typedef struct FriendNode {
    char name[MAX_NAME_LENGTH];
    Friend *connections; // Linked list of friends
} FriendNode;
// Graph structure
typedef struct FriendNetwork {
    FriendNode nodes[MAX_FRIENDS];
    int size; // Number of friends in the network
} FriendNetwork;

// Function prototypes
void initializeNetwork(FriendNetwork *network);
void addFriend(FriendNetwork *network, char *name);
void addConnection(FriendNetwork *network, char *name1, char *name2);
int findFriendIndex(FriendNetwork *network, char *name);
int isConnectionExists(Friend *connections, char *name);
void displayNetworkPattern(FriendNetwork *network);
void menu();
void exitProgram();

// Initialize the friend network
void initializeNetwork(FriendNetwork *network) {
    network->size = 0;
}

// Add a new friend to the network
void addFriend(FriendNetwork *network, char *name) {
    if (network->size >= MAX_FRIENDS) {
        printf("⚠ Network is full, cannot add more friends.\n");
        return;
    }
if (findFriendIndex(network, name) != -1) {
        printf("⚠ Friend '%s' already exists.\n", name);
        return;
    }

    strcpy (network->nodes[network->size].name, name);
    network->nodes[network->size].connections = NULL;
    network->size++;
    printf("🎉 Friend '%s' added to the network!\n", name);
}

// Find the index of a friend by name
int findFriendIndex(FriendNetwork *network, char *name) {
    for (int i = 0; i < network->size; i++) {
        if (strcmp(network->nodes[i].name, name) == 0) {
            return i;
        }
    }
    return -1; // Friend not found
}

// Check if a connection already exists
int isConnectionExists(Friend *connections, char *name) {
    while (connections) {
        if (strcmp(connections->name, name) == 0) {
            return 1; // Connection exists
       }
        connections = connections->next;
    }
    return 0; // Connection doesn't exist
}

// Add a connection between two friends
void addConnection(FriendNetwork *network, char *name1, char *name2) {
    int idx1 = findFriendIndex(network, name1);
    int idx2 = findFriendIndex(network, name2);

    if (idx1 == -1 || idx2 == -1) {
        printf("⚠ One or both friends are not in the network.\n");
        return;
    }

    if (strcmp(name1, name2) == 0) {
        printf("⚠ A friend cannot connect to themselves.\n");
        return;
    }

    if (isConnectionExists(network->nodes[idx1].connections, name2)) {
        printf("⚠ Connection already exists between '%s' and '%s'.\n", name1, name2);
        return;
    }

// Add name2 to name1's connections
    Friend *newFriend1 = (Friend *)malloc(sizeof(Friend));
    strcpy(newFriend1->name, name2);
    newFriend1->next = network->nodes[idx1].connections;
    network->nodes[idx1].connections = newFriend1;

    // Add name1 to name2's connections
    Friend *newFriend2 = (Friend *)malloc(sizeof(Friend));
    strcpy(newFriend2->name, name1);
    newFriend2->next = network->nodes[idx2].connections;
    network->nodes[idx2].connections = newFriend2;

    printf("🤝 Connection established between '%s' and '%s'!\n", name1, name2);
}

// Display the network in a pattern-like structure
void displayNetworkPattern(FriendNetwork *network) {
    printf("\n🌐 Friend Network Pattern:\n");
    for (int i = 0; i < network->size; i++) {
        printf("%s\n", network->nodes[i].name);
        Friend *connection = network->nodes[i].connections;
        while (connection) {
            printf("   └── %s\n", connection->name);
            connection = connection->next;
        }
    }
}

// Main menu function
void menu() {
    printf("\n=========================\n");
    printf("📚 Friend Network Menu\n");
    printf("=========================\n");
    printf("1. Add a Friend\n");
    printf("2. Add a Connection\n");
    printf("3. Show Network Connections (Pattern)\n");
    printf("4. Exit\n");
    printf("=========================\n");
}

// Exit program function
void exitProgram() {
    printf("👋 Exiting... Goodbye!\n");
    exit(0);
}

// Main function
int main() {
    FriendNetwork network;
    initializeNetwork(&network);
   int choice;
    char name1[MAX_NAME_LENGTH], name2[MAX_NAME_LENGTH];

    while (1) {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter friend's name: ");
                scanf("%s", name1);
                addConnection(&network, name1, name2);
                break;

            case 2:
                printf("Enter the first friend's name: ");
                scanf("%s", name1);
                printf("Enter the second friend's name: ");
                scanf("%s", name2);
                addFriend(&network, name1);
                break;

            case 3:
                displayNetworkPattern(&network);
                break;
           case 4:
                exitProgram();
                break;

            default:
                printf("⚠ Invalid choice. Please try again.\n");
        }
    }

    return 0;
}