//#************************************************************************
//#*
//#* Copyright (C) 2024 Damian-Software
//#* All rights reserved.
//#*
//#* Author: Damián Zelený
//#* Contact: (dzeleny@recvsoftware.com)
//#*
//#************************************************************************
//#
#include "common.h"

//! Tento kód implementuje základní TCP server, který:
//! Vytváří soket pro TCP spojení,
//! Nastaví možnost opakovaného použití adresy(SO_REUSEADDR),
//! Binduje soket k určitému portu,
//! Přijímá připojení od klientů a čte jejich data,
//! Uzavírá připojení po skončení komunikace nebo při chybě.
//! Každá část kódu je ošetřena pro chyby pomocí funkce perror, která poskytuje detaily o systémových chybách.


// Toto je hlavní vstupní bod programu. main
// Argumenty argc a argv[] umožňují předání parametrů z příkazové řádky,
// i když v tomto konkrétním případě nejsou využity.
// Program může přijmout vstupy, pokud byste je chtěli později přidat.
int main(int argc, char* argv[])
{
	// Funkce socket vytváří nový socket.
	// AF_INET znamená, že se jedná o IPv4 adresu.
	// SOCK_STREAM znamená, že jde o TCP spojení (spolehlivé, streamově orientované přenosy).
	// IPPROTO_TCP definuje, že se používá protokol TCP.
    int serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == 0x0)
	{
		// Pokud vytvoření socketu selže, funkce socket vrací hodnotu 0 (chybový stav),
		// což vede k vypsání chyby pomocí perror("socket") a ukončení programu s návratovým kódem 1.
		perror("socket");
		return 1;
	}
	
	int flag = 1;
	// Nastavení soketu pro opakované použití adresy.... Musí být před bind ihned po socketu !!!
	// Funkce setsockopt umožňuje nastavení možností soketu.
	// SO_REUSEADDR umožňuje znovupoužití adresy, což je užitečné, pokud server skončí a chceme znovu použít stejný port bez čekání na jeho uvolnění.
	// Tento blok musí být zavolán před funkcí bind, aby správně fungoval.!!!
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&flag, sizeof(flag)) < 0x0)
	{
		perror("setsockopt");
		return 1;
	}

	// Inicializace struktury sockaddr_in
	// Tato struktura definuje adresu a port serveru.
	// sockaddr_in je struktura specifická pro IPv4 adresy a obsahuje důležité informace,
	// jako je port a IP adresa, kterou server používá.
	struct sockaddr_in serverAddr { };

	// Nastavení adresy serveru
	// sin_family: Určuje, že se jedná o adresu IPv4 (AF_INET).
	// sin_addr.s_addr = INADDR_ANY: Nastavuje server tak, aby akceptoval připojení na všech dostupných rozhraních (např. všechna IP adresy přiřazená k serveru).
	// sin_port = htons(13000): Nastavuje port serveru na 13000. Funkce htons převádí číslo portu z lokálního formátu hostitele na síťový formát (big-endian).
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY; // Všechna dostupná rozhraní
	serverAddr.sin_port = htons(13000); // Port serveru

	// Přiřazení soketu k adrese (bind)
	// Funkce bind spojuje soket s konkrétní adresou (IP a port).
	// Pokud bind selže (vrací hodnotu menší než 0), vypíše se chybové hlášení a program se ukončí s návratovým kódem 1.
	if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		perror("bind");
		return 1;
	}

	// Přepnutí soketu do pasivního režimu (listen)
	// Funkce listen přepne soket do pasivního režimu, kde čeká na příchozí připojení.
	// SOMAXCONN určuje maximální počet klientských připojení ve frontě, které může server najednou zpracovávat.
	// Pokud listen selže, vypíše se chybové hlášení a program se ukončí s návratovým kódem 1.
	if (listen(serverSocket, SOMAXCONN) < 0)
	{
		perror("listen");
		return 1;
	}

	// Buffer pro příjem dat
	char buffer[1024]; // Vytvoření pole buffer o velikosti 1024 bytů, které bude sloužit k uložení dat přijatých od klienta.

	// Hlavní smyčka serveru
	while (true)
	{
		sockaddr_in client_addr{};	// Klient, který se připojil 
		socklen_t client_len = sizeof(client_addr);		// Velikost adresy vzdáleného počítače

		// Přijetí nového připojení
		// Funkce accept přijímá nové příchozí připojení od klienta.
		// serverSocket: Soket serveru, který čeká na připojení.
		// client_addr: Struktura, kam se uloží IP adresa a port klienta.
		// client_len: Velikost struktury client_addr.
		int ClientConnect = accept(serverSocket, (struct sockaddr*)&client_addr, &client_len); // Přijetí klientského připojení

		// Pokud přijetí selže (vrátí hodnotu menší než 0), vypíše se chybové hlášení a serverový soket se uzavře.
		if (ClientConnect < 0)
		{
			perror("accept");
			close(serverSocket);
			return 1;
		}

		// Smyčka pro příjem dat od klienta
		while (true)
		{
			// Funkce recv čte data od klienta připojeného k soketu ClientConnect
			int bytes_recived = recv(ClientConnect, buffer, sizeof(buffer), 0);	// Příjem dat od klienta

			// Pokud počet přijatých bytů (bytes_recived) je větší než 0, data se správně zpracují,
			// přidá se koncový nulový znak (pro bezpečnost) a vypíší se do konzole.
			if (bytes_recived > 0)
			{
				// Zpracuj přijatá data
				// Ošetření nulového znaku (pro případ, že by data byla interpretována jako řetězec)
				buffer[bytes_recived] = '\0';
				std::cout << "Přijata zpráva :" << buffer << std::endl;
				continue;

			}
			else if (bytes_recived == 0) 
			{
				// Pokud je hodnota bytes_recived == 0, to znamená, že klient uzavřel spojení,
				// a dojde k uzavření klientského soketu (ClientConnect) a opuštění smyčky.

				// Spojení bylo uzavřeno
				std::cout << "Spojení ukončeno." << std::endl;
				close(ClientConnect);   // Zavření socketu po ukončení komunikace s klientem
				break;
			}
			else 
			{
				// Pokud bytes_recived < 0, došlo k chybě při přijímání dat a soket se uzavře.

				// Chyba při čtení
				std::cerr << "Chyba při přijímání dat." << std::endl;
				close(ClientConnect);   // Zavření socketu po ukončení komunikace s klientem
				break;
			}

		}

	}

	// Ukončení serveru
	// Po ukončení všech připojení nebo po chybě se soket serveru uzavře pomocí funkce close.
	close(serverSocket);


	// Program se ukončí s návratovým kódem 0, což značí úspěšné dokončení operace.
    return 0;
}

