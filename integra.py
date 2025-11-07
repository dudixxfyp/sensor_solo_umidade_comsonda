# arquivo: api_sensor.py
from flask import Flask, request, jsonify
import psycopg2

app = Flask(__name__)

# --- Configuração do banco PostgreSQL ---
conn = psycopg2.connect(
    host="localhost",
    database="sensor_db",
    user="postgres",
    password="SENHA_DO_POSTGRES"
)

@app.route('/dados', methods=['POST'])
def receber_dados():
    data = request.get_json()

    data_lida = data['data']
    hora = data['hora']
    umidade_analogica = data['umidade_analogica']
    umidade_percentual = data['umidade_percentual']
    estado = data['estado_digital']

    cursor = conn.cursor()
    cursor.execute("""
        INSERT INTO umidade_solo (data_leitura, hora_leitura, umidade_analogica, umidade_percentual, estado)
        VALUES (%s, %s, %s, %s, %s)
    """, (data_lida, hora, umidade_analogica, umidade_percentual, estado))

    conn.commit()
    cursor.close()

    return jsonify({"status": "ok", "mensagem": "Dados recebidos com sucesso!"})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
