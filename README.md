# T5
Trabalho 05 de Algoritmos e Estrutura de Dados I - UEMS

# T5
Processador e Formatador de Texto em C
Um programa de linha de comando escrito em C que simula um editor de texto básico. Ele utiliza um menu interativo para oferecer funcionalidades essenciais de formatação, busca e edição de texto.

Destaques e Funcionalidades
O programa começa com um texto pré-carregado (sobre Bill Gates) e gerencia o conteúdo dentro dos limites de 10.000 caracteres em linhas de, no máximo, 80 caracteres.

Formatação e Alinhamento
Controle total sobre a apresentação do texto:

Alinhamento: Mude a apresentação do texto para Esquerda, Direita ou Centralizado.

Justificação: Distribui os espaços de forma uniforme entre as palavras para preencher toda a largura da linha (exceto a última linha de cada parágrafo).

Edição e Transformação de Texto
Altere o estilo do conteúdo rapidamente:

Caixa Alta: Converte todo o texto para MAIÚSCULAS.

Caixa Baixa: Converte todo o texto para minúsculas.

Capitalização: Capitaliza a primeira letra de cada frase no texto.

Busca e Substituição
Ferramentas úteis para localizar e modificar palavras:

Buscar Palavra: Localiza e lista todas as ocorrências de uma palavra, indicando a linha e coluna exatas.

Substituir Primeira: Troca apenas a primeira ocorrência da palavra no texto.

Substituir Todas: Troca todas as ocorrências de uma palavra por uma nova.

Como Compilar e Executar
Este projeto é um código C padrão. Você só precisa do GCC (GNU Compiler Collection) ou um compilador C compatível para rodá-lo.

Salve o código em um arquivo chamado, por exemplo, editor.c.

Compile usando o terminal:

Bash

gcc editor.c -o editor
Execute o programa compilado:

Limite	Constante	Valor
Tamanho Máximo do Texto	MAX_TEXTO	10.000 caracteres
Comprimento Máximo da Linha	MAX_LINHA_compr	80 caracteres
Máximo de Linhas	MAX_LINHAS	500 linhas

Bash

./editor
O Menu interativo será exibido, permitindo que você escolha as operações (de 1 a 11) ou saia (0).
