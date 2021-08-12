/**
 * @file InOut.h
 * @brief plik zawiekaj¹cy klase bazow¹ Memory
 */
#pragma once
#include "stdafx.h"

 /** Klasa Uk³adu wejœcia/wyjœcia */
class InOut
{
public:
	/** Konstruktor klasy InOut	*/
	InOut();
	/** Dekonstruktor klasy InOut	*/
	~InOut();
	/** Funkcja drukowania symbolu na ekran
	 * @param data znak do wypisania na ekran
	 * @param mode tryb w jaki znak ma byæ wypisany na ekran
	 */
	void print(const uchar data, const char mode);

	/** Funkcja pobierania znaku z klawiatury
	 * @param character znak do pobrania
	 * @return wartoœæ bitowa sprawdzaj¹ca czy jakiœ znak zosta³ nacisiêty
	 */
	bool getInput(char& character);
};

