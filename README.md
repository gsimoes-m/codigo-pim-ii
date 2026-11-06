# 🖥️ TechFix — Sistema de Gerenciamento de Ordens de Serviço

<p align="center">
  <strong>Sistema de consultas e gerenciamento de informações operacionais desenvolvido em C e MySQL.</strong>
</p>

---

## 📌 Sobre o Projeto

O **TechFix** é um projeto acadêmico desenvolvido no contexto do Projeto Integrado Multidisciplinar (PIM II) do curso de Análise e Desenvolvimento de Sistemas da Universidade Paulista (UNIP).

O projeto apresenta uma proposta de transformação digital para uma empresa fictícia de médio porte do segmento de assistência técnica e soluções tecnológicas.

Com o crescimento de suas operações e a existência de diferentes unidades de atendimento, a empresa passou a enfrentar dificuldades relacionadas à organização das informações, ao acompanhamento de equipamentos e ao gerenciamento de ordens de serviço.

Diante desse cenário, foi desenvolvida uma solução computacional que integra a linguagem C a um banco de dados MySQL, permitindo consultar, filtrar e visualizar informações operacionais de maneira estruturada.

O sistema tem como principal finalidade facilitar o acesso aos registros da empresa e demonstrar a aplicação prática de conceitos de programação estruturada e modelagem de banco de dados.

## 🎯 Objetivos

- Centralizar as informações operacionais em um banco de dados relacional.
- Facilitar a consulta de ordens de serviço.
- Permitir a filtragem de registros por diferentes critérios.
- Relacionar informações de clientes, equipamentos, técnicos, unidades e serviços.
- Demonstrar a integração entre uma aplicação desenvolvida em C e um banco de dados MySQL.
- Aplicar conhecimentos de programação estruturada e SQL em uma situação prática.

## ⚙️ Funcionalidades

O sistema possui um menu interativo com seis funcionalidades principais:

| Opção | Funcionalidade | Descrição |
|---|---|---|
| 1 | Listar todas as ordens | Exibe as ordens de serviço cadastradas, seus status e datas de abertura. |
| 2 | Filtrar por status | Permite consultar ordens concluídas, em reparo ou canceladas. |
| 3 | Filtrar por unidade | Apresenta as ordens vinculadas a uma unidade específica. |
| 4 | Filtrar por período | Consulta ordens dentro de um intervalo de datas informado. |
| 5 | Buscar por equipamento | Localiza ordens com base na marca do equipamento. |
| 6 | Consultar detalhes da ordem | Apresenta informações completas da ordem e os serviços associados. |

## 🗄️ Estrutura do Banco de Dados

O projeto utiliza um banco de dados relacional denominado `techfix`, desenvolvido em MySQL.

Sua estrutura é composta pelas seguintes tabelas:

| Tabela | Finalidade |
|---|---|
| `UNIDADE` | Armazena os dados das unidades da empresa. |
| `CLIENTE` | Registra informações gerais dos clientes. |
| `PESSOA_FISICA` | Armazena dados específicos de clientes pessoa física. |
| `PESSOA_JURIDICA` | Armazena dados específicos de clientes pessoa jurídica. |
| `EQUIPAMENTO` | Registra os equipamentos vinculados aos clientes. |
| `TECNICO` | Armazena informações dos técnicos responsáveis pelos serviços. |
| `SERVICO` | Registra os serviços disponibilizados pela empresa. |
| `ORDEM_SERVICO` | Armazena os registros e informações das ordens de serviço. |
| `ITEM_OS` | Relaciona as ordens de serviço aos serviços realizados. |

A modelagem permite relacionar diferentes informações por meio de identificadores e chaves entre tabelas, possibilitando consultas que reúnem dados de diferentes partes do sistema.

## 🔗 Integração entre C e MySQL

A aplicação foi desenvolvida em linguagem C e utiliza a biblioteca MySQL para estabelecer a comunicação com o banco de dados.

A integração permite que a aplicação execute instruções SQL, receba os resultados e apresente as informações diretamente no terminal.

Entre os principais recursos utilizados estão:

- `mysql_init()`: inicializa a estrutura de conexão.
- `mysql_real_connect()`: estabelece a conexão com o banco de dados.
- `mysql_query()`: executa consultas SQL.
- `mysql_store_result()`: armazena os resultados de uma consulta.
- `mysql_fetch_row()`: recupera os registros retornados.
- `mysql_stmt_prepare()`: prepara consultas parametrizadas.
- `mysql_stmt_bind_param()`: associa parâmetros às consultas preparadas.
- `mysql_stmt_execute()`: executa uma consulta preparada.
- `mysql_stmt_bind_result()`: associa os campos retornados às variáveis da aplicação.
- `mysql_close()`: encerra a conexão com o banco de dados.

Também são utilizados comandos SQL como `SELECT`, `WHERE`, `ORDER BY` e `INNER JOIN`, permitindo filtrar, ordenar e relacionar os dados armazenados.

## 🛠️ Tecnologias e Ferramentas

| Tecnologia | Aplicação no projeto |
|---|---|
| C | Desenvolvimento da aplicação e lógica do sistema. |
| MySQL | Armazenamento e gerenciamento dos dados. |
| SQL | Consulta e relacionamento das informações. |
| MySQL Connector / MariaDB Connector | Comunicação entre a aplicação C e o banco de dados. |
| GCC | Compilação do código-fonte. |
| Visual Studio Code | Ambiente de desenvolvimento. |
| MySQL Workbench | Administração e modelagem do banco de dados. |
| Git e GitHub | Versionamento e armazenamento do projeto. |


## 📂 Estrutura do Repositório

```text
TechFix/
│
├── techfix.c
│
├── codigo_sql.sql
│
└── README.md
```

A organização separa o código-fonte, os scripts do banco de dados e os documentos técnicos, facilitando a manutenção e a apresentação do projeto.

## 🔐 Segurança

O projeto utiliza conexão com banco de dados local para realizar as consultas.

Alguns cuidados devem ser observados ao utilizar ou compartilhar o código:

- Não publicar senhas ou credenciais de acesso.
- Evitar utilizar usuários administrativos, como `root`, na aplicação.
- Utilizar um usuário específico com permissões limitadas ao banco `techfix`.
- Utilizar dados fictícios ou anonimizados nos arquivos de demonstração.
- Não armazenar credenciais diretamente no repositório público.

## 📚 Contexto Acadêmico

Este projeto integra os conhecimentos desenvolvidos nas disciplinas do segundo período do curso de Análise e Desenvolvimento de Sistemas.

Entre os conteúdos aplicados estão:

- Pesquisa, Tecnologia e Inovação.
- Engenharia de Software Ágil.
- Programação Estruturada em C.
- Modelagem de Banco de Dados.
- Redes de Computadores.
- Sistemas Distribuídos.
- Direitos Humanos.

A proposta busca demonstrar como diferentes áreas da Tecnologia da Informação podem ser aplicadas de maneira integrada para atender às necessidades de uma organização.

## 👥 Equipe

Projeto desenvolvido por estudantes do curso de Análise e Desenvolvimento de Sistemas — Universidade Paulista (UNIP).

- Brian Lima Serafim
- Gabriel Pereira Mata de Ancelmo
- Gabriel Simões Pessoa Moino
- Gustavo Fernandes Justo

## 📄 Licença

Projeto desenvolvido para fins acadêmicos no contexto do Projeto Integrado Multidisciplinar (PIM II).

---

<p align="center">
  <strong>TECHFIX — Tecnologia aplicada à organização e gestão de serviços.</strong>
</p>
