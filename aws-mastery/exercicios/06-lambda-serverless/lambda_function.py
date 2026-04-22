import json

# @file lambda_function.py
# @brief Handler para processamento de alertas de telemetria.
#
# Demonstra a recepção de eventos JSON e lógica de decisão serverless.

def lambda_handler(event, context):
    """
    Entrada: Evento JSON simulando dados de um sensor de drone.
    Saída: Resposta de processamento de alerta.
    """
    drone_id = event.get('DroneID', 'UNKNOWN')
    bateria = event.get('Bateria', 100)
    
    print(f"[LOG]: Analisando Telemetria do Drone {drone_id}")
    
    status_code = 200
    mensagem = "Voo Nominal: Parâmetros estáveis."
    
    # Lógica de Negócio: Gatilho de Alerta
    if bateria < 20:
        status_code = 400
        mensagem = f"ALERTA CRÍTICO: Drone {drone_id} com {bateria}% de bateria. Retorno à base imediato!"
        print(f"[ALERTA]: {mensagem}")
    
    return {
        'statusCode': status_code,
        'body': json.dumps({
            'servico': 'SkyCargo-Alert-System',
            'resultado': mensagem,
            'drone': drone_id
        })
    }
