#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Adicionado para isalpha, toupper, tolower

#define MAX_TEXTO 10000
#define MAX_LINHA_compr 80
#define MAX_LINHAS 500

//------------- CHAMANDO FUNCOES ------------- 
int formatarTexto(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr+1]); 
void ImprimirFormatado(char linhas[MAX_LINHAS][MAX_LINHA_compr+1], int quantidade_linhas);
void BuscarPlavra(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int linha_cont[200], int *quantidade_linhas);
void SubPrimOcorrencia(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], char *text, int *quantidade_linhas);
void SubTodasOcorrencia(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int *quantidade_linhas);
void CaixaAlta(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int *quantidade_linhas);
void CaixaBaixa(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int *quantidade_linhas);
void PrimLetraMaiuFrase(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int *quantidade_linhas);
void AlinharEsquerda(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]);
void AlinharDireita(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]);
void Justificar(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1]);
void Centralizar(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1]);


//------------- IMPLEMENTACOES  -------------
// objetivo: Divide o texto em linhas com no máximo 80 caracteres, preservando palavras
// parametros: ponteiro para quantidade de linhas, texto original, matriz de linhas para armazenar o texto formatado
// retorno: nenhum
int formatarTexto(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr+1]) {
    // Implementação pendente - JOTA
    int quantidade_linhas = 0;
    int inicio = 0, fim = inicio + MAX_LINHA_compr;
    int tamanho_texto = strlen(text);

    while (inicio < tamanho_texto) {
        if (fim > tamanho_texto) {
            fim = tamanho_texto;
        }

        // Verifica se há um '\n' antes do limite da linha
        int encontrou_nova_linha = 0;
        for (int i = inicio; i < fim && i < tamanho_texto; i++) {
            if (text[i] == '\n') {
                fim = i;
                encontrou_nova_linha = 1;
                break;
            }
        }

        if (!encontrou_nova_linha) {
            while (fim > inicio && fim < tamanho_texto && text[fim] != ' ' && text[fim] != '\n') {
                fim--;
            }
        }

        if (fim == inicio) {
            fim = inicio + MAX_LINHA_compr;
            if (fim > tamanho_texto) 
                fim = tamanho_texto;
        }

        strncpy(linhas[quantidade_linhas], &text[inicio], fim - inicio);
        linhas[quantidade_linhas][fim - inicio] = '\0';
        quantidade_linhas++;
        
        inicio = fim + (encontrou_nova_linha ? 1 : 0);
        if (text[fim] == ' ' || text[fim] == '\n') {
            inicio++;
        }
        fim = inicio + MAX_LINHA_compr;

        // verifico se o quantidade de linhas eh maior que o maximo permitido
        if (quantidade_linhas >= MAX_LINHAS) 
            break;
    }
    return quantidade_linhas;
}

// objetivo: Imprime o texto já formatado linha por linha
// parametros: quantidade de linhas, matriz de linhas contendo o texto formatado
// retorno: nenhum
void ImprimirFormatado(char linhas[MAX_LINHAS][MAX_LINHA_compr+1], int quantidade_linhas) {
    // Implementação pendente - JOTA
    for (int i = 0; i < quantidade_linhas; i++) {
        printf("%s\n", linhas[i]);
    }
}

int verificarPalavraValida(char palavra_pra_encontrar[100]) {
    int tamanho_pala = strlen(palavra_pra_encontrar);
    if (tamanho_pala == 0) {
        printf("Erro: Digite uma palavra valida (não pode estar vazia)!\n");
        return 0;
    }

    for (int i = 0; i < tamanho_pala; i++) { 
        if (!isalpha(palavra_pra_encontrar[i])) {
            printf("Erro: A palavra deve conter apenas letras (A-Z, a-z)!\n");
            return 0;
        }
    }
    return 1; // valida
}

void lerPalavraBusca(char palavra[100]) {
    int valido = 0;
    do {
        printf("Digite a palavra para buscar: ");
        scanf(" %99s", palavra);
        while (getchar() != '\n'); // limpa buffer
        valido = verificarPalavraValida(palavra);
    } while (!valido);
}


// objetivo: Procura uma palavra específica no texto e mostra suas ocorrências
// parametros: matriz de linhas contendo o texto, quantidade de linhas do texto
// retorno: nenhum
void BuscarPlavra(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int linha_cont[200], int *quantidade_linhas) {
    // Implementação pendente - JOTA
    char palavra_pra_encontrar[100];
    int encontrou = 0, j = 0;

    lerPalavraBusca(palavra_pra_encontrar);
    
    int tamanho_busca = strlen(palavra_pra_encontrar);
    
    for (int i = 0; i < *quantidade_linhas; i++) {
        char *posicao_atual = linhas[i];
        while ((posicao_atual = strstr(posicao_atual, palavra_pra_encontrar)) != NULL) {
            int antes_ok = (posicao_atual == linhas[i] || !isalpha(*(posicao_atual - 1)));
            int depois_ok = (!isalpha(*(posicao_atual + tamanho_busca)) || *(posicao_atual + tamanho_busca) == '\0');

            if (antes_ok && depois_ok) {
                encontrou++;
                int coluna = posicao_atual - linhas[i] + 1; // Calcula a coluna
                if (j == 0 || linha_cont[j - 1] != i) {
                    linha_cont[j] = i;
                    j++;
                }
                printf("Ocorrencia na linha %d, coluna %d\n", i + 1, coluna);
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
    int j = 0;
    int i = 0;
    
    while (texto[i] != '\0') {
        // Se é espaço, só adiciona UM espaço (não múltiplos)
        if (texto[i] == ' ') {
            
            // Adiciona apenas um espaço
            // Verifica se o resultado não está vazio E se o último char NÃO é um espaço
            if (j > 0 && resultado[j-1] != ' ') { 
                resultado[j] = ' ';
                j++;
            }
            
            // Pula todos os espaços consecutivos (i avança até encontrar um não-espaço)
            while (texto[i] == ' ') {
                i++;
            }
            // Se o texto terminar com espaço, o próximo while (texto[i] != '\0') encerrará.
            
        } else {
            // Caractere normal
            resultado[j] = texto[i];
            j++;
            i++;
        }
    }

    // Trata o caso de um espaço final (se o texto terminou com um espaço, 
    // a última coisa que foi escrita em 'resultado' pode ter sido um espaço).
    // O loop acima já deve evitar isso, mas esta é a garantia final:
    if (j > 0 && resultado[j-1] == ' ') {
        j--;
    }

    resultado[j] = '\0';
    strcpy(texto, resultado);
}

// objetivo: Substitui apenas a primeira ocorrência de uma palavra no texto
// parametros: texto original onde será feita a substituição
// retorno: nenhum
void SubPrimOcorrencia(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], char *text, int *quantidade_linhas) {
    // Implementação pendente - JOTA 
    char palavra_a_ser_substituida[100], nova_palavra[100];
    int valido;

    do {
        printf("Digite a palavra a ser substituida: ");
        fgets(palavra_a_ser_substituida, sizeof(palavra_a_ser_substituida), stdin);
        palavra_a_ser_substituida[strcspn(palavra_a_ser_substituida, "\n")] = 0;
        valido = verificarPalavraValida(palavra_a_ser_substituida);
    } while (!valido);

    do {
        printf("Digite a nova palavra: ");        
        fgets(nova_palavra, sizeof(nova_palavra), stdin);
        nova_palavra[strcspn(nova_palavra, "\n")] = 0;
        valido = verificarPalavraValida(nova_palavra);
    } while (!valido);

    int tamanho = strlen(palavra_a_ser_substituida);
    char *posicao_atual = strstr(text, palavra_a_ser_substituida);
    int mudado = 0;

    while (posicao_atual != NULL) {
        int antes_ok = (posicao_atual == text || !isalpha(*(posicao_atual - 1))); 
        int depois_ok = (!isalpha(*(posicao_atual + tamanho)) || *(posicao_atual + tamanho) == '\0');
        // esse antes e depois eh o mesmo que em buscar palavra, porem de forma mais enxuta pra ajudar no entendimento

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

        posicao_atual = strstr(posicao_atual + 1, palavra_a_ser_substituida);  // Avanca para evitar overlaps, embora raro em palavras
    }

    if (!mudado) {
        printf("Nenhuma ocorrencia substituida.\n");
    } else {
        limparEspacosExtras(text);
        printf("AOBA");
        *quantidade_linhas = formatarTexto(text, linhas);
        printf("----------------------------------\n");
        ImprimirFormatado(linhas, *quantidade_linhas);
        printf("----------------------------------\n");
    
    }
}

// objetivo: Substitui todas as ocorrências de uma palavra no texto
// parametros: texto original onde serão feitas as substituições
// retorno: nenhum
void SubTodasOcorrencia(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int *quantidade_linhas) {
    char antiga[100], nova[100];
    char resultado[MAX_TEXTO];

    printf("informe a palavra a ser substituida: ");
    scanf("%99s", antiga);

    printf("Digite a nova palavra: ");
    scanf("%99s", nova);

    resultado[0] = '\0'; // inicia string sem nada
    char *posicao, *inicio;
    inicio = text;

    while ((posicao = strstr(inicio, antiga)) != NULL) {
        // copia parte antes da palavra encontrada
        strncat(resultado, inicio, posicao - inicio);

        // adiciona nova palavra
        strcat(resultado, nova);

        inicio = posicao + strlen(antiga);
    }

    strcat(resultado, inicio); // copia o resto do texto
    strcpy(text, resultado); // cola de volta para o texto original
    limparEspacosExtras(text); // Limpa espaços extras antes de formatar
    *quantidade_linhas = formatarTexto(text, linhas);
    ImprimirFormatado(linhas, *quantidade_linhas); // Imprime o texto formatado
}

// objetivo: Converte todo o texto para letras maiúsculas
// parametros: texto que será convertido para caixa alta
// retorno: nenhum
void CaixaAlta(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int *quantidade_linhas) {
    limparEspacosExtras(text); // Limpa espaços extras antes
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = toupper((unsigned char)text[i]); // funcao para converter maiuscula
    }
    *quantidade_linhas = formatarTexto(text, linhas);
    ImprimirFormatado(linhas, *quantidade_linhas);
}

// objetivo: Converte todo o texto para letras minúsculas
// parametros: texto que será convertido para caixa baixa
// retorno: nenhum
void CaixaBaixa(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int *quantidade_linhas) {
    limparEspacosExtras(text); // Limpa espaços extras antes
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = tolower((unsigned char)text[i]); // funcao que transforma tudo em minuscula
    }
    *quantidade_linhas = formatarTexto(text, linhas);
    ImprimirFormatado(linhas, *quantidade_linhas);
    printf("Texto convertido pra caixa baixa!\n");
}

// objetivo: Capitaliza a primeira letra de cada frase no texto
// parametros: texto que terá as primeiras letras das frases capitalizadas
// retorno: nenhum
void PrimLetraMaiuFrase(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int *quantidade_linhas) {
    limparEspacosExtras(text); // Limpa espaços extras antes
    int inicioFrase = 1; // para identificar inicio de frase
    for (int i = 0; text[i] != '\0'; i++) {
        if (inicioFrase && isalpha((unsigned char)text[i])) {
            text[i] = toupper((unsigned char)text[i]);
            inicioFrase = 0; // ja esta maiuscula a primeira frase
        } else if (text[i] == '.' || text[i] == '!' || text[i] == '?') { // se encontrou o fim da frase, repete o processo de conversao 
            inicioFrase = 1;
            // Pula espaços após o ponto
            while (text[i + 1] == ' ') {
                i++;
            }
        } else if (!isspace((unsigned char)text[i])) {
            inicioFrase = 0;
        }
    }
    *quantidade_linhas = formatarTexto(text, linhas);
    ImprimirFormatado(linhas, *quantidade_linhas);
}

// objetivo: Alinha todo o texto à esquerda (padrão)
// parametros: quantidade de linhas, matriz de linhas contendo o texto
// retorno: nenhum
void AlinharEsquerda(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]) {
    // Implementação pendente - VINI
    for (int i = 0; i < MAX_LINHAS; i++) {
        if (linhas[i][0] == '\0') break;

        // Remove espaços no final
        int tamanho_linhas = strlen(linhas[i]);
        while (tamanho_linhas > 0 && linhas[i][tamanho_linhas - 1] == ' ') {
            linhas[i][tamanho_linhas - 1] = '\0';
            tamanho_linhas--;
        }

        // Verifica se a linha tem apenas espaços
        int esta_vazio = 1;
        for (int j = 0; j < tamanho_linhas; j++) {
            if (linhas[i][j] != ' ') {
                esta_vazio = 0;
                break;
            }
        }
        if (esta_vazio) {
            linhas[i][0] = '\0';
            continue;
        }

        // Remove espaços no início
        int comeco = 0;
        while (linhas[i][comeco] == ' ') {
            comeco++;
        }
        if (comeco > 0) {
            memmove(linhas[i], &linhas[i][comeco], tamanho_linhas - comeco + 1);
        }
    }
}

// objetivo: Alinha todo o texto à direita
// parametros: quantidade de linhas, matriz de linhas contendo o texto
// retorno: nenhum
void AlinharDireita(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]) {
    // Implementação pendente - VINI
    for (int i = 0; i < MAX_LINHAS; i++) {
        if (linhas[i][0] == '\0') break;

        // Remove espaços no início e no final
        int tamanho_linhas = strlen(linhas[i]);
        while (tamanho_linhas > 0 && linhas[i][tamanho_linhas - 1] == ' ') {
            linhas[i][tamanho_linhas - 1] = '\0';
            tamanho_linhas--;
        }

        // Verifica se a linha tem apenas espaços
        int eh_vazio = 1;
        for (int j = 0; j < tamanho_linhas; j++) {
            if (linhas[i][j] != ' ') {
                eh_vazio = 0;
                break;
            }
        }
        if (eh_vazio) {
            linhas[i][0] = '\0';
            continue;
        }

        int comeco = 0;
        while (linhas[i][comeco] == ' ') {
            comeco++;
        }
        if (comeco > 0) {
            memmove(linhas[i], &linhas[i][comeco], tamanho_linhas - comeco + 1);
            tamanho_linhas -= comeco;
        }

        // Adiciona espaços à esquerda
        if (tamanho_linhas < MAX_LINHA_compr) {
            char temp[MAX_LINHA_compr + 1] = {0};
            int espaco = MAX_LINHA_compr - tamanho_linhas;
            memset(temp, ' ', espaco);
            strncpy(temp + espaco, linhas[i], MAX_LINHA_compr - espaco);
            temp[MAX_LINHA_compr] = '\0'; // Garante que não exceda
            strcpy(linhas[i], temp);
        }
    }
}

// objetivo: Justifica o texto (distribui espaços uniformemente entre palavras)
// parametros: matriz de linhas contendo o texto, quantidade de linhas
// retorno: nenhum
void Justificar(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1]) {
    // Implementação pendente - VINI
    for (int i = 0; i < MAX_LINHAS; i++) {
        if (linhas[i][0] == '\0') break;

        // Copia a linha para um buffer temporário
        char temp[MAX_LINHA_compr + 1];
        strcpy(temp, linhas[i]);
        limparEspacosExtras(temp); // Remove espaços extras antes de justificar

        // Conta palavras
        char *palavras[MAX_LINHA_compr];
        int palavra_contada = 0;
        char *token = strtok(temp, " ");
        while (token != NULL && palavra_contada < MAX_LINHA_compr) {
            palavras[palavra_contada++] = token;
            token = strtok(NULL, " ");
        }

        // Verifica se a linha tem apenas espaços ou é vazia
        if (palavra_contada == 0) {
            linhas[i][0] = '\0';
            continue;
        }

        // Calcula comprimento total das palavras
        int tam_total = 0;
        for (int j = 0; j < palavra_contada; j++) {
            tam_total += strlen(palavras[j]);
        }

        // Se for uma palavra ou a última linha, alinha à esquerda
        if (palavra_contada <= 1 || (i == MAX_LINHAS - 1 || linhas[i + 1][0] == '\0')) {
            strcpy(linhas[i], palavras[0] ? palavras[0] : "");
            continue;
        }

        // Calcula espaços necessários
        int espacos_necessario = MAX_LINHA_compr - tam_total;
        int gaps = palavra_contada - 1;
        int espacos_por_gaps = gaps > 0 ? espacos_necessario / gaps : 0;
        int espacos_extras = gaps > 0 ? espacos_necessario % gaps : 0;

        // Constrói linha justificada
        char result[MAX_LINHA_compr + 1] = {0};
        for (int j = 0; j < palavra_contada; j++) {
            strcat(result, palavras[j]);
            if (j < palavra_contada - 1) {
                for (int k = 0; k < espacos_por_gaps + (j < espacos_extras ? 1 : 0); k++) {
                    strcat(result, " ");
                }
            }
        }
        strcpy(linhas[i], result);
    }
}

// objetivo: Centraliza todas as linhas do texto
// parametros: matriz de linhas contendo o texto, quantidade de linhas
// retorno: nenhum
void Centralizar(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1]) {
    // Implementação pendente - VINI
    for (int i = 0; i < MAX_LINHAS; i++) {
        if (linhas[i][0] == '\0') break;

        // Remove espaços no início e no final
        int tamanho = strlen(linhas[i]);
        while (tamanho > 0 && linhas[i][tamanho - 1] == ' ') {
            linhas[i][tamanho - 1] = '\0';
            tamanho--;
        }

        // Verifica se a linha tem apenas espaços
        int eh_vazio = 1;
        for (int j = 0; j < tamanho; j++) {
            if (linhas[i][j] != ' ') {
                eh_vazio = 0;
                break;
            }
        }
        if (eh_vazio) {
            linhas[i][0] = '\0';
            continue;
        }

        int comeco = 0;
        while (linhas[i][comeco] == ' ') {
            comeco++;
        }
        if (comeco > 0) {
            memmove(linhas[i], &linhas[i][comeco], tamanho - comeco + 1);
            tamanho -= comeco;
        }

        // Adiciona espaços para centralizar
        if (tamanho < MAX_LINHA_compr) {
            char temp[MAX_LINHA_compr + 1] = {0};
            int espacos_total = MAX_LINHA_compr - tamanho;
            int espacos_sobrando = espacos_total / 2;
            memset(temp, ' ', espacos_sobrando);
            strcpy(temp + espacos_sobrando, linhas[i]);
            strcpy(linhas[i], temp);
        }
    }
}
//-----------------------------------------------------

// objetivo: Exibe menu interativo e chama funções de formatação de texto conforme escolha do usuário
// parametros: texto original, matriz de linhas formatadas, ponteiro para quantidade de linhas
// retorno: nenhum
void Menu(char *texto, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int *quantidade_linhas) {
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
        
        // Validação de entrada
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer
            continue;
        }
        
        // Limpar buffer após scanf
        while (getchar() != '\n');
        
        switch (opcao) {
        case 1:
            // objetivo: Imprime o texto formatado
            ImprimirFormatado(linhas, *quantidade_linhas);
            break;

        case 2:
            // objetivo: Busca palavra no texto formatado
            BuscarPlavra(linhas, linha_cont, quantidade_linhas);
            break;

        case 3:
            // objetivo: Substitui primeira ocorrência e reformata texto
            SubPrimOcorrencia(linhas, texto, quantidade_linhas);
            break;
        
        case 4:
            // objetivo: Substitui todas ocorrências e reformata texto
            SubTodasOcorrencia(texto, linhas, quantidade_linhas);
            break;

        case 5:
            // objetivo: Converte para maiúsculas e reformata texto
            CaixaAlta(texto, linhas, quantidade_linhas);
            break;

        case 6:
            // objetivo: Converte para minúsculas e reformata texto
            CaixaBaixa(texto, linhas, quantidade_linhas);
            break;

        case 7:
            // objetivo: Capitaliza frases e reformata texto
            PrimLetraMaiuFrase(texto, linhas, quantidade_linhas);
            break;
        
        case 8:
            // objetivo: Alinha texto à esquerda
            AlinharEsquerda(linhas);
            ImprimirFormatado(linhas, *quantidade_linhas);
            break;

        case 9:
            // objetivo: Alinha texto à direita
            AlinharDireita(linhas);
            ImprimirFormatado(linhas, *quantidade_linhas);
            break;

        case 10:
            // objetivo: Justifica o texto
            Justificar(linhas);
            ImprimirFormatado(linhas, *quantidade_linhas);
            break;

        case 11:
            // objetivo: Centraliza o texto
            Centralizar(linhas);
            ImprimirFormatado(linhas, *quantidade_linhas);
            break;   
            
        case 0:
            // objetivo: Sai do programa
            printf("Saindo do programa...\n");
            break;
            
        default:
            // Trata opção inválida
            printf("Opção inválida! Tente novamente.\n");
            break;
        }
    } while (opcao != 0);
}

int main() {
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
 comercializa  o deste produto, Gates e Allen fundaram a Microsoft, uma das primeiras empresas no mundo \
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
    int quantidade_linhas;
    
    // FORMATAR PELA PRIMEIRA VEZ
    quantidade_linhas = formatarTexto(text, linhas);
    
    // CHAMA MENU
    Menu(text, linhas, &quantidade_linhas);

    return 0;  // Sucesso na execução
}