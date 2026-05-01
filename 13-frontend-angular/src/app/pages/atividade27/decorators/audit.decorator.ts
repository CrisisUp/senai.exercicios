/**
 * @file audit.decorator.ts
 * @brief Decorator Customizado para Auditoria de Métodos em Sistemas Nexus.
 * @author Cristiano
 * @date 2026
 */

/**
 * @brief Decorator @Audit
 * Intercepta a execução de um método, registra os argumentos de entrada
 * e calcula o tempo de processamento.
 */
export function Audit() {
  return function (
    target: any,
    propertyKey: string,
    descriptor: PropertyDescriptor
  ) {
    const originalMethod = descriptor.value;

    descriptor.value = function (...args: any[]) {
      const startTime = performance.now();
      
      // Log de Início de Execução
      console.log(`%c[AUDIT] Iniciando: ${propertyKey}`, 'color: #f1e05a; font-weight: bold;');
      console.log(`%c[ARGS]:`, 'color: #8b949e;', args);

      // Execução do método original
      const result = originalMethod.apply(this, args);

      const endTime = performance.now();
      const duration = (endTime - startTime).toFixed(4);

      // Log de Conclusão
      console.log(`%c[AUDIT] Concluído: ${propertyKey} | Tempo: ${duration}ms`, 'color: #3fb950; font-weight: bold;');

      return result;
    };

    return descriptor;
  };
}

/* @section ArchitectureMap
 * O Decorator utiliza o pattern 'Proxy/Interception'.
 * Ele substitui a implementação original do método por uma 'wrapper function'
 * que adiciona lógica transversal (Cross-cutting Concerns) sem modificar 
 * a implementação interna do componente.
 */
