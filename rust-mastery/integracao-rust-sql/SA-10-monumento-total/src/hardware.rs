/**
 * @file hardware.rs
 * @brief Wrapper seguro para drivers de hardware em C++.
 */

/// Interface FFI com o driver C++
mod ffi {
    unsafe extern "C" {
        pub fn iniciar_motores_cpp(potencia: i32) -> i32;
    }
}

/// Tenta iniciar os motores do drone através do driver de hardware.
/// Retorna Ok(()) se o hardware responder com sucesso (1).
pub fn iniciar_ignicao(potencia: i32) -> Result<(), &'static str> {
    let resultado = unsafe { ffi::iniciar_motores_cpp(potencia) };
    
    if resultado == 1 {
        Ok(())
    } else {
        Err("Hardware recusou comando de ignição (Sinal Baixo/Erro de Sensor)")
    }
}
