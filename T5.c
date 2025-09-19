#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXTO 10000
#define MAX_LINHA_compr 80
#define MAX_LINHAS 500

//------------- CHAMANDO FUNCOES ------------- 
void formatarTexto(){} 
void ImprimirFormatado(){}
void BuscarPlavra(){}
void SubPrimOcorrencia(){}
void SubTodasOcorrencia(){}
void CaixaAlta(){}
void CaixaBaixa(){}
void PrimLetraMaiuFrase(){}
void AlinharEsquerda(){}
void AlinharDireita(){}
void Justificar(){}
void Centralizar(){}
//---------------------------------------------


void formatarTexto(int *qtd_linhas, char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr+1]){} //JOTA
void ImprimirFormatado(int qtd_linhas, char linhas[MAX_LINHAS][MAX_LINHA_compr+1]){} //JOTA
void BuscarPlavra(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int qtd_linhas){}//JOTA
void SubPrimOcorrencia(char *text){}//JOTA
void SubTodasOcorrencia(char *text){} //RYAN
void CaixaAlta(char *text){}  //RYAN
void CaixaBaixa(char *text){} //RYAN
void PrimLetraMaiuFrase(char *text){} //RYAN
void AlinharEsquerda(int qtd_linhas, char linhas[MAX_LINHAS][MAX_LINHA_compr+1]){}//VINI
void AlinharDireita(int qtd_linhas, char linhas[MAX_LINHAS][MAX_LINHA_compr+1]){}//vini
void Justificar(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int qtd_linhas){} //VINI
void Centralizar(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int qtd_linhas){} //vini

void Menu(char *texto, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int *qtd_linhas){
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
        scanf("%d", &opcao);
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer
            continue;
        }
        switch (opcao)
        {
        case 1:
            ImprimirFormatado(qtd_linhas, linhas);
            break;

        case 2:
            BuscarPalavra(linhas, *qtd_linhas);
            break;

        case 3:
            SubPrimOcorrencia(texto);
            formatarTexto(texto, linhas, qtd_linhas);
            break;
        
        case 4:
            SubTodasOcorrencia(texto);
            formatarTexto(texto, linhas, qtd_linhas);
            break;

        case 5:
            CaixaAlta(texto);
            formatarTexto(texto, linhas, qtd_linhas);
            break;

        case 6:
            CaixaBaixa(texto);
            formatarTexto(texto, linhas, qtd_linhas);
            break;

        case 7:
            PrimLetraMaiuFrase(texto);
            formatarTexto(texto, linhas, qtd_linhas);
            break;
        
        case 8:
            AlinharEsquerda(qtd_linhas, linhas);
            break;

        case 9:
            AlinharDireita(qtd_linhas, linhas);
            break;

        case 10:
            Justificar(qtd_linhas, linhas);
            break;

        case 11:
            Centralizar(qtd_linhas, linhas);
            break;   
            
        default:
            break;
        }
    } while (opcao != 0);

}


int main()
{
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


    int qtd_linhas = 0;
    char linhas[MAX_LINHAS][MAX_LINHA_compr+1];
    
    

    //FORMATAR PELA PRIMEIRA VEZ
    formatarTexto(&qtd_linhas, text, linhas);
    //CHAMA MENU
    Menu(text, linhas, &qtd_linhas);


    printf("\n\n%s",text);
    return 0;
}
