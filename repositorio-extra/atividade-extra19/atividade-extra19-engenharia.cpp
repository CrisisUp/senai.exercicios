/**
 * @file atividade-extra19-engenharia.cpp
 * @brief Monitoramento Estrutural: Membros Estáticos e Gestão Global.
 * 
 * Demonstra o uso de atributos e métodos 'static' para compartilhamento
 * de estado entre múltiplos objetos de uma classe.
 * 
 * @author SENAI - Cristiano Batista Pessoa
 * @date 19/04/2026
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// --- 1. NAMESPACE DE INTERFACE ---

namespace UI {
    const string RESET    = "\033[0m";
    const string VERMELHO = "\033[31m";
    const string VERDE    = "\033[32m";
    const string AMARELO  = "\033[33m";
    const string CIANO    = "\033[36m";
}

// --- 2. CLASSE COM MEMBROS ESTÁTICOS ---

class SensorPressao {
private:
    int id;
    double pressaoAtual;

    // --- ATRIBUTOS ESTÁTICOS (Compartilhados por todos os sensores) ---
    static int totalSensores;
    static bool alertaGeral;
    static const double LIMITE_MAXIMO; // Constante estática

public:
    // Construtor: Incrementa o contador global
    SensorPressao(int _id) : id(_id), pressaoAtual(0.0) {
        totalSensores++; 
    }

    // Método para atualizar leitura
    void atualizarLeitura(double novaPressao) {
        this->pressaoAtual = novaPressao;
        
        // Se QUALQUER sensor detectar sobrecarga, o ALERTA GERAL é ativado
        if (novaPressao > LIMITE_MAXIMO) {
            alertaGeral = true;
        }
    }

    // --- MÉTODOS ESTÁTICOS (Podem ser chamados sem um objeto específico) ---
    
    static int getTotalSensores() {
        return totalSensores;
    }

    static bool isSistemaSeguro() {
        return !alertaGeral;
    }

    static void resetarSistema() {
        alertaGeral = false;
        cout << UI::AMARELO << "[SISTEMA]: Sensores recalibrados e alerta resetado." << UI::RESET << endl;
    }

    // Método de instância para exibir dados individuais
    void exibirStatus() const {
        cout << "Sensor ID: " << id << " | Pressão: " << pressaoAtual << " tons ";
        if (pressaoAtual > LIMITE_MAXIMO) 
            cout << UI::VERMELHO << "[SOBRECARGA LOCAL]" << UI::RESET;
        else 
            cout << UI::VERDE << "[OK]" << UI::RESET;
        cout << endl;
    }
};

// --- 3. INICIALIZAÇÃO DE MEMBROS ESTÁTICOS (Obrigatório fora da classe) ---

int SensorPressao::totalSensores = 0;
bool SensorPressao::alertaGeral = false;
const double SensorPressao::LIMITE_MAXIMO = 150.0; // Limite de 150 toneladas

// --- 4. FUNÇÃO PRINCIPAL ---

int main()
{
    cout << fixed << setprecision(2);

    cout << UI::CIANO << "===============================================" << endl;
    cout << "      SISTEMA DE MONITORAMENTO ESTRUTURAL      " << endl;
    cout << "===============================================" << UI::RESET << endl;

    // Criando sensores em diferentes partes do prédio
    SensorPressao s1(101); // Pilar Norte
    SensorPressao s2(102); // Pilar Sul
    SensorPressao s3(103); // Pilar Leste

    cout << "Sensores instalados: " << SensorPressao::getTotalSensores() << endl;
    cout << "Status Global do Edifício: " << (SensorPressao::isSistemaSeguro() ? UI::VERDE + "SEGURO" : UI::VERMELHO + "RISCO") << UI::RESET << endl;

    // Simulando leituras
    cout << "\nIniciando coleta de dados estruturais..." << endl;
    s1.atualizarLeitura(120.5);
    s2.atualizarLeitura(110.0);
    
    s1.exibirStatus();
    s2.exibirStatus();

    // Simulando uma sobrecarga no Sensor 3
    cout << "\n[!] Detectando movimentação de carga pesada no pilar 103..." << endl;
    s3.atualizarLeitura(185.0); // Ultrapassa os 150.0
    s3.exibirStatus();

    // Verificando o estado global (notar que o alerta geral agora afeta a todos)
    cout << "\n--- DIAGNÓSTICO DO SISTEMA CENTRAL ---" << endl;
    if (!SensorPressao::isSistemaSeguro()) {
        cout << UI::VERMELHO << "ALERTA ESTRUTURAL: Edifício em estado de emergência!" << UI::RESET << endl;
        cout << "O Alerta Geral foi ativado por um dos " << SensorPressao::getTotalSensores() << " sensores." << endl;
    }

    // Resetando via método estático
    SensorPressao::resetarSistema();

    return 0;
}

/* 
    ===============================================================
    RESUMO TEÓRICO: MEMBROS ESTÁTICOS (static)
    ===============================================================

    1. ATRIBUTOS ESTÁTICOS:
       - Um membro 'static' é compartilhado por todas as instâncias 
         da classe. Se o objeto A muda o valor, o objeto B vê a 
         mudança instantaneamente.
       - Aplicação: Contadores de objetos, configurações globais ou 
         flags de estado de sistema (como o alertaGeral).

    2. MÉTODOS ESTÁTICOS:
       - Funções que não operam sobre um objeto específico (não 
         possuem o ponteiro 'this'). 
       - Podem ser chamadas usando o nome da classe: Classe::Metodo().
       - Só podem acessar outros membros que também sejam estáticos.

    3. INICIALIZAÇÃO EXTERNA:
       - Atributos estáticos não-constantes devem ser inicializados 
         fora da declaração da classe (no escopo global do arquivo .cpp), 
         pois a memória para eles é alocada apenas uma vez no 
         início da execução do programa.

    4. CONST STATIC:
       - Usado para definir constantes de classe (como o LIMITE_MAXIMO) 
         que economizam memória por não serem replicadas em cada objeto.

    ===============================================================
    ASSUNTOS CORRELATOS (Para pesquisa):
    - Singleton Pattern: Padrão de projeto que usa static para 
      garantir que exista apenas uma instância de uma classe.
    - Ciclo de vida de variáveis estáticas (Static Storage Duration).
    - Métodos 'static' vs Funções 'friend'.
    ===============================================================
*/
