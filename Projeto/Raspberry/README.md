# Raspberry 

O Raspberry é responsável por executar dois serviços:

- Comunicação com o Arduino para captar os dados do sensor
- Servidor Web para apresentar as informações coletadas

## Executando os Serviços

Os serviços podem ser inicializados usando `docker`

---

### Inicializando

Para iniciar os containers basta executar

```sh
docker compose up --force-recreate
```

A página web é hospedada no endereço local da máquina na porta 80, ou seja, pode ser acessando em `http://127.0.0.1`

---

### Ajustando Configuração

Em alguns casos ao fazer a ligação entre Raspberry e Arduino a porta que USB do Raspberry de comunicação pode alterar

Nesses casos é necessário alterar os arquivos `server/config.py` e `docker-compose.yml`

No arquivo `server/config.py` alterar de `/dev/ttyUSB0` para `/dev/ttyACM0` costuma ser o suficiente.

De maneira análogo no arquivo `docker-compose.yml` alterar de `- /dev/ttyUSB0:/dev/ttyUSB0` para `- /dev/ttyACM0:/dev/ttyACM0`

Depois faça a reinicialização dos serviços

```sh
docker compose restart
```
---

### Finalizando

Para parar a execução dos serviços basta executar

```sh
docker compose stop
```
