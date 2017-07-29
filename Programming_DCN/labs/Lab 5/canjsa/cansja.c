int main(void)
{
	unsigned char btr0 = 0x03, btr1 = 0x1C;
	unsigned int IdTx;
	int j = 0;

	/* Initieringar och registeravläsning */
	USART_Init();                 // Initierar USART
	USART_Flush();                // Rensar RS232-bufferten
	LCD_Init();                   // Initierar LCD
	DDRA = 0xFF;                  // Sätter Port A på STK200-kortet för bussar till/från CAN-kontroller
	DDRB = 0xFF;                  // Sätter Port B på STK200-kortet för LED:s (data output, obs flera olika kontakttyper)
								  // Sätter Port C på STK200-kortet för LCD (data output)
	DDRD = 0x00;                  // Sätter Port D på STK200-kortet för bussar till/från CAN-kontroller
								  // Sätter Port E på STK200-kortet för NC
	SJA_Init(&btr0, &btr1);       // Initierar CAN-kontrollerna SJA1000 till 125 kbit
	SJA_Dump();		           // Visar CAN-registren på terminalen via RS232-porten
							   // Status bör vara 0C, om inte starta om med Powerknappen
							   // (Observera att några SJA1000-register inte kan avläsas i körläget)

							   /* Visar text på LCD */
	LCD_Clean(LINE1);             // Rensar LCD-rad 1 och gå till början av den
	LCD_StrOut(MSG1);             // Matar ut titeln på LCD-rad 1
	LCD_Clean(LINE2);             // Rensar LCD-rad 2 och gå till början av den

								  /* Läser in IdTx och skickar en ram på CAN-bussen */
	IdTx = USART_ReceiveIdTx();   // Läser in Tx-identifieraren från terminalens tangentbord
	CAN_StrOut(IdTx, &MSG2[0]);   // Skickar dataram på CAN med texten "xxx ON-LINE ", där xxx = IdTx

								  /* Evighetsloop */
	while (1)
	{
		if (SJA_Read(CAN_STATUS) & RBS)  
// Kontrollerar om ram har kommit in till CAN-kontrollerns Rx
		{
			CAN_Check();               
// Hämtar in IdRx och meddelande från CAN-kontroller och visar på LCD


			/* Övning D:2 - Beräknar IdRx utifrån registervärden */

			unsigned int IdRx = 0;
			unsigned char tmp1 = 0, tmp2 = 0;

			tmp1 = SJA_Read(CAN_RX_ID);
			tmp2 = SJA_Read(CAN_RX_LEN);

			if (SJA_Read(CAN_STATUS) & RBS)
			{
			IdRx = ((unsigned int)tmp1 << 3) + ((tmp2 >> 5) & 0x07);
			}

			
/* Övning D:4 - Filter för inkommande identifierare. 
			Alla andra uppgifter är inuti denna if-sats */

/* IdRx-filter för Nod A står först, Nod B under */
			if(IdRx == 0x002 || IdRx == 0x007 || IdRx == 0x00C) 
             			//if(IdRx == 0x000 || IdRx == 0x005 || IdRx == 0x00A)
			{

			/* Övning D:3 - Utskrift av inkommande meddelanden */

				int i = 0;
				char R[9];

				for(i; i < 8; i++)
				{
				R[i] = SJA_Read(CAN_RX_BUF0 + i);
				}

				R[8] = '\0';

				prints("Medd: ");
				prints(R);
				prints("\n");


		/* Övning D:1 - Beräknar IdTx och skriver ut det på terminalen */

				unsigned int x1, x2;

				x1 = IdTx / 256;
				x2 = IdTx - x1 * 256;

				prints("IdTx = ");
				printh(x1);
				printh(x2);
				prints("\n");


		/* Övning D:5 - Beräknar IdTxAck(IdTx+1) och skriver ut på terminalen */

				/* IdTx = 0000 för Nod A 
IdTxAck blir 0001 och skickas till Nod B */
/* IdTx = 0001 för Nod B
IdTxAck blir 0002 och skickar till Nod A*/
				unsigned int IdTxAck = IdTx + 1;

				x1 = IdTxAck / 256;
				x2 = IdTxAck - x1 * 256;

				prints("IdTxAck = ");
				printh(x1);
				printh(x2);
				prints("\n");


		/* Övningen D:2 - Beräknar IdRx och skriver ut på terminalen */

				x1 = IdRx / 256;
				x2 = IdRx - x1 * 256;

				prints("RX = ");
				printh(x1);
				printh(x2);
				prints("\n");


/* Övning D:6 - Skickar över en ACKNOW till motsvarande nod för att bekräfta mottagen meddelande */

/* Mottagen IdTxAck för Nod B från Nod A visas i deras display som RX 0001 och blir IdRx för att skicka tillbaka deras Ack-meddelande som koden i else-if satsen visar, vice versa för mottagen IdTxAck för Nod A från Nod B visas i Nod A:s display som RX 0003 och går in i else-if satsen längre ned */
				SJA_Write(CAN_TX_ID, IdTxAck >> 3);
				SJA_Write(CAN_TX_LEN, (IdTxAck << 5) | 8);

				int i;
				char ackmessage = ['ACKNOW-'];

				for (i = 0; i <= 6; i++)
				{
				SJA_Write(CAN_TX_BUF0 + i, ackmessage[i]);
				}

			// Skriver ut ACKNOW nummer i slutet av bufferten
			// j har deklarerats innan while-loopen
				SJA_Write(CAN_TX_BUF7, j + 48);
				j = (j + 1) % 10;

				SJA_Write(CAN_CMD, TXREQ);

			}
			else if (IdRx == 0x003) //Nod A	
			//else if (IdRx == 0x001) //Nod B
//ACKNOW identifierare. Skriver ut ACK-medd
			{
				int i = 0;
				char R[9];

				for (i; i < 8; i++)
				{
				R[i] = SJA_Read(CAN_RX_BUF0 + i);
				}

				R[8] = '\0';

				prints("Ack: ");
				prints(R);
				prints("\n");

			}
	
			SJA_Write(CAN_CMD, RRB); // Frigör Rx-bufferten

		}

		if (USART_KbHit()) CAN_MessOut(IdTx);  
		// Om det finns data att skicka, hämtar detta från terminalen
		// flyttar över data till CAN-kontrollern (SJA1000) och
		// skickar ut det på CAN-bussen
	}
}

