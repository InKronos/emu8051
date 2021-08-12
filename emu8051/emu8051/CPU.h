/**
 * @file CPU.h
 * @brief plik zawiekaj¹cy klase CPU
 */
#pragma once
#include "stdafx.h"
#include "ram.h"
#include "rom.h"
#include "InOut.h"

 /** Klasa procesora */
class CPU
{
	ushort pc; ///< licznik programu

	RAM ram; ///< Obiekt pamiêci RAM
	ROM rom; ///< Obiekt pamiêci ROM
	InOut io; ///< Obiekt uk³adu wejœcia/wyjœcia
public:
	/** Konstruktor klasy CPU
	 * @param filename nazwa pliku instrukcji
	 */
	CPU(std::string filename);

	/** Dekonstruktor klasy CPU */
	~CPU();

	 /** Funkcja uruchamiania procesora */
	void run();

	/** Funkcja zwracaj¹ca licznik prgramu
	* @return licznik programu
	*/
	ushort getPC();

private:
	/** Funkcja zwracaj¹ca flage przeniesienia Carry
	* @return flaga przeniesienia
	*/
	uchar getPSW_C();		

	/** Funkcja zwracaj¹ca dodatkow¹ flage przeniesienia Carry
	* @return dodatkowa flaga przeniesienia
	*/
	uchar getPSW_AC();		

	/** Funkcja zwracaj¹ca flage 0
	* @return flaga 0
	*/
	uchar getPSW_F0();		

	/** Funkcja zwracaj¹ca Register bank selection bit 1
	* @return Register bank selection bit 1
	*/
	uchar getPSW_RS1();

	/** Funkcja zwracaj¹ca Register bank selection bit 0
	* @return Register bank selection bit 0
	*/
	uchar getPSW_RS0();	

	/** Funkcja zwracaj¹ca flage Przepe³nienia
	* @return flage przepe³nienia
	*/
	uchar getPSW_OV();		

	/** Funkcja zwracaj¹ca flage przystoœci
	* @return flage parzystoœci
	*/
	uchar getPSW_P();		

	/** Funkcja ustawiaj¹ca flage przeniesienia Carry
	* @param bit bit zmiany
	*/
	void setPSW_C(const bool bit);

	/** Funkcja ustawiaj¹ca flage dodatkowego przeniesienia Carry
	* @param bit bit zmiany
	*/
	void setPSW_AC(const bool bit);

	/** Funkcja ustawiaj¹ca flage 0
	* @param bit bit zmiany
	*/
	void setPSW_F0(const bool bit);

	/** Funkcja ustawiaj¹ca egister bank selection bit 1
	* @param bit bit zmiany
	*/
	void setPSW_RS1(const bool bit);

	/** Funkcja ustawiaj¹ca egister bank selection bit 0
	* @param bit bit zmiany
	*/
	void setPSW_RS0(const bool bit);

	/** Funkcja ustawiaj¹ca flage przeniesienia Carry
	* @param bit bit zmiany
	*/
	void setPSW_OV(const bool bit);

	/** Funkcja ustawiaj¹ca flage parzystoœci
	* @param bit bit zmiany
	*/
	void setPSW_P(const bool bit);

	/** Funkcja zwracaj¹ca 16-bitowy wskaŸnik adresu danych 
	* @return 16-bitowy wskaŸnik adresu danych 
	*/
	ushort getDPTR();

	/** Funkcja ustawiaj¹ca 16-bitowy wskaŸnik adresu danych 
	* @param address adres wskaŸnika
	*/
	void setDPTR(const ushort address);

	/** Funkcja zwracaj¹ca adres rejestru na podstawie kodu operacji
	* @param opcode kod operacji
	*/
	uchar returnRegisterAddres(uchar opcode);


	/** Funkcja obs³ugi kodów operacyjnych
	* @param opcode kod operacji
	*/
	void opcodesHandler(const uchar opcode);
};

