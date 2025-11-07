CREATE TABLE umidade_solo (
    id SERIAL PRIMARY KEY,
    data_leitura VARCHAR(20),
    hora_leitura VARCHAR(20),
    umidade_analogica INTEGER,
    umidade_percentual INTEGER,
    estado VARCHAR(10)
);
