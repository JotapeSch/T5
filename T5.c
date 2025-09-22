#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXTO 10000
#define MAX_LINHA_compr 80
#define MAX_LINHAS 500

//------------- CHAMANDO FUNCOES ------------- 
void formatarTexto(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr+1]); 
void ImprimirFormatado(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]);
void BuscarPlavra(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], char *palavra, int linha_cont[200]);
void SubPrimOcorrencia(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], char *text);
void SubTodasOcorrencia(char *text);
void CaixaAlta(char *text);
void CaixaBaixa(char *text);
void PrimLetraMaiuFrase(char *text);
void AlinharEsquerda(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]);
void AlinharDireita(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]);
void Justificar(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1]);
void Centralizar(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1]);

//------------- IMPLEMENTACOES -------------
// objetivo: Divide o texto em linhas com no máximo 80 caracteres, preservando palavras
// parametros: texto original, matriz de linhas para armazenar o texto formatado
// retorno: nenhum
void formatarTexto(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr+1]) {
    int quantidade_linhas = 0;
    int inicio = 0, fim = inicio + MAX_LINHA_compr;
    int tamanho_texto = strlen(text);

    while (inicio < tamanho_texto) {
        if (fim > tamanho_texto) {
            fim = tamanho_texto;
        }

        while (fim > inicio && fim < tamanho_texto && text[fim] != ' ' && text[fim] != '\n') {
            fim--;
        }

        if (fim == inicio) {
            fim = inicio + MAX_LINHA_compr;
            if (fim > tamanho_texto) 
                fim = tamanho_texto;
        }

        strncpy(linhas[quantidade_linhas], &text[inicio], fim - inicio);
        linhas[quantidade_linhas][fim - inicio] = '\0';
        quantidade_linhas++;
        
        if (text[fim] == ' ' || text[fim] == '\n') {
            inicio = fim + 1;    
        } else {
            inicio = fim;
        }

        fim = inicio + MAX_LINHA_compr;

        if (quantidade_linhas >= MAX_LINHAS) {
            printf("Aviso: Limite de %d linhas atingido.\n", MAX_LINHAS);
            break;
        }
    }
}

// objetivo: Imprime o texto já formatado linha por linha
// parametros: matriz de linhas contendo o texto formatado
// retorno: nenhum
void ImprimirFormatado(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]) {
    for (int i = 0; i < MAX_LINHAS; i++) {
        if (linhas[i][0] == '\0')
            break;
        printf("%s\n", linhas[i]);
    }
}

int verificarPalavraValida(char palavra_pra_encontrar[100]) {
    int tamanho_pala = strlen(palavra_pra_encontrar);
    if (tamanho_pala == 0) {
        printf("Erro: Digite uma palavra válida (não pode estar vazia)!\n");
        return 0;
    }

    for (int i = 0; i < tamanho_pala; i++) {
        if (!isalpha(palavra_pra_encontrar[i])) {
            printf("Erro: A palavra deve conter apenas letras (A-Z, a-z)!\n");
            return 0;
        }
    }
    return 1;
}

void lerPalavraBusca(char palavra[100]) {
    int valido = 0;
    do {
        printf("Digite a palavra para buscar: ");
        scanf(" %99s", palavra);
        while (getchar() != '\n');
        valido = verificarPalavraValida(palavra);
    } while (!valido);
}

// objetivo: Procura uma palavra específica no texto e mostra suas ocorrências
// parametros: matriz de linhas contendo o texto, palavra a buscar, array para índices de linhas
// retorno: nenhum
void BuscarPlavra(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], char *palavra, int linha_cont[200]) {
    char palavra_pra_encontrar[100];
    int encontrou = 0, j = 0;

    // Inicializa linha_cont
    for (int k = 0; k < 200; k++) linha_cont[k] = -1;

    lerPalavraBusca(palavra_pra_encontrar);
    
    int tamanho_busca = strlen(palavra_pra_encontrar);
    
    for (int i = 0; i < MAX_LINHAS; i++) {
        if (linhas[i][0] == '\0') {
            break;
        }

        char *posicao_atual = linhas[i];
        while ((posicao_atual = strstr(posicao_atual, palavra_pra_encontrar)) != NULL) {
            int antes_ok = (posicao_atual == linhas[i] || !isalpha(*(posicao_atual-1)));
            int depois_ok = (!isalpha(*(posicao_atual + tamanho_busca)) || *(posicao_atual + tamanho_busca) == '\0');

            if (antes_ok && depois_ok) {
                encontrou++;
                if (j == 0 || linha_cont[j-1] != i) {
                    linha_cont[j] = i;
                    j++;
                }
            }
            posicao_atual += tamanho_busca;
        }
    }

    if (encontrou == 0) {
        printf("Nao foi encontrada nenhuma ocorrencia da palavra \"%s\".\n", palavra_pra_encontrar);
    } else {
        printf("Foram encontradas %d ocorrencia(s) da palavra \"%s\" nas seguintes linhas:\n", encontrou, palavra_pra_encontrar);
        for (int i = 0; i < j; i++) {
            int indice_linha = linha_cont[i];
            printf("Linha %d: %s\n", indice_linha + 1, linhas[indice_linha]);
        }
    }
}

void limparEspacosExtras(char *texto) {
    char resultado[MAX_TEXTO];
    int j = 0, i = 0;
    
    while (texto[i] != '\0') {
        if (texto[i] == ' ') {
            if (j == 0 || resultado[j-1] != ' ') {
                resultado[j] = ' ';
                j++;
            }
            while (texto[i] == ' ') {
                i++;
            }
            i--;
        } else {
            resultado[j] = texto[i];
            j++;
            i++;
        }
    }
    
    resultado[j] = '\0';
    strcpy(texto, resultado);
}

// objetivo: Substitui apenas a primeira ocorrência de uma palavra no texto
// parametros: matriz de linhas, texto original
// retorno: nenhum
void SubPrimOcorrencia(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], char *text) {
    char palavra_a_ser_substituida[100], nova_palavra[100];
    int linha_cont[200];
    int valido = 0;
    
    printf("----------------------------------\n");
    do {
        printf("Digite a palavra a ser substituida: ");
        scanf(" %99s", palavra_a_ser_substituida);
        while (getchar() != '\n');
        valido = verificarPalavraValida(palavra_a_ser_substituida);
    } while (!valido);
    
    BuscarPlavra(linhas, palavra_a_ser_substituida, linha_cont);
    
    printf("----------------------------------\n");
    do {
        printf("Digite a palavra para substituir: ");
        scanf(" %99s", nova_palavra);
        while (getchar() != '\n');
        valido = verificarPalavraValida(nova_palavra);
    } while (!valido);

    int tamanho = strlen(palavra_a_ser_substituida);
    char *posicao_atual = text;
    int mudado = 0;

    // Verifica se a substituição excede o limite
    if (strlen(text) - tamanho + strlen(nova_palavra) >= MAX_TEXTO) {
        printf("Erro: Substituição excede o limite de %d caracteres.\n", MAX_TEXTO);
        return;
    }

    while ((posicao_atual = strstr(posicao_atual, palavra_a_ser_substituida)) != NULL) {
        int antes_ok = (posicao_atual == text || !isalpha(*(posicao_atual - 1))); 
        int depois_ok = (!isalpha(*(posicao_atual + tamanho)) || *(posicao_atual + tamanho) == '\0');

        if (antes_ok && depois_ok) {
            char resultado[MAX_TEXTO];
            strncpy(resultado, text, posicao_atual - text);
            resultado[posicao_atual - text] = '\0';
            strcat(resultado, nova_palavra);
            strcat(resultado, posicao_atual + tamanho);
            strcpy(text, resultado);
            mudado = 1;
            break;
        }
        posicao_atual += 1;
    }

    if (!mudado) {
        printf("Nenhuma ocorrencia substituida.\n");
    } else {
        limparEspacosExtras(text);
    }

    printf("----------------------------------\n");
    formatarTexto(text, linhas);
    printf("----------------------------------\n");
    ImprimirFormatado(linhas);
}

// objetivo: Substitui todas as ocorrências de uma palavra no texto
// parametros: texto original
// retorno: nenhum
void SubTodasOcorrencia(char *text) {
    char antiga[100], nova[100];
    char resultado[MAX_TEXTO];
    char *posicao, *inicio;
    int valido;

    printf("----------------------------------\n");
    do {
        printf("Informe a palavra a ser substituida: ");
        scanf("%99s", antiga);
        while (getchar() != '\n');
        valido = verificarPalavraValida(antiga);
    } while (!valido);

    do {
        printf("Digite a nova palavra: ");
        scanf("%99s", nova);
        while (getchar() != '\n');
        valido = verificarPalavraValida(nova);
    } while (!valido);

    resultado[0] = '\0';
    inicio = text;

    while ((posicao = strstr(inicio, antiga)) != NULL) {
        if (strlen(text) - strlen(antiga) + strlen(nova) >= MAX_TEXTO) {
            printf("Erro: Substituição excede o limite de %d caracteres.\n", MAX_TEXTO);
            return;
        }
        strncat(resultado, inicio, posicao - inicio);
        strcat(resultado, nova);
        inicio = posicao + strlen(antiga);
    }

    strcat(resultado, inicio);
    strcpy(text, resultado);
    limparEspacosExtras(text);
}

// objetivo: Converte todo o texto para letras maiúsculas
// parametros: texto que será convertido
// retorno: nenhum
void CaixaAlta(char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = toupper((unsigned char)text[i]);
    }
}

// objetivo: Converte todo o texto para letras minúsculas
// parametros: texto que será convertido
// retorno: nenhum
void CaixaBaixa(char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = tolower((unsigned char)text[i]);
    }
    printf("Texto convertido pra caixa baixa!\n");
}

// objetivo: Capitaliza a primeira letra de cada frase no texto
// parametros: texto que terá as primeiras letras capitalizadas
// retorno: nenhum
void PrimLetraMaiuFrase(char *text) {
    int inicioFrase = 1;
    for (int i = 0; text[i] != '\0'; i++) {
        if (inicioFrase && isalpha((unsigned char)text[i])) {
            text[i] = toupper((unsigned char)text[i]);
            inicioFrase = 0;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            inicioFrase = 1;
        }
    }
}

// objetivo: Alinha todo o texto à esquerda (padrão)
// parametros: matriz de linhas contendo o texto
// retorno: nenhum
void AlinharEsquerda(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]) {
    for (int i = 0; i < MAX_LINHAS; i++) {
        if (linhas[i][0] == '\0') break;

        // Remove espaços no final
        int len = strlen(linhas[i]);
        while (len > 0 && linhas[i][len - 1] == ' ') {
            linhas[i][len - 1] = '\0';
            len--;
        }

        // Verifica se a linha tem apenas espaços
        int is_empty = 1;
        for (int j = 0; j < len; j++) {
            if (linhas[i][j] != ' ') {
                is_empty = 0;
                break;
            }
        }
        if (is_empty) {
            linhas[i][0] = '\0';
            continue;
        }

        // Remove espaços no início
        int start = 0;
        while (linhas[i][start] == ' ') {
            start++;
        }
        if (start > 0) {
            memmove(linhas[i], &linhas[i][start], len - start + 1);
        }
    }
}

// objetivo: Alinha todo o texto à direita
// parametros: matriz de linhas contendo o texto
// retorno: nenhum
void AlinharDireita(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]) {
    for (int i = 0; i < MAX_LINHAS; i++) {
        if (linhas[i][0] == '\0') break;

        // Remove espaços no início e no final
        int len = strlen(linhas[i]);
        while (len > 0 && linhas[i][len - 1] == ' ') {
            linhas[i][len - 1] = '\0';
            len--;
        }

        // Verifica se a linha tem apenas espaços
        int is_empty = 1;
        for (int j = 0; j < len; j++) {
            if (linhas[i][j] != ' ') {
                is_empty = 0;
                break;
            }
        }
        if (is_empty) {
            linhas[i][0] = '\0';
            continue;
        }

        int start = 0;
        while (linhas[i][start] == ' ') {
            start++;
        }
        if (start > 0) {
            memmove(linhas[i], &linhas[i][start], len - start + 1);
            len -= start;
        }

        // Adiciona espaços à esquerda
        if (len < MAX_LINHA_compr) {
            char temp[MAX_LINHA_compr + 1] = {0};
            int spaces = MAX_LINHA_compr - len;
            memset(temp, ' ', spaces);
            strcpy(temp + spaces, linhas[i]);
            strcpy(linhas[i], temp);
        }
    }
}

// objetivo: Justifica o texto (distribui espaços uniformemente entre palavras)
// parametros: matriz de linhas contendo o texto
// retorno: nenhum
void Justificar(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1]) {
    for (int i = 0; i < MAX_LINHAS; i++) {
        if (linhas[i][0] == '\0') break;

        // Conta palavras e remove espaços extras
        char temp[MAX_LINHA_compr + 1];
        char *words[MAX_LINHA_compr];
        int word_count = 0;
        strcpy(temp, linhas[i]);
        char *token = strtok(temp, " ");
        while (token != NULL && word_count < MAX_LINHA_compr) {
            words[word_count++] = token;
            token = strtok(NULL, " ");
        }

        // Verifica se a linha tem apenas espaços ou é vazia
        if (word_count == 0) {
            linhas[i][0] = '\0';
            continue;
        }

        // Calcula comprimento total das palavras
        int total_len = 0;
        for (int j = 0; j < word_count; j++) {
            total_len += strlen(words[j]);
        }

        // Se for uma palavra ou a última linha, alinha à esquerda
        if (word_count <= 1 || (i == MAX_LINHAS - 1 || linhas[i + 1][0] == '\0')) {
            strcpy(linhas[i], words[0] ? words[0] : "");
            continue;
        }

        // Calcula espaços necessários
        int spaces_needed = MAX_LINHA_compr - total_len;
        int gaps = word_count - 1;
        int spaces_per_gap = gaps > 0 ? spaces_needed / gaps : 0;
        int extra_spaces = gaps > 0 ? spaces_needed % gaps : 0;

        // Constrói linha justificada
        char result[MAX_LINHA_compr + 1] = {0};
        for (int j = 0; j < word_count; j++) {
            strcat(result, words[j]);
            if (j < word_count - 1) {
                for (int k = 0; k < spaces_per_gap + (j < extra_spaces ? 1 : 0); k++) {
                    strcat(result, " ");
                }
            }
        }
        strcpy(linhas[i], result);
    }
}

// objetivo: Centraliza todas as linhas do texto
// parametros: matriz de linhas contendo o texto
// retorno: nenhum
void Centralizar(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1]) {
    for (int i = 0; i < MAX_LINHAS; i++) {
        if (linhas[i][0] == '\0') break;

        // Remove espaços no início e no final
        int len = strlen(linhas[i]);
        while (len > 0 && linhas[i][len - 1] == ' ') {
            linhas[i][len - 1] = '\0';
            len--;
        }

        // Verifica se a linha tem apenas espaços
        int is_empty = 1;
        for (int j = 0; j < len; j++) {
            if (linhas[i][j] != ' ') {
                is_empty = 0;
                break;
            }
        }
        if (is_empty) {
            linhas[i][0] = '\0';
            continue;
        }

        int start = 0;
        while (linhas[i][start] == ' ') {
            start++;
        }
        if (start > 0) {
            memmove(linhas[i], &linhas[i][start], len - start + 1);
            len -= start;
        }

        // Adiciona espaços para centralizar
        if (len < MAX_LINHA_compr) {
            char temp[MAX_LINHA_compr + 1] = {0};
            int total_spaces = MAX_LINHA_compr - len;
            int left_spaces = total_spaces / 2;
            memset(temp, ' ', left_spaces);
            strcpy(temp + left_spaces, linhas[i]);
            strcpy(linhas[i], temp);
        }
    }
}

// objetivo: Exibe menu interativo e chama funções de formatação
// parametros: texto original, matriz de linhas formatadas
// retorno: nenhum
void Menu(char *texto, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1]) {
    int opcao;
    int linha_cont[200];
    do {
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
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            while (getchar() != '\n');
            continue;
        }
        
        while (getchar() != '\n');
        
        switch (opcao) {
        case 1:
            ImprimirFormatado(linhas);
            break;
        case 2:
            BuscarPlavra(linhas, NULL, linha_cont);
            break;
        case 3:
            SubPrimOcorrencia(linhas, texto);
            formatarTexto(texto, linhas);
            break;
        case 4:
            SubTodasOcorrencia(texto);
            formatarTexto(texto, linhas);
            break;
        case 5:
            CaixaAlta(texto);
            formatarTexto(texto, linhas);
            break;
        case 6:
            CaixaBaixa(texto);
            formatarTexto(texto, linhas);
            break;
        case 7:
            PrimLetraMaiuFrase(texto);
            formatarTexto(texto, linhas);
            break;
        case 8:
            AlinharEsquerda(linhas);
            ImprimirFormatado(linhas);
            break;
        case 9:
            AlinharDireita(linhas);
            ImprimirFormatado(linhas);
            break;
        case 10:
            Justificar(linhas);
            ImprimirFormatado(linhas);
            break;
        case 11:
            Centralizar(linhas);
            ImprimirFormatado(linhas);
            break;
        case 0:
            printf("Saindo do programa...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
        }
    } while (opcao != 0);
}

int main() {
    char text[MAX_TEXTO] = "William Henry Gates III KBE GCIH (Seattle, 28 de outubro de 1955) mais conhecido como Bill Gates,\
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
 comercialização deste produto, Gates e Allen fundaram a Microsoft, uma das primeiras empresas no mundo \
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

    char linhas[MAX_LINHAS][MAX_LINHA_compr+1];
    
    formatarTexto(text, linhas);
    Menu(text, linhas);

    return 0;
}