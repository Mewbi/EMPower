# ⚙️ Arduino

O Arduino é responsável por coletar as informações do sensor EMG e realizar a movimentação dos servo motores (prótese da mão).

## 📌 Inicializando

Apenas o código presente no arquivo [main.ino](main.ino) deve ser utilizado no Arduino, os demais códigos foram usados apenas para fazer simulações e testes.

Caso seja identificado que os valores medidos durante a contração muscular esteja muito abaixo do nível de ativação, basta alterar a variável `EMGTrigger` no arquivo [main.ino](main.ino) para um valor mais baixo e recompilar o código.