#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

void adauga_coada(int* coada, int* n, int element)
{
	coada[*n] = element;
	(*n)++;
}

int extrage_coada(int* coada, int* n)
{
	int element;
	element = coada[0];
	for (int i = 0; i < (*n) - 1; i++)
		coada[i] = coada[i + 1];
	(*n)--;
	return element;
}


void prietenie_directa(int** a, int u1, int u2) {
	if (a[u1 - 1][u2 - 1] == 1)
		printf("Exista legatura directa de prietenie.\n");
	else
		printf("Nu exista legatura directa de prietenie.\n");
}


void numar_prieteni(int** a, int v, int u) {
	int prieteni = 0;
	for (int i = 0; i < v; i++) {
		if (a[u - 1][i] == 1)
			prieteni++;
	}
	printf("Utilizatorul are %d prieteni.\n", prieteni);
}


void utilizatori_izolati(int** a, int v, char nume[50][50]) {
	printf("Utilizatorii fara relatii de prietenie sunt: ");
	for (int i = 0; i < v; i++) {
		int are_prieteni = 0;
		for (int j = 0; j < v; j++) {
			if (a[i][j] == 1) {
				are_prieteni = 1;
			}
		}
		if (are_prieteni == 0) {
			printf("%s ", nume[i]);
		}
	}
	printf("\n");
}


void roy_warshall(int** a, int v, int u1, int u2) {
	int i, j, k;
	int** m_drum = (int**)malloc(v * sizeof(int*));
	for (i = 0; i < v; i++)
		m_drum[i] = (int*)malloc(v * sizeof(int));

	for (i = 0; i < v; i++)
		for (j = 0; j < v; j++)
			m_drum[i][j] = a[i][j];

	for (k = 0; k < v; k++) {
		for (i = 0; i < v; i++) {
			for (j = 0; j < v; j++) {
				if (m_drum[i][k] == 1 && m_drum[k][j] == 1) {
					m_drum[i][j] = 1;
				}
			}
		}
	}

	if (m_drum[u1 - 1][u2 - 1] == 1)
		printf("Exista o conexiune directa/indirecta intre ei.\n");
	else
		printf("Nu exista nicio conexiune intre ei.\n");


	for (i = 0; i < v; i++)
		free(m_drum[i]);
	free(m_drum);
}

void adaugare_prietenie(int** a, int v, int* m, int u1, int u2) {
	a[u1 - 1][u2 - 1] = 1;
	a[u2 - 1][u1 - 1] = 1;
	(*m)++; 

	FILE* f = fopen("retea.txt", "w");
	fprintf(f, "%d %d\n", v, *m);
	for (int i = 0; i < v; i++) {
		for (int j = i + 1; j < v; j++) {
			if (a[i][j] == 1)
				fprintf(f, "%d %d\n", i + 1, j + 1);
		}
	}
	fclose(f);
	printf("Prietenia a fost adaugata cu succes!\n");
}


void stergere_prietenie(int** a, int v, int* m, int u1, int u2) {
	a[u1 - 1][u2 - 1] = 0;
	a[u2 - 1][u1 - 1] = 0;
	(*m)--; 
	FILE* f = fopen("retea.txt", "w");
	fprintf(f, "%d %d\n", v, *m);
	for (int i = 0; i < v; i++) {
		for (int j = i + 1; j < v; j++) {
			if (a[i][j] == 1)
				fprintf(f, "%d %d\n", i + 1, j + 1);
		}
	}
	fclose(f);
	printf("Prietenia a fost stearsa!\n");
}


void bfs_postare(int v0, int** a, int v, char nume[50][50]) {
	int nr_coada = 0, vf_curent;
	int* coada = (int*)malloc(v * sizeof(int));
	int* vizitat = (int*)malloc(v * sizeof(int));
	
	for (int i = 0; i < v; i++) {
		coada[i] = 0;
		vizitat[i] = 0;
	}
	
	adauga_coada(coada, &nr_coada, v0);
	vizitat[v0] = 1;
	
	while (nr_coada > 0)
	{
		vf_curent = extrage_coada(coada, &nr_coada);
		
		
		if (vf_curent != v0) {
			printf("Postarea a fost vazuta de %s\n", nume[vf_curent]);
		}
		
		for (int i = 0; i < v; i++)
		{
			if (a[vf_curent][i] == 1 && vizitat[i] == 0) {
				adauga_coada(coada, &nr_coada, i);
				vizitat[i] = 1;
			}
		}
	}
	free(coada);
	free(vizitat);
}

int main() {
	int v, m;
	

	FILE* f_retea = fopen("retea.txt", "r");
	fscanf(f_retea, "%d %d", &v, &m);

	int** a;
	a = (int**)malloc(v * sizeof(int*));
	for (int i = 0; i < v; i++)
		a[i] = (int*)malloc(v * sizeof(int));
		
	for (int i = 0; i < v; i++)
		for (int j = 0; j < v; j++)
			a[i][j] = 0;

	int vi, vf;
	for (int i = 0; i < m; i++) {
		fscanf(f_retea, "%d %d", &vi, &vf);
		a[vi - 1][vf - 1] = 1;
		a[vf - 1][vi - 1] = 1;
	}
	fclose(f_retea);


	char nume[50][50];
	int id_temp;
	FILE* f_utilizatori = fopen("utilizatori.txt", "r");
	for (int i = 0; i < v; i++) {
		fscanf(f_utilizatori, "%d %s", &id_temp, nume[i]);
	}
	fclose(f_utilizatori);

	int optiune;
	int u1, u2;

	do {
		printf("\n--- MENIU ---\n");
		printf("1. Prietenie directa\n");
		printf("2. Numar prieteni\n");
		printf("3. Utilizatori izolati\n");
		printf("4. Legatura indirecta\n");
		printf("5. Adauga prietenie\n");
		printf("6. Sterge prietenie\n");
		printf("7. Distribuire postare\n");
		printf("0. Iesire\n");
		printf("Optiune: ");
		scanf("%d", &optiune);

		if (optiune == 1) {
			printf("ID primul utilizator: "); scanf("%d", &u1);
			printf("ID al doilea utilizator: "); scanf("%d", &u2);
			prietenie_directa(a, u1, u2);
		}
		else if (optiune == 2) {
			printf("ID utilizator: "); scanf("%d", &u1);
			numar_prieteni(a, v, u1);
		}
		else if (optiune == 3) {
			utilizatori_izolati(a, v, nume);
		}
		else if (optiune == 4) {
			printf("ID primul utilizator: "); scanf("%d", &u1);
			printf("ID al doilea utilizator: "); scanf("%d", &u2);
			roy_warshall(a, v, u1, u2);
		}
		else if (optiune == 5) {
			printf("ID primul utilizator: "); scanf("%d", &u1);
			printf("ID al doilea utilizator: "); scanf("%d", &u2);
			adaugare_prietenie(a, v, &m, u1, u2);
		}
		else if (optiune == 6) {
			printf("ID primul utilizator: "); scanf("%d", &u1);
			printf("ID al doilea utilizator: "); scanf("%d", &u2);
			stergere_prietenie(a, v, &m, u1, u2);
		}
		else if (optiune == 7) {
			printf("ID-ul celui care posteaza: "); scanf("%d", &u1);
			bfs_postare(u1 - 1, a, v, nume);
		}

	} while (optiune != 0);

	for (int i = 0; i < v; i++)
		free(a[i]);
	free(a);

	return 0;
}
