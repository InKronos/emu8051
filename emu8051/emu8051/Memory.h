/**
 * @file Memory.h
 * @brief plik zawiekaj�cy klase bazow� Memory
 */
#pragma once
#include "stdafx.h"
#include "helpFunctions.h"

 /** Klasa Pami�ci */
class Memory
{
	const  ushort size; ///< rozmiar pami�ci
	uchar *memory; ///< tablica pami�ci
public:
	/** Konstruktor klasy Memory
	 * @param size rozmiar pami�ci
	 */
	Memory(const ushort size);

	/** Deonstruktor klasy Memory */
	~Memory();

	/** Funkcja do ustawiania kom�rki pami�ci
	 * @param index indeks 
	 * @param value warto�� do wpisania
	 */
	void setMemoryCell(const size_t index, const uchar value);

	/** Operator pobrania kom�rki pami�ci
	 * @param index indeks
	 */
	uchar operator [] (const size_t index) const;

	/** Operator pobrania wska�nika kom�rki pami�ci
	 * @param index indeks
	 */
	uchar& operator [] (const size_t index);
};

