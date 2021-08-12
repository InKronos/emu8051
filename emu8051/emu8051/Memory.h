/**
 * @file Memory.h
 * @brief plik zawiekaj¹cy klase bazow¹ Memory
 */
#pragma once
#include "stdafx.h"
#include "helpFunctions.h"

 /** Klasa Pamiêci */
class Memory
{
	const  ushort size; ///< rozmiar pamiêci
	uchar *memory; ///< tablica pamiêci
public:
	/** Konstruktor klasy Memory
	 * @param size rozmiar pamiêci
	 */
	Memory(const ushort size);

	/** Deonstruktor klasy Memory */
	~Memory();

	/** Funkcja do ustawiania komórki pamiêci
	 * @param index indeks 
	 * @param value wartoœæ do wpisania
	 */
	void setMemoryCell(const size_t index, const uchar value);

	/** Operator pobrania komórki pamiêci
	 * @param index indeks
	 */
	uchar operator [] (const size_t index) const;

	/** Operator pobrania wskaŸnika komórki pamiêci
	 * @param index indeks
	 */
	uchar& operator [] (const size_t index);
};

