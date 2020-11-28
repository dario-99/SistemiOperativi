COSTANTI in PROCEDURE.h:
    ITERAZIONI: numero di volte che i processi devono ripetere la mansione [DEFAULT = 10]

    NUM_GENERATORI: Numero di processi GENERATORI da istanziare nel main [DEFAULT = 1]
    NUM_ELABORATORI: Numero di processi ELABORATORI da istanziare nel main [DEFAULT = 1]
    NUM_ANALIZZATORI: Numero di processi ANALIZZATORI da istanziare nel main [DEFAULT = 2]

    MAX_SIZE: Massima lunghezza della stringa in memoria condivisa [DEFAULT = 16]

    FTOK_CHAR e FTOK_PATH: i parametri condivisi che devono usare i processi per avere la stessa area di memoria condivisa [DEFAULT = ("./", 'd')]

    SYNCH e MUTEX_L: ALIAS dei due semafori usati

MAKEFILE:
    all: tutti gli eseguibili
    clean: regola per cancellare tutti i .o ed eseguibili

ALTRE INFO:
    Ho deciso di utilizzare un puntatore a void, per gestire la Shared memory, per avere il controllo totale sulla quantita' di info da memorizzare.
    E poi grazie all'aritmetica dei puntatori e il casting mi sono ricavato le info, quindi la stringa e l'intero n_lettori.