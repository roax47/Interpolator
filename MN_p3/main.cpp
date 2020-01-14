#include "Matrix.h"
#include "Points.h"
#include <iostream>    
#include <fstream>      
#include <stdio.h>
#include <string>
#include <conio.h>



void bubbleSort(Points arr[], int n)
{
	int i, j;
	Points temp;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j].x > arr[j + 1].x) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}			
}

void printMenu(bool random_spread) {
	std::cout << "F1 - podziel na 2" << std::endl << "F2 - podziel na 4" << std::endl
		<< "F3 - podziel na 8" << std::endl << "F4 - podziel na 16" << std::endl
		<< "F5 - podziel na 32" << std::endl << "F6 - podziel na 64" << std::endl
		<< "F7 - podziel na 128" << std::endl << "F8 - podziel na 256" << std::endl
		<< "Przedzialy: " << (random_spread ? "losowe" : "rownomierne") << " | F9 aby zmienic" << std::endl <<std::endl;
}
int main(int argc, char * argv[]) {


	int len = 0;
	int sign = 0;
	int new_size;
	Points *tab = nullptr;
	Points *apx = nullptr;
	bool random_spread = false;

	if (argc != 2) return 0;
	std::fstream input(argv[1]);
	
	if (input.is_open()) {
		std::string unused;
		while (std::getline(input, unused))
			len++;
		input.clear();
		input.seekg(0, input.beg);
		tab = new Points[len];
		for (int i = 0; i < len; i++) {
			input >> tab[i].x && std::getline(input, unused, ',') && input >> tab[i].y;
		}
	}

	printMenu(random_spread);

	while (sign != 27)
	{
		sign = _getch();
		if (sign == 0)
		{
			sign = _getch();
			if (sign == 67) {//F9
				random_spread = !random_spread;
				printMenu(random_spread);
			}
			else if (sign == 59) //F1
			{
				new_size = len / 2;
			}
			else if (sign == 60) //F2
			{
				new_size = len / 4;
			}
			else if (sign == 61) //F3
			{
				new_size = len / 8;
			}
			else if (sign == 62) //F4
			{
				new_size = len / 16;
			}
			else if (sign == 63) //F5
			{
				new_size = len / 32;
			}
			else if (sign == 64) //F6
			{
				new_size = len / 64;
			}
			else if (sign == 65) //F7
			{
				new_size = len / 128;
			}
			else if (sign == 66) //F8
			{
				new_size = len / 256;
			}
			if (sign >= 59 && sign <= 66) {
				apx = new Points[new_size];
				//Rozmieszczenie przedzia³ów
				if (!random_spread) {
					for (int i = 0; i < new_size; i++) {
						apx[i] = tab[i * len / new_size];
					}
					apx[new_size - 1] = tab[len - 1];
				}
				else {
					apx[0] = tab[0];
					apx[new_size - 1] = tab[len - 1];
					int x = 0;
					for (int i = 1; i < new_size-1; i++) {
						bool duplicate = true;
						while (duplicate) {
							x = rand() % (len - 2) + 1;
							duplicate = false;
							for (int j = 1; j < i; j++)
								if (tab[x].x == apx[j].x) {
									duplicate = true;
									break;
								}
						}
						apx[i] = tab[x];
					}
					bubbleSort(apx, new_size);
				}
				
				int *intervals = new int[len];
				double left = apx[0].x;
				double right = apx[1].x;
				int interval = 0;
				for (int i = 0; i < len; i++) {
					if (tab[i].x >= left && tab[i].x <= right) intervals[i] = interval;
					else {
						interval++;
						left = right;
						right = apx[interval + 1].x;
						intervals[i] = interval;
					}
				}

				std::ofstream file("lagrangex.txt"), file2("lagrangey.txt");
				if (file.is_open() && file2.is_open())
				{
					for (int i = 0; i < len; i++) {
						file << tab[i].x << std::endl;
						file2 << Points::Lagrange(apx, tab[i].x, new_size) << std::endl;
					}
				}
				std::cout << std::endl << "Saved to file lagrangex.txt & lagrangey.txt" << std::endl << std::endl;

				std::ofstream file3("splinex.txt"), file4("spliney.txt");
				if (file3.is_open() && file4.is_open())
				{
					Matrix x = Matrix(4*(new_size-1), 1);
					Points::Splines(apx, x, new_size - 1);
					for (int i = 0; i < len; i++) {
						
						file3 << tab[i].x << std::endl;
						file4 << Points::ThirdDegreePolymonial(x, tab[i].x-apx[intervals[i]].x,intervals[i])<< std::endl;
					}

				}
				std::cout << std::endl << "Saved to file splinex.txt & splinexy.txt" << std::endl << std::endl<<std::endl;
				printMenu(random_spread);
			}
		}
	}
	delete(apx);
	delete(tab);
	return 0;
}



