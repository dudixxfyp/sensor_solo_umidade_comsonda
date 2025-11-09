# sensor solo de umidade com sonda  
Repositório: **sensor_solo_umidade_comsonda**

## 📌 Descrição  
Este projeto consiste em um sistema para **medir a umidade do solo** utilizando uma sonda de umidade conectada a um microcontrolador, e enviar ou armazenar os dados para posterior análise.

## 🔧 O que contém neste repositório  
- `*.ino` – Código Arduino/microcontrolador para leitura da sonda de umidade e envio dos dados.  
- `integra.py` – Script Python para integração ou envio/armazenamento dos dados lidos pela sonda.  
- `tabela.SQL` – Esquema de tabela SQL ou banco de dados para armazenar os valores de umidade do solo.  
- `README.md` – Este arquivo.

## 🧠 Funcionamento  
1. A sonda de umidade do solo conecta-se ao microcontrolador.  
2. O código no arquivo `.ino` faz a leitura periódica dos valores de umidade.  
3. Em seguida, os dados são enviados (por exemplo, via comunicação serial, WiFi, ou outro protocolo) para o script `integra.py`.  
4. O `integra.py` processa ou grava esses dados em um banco de dados definido no arquivo `tabela.SQL`.  
5. Posteriormente, os dados armazenados podem ser analisados, visualizados ou usados para controlar irrigação, alertas, etc.

## 🛠️ Como usar  
### Pré-requisitos  
- Microcontrolador compatível com o código (ex: Arduino, ESP32, etc).  
- Sonda de umidade do solo (compatível com seu microcontrolador).  
- Conexão e fiação adequada para a sonda.  
- Ambiente Python com as bibliotecas necessárias (dependendo do script `integra.py`).  
- Banco de dados (ex: MySQL, SQLite, ou outro) conforme especificado no `tabela.SQL`.

### Passos  
1. Carregue o código `.ino` no seu microcontrolador.  
2. Verifique a leitura de valores da sonda e certifique-se que os dados estão sendo enviados corretamente.  
3. Configure e execute o script `integra.py` no seu computador ou servidor para receber/processar os dados.  
4. Importe ou execute o `tabela.SQL` no seu banco de dados para criar a estrutura da tabela de umidade.  
5. Verifique que os dados estão sendo gravados corretamente no banco de dados.  
6. Use os dados para visualização ou controle adicional conforme seu projeto.

## 📊 Exemplos de execução  
```bash
# Carregar o código no microcontrolador via Arduino IDE ou outra ferramenta.
# Executar o script Python:
python3 integra.py
