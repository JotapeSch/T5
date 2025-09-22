#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXTO 10000
#define MAX_LINHA_compr 80
#define MAX_LINHAS 500

//------------- CHAMANDO FUNCOES ------------- 
void formatarTexto(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr+1]); 
void ImprimirFormatado(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]);
void BuscarPlavra(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], char *text);
void SubPrimOcorrencia(char *text);
void SubTodasOcorrencia(char *text);
void CaixaAlta(char *text);
void CaixaBaixa(char *text);
void PrimLetraMaiuFrase(char *text);
void AlinharEsquerda(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]);
void AlinharDireita(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]);
void Justificar(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1]);
void Centralizar(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1]);


//------------- IMPLEMENTACOES  -------------
// objetivo: Divide o texto em linhas com no máximo 80 caracteres, preservando palavras
// parametros: ponteiro para quantidade de linhas, texto original, matriz de linhas para armazenar o texto formatado
// retorno: nenhum
void formatarTexto(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr+1]){
    // Implementação pendente - JOTA
    int quantidade_linhas = 0;
    int inicio = 0, fim = inicio + MAX_LINHA_compr;
    int tamanho_texto = strlen(text);

    while (inicio < tamanho_texto){
        if (fim > tamanho_texto){
            fim = tamanho_texto; //Intuitivo, caso fim seja maior que o texto, eh so reduzir o final para o tamanho certo
        }

        //caso a palavra seja cortado no meio, a gente resolve isso, voltando no primeiro espaco ou \n encontrado
        while(fim > inicio && fim < tamanho_texto && text[fim] != ' ' && text[fim] != '\n'){
            fim--;
        }

        //caso a palavra seja maior que o limite de comprimento da linha, que eh 80, forcamos ela 
        if (fim == inicio) {
            fim = inicio + MAX_LINHA_compr;
            if (fim > tamanho_texto) 
                fim = tamanho_texto;
        }

        strncpy(linhas[quantidade_linhas], &text[inicio], fim - inicio);
        linhas[quantidade_linhas][fim - inicio] = '\0';
        quantidade_linhas++;
        inicio = fim + 1;
        fim = inicio + MAX_LINHA_compr;

        //verifico se o quantidade de linhas eh maior que o maximo permitido
        if (quantidade_linhas >= MAX_LINHAS) 
            break;

    }
}

// objetivo: Imprime o texto já formatado linha por linha
// parametros: quantidade de linhas, matriz de linhas contendo o texto formatado
// retorno: nenhum
void ImprimirFormatado(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]){
    // Implementação pendente - JOTA


    for(int i = 0; i < MAX_LINHAS; i++){
        if (linhas[i][0] == '\0') // só imprime se não for vazio
            break;

        printf("%s\n", linhas[i]);
    }
}

// objetivo: Procura uma palavra específica no texto e mostra suas ocorrências
// parametros: matriz de linhas contendo o texto, quantidade de linhas do texto
// retorno: nenhum
void BuscarPlavra(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], char *text){
    // Implementação pendente - JOTA
    char palavra_pra_encontrar[100];
    int encontrou = 0, j = 0;
    int linha_cont[200], valido = 1;

    do{
        printf("Digite a palavra para buscar: ");
        scanf(" %99s", palavra_pra_encontrar); // O espaço antes de %99s limpa o buffer
        while (getchar() != '\n'); // Limpa o buffer
        
        if (strlen(palavra_pra_encontrar) == 0){
            printf("Erro: Digite uma palavra válida (não pode estar vazia)!\n");
            continue;
        }


        for ( int i = 0; i < strlen(palavra_pra_encontrar); i++){
            if (!isalpha(palavra_pra_encontrar[i])){
                printf("Erro: A palavra deve conter apenas letras (A-Z, a-z)!\n");
                valido = 0;
                break;
            }
        }

        if (valido){
            break;
        }
    } while (1);

    for (int i = 0; i < MAX_LINHAS; i++){
        if (linhas[i][0] == '\0'){
            break;
        }

        if (strstr(text, palavra_pra_encontrar) != NULL){
            encontrou++;
            linha_cont[j] = i;
            j++;
        }
    }

    if (encontrou == 0){
        printf("Nao foi encontrada nenhuma ocorrencia\n");
    } else if (encontrou != 0){
        printf("Foram encontradas %d palavra(s) no texto nas seguintes linhas:\n", encontrou);
        for (int i = 0; i < j; i++){
            int indice_linha = linha_cont[i];
            printf("Linha %d: %s\n", indice_linha + 1, linhas[indice_linha]);
        }
    }
}

// objetivo: Substitui apenas a primeira ocorrência de uma palavra no texto
// parametros: texto original onde será feita a substituição
// retorno: nenhum
void SubPrimOcorrencia(char *text){
    // Implementação pendente - JOTA m
    
}

// objetivo: Substitui todas as ocorrências de uma palavra no texto
// parametros: texto original onde serão feitas as substituições
// retorno: nenhum
void SubTodasOcorrencia(char *text){
    // Implementação pendente - RYAN
}

// objetivo: Converte todo o texto para letras maiúsculas
// parametros: texto que será convertido para caixa alta
// retorno: nenhum
void CaixaAlta(char *text){
    // Implementação pendente - RYAN
}

// objetivo: Converte todo o texto para letras minúsculas
// parametros: texto que será convertido para caixa baixa
// retorno: nenhum
void CaixaBaixa(char *text){
    // Implementação pendente - RYAN
}

// objetivo: Capitaliza a primeira letra de cada frase no texto
// parametros: texto que terá as primeiras letras das frases capitalizadas
// retorno: nenhum
void PrimLetraMaiuFrase(char *text){
    // Implementação pendente - RYAN
}

// objetivo: Alinha todo o texto à esquerda (padrão)
// parametros: quantidade de linhas, matriz de linhas contendo o texto
// retorno: nenhum
void AlinharEsquerda(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]){
    // Implementação pendente - VINI
}

// objetivo: Alinha todo o texto à direita
// parametros: quantidade de linhas, matriz de linhas contendo o texto
// retorno: nenhum
void AlinharDireita(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]){
    // Implementação pendente - VINI
}

// objetivo: Justifica o texto (distribui espaços uniformemente entre palavras)
// parametros: matriz de linhas contendo o texto, quantidade de linhas
// retorno: nenhum
void Justificar(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1]){
    // Implementação pendente - VINI
}

// objetivo: Centraliza todas as linhas do texto
// parametros: matriz de linhas contendo o texto, quantidade de linhas
// retorno: nenhum
void Centralizar(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1]){
    // Implementação pendente - VINI
}
//-----------------------------------------------------

// objetivo: Exibe menu interativo e chama funções de formatação de texto conforme escolha do usuário
// parametros: texto original, matriz de linhas formatadas, ponteiro para quantidade de linhas
// retorno: nenhum
void Menu(char *texto, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1]){
    int opcao;
    do{
        printf("\n===== MENU =====\n");
        printf("1 - Imprimir texto formatado\n");
        printf("2 - Buscar palavra\n");
        printf("3 - Substituir primeira ocorrencia\n");
        printf("4 - Substituir todas as ocorrencias\n");
        printf("5 - Caixa alta\n");
        printf("6 - Caixa baixa\n");
        printf("7 - Primeira letra maiuscula por frase\n");
        printf("8 - Alinhar esquerda\n");
        printf("9 - Alinhar direita\n");
        printf("10 - Justificar\n");
        printf("11 - Centralizar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        
        // Validação de entrada
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer
            continue;
        }
        
        // Limpar buffer após scanf
        while (getchar() != '\n');
        
        switch (opcao)
        {
        case 1:
            // objetivo: Imprime o texto formatado
           
            ImprimirFormatado(linhas);
            break;

        case 2:
            // objetivo: Busca palavra no texto formatado
            
            BuscarPlavra(linhas, texto);
            break;

        case 3:
            // objetivo: Substitui primeira ocorrência e reformata texto
            
            SubPrimOcorrencia(texto);
            formatarTexto(texto, linhas);
            break;
        
        case 4:
            // objetivo: Substitui todas ocorrências e reformata texto
            
            SubTodasOcorrencia(texto);
            formatarTexto(texto, linhas);
            break;

        case 5:
            // objetivo: Converte para maiúsculas e reformata texto
            
            CaixaAlta(texto);
            formatarTexto(texto, linhas);
            break;

        case 6:
            // objetivo: Converte para minúsculas e reformata texto
            
            CaixaBaixa(texto);
            formatarTexto(texto, linhas);
            break;

        case 7:
            // objetivo: Capitaliza frases e reformata texto
            
            PrimLetraMaiuFrase(texto);
            formatarTexto(texto, linhas);
            break;
        
        case 8:
            // objetivo: Alinha texto à esquerda
            
            AlinharEsquerda(linhas);
            break;

        case 9:
            // objetivo: Alinha texto à direita
            
            AlinharDireita(linhas);
            break;

        case 10:
            // objetivo: Justifica o texto
            
            Justificar(linhas);
            break;

        case 11:
            // objetivo: Centraliza o texto
            
            Centralizar(linhas);
            break;   
            
        case 0:
            // objetivo: Sai do programa
            printf("Saindo do programa...\n");
            break;
            
        default:
            //Trata opção inválida
            
            printf("Opção inválida! Tente novamente.\n");
            break;
        }
    } while (opcao != 0);
}

int main()
{

    
    // Declaração do texto original sobre Bill Gates
    char text[MAX_TEXTO]="William Henry Gates III KBE GCIH (Seattle, 28 de outubro de 1955) mais conhecido como Bill Gates,\
 e um magnata, empresario, diretor executivo, investidor, filantropo e autor americano, que ficou conhecido por \
 fundar junto com Paul Allen a Microsoft a maior e mais conhecida empresa de software do mundo em termos de valor \
 de mercado. Gates ocupa atualmente o cargo de presidente nao-executivo da Microsoft alem de ser classificado \
 regularmente como a pessoa mais rica do mundo, posicao ocupada por ele de 1995 a 2007, 2009, e de 2014 a 2017. E \
 um dos pioneiros na revolucao do computador pessoal. Gates nasceu em uma familia de classe media de Seattle. Seu \
 pai, William H. Gates, era advogado de grandes empresas, e sua mae, Mary Maxwell Gates, foi professora da \
 Universidade de Washington e diretora de bancos. Bill Gates e as suas duas irmas, Kristanne e Libby, \
 frequentaram as melhores escolas particulares de sua cidade natal, e Bill tambem participou do \
 Movimento Escoteiro ainda quando jovem. Bill Gates, foi admitido na prestigiosa Universidade \
 Harvard, (conseguindo 1590 SATs dos 1600 possiveis) mas abandonou os cursos de Matematica e \
 Direito no terceiro ano para dedicar-se a Microsoft. Trabalhou na Taito com o desenvolvimento de \
 software basico para maquinas de jogos eletronicos (fliperamas) ate seus 16 anos. Tambem \
 trabalhou como pesquisador visitante na University of Massachusetts at Amherst, UMASS, Estados Unidos, quando \
 com 17 anos, desenvolveu junto com Paul Allen um software para leitura de fitas magneticas, com informacoes \
 de trafego de veiculos, em um chip Intel 8008. Com esse produto, Gates e Allen criaram uma empresa, \
 a Traf-o-Data, porem os clientes desistiram do negocio quando descobriram a idade dos donos. Enquanto \
 estudavam em Harvard, os jovens desenvolveram um interpretador da linguagem BASIC para um dos primeiros \
 computadores pessoais a serem lancado nos Estados Unidos - o Altair 8800. Apos um modesto sucesso na \
 comercializa��o deste produto, Gates e Allen fundaram a Microsoft, uma das primeiras empresas no mundo \
 focadas exclusivamente no mercado de programas para computadores pessoais ou PCs. Gates adquiriu ao \
 longo dos anos uma fama de visionario (apostou no mercado de software na epoca em que o hardware era \
 considerado muito mais valioso) e de negociador agressivo, chegando muitas vezes a ser acusado por \
 concorrentes da Microsoft de utilizar praticas comerciais desleais. Nos anos 1980, a IBM, lider \
 no mercado de grandes computadores, resolveu entrar no mercado da microinformatica com o PC, \
 porem faltava o Sistema Operacional. Para isso, fechou contrato com a recem-criada Microsoft. Todavia, \
 a Microsoft nao possuia o software ainda. O jovem Bill Gates foi a uma pequena empresa que havia \
 desenvolvido o sistema para o processador da Intel e decidiu compra-lo, pagou cerca de US$ 50 mil, personalizou \
 o programa e vendeu-o por US$ 8 milhoes, mantendo a licenca do produto. Este viria a ser o MS-DOS. \
 Fonte: https://pt.wikipedia.org/wiki/Bill_Gates";

    // Variáveis para controle do texto formatado
    
    char linhas[MAX_LINHAS][MAX_LINHA_compr+1];  // matriz para armazenar linhas formatadas
    
    // FORMATAR PELA PRIMEIRA VEZ
    formatarTexto(text, linhas);
    
    // CHAMA MENU
    Menu(text, linhas);


    return 0;  // Sucesso na execução
}