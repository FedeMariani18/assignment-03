RELAZIONE

DBS:
Il dbs è sia sincrono che asincrono, queste due modalità sono fuse per utilizzare il meglio di entrambi per casi ben diversi.
La parte sincrona è quella dell'aggiornamento dei dati da mostrare nella DashBoard del DBS, 
infatti avere un comportamento sincrono in questo caso ci permette di avere sempre i dati aggiornati in base ad un intervallo di tempo
scelto da noi. Ciò ci permette di non rischiare un rallentamento causato dall'arrivo di tanti messaggi in poco tempo, a causa magari di un cambio molto veloce dei dati,
ma allo stesso tempo di rimanere molto aggiornati sugli ultimi aggiornamenti senza paura di perdere troppe informazioni.
La parte asincrona invece è quella dell'inivio dei dati al server nel caso di premuta del bottone per switchare modalità o di modifica dello slider per la percenutale di apertura della valvola
che avviene attraverso gli EventHandler nel js.
Il punto forte di questo approccio è che non mandiamo mai messaggi inutili e ripetitivi, ma li mandaiamo solo quando davvero vogliamo modificare lo stato del nostro sistema.
