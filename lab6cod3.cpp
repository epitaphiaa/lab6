#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

// Функция для генерации случайного графа
int** generG(int size) {
int** G = (int**)malloc(size * sizeof(int*));
for (int i = 0; i < size; i++) {
G[i] = (int*)malloc(size * sizeof(int));
for (int j = 0; j < size; j++) {
G[i][j] = 0; // Инициализация нулями
}
}
for (int i = 0; i < size; i++) {
for (int j = i + 1; j < size; j++) {
int edge = rand() % 2;
G[i][j] = edge;
G[j][i] = edge;
}
}
return G;
}

// Функция для копирования графа
int** copyG(int** G, int size) {
int** newG = (int**)malloc(size * sizeof(int*));
for (int i = 0; i < size; i++) {
newG[i] = (int*)malloc(size * sizeof(int));
for (int j = 0; j < size; j++) {
newG[i][j] = G[i][j];
}
}
return newG;
}

// Функция для объединения графов
int** unionG(int** G1, int** G2, int size) {
int** G = (int**)malloc(size * sizeof(int*));
for (int i = 0; i < size; i++) {
G[i] = (int*)malloc(size * sizeof(int));
for (int j = 0; j < size; j++) {
G[i][j] = G1[i][j] || G2[i][j];
}
}
return G;
}

// Функция для пересечения графов
int** intersectG(int** G1, int** G2, int size) {
int** G = (int**)malloc(size * sizeof(int*));
for (int i = 0; i < size; i++) {
G[i] = (int*)malloc(size * sizeof(int));
for (int j = 0; j < size; j++) {
G[i][j] = G1[i][j] && G2[i][j];
}
}
return G;
}

// Функция для кольцевой суммы графов
int** symmetricDiffG(int** G1, int** G2, int size) {
int** G = (int**)malloc(size * sizeof(int*));
for (int i = 0; i < size; i++) {
G[i] = (int*)malloc(size * sizeof(int));
for (int j = 0; j < size; j++) {
G[i][j] = (G1[i][j] + G2[i][j]) % 2;
}
}
return G;
}

// Функция для вывода графа
void printG(int** G, int size) {
printf("Матрица смежности:\n");
for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++) {
printf("%d ", G[i][j]);
}
printf("\n");
}
}

// Функция для освобождения памяти графа
void freeG(int** G, int size) {
for (int i = 0; i < size; i++) {
free(G[i]);
}
free(G);
}

// Главная функция
int main() {
setlocale(LC_ALL, "Russian");
srand(time(NULL));

int sizeG1, sizeG2;

// Запрос размера графов
printf("Введите количество вершин для графа 1: ");
scanf("%d", &sizeG1);
printf("Введите количество вершин для графа 2: ");
scanf("%d", &sizeG2);

// Генерация случайных графов
int** G1 = generG(sizeG1);
int** G2 = generG(sizeG2);

// Печать графов
printf("\nИзначальный граф 1:\n");
printG(G1, sizeG1);
printf("\nГраф 2:\n");
printG(G2, sizeG2);

printf("\n=== Бинарные операции с изначальным G1 ===\n");

if (sizeG1 == sizeG2) {
// Объединение
int** tempG1 = copyG(G1, sizeG1);
printf("\nОбъединение графов G1 ∪ G2:\n");
int** unionResult = unionG(tempG1, G2, sizeG1);
printG(unionResult, sizeG1);
freeG(tempG1, sizeG1);
freeG(unionResult, sizeG1);

// Пересечение
tempG1 = copyG(G1, sizeG1);
printf("\nПересечение графов G1 ∩ G2:\n");
int** intersectResult = intersectG(tempG1, G2, sizeG1);
printG(intersectResult, sizeG1);
freeG(tempG1, sizeG1);
freeG(intersectResult, sizeG1);

// Кольцевая сумма
tempG1 = copyG(G1, sizeG1);
printf("\nКольцевая сумма графов G1 ⊕ G2:\n");
int** symmetricDiffResult = symmetricDiffG(tempG1, G2, sizeG1);
printG(symmetricDiffResult, sizeG1);
freeG(tempG1, sizeG1);
freeG(symmetricDiffResult, sizeG1);
} else {
printf("Графы должны быть одинакового размера для выполнения бинарных операций.\n");
}

// Освобождение памяти для исходных графов
freeG(G1, sizeG1);
freeG(G2, sizeG2);

return 0;
}
