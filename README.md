# Poisson Solver

Este projeto foi desenvolvido como um trabalho para a disciplina de Algoritmos Numéricos I em 2019/1, na UFES. O objetivo principal é a solução da equação de Poisson pelo método das diferenças finitas centrais, com o sistema resultante sendo resolvido pelo método SOR. Dessa maneira, é possível testar o sistema resultante com uma solução conhecida ou propor uma modelagem aproximada de um problema com comportamento conhecido sem solução exata conhecida. Mais detalhes sobre a proposta inicial estão disponíveis no [Relatório](Relatorio.pdf), também presente no repositório.

# Utilização
Abaixo seguem algumas informações sobre a utilização do algoritmo para resolver outros problemas similares.

### Instanciando a classe
Para possibilitar  a solução de outros problemas, a classe `poissonSOR` foi implementada. Portanto, para a utilização do projeto para solução de equações de Poisson, primeiramente deve-se instanciar a classe. O construtor da classe recebe seis parâmetros:

`poissonSOR(int x0, int x1, int y0, int y1, double hx, double hy);`

Onde
- `(x0, y0)` e `(x1, y1)` representam as coordenadas dos pontos de origem e de limite do domínio da análise, respectivamente. Estes pontos devem ser determinados a priori pelo usuário (representa o ponto inferior esquerdo e o ponto superior direito, respectivamente);
- `hx` e `hy` representam o tamanho do passo (*step*) da análise;

### Determinando a função

A função a ser analisada pelo algoritmo deve ser determinada e passada como parâmetro (*callback*) à função `setFXY` da instância da classe. Por exemplo: se *f(x,y) = xy*, então basta definir uma função:
```cpp
    double fxy(double x, double y) {
    	return x * y;
    }
```
E, após instanciar a classe, usar `instancia.setFXY(fxy)`. Note que a função passada para o *callback* **deve retornar um double e receber dois doubles como parâmetros**.

### Limitação de iterações

O usuário pode determinar um número máximo de iterações usando a função `instancia.setMaxIter()`. O padrão do projeto é 1000, definido por meio de uma constante no arquivo de cabeçalho da classe.

### Casos de contorno

#### Implementação do tipo de contorno

Caso seja necessário implementar casos de contorno, primeiramente o usuário deve adicionar um "tipo" de problema ao `enum type` no [cabeçalho da classe](src/poissonSOR.h). Em seguida, o usuário deve, no arquivo principal, informar à classe qual tipo de problema será resolvido por meio da função `instancia.setType()`.

#### Adicionando as funções de contorno

Em seguida, para cada caso de contorno, o usuário deve definir uma função com a mesma formatação da função de Poisson, e enviá-la à classe por meio da função `addContorno()`. Os contornos são armazenados na ordem que são adicionados na classe.

#### Implementando os contornos

O usuário deve implementar as condições de contorno em dois locais no [arquivo de implementação da classe](src/poissonSOR.cpp): na função `checkContornos()`, que é usada para calcular o `fp`, conforme descrito na documentação (relatório). De maneira simplificada, o usuário deve implementar usando os pontos (i, j) apropriados de discretização as condições de contorno conforme a modelagem do problema. O código já inclui dois exemplos dessas condições seguindo a [especificação](especificacao.pdf) como referência. Essa alteração é separada pois o cálculo do `fp` ocorre antes da execução do método SOR. Além desse local, o usuário também deve implementar as condições de contorno no método `doSOR()`, considerando a modelagem do seu problema no plano bidimensional e as condições de contorno associadas. Novamente, há um exemplo dessa implementação no código do repositório, que pode ser usado como referência de implementação. Por fim, cabe também ao usuário implementar, na função `typeToString()`, a "tradução" do tipo de método para uma string a fim de gerar a saída organizada.

### Campo elétrico

Adicionalmente, o programa também calcula uma representação do campo elétrico, que pode ser desativada na função `process()` na [implementação da classe](src/poissonSOR.cpp) caso não seja relevante para o projeto.

### Validação

Caso o usuário tenha uma função de validação que dá o resultado exato do problema e deseje validar o resultado obtido, basta definir uma função no mesmo formato da função de Poisson e passá-la à classe usando `instancia.setValFunc()`. Dessa forma, é possível analisar o erro do método além dos dados já obtidos normalmente. Caso não seja relevante, é possível desativar o cálculo do erro comentando as linhas na função `process()`, no arquivo de [implementação da classe](src/poissonSOR.cpp).


### Processamento

Após o fim das configurações pelo usuário, basta chamar na função principal ou subrotina apropriada a função `instancia.process()`, que realiza os cálculos apropriados e os armazena na classe.

## Salvando os resultados

Para salvar os resultados do processamento, basta chamar a função `instancia.writeOutputData()` na função principal ou subrotina apropriada. Adicionalmente, se alguma parte do projeto foi desativada, como a geração dos valores de campo elétrico ou a do *"Ground Truth"* a partir da função exata, essas gravações devem ser desativadas (comentadas) no [arquivo de implementação](src/poissonSOR.cpp). Os resultados são gravados em um arquivo de texto puro na pasta `/output`, formatado de acordo com a execução do projeto.

## Gerando as visualizações

O [script em Python](plot_rw.py) fornecido permite a geração de visualizações bidimensionais e tridimensionais dos resultados obtidos. Note que há configurações adicionais necessárias para utilizar o script: os valores de hx e hy devem ser configurados de acordo com os utilizados nos cálculos internos, e é necessário instalar duas bibliotecas adicionais: `numpy` e `matplotlib`. Com isso, basta configurar o script internamente pela função `setStuff()` (sem alterar as linhas do script diretamente para manter a consistência do arquivo) e executar o programa. As visualizações geradas são armazenadas na pasta `/imgs`.