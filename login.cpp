#include <iostream>
using namespace std;
#include <cstdlib>
#include <ctime>

struct Login{
    string username;
    string senha;
};

void preencher_logins(Login *usuarios,int quant){
    for(int i = 0;i<quant;i++){
        cout << "digite o username do " << i+1 << " usuario: ";
        cin >> usuarios[i].username;
        cout << "digite a senha do " << i+1 << " usuario: ";
        cin >> usuarios[i].senha;
    }
}

double** criar_matriz(int lin,int col){
    double** matriz = new double *[lin];
    for(int i = 0;i<lin;i++){
        matriz[i] = new double[col];
    }
    return matriz;
}

int buscar(Login *usuarios,int quant, string para){
    for(int i = 0;i<quant;i++){
        if(usuarios[i].username == para){
            return i;
        }else{
            return -1;
        }
    }
}

double sorteio(){
    double quantia;
    unsigned seed = time(0);
    srand(seed);
    quantia = (1+ rand() %9) * 100;
    return quantia;
}

void calcular_investimento(double** matriz, double quantia,int col){
    double valor1,valor2,valor3;
    valor1 = quantia;
    valor2 = quantia;
    valor3 = quantia; 
    for(int i = 0;i<col;i++){
        matriz[0][i] = valor1;
        valor1 *= 1.005;
    }
    for(int i = 0;i<col;i++){
        matriz[1][i] = valor2;
        valor2 *= 1.01;
    }
    for(int i = 0;i<col;i++){
        matriz[2][i] = valor3;
        valor3 *= 1.02;
    }
}

void imprimir_matriz(double** matriz,int col){
    cout << "investimento 1: ";
    for(int i = 0;i<col;i++){
        cout << matriz[0][i] << " - ";
    }
    cout << endl;
    cout << "investimento 2: ";
    for(int i = 0;i<col;i++){
        cout << matriz[1][i] << " - ";
    }
    cout << endl;
    cout << "investimento 3: ";
    for(int i = 0;i<col;i++){
        cout << matriz[2][i] << " - ";
    }
    cout << endl;
}

int main(){
    cout << "bem-vindo ao banco inside LTDA!" << endl;
    int quant;
    cout << "quantos usuarios deseja cadastrar? ";
    cin >> quant;
    Login *usuarios = new Login[quant];
    preencher_logins(usuarios,quant);
    string username,senha;

    //conferir usuario digitado
    int index;
    do{
    cout << "nome de usuario: ";
    cin >> username;
    index = buscar(usuarios,quant,username);
    if(index == -1){
        cout << "usuario invalido digite novamente" << endl;
        }
    } 
    while(index == -1);

    //conferir senha digitada
    do {
        cout << "senha: ";
        cin >> senha;
        if(usuarios[index].senha != senha){
            cout<< "senha invalida digite novamente" << endl;
        }
    }
    while(usuarios[index].senha != senha);

    //definir quantia
    double quantia = sorteio();

    //inicializar sistema
    cout<< "seja bem-vindo " << usuarios[index].username << endl;
    cout << "seu montante em dinheiro e de " << quantia << "RS" << endl;
    cout << " qual acao deseja realizar?" << endl;
    int dec;
    double valor;
    int linhas,meses;
    linhas = 3;
    int continuar;
    int lixo;
    do{
        cout<< "opcao[1] sacar, opcao[2] depositar, opcao[3] investir: ";
        cin >> dec;
        switch (dec){
        case 1:
            cout << "quanto deseja sacar? ";
            cin >> valor;
            if(valor <= quantia){
                quantia -= valor;
                cout << "saque de " << valor << "RS concluido" << endl;
                cout << "seu novo saldo e de " << quantia << "RS " << endl;
            }else{
                cout << "quantia que deseja sacar excede quantidade de dinheiro em conta" << endl;
            }
            break;
        case 2:
            cout << "valor do deposito: ";
            cin >> valor;
            quantia += valor;
            cout << "deposito de " << valor << "RS concluido" << endl;
            cout << "seu novo saldo e de " << quantia << "RS" << endl;
            break;
        case 3:
            cout << "quanto deseja investir? ";
            cin >> valor;
            if(valor > quantia){
                cout << "quantia que deseja investir excede quantidade de dinheiro em conta" << endl;
            }else{
                cout << "quantos meses deseja calcular o investimento? ";
                cin >> meses;
                cout << "tabela de investimentos: " << endl;
                double **matriz_investimentos = criar_matriz(linhas, meses);
                calcular_investimento(matriz_investimentos,valor,meses);
                imprimir_matriz(matriz_investimentos,meses);
                cout << "o investimento 1 tem baixo risco e uma rentabilidade baixa, o 2 tem risco medio e rentabilidade media, o 3 tem risco alto e rentabilidade alta" << endl;
                cout << "em qual deseja investir? ";
                cin >> lixo;
                quantia -= valor;
                }
            cout << "seu novo saldo e de " << quantia << "RS" << endl;
            break;
        }
        cout << "deseja continuar[1] ou sair[0]? ";
        cin >> continuar;
    }
    while((dec < 1 and dec > 3) or continuar == 1);

    //fim do programa
    cin >> lixo;
    return 0;
}