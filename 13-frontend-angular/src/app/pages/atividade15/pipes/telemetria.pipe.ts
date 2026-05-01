/**
 * @file telemetria.pipe.ts
 * @brief Pipe Customizado para Transformação de Dados de Telemetria.
 * @author Cristiano
 * @date 2026
 */

import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'telemetria',
  standalone: true
})
export class TelemetriaPipe implements PipeTransform {
  /**
   * @brief Transforma valores numéricos brutos em unidades industriais.
   * @param value O valor original (number).
   * @param unit A unidade de medida (ex: 'km/h', 'm', 'V').
   * @param precision Casas decimais (default: 2).
   */
  transform(value: number | null | undefined, unit: string = '', precision: number = 2): string {
    if (value === null || value === undefined || isNaN(value)) {
      return '---';
    }

    const formatted = value.toFixed(precision);
    
    // Adiciona separador de milhar tático (simplificado para demonstração)
    const parts = formatted.split('.');
    parts[0] = parts[0].replace(/\B(?=(\d{3})+(?!\d))/g, ".");
    
    return `${parts.join(',')} ${unit}`.trim();
  }
}

/* @section ArchitectureMap
 * Pipe 'Pure' por padrão. O Angular executa o transform() apenas 
 * quando o valor de entrada ou os parâmetros mudam, otimizando a performance.
 */
