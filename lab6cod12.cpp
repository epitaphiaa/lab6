Задание 1,2
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

// Функция для генерации случайного графа
int** generG(int size) {
int** G = NULL;
G = (int**)malloc(size * sizeof(int*));
for (int i = 0; i < size; i++) {
G[i] = (int*)malloc(size * sizeof(int));
}
for (int i = 0; i < size; i++) {
for (int j = 0; j < size;j++) {
G[i][j] = 0;
}
}
for (int i = 0; i < size; i++) {
for (int j = i + 1; j < size;j++) {
int edge = rand() % 2;
G[i][j] = edge;
G[j][i] = edge;
}
}
return G;
}

// Функция для вывода матрицы смежности
void printG(int** G, int size) {
printf("Матрица смежности:\n");
for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++) {
printf("%d ", G[i][j]);
}
printf("\n");
}
}

// Функция для удаления вершины
int** delv(int** G, int size, int v) {
int** Gtemp = (int**)malloc((size - 1) * sizeof(int*));
for (int i = 0; i < size - 1; i++) {
Gtemp[i] = (int*)malloc((size - 1) * sizeof(int));
}

for (int i = 0; i < size - 1; i++) {
for (int j = 0; j < size - 1; j++) {
Gtemp[i][j] = (i < v ? G[i][j] : G[i + 1][j]);
Gtemp[i][j] = (j < v ? Gtemp[i][j] : (i < v ? G[i][j + 1] : G[i + 1][j + 1]));
}
}
for (int i = 0; i < size; i++) {
free(G[i]);
}
free(G);
return Gtemp;
}

// Операция отождествления вершин
int** unionv(int** G, int size, int v1, int v2) {
if (v1 < 0 || v1 >= size || v2 < 0 || v2 >= size || v1 == v2) {
printf("Ошибка: некорректные вершины для отождествления.\n");
return G;
}
for (int i = 0; i < size; i++) {
if (G[v2][i]) {
G[v1][i] = 1;
G[i][v1] = 1;
}
}
return delv(G, size, v2);
}

// Операция стягивания ребра
int** contrE(int** G, int size, int v1, int v2) {
if (v1 < 0 || v1 >= size || v2 < 0 || v2 >= size || G[v1][v2] == 0) {
printf("Ребра между вершинами нет, операция невозможна.\n");
return G;
}
G[v1][v2] = G[v2][v1] = 0;
for (int i = 0; i < size; i++) {
if (G[v2][i]) {
G[v1][i] = 1;
G[i][v1] = 1;
}
}
return delv(G, size, v2);
}

// Операция расщепления вершины
int** splitV(int** G, int size, int v) {
if (v < 0 || v >= size) {
printf("Ошибка: номер вершины вне допустимого диапазона (0-%d).\n", size - 1);
return G;
}
int** Gtemp = (int**)malloc((size + 1) * sizeof(int*));
for (int i = 0; i < size + 1; i++) {
Gtemp[i] = (int*)calloc(size + 1, sizeof(int));
}

for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++) {
Gtemp[i][j] = G[i][j];
}
}

for (int i = 0; i < size; i++) {
Gtemp[i][size] = G[i][v];
Gtemp[size][i] = G[i][v];
}
Gtemp[v][size] = 1;
Gtemp[size][v] = 1;

for (int i = 0; i < size; i++) {
free(G[i]);
}
free(G);
return Gtemp;
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
printf("\nГраф 1:\n");
printG(G1, sizeG1);
printf("\nГраф 2:\n");
printG(G2, sizeG2);

printf("\n=== Унарные операции ===\n");

// Отождествление вершин
printf("\nОтождествление вершин. Введите номера вершин (0-%d): ", sizeG1 - 1);
int v1, v2;
scanf("%d %d", &v1, &v2);
G1 = unionv(G1, sizeG1, v1, v2);
sizeG1--;
printG(G1, sizeG1);

// Стягивание ребра
printf("\nСтягивание ребра. Введите номера вершин (0-%d): ", sizeG1 - 1);
scanf("%d %d", &v1, &v2);
G1 = contrE(G1, sizeG1, v1, v2);
sizeG1--;
printG(G1, sizeG1);

// Расщепление вершины
printf("\nРасщепление вершины. Введите номер вершины (0-%d): ", sizeG1 - 1);
scanf("%d", &v1);
G1 = splitV(G1, sizeG1, v1);
sizeG1++;
printG(G1, sizeG1);

return 0;
}
