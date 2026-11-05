
#include <stdio.h>
#include <mysql.h>
#include <string.h>

// Funcoes de relatorios

void listarOrdens(MYSQL *conexao);
void filtrarPorStatus(MYSQL *conexao);
void filtrarPorUnidade(MYSQL *conexao);
void filtrarPorPeriodo(MYSQL *conexao);
void consultarPorEquipamento(MYSQL *conexao);
void consultarDetalhes(MYSQL *conexao);


int main(void) {
    MYSQL *conexao = mysql_init(NULL);

    if (conexao == NULL) {
        printf("Erro ao inicializar o MySQL.\n");
        return 1;
    }

    /*
       Preencha os dados localmente.
       Nunca publique sua senha no GitHub.
    */
    const char *usuario = "USUARIO_DO_MYSQL";
    const char *senha = "SENHA_DO_MYSQL";

    if (mysql_real_connect(
            conexao,
            "localhost",
            usuario,
            senha,
            "techfix",
            3306,
            NULL,
            0
        ) == NULL) {

        printf("Falha na conexao: %s\n",
               mysql_error(conexao));

        mysql_close(conexao);
        return 1;
    }

    printf("Conexao com o banco TechFix realizada!\n");

   int opcao;

   //Menu Principal

   do {

    printf("\n=============================\n");
    printf("  TECHFIX - RELATORIOS\n");
    printf("\n=============================\n");
    
    printf("1 - Listar todas as ordens\n");
    printf("2 - Filtrar por status\n");
    printf("3 - Filtrar por unidade\n");
    printf("4 - Filtrar por periodo\n");
    printf("5 - Buscar por equipamento\n");
    printf("6 - Consultar detalhes da ordem\n");
    printf("0 - Sair\n");

    printf("\nEscolha uma opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {

        case 1:
            listarOrdens(conexao);
            break;

        case 2:
            filtrarPorStatus(conexao);
            break;

        case 3:
            filtrarPorUnidade(conexao);
            break;

        case 4:
            filtrarPorPeriodo(conexao);
            break;

        case 5:
            consultarPorEquipamento(conexao);
            break;

        case 6:
            consultarDetalhes(conexao);
            break;

        case 0:
            printf("\nEncerrando o programa...\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    // Encerrar conexao
    mysql_close(conexao);

    return 0;

   }


// 1. Listar todas as Ordens

void listarOrdens(MYSQL *conexao) {

    printf("\n============ ORDENS DE SERVIÇO ============\n");

    if (mysql_query(
        conexao,
        "SELECT id_os, status, data_abertura FROM ORDEM_SERVICO ORDER BY id_os"
    ) != 0) {
        printf("Erro na consulta: %s\n",
        mysql_error(conexao));

        return;
    }
    MYSQL_RES *resultado = mysql_store_result(conexao);

    if (resultado == NULL) {
        printf("Erro ao obter resultado %s\n",
            mysql_error(conexao));
        return;

    }
    MYSQL_ROW linha;

    if (mysql_num_rows(resultado) == 0) {
        printf("Nenhuma ordem cadastrada.\n");

    } else {
        printf("\n%-8s %-20s %-15s\n",
            "OS", "STATUS", "DATA ABERTURA");
        printf("------------------------------\n");

        while ((linha = mysql_fetch_row(resultado)) != NULL) {
            printf("%-8s %-20s %-15s\n",
                linha[0],
                linha[1],
                linha[2]);
        }
    }
    mysql_free_result(resultado);
}


void filtrarPorStatus(MYSQL *conexao) {
    int opcao;

    printf("\n======== Filtro por Status =========\n");

    printf("1 - CONCLUIDA\n");
    printf("2 - EM_REPARO\n");
    printf("3 - CANCELADA\n");

    printf("\nSelecione o status: ");
    scanf("%d", &opcao);

    switch(opcao) {
        case 1:
            mysql_query(conexao, "SELECT id_os, status, data_abertura FROM ORDEM_SERVICO WHERE status = 'CONCLUIDA'");
            break;

        case 2:
            mysql_query(conexao, "SELECT id_os, status, data_abertura FROM ORDEM_SERVICO WHERE status = 'EM_REPARO'");
            break;
        
        case 3:
            mysql_query(conexao, "SELECT id_os, status, data_abertura FROM ORDEM_SERVICO WHERE status = 'CANCELADA'");
            break;
        
        default:
            printf("\nOpcao Invalida!\n");
            return;
            
    }
    MYSQL_RES *resultado = mysql_store_result(conexao);

    if (resultado == NULL) {
        printf("Erro ao obter resultado %s\n", mysql_error(conexao));
        return;

    }
    MYSQL_ROW linha;

    printf("\n=========== RESULTADO ===========\n");

    printf("\n%-8s %-20s %-15s\n", "OS", "STATUS", "DATA ABERTURA");
    printf("-------------------------------------\n");

    while ((linha = mysql_fetch_row(resultado)) != NULL) {
        printf("%-8s %-20s %-15s\n", 
        linha[0], linha[1], linha[2]);
    }
    if (mysql_num_rows(resultado) == 0) {
        printf("Nenhuma ordem encontrada.\n");
    }
    mysql_free_result(resultado);
}

void filtrarPorUnidade(MYSQL *conexao) {

    int opcao;

        printf("\n========== FILTRO POR UNIDADE ==========\n");

    printf("1 - TechFix Sao Paulo\n");
    printf("2 - TechFix Guarulhos\n");
    printf("3 - TechFix Osasco\n");
    printf("4 - TechFix Santo Andre\n");
    printf("5 - TechFix Sao Bernardo do Campo\n");

    printf("\nSelecione a unidade: ");
    scanf("%d", &opcao);


    switch (opcao) {

        case 1:
            mysql_query(conexao, "SELECT ORDEM_SERVICO.id_os, UNIDADE.nome, ORDEM_SERVICO.status, ORDEM_SERVICO.data_abertura"
                " FROM ORDEM_SERVICO INNER JOIN UNIDADE ON ORDEM_SERVICO.id_unidade = UNIDADE.id_unidade WHERE UNIDADE.id_unidade = 1");
                break;

        case 2:
            mysql_query(conexao, "SELECT ORDEM_SERVICO.id_os, UNIDADE.nome, ORDEM_SERVICO.status, ORDEM_SERVICO.data_abertura"
                " FROM ORDEM_SERVICO INNER JOIN UNIDADE ON ORDEM_SERVICO.id_unidade = UNIDADE.id_unidade WHERE UNIDADE.id_unidade = 2");
                break;
        case 3:
            mysql_query(conexao, "SELECT ORDEM_SERVICO.id_os, UNIDADE.nome, ORDEM_SERVICO.status, ORDEM_SERVICO.data_abertura"
                " FROM ORDEM_SERVICO INNER JOIN UNIDADE ON ORDEM_SERVICO.id_unidade = UNIDADE.id_unidade WHERE UNIDADE.id_unidade = 3");
                break;
        case 4:
            mysql_query(conexao, "SELECT ORDEM_SERVICO.id_os, UNIDADE.nome, ORDEM_SERVICO.status, ORDEM_SERVICO.data_abertura"
                " FROM ORDEM_SERVICO INNER JOIN UNIDADE ON ORDEM_SERVICO.id_unidade = UNIDADE.id_unidade WHERE UNIDADE.id_unidade = 4");
                break;
        case 5:
            mysql_query(conexao, "SELECT ORDEM_SERVICO.id_os, UNIDADE.nome, ORDEM_SERVICO.status, ORDEM_SERVICO.data_abertura"
                " FROM ORDEM_SERVICO INNER JOIN UNIDADE ON ORDEM_SERVICO.id_unidade = UNIDADE.id_unidade WHERE UNIDADE.id_unidade = 5");
                break;
        default:
            printf("\nOpcao Invalida!\n");
            return;
    }

    MYSQL_RES *resultado = mysql_store_result(conexao);

    if (resultado == NULL) {
        printf("Erro ao obter resultado: %s\n", mysql_error(conexao));
        return;
    }
    MYSQL_ROW linha;

    printf("\n=========== RESULTADO ===========\n");
    
    printf("\n%-8s %-30s %-20s %-15s\n", "OS", "UNIDADE", "STATUS", "DATA ABERTURA");
    printf("---------------------------------------------------\n");

    while ((linha = mysql_fetch_row(resultado)) != NULL) {
        printf("%-8s %-30s %-20s %-15s\n",
        linha[0], linha[1], linha[2], linha[3]);
    }
    
    if (mysql_num_rows(resultado) == 0) {
        printf("Nenhuma ordem encontrada nesta unidade.\n");
    }

    mysql_free_result(resultado);
}


void filtrarPorPeriodo(MYSQL *conexao) {

    char dataInicial[11];
    char dataFinal[11];

    printf("\n============== FILTRO POR PERIODO ================\n");

    printf("Digite a data inicial (AAAA-MM-DD): ");
    scanf("%10s", dataInicial);

    printf("Digite a data final (AAAA-MM-DD): ");
    scanf("%10s", dataFinal);

    MYSQL_STMT *stmt = mysql_stmt_init(conexao);

    if(stmt == NULL) {
        printf("Erro ao inicializar consulta.\n");
        return;
    }
    char consulta[] = "SELECT id_os, status, data_abertura FROM ORDEM_SERVICO WHERE data_abertura BETWEEN ? AND ?"
    " ORDER BY data_abertura";

    if (mysql_stmt_prepare(stmt, consulta, sizeof(consulta) - 1) != 0) {
        printf("Erro ao preparar consulta: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return;
    }

    MYSQL_BIND parametros[2] = {0};

    unsigned long tamanhoInicial = 10;
    unsigned long tamanhoFinal = 10;

    parametros[0].buffer_type = MYSQL_TYPE_STRING;
    parametros[0].buffer = dataInicial;
    parametros[0].buffer_length = 10;
    parametros[0].length = &tamanhoInicial;

    parametros[1].buffer_type = MYSQL_TYPE_STRING;
    parametros[1].buffer = dataFinal;
    parametros[1].buffer_length = 10;
    parametros[1].length = &tamanhoFinal;

    if (mysql_stmt_bind_param(stmt, parametros) != 0) {
        printf("Erro ao associar datas: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return;
    }

    if (mysql_stmt_execute(stmt) != 0) {
        printf("Erro ao executar consulta: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return;
    }
    int idOS;
    char status[21];
    char dataAbertura[11];

    MYSQL_BIND resultados[3] = {0};

    unsigned long tamanhoStatus;
    unsigned long tamanhoData;

    resultados[0].buffer_type = MYSQL_TYPE_LONG;
    resultados[0].buffer = &idOS;

    resultados[1].buffer_type = MYSQL_TYPE_STRING;
    resultados[1].buffer = status;
    resultados[1].buffer_length = sizeof(status);
    resultados[1].length = &tamanhoStatus;

    resultados[2].buffer_type = MYSQL_TYPE_STRING;
    resultados[2].buffer = dataAbertura;
    resultados[2].buffer_length = sizeof(dataAbertura);
    resultados[2].length = &tamanhoData;

    if (mysql_stmt_bind_result(stmt, resultados) != 0) {
        printf("Erro ao receber resultados: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return;
    
    }
    printf("\n============ RESULTADO ===========\n");

    printf("\n%-8s %-20s %-15s\n", "OS", "STATUS", "DATA ABERTURA");

    printf("-----------------------------------------\n");

    int retorno;
    int quantidade = 0;

    while ((retorno = mysql_stmt_fetch(stmt)) == 0) {
        printf("%-8d %-20s %-15s\n", idOS, status, dataAbertura);
        quantidade++;
    }
    if (retorno != MYSQL_NO_DATA) {
        printf("Erro ao buscar registros: %s\n", mysql_stmt_error(stmt));
    
    }
    if (quantidade == 0 ) {
        printf("Nenhuma ordem encontrada.\n");

    }
    mysql_stmt_close(stmt);
}

void consultarPorEquipamento(MYSQL *conexao) {

    char marcaBusca[41];

    printf("\n=============== BUSCA POR MARCA ================\n");

    printf("Digite a marca do equipamento: ");
    scanf(" %40[^\n]", marcaBusca);

    MYSQL_STMT *stmt = mysql_stmt_init(conexao);

    if (stmt == NULL) {
        printf("Erro ao inicializar consulta.\n");
        return;
    }

    char consulta[] = 
        "SELECT ORDEM_SERVICO.id_os, EQUIPAMENTO.tipo, EQUIPAMENTO.marca, EQUIPAMENTO.modelo, EQUIPAMENTO.numero_serie,"
        " ORDEM_SERVICO.status, ORDEM_SERVICO.data_abertura FROM ORDEM_SERVICO INNER JOIN EQUIPAMENTO ON ORDEM_SERVICO.id_equipamento"
        " = EQUIPAMENTO.id_equipamento WHERE EQUIPAMENTO.marca = ?";
    if (mysql_stmt_prepare(stmt, consulta, sizeof(consulta) - 1) != 0) {
        printf("Erro ao preparar consulta: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return;

    }

    MYSQL_BIND parametro[1] = {0};

    unsigned long tamanhoMarcaBusca = strlen(marcaBusca);

    parametro[0].buffer_type = MYSQL_TYPE_STRING;
    parametro[0].buffer = marcaBusca;
    parametro[0].buffer_length = sizeof(marcaBusca);
    parametro[0].length = &tamanhoMarcaBusca;

    if (mysql_stmt_bind_param(stmt, parametro) != 0) {
        printf("Erro ao associar parametro: %s\n",
               mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return;
    }

    if (mysql_stmt_execute(stmt) != 0 ) {
        printf("Erro ao executar consulta: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return;

    }
    int idOS;

    char tipo[41];
    char marca[41];
    char modelo[61];
    char serie[51];
    char status[21];
    char dataAbertura[11];

    MYSQL_BIND resultados[7] = {0};

    unsigned long tamanhoTipo = 0;
    unsigned long tamanhoMarca = 0;
    unsigned long tamanhoModelo = 0;
    unsigned long tamanhoSerie = 0;
    unsigned long tamanhoStatus = 0;
    unsigned long tamanhoData = 0;

    resultados[0].buffer_type = MYSQL_TYPE_LONG;
    resultados[0].buffer = &idOS;

    resultados[1].buffer_type = MYSQL_TYPE_STRING;
    resultados[1].buffer = tipo;
    resultados[1].buffer_length = sizeof(tipo);
    resultados[1].length = &tamanhoTipo;

    resultados[2].buffer_type = MYSQL_TYPE_STRING;
    resultados[2].buffer = marca;
    resultados[2].buffer_length = sizeof(marca);
    resultados[2].length = &tamanhoMarca;

    resultados[3].buffer_type = MYSQL_TYPE_STRING;
    resultados[3].buffer = modelo;
    resultados[3].buffer_length = sizeof(modelo);
    resultados[3].length = &tamanhoModelo;

    resultados[4].buffer_type = MYSQL_TYPE_STRING;
    resultados[4].buffer = serie;
    resultados[4].buffer_length = sizeof(serie);
    resultados[4].length = &tamanhoSerie;

    resultados[5].buffer_type = MYSQL_TYPE_STRING;
    resultados[5].buffer = status;
    resultados[5].buffer_length = sizeof(status);
    resultados[5].length = &tamanhoStatus;

    resultados[6].buffer_type = MYSQL_TYPE_STRING;
    resultados[6].buffer = dataAbertura;
    resultados[6].buffer_length = sizeof(dataAbertura);
    resultados[6].length = &tamanhoData;

    if (mysql_stmt_bind_result(stmt, resultados) != 0) {
        printf("Erro ao receber resultados: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return;

    }
    printf("\n================== ORDENS POR MARCA ================\n");

    printf("\n%-5s %-15s %-15s %-20s %-12s\n", "OS", "TIPO", "MARCA", "STATUS", "DATA");
    printf("------------------------------------------------------------\n");

    int retorno;
    int quantidade = 0;

    while ((retorno = mysql_stmt_fetch(stmt)) == 0) {
        printf("%-5d %-15s %-15s %-20s %-12s\n",
        idOS, tipo, marca, status, dataAbertura);

        quantidade++;
    }
    
    if (retorno != MYSQL_NO_DATA) {
        printf("Erro ao buscar registros: %s\n", mysql_stmt_error(stmt));

    }

    if (quantidade ==0) {
        printf("Nenhuma ordem encontrada para essa marca.\n");
    } else {
        printf("\nTotal de ordens encontradas: %d\n", quantidade);
    }

    mysql_stmt_close(stmt);

}

void consultarDetalhes(MYSQL *conexao) {

    int idOS;

    printf("\n============== DETALHES DA ORDEM DE SERVIÇO ================\n");
    
    printf("Digite o numero de id da Ordem de Servico: ");
    scanf("%d", &idOS);

    MYSQL_STMT *stmt = mysql_stmt_init(conexao);

    if (stmt == NULL) {
        printf("Erro ao inicializar consulta.\n");
        return;
    
    }

    char consulta[] = "SELECT ORDEM_SERVICO.id_os, ORDEM_SERVICO.status, ORDEM_SERVICO.data_abertura, ORDEM_SERVICO.data_encerramento, EQUIPAMENTO.tipo, EQUIPAMENTO.marca,"
        " EQUIPAMENTO.modelo, EQUIPAMENTO.numero_serie, TECNICO.nome, TECNICO.especialidade, UNIDADE.nome, UNIDADE.cidade, ORDEM_SERVICO.defeito_relatado, ORDEM_SERVICO.diagnostico"
        " FROM ORDEM_SERVICO INNER JOIN EQUIPAMENTO ON ORDEM_SERVICO.id_equipamento = EQUIPAMENTO.id_equipamento INNER JOIN TECNICO ON ORDEM_SERVICO.id_tecnico = "
        " TECNICO.id_tecnico INNER JOIN UNIDADE ON ORDEM_SERVICO.id_unidade = UNIDADE.id_unidade WHERE ORDEM_SERVICO.id_os = ?";

    if (mysql_stmt_prepare(stmt, consulta, sizeof(consulta) -1) != 0) {
        printf("Erro ao preparar consulta. %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return;

    }

    MYSQL_BIND parametro[1] = {0};

    parametro[0].buffer_type = MYSQL_TYPE_LONG;
    parametro[0].buffer = &idOS;

    if (mysql_stmt_bind_param(stmt, parametro) != 0) {
        printf("Erro ao associar numero da OS: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return;

    }

    if (mysql_stmt_execute(stmt)!= 0) {
        printf("Erro ao executar consulta: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return;

    }

    int idResultado;

    char status[21];
    char dataAbertura[11];
    char dataEncerramento[11];

    char tipo[41];
    char marca[41];
    char modelo[61];
    char numeroSerie[51];

    char nomeTecnico[101];
    char especialidade[101];

    char nomeUnidade[101];
    char cidade[101];

    char defeito[501];
    char diagnostico[501];

    MYSQL_BIND resultados[14] = {0};

    unsigned long tamanhoStatus = 0;
    unsigned long tamanhoDataAbertura = 0;
    unsigned long tamanhoDataEncerramento = 0;
    unsigned long tamanhoTipo = 0;
    unsigned long tamanhoMarca = 0;
    unsigned long tamanhoModelo = 0;
    unsigned long tamanhoSerie = 0;
    unsigned long tamanhoNomeTecnico = 0;
    unsigned long tamanhoEspecialidade = 0;
    unsigned long tamanhoNomeUnidade = 0;
    unsigned long tamanhoCidade = 0;
    unsigned long tamanhoDefeito = 0;
    unsigned long tamanhoDiagnostico = 0;
    my_bool nuloDataEncerramento = 0;
    my_bool nuloDefeito = 0;
    my_bool nuloDiagnostico = 0;

    resultados[0].buffer_type = MYSQL_TYPE_LONG;
    resultados[0].buffer = &idResultado;

    resultados[1].buffer_type = MYSQL_TYPE_STRING;
    resultados[1].buffer = status;
    resultados[1].buffer_length = sizeof(status);
    resultados[1].length = &tamanhoStatus;

    resultados[2].buffer_type = MYSQL_TYPE_STRING;
    resultados[2].buffer = dataAbertura;
    resultados[2].buffer_length = sizeof(dataAbertura);
    resultados[2].length = &tamanhoDataAbertura;

    resultados[3].buffer_type = MYSQL_TYPE_STRING;
    resultados[3].buffer = dataEncerramento;
    resultados[3].buffer_length = sizeof(dataEncerramento);
    resultados[3].length = &tamanhoDataEncerramento;
    resultados[3].is_null = &nuloDataEncerramento;

    resultados[4].buffer_type = MYSQL_TYPE_STRING;
    resultados[4].buffer = tipo;
    resultados[4].buffer_length = sizeof(tipo);
    resultados[4].length = &tamanhoTipo;

    resultados[5].buffer_type = MYSQL_TYPE_STRING;
    resultados[5].buffer = marca;
    resultados[5].buffer_length = sizeof(marca);
    resultados[5].length = &tamanhoMarca;

    resultados[6].buffer_type = MYSQL_TYPE_STRING;
    resultados[6].buffer = modelo;
    resultados[6].buffer_length = sizeof(modelo);
    resultados[6].length = &tamanhoModelo;

    resultados[7].buffer_type = MYSQL_TYPE_STRING;
    resultados[7].buffer = numeroSerie;
    resultados[7].buffer_length = sizeof(numeroSerie);
    resultados[7].length = &tamanhoSerie;

    resultados[8].buffer_type = MYSQL_TYPE_STRING;
    resultados[8].buffer = nomeTecnico;
    resultados[8].buffer_length = sizeof(nomeTecnico);
    resultados[8].length = &tamanhoNomeTecnico;

    resultados[9].buffer_type = MYSQL_TYPE_STRING;
    resultados[9].buffer = especialidade;
    resultados[9].buffer_length = sizeof(especialidade);
    resultados[9].length = &tamanhoEspecialidade;

    resultados[10].buffer_type = MYSQL_TYPE_STRING;
    resultados[10].buffer = nomeUnidade;
    resultados[10].buffer_length = sizeof(nomeUnidade);
    resultados[10].length = &tamanhoNomeUnidade;

    resultados[11].buffer_type = MYSQL_TYPE_STRING;
    resultados[11].buffer = cidade;
    resultados[11].buffer_length = sizeof(cidade);
    resultados[11].length = &tamanhoCidade;

    resultados[12].buffer_type = MYSQL_TYPE_STRING;
    resultados[12].buffer = defeito;
    resultados[12].buffer_length = sizeof(defeito);
    resultados[12].length = &tamanhoDefeito;
    resultados[12].is_null = &nuloDefeito;

    resultados[13].buffer_type = MYSQL_TYPE_STRING;
    resultados[13].buffer = diagnostico;
    resultados[13].buffer_length = sizeof(diagnostico);
    resultados[13].length = &tamanhoDiagnostico;
    resultados[13].is_null = &nuloDiagnostico;

    if (mysql_stmt_bind_result(stmt, resultados) !=0) {
        printf("Erro ao associar resultados: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return;

    }

    int retorno = mysql_stmt_fetch(stmt);

    if (retorno == MYSQL_NO_DATA) {
        printf("\nNenhuma ordem de servico encontrada com esse ID.\n");
        mysql_stmt_close(stmt);
        return;

    }
    if (retorno != 0) {
        printf("Erro ao buscar detalhes: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return;

    }

    printf("\n=========== DETALHES DA ORDEM =============\n");

    printf("\nORDEM DE SERVICO\n");
    printf("Numero: %d\n", idResultado);
    printf("Status: %s\n", status);
    printf("Data de abertura: %s\n", dataAbertura);

    if (nuloDataEncerramento) {
        printf("Data de encerramento: Em aberto\n");
    } else {
        printf("Data de encerramento: %s\n", dataEncerramento);
    }

    printf("\nEQUIPAMENTO\n");
    printf("Tipo: %s\n", tipo);
    printf("Marca: %s\n", marca);
    printf("Modelo: %s\n", modelo);
    printf("Numero de serie: %s\n", numeroSerie);

    printf("\nTECNICO RESPONSAVEL\n");
    printf("Nome: %s\n", nomeTecnico);
    printf("Especialidade: %s\n", especialidade);

    printf("\nUNIDADE RESPONSAVEL\n");
    printf("Unidade: %s\n", nomeUnidade);
    printf("Cidade: %s\n", cidade);

    printf("\nATENDIMENTO\n");

    if (nuloDefeito) {
        printf("Defeito relatado: Nao informado\n");
    } else {
        printf("Defeito relatado: %s\n", defeito);
    }

    if (nuloDiagnostico) {
        printf("Diagnostico: Ainda nao informado\n");
    } else {
        printf("Diagnostico: %s\n", diagnostico);
    }
    mysql_stmt_close(stmt);

    MYSQL_STMT *stmtServicos = mysql_stmt_init(conexao);

    if (stmtServicos == NULL) {
        printf("\nErro ao incializar consulta de servicos.\n");
        return;

    }

    char consultaServicos[] = "SELECT SERVICO.descricao, ITEM_OS.quantidade, ITEM_OS.valor_cobrado FROM ITEM_OS INNER JOIN SERVICO ON ITEM_OS.id_servico = "
        " SERVICO.id_servico WHERE ITEM_OS.id_os = ?";

    if (mysql_stmt_prepare(stmtServicos, consultaServicos, sizeof(consultaServicos)- 1) != 0) {
        printf("Erro ao preparar consulta de servicos: %s\n", mysql_stmt_error(stmtServicos));
        mysql_stmt_close(stmtServicos);
        return;

    }
    MYSQL_BIND parametroServico[1] = {0};

    parametroServico[0].buffer_type = MYSQL_TYPE_LONG;
    parametroServico[0].buffer = &idOS;

    if (mysql_stmt_bind_param(stmtServicos, parametroServico) != 0) {
        printf("Erro ao associar ID da OS aos servicos: %s\n",
               mysql_stmt_error(stmtServicos));
        mysql_stmt_close(stmtServicos);
        return;
    }

    if (mysql_stmt_execute(stmtServicos) != 0) {
        printf("Erro ao executar consulta de servicos: %s\n",
               mysql_stmt_error(stmtServicos));
        mysql_stmt_close(stmtServicos);
        return;
    }

    char descricaoServico[256];
    int quantidadeServico;
    double valorCobrado;

    MYSQL_BIND resultadosServicos[3] = {0};

    unsigned long tamanhoDescricao = 0;

    resultadosServicos[0].buffer_type = MYSQL_TYPE_STRING;
    resultadosServicos[0].buffer = descricaoServico;
    resultadosServicos[0].buffer_length = sizeof(descricaoServico);
    resultadosServicos[0].length = &tamanhoDescricao;

    resultadosServicos[1].buffer_type = MYSQL_TYPE_LONG;
    resultadosServicos[1].buffer = &quantidadeServico;

    resultadosServicos[2].buffer_type = MYSQL_TYPE_DOUBLE;
    resultadosServicos[2].buffer = &valorCobrado;

    if (mysql_stmt_bind_result(stmtServicos, resultadosServicos) != 0) {
        printf("Erro ao receber servicos: %s\n",
               mysql_stmt_error(stmtServicos));
        mysql_stmt_close(stmtServicos);
        return;
    }

    printf("\nSERVICOS DA ORDEM\n");

    printf("%-30s %-12s %-15s\n",
           "DESCRICAO", "QUANTIDADE", "VALOR");

    printf("------------------------------------------------------------\n");

    int quantidadeRegistros = 0;
    int retornoServico;

    while ((retornoServico = mysql_stmt_fetch(stmtServicos)) == 0) {

        printf("%-30s %-12d R$ %.2f\n",
               descricaoServico,
               quantidadeServico,
               valorCobrado);

        quantidadeRegistros++;
    }

    if (retornoServico != MYSQL_NO_DATA) {
        printf("Erro ao buscar servicos: %s\n",
               mysql_stmt_error(stmtServicos));
    }

    if (quantidadeRegistros == 0) {
        printf("Nenhum servico associado a esta ordem.\n");
    }

    mysql_stmt_close(stmtServicos);

}
