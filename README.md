<h1 align="center">Desafio 42Labs 3º Edição 💻</h1>
![42_Technologies_logo](https://user-images.githubusercontent.com/84791310/182486687-6cdaeda0-137b-48b2-a715-3186ecb84a68.svg)
<h2 align="center">Descrição do projeto</h2>
<p>Um serviço de monitoramente que utiliza alguns protocolos para trazer informações sobre a sua aplicação web.</p>
:hammer: Funcionalidades do projeto

- `Facil configuração`: Temos um arquivo de confiração simples onde basta você colocar algumas informações e executar o serviço.  
- `Verificação de saude`: Você conseguira ver se o seu serviço web está saudavel, perdendo pacotes, com atrasos e mais.
- `Checkagem de dominio/ip/dns`: Você também conseguira ver se o seu serviço está atendendo no dominio/ip/dns correto.


## 📁 Acesso ao projeto
- `Passo 1`: Clone o repositório do projeto em sua máquina.
- `Passo 2`: Entre no arquivo de confiração `("./logs/monitoring.db")` e coloque as sua informações.
- `Passo 3`: na pasta raiz, compile o projeto (basta usar o comando `make`).
- `Passo 4`: agora, utilize o comando `make run` | você também pode utilizar o comando `make run --simplify`
- também utilizando o comando `./monitoring --help` vai aparecer o manual do programa onde você pode tirar suas dulvidas.

## 🚀 Tecnologias utilizadas
- `Bibliotecas`: Libcurl
- `Liguagens`: C
- `Ferramentas`: Visual Studio Code

## Dependências
- gcc
- make
- libcurl
- libcurl4-openssl-dev
