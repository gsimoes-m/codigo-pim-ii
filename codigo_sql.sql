-- =====================================================================
-- TECHFIX SERVIÇOS TÉCNICOS - Banco de dados de ordens de serviço
-- =====================================================================

DROP DATABASE IF EXISTS techfix;
CREATE DATABASE techfix;
USE techfix;

-- =====================================================================
-- 1. CRIAÇÃO DAS TABELAS
-- =====================================================================

CREATE TABLE UNIDADE (
    id_unidade    INT          NOT NULL AUTO_INCREMENT,
    nome          VARCHAR(80)  NOT NULL,
    cidade        VARCHAR(60)  NOT NULL,
    endereco      VARCHAR(120) NOT NULL,
    PRIMARY KEY (id_unidade)
);

CREATE TABLE CLIENTE (
    id_cliente       INT          NOT NULL AUTO_INCREMENT,
    tipo_cliente     VARCHAR(2)   NOT NULL,
    telefone         VARCHAR(20)  NOT NULL,
    email            VARCHAR(100),
    endereco         VARCHAR(120),
    data_cadastro    DATE         NOT NULL,
    PRIMARY KEY (id_cliente)
);

CREATE TABLE PESSOA_FISICA (
    id_cliente  INT          NOT NULL,
    nome        VARCHAR(100) NOT NULL,
    cpf         CHAR(11)     NOT NULL,
    PRIMARY KEY (id_cliente),
    UNIQUE (cpf),
    FOREIGN KEY (id_cliente) REFERENCES CLIENTE (id_cliente)
);

CREATE TABLE PESSOA_JURIDICA (
    id_cliente     INT          NOT NULL,
    razao_social   VARCHAR(120) NOT NULL,
    cnpj           CHAR(14)     NOT NULL,
    nome_contato   VARCHAR(100),
    PRIMARY KEY (id_cliente),
    UNIQUE (cnpj),
    FOREIGN KEY (id_cliente) REFERENCES CLIENTE (id_cliente)
);

CREATE TABLE EQUIPAMENTO (
    id_equipamento  INT          NOT NULL AUTO_INCREMENT,
    id_cliente      INT          NOT NULL,
    tipo            VARCHAR(40)  NOT NULL,
    marca           VARCHAR(40)  NOT NULL,
    modelo          VARCHAR(60)  NOT NULL,
    numero_serie    VARCHAR(50),
    PRIMARY KEY (id_equipamento),
    UNIQUE (numero_serie),
    FOREIGN KEY (id_cliente) REFERENCES CLIENTE (id_cliente)
);

CREATE TABLE TECNICO (
    id_tecnico     INT          NOT NULL AUTO_INCREMENT,
    id_unidade     INT          NOT NULL,
    nome           VARCHAR(100) NOT NULL,
    especialidade  VARCHAR(60),
    telefone       VARCHAR(20),
    email          VARCHAR(100),
    PRIMARY KEY (id_tecnico),
    FOREIGN KEY (id_unidade) REFERENCES UNIDADE (id_unidade)
);

CREATE TABLE SERVICO (
    id_servico    INT           NOT NULL AUTO_INCREMENT,
    descricao     VARCHAR(100)  NOT NULL,
    valor_padrao  DECIMAL(10,2) NOT NULL,
    PRIMARY KEY (id_servico),
    UNIQUE (descricao)
);

CREATE TABLE ORDEM_SERVICO (
    id_os              INT          NOT NULL AUTO_INCREMENT,
    id_equipamento     INT          NOT NULL,
    id_tecnico         INT          NOT NULL,
    id_unidade         INT          NOT NULL,
    data_abertura      DATE         NOT NULL,
    data_encerramento  DATE,
    status             VARCHAR(20)  NOT NULL,
    defeito_relatado   TEXT         NOT NULL,
    diagnostico        TEXT,
    PRIMARY KEY (id_os),
    FOREIGN KEY (id_equipamento) REFERENCES EQUIPAMENTO (id_equipamento),
    FOREIGN KEY (id_tecnico)     REFERENCES TECNICO (id_tecnico),
    FOREIGN KEY (id_unidade)     REFERENCES UNIDADE (id_unidade)
);

CREATE TABLE ITEM_OS (
    id_os          INT           NOT NULL,
    id_servico     INT           NOT NULL,
    quantidade     INT           NOT NULL,
    valor_cobrado  DECIMAL(10,2) NOT NULL,
    PRIMARY KEY (id_os, id_servico),
    FOREIGN KEY (id_os)        REFERENCES ORDEM_SERVICO (id_os),
    FOREIGN KEY (id_servico)   REFERENCES SERVICO (id_servico)
);

-- =====================================================================
-- 2. INSERÇÃO DE DADOS
-- =====================================================================

-- 2.1 Unidades
INSERT INTO UNIDADE (nome, cidade, endereco) VALUES
('TechFix São Paulo',            'São Paulo',            'Rua das Palmeiras, 120'),
('TechFix Guarulhos',            'Guarulhos',            'Av. dos Ipês, 450'),
('TechFix Osasco',               'Osasco',               'Rua do Comércio, 88'),
('TechFix Santo André',          'Santo André',          'Av. das Acácias, 900'),
('TechFix São Bernardo do Campo','São Bernardo do Campo','Rua dos Cedros, 310');

-- 2.2 Clientes
INSERT INTO CLIENTE (id_cliente, tipo_cliente, telefone, email, endereco, data_cadastro) VALUES
(1, 'PF', '(11) 91111-0001', 'mariana.alves@gmail.com',    'Rua A, 10 - São Paulo',        '2026-01-15'),
(2, 'PF', '(11) 91111-0002', 'carlos.lima@gmail.com',      'Rua B, 25 - Guarulhos',        '2026-02-03'),
(3, 'PJ', '(11) 3333-0003',  'contato@gmail.com.br',  'Av. Industrial, 500 - Osasco', '2026-02-20'),
(4, 'PF', '(11) 91111-0004', 'fernanda.costa@gmail.com',  'Rua D, 77 - Santo André',      '2026-03-11'),
(5, 'PJ', '(11) 3333-0005',  'tatiane_gamer@gmail.com',    'Av. Brasil, 1200 - São Paulo', '2026-04-02'),
(6, 'PF', '(11) 91111-0006', 'roberto.nogueira@gmail.com','Rua F, 15 - Osasco',            '2026-05-18'),
(7, 'PJ', '(11) 3333-0007',  'secretaria_principiante@gmail.com','Rua das Flores, 60 - São Bernardo do Campo','2026-06-09'),
(8, 'PF', '(11) 91111-0008', 'juliana.martins@gmail.com', 'Rua H, 33 - São Paulo',        '2026-07-21');

-- 2.3 Pessoas Físicas
INSERT INTO PESSOA_FISICA (id_cliente, nome, cpf) VALUES
(1, 'Mariana Alves',        '11122233301'),
(2, 'Carlos Eduardo Lima',  '11122233302'),
(4, 'Fernanda Costa',       '11122233304'),
(6, 'Roberto Nogueira',     '11122233306'),
(8, 'Juliana Martins',      '11122233308');

-- 2.4 Pessoas Jurídicas
INSERT INTO PESSOA_JURIDICA (id_cliente, razao_social, cnpj, nome_contato) VALUES
(3, 'Construtora Horizonte Ltda',     '11222333000101', 'Marcos Pereira'),
(5, 'Clínica Vida Saudável S/A',      '11222333000202', 'Patrícia Gomes'),
(7, 'Escola Aprender Mais Ltda',      '11222333000303', 'Sérgio Batista');

-- 2.5 Equipamentos
INSERT INTO EQUIPAMENTO (id_equipamento, id_cliente, tipo, marca, modelo, numero_serie) VALUES
(1,  1, 'Celular',     'Samsung', 'Galaxy A54',       'SN-A54-0001'),
(2,  1, 'Notebook',    'Dell',    'Inspiron 15',      'SN-DELL-0002'),
(3,  2, 'Notebook',    'Lenovo',  'IdeaPad 3',        'SN-LEN-0003'),
(4,  3, 'Desktop',     'HP',      'ProDesk 400',      'SN-HP-0004'),
(5,  3, 'Switch',      'Cisco',   'SG350',            'SN-CIS-0005'),
(6,  4, 'Celular',     'Apple',   'iPhone 12',        'SN-IPH-0006'),
(7,  5, 'Impressora',  'HP',      'LaserJet Pro',     'SN-LJP-0007'),
(8,  6, 'Notebook',    'Acer',    'Aspire 5',         'SN-ACE-0008'),
(9,  7, 'Desktop',     'Dell',    'OptiPlex 3080',    'SN-OPT-0009'),
(10, 8, 'Tablet',      'Samsung', 'Galaxy Tab A8',    'SN-TAB-0010');

-- 2.6 Técnicos
INSERT INTO TECNICO (id_tecnico, id_unidade, nome, especialidade, telefone, email) VALUES
(1,  1, 'Paulo Henrique Souza', 'Celulares e tablets',         '(11) 98888-0001', 'paulo.souza@gmail.com'),
(2,  1, 'Ana Beatriz Ribeiro',  'Notebooks e desktops',        '(11) 98888-0002', 'ana.ribeiro@gmail.com'),
(3,  2, 'Lucas Ferreira',       'Redes e infraestrutura',      '(11) 98888-0003', 'lucas.ferreira@gmail.com'),
(4,  3, 'Camila Duarte',        'Notebooks e desktops',        '(11) 98888-0004', 'camila.duarte@gmail.com'),
(5,  4, 'Rafael Oliveira',      'Celulares e tablets',         '(11) 98888-0005', 'rafael.oliveira@gmail.com'),
(6,  5, 'Tatiane Moreira',      'Impressoras e periféricos',   '(11) 98888-0006', 'tatiane.moreira@gmail.com'),
(7,  1, 'Marcos Vinícius',      'Redes e servidores',          '(11) 98888-0007', 'marcos.vinicius@gmail.com'),
(8,  1, 'Juliana Castro',       'Notebooks e celulares',       '(11) 98888-0008', 'juliana.castro@gmail.com'),
(9,  2, 'Rodrigo Almeida',      'Impressoras e periféricos',   '(11) 98888-0009', 'rodrigo.almeida@gmail.com'),
(10, 2, 'Larissa Mendes',       'Celulares e tablets',         '(11) 98888-0010', 'larissa.mendes@gmail.com'),
(11, 3, 'Bruno Henrique',       'Notebooks e desktops',        '(11) 98888-0011', 'bruno.henrique@gmail.com'),
(12, 3, 'Natália Souza',        'Redes e infraestrutura',      '(11) 98888-0012', 'natalia.souza@gmail.com'),
(13, 4, 'Felipe Santos',        'Manutenção de hardware',      '(11) 98888-0013', 'felipe.santos@gmail.com'),
(14, 4, 'Vanessa Lima',         'Suporte ao usuário',          '(11) 98888-0014', 'vanessa.lima@gmail.com'),
(15, 5, 'Diego Martins',        'Celulares e tablets',         '(11) 98888-0015', 'diego.martins@gmail.com'),
(16, 5, 'Camila Rocha',         'Notebooks e desktops',        '(11) 98888-0016', 'camila.rocha@gmail.com'),
(17, 1, 'Thiago Cardoso',       'Redes e segurança',           '(11) 98888-0017', 'thiago.cardoso@gmail.com'),
(18, 1, 'Renata Dias',          'Impressoras e periféricos',   '(11) 98888-0018', 'renata.dias@gmail.com'),
(19, 2, 'Alexandre Ramos',      'Notebooks e desktops',        '(11) 98888-0019', 'alexandre.ramos@gmail.com'),
(20, 2, 'Priscila Farias',      'Celulares e tablets',         '(11) 98888-0020', 'priscila.farias@gmail.com'),
(21, 3, 'Eduardo Gomes',        'Infraestrutura de redes',     '(11) 98888-0021', 'eduardo.gomes@gmail.com'),
(22, 3, 'Tatiane Azevedo',      'Suporte técnico geral',       '(11) 98888-0022', 'tatiane.azevedo@gmail.com'),
(23, 4, 'Gabriel Moreira',      'Manutenção avançada',         '(11) 98888-0023', 'gabriel.moreira@gmail.com'),
(24, 4, 'Sabrina Pires',        'Notebooks e ultrabooks',      '(11) 98888-0024', 'sabrina.pires@gmail.com'),
(25, 5, 'Matheus Araujo',       'Redes e servidores',          '(11) 98888-0025', 'matheus.araujo@gmail.com'),
(26, 5, 'Amanda Correia',       'Celulares e dispositivos',    '(11) 98888-0026', 'amanda.correia@gmail.com'),
(27, 1, 'Leonardo Peixoto',     'Impressoras a laser',         '(11) 98888-0027', 'leonardo.peixoto@gmail.com'),
(28, 2, 'Beatriz Neves',        'Notebooks e desktops',        '(11) 98888-0028', 'beatriz.neves@gmail.com'),
(29, 3, 'Guilherme Freitas',    'Suporte de campo',            '(11) 98888-0029', 'guilherme.freitas@gmail.com'),
(30, 4, 'Jessica Carvalho',     'Celulares e tablets',         '(11) 98888-0030', 'jessica.carvalho@gmail.com');

-- 2.7 Serviços
INSERT INTO SERVICO (id_servico, descricao, valor_padrao) VALUES
(1,  'Diagnóstico técnico',                     80.00),
(2,  'Troca de tela',                          350.00),
(3,  'Troca de bateria',                       180.00),
(4,  'Formatação e reinstalação do sistema',   120.00),
(5,  'Limpeza preventiva',                      90.00),
(6,  'Configuração de rede',                   250.00),
(7,  'Substituição de SSD',                    300.00),
(8,  'Manutenção de impressora',               160.00),
(9,  'Correção de falha de conexão intermitente', 150.00),
(10, 'Reparo de queda total de sinal Wi-Fi',   180.00),
(11, 'Otimização de lentidão na navegação',    120.00),
(12, 'Resolução de conflito de endereço IP',    100.00),
(13, 'Diagnóstico e correção de perda pacotes',  200.00),
(14, 'Substituição/crimpagem cabo de rede',     90.00),
(15, 'Substituição de porta de switch',        220.00),
(16, 'Configuração de servidores DNS',         130.00),
(17, 'Reparo falha comunicação servidor local',250.00),
(18, 'Resolução interferência sobrecarga rede',180.00);

-- 2.8 Ordens de Serviço
INSERT INTO ORDEM_SERVICO
(id_os, id_equipamento, id_tecnico, id_unidade, data_abertura, data_encerramento, status, defeito_relatado, diagnostico) VALUES
(1,  1,  1,  1, '2026-08-03', '2026-08-05', 'CONCLUIDA',      'Tela trincada após queda',              'Display danificado; troca necessária'),
(2,  2,  2,  1, '2026-08-10', '2026-08-12', 'CONCLUIDA',      'Lentidão e travamentos',                'Disco rígido com falhas; substituído por SSD'),
(3,  3,  4,  3, '2026-09-01', '2026-09-02', 'CONCLUIDA',      'Equipamento não liga',                  'Bateria esgotada'),
(4,  4,  11, 3, '2026-09-05', '2026-09-09', 'CONCLUIDA',      'Falha na inicialização',                'Sistema operacional corrompido'),
(5,  5,  3,  2, '2026-09-15', NULL,         'EM_REPARO',      'Perda de conexão intermitente',         'Configuração de rede e porta de switch'),
(6,  6,  5,  4, '2026-09-20', '2026-09-22', 'CONCLUIDA',      'Bateria descarrega rapidamente',        'Bateria com desgaste natural'),
(7,  7,  6,  5, '2026-10-01', NULL,         'EM_REPARO',      'Papel enroscando na bandeja',           'Rolete de tração gasto'),
(8,  8,  4,  3, '2026-10-05', NULL,         'EM_REPARO',      'Superaquecimento durante o uso',        'Muita poeira no cooler'),
(9,  9,  2,  1, '2026-10-07', '2026-10-08', 'CANCELADA',      'Equipamento não liga',                  'Cliente optou por não realizar o reparo'),
(10, 10, 1,  1, '2026-10-12', NULL,         'EM_REPARO',      'Tela não responde ao toque',            'Digitalizador defeituoso'),
(11, 5,  12, 3, '2026-10-14', NULL,         'EM_REPARO',      'Lentidão e conflito de IP na rede',     'Dois equipamentos com o mesmo IP');

-- 2.9 Itens das Ordens de Serviço
INSERT INTO ITEM_OS (id_os, id_servico, quantidade, valor_cobrado) VALUES
(1,  1,  1,  80.00), 
(1,  2,  1, 350.00), 
(2,  1,  1,  80.00), 
(2,  7,  1, 300.00), 
(2,  4,  1, 120.00), 
(3,  1,  1,  80.00), 
(3,  3,  1, 180.00), 
(4,  1,  1,  80.00), 
(4,  4,  1, 120.00), 
(5,  1,  1,  80.00), 
(5,  6,  1, 250.00), 
(5,  9,  1, 150.00), 
(5,  15, 1, 220.00), 
(6,  1,  1,  80.00), 
(6,  3,  1, 170.00), 
(7,  8,  1, 160.00), 
(8,  5,  1,  90.00), 
(9,  1,  1,  80.00), 
(10, 1,  1,  80.00), 
(10, 2,  1, 350.00), 
(11, 11, 1, 120.00), 
(11, 12, 1, 100.00); 

