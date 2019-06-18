#include "../serialPort.h"
#include <iostream>
#include "stdlib.h"

char COM[4] = {'C', 'O', 'M', '4'};
serialPort port(COM);

int main(){
    char message;
    port.open(9600);

    for(;;){
        std::cin >> message;
        port.write(*message, 1);
        _sleep(3);
    }
}