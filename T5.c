#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#define MAX_TEXTO 10000
#define MAX_LINHA_compr 80
#define MAX_LINHAS 500

//------------- CHAMANDO FUNCOES ------------- 
int formatarTexto(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr+1]); 
void ImprimirFormatado(char linhas[MAX_LINHAS][MAX_LINHA_compr+1], int quantidade_linhas);
void lerPalavraBusca(char palavra[100]);
void BuscarPalavra(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int linha_cont[200], int *quantidade_linhas);
void limparEspacosExtras(char *texto);
void SubPrimOcorrencia(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], char *text, int *quantidade_linhas);
void SubTodasOcorrencia(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int *quantidade_linhas);
void CaixaAlta(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int *quantidade_linhas);
void CaixaBaixa(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int *quantidade_linhas);
void CapitalizarPrimLetraFrase(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int *quantidade_linhas);
void AlinharEsquerda(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]);
void AlinharDireita(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]);
void Justificar(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1]);
void Centralizar(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1]);
void AtualizarTextoOriginal(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int quantidade_linhas);


//------------- IMPLEMENTACOES  -------------

// objetivo: Divide o texto em linhas com no máximo 80 caracteres, preservando palavras
// parametros: ponteiro para quantidade de linhas, texto original, matriz de linhas para armazenar o texto formatado
// retorno: quantidade de linhas
int formatarTexto(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr+1]) {
    // Implementação - JOTA
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
    // Implementação - JOTA
    for (int i = 0; i < quantidade_linhas; i++) {
        printf("%s\n", linhas[i]);
    }
}

// objetivo: verificar se palavra existe no texto
// parametros: variavel palavra
// retorno: 1 - valido, 0 - invalido
int verificarPalavraValida(char palavra_pra_encontrar[100]) {
    //Jota
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

// objetivo: Ler uma palavra (padronizar e tals)
// parametros: uma variavel palavra
// retorno: nenhum
void lerPalavraBusca(char palavra[100]) {
    //Jota
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
void BuscarPalavra(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int linha_cont[200], int *quantidade_linhas) {
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

// objetivo: Limpar espacos extras que podem sobrar do formatar
// parametros: apenas o texto ja ou nao modificado
// retorno: nenhum
void limparEspacosExtras(char *texto) {
    //Jota
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

    if (strcmp(palavra_a_ser_substituida, nova_palavra) == 0) {
        printf("A palavra antiga e a nova palavra sao iguais. Nenhuma substituicao realizada.\n");
        return;
    }

    int tamanho = strlen(palavra_a_ser_substituida);
    char *posicao_atual = strstr(text, palavra_a_ser_substituida);
    int mudado = 0;

    while (posicao_atual != NULL) {
        int antes_ok = (posicao_atual == text || !isalpha(*(posicao_atual - 1))); 
        int depois_ok = (!isalpha(*(posicao_atual + tamanho)) || *(posicao_atual + tamanho) == '\0');
        // esse antes e depois eh o mesmo que em buscar palavra, porem de forma mais enxuta pra ajudar no entendimento

        if (antes_ok && depois_ok) {
            char resultado[MAX_TEXTO];
            int tamanho_anterior = (int)(posicao_atual - text); 
            // Construção da nova string: [Parte Antes] + [Nova Palavra] + [Parte Depois]
            snprintf(resultado, sizeof(resultado), "%.*s%s%s",tamanho_anterior, text, nova_palavra, posicao_atual + tamanho); 

            strncpy(text, resultado, MAX_TEXTO - 1);
            text[MAX_TEXTO - 1] = '\0';
            mudado = 1;
            break;
        
        }

        posicao_atual = strstr(posicao_atual + 1, palavra_a_ser_substituida);  // Avanca para evitar overlaps, embora raro em palavras
    }

    if (!mudado) {
        printf("Nenhuma ocorrencia substituida.\n");
    } else {
        limparEspacosExtras(text);
        *quantidade_linhas = formatarTexto(text, linhas);
        printf("=========================================\n");
        printf("Foi Substituido a primeira ocorrencia da palavra '%s' pela '%s'!\n",palavra_a_ser_substituida, nova_palavra);
    
    }
}

// objetivo: Substitui todas as ocorrências de uma palavra no texto
// parametros: texto original onde serão feitas as substituições
// retorno: nenhum
void SubTodasOcorrencia(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int *quantidade_linhas) {
    char antiga[100], nova[100];
    int valido;

    do {
        printf("Digite a palavra a ser substituida: ");
        // Usar fgets para entrada segura, mesmo que depois verifique apenas letras
        fgets(antiga, sizeof(antiga), stdin);
        antiga[strcspn(antiga, "\n")] = 0;
        valido = verificarPalavraValida(antiga);
    } while (!valido);

    do {
        printf("Digite a nova palavra: ");
        fgets(nova, sizeof(nova), stdin);
        nova[strcspn(nova, "\n")] = 0;
        valido = verificarPalavraValida(nova);
    } while (!valido);

    if (strcmp(antiga, nova) == 0) {
        printf("A palavra antiga e a nova palavra sao iguais. Nenhuma substituicao realizada.\n");
        return;
    }

    int tamanho_antiga = strlen(antiga);
    int tamanho_nova = strlen(nova);
    
    // Usar um buffer de tamanho MAX_TEXTO + diferença máxima de tamanho, por segurança
    char resultado[MAX_TEXTO * 2] = ""; 
    
    char *inicio_busca = text;
    char *posicao;
    int mudado = 0;
    size_t indice_resultado = 0;
    
    while ((posicao = strstr(inicio_busca, antiga)) != NULL) {
        // Verifica se é uma palavra completa 
        int antes_ok = (posicao == text || !isalpha((unsigned char)*(posicao - 1))); 
        int depois_ok = (!isalpha((unsigned char)*(posicao + tamanho_antiga)) || *(posicao + tamanho_antiga) == '\0');

        if (antes_ok && depois_ok) {
            // 1. Copia o trecho ANTERIOR à ocorrência para o resultado
            size_t tamanho_anterior = posicao - inicio_busca;
            // Se o trecho anterior couber no resultado
            if (indice_resultado + tamanho_anterior < sizeof(resultado) - 1) {
                strncpy(resultado + indice_resultado, inicio_busca, tamanho_anterior);
                indice_resultado += tamanho_anterior;
            } else {
                // Buffer overflow: aborta a substituição
                printf("Erro: Buffer de texto excedido durante a substituicao.\n");
                return; 
            }
            
            // 2. Adiciona a NOVA palavra
            if (indice_resultado + tamanho_nova < sizeof(resultado) - 1) {
                strcpy(resultado + indice_resultado, nova);
                indice_resultado += tamanho_nova;
            } else {
                // aborta a substituição caso o buffer de excede
                printf("Erro: Buffer de texto excedido durante a substituicao.\n");
                return;
            }

            // 3. Avança o ponteiro de busca para DEPOIS da palavra antiga
            inicio_busca = posicao + tamanho_antiga;
            mudado = 1;
        } else {
            // Não é palavra completa, copia apenas o primeiro caractere e avança o ponteiro de busca em 1
            if (indice_resultado < sizeof(resultado) - 1) {
                resultado[indice_resultado++] = *inicio_busca;
                resultado[indice_resultado] = '\0'; // Mantém o resultado como string válida
                inicio_busca++;
            } else {
                printf("Erro: Buffer de texto excedido durante a substituicao.\n");
                return; 
            }
        }
    }

    // Copia o restante do texto (o que sobrou de 'inicio_busca' até o final)
    if (indice_resultado + strlen(inicio_busca) < sizeof(resultado) - 1) {
        strcpy(resultado + indice_resultado, inicio_busca);
    } else {
        printf("Erro: Buffer de texto excedido ao finalizar o texto.\n");
        return;
    }
    
    // Finaliza o resultado com null
    resultado[sizeof(resultado) - 1] = '\0';

    if (mudado) {
        // Garante que o texto original não ultrapasse MAX_TEXTO
        strncpy(text, resultado, MAX_TEXTO - 1);
        text[MAX_TEXTO - 1] = '\0';

        limparEspacosExtras(text);
        *quantidade_linhas = formatarTexto(text, linhas);
        printf("=========================================\n");
        printf("Foi Substituido todas as ocorrencias da palavra '%s' pela '%s'!\n", antiga, nova);
    } else {
        printf("Nenhuma ocorrencia substituida.\n");
    }
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
    printf("=========================================\n");
    printf("O texto foi alterado para caixa alta!\n");
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
    printf("=========================================\n");
    printf("Texto convertido pra caixa baixa!\n");
}

// objetivo: Capitaliza a primeira letra de cada frase no texto
// parametros: texto que terá as primeiras letras das frases capitalizadas
// retorno: nenhum
void CapitalizarPrimLetraFrase(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int *quantidade_linhas) {
    limparEspacosExtras(text);
    
    int capitalizarProxima = 1;
    int tamanho = strlen(text);
    
    // Converte tudo para minúsculas primeiro
    for (int i = 0; i < tamanho; i++) {
        text[i] = tolower((unsigned char)text[i]);
    }
    
    // Capitaliza primeira letra de cada frase
    for (int i = 0; i < tamanho; i++) {
        if (capitalizarProxima && isalpha((unsigned char)text[i])) {
            text[i] = toupper((unsigned char)text[i]);
            capitalizarProxima = 0;
        }
        
        // Verifica fim de frase
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            int j = i + 1;
            while (j < tamanho && isspace((unsigned char)text[j])) {
                j++;
            }
            if (j < tamanho && isalpha((unsigned char)text[j])) {
                capitalizarProxima = 1;
            }
        }
    }
    
    // Garante primeira letra maiúscula
    if (tamanho > 0 && isalpha((unsigned char)text[0])) {
        text[0] = toupper((unsigned char)text[0]);
    }
    
    *quantidade_linhas = formatarTexto(text, linhas);
    printf("=========================================\n");
    printf("Texto com primeira letra de cada frase maiuscula!\n");
}

// objetivo: Alinha todo o texto à esquerda (padrão)
// parametros: quantidade de linhas, matriz de linhas contendo o texto
// retorno: nenhum
void AlinharEsquerda(char linhas[MAX_LINHAS][MAX_LINHA_compr+1]) {
    for (int i = 0; i < MAX_LINHAS; i++) {
        limparEspacosExtras(linhas[i]);
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
    for (int i = 0; i < MAX_LINHAS; i++) {
        limparEspacosExtras(linhas[i]);
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
    for (int i = 0; i < MAX_LINHAS; i++) {
        if (linhas[i][0] == '\0') break;

        char temp[MAX_LINHA_compr + 1];
        strcpy(temp, linhas[i]);
        limparEspacosExtras(temp);

        // Não justificar a última linha
        if (linhas[i+1][0] == '\0') {
            strcpy(linhas[i], temp);
            continue;
        }

        // Tokenizar palavras
        char *palavras[100];
        int cont = 0;
        char *tok = strtok(temp, " ");
        int total_chars = 0;
        while (tok != NULL) {
            palavras[cont++] = tok;
            total_chars += strlen(tok);
            tok = strtok(NULL, " ");
        }

        if (cont <= 1) {
            // nada a justificar
            strcpy(linhas[i], palavras[0]);
            continue;
        }

        int total_esp = MAX_LINHA_compr - total_chars;
        int gaps = cont - 1;
        int esp_base = total_esp / gaps;
        int extra = total_esp % gaps;

        char resultado[MAX_LINHA_compr + 1] = "";
        int pos = 0;
        for (int j = 0; j < cont; j++) {
            int len = strlen(palavras[j]);
            strncpy(&resultado[pos], palavras[j], len);
            pos += len;
            if (j < cont - 1) {
                int num = esp_base + (j < extra ? 1 : 0);
                for (int k = 0; k < num; k++) {
                    resultado[pos++] = ' ';
                }
            }
        }
        resultado[pos] = '\0';
        strcpy(linhas[i], resultado);
    }
}

// objetivo: Centraliza todas as linhas do texto
// parametros: matriz de linhas contendo o texto, quantidade de linhas
// retorno: nenhum
void Centralizar(char linhas[MAX_LINHAS][MAX_LINHA_compr + 1]) {
    // Implementação pendente - VINI
    for (int i = 0; i < MAX_LINHAS; i++) {
        limparEspacosExtras(linhas[i]);
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

// objetivo: Atualizar o texto apos alguma alteracao
// parametros: texto original ou ja alterado, linhas da matriz, quantidade de linhas
// retorno: nenhum
void AtualizarTextoOriginal(char *text, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int quantidade_linhas) {
    //Jota
    text[0] = '\0';
    for (int i = 0; i < quantidade_linhas; i++) {
        strncat(text, linhas[i], MAX_TEXTO - strlen(text) - 1);
        strncat(text, "\n", MAX_TEXTO - strlen(text) - 1);
    }
}

// objetivo: Garantir que nao tenha linhas excedendo ou ate problemas com buffer
// parametros: matriz linhas, e a quantidade de linhas que o texto tem ate o momento
// retorno: nenhum
void ajustarLinhas(char linhas[MAX_LINHAS][MAX_LINHA_compr+1], int *quantidade_linhas) {
    int i = 0;
    while (i < *quantidade_linhas){
        if(strlen(linhas[i]) > MAX_LINHA_compr){
            if (*quantidade_linhas >= MAX_LINHAS){
                printf("ERRO: limite maximo de linhas atingido! Parte do texto pode estar sendo afetado!\n");
                linhas[i][MAX_LINHA_compr] = '\0';
                i++;
                continue;
            }
            int corte = MAX_LINHA_compr;
            while(corte > 0 && linhas[i][corte] != ' '){
                corte--;
            }

            if (corte == 0){
                corte = MAX_LINHA_compr;
            }

            size_t inicio_proxima = corte;
            while (inicio_proxima < strlen(linhas[i]) && linhas[i][inicio_proxima] == ' '){
                inicio_proxima++;
            }

            //Abre espaço na matriz, basicamente to movendo todas as linhas de baixo para baixo
            for(int j = *quantidade_linhas; j > i + 1; j--) {
                strcpy(linhas[j], linhas[j-1]);
            }
            (*quantidade_linhas)++;

            strncpy(linhas[i+1], linhas[i] + inicio_proxima, MAX_LINHA_compr);
            linhas[i+1][MAX_LINHA_compr] = '\0';

            linhas[i][corte] = '\0'; //garanto que finalizei no corte
        } else {
            i++;
        }
    }
}


//-----------------------------------------------------

// objetivo: Exibe menu interativo e chama funções de formatação de texto conforme escolha do usuário
// parametros: texto original, matriz de linhas formatadas, ponteiro para quantidade de linhas
// retorno: nenhum
void Menu(char *texto, char linhas[MAX_LINHAS][MAX_LINHA_compr + 1], int *quantidade_linhas) {
    //Jota
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
        printf("7 - Capitalizar as Palavras\n");
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
            BuscarPalavra(linhas, linha_cont, quantidade_linhas);
            ajustarLinhas(linhas, quantidade_linhas);
            AtualizarTextoOriginal(texto, linhas, *quantidade_linhas);
            break;

        case 3:
            // objetivo: Substitui primeira ocorrência e reformata texto
            SubPrimOcorrencia(linhas, texto, quantidade_linhas);
            ajustarLinhas(linhas, quantidade_linhas);
            AtualizarTextoOriginal(texto, linhas, *quantidade_linhas);
            break;
        
        case 4:
            // objetivo: Substitui todas ocorrências e reformata texto
            SubTodasOcorrencia(texto, linhas, quantidade_linhas);
            ajustarLinhas(linhas, quantidade_linhas);
            AtualizarTextoOriginal(texto, linhas, *quantidade_linhas);
            break;

        case 5:
            // objetivo: Converte para maiúsculas e reformata texto
            CaixaAlta(texto, linhas, quantidade_linhas);
            ajustarLinhas(linhas, quantidade_linhas);
            AtualizarTextoOriginal(texto, linhas, *quantidade_linhas);

            break;

        case 6:
            // objetivo: Converte para minúsculas e reformata texto
            CaixaBaixa(texto, linhas, quantidade_linhas);
            ajustarLinhas(linhas, quantidade_linhas);
            AtualizarTextoOriginal(texto, linhas, *quantidade_linhas);
            break;

        case 7:
            // objetivo: Capitaliza frases e reformata texto
            CapitalizarPrimLetraFrase(texto, linhas, quantidade_linhas);
            ajustarLinhas(linhas, quantidade_linhas);
            AtualizarTextoOriginal(texto, linhas, *quantidade_linhas);
            break;
        
        case 8:
            // objetivo: Alinha texto à esquerda
            AlinharEsquerda(linhas);
            ajustarLinhas(linhas, quantidade_linhas);
            AtualizarTextoOriginal(texto, linhas, *quantidade_linhas);
            break;

        case 9:
            // objetivo: Alinha texto à direita
            AlinharDireita(linhas);        
            ajustarLinhas(linhas, quantidade_linhas);   
            AtualizarTextoOriginal(texto, linhas, *quantidade_linhas);
            break;

        case 10:
            // objetivo: Justifica o texto
            Justificar(linhas);
            ajustarLinhas(linhas, quantidade_linhas);
            AtualizarTextoOriginal(texto, linhas, *quantidade_linhas);
            break;

        case 11:
            // objetivo: Centraliza o texto
            Centralizar(linhas);
            ajustarLinhas(linhas, quantidade_linhas);
            AtualizarTextoOriginal(texto, linhas, *quantidade_linhas);
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