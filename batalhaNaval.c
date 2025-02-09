#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define SHIP_COUNT 5

// Estrutura para armazenar as coordenadas do navio
typedef struct {
    int x, y;
} Ship;

// Inicializa o tabuleiro com água (~)
void initBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '~';
        }
    }
}

// Exibe o tabuleiro
void printBoard(char board[SIZE][SIZE]) {
    printf("  ");
    for (int i = 0; i < SIZE; i++) printf("%d ", i);
    printf("\n");
    
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// Posiciona navios aleatoriamente no tabuleiro
void placeShips(char board[SIZE][SIZE], Ship ships[SHIP_COUNT]) {
    srand(time(NULL));
    for (int i = 0; i < SHIP_COUNT; i++) {
        int x, y;
        do {
            x = rand() % SIZE;
            y = rand() % SIZE;
        } while (board[x][y] == 'S');
        
        board[x][y] = 'S';
        ships[i].x = x;
        ships[i].y = y;
    }
}

// Função para processar um tiro
int shoot(char board[SIZE][SIZE], Ship ships[SHIP_COUNT], int x, int y) {
    for (int i = 0; i < SHIP_COUNT; i++) {
        if (ships[i].x == x && ships[i].y == y) {
            board[x][y] = 'X';
            printf("Acertou um navio!\n");
            return 1;
        }
    }
    board[x][y] = 'O';
    printf("Errou!\n");
    return 0;
}

// Menu interativo do jogo
void menu() {
    char board[SIZE][SIZE];
    Ship ships[SHIP_COUNT];
    int remainingShips = SHIP_COUNT;
    
    initBoard(board);
    placeShips(board, ships);
    
    int x, y;
    while (remainingShips > 0) {
        printBoard(board);
        printf("Digite as coordenadas do tiro (linha e coluna): ");
        scanf("%d %d", &x, &y);
        
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            printf("Coordenadas inválidas, tente novamente.\n");
            continue;
        }
        
        if (shoot(board, ships, x, y)) {
            remainingShips--;
        }
    }
    
    printf("Parabéns! Você destruiu todos os navios!\n");
}

int main() {
    int option;
    do {
        printf("=== BATALHA NAVAL ===\n");
        printf("1. Jogar\n");
        printf("2. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);
        
        switch (option) {
            case 1:
                menu();
                break;
            case 2:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (option != 2);
    
    return 0;
}
