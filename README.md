# gauleses
Problema de concorrência de Javalis e Gauleses

Uma tribo gaulesa janta em comunidade a parr de uma mesa enorme com espaço para M javalis grelhados. Quando um gaulês quer comer, serve-se e rera um javali da mesa a menos que esta já esteja vazia. Nesse caso o gaulês acorda o cozinheiro e aguarda que este reponha javalis na mesa. O código seguinte representa o código que implementa o gaulês e o cozinheiro.

void Gaules(){
  while(true){
    Javali j = RetiraJavali();
    ComeJavali(j);
  }
}
void Cozinheiro(){
  while(true){
    ColocaJavalis(M);
  }
}

![](https://github.com/geanceretta/gauleses/blob/master/cenario.svg)

Implemente o código das funções   e   incluindo código de sincronização que previna deadlock e acorde o cozinheiro apenas quando a mesa está vazia.
Lembre que existem muitos gauleses e apenas um cozinheiro.
Idenfique regiões crícas na vida do gaules e do cozinheiro.
A solução deve aceitar um numero N de gauleses igual ao número de letras de seu primeiro nome e 1 único cozinheiro.
Cada javali terá um nome, dado pela letra correspondente
– Ex: dalcimar = 8 javalis
Cada Javali deve imprimir na tela seu nome (dado pela letra) quando come e quando acorda o cozinheiro.
– Ex: Javali d(0) comendo
– Ex: Javali a(1) acordou cozinheiro
A quandade javalis grelhados M deve ser igual ao número dos dois primeiros dígitos de seu RA
A solução não deve ter nenhum comentário
