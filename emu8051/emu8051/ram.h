/**
 * @file ram.h
 * @brief plik zawiekaj�cy obiekt klasy RAM
 */
#pragma once

#include "stdafx.h"
#include "Memory.h"


#define RAM_SIZE 256  ///< makrodefinicja rozmiaru pami�ci RAM

 /** Klasa pami�ci RAM */
class RAM : public Memory
{
public:
	/** Konstruktor klasy RAM
	 * @param size rozmiar pami�ci
	 */
	RAM(const ushort size);

	/** Dekonstruktor klasy RAM	 */
	~RAM();

	/** Funkcja do inicjalizacji pami�ci RAM  */
	void initialize();
};

