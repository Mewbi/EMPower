# 🦾 EMPower

Projeto utilizando o sensor Eletromiográfico de Sinal Muscular (EMG) para a matéria de Sistemas Embarcados para Engenharia Biomédica (SEEB).

Os arquivos presentes nos diretórios iniciados com `lab` fazem referência aos scripts e programas criados durante a matéria.

Os arquivos e códigos utilizados para o projeto se encontram no diretório [Projeto](/Projeto/)

## 📌 Objetivos

O objetivo do projeto é identificar sinais de contração muscular para caso seja acima de um valor de ativação definido, realize a abertura ou fechamento da protese de mão utilizando servo motores.

As informações coletadas pelo sensor, assim como o status da mão devem ser apresentados em uma página Web.

## ⚙️ Arduino

As configurações no Arduino foram feitas seguindo o seguinte diagrama.

<center>

|  | |
|:----------:|:----------:|
| ![eletrodos1](/assets/diagrama.png) | ![eletrodos2](/assets/montagem.png) |

</center>

Foi aplicado um filtro para os valores lidos pelo sensor EMG.

<p align="center">
    <img src="/assets/filtro.gif">
</p>

Além disso, é feita a conexão do Arduino com a Raspberry por meio da interface Serial.

## 🖥️ Raspberry

A Raspberry possui duas responsabilidades:

- Server: recebe os dados enviados pelo Arduino, parseia e os disponibiliza em um serviço Websocket
- Web: apresenta a página Web em um serviço HTTP contendo as informações recebidas disponibilizadas no Websocket

A comunicação segue o seguinte fluxo

<p align="center">
    <img src="/assets/comunicacao.png">
</p>

## 📊 Funcionamento

Para verificar como incializar tudo acesse os READMEs do [Arduino](/Projeto/Arduino/README.md) e da [Raspberry](/Projeto/Raspberry/README.md)

É fundamental o posicionamento correto dos eletrodos conforme a imagem:

<center>

|  | |
|:----------:|:----------:|
| ![eletrodos1](/assets/eletrodos1.png) | ![eletrodos2](/assets/eletrodos2.png) |

</center>

Inicializando tudo será possível fazer a movimentação da prótese da mão conforme realizar a contração muscular do braço

<p align="center">
    <img src="/assets/funcionamento.gif">
</p>

Acessando a página web do serviço HTTP da Raspberry é possível acompanhar os valores medidos pelo sensor EMG em µV

<p align="center">
    <img src="/assets/emg.gif">
</p>

Também é apresentado o status atual da protese da mão

<p align="center">
    <img src="/assets/mao.gif">
</p>