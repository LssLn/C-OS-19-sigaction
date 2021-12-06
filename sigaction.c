//VIENE FATTA PER RENDERE PIU' ROBUSTA LA GESTIONE DEI SEGNALI, signal()
//se nella funzione, prima di reimpostare l'handler, ricevo un'altro segnale uguale, seguirà l'effetto DFL
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void f(int sig){
    printf("Segnale ricevuto n %d",sig);
    //signal(SIGINT,f); //non serve nella sigaction reimpostare l'handler
}

int main(){
    struct sigaction act;
    act.sa_handler=f; //motivo per cui non serve reimpostare l'handler in f
    sigemptyset(&act.sa_mask);
    //inizializza NULL tutti i valori della maschera segnali, cioè si va riempiendo man mano che viene invocata la f
    act.sa_flags=0; //no flags, SA_NODEFER e SA_RESETHAND
    sigaction(SIGINT,&act,0);
    
    while(1){
        printf("Hell");
        sleep(1);
    }
}
